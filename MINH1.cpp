#include<iostream>
#include<cstring>
#include<iomanip>
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
    PTRSV FirstSV=nullptr;
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

struct DS_LTC 
{
    int n = 0;
    LopTinChi *nodes[MAX_LTC];
};

/*int strcmp(char *s, char *t) { // bang nhau tra ve 0
    while (*s && *t && (*s == *t)) {
        s++;
        t++;
    }
    return (*s - *t); 
}*/
treeMH Insert(treeMH t, MonHoc mh) {
    if (t == nullptr) {
        t = new nodeMH;
        t->mh = mh;
        t->left = nullptr;
        t->right = nullptr;
    }
    if (strcmp(mh.MAMH, t->mh.MAMH) < 0)
        t->left = Insert(t->left, mh);
    else if (strcmp(mh.MAMH, t->mh.MAMH) > 0)
        t->right = Insert(t->right, mh);
    else
        cout << "Ma mon hoc da ton tai. Vui long nhap lai.\n";

    return t;
}
treeMH NhapMonHoc(treeMH t) {
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
    t=Insert(t,mh);
    return t;
}

treeMH minValueNode(treeMH node) {
	treeMH current = node;
	while(current->left) current = current->left;
	return current;
}
treeMH XoaMH(treeMH t, MonHoc mh) {
    if (t == nullptr) {
        cout <<  "Khong tim thay mon hoc de xoa" << endl;
        return;
    }
    if (strcmp(mh.MAMH, t->mh.MAMH) < 0) {
        XoaMH(t->left, mh);
    } else if (strcmp (mh.MAMH, t->mh.MAMH) > 0) {
        XoaMH(t->right, mh);
    }
    else {
        if(!t->left || !t->right) {
            treeMH temp = t->left ? t->left : t->right;

            if(!temp) { 
                temp = t;
                t = nullptr;
            } else {
                *t = *temp;  
            }
            delete temp;
        }
        else {
            treeMH temp = minValueNode(t->right);
            t->mh = temp->mh;
            t->right = XoaMH(t->right, temp->mh);
        }
    }
    return t;
}
void SuaMH (treeMH t, MonHoc mh) {
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

// =========================================================================

void NhapDiem( DS_LTC dsltc, DS_LOPSV dslop) {
    char nienkhoa[10], mamh[11];
    int hocky, nhom;
    cout << "Nhap nien khoa: ";
    cin.getline(nienkhoa,10);
    cout << "Nhap hoc ki: "; cin >> hocky;
    cout << "Nhap nhom: "; cin >> nhom;
    cin.ignore(0);
    cout << "Nhap mon hoc: ";
    cin.getline(mamh,11);
    LopTinChi *ltc = nullptr;
    for(int i = 0; i< dsltc.n; i++) {
        LopTinChi *cur = dsltc.nodes[i];
        if (strcmp(cur->NienKhoa, nienkhoa) == 0 &&
        cur->Hocky == hocky && cur->Nhom == nhom 
        && strcmp(cur->MAMH, mamh) == 0) {
            ltc = cur;
            break; 
        }
    }
    if (ltc == nullptr) {
        cout << "Khong tim thay lop tin chi tuong ung!\n";
        return;
    }
    if (ltc->huylop) {
        cout << "Lop tin chi nay da bi huy, khong the nhap diem!\n";
        return;
    }
    if (ltc->dssvdk == nullptr) {
        cout << "Khong co sinh vien dang ky lop tin chi nay!\n";
        return;
    }
    cout << "\n              -==== DANH SACH SINH VIEN DANG KY ====-";
    cout << left << setw(5) << "STT" << setw(15) << "MASV" << setw(25) << "HO"<<
    setw(15) << "TEN" << setw(10) << "DIEM" << endl;
    cout << "------------------------------------------------\n";
    int stt = 1;
    PTRDK p = ltc->dssvdk;
    while(p != nullptr) {
        SinhVien *sv = nullptr;
        for(int i = 0; i<dslop.n && !sv; i++) {
            PTRSV q = dslop.nodes[i]->FirstSV;
            while (q!= nullptr) {
                if(strcmp(q->sv.MASV, p->dk.MASV) == 0) {
                    sv =&q->sv;
                    break;
                }
                q = q->next;
            }
        }
        if(sv) {
            cout << left << setw(5) << stt++<< setw(15) << sv->MASV<< setw(25) << sv->HO<< setw(15) << sv->TEN
            << setw(10) << fixed << setprecision(2) << p->dk.DIEM;cout << "\nNhap diem moi (-1 de giu nguyen): ";
            float diemMoi;
            cin >>diemMoi;
            if(diemMoi >= 0 && diemMoi <=10) p->dk.DIEM = diemMoi;
        } else {
            cout << setw(5) << stt++<< setw(15) << p->dk.MASV<< setw(25) << "Khong tim thay"
            << setw(15) << ""<< setw(10) << "----" << endl;
        }
        p = p->next;
    }
    cout << "\n==> Da nhap / cap nhat diem thanh cong! <==\n";
}
int main() {

}