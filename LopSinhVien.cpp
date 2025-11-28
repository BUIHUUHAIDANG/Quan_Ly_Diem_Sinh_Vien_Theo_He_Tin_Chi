#include "LopSinhVien.h"
#include "CTDL.h"
#include <cstring>
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <string>
#include <fstream>      
#include <sstream>   
#include <limits>  


using namespace std;

bool isEmpty(PTRLTC &First){ return First == nullptr; }
int deleteFirst(PTRLTC &First){
    if(isEmpty(First)) return 0;
    PTRLTC p = First;
    First = p->next;
    delete p;
    return 1;
}
PTRSV GetLop(DS_LOPSV &dslop, char malop[]) {
    PTRSV FirstSV = nullptr;
    for(int i=0; i<dslop.n; i++) {
        if(strcmp(malop,dslop.nodes[i]->MALOP) == 0) {
            FirstSV = dslop.nodes[i]->FirstSV;
            break;
        }
    }
    return FirstSV;
}
void InDSSV(DS_LOPSV &dslop, char MALOP[]) {
    SinhVien sv;
    PTRSV FirstSV = GetLop(dslop,MALOP);
    if(!FirstSV) {
        cout << "\n\nDanh sach sinh vien rong!";
        return;
    }
    cout << "Chi tiet danh sach sinh vien cua lop" << MALOP <<"\n";
    cout << left  << setw(15) << "MASV" << setw(25) << "HO" << setw(15) << "TEN" << setw(10) << "PHAI"
    << setw(20) << "SO DT" << setw(30) << "Email" << endl;
    cout << "---------------------------------------------------------------------------------------------------------\n";
    for(PTRSV p = FirstSV; p!= nullptr; p=p->next) {
        
        cout << left  << setw(15) << p->sv.MASV << setw(25) << p->sv.HO << setw(15) << p->sv.TEN 
        << setw(10) << p->sv.PHAI << setw(20) << p->sv.SODT << setw(30) << p->sv.Email << endl;
    }
}
void InDSLTC(PTRLTC &FirstLTC) {
    if(!FirstLTC) {
        cout << "\n\nDanh sach LTC rong!";
        return;
    }
    for(PTRLTC p = FirstLTC; p != nullptr; p=p->next) {
        cout << "Chi Tiet Cua Lop Tin Chi";
        cout<<"\n\nMa lop tin chi: "<<p->ltc.MALOPTC
            <<"\nMa mon hoc: "<<p->ltc.MAMH
            <<"\nNien Khoa: "<<p->ltc.NienKhoa
            <<"\nHoc ky: "<<p->ltc.Hocky
            <<"\nNhom: "<<p->ltc.Nhom
            <<"\nSo sinh vien toi da: "<<p->ltc.sosvmax
            <<"\nSo sinh vien toi thieu: "<<p->ltc.sosvmin<<endl;
    }
}
int getNextMaLopTinChi(PTRLTC First) {
    int maxID = 0;
    PTRLTC p = First;
    while (p != nullptr) {
        if (p->ltc.MALOPTC > maxID)
            maxID = p->ltc.MALOPTC;
        p = p->next;
    }
    return maxID + 1;
}
void InDSSVDK(PTRLTC &FirstLTC, int maloptc, DS_LOPSV &dslop) {
    if(!FirstLTC) {
        cout << "\n\nDanh sach LTC rong!";
        return;
    }
    cout << left  << setw(15) << "MASV" << setw(25) << "HO" << setw(15) << "TEN" << setw(10) << "DIEM" << endl;
    cout << "-------------------------------------------------------------\n";
    for(PTRLTC p = FirstLTC; p != nullptr; p=p->next) {
        if(maloptc == p->ltc.MALOPTC) {
            for(PTRDK q = p->ltc.dssvdk; q != nullptr; q = q->next) {
                int flag = 0;
                for (int i = 0; i < dslop.n; i++) {
                    LopSV* lop = dslop.nodes[i];
                    for (PTRSV sv = lop->FirstSV; sv != nullptr; sv = sv->next) {
                        if(strcmp(sv->sv.MASV,q->dk.MASV) == 0) {
                            cout << left  << setw(15) << sv->sv.MASV << setw(25) 
                            << sv->sv.HO << setw(15) << sv->sv.TEN << setw(10) << q->dk.DIEM << endl;
                            flag = 1;
                            break;
                        }
                    }
                    if(flag == 1) break;
                }
            }
            break;
        }
    }
}
void InDSLSV(DS_LOPSV &dslop) {
    if(dslop.n == 0) {
        cout << "\n\nDanh sach LopSV rong!";
        return;
    }
    
    for(int i = 0; i < dslop.n; i++) {
        cout << "Chi tiet lop SV";
        cout<<"\nMa lop: "<<dslop.nodes[i]->MALOP
            <<"\nTen lop: "<<dslop.nodes[i]->TENLOP<<endl;
    }
}
bool isSinhVien(PTRSV &First,char MASV[16]){
    PTRSV p=First;
    while(p!=nullptr){ if(strcmp(p->sv.MASV,MASV)==0) return true; p=p->next; }
    return false;
}
SinhVien getSinhVien(DS_LOPSV dslop, char MASV[16]) {
    for (int i = 0; i < dslop.n; i++) {
        LopSV* lop = dslop.nodes[i];
        for (PTRSV sv = lop->FirstSV; sv != nullptr; sv = sv->next) {
            if(strcmp(sv->sv.MASV,MASV) == 0) {
                return sv->sv;
            }
        }
    }
    SinhVien empty = {};
    return empty;
}
bool checkSV(DS_LOPSV &dslop, SinhVien sv) {
    if (dslop.n == 0) return false;

    for (int i = 0; i < dslop.n; i++) {
        PTRSV p = dslop.nodes[i]->FirstSV;
        while (p != nullptr) {
            if (strcmp(p->sv.MASV, sv.MASV) == 0)
                return true; 
            p = p->next;
        }
    }
    return false;
}

