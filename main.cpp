#include <iostream>
#include <conio.h>      
#include <windows.h>    
#include <cstdio>
#include <cstring>
#include "mylib.h"    
#include "MonHoc.h"
#include "LopSinhVien.h"

using namespace std;
// === Draw Menu ===
void drawMenu(const char *title, const char *role, const char *options[], int n, int highlight) {
    clrscr();
    SetBGColor(0);  // black background
    SetColor(7);    // white text
    gotoxy(20, 2);
    SetBold(true);
    SetColor(4);
    cout << title;
    drawLine(5, 3, 53);
    ResetColor();
    SetBold(false);
    gotoxy(5, 4);
    cout << "Vai tro: ";
    SetBold(true);
    SetColor(10);
    cout << role;
    ResetColor();
    SetBold(false);
    for (int i = 0; i < n; i++) {
        gotoxy(8, 6 + i * 2);
        if (i == highlight) {
            SetBGColor(7); SetColor(0);
            cout << "> " << options[i] << " <";
            ResetColor();
        } else {
            cout << "  " << options[i];
        }
    }
    gotoxy(5, 6 + n * 2);
    cout << "(Dung phim ↑ ↓ hoac W/S de di chuyen, Enter de chon)";
}

// === Menu Logic ===
int menu(const char *title, const char *role, const char *options[], int n) {
    int highlight = 0;
    while (true) {
        drawMenu(title, role, options, n, highlight);
        int ch = _getch();

        // support both arrow keys and WASD
        if (ch == 224) {
            int arrow = _getch();
            if (arrow == 72) highlight = (highlight - 1 + n) % n; // up
            if (arrow == 80) highlight = (highlight + 1) % n;     // down
        } else if (ch == 'w' || ch == 'W') {
            highlight = (highlight - 1 + n) % n;
        } else if (ch == 's' || ch == 'S') {
            highlight = (highlight + 1) % n;
        } else if (ch == 13) { // Enter
            return highlight;
        }
    }
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    const char *roles[] = {"Sinh vien", "Giang vien", "Admin", "Thoat"};
    const char *features_sinhvien[] = {
        "Xem danh sach mon hoc",
        "In danh sach sinh vien",
        "In bang diem trung binh",
        "In bang diem tong ket",
        "In danh sach sinh vien da dang ki",
        "In bang diem cua lop tin chi",
        "← Quay lai"
    };
    const char *features_giangVien[] = {
        "Xem danh sach mon hoc",
        "In danh sach sinh vien",
        "In bang diem trung binh",
        "In bang diem tong ket",
        "In danh sach sinh vien da dang ki",
        "In bang diem cua lop tin chi",
        "← Quay lai"
    };
    const char *features_admin[] = {
        "Xem danh sach mon hoc",
        "Them/cap nhat/xoa mon hoc",
        "Tao/cap nhat/huy lop sinh vien",
        "In danh sach sinh vien",
        "In bang diem trung binh",
        "In bang diem tong ket",
        "Tao/cap nhat/huy lop tin chi",
        "In danh sach sinh vien da dang ki",
        "In bang diem cua lop tin chi",
        "← Quay lai"
    };

    int n_roles = 4, n_features_sinhvien = 7, n_features_giangvien = 7, n_features_admin = 10;

    while (1) {
        int r = menu("CHON VAI TRO DANG NHAP", "", roles, n_roles);
        if (r == 3) break;

        const char *role = roles[r];
        if (r == 0) {
            while (1) {
                int f = menu("🏫 QUAN LY HE TIN CHI 🏫", role, features_sinhvien, n_features_sinhvien);
                if (f == n_features_sinhvien - 1) break;

                clrscr();
                gotoxy(10, 10);
                cout << "Ban da chon: " << features_sinhvien[f];
                gotoxy(10, 12);
                cout << "(Nhan phim bat ky de quay lai...)";
                _getch();
            }
        } else if (r == 1) {
            while (1) {
                int f = menu("🏫 QUAN LY HE TIN CHI 🏫", role, features_giangVien, n_features_giangvien);
                if (f == n_features_giangvien - 1) break;

                clrscr();
                gotoxy(10, 10);
                cout << "Ban da chon: " << features_giangVien[f];
                gotoxy(10, 12);
                cout << "(Nhan phim bat ky de quay lai...)";
                _getch();
            }
        } else if (r == 2) {
            while (1) {
                int f = menu("🏫 QUAN LY HE TIN CHI 🏫", role, features_admin, n_features_admin);
                if (f == n_features_admin - 1) break;

                clrscr();
                gotoxy(10, 10);
                cout << "Ban da chon: " << features_admin[f];
                gotoxy(10, 12);
                cout << "(Nhan phim bat ky de quay lai...)";
                _getch();
            }
        }
    }

    clrscr();
    gotoxy(10, 10);
    cout << "Tam biet!\n";
    return 0;
}
