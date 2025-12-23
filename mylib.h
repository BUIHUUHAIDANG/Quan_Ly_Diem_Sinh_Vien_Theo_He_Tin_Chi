#ifndef MYLIB_H
#define MYLIB_H

// ==== Fix WinAPI x C++ ====
#define WIN32_LEAN_AND_MEAN
#define _HAS_STD_BYTE 0

#include <windows.h>

// ========== Constants ==========
#define Enter 13
#define ESC   27
#define PASSWORD "abcdef"

// ========== Environment ==========
bool useANSI();

// ========== Cursor / Screen ==========
void gotoxy(short x, short y);
void clrscr();

// ========== Color ==========
void SetColor(WORD color);
void SetBGColor(WORD color);
void ResetColor();
void SetBold(bool enable = true);

// ========== Drawing ==========
void drawLine(int x, int y, int len);
void ClearLine(int y, int width = 120);
void DrawBox(int x, int y, int w, int h, WORD borderColor = 7, WORD bgColor = 0);
void ClearBox(int x, int y, int w, int h);

#endif
