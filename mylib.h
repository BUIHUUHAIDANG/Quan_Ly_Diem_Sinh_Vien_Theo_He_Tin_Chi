#ifndef MYLIB_H
#define MYLIB_H
#include <windows.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
using namespace std;

// ========== Constants ==========
#define Enter 13
#define ESC   27
#define PASSWORD "abcdef"

// ========== Environment Detection ==========
// Detect if ANSI escape codes are supported (Linux, WSL, Git Bash, VS Code ConPTY)
inline bool useANSI() {
    char* term = getenv("TERM");
    char* vscode = getenv("TERM_PROGRAM");
    char* conemu = getenv("ConEmuPID");
    char* wt = getenv("WT_SESSION");
    return (term && strstr(term, "xterm")) ||
           (vscode && strstr(vscode, "vscode")) ||
           conemu || wt;
}

// ========== Cursor Control ==========
inline void gotoxy(short x, short y) {
    if (useANSI()) {
        printf("\x1b[%d;%dH", y + 1, x + 1);
        fflush(stdout);
    } else {
        HANDLE hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
        COORD pos = { x, y };
        SetConsoleCursorPosition(hConsoleOutput, pos);
    }
}

// ========== Clear Screen ==========
// Always uses Windows API clear (more reliable in all Windows terminals)
inline void clrscr() {
    // If ANSI environment (Linux/WSL/Git Bash) â†’ use ANSI clear
    if (useANSI()) {
        printf("\x1b[2J\x1b[H");
        fflush(stdout);
        return;
    }

    // Otherwise use Windows native clear
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO info;
    DWORD cells, written;
    COORD home = {0, 0};
    if (!GetConsoleScreenBufferInfo(hConsole, &info)) return;
    cells = info.dwSize.X * info.dwSize.Y;
    FillConsoleOutputCharacter(hConsole, ' ', cells, home, &written);
    FillConsoleOutputAttribute(hConsole, info.wAttributes, cells, home, &written);
    SetConsoleCursorPosition(hConsole, home);
}

// ========== Color Control ==========
inline void SetColor(WORD color) {
    if (useANSI()) {
        printf("\x1b[%dm", 30 + (color % 8));
        fflush(stdout);
    } else {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_SCREEN_BUFFER_INFO info;
        GetConsoleScreenBufferInfo(hConsole, &info);
        WORD attrs = info.wAttributes;
        attrs &= 0xFFF0;
        attrs |= (color & 0x000F);
        SetConsoleTextAttribute(hConsole, attrs);
    }
}

inline void SetBGColor(WORD color) {
    if (useANSI()) {
        printf("\x1b[%dm", 40 + (color % 8));
        fflush(stdout);
    } else {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_SCREEN_BUFFER_INFO info;
        GetConsoleScreenBufferInfo(hConsole, &info);
        WORD attrs = info.wAttributes;
        attrs &= 0xFF0F;
        attrs |= ((color & 0x000F) << 4);
        SetConsoleTextAttribute(hConsole, attrs);
    }
}

inline void ResetColor() {
    if (useANSI()) {
        printf("\x1b[0m");
        fflush(stdout);
    } else {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    }
}

inline void SetBold(bool enable = true) {
    if (useANSI()) {
        printf(enable ? "\x1b[1m" : "\x1b[22m");
        fflush(stdout);
    }
}

// ========== Line Drawing ==========
inline void drawLine(int x, int y, int len) {
    gotoxy(x, y);
    for (int i = 0; i < len; i++) cout << "-";
}
inline void ClearLine(int y, int width = 120) {
    gotoxy(0, y); 
    if (useANSI()) {
       
        printf("\x1b[2K");  
        printf("\x1b[%d;1H", y + 1); 
    } else {
        cout << string(width, ' ');
        gotoxy(0, y);
    }
}

inline void DrawBox(int x, int y, int w, int h, WORD borderColor = 7, WORD bgColor = 0) { // cot x, dong y, be rong width, chieu cao height, mau bien, mau nen 
    if (w < 2 || h < 2) return;

    SetColor(borderColor);
    SetBGColor(bgColor);
    // corners
    gotoxy(x, y); cout << "o";
    gotoxy(x + w - 1, y); cout << "o";
    gotoxy(x, y + h - 1); cout << "o";
    gotoxy(x + w - 1, y + h - 1); cout << "o";

    for (int i = 1; i < w - 1; i++) {
        gotoxy(x + i, y); cout << "-";
        gotoxy(x + i, y + h - 1); cout << "-";
    }
    for (int i = 1; i < h - 1; i++) {
        gotoxy(x, y + i); cout << "|";
        gotoxy(x + w - 1, y + i); cout << "|";
    }
    for (int i = 1; i < h - 1; i++) {
        gotoxy(x + 1, y + i);
        cout << string(w - 2, ' ');
    }

    ResetColor();
}


inline void ClearBox(int x, int y, int w, int h) {
    for (int i = 0; i < h; i++) {
        gotoxy(x, y + i);
        cout << string(w, ' ');
    }
}


#endif