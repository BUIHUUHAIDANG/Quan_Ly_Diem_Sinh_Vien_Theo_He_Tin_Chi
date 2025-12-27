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
void InTrangLTC(PTRLTC loptinchi, char nienkhoa[], int hocky, treeMH t, int page, int pageSize);
void SVDangKy(PTRDK &dssvdk, PTRSV sv);
PTRLTC checkmamh(PTRLTC loptinchi, char nienkhoa[], int hocky);
PTRLTC checkmaltc(PTRLTC loptinchi, char nienkhoa[], int hocky);
void DangKyLTC(PTRLTC loptinchi, LopTinChi lop, treeMH t, DS_LOPSV dslop);
// -------------------- HÀM CLEAR ---------------------
void ClearTree(treeMH &t);
void ClearStackMH(stack &st);

#endif