#ifndef MYLIB_H
#define MYLIB_H

#include <windows.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

// ========== Constants ==========
#define Enter 13
#define ESC   27
#define PASSWORD "abcdef"

// ========== Utility ==========
inline bool isVSCodeTerminal() {
    // VS Code sets the TERM_PROGRAM environment variable
    char* term = getenv("TERM_PROGRAM");
    return term && strstr(term, "vscode");
}

// ========== Cursor Control ==========
inline void gotoxy(short x, short y) {
    if (isVSCodeTerminal()) {
        // ANSI cursor move (works in VS Code)
        printf("\x1b[%d;%dH", y + 1, x + 1);
    } else {
        // Windows API (for Dev-C++)
        HANDLE hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
        COORD pos = { x, y };
        SetConsoleCursorPosition(hConsoleOutput, pos);
    }
}

// ========== Clear Screen ==========
inline void clrscr() {
    if (isVSCodeTerminal()) {
        // ANSI clear screen
        printf("\x1b[2J\x1b[H");
        fflush(stdout);
    } else {
        // Windows API full buffer clear
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
}

// ========== Color Control ==========
inline void SetColor(WORD color) {
    if (isVSCodeTerminal()) {
        // ANSI foreground color (0–7 base colors)
        printf("\x1b[3%dm", color % 8);
    } else {
        // Windows API
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_SCREEN_BUFFER_INFO info;
        GetConsoleScreenBufferInfo(hConsole, &info);
        WORD attrs = info.wAttributes;
        color &= 0x000F;
        attrs &= 0xFFF0;
        attrs |= color;
        SetConsoleTextAttribute(hConsole, attrs);
    }
}

inline void SetBGColor(WORD color) {
    if (isVSCodeTerminal()) {
        // ANSI background color (0–7)
        printf("\x1b[4%dm", color % 8);
    } else {
        // Windows API
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_SCREEN_BUFFER_INFO info;
        GetConsoleScreenBufferInfo(hConsole, &info);
        WORD attrs = info.wAttributes;
        color &= 0x000F;
        color <<= 4;
        attrs &= 0xFF0F;
        attrs |= color;
        SetConsoleTextAttribute(hConsole, attrs);
    }
}

inline void ResetColor() {
    if (isVSCodeTerminal())
        printf("\x1b[0m");
    else
        SetColor(7);
}

void drawLine(int x, int y, int len) {
    gotoxy(x, y);
    for (int i = 0; i < len; i++) cout << "-";
}
inline void SetBold(bool enable = true) {
    if (isVSCodeTerminal()) {
        printf(enable ? "\x1b[1m" : "\x1b[22m");
    } else {
        // old cmd.exe fallback (no real bold)
    }
}


#endif
