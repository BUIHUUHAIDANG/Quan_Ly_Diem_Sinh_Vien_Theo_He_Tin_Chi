#ifndef MONHOC_H
#define MONHOC_H

#include <iostream>
#include "CTDL.h"
using namespace std;

// -------------------- CẤU TRÚC --------------------


// -------------------- HÀM AVL --------------------
int GetHeight(treeMH t);
int GetBalance(treeMH t);
treeMH RotateRight(treeMH y);
treeMH RotateLeft(treeMH x);
treeMH CheckandRotation(treeMH t);
treeMH Insert(treeMH t, MonHoc mh);
treeMH XoaMH(treeMH &t, char MAMH[]);

// -------------------- HÀM FILE --------------------
                // Save load theo text
//void LuuMonHoc(treeMH t, string filename);
//treeMH DocMonHoc(string filename);
                // Save load theo binary
void GhiNode(FILE* f, treeMH t);
void LuuMonHoc(treeMH &t, const char* tenfile);
void DocMonHoc(const char* tenfile, treeMH &t);

// -------------------- HÀM HỖ TRỢ --------------------
bool checkMH(treeMH t, MonHoc mh);
void NhapMonHoc(treeMH &t);
void SuaMH(treeMH &t, MonHoc mh);
void InDSMH(treeMH t);
bool timMonHoc(treeMH t, char mamh[]);

#endif
