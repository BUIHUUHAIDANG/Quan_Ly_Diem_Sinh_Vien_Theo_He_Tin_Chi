#ifndef CTDL_H
#define CTDL_H

#include<iostream>
#include<iomanip>
#include<cstring>
using namespace std;
const int MAX_LOPSV = 10000;
struct MonHoc {
    char MAMH[11] ; char TENMH[51]; 
    int STCLT ,STCTH; 
};
struct nodeMH {
    MonHoc mh;
    nodeMH *left, *right;
    int height;
};
typedef nodeMH* treeMH;

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


#endif

