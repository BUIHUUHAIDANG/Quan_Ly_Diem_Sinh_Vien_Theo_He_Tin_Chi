#include "MonHoc.h"
#include "CTDL.h"
#include <cstring>
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <string>
#include <fstream>      
#include <sstream>   
#include <limits> 
#include "mylib.h"
#include <conio.h>

using namespace std;

// -------------------- HÀM AVL --------------------
int GetHeight(treeMH t) { 
    return t ? t->height : 0; 
}

int GetBalance(treeMH t) { 
    return t ? (GetHeight(t->left) - GetHeight(t->right)) : 0; 
}

treeMH RotateRight(treeMH y) {
    treeMH x = y->left;
    treeMH T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(GetHeight(y->left), GetHeight(y->right)) + 1;
    x->height = max(GetHeight(x->left), GetHeight(x->right)) + 1;

    return x;
}

treeMH RotateLeft(treeMH x) {
    treeMH y = x->right;
    treeMH T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(GetHeight(x->left), GetHeight(x->right)) + 1;
    y->height = max(GetHeight(y->left), GetHeight(y->right)) + 1;

    return y;
}

treeMH CheckandRotation(treeMH t) {
    if (!t) return nullptr;

    t->height = 1 + max(GetHeight(t->left), GetHeight(t->right));
    int balance = GetBalance(t);

    if (balance > 1 && GetBalance(t->left) >= 0)
        return RotateRight(t);

    if (balance < -1 && GetBalance(t->right) <= 0)
        return RotateLeft(t);

    if (balance > 1 && GetBalance(t->left) < 0) {
        t->left = RotateLeft(t->left);
        return RotateRight(t);
    }

    if (balance < -1 && GetBalance(t->right) > 0) {
        t->right = RotateRight(t->right);
        return RotateLeft(t);
    }

    return t;
}

void init(stack &s) {
    s.top = nullptr;
}

bool empty(stack s) {
    return s.top == nullptr;
}

void push(stack &s, ActionMH action) {
    PTRNode newNode = new node;
    newNode->data = action;
    newNode->next = s.top;
    s.top = newNode;
}

void pop(stack &s) {
    if (empty(s)) return;
    PTRNode temp = s.top;
    s.top = s.top->next;
    delete temp;
}

ActionMH top(stack s) {
    return s.top->data; 
}

//tim sinh vien trong danh sach sinh vien toan truong
PTRSV findSinhVien(PTRSV First, char MASV[], PTRSV dssv) {
    First = dssv;
    while (First != nullptr) {
        if (strcmp(First->sv.MASV, MASV) == 0) return First;
        else First = First->next;
    }
    return nullptr;
}

treeMH Insert(treeMH t, MonHoc mh) {
    if (!t) {
        t = new nodeMH;
        t->mh = mh;
        t->left = t->right = nullptr;
        t->height = 1;
        return t;
    }

    if (strcmp(mh.MAMH, t->mh.MAMH) < 0)
        t->left = Insert(t->left, mh);
    else if (strcmp(mh.MAMH, t->mh.MAMH) > 0)
        t->right = Insert(t->right, mh);
    else return t;

    return CheckandRotation(t);
}
// -------------------- HÀM FILE --------------------
void WriteNode(FILE* f, treeMH node) {
    if (node == nullptr) {
        int flag = -1; // node rỗng
        fwrite(&flag, sizeof(int), 1, f);
        return;
    }

    int flag = 1; // node có dữ liệu
    fwrite(&flag, sizeof(int), 1, f);

    fwrite(&node->mh, sizeof(MonHoc), 1, f);
    fwrite(&node->height, sizeof(int), 1, f);

    WriteNode(f, node->left);
    WriteNode(f, node->right);
}


void LuuMonHoc(treeMH t, const string &filename) {
    FILE* f = fopen(filename.c_str(), "wb");
    if (f == nullptr) {
        cout << "Khong mo duoc file de ghi!\n";
        return;
    }

    WriteNode(f, t);

    fclose(f);
}


