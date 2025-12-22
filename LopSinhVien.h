#ifndef LOPSV_H
#define LOPSV_H

#include <iostream>
#include "CTDL.h"
using namespace std;

//stack Hieu Chinh LTC
stackNode* newNode(ActionLTC data);
bool isEmpty(stackNode* &root);
void push(stackNode* &root, ActionLTC data);
void pop(stackNode* &root);
ActionLTC top(stackNode* &root);
void undoSuaLTC(PTRLTC &First, LopTinChi ltc);
void undoLTC(PTRLTC &First, stackNode* &root);
void initializeStackNode(stackNode* &root);
bool deleteFirstStackLTC(stackNode* &root);

//stack Hieu Chinh Sinh Vien
stackNodeSV* newNode(ActionSV data);
bool isEmpty(stackNodeSV* &root);
void push(stackNodeSV* &root, ActionSV data);
void pop(stackNodeSV* &root);
ActionSV top(stackNodeSV* &root);
void undoSuaSV(PTRSV &First,SinhVien sv);
void undoSV(PTRSV &First, stackNodeSV* &root);
bool deleteFirstStackSV(stackNodeSV* &root);
// void undoSuaLTC(PTRLTC &First, LopTinChi ltc);
// void undoLTC(PTRLTC &First, stackNode* &root);
// void initializeStackNode(stackNode* &root);
// bool deleteFirstStackLTC(stackNode* &root);

//Lop Tin Chi
PTRLTC createNodeLopTinChi(LopTinChi data);
void insertLopTinChi(PTRLTC &First, LopTinChi data);
bool isEmpty(PTRLTC &First);
int deleteFirst(PTRLTC &First);
int deleteAfter(PTRLTC p);
int deleteLopTinChi(PTRLTC &First, int MALTC);

PTRLTC searchLopTinChi(PTRLTC &First, int x);
PTRLTC searchLTC(PTRLTC &First, char nienkhoa[10], int hocky, int nhom, char MAMH[11]);

bool editLopTinChi(PTRLTC &First, int x);
bool checkLTC(PTRLTC FirstLTC, LopTinChi ltc);

//Danh Sach Sinh Vien Dang Ky
void showDanhSachSinhVienDangKy(PTRDK &l);
void insertSinhVienDangKy(PTRDK &First, DangKy svdk);
int deleteFirstDK(PTRDK &First);
void ClearlistDSSVDK(PTRDK &First);
bool CheckDK(PTRDK dssvdk, const char* masv);
PTRDK taonodeSVDK(const char* masv);

//In LTC va DSSVDK
void InDSSVDK(PTRLTC &FirstLTC, int maloptc, DS_LOPSV &dslop);
void InDSLTC(PTRLTC &l);

//Danh Sach Sinh Vien
bool isEmptySinhVien(PTRSV &First);
void insertSinhVien(PTRSV &First, SinhVien x);
int deleteFirstSinhVien(PTRSV &First);
int deleteAfterSinhVien(PTRSV p);
int deleteSinhVien(PTRSV &First, char MASV[16]);
bool findSinhVien(PTRSV &First, char MASV[16]);
bool editSinhVien(PTRSV &sv);

//Lop Sinh Vien
PTRSV GetLop(DS_LOPSV &dslop, char malop[16]);
void InDSLSV(DS_LOPSV &dslop);
SinhVien getSinhVien(DS_LOPSV dslop, char MASV[16]);
PTRSV getSinhVienv2(PTRSV &First, char masv[16]);
bool checkSV(DS_LOPSV &dslop, SinhVien sv);
bool CheckLopSV(DS_LOPSV dslop, LopSV lop);

void NhapSV(DS_LOPSV &dslop);
void NhapLopSV(DS_LOPSV &dslop);

//Dang Ki Lop Tin Chi
void dangkyLTC(PTRLTC &FirstLTC, DS_LOPSV dslop);

//Sap Xep theo Alphabet
LopSV* searchLopSV(DS_LOPSV &dsLop, const char* MALOP);
int compareSV(const SinhVien& a, const SinhVien& b);
int listToArray(PTRSV First, SinhVien arr[]);
void sortSinhVien(SinhVien arr[], int n);
void printDSSV_sorted(LopSV *lop);

//Nhap Lop Tin Chi + Sua lop Tin Chi
bool isValidSoSV(int min, int max);
void formatName(char s[]);
bool checkformatdeadline (string s);
bool validdealine (time_t deadline);
LopTinChi NhapLTC();
int getNextMaLopTinChi(PTRLTC First);

string inputOrKeep(const string &oldValue, const string &label);
int inputIntOrKeep(int oldValue, const string &label);

PTRLTC findLTCByParams(PTRLTC FirstLTC);

// Save/Load cua Lop Tin Chi(Danh sach sinh vien dang ky) va Lop Sinh Vien(danh sach sinh vien cua lop do)
void saveLopSV_Binary(DS_LOPSV &ds, const char *fileLop, const char *fileSV);
void loadLopSV_Binary(DS_LOPSV &ds, const char *fileLop, const char *fileSV);

void saveLopTinChi_Binary(PTRLTC &First, const char *fileloptinchi, const char *fileSVDK);
void loadLopTinChi_Binary(PTRLTC &First, const char *fileLop, const char *fileSVDK);

//Tinh/In bang diem cua sinh vien 
float Tinhdiemtb(SinhVien sv, PTRLTC dsltc, treeMH dsmh);
void IndiemtbLop(PTRLTC &dsltc, DS_LOPSV &dslop, treeMH &dsmh);
void IndiemtbSinhvien(const PTRLTC &dsltc, const DS_LOPSV &dslop, const treeMH &dsmh);

void duyettreeMH(treeMH t, char dsMAMH[][11], int &soMH);
void InbangdiemtongketLop(PTRLTC dsltc, DS_LOPSV dslop, treeMH dsmh);
void InbangdiemtongketSinhvien(PTRLTC dsltc, DS_LOPSV dslop, treeMH dsmh);

void NhapDiem(nodeLTC* dsltc, DS_LOPSV &dslop);
void InbangDiemLTC(nodeLTC* dsltc, DS_LOPSV &dslop);

//Tim/Xoa/CapNhap Sinh Vien 
int posLop(DS_LOPSV &ds, char MALOP[16]);
void xoaLopByPos(DS_LOPSV &ds, int pos);

//don dep sau khi thoat chuong trinh 
void ClearlistSV(PTRSV &First);
void ClearLTC(PTRLTC &First);
void ClearDS_Lop(DS_LOPSV &ds);
void ClearStackLTC(stackNode* &dsnode);
void ClearStackSV(stackNodeSV* &dsnode);
//recode function insert
void insertSinhVienV2(PTRSV &First,SinhVien sv);
void insertSinhVienDKV2(PTRDK &First,DangKy svdk);
//get 3number at the end of MaSV
int getNumOfSinhVien(char MaSV[]);

//change time to int
time_t stringToTime(string s);
void AutoCancelExpiredClasses(PTRLTC &l);
#endif
