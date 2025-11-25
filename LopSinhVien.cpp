#include "LopSinhVien.h"
#include "CTDL.h"
#include <cstring>
#include <iostream>
#include <algorithm>
#include <fstream>      
#include <sstream>      
#include <string>      
using namespace std;


// nodeSV::nodeSV() { next = nullptr; }
// LopSV::LopSV() { FirstSV = nullptr; MALOP[0]=0; TENLOP[0]=0; }
// DS_LOPSV::DS_LOPSV() { n = 0; for(int i=0;i<MAX_LOPSV;i++) nodes[i]=nullptr; }
// nodeDK::nodeDK() { next = nullptr; }
// LopTinChi::LopTinChi() {
//     MALOPTC = 0; MAMH[0]=0; NienKhoa[0]=0;
//     Hocky = 0; Nhom = 0; sosvmin = 0; sosvmax = 0;
//     huylop = false; dssvdk = nullptr;
// }
// nodeLTC::nodeLTC() { next = nullptr; }
// nodeLTC::nodeLTC(LopTinChi data) { this->ltc = data; this->next = nullptr; }
stackNode* newNode(ActionLTC Data){
    stackNode* p= new stackNode();
    p->data=Data;
    p->next=nullptr;
    return p;
}
bool isEmpty(stackNode* &root){
    return !root;
}
void push(stackNode* &root,ActionLTC data){
     stackNode* p= newNode(data);
     p->next=root;
     root=p;
}
void pop(stackNode* &root){
    if(isEmpty(root))return;
    stackNode* tmp= root;
    root=root->next;
    delete(tmp);
}
ActionLTC top(stackNode* &root){
     return root->data;
}
void undoSuaLTC(PTRLTC &First,LopTinChi ltc){
     PTRLTC p=searchLopTinChi(First,ltc.MALOPTC);
     if(!p){
        cout<<"Khong tim thay Lop Tin Chi"<<endl;
        return;
     }
     strcpy(p->ltc.MAMH, ltc.MAMH);       
     strcpy(p->ltc.NienKhoa, ltc.NienKhoa);
     p->ltc.Hocky=ltc.Hocky;
     p->ltc.Nhom=ltc.Nhom;
     p->ltc.sosvmax=ltc.sosvmax;
     p->ltc.sosvmin=ltc.sosvmin;
}
void undoLTC(PTRLTC &First,stackNode* &root){
    if(isEmpty(root)){
        cout<<"khong co gi de hieu chinh Lop Tin Chi"<<endl;
        return;
    }
    ActionLTC act =root->data;
    pop(root);
    //them
    if(act.type==1){
       int maloptc=act.ltc.MALOPTC;
       deleteLopTinChi(First,act.ltc.MALOPTC);
       cout<<"Ban vua xoa di Lop Tin Chi vua tao voi MALOPTC la: "<<maloptc<<endl;
    }
    //xoa
    else if(act.type==2){
       insertLopTinChi(First,act.ltc);
    }
    //sua
    else if(act.type==3){
        int maloptc=act.ltc.MALOPTC;
       undoSuaLTC(First,act.ltc);
       cout<<"Ban vua quay nguoc lai du lieu cu cua MALOPTC "<<maloptc<<endl;
    }
    return;
}
void initializeStackNode(stackNode* root){root=nullptr;}
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
int deleteFirstDK(PTRDK &First){
    if(!First)return 0;
    PTRDK p = First;
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
void ClearlistDSSVDK(PTRDK &First){
      while(First!=nullptr) deleteFirstDK(First);
}
void ClearLTC(PTRLTC &First){
     while(First!=nullptr){
          ClearlistDSSVDK(First->ltc.dssvdk);
          deleteFirst(First);
          First=First->next;
     }
}
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
void showLopTinChi(PTRLTC &l){
    cout<<"Chi Tiet Cua Lop Tin Chi\nMa lop tin chi: "<<l->ltc.MALOPTC
        <<"\nMa mon hoc: "<<l->ltc.MAMH
        <<"\nNien Khoa: "<<l->ltc.NienKhoa
        <<"\nHoc ky: "<<l->ltc.Hocky
        <<"\nNhom: "<<l->ltc.Nhom
        <<"\nSo sinh vien toi da: "<<l->ltc.sosvmax
        <<"\nSo sinh vien toi thieu: "<<l->ltc.sosvmin<<endl;
}
void showDanhSachSinhVienDangKy(PTRDK &l){
     while(!l){
        cout<<l->dk.MASV<<"|"<<l->dk.DIEM<<"|"<<l->dk.HuyDK<<endl;
        l=l->next;
     }
}

bool isEmptySinhVien(PTRSV &First){ return First == nullptr; }
void insertSinhVien(PTRSV &First,SinhVien x){
    PTRSV p = new nodeSV; p->sv=x; p->next=nullptr;
    if(!First) First=p;
    else { PTRSV tmp=First; while(tmp->next) tmp=tmp->next; tmp->next=p; }
}
void insertSinhVienDangKy(PTRDK &First,DangKy svdk){
    PTRDK p=new nodeDK; 
    p->dk=svdk;
    p->next=nullptr;
    if(!First)First=p;
    else { PTRDK tmp=First; while(tmp->next) tmp=tmp->next; tmp->next=p; }
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

LopTinChi NhapLTC(){
     LopTinChi ltc;

        cout << "\n=== THEM LOP TIN CHI ===\n";
        ltc.MALOPTC = -1; // sẽ gán tự động sau

        cout << "Nhap Ma Mon Hoc: "; cin.getline(ltc.MAMH, 11);
        cout << "Nhap Nien Khoa: "; cin.getline(ltc.NienKhoa, 10);
        cout << "Nhap Hoc Ky: "; cin >> ltc.Hocky;
        cout << "Nhap Nhom: "; cin >> ltc.Nhom;
        cout << "Nhap SV Min va Max: "; cin >> ltc.sosvmin >> ltc.sosvmax;
        cin.ignore();

        return ltc;
}
void saveLopTinChi(PTRLTC &First, const string &fileLoptinchi, const string &fileSVDK){
     ofstream fLTC(fileLoptinchi);
     ofstream fSVDK(fileSVDK);
     if(!fLTC||!fSVDK){
        cout<<"Khong the mo file!"<<endl;
        return;
     }
     while(!First){
        fLTC << First->ltc.MALOPTC<<"|"
             <<First->ltc.MAMH<<"|"
             <<First->ltc.NienKhoa<<"|"
             <<First->ltc.Hocky<<"|"
             <<First->ltc.Nhom<<"|"
             <<First->ltc.sosvmin<<"|"
             <<First->ltc.sosvmax<<"|"
             <<First->ltc.huylop<<endl;
        PTRDK p=First->ltc.dssvdk;
        while(!p){
         fSVDK <<First->ltc.MALOPTC<<"|"
               <<p->dk.MASV<<"|"
               <<p->dk.DIEM<<"|"
               <<p->dk.HuyDK<<"|"<<endl;
               p=p->next; 
        }
        First=First->next;
     }
     fLTC.close();
     fSVDK.close();
}
void loadLopTinChi(PTRLTC &First, const string &fileLopTinChi, const string &fileSVDK){
     ifstream fLTC(fileLopTinChi);
     if(!fLTC){
        cout<<"Khong mo duoc file"<<endl;
        return;
     }
     string line;
     while(getline(fLTC,line)){
           if(line.empty()){
            continue;
           }
           stringstream ss(line);
           string maloptc;
           string mamh;
           string nienkhoa;
           string hk;
           string nhom;
           string svmax;
           string svmin;
           string huylop;
           getline(ss, maloptc, '|');
           getline(ss, mamh, '|');
           getline(ss, nienkhoa, '|');
           getline(ss, hk, '|');
           getline(ss, nhom, '|');
           getline(ss, svmax, '|');
           getline(ss, svmin, '|');
           getline(ss, huylop, '|');
           LopTinChi ltc;
           ltc.MALOPTC = stoi(maloptc);
           strcpy(ltc.MAMH, mamh.c_str());
           strcpy(ltc.NienKhoa, nienkhoa.c_str());
           ltc.Hocky = stoi(hk);
           ltc.Nhom = stoi(nhom);
           ltc.sosvmin = stoi(svmax);
           ltc.sosvmax = stoi(svmin);
           ltc.huylop = (huylop == "1");
           ltc.dssvdk=nullptr;
           insertLopTinChi(First, ltc);
     }
     fLTC.close();
     ifstream fSVDK(fileSVDK);
     if(!fSVDK){
        cout<<"khong mo duoc file!"<<endl;
        return;
     }
     while(getline(fSVDK,line)){
        if(line.empty())continue;
        stringstream ss(line);
        int maloptc;
        DangKy svdk;
        string temp;
        getline(ss, temp, '|'); maloptc=stoi(temp);
        getline(ss, temp, '|'); strcpy(svdk.MASV, temp.c_str());
        getline(ss, temp, '|'); svdk.DIEM=stof(temp);
        getline(ss, temp, '|'); svdk.HuyDK = (temp == "1");
        PTRLTC p=searchLopTinChi(First,maloptc);
        if(p)insertSinhVienDangKy(p->ltc.dssvdk,svdk);
     }
     fSVDK.close();

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
void saveLopSV_Binary(DS_LOPSV &ds, const string &fileLop, const string &fileSV) {
    FILE *fLop = fopen(fileLop.c_str(), "wb");
    FILE *fSV  = fopen(fileSV.c_str(), "wb");
    if(!fLop || !fSV){ 
        cout << "Khong mo duoc file!\n"; 
        return; 
    }
    fwrite(&ds.n, sizeof(int), 1, fLop);

    for(int i=0; i<ds.n; i++){
        LopSV* lop = ds.nodes[i];
        fwrite(lop->MALOP, sizeof(lop->MALOP), 1, fLop);
        fwrite(lop->TENLOP, sizeof(lop->TENLOP), 1, fLop);
        int countSV = 0;
        for(PTRSV p = lop->FirstSV; p != nullptr; p = p->next) countSV++;
        fwrite(&countSV, sizeof(int), 1, fLop);
        for(PTRSV p = lop->FirstSV; p != nullptr; p = p->next){
            fwrite(lop->MALOP, sizeof(lop->MALOP), 1, fSV);
            fwrite(&p->sv, sizeof(SinhVien), 1, fSV);
        }
    }

    fclose(fLop);
    fclose(fSV);
}
void loadLopSV_Binary(DS_LOPSV &ds, const string &fileLop, const string &fileSV) {
    FILE *fLop = fopen(fileLop.c_str(), "rb");
    if(!fLop){ 
        cout << "Khong mo duoc file LopSV!\n"; 
        return; 
    }
    fread(&ds.n, sizeof(int), 1, fLop);

    for(int i=0; i<ds.n; i++){
        LopSV* lop = new LopSV;

        fread(lop->MALOP, sizeof(lop->MALOP), 1, fLop);
        fread(lop->TENLOP, sizeof(lop->TENLOP), 1, fLop);

        int countSV;
        fread(&countSV, sizeof(int), 1, fLop);

        lop->FirstSV = nullptr;
        ds.nodes[i] = lop;
    }
    fclose(fLop);
    FILE *fSV = fopen(fileSV.c_str(), "rb");
    if(!fSV){ 
        cout << "Khong mo duoc file SinhVien!\n"; 
        return; 
    }

    while(true){
        char malop[16];
        SinhVien sv;

        if(fread(malop, sizeof(malop), 1, fSV) != 1) break; // EOF
        fread(&sv, sizeof(SinhVien), 1, fSV);

        LopSV* lop = searchLopSV(ds, malop);
        if(lop) insertSinhVien(lop->FirstSV, sv);
    }

    fclose(fSV);
}
void saveLopTinChi_Binary(PTRLTC &First, const string &fileLoptinchi, const string &fileSVDK) {
    FILE *fLTC = fopen(fileLoptinchi.c_str(), "wb");
    FILE *fSVDK = fopen(fileSVDK.c_str(), "wb");
    if(!fLTC || !fSVDK){
        cout << "Khong the mo duoc file!" << endl;
        return;
    }
    int countLTC = 0;
    for(PTRLTC p = First; p != nullptr; p = p->next) countLTC++;
    fwrite(&countLTC, sizeof(int), 1, fLTC);
    for(PTRLTC p = First; p != nullptr; p = p->next){
        fwrite(&p->ltc.MALOPTC, sizeof(int), 1, fLTC);
        fwrite(p->ltc.MAMH, sizeof(p->ltc.MAMH), 1, fLTC);
        fwrite(p->ltc.NienKhoa, sizeof(p->ltc.NienKhoa), 1, fLTC);
        fwrite(&p->ltc.Hocky, sizeof(int), 1, fLTC);
        fwrite(&p->ltc.Nhom, sizeof(int), 1, fLTC);
        fwrite(&p->ltc.sosvmin, sizeof(int), 1, fLTC);
        fwrite(&p->ltc.sosvmax, sizeof(int), 1, fLTC);
        fwrite(&p->ltc.huylop, sizeof(bool), 1, fLTC);
        int countDK = 0;
        for(PTRDK q = p->ltc.dssvdk; q != nullptr; q = q->next) countDK++;
        fwrite(&countDK, sizeof(int), 1, fSVDK);

        for(PTRDK q = p->ltc.dssvdk; q != nullptr; q = q->next){
            fwrite(&p->ltc.MALOPTC, sizeof(int), 1, fSVDK); 
            fwrite(&q->dk, sizeof(DangKy), 1, fSVDK);
        }
    }

    fclose(fLTC);
    fclose(fSVDK);
}
void loadLopTinChi_Binary(PTRLTC &First, const string &fileLoptinchi, const string &fileSVDK) {
    FILE *fLTC = fopen(fileLoptinchi.c_str(), "rb");
    if(!fLTC){
        cout << "Khong mo duoc file!" << endl;
        return;
    }

    int countLTC;
    fread(&countLTC, sizeof(int), 1, fLTC);

    for(int i=0; i<countLTC; i++){
        LopTinChi ltc;
        fread(&ltc.MALOPTC, sizeof(int), 1, fLTC);
        fread(ltc.MAMH, sizeof(ltc.MAMH), 1, fLTC);
        fread(ltc.NienKhoa, sizeof(ltc.NienKhoa), 1, fLTC);
        fread(&ltc.Hocky, sizeof(int), 1, fLTC);
        fread(&ltc.Nhom, sizeof(int), 1, fLTC);
        fread(&ltc.sosvmin, sizeof(int), 1, fLTC);
        fread(&ltc.sosvmax, sizeof(int), 1, fLTC);
        fread(&ltc.huylop, sizeof(bool), 1, fLTC);

        ltc.dssvdk = nullptr;
        insertLopTinChi(First, ltc);
    }
    fclose(fLTC);

    FILE *fSVDK = fopen(fileSVDK.c_str(), "rb");
    if(!fSVDK){
        cout << "Khong mo duoc file SVDK!" << endl;
        return;
    }

    while(true){
        int maloptc;
        DangKy dk;
        if(fread(&maloptc, sizeof(int), 1, fSVDK) != 1) break; // EOF
        if(fread(&dk, sizeof(DangKy), 1, fSVDK) != 1) break;

        PTRLTC p = searchLopTinChi(First, maloptc);
        if(p) insertSinhVienDangKy(p->ltc.dssvdk, dk);
    }

    fclose(fSVDK);
}
