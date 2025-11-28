#ifndef LOPSV_H
#define LOPSV_H

#include <iostream>
#include "CTDL.h"
using namespace std;
//void initializeLTC(PTRLTC &First);
//void initializeSV(PTRSV & FirstSV);
//PTRLTC createNodeLopTinChi(LopTinChi data);
//void insertLopTinChi(PTRLTC &First, LopTinChi data);
bool isEmpty(PTRLTC &First);
int deleteFirst(PTRLTC &First);
//int deleteAfter(PTRLTC p);
//int deleteLopTinChi(PTRLTC &First,int MALTC);
//void Clearlist(PTRLTC &First);
//void ClearlistSV(PTRSV &First);
//void ClearDS_Lop(DS_LOPSV &ds);
//PTRLTC searchLopTinChi(PTRLTC &First,int x);
//PTRLTC searchLTC(PTRLTC &First,char nienkhoa[10],int hocky,int nhom,char MAMH[11]);
//bool editLopTinChi(PTRLTC &First,int x);
//void showDanhSachSinhVienDangKy(PTRLTC &l);
//void showLopTinChi(PTRLTC &l);
void InDSSV(DS_LOPSV &dslop, char MALOP[]);
void InDSSVDK(PTRLTC &FirstLTC, int maloptc, DS_LOPSV &dslop);
void InDSLTC(PTRLTC &FirstLTC); // In DSLTC
void InDSLSV(DS_LOPSV &dslop);  // In DSLOPSV

//bool showDSSVOfLopTinChi(PTRLTC &First,char nienkhoa[10],int hocky,int nhom,char MAMH[11]);

//bool isEmptySinhVien(PTRSV &First);
//void insertSinhVien(PTRSV &First,SinhVien x);
//int deleteFirstSinhVien(PTRSV &First);
//int deleteAfterSinhVien(PTRSV p);
//int deleteSinhVien(PTRSV &First,char MASV[16]);
//bool findSinhVien(PTRSV &First,char MASV[16]);
//SinhVien getSinhVien(PTRSV &FirstSV, char MASV[16]); 
//bool editSinhVien(PTRSV &sv);

//LopSV* searchLopSV(DS_LOPSV &dsLop,const char* MALOP);
//int compareSV(const SinhVien& a, const SinhVien& b);
//int listToArray(PTRSV First, SinhVien arr[]);
//void sortSinhVien(SinhVien arr[], int n);
//void printDSSV_sorted(LopSV *lop);
void NhapSV(DS_LOPSV &dslop); // Nhap SV
void NhapLTC(PTRLTC &FirstLTC); // Nhap LTC
void NhapLopSV(DS_LOPSV &dslop); // Nhap LopSV
//void saveLopTinChiToFileText(PTRLTC First, const string &filename);
//void loadLopTinChiFromFileText(PTRLTC &First, const string &filename);
int getNextMaLopTinChi(PTRLTC First);
//string inputOrKeep(const string &oldValue, const string &label);
//int inputIntOrKeep(int oldValue, const string &label);
//PTRLTC findLTCByParams(PTRLTC FirstLTC);
// void saveSinhVienToFile(PTRSV First, const string &filename);
// void loadSinhVienFromFile(PTRSV &First, const string &filename);
// LopSV* searchLopSV(DS_LOPSV &ds, const char* MALOP);
//void saveLopSV(DS_LOPSV &ds, const string &fileLop, const string &fileSV);
//void loadLopSV(DS_LOPSV &ds, const string &fileLop, const string &fileSV);

// ========================================================================================
// -- SINH VIEN --

PTRDK taonodeSVDK(const char* masv);
void insertSVDK(PTRDK &First, PTRDK node);
void InsertSV(PTRSV &FirstSV, SinhVien sv);
void dangkyLTC(PTRLTC &FirstLTC, DS_LOPSV dslop);

// -- HAM HO TRO --
void DeleteDSSV(PTRSV &FirstSV);
void DeleteDSLopSV(DS_LOPSV &dslop);
void DeleteDSLTC(PTRLTC &FirstLTC);

void InsertLast_LTC(PTRLTC &FirstLTC,LopTinChi &ltc);
void InsertLast_DK(PTRDK &dssvdk, DangKy dk);
void duyettreeMH(treeMH t, char dsMAMH[][11], int &soMH);

// -- SAVE LOAD --
int SaveFile_LopSV(const char* tenfile, DS_LOPSV &dslop);
int LoadFile_LopSV(const char* tenfile, DS_LOPSV &dslop);
int SaveFile_LTC(const char* tenfile, PTRLTC &FirstLTC);
int LoadFile_LTC(const char* tenfile, PTRLTC &FirstLTC);

// -- DIEM --
float Tinhdiemtb(SinhVien &sv, PTRLTC &dsltc, treeMH &dsmh);
void IndiemtbLop(PTRLTC &dsltc,DS_LOPSV &dslop, treeMH &dsmh);
void IndiemtbSinhvien( PTRLTC &dsltc,  DS_LOPSV &dslop,  treeMH &dsmh);
void NhapDiem(nodeLTC* dsltc, DS_LOPSV &dslop);
void InbangDiemLTC(nodeLTC* dsltc, DS_LOPSV &dslop);
void InbangdiemtongketLop( PTRLTC &dsltc,  DS_LOPSV &dslop,  treeMH &dsmh);
void InbangdiemtongketSinhvien( PTRLTC &dsltc,  DS_LOPSV &dslop, treeMH &dsmh);


#endif
