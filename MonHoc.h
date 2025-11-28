#ifndef MONHOC_H
#define MONHOC_H

#include <iostream>
using namespace std;

// -------------------- CẤU TRÚC --------------------
struct SinhVien //node
{
    char MASV[16];
    char HO[51];
    char TEN[11];
    char PHAI[4];
    char SODT[16];
    char Email[50];
};

struct nodeSV
{
    SinhVien sv;
    nodeSV *next;
};

typedef nodeSV* PTRSV;

struct MonHoc
{
    char MAMH[11];
    char TENMH[51];
    int STCLT;
    int STCTH;
};

struct nodeMH // cây AVL
{
    MonHoc mh;
    nodeMH *left;
    nodeMH *right;
    int height;
};

typedef nodeMH* treeMH;

struct ActionMH {
    int type = 0; //1 = them, 2 = xoa, 3 = sua mh
    MonHoc mh;
}

struct node {
    ActionMH data;
    node* next;
};

typedef node* PTRNode;

struct stack {
    node* top = nullptr; // đỉnh stack
};

// -------------------- HÀM HỖ TRỢ STACK --------------
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
void LuuMonHoc(treeMH t, string filename);
treeMH DocMonHoc(string filename);

// -------------------- HÀM HỖ TRỢ --------------------
PTRLTC FilterLTC(PTRLTC First, char nienkhoa[], int hocky);
PTRSV findSinhVien(PTRSV First, char MASV[]);
bool checkMH(treeMH t, MonHoc mh);
void NhapMonHoc(treeMH &t, stack &undostackMH);
treeMH UndoThemMH (treeMH &t, char MAMH[]);
treeMH XoaMH(treeMH &t, char MAMH[], stack &undostackMH);
void UndoSuaMH (treeMH &t, MonHoc mh);
void SuaMH(treeMH &t, MonHoc mh, stack &undostackMH);
void UndoMH (treeMH &t, stack &undostackMH);
void InDSMH(treeMH t);
treeMH timMonHoc(treeMH t, char mamh[]);
void InLTC (PTRLTC loptinchi, char nienkhoa[], int hocky, treeMH t);
void SVDangKy(PTRDK &dssvdk, PTRSV sv);
PTRLTC checkmamh(PTRLTC loptinchi, char nienkhoa[], int hocky);
void DangKyLTC(PTRLTC loptinchi, LopTinChi lop, treeMH t, PTRSV dssv);

#endif
