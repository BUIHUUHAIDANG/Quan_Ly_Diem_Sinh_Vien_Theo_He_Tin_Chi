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

/*nodeSV::nodeSV() { next = nullptr; }
LopSV::LopSV() { FirstSV = nullptr; MALOP[0]=0; TENLOP[0]=0; }
DS_LOPSV::DS_LOPSV() { n = 0; for(int i=0;i<MAX_LOPSV;i++) nodes[i]=nullptr; }
nodeDK::nodeDK() { next = nullptr; }
LopTinChi::LopTinChi() {
    MALOPTC = 0; MAMH[0]=0; NienKhoa[0]=0;
    Hocky = 0; Nhom = 0; sosvmin = 0; sosvmax = 0;
    huylop = false; dssvdk = nullptr;
}
nodeLTC::nodeLTC() { next = nullptr; }
nodeLTC::nodeLTC(LopTinChi data) { this->ltc = data; this->next = nullptr; }*/
void initializeLTC(PTRLTC & First) { First = nullptr; }
void initializeSV(PTRSV &FirstSV){FirstSV=nullptr;}
PTRLTC createNodeLopTinChi(LopTinChi data) { return new nodeLTC(data); }
void insertLopTinChi(PTRLTC &First, LopTinChi data){
    PTRLTC p = createNodeLopTinChi(data);
    if(First == nullptr) First = p;
    else {
        PTRLTC tmp = First;
        while(tmp->next != nullptr) tmp = tmp->next;
        tmp->next = p;
    }
}
bool isEmpty(PTRLTC &First){ return First == nullptr; }
int deleteFirst(PTRLTC &First){
    if(isEmpty(First)) return 0;
    PTRLTC p = First;
    First = p->next;
    delete p;
    return 1;
}
int deleteAfter(PTRLTC p){
    if(!p || !p->next) return 0;
    PTRLTC q = p->next;
    p->next = q->next;
    delete q;
    return 1;
}
int deleteLopTinChi(PTRLTC &First,int MALTC){
    if(isEmpty(First)) return 0;
    if(First->ltc.MALOPTC == MALTC) return deleteFirst(First);
    PTRLTC p;
    for(p=First; p->next!=nullptr && p->next->ltc.MALOPTC!=MALTC; p=p->next);
    if(p->next != nullptr) return deleteAfter(p);
    return 0;
}
void Clearlist(PTRLTC &First){ while(First!=nullptr) deleteFirst(First); }
void ClearlistSV(PTRSV &First){ while(First!=nullptr) deleteFirstSinhVien(First);}
void ClearDS_Lop(DS_LOPSV &ds) {
    for (int i = 0; i < ds.n; i++) {
        if (ds.nodes[i]) {
            ClearlistSV(ds.nodes[i]->FirstSV);
            delete ds.nodes[i];
            ds.nodes[i] = nullptr;
        }
    }
    ds.n = 0; 
}