bool checkLTC(PTRLTC FirstLTC, LopTinChi ltc) { // Kiem tra xem lop tin chi co trong danh sach lop tin chi khong
                                                // Neu co thi tra ve true
    if (!FirstLTC) return false;
    for(PTRLTC p = FirstLTC; p != nullptr; p=p->next ) {
        if ((strcmp(ltc.MAMH, p->ltc.MAMH) == 0)
        && (strcmp(ltc.NienKhoa, p->ltc.NienKhoa) == 0)
        && (ltc.Hocky == p->ltc.Hocky)
        && (ltc.Nhom == p->ltc.Nhom)
        ) return true;
    }
    return false;
}
bool CheckLopSV(DS_LOPSV dslop, LopSV lop) { // Kiem tra xem lop sinh vien co trong danh sach lop sinh vien khong
                                             // Neu co thi tra ve true
    if (dslop.n==0) return false;
    for(int i = 0; i< dslop.n; i++) {
        if ((strcmp(lop.MALOP, dslop.nodes[i]->MALOP) == 0)) return true;
    }
    return false;
}
void NhapSV(DS_LOPSV &dslop) {
    LoadFile_LopSV("LopSinhVien.txt", dslop); 
    while (true) {
        char malop[16];
        SinhVien sv;
        cout << "\nNhap ma sinh vien (Nhap 0 de thoat):"; cin.getline(sv.MASV,16);
        if (strcmp(sv.MASV, "0") == 0) break;
        cout << "Nhap Ho: "; cin.getline(sv.HO,51);
        cout << "Nhap Ten: "; cin.getline(sv.TEN,11);
        cout << "Nhap Phai: "; cin.getline(sv.PHAI,4);
        cout << "Nhap SDT: "; cin.getline(sv.SODT,16);
        cout << "Nhap email: "; cin.getline(sv.Email,50);

        cout << "Nhap lop: "; cin.getline(malop,16);
        if(checkSV(dslop, sv)) {
            cout << "Sinh vien da ton tai. Vui long nhap lai!\n";
            continue;
        }
        for(int i=0; i<dslop.n; i++) {
            if(strcmp(malop, dslop.nodes[i]->MALOP) == 0) {
                InsertSV(dslop.nodes[i]->FirstSV,sv);
                break;
            }
        }
        cout << "Luu thanh cong!\n\n";
    }
}
void NhapLTC(PTRLTC &FirstLTC){
    LoadFile_LTC("LopTinChi.txt", FirstLTC);
    
    while (true) {
        LopTinChi ltc;
        ltc.MALOPTC = -1; // sẽ gán tự động sau
        
        cout << "\nNhap Ma Mon Hoc (Nhap 0 de thoat):"; cin.getline(ltc.MAMH, 11);
        if (strcmp(ltc.MAMH, "0") == 0) break;
        cout << "Nhap Nien Khoa: "; cin.getline(ltc.NienKhoa, 10);
        cout << "Nhap Hoc Ky: "; cin >> ltc.Hocky;
        cout << "Nhap Nhom: "; cin >> ltc.Nhom;
        cout << "Nhap SV Min va Max: "; cin >> ltc.sosvmin >> ltc.sosvmax;
        cin.ignore();

        if (checkLTC(FirstLTC, ltc)) {
            cout << "Lop tin chi da ton tai. Vui long nhap lai.\n";
            continue;
        }

        ltc.MALOPTC = getNextMaLopTinChi(FirstLTC);
        InsertLast_LTC(FirstLTC, ltc);

        cout << "Luu thanh cong!\n\n";
    }   
}
void NhapLopSV(DS_LOPSV &dslop){
    LoadFile_LopSV("LopSinhVien.txt",dslop);
    if (dslop.n >= MAX_LOPSV) {
        cout << "Da dat so luong lop toi da!\n";
        return;
    }
    while (true) {
        LopSV lop;

        cout << "\nNhap Ma Lop (Nhap 0 de thoat):"; cin.getline(lop.MALOP,16);
        if (strcmp(lop.MALOP, "0") == 0) break;
        cout << "Nhap Ten Lop: "; cin.getline(lop.TENLOP,51);
        if (CheckLopSV(dslop,lop)) {
            cout << "LopSV da ton tai. Vui long nhap lai.\n";
            continue;
        }
        lop.FirstSV = nullptr;
        dslop.nodes[dslop.n] = new LopSV(lop);
        dslop.n++;
        cout << "Luu thanh cong!\n\n";
    }   
}




