#include "console.h"
#include <stdio.h>
#include <termios.h>
#include <unistd.h>

// =======================
//    GOTOXY
// =======================
void gotoxy(int x, int y) {
    printf("\033[%d;%dH", y, x);
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
    for(int i=0;i<len;i++) printf("─");
}
