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
void initializeStackNode(stackNode* root);
void initializeLTC(PTRLTC &First);
void initializeSV(PTRSV & FirstSV);
PTRLTC createNodeLopTinChi(LopTinChi data);
void insertLopTinChi(PTRLTC &First, LopTinChi data);
bool isEmpty(PTRLTC &First);
int deleteFirst(PTRLTC &First);
int deleteFirstDK(PTRDK &First);
int deleteAfter(PTRLTC p);
int deleteLopTinChi(PTRLTC &First,int MALTC);
void ClearlistDSSVDK(PTRDK &First);
void ClearLTC(PTRLTC &First);
void ClearlistSV(PTRSV &First);
void ClearDS_Lop(DS_LOPSV &ds);
PTRLTC searchLopTinChi(PTRLTC &First,int x);
PTRLTC searchLTC(PTRLTC &First,char nienkhoa[10],int hocky,int nhom,char MAMH[11]);
bool editLopTinChi(PTRLTC &First,int x);
void showDanhSachSinhVienDangKy(PTRDK &l);
void showLopTinChi(PTRLTC &l);
bool showDSSVOfLopTinChi(PTRLTC &First,char nienkhoa[10],int hocky,int nhom,char MAMH[11]);

bool isEmptySinhVien(PTRSV &First);
void insertSinhVien(PTRSV &First,SinhVien x);
void insertSinhVienDangKy(PTRDK &First,DangKy svdk);
int deleteFirstSinhVien(PTRSV &First);
int deleteAfterSinhVien(PTRSV p);
int deleteSinhVien(PTRSV &First,char MASV[16]);
bool findSinhVien(PTRSV &First,char MASV[16]);
bool editSinhVien(PTRSV &sv);

LopSV* searchLopSV(DS_LOPSV &dsLop,const char* MALOP);
int compareSV(const SinhVien& a, const SinhVien& b);
int listToArray(PTRSV First, SinhVien arr[]);
void sortSinhVien(SinhVien arr[], int n);
void printDSSV_sorted(LopSV *lop);
LopTinChi NhapLTC();
void saveLopTinChi(PTRLTC &First, const string &fileLoptinchi, const string &fileSVDK);
void loadLopTinChi(PTRLTC &First, const string &fileLop, const string &fileSVDK);
int getNextMaLopTinChi(PTRLTC First);
string inputOrKeep(const string &oldValue, const string &label);
int inputIntOrKeep(int oldValue, const string &label);
PTRLTC findLTCByParams(PTRLTC FirstLTC);
void saveLopSV(DS_LOPSV &ds, const string &fileLop, const string &fileSV);
void loadLopSV(DS_LOPSV &ds, const string &fileLop, const string &fileSV);
void saveLopSV_Binary(DS_LOPSV &ds, const string &fileLop, const string &fileSV);
void loadLopSV_Binary(DS_LOPSV &ds, const string &fileLop, const string &fileSV);
void saveLopTinChi_Binary(PTRLTC &First,const string &fileloptinchi,const string &fileSVDK);
void loadLopTinChi_Binary(PTRLTC &First, const string &fileLop, const string &fileSVDK);



#endif