PTRLTC searchLopTinChi(PTRLTC &First,int x){
    PTRLTC p=First;
    while(p!=nullptr){ if(p->ltc.MALOPTC==x) return p; p=p->next; }
    return nullptr;
}
PTRLTC searchLTC(PTRLTC &First,char nienkhoa[10],int hocky,int nhom,char MAMH[11]){
    PTRLTC p=First;
    while(p!=nullptr){
        if(strcmp(p->ltc.NienKhoa,nienkhoa)==0 && p->ltc.Hocky==hocky &&
           p->ltc.Nhom==nhom && strcmp(p->ltc.MAMH,MAMH)==0) return p;
        p=p->next;
    }
    return nullptr;
}
bool editLopTinChi(PTRLTC &First, int id) {
    PTRLTC p = searchLopTinChi(First, id);
    if (!p) {
        cout << "Khong tim thay lop tin chi!\n";
        return false;
    }

    cout << "\n=== CHINH SUA LOP TIN CHI ===\n";
    cout << "[DU LIEU] [DU LIEU CU] [Nhap DU LIEU MOI]/n";
    cout << ">> De trong = giu nguyen gia tri cu(ro roi thi enter de tiep tuc)\n\n";

    cin.ignore(); 

    
    string newMAMH = inputOrKeep(p->ltc.MAMH, "Ma Mon Hoc");
    strcpy(p->ltc.MAMH, newMAMH.c_str());

    string newNienKhoa = inputOrKeep(p->ltc.NienKhoa, "Nien Khoa");
    strcpy(p->ltc.NienKhoa, newNienKhoa.c_str());

    p->ltc.Hocky = inputIntOrKeep(p->ltc.Hocky, "Hoc Ky");
    p->ltc.Nhom   = inputIntOrKeep(p->ltc.Nhom, "Nhom");
    p->ltc.sosvmin = inputIntOrKeep(p->ltc.sosvmin, "SV Min");
    p->ltc.sosvmax = inputIntOrKeep(p->ltc.sosvmax, "SV Max");

    cout << "\n>>> Cap nhat lop tin chi thanh cong!\n";
    return true;
}
void showDanhSachSinhVienDangKy(PTRLTC &l){
    cout << "Danh Sach Sinh Vien Da Dang Ky:\n";
    PTRDK p = l->ltc.dssvdk;
    while(p!=nullptr){
        cout<<"Ma SV: "<<p->dk.MASV<<"\nHo: "<<p->dk.sinhVien->sv.HO
            <<"\nTen: "<<p->dk.sinhVien->sv.TEN
            <<"\nSo DT: "<<p->dk.sinhVien->sv.SODT
            <<"\nPhai: "<<p->dk.sinhVien->sv.PHAI<<"\n";
        p=p->next;
    }
}
void showLopTinChi(PTRLTC &l){
    cout<<"\nChi Tiet Cua Lop Tin Chi\nMa lop tin chi: "<<l->ltc.MALOPTC
        <<"\nMa mon hoc: "<<l->ltc.MAMH
        <<"\nNien Khoa: "<<l->ltc.NienKhoa
        <<"\nHoc ky: "<<l->ltc.Hocky
        <<"\nNhom: "<<l->ltc.Nhom
        <<"\nSo sinh vien toi da: "<<l->ltc.sosvmax
        <<"\nSo sinh vien toi thieu: "<<l->ltc.sosvmin<<endl;
}