treeMH ReadNode(FILE* f) {
    int flag;
    size_t bytes = fread(&flag, sizeof(int), 1, f);

    if (bytes == 0 || flag == -1) {  // hết file hoặc node rỗng
        return nullptr;
    }

    // đọc dữ liệu node
    MonHoc mh;
    int height;

    fread(&mh, sizeof(MonHoc), 1, f);
    fread(&height, sizeof(int), 1, f);

    // tạo node mới
    treeMH node = new nodeMH;
    node->mh = mh;
    node->height = height;
    node->left = nullptr;
    node->right = nullptr;

    // đọc tiếp cây con trái/phải
    node->left = ReadNode(f);
    node->right = ReadNode(f);

    return node;
}

treeMH DocMonHoc(const string &filename) {
    FILE* f = fopen(filename.c_str(), "rb");
    if (f == nullptr) {
        cout << "Khong mo duoc file de doc!\n";
        return nullptr;
    }

    treeMH root = ReadNode(f);

    fclose(f);
    return root;
}
void Deletespaceandtoupper (char s[]) {
    int left = 0;
    int i = 0;
    int n=strlen(s);
    while (i < n) {
        while (i < n && s[i] == ' ') i++;
        if (i >= n) break;

        while (i < n && s[i] != ' ') {
            s[left++] = s[i++];
        }
        s[left++] = ' ';
    }
    if (left > 0) left--;
    s[left] = '\0';
}

void UpperFirstCharName(char s[]) {
    if (s[0] == '\0') return;

    s[0] = toupper(s[0]);

    for (int i = 1; i < strlen(s); i++) {
        if (s[i - 1] == ' ' && s[i] != ' ') {
            s[i] = toupper(s[i]);
        } else s[i] = tolower(s[i]);
    }
}

// -------------------- HÀM HỖ TRỢ --------------------
bool checkMH(treeMH t, MonHoc mh) {
    if (!t) return false;
    if (strcmp(mh.MAMH, t->mh.MAMH) == 0) return true;
    if (strcmp(mh.MAMH, t->mh.MAMH) < 0) return checkMH(t->left, mh);
    return checkMH(t->right, mh);
}

void NhapMonHoc(treeMH &t, stack &undostackMH) {
    while (true) {
        MonHoc mh;

        clrscr();
        DrawBox(20, 3, 60, 20, 3);
        gotoxy(35, 4);
        SetBold(true);
        SetColor(14);
        cout << "NHAP MON HOC";
        ResetColor();
        SetBold(false);

        // ===== MA MON HOC =====
        while (true) {
            gotoxy(22, 6);
            cout << "Ma mon hoc (0 de thoat): ";
            gotoxy(48, 6);
            cout << "          ";
            gotoxy(48, 6);

            cin.getline(mh.MAMH, 11);

            if (strcmp(mh.MAMH, "0") == 0) return;

            if (strlen(mh.MAMH) == 0) {
                gotoxy(22, 15);
                SetColor(4);
                cout << "Ma mon hoc khong duoc de trong!";
                ResetColor();
                continue;
            }

            if (checkMH(t, mh)) {
                gotoxy(22, 15);
                SetColor(4);
                cout << "Ma mon hoc da ton tai!";
                ResetColor();
                continue;
            }
            break;
        }

        // ===== TEN MON HOC =====
        while (true) {
            gotoxy(22, 8);
            cout << "Ten mon hoc: ";
            gotoxy(48, 8);
            cout << string(30, ' ');
            gotoxy(48, 8);

            cin.getline(mh.TENMH, 51);

            if (strlen(mh.TENMH) == 0) {
                gotoxy(22, 15);
                SetColor(4);
                cout << "Ten mon hoc khong duoc de trong!";
                ResetColor();
                continue;
            }
            break;
        }

        Deletespaceandtoupper(mh.TENMH);
        UpperFirstCharName(mh.TENMH);

        // ===== STCLT =====
        int tempLT;
        while (true) {
            gotoxy(22,10);
            cout << "So TC ly thuyet: ";
            gotoxy(48,10);
            cout << "     ";
            gotoxy(48,10);

            
            cin >> tempLT;

            if (!cin.fail() && tempLT > 0) {
                cin.ignore(1000, '\n');
                break;
            }

            cin.clear();
            cin.ignore(1000, '\n');
            gotoxy(22,15);
            SetColor(4);
            cout << "STCLT phai la so nguyen > 0!";
            ResetColor();
        }

        mh.STCLT = tempLT;

        // ===== STCTH =====
        int tempTH;
        while (true) {
            gotoxy(22,12);
            cout << "So TC thuc hanh: ";
            gotoxy(48,12);
            cout << "     ";
            gotoxy(48,12);

            cin >> tempTH;

            if (!cin.fail() && tempTH > 0) {
                cin.ignore(1000, '\n');
                break;
            }

            cin.clear();
            cin.ignore(1000, '\n');
            gotoxy(22,15);
            SetColor(4);
            cout << "STCTH phai la so nguyen > 0!";
            ResetColor();
        }

        mh.STCTH = tempTH;

        // ===== INSERT + SAVE =====
        t = Insert(t, mh);
        LuuMonHoc(t, "MonHocdata.txt");

        ActionMH act;
        act.type = 1;
        act.mh = mh;
        push(undostackMH, act);

        // ===== THONG BAO =====
        gotoxy(22,15);
        SetColor(10);
        cout << "Them mon hoc thanh cong!";
        ResetColor();

        gotoxy(22,17);
        cout << "Nhan phim bat ky de tiep tuc...";
        getch();
    }
}


