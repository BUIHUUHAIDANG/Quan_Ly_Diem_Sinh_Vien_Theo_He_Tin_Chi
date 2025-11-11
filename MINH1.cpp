
#include<iostream>
#include<iomanip>
#include<cstring>
using namespace std;

const int MAX_LOPSV = 10000;
struct MonHoc {
    char MAMH[11] ; char TENMH[51]; 
    int STCLT ,STCTH; int height;
};
struct nodeMH {
    MonHoc mh;
    nodeMH *left, *right;
};
typedef nodeMH* treeMH;

struct SinhVien {
    char MASV [16]; char HO[51] ; char TEN[11];
    char  PHAI[4]; char SODT[16]; char Email [50];

};
struct nodeSV {
    SinhVien sv;
    nodeSV *next;
};
typedef nodeSV* PTRSV;

struct LopSV  {
    char MALOP[16] ; char TENLOP[51];
    PTRSV FirstSV=NULL; 
};
struct DS_LOPSV {
    int n=0;
    LopSV* nodes[MAX_LOPSV];
};
struct DangKy {
    char MASV[16] ; float DIEM; 
};
 
struct nodeDK {
    DangKy dk;
    nodeDK *next;
};
typedef nodeDK* PTRDK;
struct LopTinChi {
    int MALOPTC ;
    char  MAMH[11];
    char NienKhoa[10];  
    int Hocky, Nhom,sosvmin, sosvmax;
    bool huylop = false;
    PTRDK dssvdk=NULL; 
};
struct nodeLTC {
    LopTinChi ltc;
    nodeLTC *next;
};
typedef nodeLTC* PTRLTC;
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

// === save ltc ===

int SaveFile_LTC(const char* tenfile, PTRLTC FirstLTC) {
    FILE *f = fopen(tenfile, "wb");
    if (f == NULL) return 0;

    for (PTRLTC p = FirstLTC; p != NULL; p = p->next) {
        // 
        fwrite(&p->ltc.MALOPTC, sizeof(int), 1, f);
        fwrite(&p->ltc.MAMH, sizeof(p->ltc.MAMH), 1, f);
        fwrite(&p->ltc.NienKhoa, sizeof(p->ltc.NienKhoa), 1, f);
        fwrite(&p->ltc.Hocky, sizeof(int), 1, f);
        fwrite(&p->ltc.Nhom, sizeof(int), 1, f);
        fwrite(&p->ltc.sosvmin, sizeof(int), 1, f);
        fwrite(&p->ltc.sosvmax, sizeof(int), 1, f);
        fwrite(&p->ltc.huylop, sizeof(bool), 1, f);

        // dssv dang ki
        int count = 0;
        for (PTRDK q = p->ltc.dssvdk; q != NULL; q = q->next) count++;
        fwrite(&count, sizeof(int), 1, f);

        for (PTRDK q = p->ltc.dssvdk; q != NULL; q = q->next)
            fwrite(&q->dk, sizeof(DangKy), 1, f);
    }

    fclose(f);
    return 1;
}
// ===
void DeleteDSLTC(PTRLTC FirstLTC) {
    while (FirstLTC != NULL) {
        PTRLTC temp = FirstLTC;
        FirstLTC = FirstLTC->next;

        // giai phong dsdk
        while (temp->ltc.dssvdk != NULL) {
            PTRDK q = temp->ltc.dssvdk;
            temp->ltc.dssvdk = q->next;
            delete q;
        }

        delete temp;
    }
}
void InsertLast_LTC(PTRLTC FirstLTC,LopTinChi ltc) {
    PTRLTC newNode = new nodeLTC;
    newNode->ltc = ltc;
    newNode->next = NULL;

    if (FirstLTC == NULL)
        FirstLTC = newNode;
    else {
        PTRLTC p = FirstLTC;
        while (p->next != NULL) p = p->next;
        p->next = newNode;
    }
}
void InsertLast_DK(PTRDK dssvdk, DangKy dk) {
    PTRDK newNode = new nodeDK;
    newNode->dk = dk;
    newNode->next = NULL;
    if(dssvdk == NULL) dssvdk = newNode;
    else {
        newNode->next = dssvdk;
        dssvdk = newNode; 
    }
}
// === load dslk ltc ===
int LoadFile_LTC(const char* tenfile, PTRLTC FirstLTC) {
    FILE* f = fopen(tenfile, "rb");
    if (f == NULL) return 0;
    DeleteDSLTC(FirstLTC);
    while (1) {
        LopTinChi ltc;
        if (fread(&ltc.MALOPTC, sizeof(int), 1, f) != 1) break;
        fread(&ltc.MAMH, sizeof(ltc.MAMH), 1, f);
        fread(&ltc.NienKhoa, sizeof(ltc.NienKhoa), 1, f);
        fread(&ltc.Hocky, sizeof(int), 1, f);
        fread(&ltc.Nhom, sizeof(int), 1, f);
        fread(&ltc.sosvmin, sizeof(int), 1, f);
        fread(&ltc.sosvmax, sizeof(int), 1, f);
        fread(&ltc.huylop, sizeof(bool), 1, f);

        int count;
        fread(&count, sizeof(int), 1, f);

        ltc.dssvdk = NULL;
        for (int i = 0; i < count; i++) {
            DangKy dk;
            fread(&dk, sizeof(DangKy), 1, f);
            InsertLast_DK(ltc.dssvdk, dk);
        }

        InsertLast_LTC(FirstLTC, ltc);
    }
    fclose(f);
    return 1;
}

