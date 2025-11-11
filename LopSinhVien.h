#ifndef LOPSV_H
#define LOPSV_H

#include <iostream>
using namespace std;

const int MAX_LOPSV = 10000;
struct SinhVien {
    char MASV[16];
    char HO[51];
    char TEN[11];
    char PHAI[4];
    char SODT[16];
    char Email[50];
};

struct nodeSV {
    SinhVien sv;
    nodeSV *next;
    nodeSV();
};
typedef nodeSV* PTRSV;

struct LopSV {
    char MALOP[16];
    char TENLOP[51];
    PTRSV FirstSV;
    LopSV();
};

struct DS_LOPSV {
    int n;
    LopSV* nodes[MAX_LOPSV];
    DS_LOPSV();
};

struct DangKy {
    char MASV[16];
    float DIEM;
    bool HuyDK;
    PTRSV sinhVien;
};

struct nodeDK {
    DangKy dk;
    nodeDK *next;
    nodeDK();
};
typedef nodeDK* PTRDK;

struct LopTinChi {
    int MALOPTC;
    char MAMH[11];
    char NienKhoa[10];
    int Hocky;
    int Nhom;
    int sosvmin, sosvmax;
    bool huylop;
    PTRDK dssvdk;
    LopTinChi();
};

struct nodeLTC {
    LopTinChi ltc;
    nodeLTC *next;
    nodeLTC();
    nodeLTC(LopTinChi data);
};
typedef nodeLTC* PTRLTC;

void initializeLTC(PTRLTC &First);
PTRLTC createNodeLopTinChi(LopTinChi data);
void insertLopTinChi(PTRLTC &First, LopTinChi data);
bool isEmpty(PTRLTC &First);
int deleteFirst(PTRLTC &First);
int deleteAfter(PTRLTC p);
int deleteLopTinChi(PTRLTC &First,int MALTC);
void Clearlist(PTRLTC &First);
PTRLTC searchLopTinChi(PTRLTC &First,int x);
PTRLTC searchLTC(PTRLTC &First,char nienkhoa[10],int hocky,int nhom,char MAMH[11]);
bool editLopTinChi(PTRLTC &First,int x);
void showDanhSachSinhVienDangKy(PTRLTC &l);
void showLopTinChi(PTRLTC &l);
bool showDSSVOfLopTinChi(PTRLTC &First,char nienkhoa[10],int hocky,int nhom,char MAMH[11]);

bool isEmptySinhVien(PTRSV &First);
void insertSinhVien(PTRSV &First,SinhVien x);
int deleteFirstSinhVien(PTRSV &First);
int deleteAfterSinhVien(PTRSV p);
int deleteSinhVien(PTRSV &First,char MASV[16]);
bool findSinhVien(PTRSV &First,char MASV[16]);
bool editSinhVien(PTRSV &sv);
bool nhapSinhVienVao1Lop(LopSV *lop);
void InDSSV_TheoTen(PTRSV first);

LopSV* searchLopSV(DS_LOPSV dsLop,char MALOP[16]);

#endif
