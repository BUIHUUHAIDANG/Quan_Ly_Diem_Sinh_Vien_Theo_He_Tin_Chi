#include <iostream> 
#include <conio.h>
#include <cstdio>
#include <cstring>
#include <limits>
#include <iomanip>
#include "CTDL.h"
#include "mylib.h"
#include "menu.h"    
#include "MonHoc.h"
#include "LopSinhVien.h"
using namespace std;

int main() {
    // Khoi tao DS LopSV
    DS_LOPSV ds;
    ds.n = 0;
    for (int i = 0; i < MAX_LOPSV; ++i) ds.nodes[i] = nullptr;

    // Khoi tao DSLTC
    PTRLTC FirstLTC = nullptr;
    stackNode *rootLTC = nullptr;
    treeMH dsMonHoc = nullptr;
    stack undostackMH;
    // Load data (file name theo file binary/text tu ham cua ban)
    loadLopTinChi_Binary(FirstLTC, "LopTinChi.txt", "DSSVDK.txt");  
    loadLopSV_Binary(ds, "LopSV.txt", "SinhVien.txt");
    dsMonHoc = DocMonHoc("MonHocdata.txt");
    // Menu options (khai bao como const char* arrays)
    const char *roles[] = { "Sinh vien", "Giang vien", "Admin", "Thoat" };

    const char *features_sinhvien[] = {
        "Xem danh sach mon hoc",
        "Dang ki/Huy dang ki lop tin chi",
        "Xem danh sach lop tin chi",
        "Xem diem trung binh",
        "Xem diem tong ket",
        "← Quay lai"
    };

    const char *features_giangVien[] = {
        "Xem danh sach mon hoc",
        "Xem danh sach sinh vien",
        "Xem danh sach lop tin chi phu trach",
        "Xem danh sach sinh vien da dang ki lop tin chi phu trach",
        "Nhap diem/ Sua diem cua sinh vien",
        "Xem bang diem cua mot lop tin chi",
        "Xem bang diem trung binh",
        "Xem bang diem tong ket",
        "← Quay lai"
    };

    const char *features_admin[] = {
        "Xem danh sach mon hoc",
        "Xem danh sach lop tin chi",
        "xem danh sach lop sinh vien",
        "Them/cap nhat/xoa mon hoc",
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

    const char *features_admin_3[] = {
        "Them Mon Hoc moi",
        "Xoa Mon Hoc",
        "Sua Mon Hoc",
        "Hoan tac thao tac",
        "← Quay lai"
    };

    const char* SUA_MH_OPTIONS[] = {
    "Sua ten mon hoc",
    "Sua so tin chi ly thuyet",
    "Sua so tin chi thuc hanh",
    "Thoat"
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
    const int n_features_admin_3 = sizeof(features_admin_3) / sizeof(features_admin_3[0]);
    const int n_SUA_MH_OPTIONS = sizeof(SUA_MH_OPTIONS) / sizeof(SUA_MH_OPTIONS[0]);
    const int n_features_admin_4 = sizeof(features_admin_4) / sizeof(features_admin_4[0]);
    const int n_features_admin_7 = sizeof(features_admin_7) / sizeof(features_admin_7[0]);
    const int n_features_admin_9 = sizeof(features_admin_9) / sizeof(features_admin_9[0]);
    const int n_featuresdangkyhuy = sizeof(featuresdangkyhuy) / sizeof(featuresdangkyhuy[0]);

    // Vong chinh
    while (true) {
        AutoCancelExpiredClasses(FirstLTC);
        int r = menu("CHON VAI TRO DANG NHAP", "", roles, n_roles);
        if (r == -1) break; // neu nhan ESC o menu
        if (r == 3) break;  // Thoat

        const char *role = roles[r];

        // === Sinh vien ===
        if (r == 0) {
            while (true) {
                int f = menu("QUAN LY HE TIN CHI", role, features_sinhvien, n_features_sinhvien);
                if (f == -1 || f == n_features_sinhvien - 1) break;

                if (f == 0) {
                    clrscr();
                    gotoxy(10, 10);
                    cout << "Ban da chon: " << features_sinhvien[f] << endl;
                    InDSMH_Bang(dsMonHoc); 
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

                if (f == 0) {
                    clrscr();
                    gotoxy(10, 10);
                    cout << "Ban da chon: " << features_giangVien[f] << endl;
                    InDSMH_Bang(dsMonHoc);
                }
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
                    cout << "Ban da chon: " << features_admin[f] << endl;
                    InDSMH_Bang(dsMonHoc);
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
                else if (f == 3) {
                    clrscr();
                    while (true) {
                        int n = menu("===== THEM/XOA/SUA MON HOC =====", "", features_admin_3, n_features_admin_3);
                        if (n == - 1 || n == n_features_admin_3 - 1) break;
                        
                        if (n == 0) { // Them moi MH
                            clrscr();

                            // ====== TIEU DE ======
                            DrawBox(20, 2, 60, 5, 11);
                            gotoxy(35, 4);
                            SetBold(true);
                            SetColor(14);
                            cout << "NHAP MON HOC";
                            ResetColor();
                            SetBold(false);
                            // ====== KHU NHAP ======
                            gotoxy(0, 8);
                            NhapMonHoc(dsMonHoc, undostackMH);

                            // ====== THONG BAO THANH CONG ======
                            DrawBox(22, 18, 56, 5, 10);
                            gotoxy(30, 20);
                            SetColor(10);
                            cout << ">>> THEM MON HOC THANH CONG <<<";
                            ResetColor();

                            gotoxy(28, 21);
                            cout << "Nhan phim bat ky de quay lai...";
                            getch();

                        }
                        else if (n == 1) { // Xoa MH
                            clrscr();
                            char mamh[11];
                            cout << "Nhap ma mon hoc can xoa: ";
                            cin >> mamh;
                            cin.ignore();
                            dsMonHoc = XoaMH(dsMonHoc, mamh, undostackMH);
                            LuuMonHoc(dsMonHoc, "MonHocdata.txt");
                            cout << "\n>>> Da xoa mon hoc!\n";
                            cout << "Nhan phim bat ky de quay lai...";
                            getch();
                        }
                        else if (n == 2) { // Sua MH
                            clrscr();
                            treeMH temp;
                            MonHoc mh;
                            cout << "Nhap ma mon hoc can sua: ";
                            cin >> mh.MAMH;
                            int n = menu("===== SUA MON HOC =====", "", SUA_MH_OPTIONS, n_SUA_MH_OPTIONS);
                            if (n == - 1 || n == n_SUA_MH_OPTIONS - 1) break;

                            if (n == 0) {
                                temp = getMH(dsMonHoc, mh, undostackMH);
                                SuaTenMH(temp, undostackMH);
                            } 
                            else if (n == 1) {
                                temp = getMH(dsMonHoc, mh, undostackMH);
                                SuaSTCLT(temp, undostackMH);
                            }
                            else if (n == 2) {
                                temp = getMH(dsMonHoc, mh, undostackMH);
                                SuaSTCTH(temp, undostackMH);
                            }

                            LuuMonHoc(dsMonHoc, "MonHocdata.txt");
                            gotoxy(0, 22);
                            cout << "\n>>> Da sua mon hoc!\n";
                            gotoxy(0, 23);
                            cout << "Nhan phim bat ky de quay lai...";
                            getch();
                        }
                        else if (n == 3) { // Undo
                            clrscr();
                            UndoMH(dsMonHoc, undostackMH);
                            LuuMonHoc(dsMonHoc, "MonHocdata.txt");
                            cout << "\n>>> Da hoan tac thao tac!\n";
                            cout << "Nhan phim bat ky de quay lai...";
                            getch();
                        }

                    }
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
                                cout << "Chuc nang sua (chua implement)\n";
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
    ClearTree(dsMonHoc);
    ClearStackMH(undostackMH);
    clrscr();
    gotoxy(10, 10);
    cout << "Tam biet!\n";
    return 0;
}

// g++ main.cpp CTDL.cpp LopSinhVien.cpp MonHoc.cpp menu.cpp mylib.cpp -o main

