#include "LopSinhVien.h"
#include "CTDL.h"
#include "menu.h"
#include "MonHoc.h"
#include "mylib.h"
#include <cstring>
#include <iostream>
#include <algorithm>
#include <fstream>      
#include <sstream>      
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
       insertSinhVienV2(First,p.sv);
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

    LopTinChi old = p->ltc;

    cout << "\n=== CHINH SUA LOP TIN CHI ===\n";
    cout << "(Enter = giu nguyen)\n\n";

    inputOrKeep(p->ltc.MAMH, 11, old.MAMH, "Ma Mon Hoc");
    inputOrKeep(p->ltc.NienKhoa, 10, old.NienKhoa, "Nien Khoa");

    p->ltc.Hocky   = inputIntOrKeep(old.Hocky, "Hoc Ky", true);
    p->ltc.Nhom    = inputIntOrKeep(old.Nhom, "Nhom", false);
    p->ltc.sosvmin = inputIntOrKeep(old.sosvmin, "SV Min", false);
    p->ltc.sosvmax = inputIntOrKeep(old.sosvmax, "SV Max", false);

    if (p->ltc.sosvmin > p->ltc.sosvmax) {
        cout << "SV Min khong duoc lon hon SV Max!\n";
        p->ltc = old;
        return false;
    }

    return true;
}
int DemSoLTC(PTRLTC FirstLTC) {
    int cnt = 0;
    for (PTRLTC p = FirstLTC; p != nullptr; p = p->next)
        cnt++;
    return cnt;
}
int TinhTrangHienTai(PTRLTC FirstLTC, PTRLTC currPage) {
    int pos = 0;
    for (PTRLTC p = FirstLTC; p != currPage; p = p->next)
        pos++;
    return pos / 5 + 1;
}
PTRLTC In1TrangLTC_Bang(PTRLTC start) {
    PTRLTC p = start;
    int dem = 0;

    int x = 2;
    int y = 4;
    int w = 110;   

    gotoxy(x + 2, y);
    SetBold(true);
    SetColor(11);
    cout << left
         << setw(10) << "MaLTC"
         << setw(10) << "MaMH"
         << setw(12) << "NienKhoa"
         << setw(6)  << "HK"
         << setw(6)  << "Nhom"
         << setw(8)  << "Min"
         << setw(8)  << "Max"
         << setw(10) << "DangKy"     
         << setw(20) << "Deadline"  
         << setw(20) << "HuyLop"; 
    ResetColor();
    SetBold(false);

    drawLine(x + 1, y + 1, w - 2);

    int row = y + 2;
    while (p != nullptr && dem < 5) {
        gotoxy(x + 2, row++);
        cout << left
             << setw(10) << p->ltc.MALOPTC
             << setw(10) << p->ltc.MAMH
             << setw(12) << p->ltc.NienKhoa
             << setw(6)  << p->ltc.Hocky
             << setw(6)  << p->ltc.Nhom
             << setw(8)  << p->ltc.sosvmin
             << setw(8)  << p->ltc.sosvmax
             << setw(10) << p->ltc.currentsv
             << setw(20) << p->ltc.deadline
             << setw(20) << (p->ltc.huylop ? "Da qua han" : "Dang mo");

        dem++;   
        p = p->next; 
    }

    return p;  
}