// -----------------------------------------------------------------------------------

bool CheckDK(PTRDK dssvdk, const char* masv) {
     for (PTRDK p = dssvdk; p != NULL; p = p->next) {
        if (strcmp(p->dk.MASV, masv) == 0 && p->dk.HuyDK == false)
            return true;
    }
    return false;
}
PTRDK taonodeSVDK(const char* masv) {
    PTRDK p = new nodeDK;
    strcpy(p->dk.MASV, masv);
    p->dk.DIEM = -1;
    p->dk.HuyDK = false;
    p->next = nullptr;
    return p;
}
void insertSVDK(PTRDK &First, PTRDK pnode) {
    if (First == nullptr) {
        First = pnode;
        return;
    }
    PTRDK p = First;
    while (p->next != nullptr) p = p->next;
    p->next = pnode;
}
void dangkyLTC(PTRLTC &FirstLTC, DS_LOPSV dslop) { // Sinh vien dang ki ltc
    char masv[16];
    cout << "\nNhap ma sinh vien: ";
    cin.getline(masv, 16);
    bool found = false;
    for(int i=0 ; i < dslop.n; i++) { // Kiem tra xem sinh vien co ton tai hay khong
        PTRSV p = dslop.nodes[i]->FirstSV;
        while (p != NULL) {
            if (strcmp(p->sv.MASV, masv) == 0) {
                found = true;
                break;
            }
        p = p->next;
        }
    }
    if(!found) {
        cout << "Ma sinh vien khong tim thay!";
        return;
    }
    while (true) {
        int maloptc;
        cout << "Nhap ma lop tin chi ban muon dang ky (nhap 0 de thoat):";
        cin >> maloptc;
        cin.ignore();
        if (maloptc == 0) break;
        
        PTRLTC pltc = FirstLTC;
        while (pltc != NULL && pltc->ltc.MALOPTC != maloptc)
        pltc = pltc->next;
        if (!pltc) {
            cout << "Lop tin chi khong ton tai!\n";
            return;
        }
        if(CheckDK(pltc->ltc.dssvdk,masv)) {
            cout << "Sinh vien da dang ky lop nay roi!\n";
            return;
        }
        PTRDK pnode = taonodeSVDK(masv);
        insertSVDK(pltc->ltc.dssvdk, pnode);
        cout << " Dang ky thanh cong!\n";
    }
}


