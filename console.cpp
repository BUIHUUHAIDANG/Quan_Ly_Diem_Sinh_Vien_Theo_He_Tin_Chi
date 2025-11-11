#include "console.h"

// Di chuyển con trỏ tới vị trí (x, y)
void gotoxy(int x, int y) {
    printf("\033[%d;%dH", y, x);
}

// Xóa toàn bộ màn hình và đưa con trỏ về góc trên trái
void clrscr() {
    printf("\033[2J\033[1;1H");
}

// Đổi màu chữ (theo ANSI color code)
void textcolor(int color) {
    printf("\033[1;%dm", 30 + color);
}

// Đọc 1 ký tự mà không cần nhấn Enter
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
