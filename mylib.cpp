#include "mylib.h"

#include <conio.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>

using namespace std;

// ========== Environment Detection ==========
bool useANSI() {
    char* term = getenv("TERM");
    char* vscode = getenv("TERM_PROGRAM");
    char* conemu = getenv("ConEmuPID");
    char* wt = getenv("WT_SESSION");
    return (term && strstr(term, "xterm")) ||
           (vscode && strstr(vscode, "vscode")) ||
           conemu || wt;
}

// ========== Cursor ==========
void gotoxy(short x, short y) {
    if (useANSI()) {
        printf("\x1b[%d;%dH", y + 1, x + 1);
        fflush(stdout);
    } else {
        HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
        COORD pos = { x, y };
        SetConsoleCursorPosition(h, pos);
    }
}

// ========== Clear Screen ==========
void clrscr() {
    if (useANSI()) {
        printf("\x1b[2J\x1b[H");
        fflush(stdout);
        return;
    }

    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO info;
    DWORD cells, written;
    COORD home = {0, 0};

    if (!GetConsoleScreenBufferInfo(h, &info)) return;
    cells = info.dwSize.X * info.dwSize.Y;

    FillConsoleOutputCharacter(h, ' ', cells, home, &written);
    FillConsoleOutputAttribute(h, info.wAttributes, cells, home, &written);
    SetConsoleCursorPosition(h, home);
}

// ========== Color ==========
void SetColor(WORD color) {
    if (useANSI()) {
        printf("\x1b[%dm", 30 + (color % 8));
        fflush(stdout);
    } else {
        HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_SCREEN_BUFFER_INFO info;
        GetConsoleScreenBufferInfo(h, &info);
        WORD attrs = (info.wAttributes & 0xFFF0) | (color & 0x000F);
        SetConsoleTextAttribute(h, attrs);
    }
}

void SetBGColor(WORD color) {
    if (useANSI()) {
        printf("\x1b[%dm", 40 + (color % 8));
        fflush(stdout);
    } else {
        HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_SCREEN_BUFFER_INFO info;
        GetConsoleScreenBufferInfo(h, &info);
        WORD attrs = (info.wAttributes & 0xFF0F) | ((color & 0x000F) << 4);
        SetConsoleTextAttribute(h, attrs);
    }
}

void ResetColor() {
    if (useANSI()) {
        printf("\x1b[0m");
        fflush(stdout);
    } else {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    }
}

void SetBold(bool enable) {
    if (useANSI()) {
        printf(enable ? "\x1b[1m" : "\x1b[22m");
        fflush(stdout);
    }
}

// ========== Drawing ==========
void drawLine(int x, int y, int len) {
    gotoxy(x, y);
    for (int i = 0; i < len; i++) cout << "-";
}

void ClearLine(int y, int width) {
    gotoxy(0, y);
    if (useANSI()) {
        printf("\x1b[2K");
        printf("\x1b[%d;1H", y + 1);
    } else {
        cout << string(width, ' ');
        gotoxy(0, y);
    }
}

void DrawBox(int x, int y, int w, int h, WORD borderColor, WORD bgColor) {
    if (w < 2 || h < 2) return;

    SetColor(borderColor);
    SetBGColor(bgColor);

    gotoxy(x, y);                 cout << "o";
    gotoxy(x + w - 1, y);         cout << "o";
    gotoxy(x, y + h - 1);         cout << "o";
    gotoxy(x + w - 1, y + h - 1); cout << "o";

    for (int i = 1; i < w - 1; i++) {
        gotoxy(x + i, y);         cout << "-";
        gotoxy(x + i, y + h - 1); cout << "-";
    }
    for (int i = 1; i < h - 1; i++) {
        gotoxy(x, y + i);         cout << "|";
        gotoxy(x + w - 1, y + i); cout << "|";
    }
    for (int i = 1; i < h - 1; i++) {
        gotoxy(x + 1, y + i);
        cout << string(w - 2, ' ');
    }

    ResetColor();
}

void ClearBox(int x, int y, int w, int h) {
    for (int i = 0; i < h; i++) {
        gotoxy(x, y + i);
        cout << string(w, ' ');
    }
}
