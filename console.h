#ifndef CONSOLE_H
#define CONSOLE_H

#include <termios.h>
#include <unistd.h>
#include <cstdio>

// ======== MÔ PHỎNG CONIO.H CHO LINUX ========

void gotoxy(int x, int y);
void clrscr();
int getch();
void SetBGColor(int color);
void ResetColor();
void SetBold(bool enable);
void drawLine(int x, int y, int len);
void SetColor(int color);
// ============================================

#endif
