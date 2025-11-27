#ifndef MONHOC_H
#define MONHOC_H

#include <iostream>
#include "CTDL.h"
using namespace std;
int GetHeight(treeMH t);
int GetBalance(treeMH t);
treeMH RotateRight(treeMH y);
treeMH RotateLeft(treeMH x);
treeMH CheckandRotation(treeMH t);
treeMH Insert(treeMH t, MonHoc mh);
void init(stack &s);
bool empty(stack s);
void push(stack &s, ActionMH action);
void pop(stack &s); 
ActionMH top(stack s); 


// -------------------- HÀM FILE --------------------
void LuuMonHoc(treeMH t, string filename);
treeMH DocMonHoc(string filename);

// -------------------- HÀM HỖ TRỢ --------------------
bool checkMH(treeMH t, MonHoc mh);
void NhapMonHoc(treeMH &t);
treeMH UndoThemMH (treeMH &t, char MAMH[]);
treeMH XoaMH (treeMH &t, char MAMH[], stack &undostackMH);
void SuaMH(treeMH &t, MonHoc mh);
void UndoSuaMH (treeMH &t, MonHoc mh);
void UndoMH (treeMH &t, stack &undostackMH);
void InDSMH(treeMH t);
bool timMonHoc(treeMH t, char mamh[]);

#endif