treeMH UndoThemMH (treeMH &t, char MAMH[]) {
    MonHoc mh;
    if (t == nullptr) {
        cout <<  "Khong tim thay mon hoc de xoa" << endl;
        return nullptr;
    }
    if (strcmp(MAMH, t->mh.MAMH) < 0) {
        t->left = UndoThemMH(t->left, MAMH);
    } else if (strcmp(MAMH, t->mh.MAMH) > 0) {
        t->right = UndoThemMH(t->right, MAMH);
    } else {
        if (t->left == nullptr && t->right == nullptr) {
            delete t;
            return nullptr;
        } else if (t->left == nullptr) {
            treeMH temp = t->right;
            delete t;
            return temp;
        } else if (t->right == nullptr) {
            treeMH temp = t->left;
            delete t;
            return temp;
        } else if (t->left != nullptr && t->right != nullptr) {
            //Node có 2 cây con -> tìm node nhỏ nhất bên phải để xóa
            treeMH minRight = t->right;
            while (minRight->left != nullptr) {
                minRight = minRight->left;
            }
            t->mh = minRight->mh;
            t->right = UndoThemMH(t->right, minRight->mh.MAMH);
        }
    }
    if (t == nullptr) return nullptr; //Nếu cây rồng thì không cần quay
    return CheckandRotation(t);
}

treeMH XoaMH (treeMH &t, char MAMH[], stack &undostackMH) {
    MonHoc mh;
    if (t == nullptr) {
        cout <<  "Khong tim thay mon hoc de xoa" << endl;
        return nullptr;
    }
    if (strcmp(MAMH, t->mh.MAMH) < 0) {
        t->left = XoaMH(t->left, MAMH, undostackMH);
    } else if (strcmp(MAMH, t->mh.MAMH) > 0) {
        t->right = XoaMH(t->right, MAMH, undostackMH);
    } else {
        if (t->left == nullptr && t->right == nullptr) {
            delete t;
            return nullptr;
        } else if (t->left == nullptr) {
            treeMH temp = t->right;
            delete t;
            return temp;
        } else if (t->right == nullptr) {
            treeMH temp = t->left;
            delete t;
            return temp;
        } else if (t->left != nullptr && t->right != nullptr) {
            //Node có 2 cây con -> tìm node nhỏ nhất bên phải để xóa
            treeMH minRight = t->right;
            while (minRight->left != nullptr) {
                minRight = minRight->left;
            }
            t->mh = minRight->mh;
            t->right = XoaMH(t->right, minRight->mh.MAMH, undostackMH);
        }
    }
    if (t == nullptr) return nullptr; //Nếu cây rồng thì không cần quay
    return CheckandRotation(t);
    ActionMH act;
    act.type = 2;
    act.mh = t->mh;
    push(undostackMH, act);
}

void UndoSuaMH (treeMH &t, MonHoc mh) {
    if (strcmp(mh.MAMH, t->mh.MAMH) < 0) {
        UndoSuaMH(t->left, mh);
    } else if (strcmp(mh.MAMH, t->mh.MAMH) > 0) {
        UndoSuaMH(t->right, mh);
    } else {
        t->mh = mh;
        return;
    }
}

