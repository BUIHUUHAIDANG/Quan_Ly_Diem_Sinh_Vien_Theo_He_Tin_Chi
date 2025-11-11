#ifndef CONSOLE_H
#define CONSOLE_H

#include <termios.h>
#include <unistd.h>
#include <cstdio>

// ======== MÔ PHỎNG CONIO.H CHO LINUX ========

void gotoxy(int x, int y);
void clrscr();
void textcolor(int color);
int getch();

// ============================================

#endif
