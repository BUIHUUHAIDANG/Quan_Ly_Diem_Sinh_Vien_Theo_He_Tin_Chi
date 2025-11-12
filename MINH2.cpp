#include <iostream>
#include <cstring>
#include "mylib.h"
using namespace std;
enum MenuState { ROLE_SELECT, MAIN_MENU };
enum Role { ROLE_NONE=0, ROLE_SINHVIEN, ROLE_GIANGVIEN, ROLE_ADMIN };

// ====== PERMISSION TABLE ======
struct Permission {
    const char *action;
    bool sinhvien;
    bool giangvien;
    bool admin;
};

Permission permissionTable[] = {
    {"Xem danh sach mon hoc",             true,   true,  true },
    {"Them / cap nhat / xoa mon hoc",     false,  false, true },
    {"Tao / cap nhat / huy lop sinh vien",false,  false, true },
    {"In danh sach sinh vien",            true,   true,  true },
    {"In bang diem trung binh",           true,   true,  true },
    {"In bang diem tong ket",             true,   true,  true },
    {"Tao / cap nhat / huy lop tin chi",  false,  false, true },
    {"In danh sach sinh vien da dang ki", true,   true,  true },
    {"In bang diem cua lop tin chi",      true,   true,  true },
};
int permissionCount = sizeof(permissionTable)/sizeof(permissionTable[0]);

bool checkPermission(Role role, const char *action);
int  buildAllowedList(Role role, int allowed[]);
bool roleSelectionMenu(Role &selectedRole);
void mainMenu(Role role);
void drawLine(int x, int y, int len);
void drawCenteredText(int y, const char *txt, WORD color = 14);

// ====== IMPLEMENTATION ======
bool checkPermission(Role role, const char *action) {
    for (int i = 0; i < permissionCount; ++i) {
        if (strcmp(permissionTable[i].action, action) == 0) {
            if (role == ROLE_SINHVIEN) return permissionTable[i].sinhvien;
            if (role == ROLE_GIANGVIEN) return permissionTable[i].giangvien;
            if (role == ROLE_ADMIN) return permissionTable[i].admin;
        }
    }
    return false;
}

int buildAllowedList(Role role, int allowed[]) {
    int count = 0;
    for (int i = 0; i < permissionCount; ++i) {
        bool ok = false;
        if (role == ROLE_SINHVIEN) ok = permissionTable[i].sinhvien;
        if (role == ROLE_GIANGVIEN) ok = permissionTable[i].giangvien;
        if (role == ROLE_ADMIN) ok = permissionTable[i].admin;
        if (ok) allowed[count++] = i;
    }
    return count;
}

void drawLine(int x, int y, int len) {
    gotoxy(x, y);
    for (int i = 0; i < len; i++) cout << "-";
}

void drawCenteredText(int y, const char *txt, WORD color) {
    int width = 80;
    int len = strlen(txt);
    int x = (width - len) / 2;
    gotoxy(x, y);
    SetColor(color);
    cout << txt;
    ResetColor();
}

// ====== ROLE SELECTION MENU ======
bool roleSelectionMenu(Role &selectedRole) {
    const char *roles[] = {"Sinh vien", "Giang vien", "Admin", "Thoat"};
    int roleCount = 4;
    int index = 0;

    while (true) {
        clrscr();
        drawCenteredText(2, "===== CHON VAI TRO DANG NHAP =====", 14);
        drawLine(20, 3, 40);

        for (int i = 0; i < roleCount; ++i) {
            gotoxy(30, 6 + i);
            if (i == index) {
                SetBGColor(7); SetColor(0);
                cout << "> " << roles[i] << " <";
                ResetColor();
            } else {
                cout << "  " << roles[i] << "  ";
            }
        }

        drawCenteredText(12, "↑ ↓ de chon, Enter de xac nhan, ESC de thoat", 8);

        int c = _getch();
        if (c == 224) {
            int arrow = _getch();
            if (arrow == 72) index = (index - 1 + roleCount) % roleCount; // up
            if (arrow == 80) index = (index + 1) % roleCount;             // down
        } else if (c == Enter) {
            if (index == 3) return false; // Thoat
            selectedRole = (Role)(index + 1);
            return true;
        } else if (c == 27) { // ESC
            return false;
        }
    }
}

// ====== MAIN MENU ======
void mainMenu(Role role) {
    int allowed[20];
    int allowedCount = buildAllowedList(role, allowed);
    int index = 0;
    const char *roleName =
        (role == ROLE_SINHVIEN) ? "Sinh vien" :
        (role == ROLE_GIANGVIEN) ? "Giang vien" : "Admin";

    while (true) {
        clrscr();
        drawCenteredText(2, "🏫 QUAN LY THEO HE TIN CHI 🏫", 12);
        gotoxy(10, 4);
        cout << "Vai tro: ";
        SetColor(10); cout << roleName; ResetColor();

        drawLine(8, 5, 65);
        gotoxy(10, 6); cout << "Chuc nang:";

        for (int i = 0; i < allowedCount; ++i) {
            gotoxy(12, 8 + i);
            if (i == index) {
                SetBGColor(7); SetColor(0);
                cout << permissionTable[allowed[i]].action;
                ResetColor();
            } else {
                cout << permissionTable[allowed[i]].action;
            }
        }

        gotoxy(12, 9 + allowedCount);
        if (index == allowedCount) {
            SetBGColor(7); SetColor(0);
            cout << "<- Quay lai";
            ResetColor();
        } else {
            cout << "<- Quay lai";
        }

        drawCenteredText(12 + allowedCount, "↑ ↓ de chon, Enter de thuc hien (ESC de thoat)", 8);

        int c = _getch();
        if (c == 224) {
            int arrow = _getch();
            if (arrow == 72) index = (index - 1 + allowedCount + 1) % (allowedCount + 1);
            if (arrow == 80) index = (index + 1) % (allowedCount + 1);
        } else if (c == Enter) {
            if (index == allowedCount) return; // Back
            clrscr();
            SetColor(11);
            cout << "[Thuc hien]: " << permissionTable[allowed[index]].action << endl;
            cout << permissionTable[allowed[index]].action; // testing
            ResetColor();
            cout << "\nNhan phim bat ky de tiep tuc...";
            _getch();
        } else if (c == 27) { // ESC
            return;
        }
    }
}

int main() {

    SetConsoleOutputCP(CP_UTF8);

    Role role = ROLE_NONE;
    while (true) {
        clrscr();
        bool ok = roleSelectionMenu(role);
        if (!ok) break;
        clrscr();
        mainMenu(role);
    }

    clrscr();
    SetColor(10);
    cout << "Cam on ban da su dung chuong trinh!\n";
    ResetColor();
    return 0;
}
