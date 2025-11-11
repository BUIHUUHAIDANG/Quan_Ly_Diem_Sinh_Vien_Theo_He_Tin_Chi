#include "LopSinhVien.h"
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;


nodeSV::nodeSV() { next = nullptr; }
LopSV::LopSV() { FirstSV = nullptr; MALOP[0]=0; TENLOP[0]=0; }
DS_LOPSV::DS_LOPSV() { n = 0; for(int i=0;i<MAX_LOPSV;i++) nodes[i]=nullptr; }
nodeDK::nodeDK() { next = nullptr; }
LopTinChi::LopTinChi() {
    MALOPTC = 0; MAMH[0]=0; NienKhoa[0]=0;
    Hocky = 0; Nhom = 0; sosvmin = 0; sosvmax = 0;
    huylop = false; dssvdk = nullptr;
}
nodeLTC::nodeLTC() { next = nullptr; }
nodeLTC::nodeLTC(LopTinChi data) { this->ltc = data; this->next = nullptr; }


void initializeLTC(PTRLTC & First) { First = nullptr; }
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
bool editLopTinChi(PTRLTC &First,int x){
    PTRLTC p=searchLopTinChi(First,x);
    if(!p){ cout<<"khong tim thay lop tinh chi"<<endl; return false; }
    char nk[10]; cout<<"Nhap Nien Khoa ma ban muon: "; cin.getline(nk,10);
    if(strlen(nk)>0) strcpy(p->ltc.NienKhoa,nk);
    int hk; cout<<"Nhap Hoc Ky ma ban muon: "; cin>>hk; cin.ignore();
    if(hk>0) p->ltc.Hocky=hk;
    int n; cout<<"Nhap Nhom ma ban muon: "; cin>>n; if(n>0) p->ltc.Nhom=n;
    int svmin, svmax; cout<<"Nhap svmin va svmax ma ban muon: "; cin>>svmin>>svmax;
    if(svmin>0 && svmax>0 && svmin<svmax && svmax<1000){ p->ltc.sosvmin=svmin; p->ltc.sosvmax=svmax; }
    bool h; cout<<"Ban muon Huy Lop(1 la co, 0 la khong): "; cin>>h;
    if(h==0||h==1) p->ltc.huylop=h;
    cin.ignore();
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
    cout<<"Chi Tiet Cua Lop Tin Chi\nMa lop tin chi: "<<l->ltc.MALOPTC
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
bool nhapSinhVienVao1Lop(LopSV *lop){
    if(!lop) return false;
    SinhVien sv;
    while(true){
        cout<<"\nNhap ma SV (Enter de dung): "; cin.getline(sv.MASV,16);
        if(sv.MASV[0]=='\0') break;
        cout<<"Nhap ho: "; cin.getline(sv.HO,51);
        cout<<"Nhap ten: "; cin.getline(sv.TEN,11);
        cout<<"Nhap phai: "; cin.getline(sv.PHAI,4);
        cout<<"Nhap so dien thoai: "; cin.getline(sv.SODT,16);
        insertSinhVien(lop->FirstSV,sv);
    }
    cout<<"cap nhap sinh vien thanh cong"<<endl;
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
LopSV* searchLopSV(DS_LOPSV dsLop,char MALOP[16]){
    for(int i=0;i<dsLop.n;i++){
        if(strcmp(dsLop.nodes[i]->MALOP,MALOP)==0) return dsLop.nodes[i];
    }
    return nullptr;
}
