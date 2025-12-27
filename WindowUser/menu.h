#ifndef MENU_H
#define MENU_H

#include <iostream>
#include "CTDL.h"
using namespace std;
void drawStaticMenu(const char *title, const char *role, int n);
void drawOptions(const char *options[], int n, int highlight);
int menu(const char *title, const char *role, const char *options[], int n);
void drawBangDiem(PTRDK arr[], int count, int highlight, DS_LOPSV &dslop, int index);
void BangDiem_Interact(PTRDK arr[], int count, DS_LOPSV &dslop);
void BangDiemLTC(PTRDK arr[], int count, DS_LOPSV &dslop);
void BangDiemTB(PTRSV arr[], int count, PTRLTC &dsltc,DS_LOPSV &dslop,treeMH &dsmh, LopSV* lop);
void BangDiemTK(PTRSV arr[], int count, PTRLTC &dsltc,DS_LOPSV &dslop,treeMH &dsmh, LopSV* lop);
void drawMonHoc (treeMH t, MonHoc mh, int count, int highlight, int index);
void InLTC_UI(PTRLTC loptinchi, char nienkhoa[], int hocky, treeMH t);
#endif