bool isEmptySinhVien(PTRSV &First){ return First == nullptr; }
void insertSinhVien(PTRSV &First,SinhVien x){
    PTRSV p = new nodeSV; p->sv=x; p->next=nullptr;
    if(!First) First=p;
    else { PTRSV tmp=First; while(tmp->next) tmp=tmp->next; tmp->next=p; }
}
int deleteFirstSinhVien(PTRSV &First){ if(isEmptySinhVien(First)) return 0; PTRSV p=First; First=p->next; delete p; return 1; }
int deleteAfterSinhVien(PTRSV p){ if(!p||!p->next) return 0; PTRSV q=p->next; p->next=q->next; delete q; return 1; }
int deleteSinhVien(PTRSV &First,char MASV[16]){
    if(isEmptySinhVien(First)) return 0;
    if(strcmp(First->sv.MASV,MASV)==0) return deleteFirstSinhVien(First);
    PTRSV p;
    for(p=First; p->next!=nullptr && strcmp(p->next->sv.MASV,MASV)!=0; p=p->next);
    if(p->next!=nullptr) return deleteAfterSinhVien(p);
    return 0;
}
bool findSinhVien(PTRSV &First,char MASV[16]){
    PTRSV p=First;
    while(p!=nullptr){ if(strcmp(p->sv.MASV,MASV)==0) return true; p=p->next; }
    return false;
}
bool editSinhVien(PTRSV &sv){
    char h[51], t[11], p[4], sdt[16], email[50];
    cout<<"nhap ho moi: "; cin.getline(h,51); if(strlen(h)>0) strcpy(sv->sv.HO,h);
    cout<<"nhap ten moi: "; cin.getline(t,11); if(strlen(t)>0) strcpy(sv->sv.TEN,t);
    cout<<"doi phai moi: "; cin.getline(p,4); if(strlen(p)>0) strcpy(sv->sv.PHAI,p);
    cout<<"so dien thoai moi: "; cin.getline(sdt,16); if(strlen(sdt)>0) strcpy(sv->sv.SODT,sdt);
    cout<<"email moi: "; cin.getline(email,50); if(strlen(email)>0) strcpy(sv->sv.Email,email);
    return true;
}
void InDSSV_TheoTen(PTRSV first){
    if(!first){ cout<<"Danh sach rong!\n"; return; }
    int n=0; for(PTRSV p=first;p;p=p->next) n++;
    SinhVien* arr=new SinhVien[n]; int i=0;
    for(PTRSV p=first;p;p=p->next) arr[i++]=p->sv;
    for(int i=0;i<n-1;i++){
        for(int j=i+1;j<n;j++){
            if(strcmp(arr[i].TEN,arr[j].TEN)>0 || (strcmp(arr[i].TEN,arr[j].TEN)==0 && strcmp(arr[i].HO,arr[j].HO)>0)) swap(arr[i],arr[j]);
        }
    }
    cout<<"\ndanh sach sinh vien theo alphabet\n";
    for(int i=0;i<n;i++){
        cout<<arr[i].MASV<<" | "<<arr[i].HO<<" "<<arr[i].TEN<<" | "<<arr[i].PHAI<<" | "<<arr[i].SODT<<endl;
    }
    delete[] arr;
}
LopSV* searchLopSV(DS_LOPSV &dsLop,const char* MALOP){
    for(int i=0;i<dsLop.n;i++){
        if(strcmp(dsLop.nodes[i]->MALOP,MALOP)==0) return dsLop.nodes[i];
    }
    return nullptr;
}
int compareSV(const SinhVien& a, const SinhVien& b) {
    int cmp = strcmp(a.TEN, b.TEN);
    if (cmp != 0) return cmp;
    return strcmp(a.HO, b.HO);
}
void sortSinhVien(SinhVien arr[], int n) {
    for(int i = 0; i < n - 1; i++) {
        for(int j = i + 1; j < n; j++) {
            if(compareSV(arr[i], arr[j]) > 0) {
                SinhVien tmp = arr[i];
                arr[i] = arr[j];
                arr[j] = tmp;
            }
        }
    }
}
void printDSSV_sorted(LopSV *lop) {
    if(!lop || !lop->FirstSV) {
        cout << "Lop khong co sinh vien!\n";
        return;
    }
    int n = 0;
    PTRSV p = lop->FirstSV;
    while(p){ n++; p = p->next; }

    SinhVien* arr = new SinhVien[n];
    p = lop->FirstSV;
    for(int i=0;i<n;i++){
        arr[i] = p->sv;
        p = p->next;
    }

    sortSinhVien(arr, n);

    cout << "\n===== DANH SACH SINH VIEN (SORT BY TEN + HO) =====\n";
    for(int i=0;i<n;i++){
        cout << i+1 << ". "
             << arr[i].HO << " " << arr[i].TEN
             << " | MSV: " << arr[i].MASV
             << " | Phai: " << arr[i].PHAI
             << " | SDT: " << arr[i].SODT
             << " | Email: " << arr[i].Email
             << endl;
    }

    delete[] arr; 
}
bool checkLTC(PTRLTC FirstLTC, LopTinChi ltc) { // Kiem tra xem lop tin chi co trong danh sach lop tin chi khong
                                                // Neu co thi tra ve true
    if (!FirstLTC) return false;
    if ((strcmp(ltc.MAMH, FirstLTC->ltc.MAMH) == 0)
     && (strcmp(ltc.NienKhoa, FirstLTC->ltc.NienKhoa) == 0)
     && (ltc.Hocky == FirstLTC->ltc.Hocky)
     && (ltc.Nhom == FirstLTC->ltc.Nhom)
    ) return true;
    else return false;
}
void NhapLTC(PTRLTC &FirstLTC){
    LoadFile_LTC("LopTinChi.txt", FirstLTC);
    
    while (true) {
        LopTinChi ltc;
        ltc.MALOPTC = -1; // sẽ gán tự động sau
        
        cout << "\nNhap Ma Mon Hoc: (Nhap 0 de thoat)"; cin.getline(ltc.MAMH, 11);
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

void saveLopTinChiToFileText(PTRLTC First, const string &filename) {
    ofstream f(filename);
    if (!f) {
        cout << "Khong mo duoc file de ghi!\n";
        return;
    }

    PTRLTC p = First;
    while (p) {
        f << p->ltc.MALOPTC << "|"
          << p->ltc.MAMH << "|"
          << p->ltc.NienKhoa << "|"
          << p->ltc.Hocky << "|"
          << p->ltc.Nhom << "|"
          << p->ltc.sosvmin << "|"
          << p->ltc.sosvmax << "|"
          << p->ltc.huylop << "\n";
        p = p->next;
    }

    f.close();
}
void loadLopTinChiFromFileText(PTRLTC &First, const string &filename) {
    ifstream f(filename);
    if (!f) {
        cout << "Khong tim thay file du lieu!\n";
        First = nullptr;
        return;
    }

    Clearlist(First);

    string line;
    while (getline(f, line)) {
    if (line.empty() || line == "#") continue;

    stringstream ss(line);
    LopTinChi ltc;
    string temp;

    
    getline(ss, temp, '|'); ltc.MALOPTC = stoi(temp);
    getline(ss, temp, '|'); strcpy(ltc.MAMH, temp.c_str());
    getline(ss, temp, '|'); strcpy(ltc.NienKhoa, temp.c_str());
    getline(ss, temp, '|'); ltc.Hocky = stoi(temp);
    getline(ss, temp, '|'); ltc.Nhom = stoi(temp);
    getline(ss, temp, '|'); ltc.sosvmin = stoi(temp);
    getline(ss, temp, '|'); ltc.sosvmax = stoi(temp);
    getline(ss, temp, '|'); ltc.huylop = (temp == "1");

    insertLopTinChi(First, ltc);
}


    f.close();
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
string inputOrKeep(const string &oldValue, const string &label) {
    cout << label << " [" << oldValue << "]: ";
    string s;
    getline(cin, s);
    if (s.empty()) return oldValue;
    return s;
}
int inputIntOrKeep(int oldValue, const string &label) {
    cout << label << " [" << oldValue << "]: ";
    string s;
    getline(cin, s);
    if (s.empty()) return oldValue; 

    return stoi(s); 
}
PTRLTC findLTCByParams(PTRLTC FirstLTC) {
    char nienkhoa[10], MAMH[11];
    int hocky, nhom;

    cout << "Nhap Nien Khoa: "; cin.getline(nienkhoa, 10);
    cout << "Nhap Hoc Ky: "; cin >> hocky;
    cout << "Nhap Nhom: "; cin >> nhom;
    cin.ignore();
    cout << "Nhap Ma Mon Hoc: "; cin.getline(MAMH, 11);

    return searchLTC(FirstLTC, nienkhoa, hocky, nhom, MAMH);
}
// void saveSinhVienToFile(PTRSV First, const string &filename) {
//     ofstream f(filename);
//     if(!f) {
//         cout << "Khong mo duoc file de ghi!\n";
//         return;
//     }

//     PTRSV p = First;
//     while(p) {
//         f << p->sv.MASV << "|"
//           << p->sv.HO << "|"
//           << p->sv.TEN << "|"
//           << p->sv.PHAI << "|"
//           << p->sv.SODT << "|"
//           << p->sv.Email << "\n";
//         p = p->next;
//     }

//     f.close();
// }
// void loadSinhVienFromFile(PTRSV &First, const string &filename) {
//     ifstream f(filename);
//     if(!f) {
//         cout << "Khong tim thay file du lieu!\n";
//         First = nullptr;
//         return;
//     }
//     while(First) {
//         PTRSV tmp = First;
//         First = First->next;
//         delete tmp;
//     }

//     string line;
//     while(getline(f, line)) {
//         if(line.empty()) continue;

//         stringstream ss(line);
//         SinhVien sv;
//         string temp;

//         getline(ss, temp, '|'); strcpy(sv.MASV, temp.c_str());
//         getline(ss, temp, '|'); strcpy(sv.HO, temp.c_str());
//         getline(ss, temp, '|'); strcpy(sv.TEN, temp.c_str());
//         getline(ss, temp, '|'); strcpy(sv.PHAI, temp.c_str());
//         getline(ss, temp, '|'); strcpy(sv.SODT, temp.c_str());
//         getline(ss, temp, '|'); strcpy(sv.Email, temp.c_str());

//         insertSinhVien(First, sv);
//     }

//     f.close();
// }
void saveLopSV(DS_LOPSV &ds, const string &fileLop, const string &fileSV) {
    ofstream fLop(fileLop);
    ofstream fSV(fileSV);
    if(!fLop || !fSV) { cout << "Khong mo duoc file!\n"; return; }

    for(int i=0;i<ds.n;i++){
        fLop << ds.nodes[i]->MALOP << "|" << ds.nodes[i]->TENLOP << "\n";
        PTRSV p = ds.nodes[i]->FirstSV;
        while(p){
            fSV << ds.nodes[i]->MALOP << "|"
                << p->sv.MASV << "|"
                << p->sv.HO << "|"
                << p->sv.TEN << "|"
                << p->sv.PHAI << "|"
                << p->sv.SODT << "|"
                << p->sv.Email << "\n";
            p = p->next;
        }
    }

    fLop.close();
    fSV.close();
}
void loadLopSV(DS_LOPSV &ds, const string &fileLop, const string &fileSV) {
    ds.n = 0;
    ifstream fLop(fileLop);
    if(!fLop){ cout << "Khong tim thay file LopSV\n"; return; }

    string line;
    while(getline(fLop,line)){
        if(line.empty()) continue;
        stringstream ss(line);
        string malop, tenlop;
        getline(ss, malop, '|');
        getline(ss, tenlop, '|');

        LopSV* lop = new LopSV;
        strcpy(lop->MALOP, malop.c_str());
        strcpy(lop->TENLOP, tenlop.c_str());
        lop->FirstSV = nullptr;

        ds.nodes[ds.n++] = lop;
    }
    fLop.close();

    ifstream fSV(fileSV);
    if(!fSV){ cout << "Khong tim thay file SinhVien\n"; return; }

    while(getline(fSV,line)){
        if(line.empty()) continue;
        stringstream ss(line);
        string malop;
        SinhVien sv;
        string temp;
        getline(ss, malop, '|');
        getline(ss, temp, '|'); strcpy(sv.MASV, temp.c_str());
        getline(ss, temp, '|'); strcpy(sv.HO, temp.c_str());
        getline(ss, temp, '|'); strcpy(sv.TEN, temp.c_str());
        getline(ss, temp, '|'); strcpy(sv.PHAI, temp.c_str());
        getline(ss, temp, '|'); strcpy(sv.SODT, temp.c_str());
        getline(ss, temp, '|'); strcpy(sv.Email, temp.c_str());

        LopSV* lop = searchLopSV(ds, malop.c_str());
        if(lop) insertSinhVien(lop->FirstSV, sv);
    }
    fSV.close();
}

// -----------------------------------------------------------------------------------


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

        fwrite(&lop->MALOP, sizeof(lop->MALOP), 1, f);
        fwrite(&lop->TENLOP, sizeof(lop->TENLOP), 1, f);
        int countSV = 0;
        for (PTRSV p = lop->FirstSV; p != NULL; p = p->next) 
            countSV++;
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

            if (lop->FirstSV == NULL) {
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
void DeleteDSLTC(PTRLTC FirstLTC) { // Delete toan bo cac LTC trong danh sach lien ket
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
void InsertLast_LTC(PTRLTC &FirstLTC,LopTinChi &ltc) { // Insert mot LTC vao DSLTC
    PTRLTC newNode = new nodeLTC;
    newNode->ltc = ltc;
    newNode->next = NULL;

    if (FirstLTC == NULL) {
        FirstLTC = newNode;
        cout << "\n\nFirstLTC = ";
    }
    else {
        PTRLTC p = FirstLTC;
        while (p->next != NULL) p = p->next;
        p->next = newNode;
    }
}
void InsertLast_DK(PTRDK dssvdk, DangKy dk) { // Insert mot sinh vien dang ky vao dssvdk ltc do
    PTRDK newNode = new nodeDK;
    newNode->dk = dk;
    newNode->next = NULL;
    if(dssvdk == NULL) dssvdk = newNode;
    else {
        newNode->next = dssvdk;
        dssvdk = newNode; 
    }
}
int SaveFile_LTC(const char* tenfile, PTRLTC FirstLTC) { 
    FILE *f = fopen(tenfile, "wb");
    //if (FirstLTC == NULL) cout << "\n\n\n\nLOI";
    for (PTRLTC p = FirstLTC; p != nullptr; p = p->next) {
        

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
void IndiemtbLop(PTRLTC dsltc, DS_LOPSV dslop, treeMH dsmh) { // In diem tb cho ca lop
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
void IndiemtbSinhvien(PTRLTC dsltc, DS_LOPSV dslop, treeMH dsmh) { // In diem tb cho ca nhan
    char MASV[16];
    cout << "Nhap ma so sinh vien: ";
    cin.getline(MASV, 16);

    LopSV* lop = nullptr;
    cout << "\n -==== DIEM TRUNG BINH ====- \n";
    cout << "Lop: " << lop->TENLOP << endl;
    cout << left  << setw(15) << "MASV" << setw(25) << "HO" << setw(15) << "TEN" << setw(10) << "DIEM TB" << endl;
    cout << "-------------------------------------------------------------\n";
    int flag = 0;
    for (int i = 0; i < dslop.n; i++) {
        lop = dslop.nodes[i];
        for (PTRSV sv = lop->FirstSV; sv != nullptr; sv = sv->next) {
            if(strcmp(sv->sv.MASV,MASV) == 0) {
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
void InbangdiemtongketLop(PTRLTC dsltc, DS_LOPSV dslop, treeMH dsmh) {
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
void InbangdiemtongketSinhvien(PTRLTC dsltc, DS_LOPSV dslop, treeMH dsmh) {
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
    cout << " -==== DIEM TONG KET ====- ";
    cout << "Lop: " << lop->TENLOP << endl;
    cout << left <<setw(15) << "MASV" << setw(25) << "HO TEN";
    for (int i = 0; i < soMH; i++) cout << setw(8) << dsMAMH[i];
    cout << endl;
    int flag = 0;
    for (int i = 0; i < dslop.n; i++) {
        lop = dslop.nodes[i];
        for (PTRSV sv = lop->FirstSV; sv != nullptr; sv = sv->next) {
            if(strcmp(sv->sv.MASV,MASV)==0) {
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
void InbangDiemLTC(nodeLTC* dsltc, DS_LOPSV dslop) {
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
            << setw(10) << fixed << setprecision(2) << p->dk.DIEM;
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

