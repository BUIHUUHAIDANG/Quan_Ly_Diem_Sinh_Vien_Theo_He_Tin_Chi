#include <iostream>
#include <conio.h>      
#include <windows.h>    
#include <cstdio>
#include <cstring>
<<<<<<< HEAD
#include "mylib.h"    
#include "MonHoc.h"
#include "LopSinhVien.h"

using namespace std;
// === Draw Menu ===
void drawMenu(const char *title, const char *role, const char *options[], int n, int highlight) {
    clrscr();
    SetBGColor(0);  // black background
    SetColor(7);    // white text
=======
#include <limits>

#include "console.h"
#include "MonHoc.h"
#include "LopSinhVien.h"
#include "CTDL.h"

using namespace std;
// Vẽ menu
void drawMenu(const char *title, const char *role, const char *options[], int n, int highlight) {
    clrscr();
    textcolor(7);

>>>>>>> a21d178e19af713955bb738e5fe7a0b7c1f62e28
    gotoxy(20, 2);
    SetBold(true);
    SetColor(4);
    cout << title;
<<<<<<< HEAD
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
=======

    gotoxy(5, 4);
    cout << "Vai tro: " << role;

    for (int i = 0; i < n; ++i) {
        gotoxy(8, 6 + i * 2);
        if (i == highlight) {
            // in ngược để highlight
            printf("\033[47m");   // background white
            printf("\033[30m");   // text black
            cout << "> " << options[i] << " <";
            printf("\033[0m");    // reset
            textcolor(7);
>>>>>>> a21d178e19af713955bb738e5fe7a0b7c1f62e28
        } else {
            cout << "  " << options[i];
        }
    }

    gotoxy(5, 6 + n * 2);
    cout << "(Dung phim ↑ ↓ hoac W/S de di chuyen, Enter de chon)";
}

<<<<<<< HEAD
// === Menu Logic ===
=======
// Nhận phím (getch đã có trong console.h giả sử)
// Trả về ký tự thường hoá cho W/w, S/s; phát hiện Enter = '\n' hoặc 10
>>>>>>> a21d178e19af713955bb738e5fe7a0b7c1f62e28
int menu(const char *title, const char *role, const char *options[], int n) {
    int highlight = 0;
    while (true) {
        drawMenu(title, role, options, n, highlight);
<<<<<<< HEAD
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
=======
        int ch = getch();
        if (ch == 'w' || ch == 'W') {
            highlight = (highlight - 1 + n) % n;
        } else if (ch == 's' || ch == 'S') {
            highlight = (highlight + 1) % n;
        } else if (ch == '\n' || ch == 10 || ch == 13) { // Enter
            return highlight;
        } else if (ch == 27) { // Esc -> trả về -1 (nếu cần xử lý)
            return -1;
>>>>>>> a21d178e19af713955bb738e5fe7a0b7c1f62e28
        }
    }
}

int main() {
<<<<<<< HEAD
    SetConsoleOutputCP(CP_UTF8);
    const char *roles[] = {"Sinh vien", "Giang vien", "Admin", "Thoat"};
    const char *features_sinhvien[] = {
        "Xem danh sach mon hoc",
        "In danh sach sinh vien",
        "In bang diem trung binh",
        "In bang diem tong ket",
        "In danh sach sinh vien da dang ki",
        "In bang diem cua lop tin chi",
=======
    // Khoi tao DS LopSV
    DS_LOPSV ds;
    ds.n = 0;
    for (int i = 0; i < MAX_LOPSV; ++i) ds.nodes[i] = nullptr;

    // Khoi tao DSLTC
    PTRLTC FirstLTC = nullptr;
    stackNode *rootLTC = nullptr;
    // Load data (file name theo file binary/text tu ham cua ban)
    loadLopTinChi_Binary(FirstLTC, "LopTinChi.txt", "DSSVDK.txt");
    loadLopSV_Binary(ds, "LopSV.txt", "SinhVien.txt");
    // Menu options (khai bao como const char* arrays)
    const char *roles[] = { "Sinh vien", "Giang vien", "Admin", "Thoat" };

    const char *features_sinhvien[] = {
        "Xem danh sach mon hoc",
        "Dang ki/Huy dang ki lop tin chi",
        "Xem danh sach lop tin chi",
        "Xem diem trung binh",
        "Xem diem tong ket",
>>>>>>> a21d178e19af713955bb738e5fe7a0b7c1f62e28
        "← Quay lai"
    };

    const char *features_giangVien[] = {
        "Xem danh sach mon hoc",
<<<<<<< HEAD
        "In danh sach sinh vien",
        "In bang diem trung binh",
        "In bang diem tong ket",
        "In danh sach sinh vien da dang ki",
        "In bang diem cua lop tin chi",
=======
        "Xem danh sach sinh vien",
        "Xem danh sach lop tin chi phu trach",
        "Xem danh sach sinh vien da dang ki lop tin chi phu trach",
        "Nhap diem/ Sua diem cua sinh vien",
        "Xem bang diem cua mot lop tin chi",
        "Xem bang diem trung binh",
        "Xem bang diem tong ket",
>>>>>>> a21d178e19af713955bb738e5fe7a0b7c1f62e28
        "← Quay lai"
    };

    const char *features_admin[] = {
        "Xem danh sach mon hoc",
        "Xem danh sach lop tin chi",
        "xem danh sach lop sinh vien",
        "Them/cap nhat/xoa mon hoc",
<<<<<<< HEAD
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
=======
        "Them/cap nhat/huy lop tin chi",
        "Xem danh sach sinh vien da dang ky lop tin chi",
        "Xem bang diem cua lop tin chi",
        "Them/cap nhat/huy lop sinh vien",
        "Them sinh vien vao 1 lop",
        "Xem danh sach sinh vien",
        "Xem bang diem trung binh",
        "Xem bang diem tong ket",
        "← Quay lai"
    };

    const char *features_admin_4[] = {
        "Them moi Lop Tin Chi",
        "Cap nhat xoa sua Lop Tin Chi",
        "Hieu chinh Lop Tin Chi",
        "← Quay lai"
    };

    const char *features_admin_7[] = {
        "them lop sinh vien",
        "sua lop sinh vien",
        "xoa lop sinh vien",
        "Quay lai"
    };
>>>>>>> a21d178e19af713955bb738e5fe7a0b7c1f62e28

    const char *features_admin_9[] = {
        "Xem danh sach sinh vien(dua vao ma lop) theo thu tu alphabet theo ten",
        "xem danh sach ....",
        "← Quay lai"
    };

    const char *featuresdangkyhuy[] = {
        "Dang ky LTC",
        "Huy LTC",
        "← Quay lai"
    };

    const int n_roles = sizeof(roles) / sizeof(roles[0]);
    const int n_features_sinhvien = sizeof(features_sinhvien) / sizeof(features_sinhvien[0]);
    const int n_features_giangvien = sizeof(features_giangVien) / sizeof(features_giangVien[0]);
    const int n_features_admin = sizeof(features_admin) / sizeof(features_admin[0]);
    const int n_features_admin_4 = sizeof(features_admin_4) / sizeof(features_admin_4[0]);
    const int n_features_admin_7 = sizeof(features_admin_7) / sizeof(features_admin_7[0]);
    const int n_features_admin_9 = sizeof(features_admin_9) / sizeof(features_admin_9[0]);
    const int n_featuresdangkyhuy = sizeof(featuresdangkyhuy) / sizeof(featuresdangkyhuy[0]);

    // Vong chinh
    while (true) {
        int r = menu("CHON VAI TRO DANG NHAP", "", roles, n_roles);
<<<<<<< HEAD
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
=======
        if (r == -1) break; // neu nhan ESC o menu
        if (r == 3) break;  // Thoat

        const char *role = roles[r];

        // === Sinh vien ===
        if (r == 0) {
            while (true) {
                int f = menu("QUAN LY HE TIN CHI", role, features_sinhvien, n_features_sinhvien);
                if (f == -1 || f == n_features_sinhvien - 1) break;
>>>>>>> a21d178e19af713955bb738e5fe7a0b7c1f62e28

                if (f == 0) {
                    clrscr();
                    gotoxy(10, 10);
                    cout << "Chuc nang: " << features_sinhvien[f];
                    gotoxy(10, 12);
                    cout << "(Nhan phim bat ky de quay lai...)";
                    getch();
                }
                else if (f == 1) {
                    // Dang ky / Huy
                    while (true) {
                        int g = menu("SINH VIEN DANG KY/HUY LTC", role, featuresdangkyhuy, n_featuresdangkyhuy);
                        if (g == -1 || g == n_featuresdangkyhuy - 1) break;
                        if (g == 0) {
                            clrscr();
                            // TODO: goi ham dang ky
                            dangkyLTC(FirstLTC,ds);
                            saveLopTinChi_Binary(FirstLTC, "LopTinChi.txt", "DSSVDK.txt");
                            cout << "Thuc hien dang ky...\n";
                            getch();
                        } else if (g == 1) {
                            clrscr();
                            // TODO: goi ham huy
                            cout << "Thuc hien huy...\n";
                            getch();
                        }
                    }
                } else {
                    clrscr();
                    gotoxy(10, 10);
                    cout << "Chuc nang (chua cài): " << features_sinhvien[f];
                    InDSLTC(FirstLTC);
                    gotoxy(10, 12);
                    cout << "(Nhan phim bat ky de quay lai...)";
                    getch();
                }
            }
        }

        // === Giang vien ===
        else if (r == 1) {
            while (true) {
                int f = menu("QUAN LY HE TIN CHI", role, features_giangVien, n_features_giangvien);
                if (f == -1 || f == n_features_giangvien - 1) break;

                clrscr();
                gotoxy(10, 10);
                cout << "Ban da chon: " << features_giangVien[f];
                gotoxy(10, 12);
                cout << "(Nhan phim bat ky de quay lai...)";
                getch();
            }
        }

        // === Admin ===
        else if (r == 2) {
            while (true) {
                int f = menu("QUAN LY HE TIN CHI", role, features_admin, n_features_admin);
                if (f == -1 || f == n_features_admin - 1) break;

                // Mot so chuc nang minh da implement (in danh sach, them LTC, ...), cac chuc nang khac de TODO
                if (f == 0) {
                    clrscr();
                    gotoxy(10, 10);
                    cout << "Ban da chon: " << features_admin[f];
                    gotoxy(10, 12);
                    cout << "(Nhan phim bat ky de quay lai...)";
                    getch();
                }
                else if (f == 1) {
                    clrscr();
                    gotoxy(10, 10);
                    cout << "Ban da chon: " << features_admin[f];
                    InDSLTC(FirstLTC); // ham hien thi tu header
                    gotoxy(10, 12);
                    cout << "(Nhan phim bat ky de quay lai...)";
                    getch();
                }
                else if (f == 2) {
                    clrscr();
                    gotoxy(10, 10);
                    InDSLSV(ds); // hien ds lop sinh vien
                    cout << "(Nhan phim bat ky de quay lai...)";
                    getch();
                }
                else if (f == 4) { // Them/CN/Huy LTC
                    while (true) {
                        int n = menu("===== THEM/XOA/SUA LOP TIN CHI =====", "", features_admin_4, n_features_admin_4);
                        if (n == -1 || n == n_features_admin_4 - 1) break;

                        if (n == 0) { // Them moi LTC
                            clrscr();
                            LopTinChi ltc = NhapLTC();
                            ltc.MALOPTC = getNextMaLopTinChi(FirstLTC);
                            insertLopTinChi(FirstLTC, ltc);
                            saveLopTinChi_Binary(FirstLTC, "LopTinChi.txt", "DSSVDK.txt");
                            cout << "\n>>> Da them lop tin chi thanh cong! MA MOI: " << ltc.MALOPTC;
                            ActionLTC act; act.type = 1; act.ltc = ltc;
                            push(rootLTC, act);
                            cout << "\nNhan phim bat ky de quay lai...";
                            getch();
                        }
                        else if (n == 1) { // Cap nhat/Sua
                            clrscr();
                            cout << "=== SUA LOP TIN CHI ===\n";
                            int malop;
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            cout << "Nhap Ma Lop TC muon sua: ";
                            cin >> malop;
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');

                            PTRLTC tmp = searchLopTinChi(FirstLTC, malop);
                            if (!tmp) {
                                cout << "Khong tim thay Lop Tin Chi\n";
                                getch();
                                clrscr();
                                continue;
                            }

                            LopTinChi oldLTC = tmp->ltc;
                            if (editLopTinChi(FirstLTC, malop)) {
                                saveLopTinChi_Binary(FirstLTC, "LopTinChi.txt", "DSSVDK.txt");
                                cout << "\n>>> Sua thong tin lop tin chi thanh cong!";
                                ActionLTC act; act.type = 3; act.ltc = oldLTC;
                                push(rootLTC, act);
                            } else {
                                cout << "\n>>> Khong the sua lop tin chi!";
                            }
                            cout << "\nNhan phim bat ky de quay lai...";
                            getch();
                        }
                        else if (n == 2) { // Undo/Hieu chinh
                            clrscr();
                            undoLTC(FirstLTC, rootLTC);
                            saveLopTinChi_Binary(FirstLTC, "LopTinChi.txt", "DSSVDK.txt");
                            cout << "(Nhan phim bat ky de quay lai...)";
                            getch();
                        }
                    }
                }
                else if (f == 5) { // Xem DSSV da dang ky
                    clrscr();
                    cout << "=== DANH SACH SINH VIEN DA DANG KY LOP TIN CHI ===\n";
                    PTRLTC pLTC = findLTCByParams(FirstLTC);
                    if (pLTC) {
                        showDanhSachSinhVienDangKy(pLTC->ltc.dssvdk);
                    } else {
                        cout << "Khong tim thay lop tin chi voi cac tham so da nhap.\n";
                    }
                    cout << "\nNhan phim bat ky de quay lai...";
                    getch();
                }
                else if (f == 7) { // Quan ly lop sinh vien
                    while (true) {
                        int n = menu("Quan Ly Lop Sinh Vien", "", features_admin_7, n_features_admin_7);
                        if (n == -1 || n == n_features_admin_7 - 1) break;

                        if (n == 0) { // Them lop sinh vien
                            clrscr();
                            NhapLopSV(ds);
                            saveLopSV_Binary(ds, "LopSV.txt", "SinhVien.txt");
                            cout << "(Nhan phim bat ky de quay lai...)";
                            getch();
                        }
                        else if (n == 1) { // Sua lop sinh vien (basic)
                            clrscr();
                            char malop[16];
                            cout << "Nhap ma lop can sua: ";
                            cin.getline(malop, 16);
                            int pos = posLop(ds, malop);
                            if (pos == -1) {
                                cout << "Khong tim thay lop\n";
                                getch();
                            } else {
                                // TODO: goi ham sua
                                cout << "[Du Lieu]====[Du Lieu Cu]====[Du Lieu Moi]\n";
                                cout << "Neu muon giu lai du lieu chi can nhap {0}\n";
                                int a=editLopSinhVien(ds,pos);
                                if(a==1){
                                    cout<<"Du lieu duoc cap nhat thanh cong!"<<endl;
                                }
                                else{
                                    cout<<"Du lieu duoc giu nguyen nhu cu!"<<endl;
                                }
                                getch();
                            }
                        }
                        else if (n == 2) { // Xoa
                            clrscr();
                            char malop[16];
                            cout << "Nhap ma lop can xoa: ";
                            cin.getline(malop, 16);
                            int pos = posLop(ds, malop);
                            if (pos == -1) {
                                cout << "khong tim thay lop\n";
                                getch();
                            } else {
                                xoaLopByPos(ds, pos);
                                cout << "Xoa Lop Thanh Cong\n";
                                saveLopSV_Binary(ds, "LopSV.txt", "SinhVien.txt");
                                getch();
                            }
                        }
                    }
                }
                else if (f == 8) { // Nhap sinh vien vao lop
                    clrscr();
                    gotoxy(10, 10);
                    cout << "=== NHAP SINH VIEN VAO LOP ===\n";

                    char malop[16];
                    cout << "Nhap Ma Lop: ";
                    cin.getline(malop, 16);

                    LopSV *lop = searchLopSV(ds, malop);
                    if (!lop) {
                        cout << "Khong tim thay lop!\n";
                        getch();
                        continue;
                    }

                    cout << "Ten lop: " << lop->TENLOP << endl;
                    SinhVien sv;
                    while (true) {
                        cout << "\nNhap ma SV (Enter de dung): ";
                        cin.getline(sv.MASV, 16);
                        if (sv.MASV[0] == '\0') break;

                        cout << "Nhap ho: "; cin.getline(sv.HO, 51);
                        cout << "Nhap ten: "; cin.getline(sv.TEN, 11);
                        cout << "Nhap phai: "; cin.getline(sv.PHAI, 4);
                        cout << "Nhap so dien thoai: "; cin.getline(sv.SODT, 16);
                        cout << "Nhap email: "; cin.getline(sv.Email, 50);

                        insertSinhVien(lop->FirstSV, sv);
                    }

                    saveLopSV_Binary(ds, "LopSV.txt", "SinhVien.txt");
                    cout << "\n>>> Da cap nhat danh sach sinh vien vao lop!\n";
                    cout << "(Nhan phim bat ky de quay lai...)";
                    getch();
                }
                else if (f == 9) { // Xem danh sach sinh vien theo alphabet
                    while (true) {
                        int n = menu("======= XEM DANH SACH SINH VIEN =======", "", features_admin_9, n_features_admin_9);
                        if (n == -1 || n == n_features_admin_9 - 1) break;
                        if (n == 0) {
                            clrscr();
                            cout << "=== XEM DANH SACH SINH VIEN THEO ALPHABET ===\n";
                            char malop[20];
                            cout << "Nhap Ma Lop: ";
                            cin >> malop;
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');

                            LopSV *lop = searchLopSV(ds, malop);
                            if (!lop) {
                                cout << "\n>>> Khong tim thay lop!\n";
                                cout << "Nhan phim bat ky de quay lai...";
                                getch();
                                continue;
                            }

                            cout << "\nMa lop : " << lop->MALOP << endl;
                            cout << "Ten lop: " << lop->TENLOP << endl;

                            printDSSV_sorted(lop);
                            cout << "\nNhan phim bat ky de quay lai...";
                            getch();
                        }
                    }
                }
                else {
                    // Các trường hợp khác chưa implement
                    clrscr();
                    cout << "Chuc nang chua duoc ho tro: " << features_admin[f] << "\n";
                    cout << "(Nhan phim bat ky de quay lai...)";
                    getch();
                }
            }
        } // end admin
    } // end while main

    // Giai phong bo nho truoc khi thoat
    ClearLTC(FirstLTC);
    ClearDS_Lop(ds);
    ClearStackLTC(rootLTC);
    clrscr();
    gotoxy(10, 10);
    cout << "Tam biet!\n";
    return 0;
}