void DeleteDSSV(PTRSV &FirstSV) { // Delete toan bo dssv cua mot lop
    while(FirstSV != NULL) {
        PTRSV temp = FirstSV;
        FirstSV = FirstSV ->next;
        delete temp;
    }
}
void DeleteDSLopSV(DS_LOPSV &dslop) {   // Delete toan bo dssv cua tat
    for (int i = 0; i < dslop.n; i++) { // ca cac lop sau do gan so lop = 0
        DeleteDSSV(dslop.nodes[i]->FirstSV);
        delete dslop.nodes[i];
    }
    dslop.n = 0;
}

int SaveFile_LopSV(const char* tenfile, DS_LOPSV &dslop) { // Save toan bo thong tin lop cua tat ca cac lop
    FILE *f = fopen(tenfile, "wb");                        // Thong tin lop: MALOP, TENLOP, so luong sv, tat ca      
    if (f == NULL) {                                       // cac sinh vien cua lop
        cout << "Khong the save duoc file!\n";
        return 0;
    }
    fwrite(&dslop.n, sizeof(int), 1, f);
    for (int i = 0; i < dslop.n; i++) {
        LopSV *lop = dslop.nodes[i];

        fwrite(lop->MALOP, sizeof(lop->MALOP), 1, f);
        fwrite(lop->TENLOP, sizeof(lop->TENLOP), 1, f);
        int countSV = 0;
        for (PTRSV p = lop->FirstSV; p != NULL; p = p->next) countSV++;
        fwrite(&countSV, sizeof(int), 1, f);
        for (PTRSV p = lop->FirstSV; p != NULL; p = p->next) {
            fwrite(&p->sv, sizeof(SinhVien), 1, f);
        }
    }

    fclose(f);
    return 1;
}
int LoadFile_LopSV(const char* tenfile, DS_LOPSV &dslop) {  // Load toan bo thong tin lop cua tat ca cac lop
    FILE* f = fopen(tenfile, "rb");                         // Thong tin lop: MALOP, TENLOP, so luong sv, tat ca
    if (!f) return 0;                                       // cac sinh vien cua lop. Tat ca cac sv duoc doc ra
                                                            // se dua vao cac node sinh vien de tao ra DSSV.
    
    DeleteDSLopSV(dslop);
    
    fread(&dslop.n, sizeof(int), 1, f);

    for (int i = 0; i < dslop.n; i++) {
        LopSV* lop = new LopSV;

        fread(lop->MALOP, sizeof(lop->MALOP), 1, f);
        fread(lop->TENLOP, sizeof(lop->TENLOP), 1, f);

        int soSV;
        fread(&soSV, sizeof(int), 1, f);

        lop->FirstSV = NULL;
        PTRSV lastSV = NULL;
        for (int j = 0; j < soSV; j++) {
            PTRSV svNode = new nodeSV;
            fread(&svNode->sv, sizeof(SinhVien), 1, f);
            svNode->next = NULL;

            if (!lop->FirstSV) {
                lop->FirstSV = svNode;
                lastSV = svNode;
            } else {
                lastSV->next = svNode;
                lastSV = svNode;
            }
        }
     
        dslop.nodes[i] = lop;
    }
    fclose(f);
    return 1; 
    
}


