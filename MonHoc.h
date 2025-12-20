#ifndef MONHOC_H
#define MONHOC_H

#include <iostream>
#include "CTDL.h"
using namespace std;
void init(stack &s);
bool empty(stack s);
void push(stack &s, ActionMH action);
void pop(stack &s);
ActionMH top(stack s);

// -------------------- HÀM AVL --------------------
int GetHeight(treeMH t);
int GetBalance(treeMH t);
treeMH RotateRight(treeMH y);
treeMH RotateLeft(treeMH x);
treeMH CheckandRotation(treeMH t);
treeMH Insert(treeMH t, MonHoc mh);

// -------------------- HÀM FILE --------------------
void WriteNode(FILE* f, treeMH node);
void LuuMonHoc(treeMH t, const string &filename);
treeMH ReadNode(FILE* f);
treeMH DocMonHoc(const string &filename);

// -------------------- HÀM HỖ TRỢ --------------------
PTRLTC FilterLTC(PTRLTC First, char nienkhoa[], int hocky);
PTRSV findSinhVien(PTRSV First, char MASV[], PTRSV dssv);
bool checkMH(treeMH t, MonHoc mh);
void NhapMonHoc(treeMH &t, stack &undostackMH);
treeMH UndoThemMH (treeMH &t, char MAMH[]);
treeMH XoaMH(treeMH &t, char MAMH[], stack &undostackMH);
void UndoSuaMH (treeMH &t, MonHoc mh);
void SuaMH(treeMH &t, MonHoc mh, stack &undostackMH);
void UndoMH (treeMH &t, stack &undostackMH);
void LuuMH_Inorder(treeMH t, MonHoc ds[], int &n);
void In1TrangMH(MonHoc ds[], int n, int page, int pageSize);
void InDSMH(treeMH t);
treeMH timMonHoc(treeMH t, char mamh[]);
void InLTC (PTRLTC loptinchi, char nienkhoa[], int hocky, treeMH t);
void SVDangKy(PTRDK &dssvdk, PTRSV sv);
PTRLTC checkmamh(PTRLTC loptinchi, char nienkhoa[], int hocky);
void DangKyLTC(PTRLTC loptinchi, LopTinChi lop, treeMH t, PTRSV dssv);

#endif