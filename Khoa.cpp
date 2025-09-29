#include<iostream>
using namespace std;

const int MAX_LOPSV = 10000;
const int MAX_LTC=10000;
struct MonHoc
{
    char MAMH[11];
    char TENMH[51];
    int STCLT;
    int STCTH;
    int height;
};
struct nodeMH //tree
{
    MonHoc mh;
    nodeMH *left;
    nodeMH *right;
};
typedef nodeMH* treeMH;
struct SinhVien //tree
{
    char MASV[16];
    char HO[51];
    char TEN[11];
    char PHAI[4];
    char SODT[16];
    char Email[50];
};
struct nodeSV
{
    SinhVien sv;
    nodeSV *next;
};
typedef nodeSV* PTRSV;
struct LopSV
{
    char MALOP[16];
    char TENLOP[51];
    PTRSV FristSV=nullptr;
};
struct DS_LOPSV
{
    int n=0;
    LopSV* nodes[MAX_LOPSV];
};
struct DangKy
{
    char MASV[16];
    float DIEM;
};
struct nodeDK
{
    DangKy dk;
    nodeDK *next;
};
typedef nodeDK* PTRDK;
struct LopTinChi
{
    int MALOPTC;
    char MAMH[11];
    char NienKhoa[10];
    int Hocky,Nhom,sosvmin,sosvmax;
    bool huylop =false;
    PTRDK dssvdk=nullptr;
};

struct nodeLTC 
{
    LopTinChi ltc;
    LopTinChi *nodes[MAX_LTC];
};

int strcmp(char *s, char *t) {
    while (*s && *t && (*s == *t)) {
        s++;
        t++;
    }
    return (*s - *t);
}

treeMH* NhapMonHoc(treeMH &t) {
    MonHoc mh;
    cout << "Nhap ma mon hoc: ";
    cin >> mh.MAMH;
    if (strcmp(mh.MAMH, "0") == 0) return nullptr;
    cout << "Nhap ten mon hoc: ";
    cin.ignore();
    cin.getline(mh.TENMH, 51);
    cout << "Nhap so tin chi ly thuyet: ";
    cin >> mh.STCLT;
    cout << "Nhap so tin chi thuc hanh: ";
    cin >> mh.STCTH;
    mh.height = 1;

    if (t == nullptr) {
        t = new nodeMH;
        t->mh = mh;
        t->left = nullptr;
        t->right = nullptr;
    }
    
    else {
        if (strcmp(mh.MAMH, t->mh.MAMH) < 0) {
            NhapMonHoc(t->left);
        }
        else if (strcmp(mh.MAMH, t->mh.MAMH) > 0) {
            NhapMonHoc(t->right);
        }
        else {
            cout << "Ma mon hoc da ton tai. Vui long nhap lai." << endl;
        }
    }
    return &t;
}

void XoaMH (treeMH &t, MonHoc mh) {
    if (t == nullptr) {
        cout <<  "Khong tim thay mon hoc de xoa" << endl;
        return;
    }
    if (strcmp(mh.MAMH, t->mh.MAMH) < 0) {
        XoaMH(t->left, mh);
    } else if (strcmp (mh.MAMH, t->mh.MAMH) > 0) {
        XoaMH(t->right, mh);
    } else {
        treeMH temp = t;
        if (t->left == nullptr) {
            t = t->right;
        } else if (t->right == nullptr) {
            t = t->left;
        } 
        delete temp;
    }
}

void SuaMH (treeMH &t, MonHoc mh) {
    if (t == nullptr) {
        cout <<  "Khong tim thay mon hoc de sua" << endl;
        return;
    }
    if (strcmp(mh.MAMH, t->mh.MAMH) < 0) {
        SuaMH(t->left, mh);
    } else if (strcmp (mh.MAMH, t->mh.MAMH) > 0) {
        SuaMH(t->right, mh);
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
                cout << "Nhap ten mon hoc moi: ";
                cin.ignore();
                cin.getline(t->mh.TENMH, 51);
                cout << "Sua ten mon hoc thanh cong" << endl;
                continue;
            } else if (choice == 2) {
                cout << "Nhap so tin chi ly thuyet moi: ";
                cin >> t->mh.STCLT;
                cout << "Sua so tin chi ly thuyet thanh cong" << endl;
                continue;
            } else if (choice == 3) {
                cout << "Nhap so tin chi thuc hanh moi: ";
                cin >> t->mh.STCTH;
                cout << "Sua so tin chi thuc hanh thanh cong" << endl;
                continue;
            } else return;
        }
    }
}

//LNR
void InDSMH (treeMH t) {
    if (t == nullptr) {
        cout << "Danh sach mon hoc rong" << endl;
        return;
    } else {
        InDSMH(t->left);
        cout << t->mh.MAMH << endl;
        InDSMH(t->right);  
    }
}