// ===
void DeleteDSLTC(PTRLTC &FirstLTC) { // Delete toan bo cac LTC trong danh sach lien ket
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
void InsertSV(PTRSV &FirstSV, SinhVien sv) {
    PTRSV newNode = new nodeSV;
    newNode->sv = sv;
    newNode->next = NULL;
    if (FirstSV == NULL) FirstSV = newNode;
    else {
        PTRSV p = FirstSV;
        while (p->next != NULL) p = p->next;
        p->next = newNode;
    }
}
void InsertLast_LTC(PTRLTC &FirstLTC,LopTinChi &ltc) { // Insert mot LTC vao DSLTC
    PTRLTC newNode = new nodeLTC;
    newNode->ltc = ltc;
    newNode->next = NULL;
    if (FirstLTC == NULL) FirstLTC = newNode;
    else {
        PTRLTC p = FirstLTC;
        while (p->next != NULL) p = p->next;
        p->next = newNode;
    }
}
void InsertLast_DK(PTRDK &dssvdk, DangKy dk) { // Insert mot sinh vien dang ky vao dssvdk ltc do
    PTRDK newNode = new nodeDK;
    newNode->dk = dk;
    newNode->next = NULL;
    if(dssvdk == NULL) dssvdk = newNode;
    else {
        newNode->next = dssvdk;
        dssvdk = newNode; 
    }
}
int SaveFile_LTC(const char* tenfile, PTRLTC &FirstLTC) { 
    FILE *f = fopen(tenfile, "wb");
    if(!f) {
        cout <<"\n\n\nLOI";
        return 0;
    }
    for (PTRLTC p = FirstLTC; p != nullptr; p = p->next) {
         cout << "\nMALOPTC =" << p->ltc.MALOPTC;
        fwrite(&p->ltc.MALOPTC, sizeof(int), 1, f);
        fwrite(p->ltc.MAMH, sizeof(p->ltc.MAMH), 1, f);
        fwrite(p->ltc.NienKhoa, sizeof(p->ltc.NienKhoa), 1, f);
        fwrite(&p->ltc.Hocky, sizeof(int), 1, f);
        fwrite(&p->ltc.Nhom, sizeof(int), 1, f);
        fwrite(&p->ltc.sosvmin, sizeof(int), 1, f);
        fwrite(&p->ltc.sosvmax, sizeof(int), 1, f);
        fwrite(&p->ltc.huylop, sizeof(bool), 1, f);
        // dssv dang ki
        int count = 0;
        for (PTRDK q = p->ltc.dssvdk; q != NULL; q = q->next) count++;
        fwrite(&count, sizeof(int), 1, f);
        for (PTRDK q = p->ltc.dssvdk; q != NULL; q = q->next) {
            fwrite(&q->dk, sizeof(DangKy), 1, f);
        }
    }
 
    fclose(f);
    return 1;
}
// === load dslk ltc ===
int LoadFile_LTC(const char* tenfile, PTRLTC &FirstLTC) {
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
float Tinhdiemtb(SinhVien &sv, PTRLTC &dsltc, treeMH &dsmh) { // dtb = tong diem / (tong tin chi)
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


void IndiemtbLop(PTRLTC &dsltc,DS_LOPSV &dslop,treeMH &dsmh) { // In diem tb cho ca lop
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
void IndiemtbSinhvien(PTRLTC &dsltc,DS_LOPSV &dslop, treeMH &dsmh) { // In diem tb cho ca nhan
    char MASV[16];
    cout << "Nhap ma so sinh vien: ";
    cin.getline(MASV, 16);
    
    LopSV* lop = nullptr;
    int flag = 0;
    for (int i = 0; i < dslop.n; i++) {
        lop = dslop.nodes[i];
        for (PTRSV sv = lop->FirstSV; sv != nullptr; sv = sv->next) {
            if(strcmp(sv->sv.MASV,MASV) == 0) {
                cout << "\n -==== DIEM TRUNG BINH ====- \n";
                cout << "Lop: " << lop->TENLOP << endl;
                cout << left  << setw(15) << "MASV" << setw(25) << "HO" << setw(15) << "TEN" << setw(10) << "DIEM TB" << endl;
                cout << "-------------------------------------------------------------\n";
                float diemTB = Tinhdiemtb(sv->sv, dsltc, dsmh);
                if (diemTB >= 0) {
                    cout << left  << setw(15) << sv->sv.MASV << setw(25) << sv->sv.HO 
                    << setw(15) << sv->sv.TEN << setw(10) << fixed << setprecision(2) << diemTB << endl;
                } else {
                    cout << left  << setw(15) << sv->sv.MASV << setw(25) 
                    << sv->sv.HO << setw(15) << sv->sv.TEN << setw(10) << "Chua co" << endl;
                }
                flag = 1;
                break;
            }
        }
        if(flag) break;
    }
}
void duyettreeMH(treeMH t, char dsMAMH[][11], int &soMH) {
    if (t == nullptr) return;
    duyettreeMH(t->left, dsMAMH, soMH);
    strcpy(dsMAMH[soMH++], t->mh.MAMH);
    duyettreeMH(t->right, dsMAMH, soMH);
}
void InbangdiemtongketLop( PTRLTC &dsltc,  DS_LOPSV &dslop,  treeMH &dsmh) {
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
void InbangdiemtongketSinhvien( PTRLTC &dsltc,  DS_LOPSV &dslop,  treeMH &dsmh) {
    char dsMAMH[200][11];
    char MASV[16];
    int soMH = 0;
    duyettreeMH(dsmh, dsMAMH, soMH);
    if (soMH == 0) {
        cout << "Danh sach mon hoc rong!\n";
        return;
    }
    cout << "Nhap ma so sinh vien: ";
    cin.getline(MASV,16);
    LopSV* lop = nullptr;
    int flag = 0;
    for (int i = 0; i < dslop.n; i++) {
        lop = dslop.nodes[i];
        for (PTRSV sv = lop->FirstSV; sv != nullptr; sv = sv->next) {
            if(strcmp(sv->sv.MASV,MASV)==0) {
                cout << " -==== DIEM TONG KET ====- ";
                cout << "\nLop: " << lop->TENLOP << endl;
                cout << left <<setw(15) << "MASV" << setw(25) << "HO TEN";
                for (int j = 0; j < soMH; j++) cout << setw(8) << dsMAMH[j];
                cout << endl;
                cout << "------------------------------------------------------------\n";
                float diemMax[200];
                for (int j = 0; j < soMH; j++) diemMax[j] = -1;
                for (PTRLTC cur = dsltc; cur != nullptr; cur = cur->next) {
                    if (cur->ltc.huylop) continue;

                    for (PTRDK dk = cur->ltc.dssvdk; dk != nullptr; dk = dk->next) {
                        if (strcmp(dk->dk.MASV, sv->sv.MASV) == 0) {
                            for (int j = 0; j < soMH; j++) {
                                if (strcmp(dsMAMH[j], cur->ltc.MAMH) == 0) {
                                    if (dk->dk.DIEM > diemMax[j]) diemMax[j] = dk->dk.DIEM;
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
                cout << left << setw(15) << sv->sv.MASV << setw(25) << hoten;
                for(int j=0; j< soMH; j++) {
                    if(diemMax[j] >= 0) {
                        cout << setw(8) << fixed << setprecision(2) << diemMax[j];
                    } else {
                        cout << setw(8) << "-";
                    }
                    
                }
                cout << endl;
                flag = 1;
                break;
            }
        }
        if (flag) break;
    }
}
void NhapDiem(nodeLTC* dsltc, DS_LOPSV &dslop) {
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
        cout << "\n\nKhong tim thay lop tin chi tuong ung!\n";
        return;
    }
    if (ltc->ltc.huylop) {
        cout << "\n\nLop tin chi nay da bi huy, khong the nhap diem!\n";
        return;
    }
    if (ltc->ltc.dssvdk == nullptr) {
        cout << "\n\nKhong co sinh vien dang ky lop tin chi nay!\n";
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
void InbangDiemLTC(nodeLTC* dsltc, DS_LOPSV &dslop) {
    char nienkhoa[10], mamh[11];
    int hocky, nhom;
    cout << "Nhap nien khoa: ";
    cin.getline(nienkhoa,10);
    cout << "Nhap hoc ki: "; cin >> hocky; cin.ignore();
    cout << "Nhap nhom: "; cin >> nhom; cin.ignore();
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
    cout << "\n                -==== BANG DIEM LOP TIN CHI ====- \n";
    cout << left << setw(5) << "STT" << setw(15) << "MASV" << setw(25) << "HO"<<
    setw(15) << "TEN" << setw(10) << "DIEM" << endl;
    cout << "-----------------------------------------------------------------------------------------------\n";
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
            << setw(10) << fixed << setprecision(2) << p->dk.DIEM << endl;
        } else {
            cout << setw(5) << stt++<< setw(15) << p->dk.MASV<< setw(25) << "Khong tim thay"
            << setw(15) << ""<< setw(10) << "----" << endl;
        }
        p = p->next;
    }
    
}

