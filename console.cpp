#include "console.h"
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <string>
#include <iostream>

using namespace std;
// =======================
//    GOTOXY
// =======================
void gotoxy(int x, int y) {
    printf("\033[%d;%dH", y + 1, x + 1);
}

// =======================
//    CLEAR SCREEN
// =======================
void clrscr() {
    printf("\033[2J\033[H");
}

// =======================
//    SET TEXT COLOR
// color = 0-15 (style ANSI hệ 256 màu nhẹ)
// =======================
void SetColor(int color) {
    printf("\033[38;5;%dm", color); // text color
}

// =======================
//    SET BACKGROUND COLOR
// color = 0-15
// =======================
void SetBGColor(int color) {
    printf("\033[48;5;%dm", color); // background color
}

// =======================
//    RESET COLOR (về mặc định)
// =======================
void ResetColor() {
    printf("\033[0m");
}

// =======================
//   BOLD (đậm chữ)
// =======================
void SetBold(bool enable) {
    if (enable) printf("\033[1m");
    else printf("\033[22m");
}

// =======================
//   GETCH() — không cần Enter
// =======================
int getch() {
    struct termios oldt, newt;
    int ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}

// =======================
//   DRAW LINE
// =======================
void drawLine(int x, int y, int len){
    gotoxy(x, y);
    for(int i = 0; i < len; i++) cout << "-";
}
inline bool useANSI() {
    return true;
}

inline void ClearLine(int y, int width = 120) {
    if (useANSI()) {
        printf("\033[%d;1H", y + 1); // về đầu dòng y
        printf("\033[2K");           // clear line
    } else {
        gotoxy(0, y);
        cout << string(width, ' ');
    }
}

void DrawBox(int x, int y, int w, int h, int borderColor , int bgColor) {
    if (w < 2 || h < 2) return;

    SetColor(borderColor);
    SetBGColor(bgColor);

    // corners
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