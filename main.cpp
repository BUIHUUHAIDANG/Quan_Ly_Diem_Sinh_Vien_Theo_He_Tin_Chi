#include <iostream>
#include <termios.h>
#include <unistd.h>
#include <cstdio>
#include <cstring>
using namespace std;

// =================== MÔ PHỎNG CONIO.H ===================
void gotoxy(int x, int y) {
    printf("\033[%d;%dH", y, x);
}

void clrscr() {
    printf("\033[2J\033[1;1H");
}

void textcolor(int color) {
    printf("\033[1;%dm", 30 + color); // 0=đen, 1=đỏ, 2=lục, 3=vàng, 4=xanh dương...
}

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
// =======================================================

void drawMenu(const char *title, const char *role, const char *options[], int n, int highlight) {
    clrscr();
    textcolor(7); // trắng
    gotoxy(20, 2);
    cout << title;
    gotoxy(5, 4);
    cout << "Vai tro: " << role;

    for (int i = 0; i < n; i++) {
        gotoxy(8, 6 + i * 2);
        if (i == highlight) {
            textcolor(0);
            printf("\033[47m"); // nền trắng
            cout << "> " << options[i] << " <";
            printf("\033[0m"); // reset
            textcolor(7);
        } else {
            cout << "  " << options[i];
        }
    }
    gotoxy(5, 6 + n * 2);
    cout << "(Dung phim W/S de di chuyen, Enter de chon)";
}

int menu(const char *title, const char *role, const char *options[], int n) {
    int highlight = 0;
    while (true) {
        drawMenu(title, role, options, n, highlight);
        int ch = getch();

        if (ch == 'w' || ch == 'W')
            highlight = (highlight - 1 + n) % n;
        else if (ch == 's' || ch == 'S')
            highlight = (highlight + 1) % n;
        else if (ch == 10) // Enter
            return highlight;
    }
}

int main() {
    const char *roles[] = {"Sinh vien", "Giang vien", "Admin", "Thoat"};
    const char *features[] = {
        "Xem danh sach mon hoc",
        "In danh sach sinh vien",
        "In bang diem trung binh",
        "In bang diem tong ket",
        "In danh sach sinh vien da dang ki",
        "In bang diem cua lop tin chi",
        "← Quay lai"
    };

    int n_roles = 4, n_features = 7;

    while (1) {
        int r = menu("CHON VAI TRO DANG NHAP", "", roles, n_roles);
        if (r == 3) break; // Thoát

        const char *role = roles[r];
        while (1) {
            int f = menu("📚 QUAN LY HE TIN CHI 📚", role, features, n_features);
            if (f == n_features - 1) break;

            clrscr();
            gotoxy(10, 10);
            cout << "Ban da chon: " << features[f];
            gotoxy(10, 12);
            cout << "(Nhan phim bat ky de quay lai...)";
            getch();
        }
    }

    clrscr();
    gotoxy(10, 10);
    cout << "Tam biet!\n";
    return 0;
}
