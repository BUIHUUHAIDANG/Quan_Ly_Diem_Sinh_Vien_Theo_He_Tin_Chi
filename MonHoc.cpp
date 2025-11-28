#include "MonHoc.h"
#include <fstream>
#include <sstream>
#include <cstring>
#include <algorithm>

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

PTRSV findSinhVien(PTRSV First, char MASV[], PTRSV dssv) {
    First = dssv;
    while (First != nullptr) {
        if (strcmp(First->sv.MASV, MASV) == 0) return First;
        else First = First->next;
    }
    return nullptr;
}

PTRSV findSinhVien(PTRSV First, char MASV[]) {
    SinhVien sv;
    while (First != nullptr) {
        if (strcmp(First->sv.MASV, MASV) == 0)
            return First;
        First = First->next;
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
void LuuMonHoc(treeMH t, string filename) {
    ofstream f(filename, ios::app);
    if (!t) {
        f << "#\n";
        return;
    }

    f << t->mh.MAMH << "|"
      << t->mh.TENMH << "|"
      << t->mh.STCLT << "|"
      << t->mh.STCTH << "|"
      << t->height << "\n";

    LuuMonHoc(t->left, filename);
    LuuMonHoc(t->right, filename);
    f.close();
}

treeMH DocMonHoc(string filename) {
    ifstream f(filename);
    if (!f.is_open()) {
        cout << "Khong mo duoc file!\n";
        return nullptr;
    }

    string line;
    treeMH root = nullptr;
    while (getline(f, line)) {
        if (line == "#" || line.empty()) continue;

        stringstream ss(line);
        MonHoc mh;
        string temp;

        getline(ss, temp, '|'); strcpy(mh.MAMH, temp.c_str());
        getline(ss, temp, '|'); strcpy(mh.TENMH, temp.c_str());
        getline(ss, temp, '|'); mh.STCLT = stoi(temp);
        getline(ss, temp, '|'); mh.STCTH = stoi(temp);

        root = Insert(root, mh);
    }

    f.close();
    return root;
}

// -------------------- HÀM HỖ TRỢ --------------------
bool checkMH(treeMH t, MonHoc mh) {
    if (!t) return false;
    if (strcmp(mh.MAMH, t->mh.MAMH) == 0) return true;
    if (strcmp(mh.MAMH, t->mh.MAMH) < 0) return checkMH(t->left, mh);
    return checkMH(t->right, mh);
}

void NhapMonHoc(treeMH &t, stack &undostackMH) {
    t = DocMonHocFromFile("D:\\MonHocdata.txt");

    while (true) {
        MonHoc mh;
        cout << "Nhap ma mon hoc (nhap 0 de thoat): ";
        cin >> mh.MAMH;
        if (strcmp(mh.MAMH, "0") == 0) break;

        if (checkMH(t, mh)) {
            cout << "Ma mon hoc da ton tai. Vui long nhap lai.\n";
            continue;
        }

        cout << "Nhap ten mon hoc: ";
        cin.ignore();
        cin.getline(mh.TENMH, 51);
        cout << "Nhap so tin chi ly thuyet: ";
        cin >> mh.STCLT;
        cout << "Nhap so tin chi thuc hanh: ";
        cin >> mh.STCTH;

        t = Insert(t, mh);

        LuuMonHocToFile(t, "D:\\MonHocdata.txt");

        cout << "Luu thanh cong!\n\n";

        ActionMH act;
        act.type = 1;
        act.mh = mh;
        push(undostackMH, act);
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
            if (choice < 1 || choice > 3) {
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

void InDSMH(treeMH t) {
    if (!t) return;
    InDSMH(t->left);
    cout << "Ma MH: " << t->mh.MAMH << ", Ten MH: " << t->mh.TENMH << endl;
    InDSMH(t->right);
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

void SVDangKy(PTRDK &dssvdk, PTRSV sv) {
    PTRDK p = new nodeDK;
    strcpy(p->dk.MASV, sv->sv.MASV);
    p->dk.SinhVien = sv;
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
    c = checkmamh(loptinchi, lop.NienKhoa, lop.Hocky);
    if (c == nullptr) {
        return;
    }
    SVDangKy(c->ltc.dssvdk, p); //luu sinh vien dang ky vao danh sach dang ky cua lop tin chi
    c->ltc.currentsv++; //tang so luong sinh vien da dang ky len 1
    cout << "Dang ky thanh cong!" << endl;
}
