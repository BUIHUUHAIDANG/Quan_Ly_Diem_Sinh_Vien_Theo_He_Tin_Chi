#ifndef CTDL_H
#define CTDL_H

#include<iostream>
#include<iomanip>
#include<cstring>
#include<ctime>
using namespace std;
/// @brief Cấu trúc dữ liệu và các hàm hỗ trợ cho quản lý điểm sinh viên theo hệ tín chỉ
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
    bool huylop;
    PTRDK dssvdk;
    int currentsv;
    time_t deadline;
    LopTinChi();
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
struct ActionSV {
    int type;
    SinhVien sv;
};
struct stackNodeSV
{
    ActionSV data;
    stackNodeSV* next;
};
struct ActionMH {
    int type = 0; //1 = them, 2 = xoa, 3 = sua mh
    MonHoc mh;
};

struct node {
    ActionMH data;
    node* next;
};

typedef node* PTRNode;

struct stack {
    node* top = nullptr; // đỉnh stack
};



#endif