void InDSLTC(PTRLTC &FirstLTC) {
    if (!FirstLTC) {
        cout << "\nDanh sach LTC rong!";
        getch();
        return;
    }

    int totalLTC = DemSoLTC(FirstLTC);
    int totalPage = (totalLTC + 4) / 5;

    PTRLTC currPage = FirstLTC;
    PTRLTC nextPage = nullptr;

    while (true) {
        clrscr();

        int x = 1;
        int y = 1;
        int w = 114;
        int h = 14;

        DrawBox(x, y, w, h, 7, 0);

        gotoxy(x + 45, y + 1);
        SetBold(true);
        SetColor(14);
        cout << "DANH SACH LOP TIN CHI";
        ResetColor();
        SetBold(false);

        nextPage = In1TrangLTC_Bang(currPage);

        int currPageIndex = TinhTrangHienTai(FirstLTC, currPage);

        drawLine(x + 1, y + h - 3, w - 2);
        gotoxy(x + 2, y + h - 2);
        SetColor(10);
        cout << "Trang " << currPageIndex << "/" << totalPage
             << "   [A] Truoc   [D] Sau   [ESC] Thoat";
        ResetColor();

        char key = getch();

        if (key == 27) break;

        if ((key == 'd' || key == 'D') && nextPage != nullptr) {
            currPage = nextPage;
        }

        if (key == 'a' || key == 'A') {
            PTRLTC p = FirstLTC;
            PTRLTC prevPage = FirstLTC;

            while (p != currPage) {
                prevPage = p;
                for (int i = 0; i < 5 && p != currPage; i++)
                    p = p->next;
            }
            currPage = prevPage;
        }
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
PTRDK In1TrangSVDK_Bang(PTRDK start, DS_LOPSV dslop) {
    PTRDK p = start;
    int dem = 0;

    int x = 4;
    int y = 4;
    int w = 80;

    // ===== HEADER =====
    gotoxy(x + 2, y);
    SetBold(true);
    SetColor(11);
    cout << left
         << setw(12) << "MASV"
         << setw(25) << "HO"
         << setw(12) << "TEN"
         << setw(8)  << "DIEM"
         << setw(8)  << "HUYDK";
    ResetColor();
    SetBold(false);

    drawLine(x + 1, y + 1, w - 2);

    // ===== DATA =====
    int row = y + 2;
    while (p != nullptr && dem < 5) {
        SinhVien sv = getSinhVien(dslop, p->dk.MASV);

        gotoxy(x + 2, row);
        cout << left << setw(12) << p->dk.MASV;

        if (strlen(sv.MASV) != 0) {
            cout << setw(25) << sv.HO
                 << setw(12) << sv.TEN;
        } else {
            cout << setw(25) << "(Khong tim thay)"
                 << setw(12) << "";
        }

        cout << setw(8) << p->dk.DIEM
             << setw(8) << p->dk.HuyDK;

        row++;
        p = p->next;
        dem++;
    }

    return p;   // trang kế
}

int DemSoSVDK(PTRDK l) {
    int cnt = 0;
    for (PTRDK p = l; p != nullptr; p = p->next)
        cnt++;
    return cnt;
}
int TinhTrangHienTai(PTRDK First, PTRDK currPage) {
    int pos = 0;
    for (PTRDK p = First; p != currPage; p = p->next)
        pos++;
    return pos / 5 + 1;
}
void showDanhSachSinhVienDangKy(PTRDK &l, DS_LOPSV dslop) {
    if (l == nullptr) {
        cout << "Khong Co Sinh Vien Dang Ky\n";
        cout << "Nhap bat ky phim nao de quay lai...";
        getch();
        return;
    }

    int totalSV = DemSoSVDK(l);
    int totalPage = (totalSV + 4) / 5;

    PTRDK currPage = l;
    PTRDK nextPage = nullptr;

    int x = 2;
    int y = 1;
    int w = 84;
    int h = 14;

    while (true) {
        clrscr();

        DrawBox(x, y, w, h, 7, 0);

        
        gotoxy(x + (w - 36) / 2, y + 1);
        SetBold(true);
        SetColor(14);
        cout << "DANH SACH SINH VIEN DANG KY";
        ResetColor();
        SetBold(false);

        nextPage = In1TrangSVDK_Bang(currPage, dslop);

        int currPageIndex = TinhTrangHienTai(l, currPage);


        drawLine(x + 1, y + h - 3, w - 2);
        gotoxy(x + 2, y + h - 2);
        SetColor(10);
        cout << "Trang " << currPageIndex << "/" << totalPage
             << "   [A] Truoc   [D] Sau   [ESC] Thoat";
        ResetColor();

        
        char key = getch();

        if (key == 27) break;

        if ((key == 'd' || key == 'D') && nextPage != nullptr)
            currPage = nextPage;

        if ((key == 'a' || key == 'A')) {
            PTRDK p = l;
            PTRDK prevPage = l;

            while (p != currPage) {
                prevPage = p;
                for (int i = 0; i < 5 && p != currPage; i++)
                    p = p->next;
            }
            currPage = prevPage;
        }
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
int getNumOfSinhVien(char MaSV[]){
    int length=strlen(MaSV);
    if (length < 3) return -1;

    int result=0;
    for(int i=length-3;i<length;i++){
        result=result*10+(MaSV[i]-'0');
    }
    return result;
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
    if (First == nullptr) return 0;

    int target = getNumOfSinhVien(MASV);

    if (getNumOfSinhVien(First->sv.MASV) == target &&
        strcmp(First->sv.MASV, MASV) == 0)
        return deleteFirstSinhVien(First);

    PTRSV p = First;
    while (p->next != nullptr) {
        int nextNum = getNumOfSinhVien(p->next->sv.MASV);

        if (nextNum == target && strcmp(p->next->sv.MASV, MASV) == 0)
            return deleteAfterSinhVien(p);

        if (nextNum > target)
            break;

        p = p->next;
    }
    return 0;
}
bool findSinhVien(PTRSV &First,char MASV[16]){
    PTRSV p=First;
    while(p!=nullptr){ if(strcmp(p->sv.MASV,MASV)==0) return true; p=p->next; }
    return false;
}
bool editSinhVien(PTRSV &First, char MASV[16]){
    PTRSV p = getSinhVienv2(First, MASV);
    if (!p) {
        cout << "Khong tim thay sinh vien!\n";
        return false;
    }

    SinhVien old = p->sv;

    cout << "\n=== CHINH SUA SINH VIEN ===\n";
    cout << "(Enter = giu nguyen)\n\n";

    inputOrKeep(p->sv.HO,   51, old.HO,   "Ho");
    inputOrKeep(p->sv.TEN,  11, old.TEN,  "Ten");
    inputOrKeep(p->sv.PHAI, 4,  old.PHAI, "Phai");
    inputOrKeep(p->sv.SODT, 16, old.SODT, "So DT");
    inputOrKeep(p->sv.Email,50, old.Email,"Email");

    formatName(p->sv.HO);
    formatName(p->sv.TEN);

    return true;
}
void toUpperCase(char s[]) {
    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] >= 'a' && s[i] <= 'z') {
            s[i] = s[i] - ('a' - 'A');
        }
    }
}
void NhapSinhVien(DS_LOPSV ds){
    gotoxy(10, 10);
    cout << "=== NHAP SINH VIEN VAO LOP ===\n";
    char malop[16];
    cout << "Nhap Ma Lop: ";
    cin.getline(malop, 16);
    toUpperCase(malop);
    LopSV *lop = searchLopSV(ds, malop);
    if (!lop) {
        cout << "Khong tim thay lop!\n";
        getch();
        return;
    }
    cout << "Ten lop: " << lop->TENLOP << endl;
    SinhVien sv;
    while (true) {
        cout << "\nNhap ma SV (Enter de dung): ";
        cin.getline(sv.MASV, 16);
        toUpperCase(sv.MASV);
        if (sv.MASV[0] == '\0') break;
        if (checkSV(ds,sv)){
            cout<<"Ma Sinh Vien da ton tai vui long nhap lai...."<<endl;
            continue;
        }
        do
        {
        cout<<"nhap Ho: ";
        cin.getline(sv.HO,51);
        if(strlen(sv.HO)==0){
          cout<<"Khong duoc bo trong"<<endl;
        }
        } while (strlen(sv.HO)==0);
        do
        {
        cout << "Nhap ten: "; cin.getline(sv.TEN, 11);
        if(strlen(sv.TEN)==0){
          cout<<"Khong duoc bo trong"<<endl;
        }
        } while (strlen(sv.TEN)==0);
        do
        {
        cout << "Nhap phai: "; cin.getline(sv.PHAI, 4);
        if(strlen(sv.PHAI)==0){
          cout<<"Khong duoc bo trong"<<endl;
        }
        } while (strlen(sv.PHAI)==0);
        do
        {
        cout << "Nhap so dien thoai: "; cin.getline(sv.SODT, 16);
        if(strlen(sv.SODT)==0){
          cout<<"Khong duoc bo trong"<<endl;
        }
        } while (strlen(sv.SODT)==0);
        do
        {
        cout << "Nhap email: "; cin.getline(sv.Email, 50);
        if(strlen(sv.Email)==0){
          cout<<"Khong duoc bo trong"<<endl;
        }
        } while (strlen(sv.Email)==0);
        formatName(sv.HO);
        formatName(sv.TEN);
        insertSinhVienV2(lop->FirstSV, sv);
    }

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
    if (dslop.n == 0) {
        cout << "\nDanh sach LopSV rong!";
        getch();
        return;
    }

    int page = 1;
    int pageSize = 5;
    int totalPage = (dslop.n + pageSize - 1) / pageSize;

    
    int x = 6;
    int y = 2;
    int w = 70;
    int h = pageSize + 9;

    while (true) {
        clrscr();

        DrawBox(x, y, w, h, 7, 0);

        gotoxy(x + (w - 24) / 2, y + 1);
        SetBold(true);
        SetColor(14);
        cout << "DANH SACH LOP SINH VIEN";
        ResetColor();
        SetBold(false);


        gotoxy(x + 2, y + 3);
        SetBold(true);
        SetColor(11);
        cout << left
             << setw(10) << "STT"
             << setw(15) << "MA LOP"
             << setw(30) << "TEN LOP";
        ResetColor();
        SetBold(false);

        drawLine(x + 1, y + 4, w - 2);

        int start = (page - 1) * pageSize;
        int end = min(start + pageSize, dslop.n);

        int row = y + 5;
        for (int i = start; i < end; i++) {
            gotoxy(x + 2, row++);
            cout << left
                 << setw(10) << (i + 1)
                 << setw(15) << dslop.nodes[i]->MALOP
                 << setw(30) << dslop.nodes[i]->TENLOP;
        }

        drawLine(x + 1, y + h - 3, w - 2);
        gotoxy(x + 2, y + h - 2);
        SetColor(10);
        cout << "Trang " << page << " / " << totalPage
             << "   [A] Truoc   [D] Sau   [ESC] Thoat";
        ResetColor();

        char key = getch();

        if (key == 27) break;
        if ((key == 'd' || key == 'D') && page < totalPage) page++;
        if ((key == 'a' || key == 'A') && page > 1) page--;
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
void NhapLopSV(DS_LOPSV &dslop){
    // LoadFile_LopSV("LopSinhVien.txt",dslop);
    if (dslop.n >= MAX_LOPSV) {
        cout << "Da dat so luong lop toi da!\n";
        return;
    }
    while (true) {
        LopSV lop;

        cout << "\nNhap Ma Lop (Nhap 0 de thoat):"; cin.getline(lop.MALOP,16);
        toUpperCase(lop.MALOP);
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
        insertSinhVienDangKy(pltc->ltc.dssvdk, pnode->dk);
        cout << " Dang ky thanh cong!\n";
    }
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
void in1TrangSV(SinhVien arr[], int n, int page, int pageSize) {
    int start = (page - 1) * pageSize;
    int end = start + pageSize;
    if (end > n) end = n;

    cout << left
         << setw(5)  << "STT"
         << setw(15) << "MaSV"
         << setw(20) << "Ho"
         << setw(15) << "Ten"
         << setw(8)  << "Phai"
         << setw(15) << "SDT"
         << setw(25) << "Email"
         << endl;

    cout << "-------------------------------------------------------------------------------\n";

    for (int i = start; i < end; i++) {
        cout << left
             << setw(5)  << (i + 1)
             << setw(15) << arr[i].MASV
             << setw(20) << arr[i].HO
             << setw(15) << arr[i].TEN
             << setw(8)  << arr[i].PHAI
             << setw(15) << arr[i].SODT
             << setw(25) << arr[i].Email
             << endl;
    }
}
void printDSSV_sorted(LopSV *lop) {
    if(!lop || !lop->FirstSV) {
        cout << "Lop khong co sinh vien!\n";
        getch();
        return;
    }

    int n = 0;
    PTRSV p = lop->FirstSV;
    while(p){ n++; p = p->next; }

    
    SinhVien* arr = new SinhVien[n];
    p = lop->FirstSV;
    for(int i = 0; i < n; i++){
        arr[i] = p->sv;
        p = p->next;
    }

    
    sortSinhVien(arr, n);

    
    int pageSize = 5;
    int page = 1;
    int totalPage = (n + pageSize - 1) / pageSize;

    while(true) {
        clrscr();

        cout << "===== DANH SACH SINH VIEN (SORT THEO TEN + HO) =====\n\n";
        in1TrangSV(arr, n, page, pageSize);

        cout << "\nTrang " << page << " / " << totalPage;
        cout << "    [A] Truoc   [D] Sau   [ESC] Thoat";

        char key = getch();

        if(key == 27) break;

        if((key == 'd' || key == 'D') && page < totalPage)
            page++;

        if((key == 'a' || key == 'A') && page > 1)
            page--;
    }

    delete[] arr;
}
void printDSSV(LopSV *lop) {
    if(!lop || !lop->FirstSV) {
        cout << "Lop khong co sinh vien!\n";
        getch();
        return;
    }
    int n = 0;
    PTRSV p = lop->FirstSV;
    while(p){ n++; p = p->next; }

    
    SinhVien* arr = new SinhVien[n];
    p = lop->FirstSV;
    for(int i = 0; i < n; i++){
        arr[i] = p->sv;
        p = p->next;
    }
    int pageSize = 5;
    int page = 1;
    int totalPage = (n + pageSize - 1) / pageSize;

    while(true) {
        clrscr();

        cout << "===== DANH SACH SINH VIEN =====\n\n";
        in1TrangSV(arr, n, page, pageSize);

        cout << "\nTrang " << page << " / " << totalPage;
        cout << "    [A] Truoc   [D] Sau   [ESC] Thoat";

        char key = getch();

        if(key == 27) break;

        if((key == 'd' || key == 'D') && page < totalPage)
            page++;

        if((key == 'a' || key == 'A') && page > 1)
            page--;
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
LopTinChi NhapLTC(treeMH t){
    LopTinChi ltc;
    cout << "\n=== THEM LOP TIN CHI ===\n";
    ltc.MALOPTC = -1; 

    char tempMAMH[11];
    while (true) {
        cout << "Nhap Ma Mon Hoc: ";
        cin.getline(tempMAMH, 11);

        toUpperCase(tempMAMH);

        if (strlen(tempMAMH) == 0) {
            cout << "Loi: Khong duoc de trong!\n";
            continue;
        }

        if (timMonHoc(t, tempMAMH) == nullptr) {
            cout << "Loi: Ma mon hoc khong ton tai!\n";
            continue;
        }
        break;
    }
    strcpy(ltc.MAMH, tempMAMH);

    char tempNienKhoa[10];
    while (true) {
        cout << "Nhap Nien Khoa: ";
        cin.getline(tempNienKhoa, 10);

        if (strlen(tempNienKhoa) == 0) {
            cout << "Loi: Khong duoc de trong!\n";
            continue;
        }
        break;
    }
    strcpy(ltc.NienKhoa, tempNienKhoa);

    int tempHK;
    while (true) {
    cout << "Nhap Hoc Ky: ";
    cin >> tempHK;

    if (!cin.fail() && tempHK > 0 && tempHK <=3) {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        break;
    }

    cout << "Loi! Hay nhap so nguyen > 0\n";
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    ltc.Hocky = tempHK;

    int tempNhom;
    while (true) {
    cout << "Nhap Nhom: ";
    cin >> tempNhom;

    if (!cin.fail() && tempNhom > 0) {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        break;
    }

    cout << "Loi! Hay nhap so nguyen > 0\n";
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    ltc.Nhom = tempNhom;

    int tempSVMIN, tempSVMAX;
    while (true) {
        cout << "Nhap SV Min va Max: ";
        cin >> tempSVMIN >> tempSVMAX;

        if (!cin.fail() && isValidSoSV(tempSVMIN, tempSVMAX)) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;
        }

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Loi: SV Min phai <= SV Max va > 0. Nhap lai!\n";
    }
    ltc.sosvmin = tempSVMIN;
    ltc.sosvmax = tempSVMAX;

    cout << "Nhap Deadline (YYYY-MM-DD HH:MM): ";
    char deadlinechar[17];

    while (true) {
        cin.getline(deadlinechar, 17);
        string deadlinestr = deadlinechar;

        if (checkformatdeadline(deadlinestr) &&
            validdealine(stringToTime(deadlinestr))) {
            break;
        }

        cout << "Loi: Deadline khong hop le. Nhap lai (YYYY-MM-DD HH:MM): ";
    }

    strcpy(ltc.deadline, deadlinechar);
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
void inputOrKeep(char dest[], int maxLen, const char oldValue[], const char *label) {
    char buf[100];

    while (true) {
        cout << label << " [" << oldValue << "]: ";
        cin.getline(buf, sizeof(buf));

        if (strlen(buf) == 0) {     // Enter
            strcpy(dest, oldValue);
            return;
        }

        if (strlen(buf) < maxLen) {
            strcpy(dest, buf);
            return;
        }

        cout << "Du lieu qua dai! Nhap lai.\n";
    }
}
int inputIntOrKeep(int oldValue, const char *label, bool smaller3) {
    char buf[50];
    int x;

    while (true) {
        cout << label << " [" << oldValue << "]: ";
        cin.getline(buf, sizeof(buf));

        if (strlen(buf) == 0)
            return oldValue;

        char *end;
        x = strtol(buf, &end, 10);

        if (*end == '\0' && x > 0 && (!smaller3 || x <= 3))
            return x;

        cout << "Nhap sai! Hay nhap so hop le.\n";
    }
}
PTRLTC findLTCByParams(PTRLTC FirstLTC) {
    char nienkhoa[10], MAMH[11];
    int hocky, nhom;

    do {
    cout << "Nhap Nien Khoa: ";
    cin.getline(nienkhoa, 10);

    if (strlen(nienkhoa) == 0)
    cout << "Loi: Khong duoc de trong!\n";

    } while (strlen(nienkhoa) == 0);

    while (true) {
    cout << "Nhap Hoc Ky: ";
    cin >> hocky;

    if (!cin.fail() && hocky > 0 && hocky <=2) {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        break;
    }

    cout << "Loi! Hay nhap so nguyen > 0\n";
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    while (true) {
    cout << "Nhap Nhom: ";
    cin >> nhom;

    if (!cin.fail() && nhom > 0) {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        break;
    }

    cout << "Loi! Hay nhap so nguyen > 0\n";
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    do {
    cout << "Nhap Ma Mon Hoc: ";
    cin.getline(MAMH, 11);

    if (strlen(MAMH) == 0)
    cout << "Loi: Khong duoc de trong!\n";

    } while (strlen(MAMH) == 0);
    toUpperCase(MAMH);
    
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
        if(lop) insertSinhVienV2(lop->FirstSV, sv);
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
        fwrite(&p->ltc.deadline, sizeof(p->ltc.deadline), 1, fLTC); 

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
        fread(&ltc.deadline, sizeof(ltc.deadline), 1, fLTC);     

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
    SetColor(5);
    cout << "\nNhap ma lop: ";
    cin.getline(malop, 16);
    ResetColor();

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
    PTRSV arr[500];
    int count = 0;
    for (PTRSV p = lop->FirstSV; p != nullptr; p = p->next) arr[count++] = p;
    BangDiemTB(arr,count,dsltc,dslop,dsmh,lop);
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
                SetBold(true);
                SetColor(4);
                cout << "\n             -==== DIEM TRUNG BINH ====- \n";
                SetBold(false);
                ResetColor();
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

void getmonhocDK(bool MHdaDK[], int soMH, char dsMAMH[][11], const char MASV[], PTRLTC dsltc) {
    for(int i=0; i<soMH; i++) MHdaDK[i] = false;
    for (PTRLTC cur = dsltc; cur != nullptr; cur = cur->next) {
        if (cur->ltc.huylop) continue;
        for (PTRDK dk = cur->ltc.dssvdk; dk != nullptr; dk = dk->next) {
            if(dk->dk.HuyDK) continue; 
            if (strcmp(dk->dk.MASV, MASV) == 0) {
                for (int j = 0; j < soMH; j++) {
                    if (strcmp(dsMAMH[j], cur->ltc.MAMH) == 0) {
                        MHdaDK[j] = true;
                        break;
                    }
                }
            }
        }
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
                bool MHdaDK[200];
                getmonhocDK(MHdaDK,soMH,dsMAMH,MASV,dsltc);
                cout << " -==== DIEM TONG KET ====- ";
                cout << "\nLop: " << lop->TENLOP << endl;
                cout << left <<setw(15) << "MASV" << setw(25) << "HO TEN";
                for (int j = 0; j < soMH; j++) {
                    if(MHdaDK[j]) cout << setw(8) << dsMAMH[j];
                }
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
                    if(!MHdaDK[j]) continue; // skip mon hoc khong dk
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
void duyettreeMH(treeMH t, char dsMAMH[][11], int &soMH) {
    if (t == nullptr) return;
    duyettreeMH(t->left, dsMAMH, soMH);
    strcpy(dsMAMH[soMH++], t->mh.MAMH);
    duyettreeMH(t->right, dsMAMH, soMH);
}
void InbangdiemtongketLop( PTRLTC &dsltc,  DS_LOPSV &dslop,  treeMH &dsmh) {
    char malop[16];
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
        cout << "(Nhan phim bat ky de quay lai...)";
        getch(); 
        return;
    }
    PTRSV arr[500];
    int count = 0;
    for (PTRSV p = lop->FirstSV; p != nullptr; p = p->next) arr[count++] = p;
    BangDiemTK(arr,count,dsltc,dslop,dsmh,lop);
}
const char *featuresdiem[] = {"Sua diem", "← Quay lai"};
int n_featuressuadiem = sizeof(featuresdiem) / sizeof(featuresdiem[0]);
void NhapDiem(PTRLTC &FirstLTC, DS_LOPSV &dslop) {
    char nienkhoa[10], mamh[11];
    int hocky, nhom;
    do {
    cout << "Nhap Nien Khoa: ";
    cin.getline(nienkhoa, 10);

    if (strlen(nienkhoa) == 0)
    cout << "Loi: Khong duoc de trong!\n";

    } while (strlen(nienkhoa) == 0);

    while (true) {
    cout << "Nhap Hoc Ky: ";
    cin >> hocky;

    if (!cin.fail() && hocky > 0 && hocky <=2) {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        break;
    }

    cout << "Loi! Hay nhap so nguyen > 0\n";
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    while (true) {
    cout << "Nhap Nhom: ";
    cin >> nhom;

    if (!cin.fail() && nhom > 0) {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        break;
    }

    cout << "Loi! Hay nhap so nguyen > 0\n";
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    do {
    cout << "Nhap Ma Mon Hoc: ";
    cin.getline(mamh, 11);

    if (strlen(mamh) == 0)
    cout << "Loi: Khong duoc de trong!\n";

    } while (strlen(mamh) == 0);
    toUpperCase(mamh);
    PTRLTC cur = FirstLTC;
    PTRLTC ltc = nullptr;
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
        cout << "\nNhan phim bat ky de quay lai...";
        getch();
        return;
    }
    if (ltc->ltc.huylop) {
        cout << "\n\nLop tin chi nay da bi huy, khong the nhap diem!\n";
        cout << "\nNhan phim bat ky de quay lai...";
        getch();
        return;
    }
    if (ltc->ltc.dssvdk == nullptr) {
        cout << "\n\nKhong co sinh vien dang ky lop tin chi nay!\n";
        cout << "\nNhan phim bat ky de quay lai...";
        getch();
        return;
    }
    PTRDK arr[500];
    int count = 0;
    for (PTRDK p = cur->ltc.dssvdk; p != nullptr; p = p->next) arr[count++] = p;
    BangDiem_Interact(arr,count, dslop);
}
void InbangDiemLTC(nodeLTC* dsltc, DS_LOPSV &dslop) {
    char nienkhoa[10], mamh[11];
    int hocky, nhom;
    cout << "\n";
    do {
    cout << "Nhap Nien Khoa: ";
    cin.getline(nienkhoa, 10);

    if (strlen(nienkhoa) == 0)
    cout << "Loi: Khong duoc de trong!\n";

    } while (strlen(nienkhoa) == 0);

    while (true) {
    cout << "Nhap Hoc Ky: ";
    cin >> hocky;

    if (!cin.fail() && hocky > 0 && hocky <=2) {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        break;
    }

    cout << "Loi! Hay nhap so nguyen > 0\n";
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    while (true) {
    cout << "Nhap Nhom: ";
    cin >> nhom;

    if (!cin.fail() && nhom > 0) {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        break;
    }

    cout << "Loi! Hay nhap so nguyen > 0\n";
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    do {
    cout << "Nhap Ma Mon Hoc: ";
    cin.getline(mamh, 11);

    if (strlen(mamh) == 0)
    cout << "Loi: Khong duoc de trong!\n";

    } while (strlen(mamh) == 0);
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
        cout << "\nNhan phim bat ky de quay lai...";
        getch();
        return;
    }
    if (ltc->ltc.huylop) {
        cout << "Lop tin chi nay da bi huy, khong the nhap diem!\n";
        cout << "\nNhan phim bat ky de quay lai...";
        getch();
        return;
    }
    if (ltc->ltc.dssvdk == nullptr) {
        cout << "Khong co sinh vien dang ky lop tin chi nay!\n";
        cout << "\nNhan phim bat ky de quay lai...";
        getch();
        return;
    }
    PTRDK arr[500];
    int count = 0;
    for (PTRDK p = cur->ltc.dssvdk; p != nullptr; p = p->next) arr[count++] = p;
    BangDiemLTC(arr,count,dslop);
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
        string temp = cur->ltc.deadline;
        bool hetHan = (now >= stringToTime(temp));
        bool thieuSV = (cur->ltc.currentsv < cur->ltc.sosvmin);

        if (hetHan && thieuSV) {
            cur->ltc.huylop = true;
        } 
            cur = cur->next;
    }
}



