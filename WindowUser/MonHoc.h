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
// format
void Deletespaceandtoupper (char s[]);
void UpperFirstCharName(char s[]);
// -------------------- HÀM HỖ TRỢ --------------------
bool Checkkhoangtrang(char s[]);
void NhapMonHoc(treeMH &t, stack &undostackMH);
treeMH UndoThemMH (treeMH t, char MAMH[]);
treeMH XoaMH(treeMH t, char MAMH[], MonHoc &mhDeleted);
void UndoSuaMH (treeMH &t, MonHoc mh);
void SuaMH(treeMH &t, MonHoc mh, stack &undostackMH);
void UndoMH (treeMH &t, stack &undostackMH);
void LuuMH_Inorder(treeMH t, MonHoc ds[], int &n);
PTRLTC InTrangLTC_UI_Bang(PTRLTC start, char nienkhoa[], int hocky, treeMH t);
PTRLTC TimTrangTruoc(PTRLTC first, PTRLTC curr, char nienkhoa[], int hocky, treeMH t);
void InLTC_UI(PTRLTC FirstLTC, char nienkhoa[], int hocky, treeMH t);
void InDSMH(treeMH t);
treeMH timMonHoc(treeMH t, char mamh[]);
void SVDangKy(PTRDK &dssvdk, PTRSV sv);
bool SVdaDangKy(PTRDK dssvdk, char masv[16]);
PTRLTC checkmaltc(PTRLTC loptinchi, char nienkhoa[], int hocky);
bool formatNK(char nk[]);
void DangKyLTC(PTRLTC loptinchi, LopTinChi lop, treeMH t, DS_LOPSV dslop);
// -------------------- HÀM CLEAR ---------------------
void ClearTree(treeMH &t);
void ClearStackMH(stack &st);

#endif