void SuaMH (treeMH &t, MonHoc mh, stack &undostackMH) {
    if (t == nullptr) {
        cout <<  "Khong tim thay mon hoc de sua" << endl;
        return;
    }
    if (strcmp(mh.MAMH, t->mh.MAMH) < 0) {
        SuaMH(t->left, mh, undostackMH);
    } else if (strcmp (mh.MAMH, t->mh.MAMH) > 0) {
        SuaMH(t->right, mh, undostackMH);
    } else {
        while (true) {
            cout << "Ban muon sua thong tin gi:" << endl;
            cout << "1. Ten mon hoc" << endl;
            cout << "2. So tin chi ly thuyet" << endl;
            cout << "3. So tin chi thuc hanh" << endl;
            cout << "4. Thoat" << endl;
            int choice;
            cout << "Nhap lua chon cua ban: ";
            cin >> choice;
            if (choice < 1 || choice > 4) {
                cout << "Lua chon khong hop le" << endl;
                continue;
            } else if (choice == 1) {
                ActionMH act;
                act.type = 3;
                act.mh = t->mh;
                cout << "Nhap ten mon hoc moi: ";
                cin.ignore();
                cin.getline(t->mh.TENMH, 51);
                cout << "Sua ten mon hoc thanh cong" << endl;
                push(undostackMH, act);
                continue;
            } else if (choice == 2) {
                ActionMH act;
                act.type = 3;
                act.mh = t->mh;
                cout << "Nhap so tin chi ly thuyet moi: ";
                cin >> t->mh.STCLT;
                cout << "Sua so tin chi ly thuyet thanh cong" << endl;
                push(undostackMH, act);
                continue;
            } else if (choice == 3) {
                ActionMH act;
                act.type = 3;
                act.mh = t->mh;
                cout << "Nhap so tin chi thuc hanh moi: ";
                cin >> t->mh.STCTH;
                cout << "Sua so tin chi thuc hanh thanh cong" << endl;
                push(undostackMH, act);
                continue;
            } else return;
        }
    }
}

void UndoMH (treeMH &t, stack &undostackMH) {
    MonHoc mh;
    if (empty(undostackMH)) {
        cout << "Khong co thao tac de hoan tac." << endl;
        return;
    }

    ActionMH act = top(undostackMH);
    pop(undostackMH);

    if (act.type == 1) {
        t = UndoThemMH(t, act.mh.MAMH);
        cout << "Hoan tac them mon hoc thanh cong." << endl;
    } else if (act.type == 2) {
        t = Insert(t, act.mh);
        cout << "Hoan tac xoa mon hoc thanh cong." << endl;
    } else if (act.type == 3) {
        UndoSuaMH(t, act.mh);
        cout << "Hoan tac sua mon hoc thanh cong." << endl;
    }
}
void LuuMH_Inorder(treeMH t, MonHoc ds[], int &n) {
    if (!t) return;

    LuuMH_Inorder(t->left, ds, n);
    ds[n++] = t->mh;
    LuuMH_Inorder(t->right, ds, n);
}
void In1TrangMH(MonHoc ds[], int n, int page, int pageSize) {
    int start = (page - 1) * pageSize;
    int end = start + pageSize;
    if (end > n) end = n;

    int x = 5;
    int y = 4;
    int w = 70;
    gotoxy(x + 2, y);
    SetBold(true);
    SetColor(11);
    cout << left
         << setw(5)  << "STT"
         << setw(12) << "MaMH"
         << setw(40) << "Ten Mon Hoc";
    ResetColor();
    SetBold(false);

    drawLine(x + 1, y + 1, w - 2);

    int row = y + 2;
    for (int i = start; i < end; i++) {
        gotoxy(x + 2, row++);
        cout << left
             << setw(5)  << (i + 1)
             << setw(12) << ds[i].MAMH
             << setw(40) << ds[i].TENMH;
    }
}


void InDSMH(treeMH t) {
    if (!t) {
        cout << "Danh sach mon hoc rong!";
        getch();
        return;
    }

    MonHoc ds[500];
    int n = 0;

    LuuMH_Inorder(t, ds, n);

    int pageSize = 5;
    int page = 1;
    int totalPage = (n + pageSize - 1) / pageSize;

    while (true) {
        clrscr();

        int x = 3;
        int y = 1;
        int w = 76;
        int h = pageSize + 9;

        DrawBox(x, y, w, h, 7, 0);

        gotoxy(x + 25, y + 1);
        SetBold(true);
        SetColor(14);
        cout << "DANH SACH MON HOC";
        ResetColor();
        SetBold(false);

        In1TrangMH(ds, n, page, pageSize);

        drawLine(x + 1, y + h - 3, w - 2);
        gotoxy(x + 2, y + h - 2);
        SetColor(10);
        cout << "Trang " << page << "/" << totalPage
             << "   [A] Truoc   [D] Sau   [ESC] Thoat";
        ResetColor();

        char key = getch();

        if (key == 27) break;
        if ((key == 'd' || key == 'D') && page < totalPage) page++;
        if ((key == 'a' || key == 'A') && page > 1) page--;
    }
}