void NhapDiem(nodeLTC* dsltc, DS_LOPSV dslop) {
    char nienkhoa[10], mamh[11];
    int hocky, nhom;
    cout << "Nhap nien khoa: ";
    cin.getline(nienkhoa,10);
    cout << "Nhap hoc ki: "; cin >> hocky;
    cout << "Nhap nhom: "; cin >> nhom;
    cin.ignore();
    cout << "Nhap mon hoc: ";
    cin.getline(mamh,11);
    nodeLTC *ltc = nullptr;
    nodeLTC *cur;
    cur = dsltc;
    while(cur) {
        if (strcmp(cur->ltc.NienKhoa, nienkhoa) == 0 &&
        cur->ltc.Hocky == hocky && cur->ltc.Nhom == nhom 
        && strcmp(cur->ltc.MAMH, mamh) == 0) {
            ltc = cur;
            break; 
        }
        cur = cur->next; 
    }
    if (ltc == nullptr) {
        cout << "Khong tim thay lop tin chi tuong ung!\n";
        return;
    }
    if (ltc->ltc.huylop) {
        cout << "Lop tin chi nay da bi huy, khong the nhap diem!\n";
        return;
    }
    if (ltc->ltc.dssvdk == nullptr) {
        cout << "Khong co sinh vien dang ky lop tin chi nay!\n";
        return;
    }
    cout << "\n              -==== DANH SACH SINH VIEN DANG KY ====- \n";
    cout << left << setw(5) << "STT" << setw(15) << "MASV" << setw(25) << "HO"<<
    setw(15) << "TEN" << setw(10) << "DIEM" << endl;
    cout << "------------------------------------------------\n";
    int stt = 1;
    PTRDK p = ltc->ltc.dssvdk;
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
float Tinhdiemtb(SinhVien sv, PTRLTC dsltc, treeMH dsmh) {
    float tongDiem = 0, tongTinChi = 0;

    for (PTRLTC cur = dsltc; cur != nullptr; cur = cur->next) {
        if (cur->ltc.huylop) continue;

        for (PTRDK dk = cur->ltc.dssvdk; dk != nullptr; dk = dk->next) {
            if (strcmp(dk->dk.MASV, sv.MASV) == 0 && dk->dk.DIEM >= 0) {
                // tim tin chi mon
                treeMH p = dsmh;
                int tinchi = 0;
                while (p != nullptr) {
                    int cmp = strcmp(cur->ltc.MAMH, p->mh.MAMH);
                    if (cmp == 0) {
                        tinchi = p->mh.STCLT + p->mh.STCTH;
                        break;
                    }
                    p = (cmp < 0) ? p->left : p->right;
                }
                tongDiem += dk->dk.DIEM * tinchi;
                tongTinChi += tinchi;
                break;
            }
        }
    }
    return (tongTinChi > 0) ? (tongDiem / tongTinChi) : -1; 
}
void Indiemtb(PTRLTC dsltc, DS_LOPSV dslop, treeMH dsmh) {
    char malop[16];
    cout << "Nhap ma lop: ";
    cin.getline(malop, 16);

    LopSV* lop = nullptr;
    for (int i = 0; i < dslop.n; i++) {
        if (strcmp(dslop.nodes[i]->MALOP, malop) == 0) {
            lop = dslop.nodes[i];
            break;
        }
    }
    if (!lop) {
        cout << "Khong tim thay lop!\n";
        return;
    }

    cout << "\n -==== BANG DIEM TRUNG BINH KHOA HOC ====- \n";
    cout << "Lop: " << lop->TENLOP << endl;
    cout << left << setw(5) << "STT" << setw(15) << "MASV"
         << setw(25) << "HO" << setw(15) << "TEN" << setw(10) << "DIEM TB" << endl;
    cout << "-------------------------------------------------------------\n";

    int stt = 1;
    for (PTRSV sv = lop->FirstSV; sv != nullptr; sv = sv->next) {
        float diemTB = Tinhdiemtb(sv->sv, dsltc, dsmh);
        if (diemTB >= 0) {
            cout << left << setw(5) << stt++ << setw(15) << sv->sv.MASV << setw(25) << sv->sv.HO 
            << setw(15) << sv->sv.TEN << setw(10) << fixed << setprecision(2) << diemTB << endl;
        } else {
            cout << left << setw(5) << stt++ << setw(15) << sv->sv.MASV << setw(25) 
            << sv->sv.HO << setw(15) << sv->sv.TEN << setw(10) << "Chua co" << endl;
        }
    }
}
void duyettreeMH(treeMH t, char dsMAMH[][11], int &soMH) {
    if (t == nullptr) return;
    duyettreeMH(t->left, dsMAMH, soMH);
    strcpy(dsMAMH[soMH++], t->mh.MAMH);
    duyettreeMH(t->right, dsMAMH, soMH);

}
void Inbangdiemtongket(PTRLTC dsltc, DS_LOPSV dslop, treeMH dsmh) {
    char dsMAMH[200][11];
    char malop[16];
    int soMH = 0;
    duyettreeMH(dsmh, dsMAMH, soMH);
    if (soMH == 0) {
        cout << "Danh sach mon hoc rong!\n";
        return;
    }

    cout << "Nhap ma lop: ";
    cin.getline(malop,16);
    LopSV* lop = nullptr;
    for (int i = 0; i < dslop.n; i++) {
        if (strcmp(dslop.nodes[i]->MALOP, malop) == 0) {
            lop = dslop.nodes[i];
            break;
        }
    }
    if (!lop) {
        cout << "Khong tim thay lop!\n";
        return;
    }

    cout << " -==== BANG DIEM TONG KET ====- ";
    cout << "Lop: " << lop->TENLOP << endl;
    cout << left << setw(5) << "STT" << setw(15) << "MASV" << setw(25) << "HO TEN";
    for (int i = 0; i < soMH; i++) cout << setw(8) << dsMAMH[i];
    cout << endl;

    int stt = 1;
    for (PTRSV sv = lop->FirstSV; sv != nullptr; sv = sv->next) {
        float diemMax[200];
        for (int i = 0; i < soMH; i++) diemMax[i] = -1;

        for (PTRLTC cur = dsltc; cur != nullptr; cur = cur->next) {
            if (cur->ltc.huylop) continue;

            for (PTRDK dk = cur->ltc.dssvdk; dk != nullptr; dk = dk->next) {
                if (strcmp(dk->dk.MASV, sv->sv.MASV) == 0) {
                    for (int i = 0; i < soMH; i++) {
                        if (strcmp(dsMAMH[i], cur->ltc.MAMH) == 0) {
                            if (dk->dk.DIEM > diemMax[i]) diemMax[i] = dk->dk.DIEM;
                            break;
                        }
                    }
                }
            }
        }
        char hoten[51];
        strcpy(hoten, sv->sv.HO);
        strcat(hoten, " ");
        strcat(hoten, sv->sv.TEN);
        cout << left << setw(5) << stt++ << setw(15) << sv->sv.MASV << setw(25) << hoten;
        for(int i=0; i< soMH; i++) {
            if(diemMax[i] >= 0) {
                cout << setw(8) << fixed << setprecision(2) << diemMax[i];
            } else {
                cout << setw(8) << "-";
            }
            
        }
        cout << endl;
    }

}
int main() {
    treeMH dsmh=NULL;
    PTRLTC dsltc=NULL; 
    DS_LOPSV dslopsv;
    SaveFile_LTC("ltc.txt", FirstLTC);
    LoadFile_LTC("ltc.txt", FirstLTC);
    if (!LoadFile_LTC("ltc.txt", dsltc)) {
        cout << "Khong the mo file ltc.txt (co the chua ton tai)"<< endl;
    }
    cin.ignore();
    Indiemtb(dsltc, dslopsv, dsmh);
}
