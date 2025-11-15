#include <iostream>
#include <termios.h>
#include <unistd.h>
#include <cstdio>
#include <cstring>
#include "console.h"
#include "MonHoc.h"
#include "LopSinhVien.h"
using namespace std;
void drawMenu(const char *title, const char *role, const char *options[], int n, int highlight) {
    clrscr();
    textcolor(7); 
    gotoxy(20, 2);
    cout << title;
    gotoxy(5, 4);
    cout << "Vai tro: " << role;

    for (int i = 0; i < n; i++) {
        gotoxy(8, 6 + i * 2);
        if (i == highlight) {
            textcolor(0);
            printf("\033[47m"); 
            cout << "> " << options[i] << " <";
            printf("\033[0m"); 
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
// Menu cua  LTC 


int main() {
    const char *roles[] = {"Sinh vien", "Giang vien", "Admin", "Thoat"};
    const char *features_sinhvien[] = {
        "Xem danh sach mon hoc",
        "In danh sach sinh vien",
        "In bang diem trung binh",
        "In bang diem tong ket",
        "In danh sach sinh vien da dang ki",// cua Dang 
        "In bang diem cua lop tin chi",
        "← Quay lai"
    };
    const char *features_giangVien[] = {
        "Xem danh sach mon hoc",
        "In danh sach sinh vien",// cua Dang -> DSSV theo alphabet
        "In bang diem trung binh",
        "In bang diem tong ket",
        "In danh sach sinh vien da dang ki", // cua Dang
        "In bang diem cua lop tin chi",
        "← Quay lai"
    };
    const char *features_admin[] = {
        "Xem danh sach mon hoc",
        "Them/cap nhat/xoa mon hoc",
        "Tao/cap nhat/huy lop sinh vien",// cua Dang (nhap lop -> tu hien ra ma Lop-> nhap SV) (detail_feat_3)
        "In danh sach sinh vien",
        "In bang diem trung binh",
        "In bang diem tong ket",
        "Tao/cap nhat/huy lop tin chi",// cua Dang
        "In danh sach sinh vien da dang ki",
        "In bang diem cua lop tin chi",
        "← Quay lai"
    };
    //function them/xoa/sua LTC
    const char *features_admin_6[] = {
        "Them moi Lop Tin Chi",
        "Cap nhat xoa sua Lop Tin Chi",
        "Huy Lop Tin Chi",
        "← Quay lai"
    };
    int n_features_admin_6=4;// num of func 6


    int n_roles = 4, n_features_sinhvien = 7,n_features_giangvien=7,n_features_admin=10;

    while (1) {
        int r = menu("CHON VAI TRO DANG NHAP", "", roles, n_roles);
        if (r == 3) break; 

        const char *role = roles[r];
        if(r==0){
        while (1) {
            int f = menu(" QUAN LY HE TIN CHI ", role, features_sinhvien, n_features_sinhvien);
            if (f == n_features_sinhvien - 1) break;
            
            clrscr();
            gotoxy(10, 10);
            cout << "Ban da chon: " << features_sinhvien[f];
            gotoxy(10, 12);
            cout << "(Nhan phim bat ky de quay lai...)";
            getch();
        }}
        if(r==1){
        while (1) {
            int f = menu(" QUAN LY HE TIN CHI ", role, features_giangVien, n_features_giangvien);
            if (f == n_features_giangvien - 1) break;

            clrscr();
            gotoxy(10, 10);
            cout << "Ban da chon: " << features_giangVien[f];
            gotoxy(10, 12);
            cout << "(Nhan phim bat ky de quay lai...)";
            getch();
        }}
        if(r==2){
        while (1) {
            int f = menu(" QUAN LY HE TIN CHI ", role, features_admin, n_features_admin);
            if (f == n_features_admin - 1) break;
            if(f==0){
                clrscr();
            gotoxy(10, 10);
            cout << "Ban da chon: " << features_admin[f];
            gotoxy(10, 12);
            cout << "(Nhan phim bat ky de quay lai...)";
            getch();
            }
            if(f==1){
                clrscr();
            gotoxy(10, 10);
            cout << "Ban da chon: " << features_admin[f];
            gotoxy(10, 12);
            cout << "(Nhan phim bat ky de quay lai...)";
            getch();
            }
            if(f==2){
                clrscr();
            gotoxy(10, 10);
            cout << "Ban da chon: " << features_admin[f];
            gotoxy(10, 12);
            cout << "(Nhan phim bat ky de quay lai...)";
            getch();
            }
            if(f==3){
                clrscr();
            gotoxy(10, 10);
            cout << "Ban da chon: " << features_admin[f];
            gotoxy(10, 12);
            cout << "(Nhan phim bat ky de quay lai...)";
            getch();
            }
            if(f==4){
                clrscr();
            gotoxy(10, 10);
            cout << "Ban da chon: " << features_admin[f];
            gotoxy(10, 12);
            cout << "(Nhan phim bat ky de quay lai...)";
            getch();
            }
            if(f==5){
                clrscr();
            gotoxy(10, 10);
            cout << "Ban da chon: " << features_admin[f];
            gotoxy(10, 12);
            cout << "(Nhan phim bat ky de quay lai...)";
            getch();
            }
            if(f==6){
            while(1){
                int n = menu("=======THEM/XOA/SUA LOP TIN CHI=======","",features_admin_6,n_features_admin_6);
                if(n==n_features_admin_6-1)break;
                if(n==0){
                    clrscr();
                    gotoxy(10, 10);
                    cout << "Ban da chon: " << features_admin_6[n];
                    gotoxy(10, 12);
                    cout << "(Nhan phim bat ky de quay lai...)";
                    getch();
                }
                if(n==1){
                    clrscr();
                    gotoxy(10, 10);
                    cout << "Ban da chon: " << features_admin_6[n];
                    gotoxy(10, 12);
                    cout << "(Nhan phim bat ky de quay lai...)";
                    getch();
                }
                if(n==2){
                    clrscr();
                    gotoxy(10, 10);
                    cout << "Ban da chon: " << features_admin_6[f];
                    gotoxy(10, 12);
                    cout << "(Nhan phim bat ky de quay lai...)";
                    getch();
                }
            }
            }
            if(f==7){
                clrscr();
            gotoxy(10, 10);
            cout << "Ban da chon: " << features_admin[f];
            gotoxy(10, 12);
            cout << "(Nhan phim bat ky de quay lai...)";
            getch();
            }
            if(f==8){
                clrscr();
            gotoxy(10, 10);
            cout << "Ban da chon: " << features_admin[f];
            gotoxy(10, 12);
            cout << "(Nhan phim bat ky de quay lai...)";
            getch();
            }
        }}
    }

    clrscr();
    gotoxy(10, 10);
    cout << "Tam biet!\n";
    return 0;
}
