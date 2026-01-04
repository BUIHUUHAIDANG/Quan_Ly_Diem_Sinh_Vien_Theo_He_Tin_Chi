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
#include "menu.h"
#include "LopSinhVien.h"
#include <conio.h>

using namespace std;

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
treeMH timMonHoc(treeMH t, char mamh[]) {
    if (t == nullptr) return nullptr;
    
    if (strcmp(mamh, t->mh.MAMH) < 0) {
        return timMonHoc(t->left, mamh);
    } else if (strcmp(mamh, t->mh.MAMH) > 0) {
        return timMonHoc(t->right, mamh);
    } else return t;
}

bool Checkkhoangtrang(char s[]) {
    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] == ' ' || s[i] == '\t')
            return true;
    }
    return false;
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
        char tempMAMH[11];
        while (true) {
            gotoxy(22, 6);
            cout << "Ma mon hoc (0 de thoat): ";
            gotoxy(48, 6);
            cout << "          ";
            gotoxy(48, 6);

            cin.getline(tempMAMH, 11);

            if (strcmp(tempMAMH, "0") == 0) return;

            if (strlen(tempMAMH) == 0) {
                gotoxy(22, 25);
                SetColor(4);
                cout << "Ma mon hoc khong duoc de trong!";
                ResetColor();
                continue;
            }

            if (Checkkhoangtrang(tempMAMH)) {
                gotoxy(22, 26);
                SetColor(4);
                cout << "Ma mon hoc khong duoc chua khoang trang!";
                ResetColor();
                continue;
            }   

            if (timMonHoc(t, tempMAMH) != nullptr) {
                gotoxy(22, 27);
                SetColor(4);
                cout << "Ma mon hoc da ton tai!";
                ResetColor();
                continue;
            }
            break;
        }
        strcpy(mh.MAMH, tempMAMH);
        toUpperCase(mh.MAMH);

        // ===== TEN MON HOC =====
        char tempTENMH[51];
        while (true) {
            gotoxy(22, 8);
            cout << "Ten mon hoc: ";
            gotoxy(48, 8);
            cout << string(30, ' ');
            gotoxy(48, 8);

            cin.getline(tempTENMH, 51);

            if (strlen(tempTENMH) == 0) {
                gotoxy(22, 28);
                SetColor(4);
                cout << "Ten mon hoc khong duoc de trong!";
                ResetColor();
                continue;
            }
            break;
        }
        strcpy(mh.TENMH, tempTENMH);

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
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            }

            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            gotoxy(22,29);
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
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            }

            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            gotoxy(22,30);
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


treeMH UndoThemMH (treeMH t, char MAMH[]) {
    MonHoc mh;
    if (t == nullptr) return nullptr;
    
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

treeMH XoaMH (treeMH t, char MAMH[], MonHoc &mhDeleted) {
    MonHoc mh;
    if (t == nullptr) {
        cout <<  "Khong tim thay mon hoc de xoa" << endl;
        return nullptr;
    }
    if (strcmp(MAMH, t->mh.MAMH) < 0) {
        t->left = XoaMH(t->left, MAMH, mhDeleted);
    } else if (strcmp(MAMH, t->mh.MAMH) > 0) {
        t->right = XoaMH(t->right, MAMH, mhDeleted);
    } else {
        if (mhDeleted.MAMH[0] == '\0') mhDeleted = t->mh; //Chỉ lưu lần đần tiên tìm thấy
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
            t->right = XoaMH(t->right, minRight->mh.MAMH, mhDeleted);
        }
    }
    if (t == nullptr) return nullptr; //Nếu cây rồng thì không cần quay
    return CheckandRotation(t);
}

