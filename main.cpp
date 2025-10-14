#include<iostream>
using namespace std;

const int MAX_LOPSV = 10000;
struct MonHoc {
 char MAMH[11] ; char TENMH[51]; 
 int STCLT ,STCTH; int height;
};
struct nodeMH {
 MonHoc mh;
 nodeMH *left, *right;
};
typedef nodeMH* treeMH;

struct SinhVien {
 char MASV [16]; char HO[51], ; char TEN[11];
 char  PHAI[4]; char SODT[16]; char Email [50];

};
struct nodeSV {
 SinhVien sv;
 nodeSV *next;
};
typedef nodeSV* PTRSV;

 struct LopSV  {
 char MALOP[16] ; char TENLOP[51];
 PTRSV FirstSV=NULL; 
};
struct DS_LOPSV {
 int n=0;
 LopSV* nodes[MAX_LOPSV];
};
 struct DangKy {
  char MASV[16] ; float DIEM; 
 };
 
 struct nodeDK {
 DangKy dk;
 nodeDK *next;
};
typedef nodeDK* PTRDK;

 struct LopTinChi {
  int MALOPTC ;
  char  MAMH[11];
  char NienKhoa[10];  
  int Hocky, Nhom,sosvmin, sosvmax;
  bool huylop = false;
  PTRDK dssvdk=NULL; 
 };
 
 struct nodeLTC {
  LopTinChi ltc;
  nodeLTC *next;
 };

typedef nodeLTC* PTRLTC;

 int main(){
  treeMH dsmh=NULL;
    PTRLTC dsltc=NULL; 
  DS_LOPSV dslopsv;
 }