treeMH timMonHoc(treeMH t, char mamh[]) {
    MonHoc mh;
    if (t == nullptr) {
        return nullptr;
    }
    
    if (strcmp(mamh, t->mh.MAMH) < 0) {
        return timMonHoc(t->left, mamh);
    } else if (strcmp(mamh, t->mh.MAMH) > 0) {
        return timMonHoc(t->right, mamh);
    } else return t;
}

void InLTC(PTRLTC loptinchi, char nienkhoa[], int hocky, treeMH t) {
    LopTinChi ltc;
    MonHoc mh;
    if (loptinchi == nullptr) {
        cout << "Danh sach lop tin chi rong" << endl;
        return;
    } 
    
    PTRLTC p = loptinchi;
    while (p != nullptr) {
        if (strcmp(p->ltc.NienKhoa, nienkhoa) == 0 && p->ltc.Hocky == hocky) {
            treeMH found = timMonHoc(t, p->ltc.MAMH);
            if (found != nullptr) {
                cout << "Ma mon hoc: " << p->ltc.MAMH << endl;
                cout << "Ten mon hoc: " << found->mh.TENMH << endl;
                cout << "Nhom: " << p->ltc.Nhom << endl;
                cout << "So sinh vien da dang ky: " << p->ltc.currentsv << endl;
                cout << "So slot con trong: " << (p->ltc.sosvmax - p->ltc.currentsv) << endl;
                cout << "------------------------------\n";
            }
        }
        p = p->next;
    }
}

//luu sinh vien dang ky vao danh sach dang ky cua lop tin chi
void SVDangKy(PTRDK &dssvdk, PTRSV sv) {
    PTRDK p = new nodeDK;
    strcpy(p->dk.MASV, sv->sv.MASV);
    p->dk.DIEM = 0;
    p->dk.HuyDK = false;
    p->next = nullptr;

    if (dssvdk == nullptr) {
        dssvdk = p;
    } else {
        PTRDK tmp = dssvdk;
        while(tmp->next != nullptr) tmp = tmp->next;
        tmp->next = p;
    }
}

//kiem tra ma mon hoc co ton tai khong
PTRLTC checkmamh(PTRLTC loptinchi, char nienkhoa[], int hocky) {
    LopTinChi ltc;
    cout << "Nhap ma mon hoc (Nhap 0 de thoat): ";
    char mamh[11];
    cin >> mamh;
    if (strcmp(mamh, "0") == 0) return nullptr;
    PTRLTC p = loptinchi;
    while (p != nullptr) {
        if (strcmp(p->ltc.MAMH, mamh) == 0 && strcmp(p->ltc.NienKhoa, nienkhoa) == 0 && p->ltc.Hocky == hocky) {
            return p;
        }
        p = p->next;
    }
    cout << "Khong tim thay ma mon hoc vua nhap, vui long kiem tra lai!" << endl;
    return checkmamh(loptinchi, nienkhoa, hocky);
}
PTRLTC checkmaltc(PTRLTC loptinchi, char nienkhoa[], int hocky) {
    LopTinChi ltc;
    cout << "Nhap ma lop tin chi (Nhap 0 de thoat): ";
    int maltc;
    cin >> maltc;
    if (maltc == 0) return nullptr;
    PTRLTC p = loptinchi;
    while (p != nullptr) {
        if ((p->ltc.MALOPTC == maltc) && strcmp(p->ltc.NienKhoa, nienkhoa) == 0 && p->ltc.Hocky == hocky && !p->ltc.huylop) {
            return p;
        }
        p = p->next;
    }
    cout << "Khong tim thay ma lop tin chi vua nhap hoac ma lop tin chi da het han, vui long kiem tra lai!" << endl;
    return checkmaltc(loptinchi, nienkhoa, hocky);
}
void DangKyLTC(PTRLTC loptinchi, LopTinChi lop, treeMH t, PTRSV dssv) {
    PTRSV p = nullptr;
    PTRSV First = nullptr;
    char masv[16];
    cout << "Nhap ma so sinh vien: ";
    cin.ignore();
    cin.getline(masv, 16);
    
    if ((p = findSinhVien(First, masv, dssv)) != nullptr) {
        cout << "Ho:" << p->sv.HO << endl <<
            "Ten: " << p->sv.TEN << endl << 
            "Phai:" << p->sv.PHAI << endl <<
            "So dien thoai: " << p->sv.SODT << endl <<
            "Email: " << p->sv.Email << endl;
    } else {
        cout << "Khong tim thay sinh vien" << endl;
        return;
    }
    
    cout << "Nhap nien khoa: ";
    cin >> lop.NienKhoa;
    cout << "Nhap hoc ky: ";
    cin >> lop.Hocky;
    InLTC(loptinchi, lop.NienKhoa, lop.Hocky, t);
    PTRLTC c = nullptr;
    c = checkmaltc(loptinchi, lop.NienKhoa, lop.Hocky);
    if (c == nullptr) {
        return;
    }
    SVDangKy(c->ltc.dssvdk, p); 
    c->ltc.currentsv++; //tang so luong sinh vien da dang ky len 1
    cout << "Dang ky thanh cong!" << endl;
}

