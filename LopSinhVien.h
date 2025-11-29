#ifndef LOPSV_H
#define LOPSV_H

#include <iostream>
#include "CTDL.h"
using namespace std;
stackNode* newNode(ActionLTC data);
bool isEmpty(stackNode* &root);
void push(stackNode* &root,ActionLTC data);
void pop(stackNode* &root);
ActionLTC top(stackNode* &root);
void undoSuaLTC(PTRLTC &First,LopTinChi ltc);
void undoLTC(PTRLTC &First,stackNode* &root);
void initializeStackNode(stackNode* &root);
void initializeLTC(PTRLTC &First);
void initializeSV(PTRSV & FirstSV);
PTRLTC createNodeLopTinChi(LopTinChi data);
void insertLopTinChi(PTRLTC &First, LopTinChi data);//Same with insertLast_LTC
bool isEmpty(PTRLTC &First);//checked 
int deleteFirst(PTRLTC &First);//checked
int deleteFirstDK(PTRDK &First);
int deleteAfter(PTRLTC p);
int deleteLopTinChi(PTRLTC &First,int MALTC);
void ClearlistDSSVDK(PTRDK &First);
void ClearLTC(PTRLTC &First);// same with deleteDSLTC
void ClearlistSV(PTRSV &First);
void ClearDS_Lop(DS_LOPSV &ds);// it is a combination of two functions deleteDSSV and DeleteDSlopSV
PTRLTC searchLopTinChi(PTRLTC &First,int x);
PTRLTC searchLTC(PTRLTC &First,char nienkhoa[10],int hocky,int nhom,char MAMH[11]);
bool editLopTinChi(PTRLTC &First,int x);
void showDanhSachSinhVienDangKy(PTRDK &l);
void InDSSVDK(PTRLTC &FirstLTC, int maloptc, DS_LOPSV &dslop);// problem 
void InDSLTC(PTRLTC &l);//checked
bool checkLTC(PTRLTC FirstLTC, LopTinChi ltc);// take it from Minh



bool isEmptySinhVien(PTRSV &First);
void insertSinhVien(PTRSV &First,SinhVien x);// same with insertSV of Minh
void insertSinhVienDangKy(PTRDK &First,DangKy svdk);//same with insertSVDK
int deleteFirstSinhVien(PTRSV &First);
int deleteAfterSinhVien(PTRSV p);
int deleteSinhVien(PTRSV &First,char MASV[16]);
bool findSinhVien(PTRSV &First,char MASV[16]); // Same with isSinhVien()
bool editSinhVien(PTRSV &sv);
PTRSV GetLop(DS_LOPSV &dslop, char malop[16]);//take it from Minh and it look same with searchLopSV of Dang
void InDSLSV(DS_LOPSV &dslop);//take it from Minh 
SinhVien getSinhVien(DS_LOPSV dslop, char MASV[16]);//take it from Minh
bool checkSV(DS_LOPSV &dslop, SinhVien sv);//take it from Minh
bool CheckLopSV(DS_LOPSV dslop, LopSV lop);//take it from Minh 
void NhapSV(DS_LOPSV &dslop);//take it from Minh
void NhapLopSV(DS_LOPSV &dslop);//take it from Minh
bool CheckDK(PTRDK dssvdk, const char* masv);//take it from Minh
PTRDK taonodeSVDK(const char* masv);//take it from Minh
void dangkyLTC(PTRLTC &FirstLTC, DS_LOPSV dslop);//take it from Minh



LopSV* searchLopSV(DS_LOPSV &dsLop,const char* MALOP);
int compareSV(const SinhVien& a, const SinhVien& b);
int listToArray(PTRSV First, SinhVien arr[]);
void sortSinhVien(SinhVien arr[], int n);
void printDSSV_sorted(LopSV *lop);
LopTinChi NhapLTC();// Make it look like nhapLTC of Minh
int getNextMaLopTinChi(PTRLTC First);//checked
string inputOrKeep(const string &oldValue, const string &label);
int inputIntOrKeep(int oldValue, const string &label);
PTRLTC findLTCByParams(PTRLTC FirstLTC);
void saveLopSV_Binary(DS_LOPSV &ds, const char *fileLop, const char *fileSV);
void loadLopSV_Binary(DS_LOPSV &ds, const char *fileLop, const char *fileSV);
void saveLopTinChi_Binary(PTRLTC &First,const char *fileloptinchi,const char *fileSVDK);
void loadLopTinChi_Binary(PTRLTC &First, const char *fileLop, const char *fileSVDK);

// take it from Minh
float Tinhdiemtb(SinhVien sv, PTRLTC dsltc, treeMH dsmh); 
void IndiemtbLop(PTRLTC &dsltc, DS_LOPSV &dslop, treeMH &dsmh);
void IndiemtbSinhvien(const PTRLTC &dsltc, const DS_LOPSV &dslop, const treeMH &dsmh);
void duyettreeMH(treeMH t, char dsMAMH[][11], int &soMH);
void InbangdiemtongketLop(PTRLTC dsltc, DS_LOPSV dslop, treeMH dsmh);
void InbangdiemtongketSinhvien(PTRLTC dsltc, DS_LOPSV dslop, treeMH dsmh);
void NhapDiem(nodeLTC* dsltc, DS_LOPSV &dslop);
void InbangDiemLTC(nodeLTC* dsltc, DS_LOPSV &dslop);
//tim lop 
int posLop(DS_LOPSV &ds,char MALOP[16]);
void xoaLopByPos(DS_LOPSV &ds,int pos);


#endif
