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
    bool HuyDK=false;
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
    int currentsv;
    time_t deadline;
    bool huylop;
    PTRDK dssvdk;
    LopTinChi() {
        MALOPTC = 0; MAMH[0]=0; NienKhoa[0]=0;
        Hocky = 0; Nhom = 0; sosvmin = 0; sosvmax = 0; currentsv = 0;
        deadline = 0; huylop = false; dssvdk = nullptr;
    }
};

struct nodeLTC {
    LopTinChi ltc;
    nodeLTC *next;
    nodeLTC();
    nodeLTC(LopTinChi data);
};
typedef nodeLTC* PTRLTC;
struct ActionLTC {
    int type;
    LopTinChi ltc;
};
struct stackNode
{
    ActionLTC data;
    stackNode* next;
};



#endif