void ClearTree(treeMH &t) {
    if (t == nullptr) return;

    ClearTree(t->left);
    ClearTree(t->right);

    delete t;
    t = nullptr;
}

void ClearStackMH(stack &st) {
    while (st.top != nullptr) {
        node* temp = st.top;
        st.top = st.top->next;
        delete temp;
    }
}
treeMH getMH(treeMH &t, MonHoc mh, stack &undostackMH) {
    if (t == nullptr) return nullptr;

    if (strcmp(mh.MAMH, t->mh.MAMH) < 0)
        getMH(t->left, mh, undostackMH);
    else if (strcmp(mh.MAMH, t->mh.MAMH) > 0)
        getMH(t->right, mh, undostackMH);
    
    return t;
}

void SuaTenMH(treeMH t, stack &undostackMH) {
    ActionMH act;
    act.type = 3;
    act.mh = t->mh;   // lưu TRẠNG THÁI CŨ

    char tenMoi[51];
    while (true) {
        gotoxy(25, 18);
        cout << "Ten mon hoc moi: ";
        gotoxy(45, 18);
        cout << string(30, ' ');
        gotoxy(45, 18);

        cin.getline(tenMoi, 51);
        if (strlen(tenMoi) == 0) continue;
        break;
    }

    Deletespaceandtoupper(tenMoi);
    UpperFirstCharName(tenMoi);
    strcpy(t->mh.TENMH, tenMoi);

    push(undostackMH, act);

    LuuMonHoc(t, "MonHocdata.txt");

    gotoxy(8, 6 + 4 * 2 + 2);
    SetColor(10);
    cout << "Cap nhat thanh cong! Nhan phim bat ky...";
    ResetColor();
    getch();
}

void SuaSTCLT(treeMH t, stack &undostackMH) {
    ActionMH act;
    act.type = 3;
    act.mh = t->mh;

    while (true) {
        gotoxy(25, 18);
        cout << "So tin chi LT moi: ";
        cin >> t->mh.STCLT;

        if (!cin.fail() && t->mh.STCLT > 0) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    push(undostackMH, act);

    LuuMonHoc(t, "MonHocdata.txt");

    gotoxy(8, 6 + 4 * 2 + 2);
    SetColor(10);
    cout << "Cap nhat thanh cong! Nhan phim bat ky...";
    ResetColor();
    getch();
}

void SuaSTCTH(treeMH t, stack &undostackMH) {
    ActionMH act;
    act.type = 3;
    act.mh = t->mh;

    while (true) {
        gotoxy(25, 18);
        cout << "So tin chi TH moi: ";
        cin >> t->mh.STCTH;

        if (!cin.fail() && t->mh.STCTH > 0) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    push(undostackMH, act);

    LuuMonHoc(t, "MonHocdata.txt");

    gotoxy(8, 6 + 4 * 2 + 2);
    SetColor(10);
    cout << "Cap nhat thanh cong! Nhan phim bat ky...";
    ResetColor();
    getch();
}