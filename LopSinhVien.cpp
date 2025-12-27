#include "LopSinhVien.h"
#include "CTDL.h"
#include <cstring>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <fstream>         
#include <string> 
#include <limits>     
using namespace std;


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
     if(isEmpty(root))return {};
     return root->data;
}
stackNodeSV* newNode(ActionSV Data){
     stackNodeSV* p= new stackNodeSV();
     p->data=Data;
     p->next=nullptr;
     return p;
}
bool isEmpty(stackNodeSV* &root){
     return !root;
}
void push(stackNodeSV* &root, ActionSV data){
     stackNodeSV* p=newNode(data);
     p->next=root;
     root=p;
}
void pop(stackNodeSV* &root){
     if(isEmpty(root))return;
     stackNodeSV* tmp=root;
     root=root->next;
     delete(tmp);
}
ActionSV top(stackNodeSV* &root){
     return root->data;
}
void undoSuaSV(PTRSV &First,SinhVien sv){
     PTRSV p=getSinhVienv2(First,sv.MASV);
     if(p==nullptr){
        cout<<"Sinh vien khong co ton tai"<<endl;
        return;
     }
     strcpy(p->sv.HO,sv.HO);
     strcpy(p->sv.TEN,sv.TEN);
     strcpy(p->sv.PHAI,sv.PHAI);
     strcpy(p->sv.SODT,sv.SODT);
     strcpy(p->sv.Email,sv.Email);
}
void undoSV(PTRSV &First, stackNodeSV* &root){
     if(isEmpty(root)){
        cout<<"Khong co gi de hieu chinh"<<endl;
     }
     ActionSV p=root->data;
     pop(root);
     //them
     if(p.type==1){
       //function xoa
       deleteSinhVien(First,p.sv.MASV);
     }
     //xoa
     else if(p.type==2){
       //function them
       insertSinhVien(First,p.sv);
     }
     //sua
     else if(p.type==3){
       //function Hoan Tac
       undoSuaSV(First,p.sv);
     }
}
bool deleteFirstStackSV(stackNodeSV* &root){
     if(root==nullptr)return 0;
     stackNodeSV* p=root;
     root=root->next;
     delete p;
     return 1; 
}
void ClearStackSV(stackNodeSV* &dsnode){
    while(dsnode!=nullptr){
         deleteFirstStackSV(dsnode);
    }
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
void showDanhSachSinhVienDangKy(PTRDK &l){
    PTRDK p=l;
     while(p){
        cout<<p->dk.MASV<<"|"<<p->dk.DIEM<<"|"<<p->dk.HuyDK<<endl;
        p=p->next;
     }
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

PTRSV GetLop(DS_LOPSV &dslop, char malop[16]) {
    PTRSV FirstSV = nullptr;
    for(int i=0; i<dslop.n; i++) {
        if(strcmp(malop,dslop.nodes[i]->MALOP) == 0) {
            FirstSV = dslop.nodes[i]->FirstSV;
            break;
        }
    }
    return FirstSV;
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

int getNumOfSinhVien( char MaSV[]){
    int length=strlen(MaSV);
    int result=0;
    for(int i=length-3;i<length;i++){
        result=result*10+(MaSV[i]-'0');
    }
    return result;
}

PTRSV getSinhVienv2(PTRSV &First, char masv[16]){
      if (First == nullptr) return nullptr;

    int target = getNumOfSinhVien(masv);
    PTRSV p = First;

    while (p != nullptr) {
        int curr = getNumOfSinhVien(p->sv.MASV);

        if (curr == target && strcmp(p->sv.MASV,masv) == 0)
            return p;

        if (curr > target) 
            return nullptr;

        p = p->next;
    }
    return nullptr;
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
bool CheckLopSV(DS_LOPSV dslop, LopSV lop) { // Kiem tra xem lop sinh vien co trong danh sach lop sinh vien khong
                                             // Neu co thi tra ve true
    if (dslop.n==0) return false;
    for(int i = 0; i< dslop.n; i++) {
        if ((strcmp(lop.MALOP, dslop.nodes[i]->MALOP) == 0)) return true;
    }
    return false;
}
//fix NhapSV()
void NhapSV(DS_LOPSV &dslop) {
    // LoadFile_LopSV("LopSinhVien.txt", dslop); 
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
                // InsertSV(dslop.nodes[i]->FirstSV,sv);
                break;
            }
        }
        cout << "Luu thanh cong!\n\n";
    }
}
void NhapLopSV(DS_LOPSV &dslop){
    // LoadFile_LopSV("LopSinhVien.txt",dslop);
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
        insertSinhVienDangKy(FirstLTC->ltc.dssvdk, pnode->dk);
        cout << " Dang ky thanh cong!\n";
    }
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

bool isValidSoSV(int min, int max) {
    return min > 0 && max > 0 && min <= max;
}
void formatName(char s[]) {
    int n = strlen(s);
    int i = 0, j = 0;
    while (i < n) {
        while (i < n && s[i]==' '){
            i++;
        }
        if (i >= n) break;
        s[j++] = toupper(s[i++]);
        while (i < n && s[i]!=' ') {
            s[j++] = tolower(s[i++]);
        }
        s[j++] = ' ';
    }
    if (j > 0)j--;
    s[j] = '\0';
}

bool checkformatdeadline (string s) {
    if (s.length() != 16) return false;
    if (s[4] != '-' || s[7] != '-' || s[10] != ' ' || s[13] != ':') return false;
    for (int i = 0; i < s.length(); i++) {
        if (i == 4 || i == 7 || i == 10 || i == 13) continue;
        if(!isdigit(s[i])) return false;
    }
    return true;
}

bool validdealine (time_t deadline) {
    time_t now = time(0);
    if (difftime(deadline, now) <= 0) return false;
    return true;
}

LopTinChi NhapLTC(){
    LopTinChi ltc;
    cout << "\n=== THEM LOP TIN CHI ===\n";
    ltc.MALOPTC = -1; 

    do {
    cout << "Nhap Ma Mon Hoc: ";
    cin.getline(ltc.MAMH, 11);

    if (strlen(ltc.MAMH) == 0)
    cout << "Loi: Khong duoc de trong!\n";

    } while (strlen(ltc.MAMH) == 0);

    do {
    cout << "Nhap Nien Khoa: ";
    cin.getline(ltc.NienKhoa, 10);

    if (strlen(ltc.NienKhoa) == 0)
    cout << "Loi: Khong duoc de trong!\n";

    } while (strlen(ltc.NienKhoa) == 0);

    while (true) {
    cout << "Nhap Hoc Ky: ";
    cin >> ltc.Hocky;

    if (!cin.fail() && ltc.Hocky > 0 && ltc.Hocky <=2) {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        break;
    }

    cout << "Loi! Hay nhap so nguyen > 0\n";
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    while (true) {
    cout << "Nhap Nhom: ";
    cin >> ltc.Nhom;

    if (!cin.fail() && ltc.Nhom > 0) {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        break;
    }

    cout << "Loi! Hay nhap so nguyen > 0\n";
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    do {
        cout << "Nhap SV Min va Max: ";
        cin >> ltc.sosvmin >> ltc.sosvmax;

        if (!isValidSoSV(ltc.sosvmin, ltc.sosvmax)) {
            cout << "Loi: SV Min phai <= SV Max va > 0. Nhap lai!\n";
        }
    } while (!isValidSoSV(ltc.sosvmin, ltc.sosvmax));
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
    cout << "Nhap Deadline (YYYY-MM-DD HH:MM): ";
    string deadlinestr;
    while (true) {
        getline(cin, deadlinestr);
        if (checkformatdeadline(deadlinestr) && validdealine(stringToTime(deadlinestr))) break;
        cout << "Loi: Deadline phai dung format va lon hon thoi gian hien tai. Nhap lai (YYYY-MM-DD HH:MM): ";
    }
    ltc.deadline = deadlinestr;
    ltc.huylop = false;
    ltc.dssvdk = nullptr;
    return ltc;
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
void saveLopSV_Binary(DS_LOPSV &ds, const char *fileLop, const char *fileSV) {
    FILE *fLop = fopen(fileLop, "wb");
    FILE *fSV  = fopen(fileSV, "wb");
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
void loadLopSV_Binary(DS_LOPSV &ds, const char *fileLop, const char *fileSV) {
    FILE *fLop = fopen(fileLop, "rb");
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
    FILE *fSV = fopen(fileSV, "rb");
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
void saveLopTinChi_Binary(PTRLTC &First, const char *fileLoptinchi, const char *fileSVDK) {
    FILE *fLTC = fopen(fileLoptinchi, "wb");
    FILE *fSVDK = fopen(fileSVDK, "wb");
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
        fwrite(&p->ltc.currentsv, sizeof(int), 1, fLTC);     
        fwrite(&p->ltc.deadline, sizeof(string), 1, fLTC); 

        int countDK = 0;
        for(PTRDK q = p->ltc.dssvdk; q != nullptr; q = q->next) countDK++;

        // Ghi mã lớp trước
        fwrite(&p->ltc.MALOPTC, sizeof(int), 1, fSVDK);
        
        // Ghi số lượng sinh viên đăng ký của lớp đó
        fwrite(&countDK, sizeof(int), 1, fSVDK);
        
        // Ghi toàn bộ DK
        for(PTRDK q = p->ltc.dssvdk; q != nullptr; q = q->next) {
            fwrite(&q->dk, sizeof(DangKy), 1, fSVDK);
        }
    }

    fclose(fLTC);
    fclose(fSVDK);
}
void loadLopTinChi_Binary(PTRLTC &First, const char *fileLoptinchi, const char *fileSVDK) {
    FILE *fLTC = fopen(fileLoptinchi, "rb");
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
        fread(&ltc.currentsv, sizeof(int), 1, fLTC);     
        fread(&ltc.deadline, sizeof(string), 1, fLTC);     

        ltc.dssvdk = nullptr;
        insertLopTinChi(First, ltc);
    }
    fclose(fLTC);

    FILE *fSVDK = fopen(fileSVDK, "rb");
    if(!fSVDK){
        cout << "Khong mo duoc file SVDK!" << endl;
        return;
    }

    while (true) {
    int maloptc, countDK;

    
    if (fread(&maloptc, sizeof(int), 1, fSVDK) != 1) break;

    
    fread(&countDK, sizeof(int), 1, fSVDK);

    PTRLTC p = searchLopTinChi(First, maloptc);

    while (countDK--) {
        DangKy dk;
        fread(&dk, sizeof(DangKy), 1, fSVDK);
        if (p) insertSinhVienDangKy(p->ltc.dssvdk, dk);
    }
}

    fclose(fSVDK);
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
void IndiemtbLop(PTRLTC &dsltc, DS_LOPSV &dslop, treeMH &dsmh) { // In diem tb cho ca lop
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
void IndiemtbSinhvien(const PTRLTC &dsltc, const DS_LOPSV &dslop, const treeMH &dsmh) { // In diem tb cho ca nhan
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
void InbangDiemLTC(nodeLTC* dsltc, DS_LOPSV &dslop){
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
int posLop(DS_LOPSV &ds,char MALOP[16]){
    for(int i=0;i<ds.n;i++){
        if(strcmp(ds.nodes[i]->MALOP,MALOP)==0)return i;
    }
    return -1;
}
void xoaLopByPos(DS_LOPSV &ds,int pos){
    if(pos<0||pos>=ds.n)return;
    PTRSV p=ds.nodes[pos]->FirstSV;
    ClearlistSV(p);
    delete ds.nodes[pos];
    for(int i=pos;i<ds.n-1;i++){//-1 because the end of array
        ds.nodes[pos]=ds.nodes[pos+1];
    }
    ds.n--;
}
bool deleteFirstStackLTC(stackNode* &root){
    if(root==nullptr)return 0;
    stackNode* p=root;
    root=root->next;
    delete p;
    return 1;
}
void ClearStackLTC(stackNode* &dsnode){
    while(dsnode!=nullptr){
         deleteFirstStackLTC(dsnode);
    }
}
int editLopSinhVien(DS_LOPSV &ds,int pos){
    char malop[16];
    char tenlop[51];
     cout<<"[Ma Lop Sinh Vien]"<<"["<<ds.nodes[pos]->MALOP<<"] :";
     cin.getline(malop,16);
     cout<<"[Ten Lop Sinh Vien]"<<"["<<ds.nodes[pos]->TENLOP<<"] :";
     cin.getline(tenlop,51);
     if(strcmp(malop,"0")!=0){
        strcpy(ds.nodes[pos]->MALOP,malop);
     }
     else if(strcmp(ds.nodes[pos]->TENLOP,"0")!=0){
        strcpy(ds.nodes[pos]->TENLOP,tenlop);
     }
     else if(strcmp(malop,"0")==0&&strcmp(ds.nodes[pos]->TENLOP,"0")==0){
        return 0;
     }
     return 1;
}
//order
void insertSinhVienV2(PTRSV &First,SinhVien sv){
     PTRSV p,t,s;
     p=new nodeSV();
     p->sv=sv;
     p->next=nullptr;
     for(s=First;s!=nullptr&&(getNumOfSinhVien(s->sv.MASV)<getNumOfSinhVien(sv.MASV));t=s,s=s->next);
     if(s==First){
        p->next=First;
        First=p;
     }
     else{
        p->next=s;
        t->next=p;
     }
}
void insertSinhVienDKV2(PTRDK &First,DangKy svdk){
     PTRDK p,t,s;
     p= new nodeDK();
     p->dk=svdk;
     p->next=nullptr;
     for(s=First;s!=nullptr&&(getNumOfSinhVien(s->dk.MASV)<getNumOfSinhVien(svdk.MASV));t=s,s=s=s->next);
     if(s==First){
        p->next=First;
        First=p;
     }
     else{
        p->next=s;
        t->next=p;
     }
}

time_t stringToTime(string s) {
    tm t = {};
    stringstream ss(s);
    ss >> get_time(&t, "%Y-%m-%d %H:%M");
    return mktime(&t);
}

void AutoCancelExpiredClasses(PTRLTC &l) {
    time_t now = time(nullptr);

    PTRLTC cur = l;

    while (cur != nullptr) {
        bool hetHan = (now >= stringToTime(cur->ltc.deadline));
        bool thieuSV = (cur->ltc.currentsv < cur->ltc.sosvmin);

        if (hetHan && thieuSV) {
            cur->ltc.huylop = true;
        } 
        cur = cur->next;
    }
}