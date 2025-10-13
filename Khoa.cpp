#include<iostream>
#include<cstring>
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
    int Hocky, Nhom, sosvmin, sosvmax;
    bool huylop =false;
    PTRDK dssvdk=nullptr;
};

struct nodeLTC 
{
    LopTinChi ltc;
    LopTinChi *nodes[MAX_LTC];
};

void Insert(treeMH &t, MonHoc mh) {
    if (t == nullptr) {
        t = new nodeMH;
        t->mh = mh;
        t->left = nullptr;
        t->right = nullptr;
    } else {
        if (strcmp(mh.MAMH, t->mh.MAMH) < 0) {
            Insert(t->left, mh);
        } else if (strcmp(mh.MAMH, t->mh.MAMH) > 0) {
            Insert(t->right, mh);
        } else {
            cout << "Ma mon hoc da ton tai. Vui long nhap lai." << endl;
        }
    }
}

void NhapMonHoc(treeMH &t) {
    MonHoc mh;
    while (true) {
        cout << "Nhap ma mon hoc (nhap 0 de thoat): ";
        cin >> mh.MAMH;
        if (strcmp(mh.MAMH, "0") == 0) {
            break;
        }
        cout << "Nhap ten mon hoc: ";
        cin.ignore();
        cin.getline(mh.TENMH, 51);
        cout << "Nhap so tin chi ly thuyet: ";
        cin >> mh.STCLT;
        cout << "Nhap so tin chi thuc hanh: ";
        cin >> mh.STCTH;
        mh.height = 1;
        Insert(t, mh);
    }
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
void InDSMH(treeMH t) {
    if (t != nullptr) {
        InDSMH(t->left);
        cout << "Ma MH: " << t->mh.MAMH << ", Ten MH: " << t->mh.TENMH << endl;
        InDSMH(t->right);
    }
}

/*void InLTC (nodeLTC *ltc, treeMH monhoc) {
    if (ltc == nullptr) {
        cout << "Danh sach lop tin chi rong" << endl;
        return;
    } else {
        for (int i = 0; i < MAX_LTC && ltc->nodes[i] != nullptr; i++) { 
            cout << "Ma mon hoc: " << ltc->nodes[i]->MAMH << endl; 
            cout << "Ten mon hoc: " << monhoc->mh->TENMH << endl;
        }
    }
}

void DangKyLTC (nodeLTC *ltc, LopTinChi lop) {
    cout << "Nhap nien khoa: ";
    cin.ignore();
    cin.getline(lop.NienKhoa, 10); 
    cout << "Nhap hoc ky: ";
    cin >> lop.Hocky;
    InLTC(ltc);
}*/

int main () {
    treeMH t = NULL;
    NhapMonHoc(t);
    if (t == nullptr) {
        cout << "Danh sach mon hoc rong." << endl;
    } else {
        InDSMH(t);
    }
    system("pause");
    return 0;
}