void UndoSuaMH (treeMH &t, MonHoc mh) {
    if (t == nullptr) return;

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
            ActionMH act;
            MonHoc old = t->mh;
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
                act.type = 3;
                act.mh = t->mh;
                
                inputOrKeep(t->mh.TENMH, 51, old.TENMH, "Ten mon hoc");

                Deletespaceandtoupper(t->mh.TENMH);
                UpperFirstCharName(t->mh.TENMH);
                cout << "Sua ten mon hoc thanh cong!\n";
                push(undostackMH, act);
                continue;
            } else if (choice == 2) {
                act.type = 3;
                act.mh = t->mh;

                t->mh.STCLT = inputIntOrKeep(old.STCLT, "So tin chi ly thuyet", false);

                cout << "Sua so tin chi ly thuyet thanh cong" << endl;
                push(undostackMH, act);
                continue;
            } else if (choice == 3) {
                act.type = 3;
                act.mh = t->mh;

                t->mh.STCTH = inputIntOrKeep(old.STCTH, "So tin chi thuc hanh", false);

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

PTRLTC InTrangLTC_UI_Bang(PTRLTC start, char nienkhoa[], int hocky, treeMH t) {
    PTRLTC p = start;
    int dem = 0;

    int x = 2, y = 4, w = 100;

    gotoxy(x + 2, y);
    SetBold(true);
    SetColor(11);
    cout << left
         << setw(10) << "MaLTC"
         << setw(10) << "MaMH"
         << setw(35) << "Ten MH"
         << setw(10)  << "Nhom"
         << setw(10) << "DangKy"
         << setw(20) << "Deadline";
    ResetColor();
    SetBold(false);

    drawLine(x + 1, y + 1, w - 2);

    int row = y + 2;

    while (p != nullptr && dem < 5) {

        if (!p->ltc.huylop &&
            strcmp(p->ltc.NienKhoa, nienkhoa) == 0 &&
            p->ltc.Hocky == hocky) {

            treeMH mh = timMonHoc(t, p->ltc.MAMH);
            if (mh != nullptr) {
                gotoxy(x + 2, row++);
                cout << left
                     << setw(10) << p->ltc.MALOPTC
                     << setw(10) << p->ltc.MAMH
                     << setw(35) << mh->mh.TENMH
                     << setw(10)  << p->ltc.Nhom
                     << setw(10) << (to_string(p->ltc.currentsv) + "/" +
                                     to_string(p->ltc.sosvmax))
                     << setw(20) << p->ltc.deadline;

                dem++;
                if (dem == 5) {
                    p = p->next;
                    break;
                }
            }
        }
        p = p->next;
    }
    return p;
}
PTRLTC TimTrangTruoc(PTRLTC first, PTRLTC curr, char nienkhoa[], int hocky, treeMH t) {
    if (curr == first) return first;

    PTRLTC p = first;
    PTRLTC prevPage = first;
    PTRLTC pageStart = first;

    while (p != nullptr) {
        int dem = 0;
        pageStart = p;

        while (p != nullptr) {
            if (!p->ltc.huylop &&
                strcmp(p->ltc.NienKhoa, nienkhoa) == 0 &&
                p->ltc.Hocky == hocky &&
                timMonHoc(t, p->ltc.MAMH) != nullptr) {

                dem++;
                if (dem == 5) {
                    p = p->next;
                    break;
                }
            }
            p = p->next;
        }

        if (pageStart == curr) {
            return prevPage;
        }

        prevPage = pageStart;
    }

    return first;
}

void InLTC_UI(PTRLTC FirstLTC, char nienkhoa[], int hocky, treeMH t) {
    if (FirstLTC == nullptr) {
        cout << "Danh sach lop tin chi rong!";
        getch();
        return;
    }

    PTRLTC currPage = FirstLTC;
    PTRLTC nextPage = nullptr;

    while (true) {
        clrscr();

        int x = 1, y = 1, w = 104, h = 14;
        DrawBox(x, y, w, h, 7, 0);

        gotoxy(x + 35, y + 1);
        SetBold(true);
        SetColor(14);
        cout << "DANH SACH LOP TIN CHI";
        ResetColor();
        SetBold(false);

        gotoxy(x + 3, y + 2);
        cout << "Nien khoa: " << nienkhoa << " | Hoc ky: " << hocky;

        nextPage = InTrangLTC_UI_Bang(currPage, nienkhoa, hocky, t);

        drawLine(x + 1, y + h - 3, w - 2);
        gotoxy(x + 3, y + h - 2);
        SetColor(10);
        cout << "[A] Truoc   [D] Sau   [ESC] Thoat de nhap ma lop tin chi";
        ResetColor();

        char key = getch();
        if (key == 27) break;

        if ((key == 'd' || key == 'D') && nextPage != nullptr) {
            currPage = nextPage;
        }

        if (key == 'a' || key == 'A') {
            currPage = TimTrangTruoc(FirstLTC, currPage, nienkhoa, hocky, t);
        }
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

bool SVdaDangKy(PTRDK dssvdk, char masv[16]) {
    PTRDK p = dssvdk;
    while (p != nullptr) {
        if (strcmp(p->dk.MASV, masv) == 0 && !p->dk.HuyDK) {
            return true; // da dang ky va chua huy
        }
        p = p->next;
    }
    return false;
}


PTRLTC checkmaltc(PTRLTC loptinchi, char nienkhoa[], int hocky) {
    int maltc;

    while (true) {
        gotoxy(0, 15);
        cout << "Nhap ma lop tin chi (Nhap 0 de thoat): ";
        gotoxy(40, 15);
        cout << "                                                  ";
        gotoxy(40, 15);
        cin >> maltc;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            gotoxy(0, 16);
            cout << "                                                         ";
            gotoxy(0, 16);
            cout << "Gia tri khong hop le! Vui long nhap so nguyen.\n";
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (maltc == 0) return nullptr;

        bool foundMa = false;
        bool foundNK_HK = false;
        bool biHuy = false;
        bool biDay = false;

        PTRLTC p = loptinchi;
        while (p != nullptr) {
            if (p->ltc.MALOPTC == maltc) {
                foundMa = true;

                if (strcmp(p->ltc.NienKhoa, nienkhoa) == 0 &&
                    p->ltc.Hocky == hocky) {

                    foundNK_HK = true;

                    if (p->ltc.huylop) {
                        biHuy = true;
                    }
                    else if (p->ltc.currentsv >= p->ltc.sosvmax) {
                        biDay = true;
                    }
                    else {
                        return p; // hop le hoan toan
                    }
                }
            }
            p = p->next;
        }

        if (!foundMa) {
            gotoxy(0, 16);
            cout << "                                                         ";
            gotoxy(0, 16);
            cout << "Khong ton tai ma lop tin chi nay!\n";
        }
        else if (!foundNK_HK) {
            gotoxy(0, 16);
            cout << "                                                         ";
            gotoxy(0, 16);
            cout << "Ma lop tin chi khong thuoc nien khoa hoac hoc ky nay!\n";
        }
        else if (biHuy) {
            gotoxy(0, 16);
            cout << "                                                         ";
            gotoxy(0, 16);
            cout << "Lop tin chi nay da bi huy!\n";
        }
        else if (biDay) {
            gotoxy(0, 16);
            cout << "                                                         ";
            gotoxy(0, 16);
            cout << "Lop tin chi nay da du so luong sinh vien!\n";
        }
        else {
            gotoxy(0, 16);
            cout << "                                                         ";
            gotoxy(0, 16);
            cout << "Du lieu lop tin chi khong hop le!\n";
        }   
    }
}

bool formatNK(char nk[]) {
    return strlen(nk) == 9 && nk[4] == '-';
}

void DangKyLTC(PTRLTC loptinchi, LopTinChi lop, treeMH t, DS_LOPSV dslop) {
    PTRSV p = nullptr;
    char masv[16];
    char malop[16];
    
    PTRSV First = nullptr;   
    while (true) {
        gotoxy(0, 0);
        cout << "                                                                 ";
        gotoxy(0, 1);
        cout << "                                                                 ";
        gotoxy(0, 0);
        cout << "Nhap ma so sinh vien (Nhap 0 de thoat): ";
        cin.getline(masv, 16);

        if (strlen(masv) == 0) {
            gotoxy(0, 2);
            cout << "                                                        ";
            gotoxy(0, 2);
            cout << "Loi: Khong duoc de trong!\n";
            continue;
        } 

        if (strcmp(masv, "0") == 0) return;
        toUpperCase(masv);

        gotoxy(0, 2);
        cout << "                                                        ";
        gotoxy(0, 1);
        cout << "Nhap ma lop sinh vien: ";
        cin.getline(malop, 16);

        if (strlen(malop) == 0) {
            gotoxy(0, 2);
            cout << "                                                        ";
            gotoxy(0, 2);
            cout << "Loi: Khong duoc de trong!\n";
            continue;
        } 
        toUpperCase(malop);

        First = GetLop(dslop, malop);
        if (First == nullptr) {
            gotoxy(0, 2);
            cout << "                                                        ";
            gotoxy(0, 2);
            cout << "Ma lop sinh vien khong ton tai, vui long kiem tra lai!" << endl;
            continue;
        } else {
            if ((p = getSinhVienv2(First, masv)) != nullptr) {
                gotoxy(0, 2);
                cout << "                                                        ";
                gotoxy(0, 2);
                cout << "Ho:" << p->sv.HO << endl <<
                "Ten: " << p->sv.TEN << endl << 
                "Phai:" << p->sv.PHAI << endl <<
                "So dien thoai: " << p->sv.SODT << endl <<
                "Email: " << p->sv.Email << endl;

                while (true) {
                    cout << "Nhap Nien Khoa: ";
                    cin.getline(lop.NienKhoa, 10);

                    if (strlen(lop.NienKhoa) == 0) {
                            cout << "Loi: Khong duoc de trong!\n";
                    } 
                    else if (!formatNK(lop.NienKhoa)) {
                        cout << "Nien khoa khong dung dinh dang (VD: 2025-2026)!\n";
                    } 
                    else {            
                        break;
                    }
                }
            
                while (true) {
                    cout << "Nhap Hoc Ky: ";
                    cin >> lop.Hocky;
            
                    if (!cin.fail() && lop.Hocky > 0 && lop.Hocky <=3) {
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        break;
                    }
            
                    cout << "Loi! Hay nhap so nguyen > 0\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }

                InLTC_UI(loptinchi, lop.NienKhoa, lop.Hocky, t);

                PTRLTC c = nullptr;
                c = checkmaltc(loptinchi, lop.NienKhoa, lop.Hocky);

                if (c == nullptr) {
                    return;
                }

                if (SVdaDangKy(c->ltc.dssvdk, p->sv.MASV)) {
                    cout << "Sinh vien da dang ky lop tin chi nay roi!\n";
                    return;
                }

                SVDangKy(c->ltc.dssvdk, p); 
                c->ltc.currentsv++;

                cout << "Dang ky thanh cong!" << endl;
                cout << "Nhan phim bat ky de quay lai...";
                getch();
                return;
            } else {
                cout << "Ma so sinh vien khong ton tai trong lop, vui long kiem tra lai!" << endl;
                continue;
            }
        }
    }
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