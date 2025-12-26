#include <iostream>    
#include <cstdio>
#include <cstring>
#include <limits>

#include "mylib.h"
#include "MonHoc.h"
#include "LopSinhVien.h"
#include "CTDL.h"

using namespace std;
void drawStaticMenu(const char *title, const char *role, int n) {
    int baseX = 75;
    int baseY = 4;

    clrscr();
    SetBGColor(0);
    SetColor(7);

    gotoxy(baseX + 10, baseY);
    SetBold(true);
    SetColor(4);
    cout << title;
    SetBold(false);
    ResetColor();

    drawLine(baseX, baseY + 1, 40);

    gotoxy(baseX, baseY + 2);
    cout << "Vai tro: ";
    SetBold(true);
    SetColor(10);
    cout << role;
    ResetColor();
    SetBold(false);

    gotoxy(baseX, baseY + 4 + n * 2);
    cout << "(↑ ↓ hoac W/S de di chuyen, Enter de chon)";
}

void drawOptions(const char *options[], int n, int highlight) {
    int baseX = 75;
    int baseY = 4;

    for (int i = 0; i < n; i++) {
        gotoxy(baseX + 3, baseY + 4 + i * 2);
        cout << string(80, ' ');

        gotoxy(baseX + 3, baseY + 4 + i * 2);
        if (i == highlight) {
            SetBGColor(7);
            SetColor(0);
            cout << "> " << options[i] << " <";
        } else {
            ResetColor();
            cout << "  " << options[i];
        }
        ResetColor();
    }
}



int menu(const char *title, const char *role, const char *options[], int n)  {
    int highlight = 0;
    drawStaticMenu(title, role, n);
    while (true) {
        drawOptions(options, n, highlight);
        int ch = getch();
        // support both arrow keys and WASD
        if (ch == 27 && getch() == 91) {  
        int arrow = getch(); // byte cuối xác định hướng
        if (arrow == 65) highlight = (highlight - 1 + n) % n; // ↑
        if (arrow == 66) highlight = (highlight + 1) % n;     // ↓
           }
       else if (ch == 'w' || ch == 'W')
           highlight = (highlight - 1 + n) % n;
       else if (ch == 's' || ch == 'S')
           highlight = (highlight + 1) % n;
       else if (ch == 10 || ch == 13) // Enter trên Linux = 10
           return highlight;
       }
}   
   
int main() {
    //Khoi tao Tree
    treeMH dsmh=nullptr;
    stack undostackMH;
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
    dsmh = DocMonHoc("MonHocdata.txt");
    // Menu options (khai bao como const char* arrays)
    const char *roles[] = { "Sinh vien", "Giang vien", "Admin", "Thoat" };

    const char *features_sinhvien[] = {
        "Xem danh sach mon hoc",
        "Dang ki/Huy dang ki lop tin chi",//done
        "Xem danh sach lop tin chi",//done
        "Xem diem trung binh",//->MASV->done
        "Xem diem tong ket",//->MASV->done
        "← Quay lai"
    };

    const char *features_giangVien[] = {
        "Xem danh sach mon hoc",
        "Xem danh sach sinh vien",
        "Xem danh sach lop tin chi",
        "Xem danh sach sinh vien da dang ki lop tin chi",
        "Nhap diem/ Sua diem cua sinh vien",//done
        "Xem bang diem cua mot lop tin chi",//done
        "Xem bang diem trung binh",//done
        "Xem bang diem tong ket",//done
        "← Quay lai"
    };

    const char *features_admin[] = {
        "Xem danh sach mon hoc",//done
        "Xem danh sach lop tin chi",//done
        "xem danh sach lop sinh vien",//done
        "Them/cap nhat/xoa mon hoc",//done
        "Them/cap nhat/huy lop tin chi",//done
        "Xem danh sach sinh vien da dang ky lop tin chi",//done
        "Xem bang diem cua lop tin chi",
        "Them/cap nhat/huy lop sinh vien",//done
        "Them sinh vien vao 1 lop",//done
        "Xem danh sach sinh vien",//done
        "Xem bang diem trung binh",//done
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
    const char *features_admin_8[]= {
        "Them Sinh Vien vao 1 lop",
        "Xoa Sinh Vien",
        "Sua Sinh Vien",
        "Quay lai"
    };

    const char *features_admin_9[] = {
        "Xem danh sach sinh vien theo thu tu alphabet",
        "xem danh sach sinh vien (dua vao ma lop)",
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
    const int n_features_admin_4 = sizeof(features_admin_4) / sizeof(features_admin_4[0]);
    const int n_features_admin_7 = sizeof(features_admin_7) / sizeof(features_admin_7[0]);
    const int n_features_admin_8 = sizeof(features_admin_8) / sizeof(features_admin_8[0]);
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
                    cout << "Chuc nang: " << features_sinhvien[f]<<endl;
                    InDSMH(dsmh);
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
                } else if(f==2) {
                    clrscr();
                    gotoxy(10, 10);
                    cout << "Chuc nang: " << features_sinhvien[f]<<endl;
                    InDSLTC(FirstLTC);
                }
                else if(f==3){
                    clrscr();
                    gotoxy(10, 10);
                    cout << "Chuc nang: " << features_sinhvien[f]<<endl;
                    IndiemtbSinhvien(FirstLTC,ds,dsmh);
                    cout << "(Nhan phim bat ky de quay lai...)";
                    getch();
                }
                else if(f==4){
                    clrscr();
                    gotoxy(10, 10);
                    cout << "Chuc nang: " << features_sinhvien[f]<<endl;
                    InbangdiemtongketSinhvien(FirstLTC,ds,dsmh);
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
                if(f==0){
                    clrscr();
                    gotoxy(10, 10);
                    cout << "Chuc nang: " << features_sinhvien[f]<<endl;
                    InDSMH(dsmh);
                }
                else if(f==1){
                    clrscr();
                    gotoxy(10, 10);
                    InDSLSV(ds); // hien ds lop sinh vien
                }
                else if(f==2){
                    clrscr();
                    gotoxy(10, 10);
                    cout << "Ban da chon: " << features_admin[f]<<endl;
                    InDSLTC(FirstLTC); // ham hien thi tu header
                }
                else if(f==3){
                    clrscr();
                    cout << "=== DANH SACH SINH VIEN DA DANG KY LOP TIN CHI ===\n";
                    PTRLTC pLTC = findLTCByParams(FirstLTC);
                    if (pLTC) {
                        showDanhSachSinhVienDangKy(pLTC->ltc.dssvdk,ds);
                    } else {
                        cout << "Khong tim thay lop tin chi voi cac tham so da nhap.\n";
                        cout << "\nNhan phim bat ky de quay lai...";
                        getch();
                    }
                }
                else if(f==4){
                   clrscr();
                   gotoxy(10, 10);
                   cout << "Ban da chon: " << features_giangVien[f]<<endl;
                   NhapDiem(FirstLTC,ds);
                   saveLopTinChi_Binary(FirstLTC, "LopTinChi.txt", "DSSVDK.txt");
                }
                else if(f==5){
                   clrscr();
                   gotoxy(10, 10);
                   cout << "Ban da chon: " << features_giangVien[f]<<endl;
                   InbangDiemLTC(FirstLTC,ds);
                }
                else if(f==6){
                   clrscr();
                   gotoxy(10, 10);
                   cout << "Ban da chon: " << features_giangVien[f]<<endl;
                   IndiemtbLop(FirstLTC,ds,dsmh);
                }
                else if(f==7){
                   clrscr();
                   gotoxy(10, 10);
                   cout << "Ban da chon: " << features_giangVien[f]<<endl;
                   InbangdiemtongketLop(FirstLTC,ds,dsmh);  
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
                    cout << "Ban da chon: " << features_admin[f]<<endl;
                    InDSMH(dsmh);
                }
                else if (f == 1) {
                    clrscr();
                    gotoxy(10, 10);
                    cout << "Ban da chon: " << features_admin[f]<<endl;
                    InDSLTC(FirstLTC); // ham hien thi tu header
                }
                else if (f == 2) {
                    clrscr();
                    gotoxy(10, 10);
                    InDSLSV(ds); // hien ds lop sinh vien
                }
                else if (f == 3) {
                    clrscr();
                    while (true) {
                        int n = menu("===== THEM/XOA/SUA MON HOC =====", "", features_admin_3, n_features_admin_3);
                        if (n == - 1 || n == n_features_admin_3 - 1) break;
                        
                        if (n == 0) { // Them moi MH
                            clrscr();
                            cout << "\n=== Nhap mon hoc ===\n";
                            NhapMonHoc(dsmh, undostackMH);
                        }
                        else if (n == 1) { // Xoa MH
                            clrscr();
                            char mamh[11];
                            cout << "Nhap ma mon hoc can xoa: ";
                            cin >> mamh;
                            dsmh = XoaMH(dsmh, mamh, undostackMH);
                            LuuMonHoc(dsmh, "MonHocdata.txt");
                            cout << "\n>>> Da xoa mon hoc!\n";
                            cout << "Nhan phim bat ky de quay lai...";
                            getch();
                        }
                        else if (n == 2) { // Sua MH
                            clrscr();
                            MonHoc mh;
                            cout << "Nhap ma mon hoc can sua: ";
                            cin >> mh.MAMH;
                            SuaMH(dsmh, mh, undostackMH);
                            LuuMonHoc(dsmh, "MonHocdata.txt");
                            cout << "\n>>> Da sua mon hoc!\n";
                            cout << "Nhan phim bat ky de quay lai...";
                            getch();
                        }
                        else if (n == 3) { // Undo
                            clrscr();
                            UndoMH(dsmh, undostackMH);
                            LuuMonHoc(dsmh, "MonHocdata.txt");
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
                            while (true) {
                                clrscr();
                            
                                LopTinChi ltc = NhapLTC();
                                ltc.MALOPTC = getNextMaLopTinChi(FirstLTC);
                            
                                insertLopTinChi(FirstLTC, ltc);
                                saveLopTinChi_Binary(FirstLTC, "LopTinChi.txt", "DSSVDK.txt");
                            
                                cout << "\n>>> Da them lop tin chi thanh cong!";
                                cout << "\n>>> MA LOP TC MOI: " << ltc.MALOPTC;
                            
                                // Undo / Action
                                ActionLTC act;
                                act.type = 1;      // 1 = them
                                act.ltc  = ltc;
                                push(rootLTC, act);
                            
                                cout << "\n\nNhan [ESC] de thoat | Nhan phim bat ky de them tiep...";
                            
                                char key = getch();
                                if (key == 27) break;   // ESC -> thoat chuc nang
                            }
                        }
                        else if (n == 1) { // Cap nhat/Sua
                            clrscr();
                            cout << "=== SUA LOP TIN CHI ===\n";
                            int malop;
                            while (true) {
                            cout << "Nhap Ma Lop TC muon sua: ";
                            cin >> malop;
                        
                            if (!cin.fail() && malop > 0) {
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                break;
                            }
                        
                            cout << "Loi! Hay nhap so nguyen > 0\n";
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            }

                            PTRLTC tmp = searchLopTinChi(FirstLTC, malop);
                            if (!tmp) {
                                cout << "Khong tim thay Lop Tin Chi\n";
                                cout << "nhan bat ky phim nao de quay lai...."<<endl;
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
                        showDanhSachSinhVienDangKy(pLTC->ltc.dssvdk,ds);
                    } else {
                        cout << "Khong tim thay lop tin chi voi cac tham so da nhap.\n";
                        cout << "\nNhan phim bat ky de quay lai...";
                        getch();
                    }
                }
                else if (f==6){
                   clrscr();
                   gotoxy(10, 10);
                   cout << "Ban da chon: " << features_giangVien[f]<<endl;
                   InbangDiemLTC(FirstLTC,ds);
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
                            toUpperCase(malop);
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
                            toUpperCase(malop);
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
                    while(true){
                    int n = menu("Quan Ly Sinh Vien", "", features_admin_8, n_features_admin_8);
                    if (n == -1 || n == n_features_admin_8 - 1) break;
                    if (n==0){
                    clrscr();
                    NhapSinhVien(ds);
                    saveLopSV_Binary(ds, "LopSV.txt", "SinhVien.txt");
                    cout << "\n>>> Da cap nhat danh sach sinh vien vao lop!\n";
                    cout << "(Nhan phim bat ky de quay lai...)";
                    getch();
                    }
                    if (n==1){
                     clrscr();
                     char malop[16], masv[16];

                     cout << "Nhap ma lop: ";
                     cin.getline(malop, 16);
                     LopSV *lop = searchLopSV(ds, malop);
                     if (!lop) {
                         cout << "Khong tim thay lop!\n";
                         getch();
                         continue;
                     }

                     cout << "Nhap ma sinh vien can xoa: ";
                     cin.getline(masv, 16);
                     toUpperCase(masv);

                     if (deleteSinhVien(lop->FirstSV, masv)) {
                         cout << ">>> Xoa sinh vien thanh cong!\n";
                         saveLopSV_Binary(ds, "LopSV.txt", "SinhVien.txt");
                     } else {
                         cout << "Khong tim thay sinh vien!\n";
                     }
                     getch();
                    }
                    if (n==2){
                      clrscr();
                      char malop[16], masv[16];

                      cout << "Nhap ma lop: ";
                      cin.getline(malop, 16);
                      toUpperCase(malop);
                      LopSV *lop = searchLopSV(ds, malop);
                      if (!lop) {
                          cout << "Khong tim thay lop!\n";
                          getch();
                          continue;
                      }

                     cout << "Nhap ma sinh vien can sua: ";
                     cin.getline(masv, 16);
                     toUpperCase(masv);

                     if (editSinhVien(lop->FirstSV, masv)) {
                         cout << "\n>>> Cap nhat sinh vien thanh cong!\n";
                         saveLopSV_Binary(ds, "LopSV.txt", "SinhVien.txt");
                     }
                     getch();
                    }
                  }
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

                        }
                        if(n==1){
                          clrscr();
                          cout << "=== XEM DANH SACH SINH VIEN ===\n";
                          char malop[20];
                          cout << "Nhap Ma Lop: ";
                          cin >> malop;
                          toUpperCase(malop);
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
                          printDSSV(lop);
                        }

                    }
                }
                else if(f==10){
                   clrscr();
                   gotoxy(10, 10);
                   cout << "Ban da chon: " << features_admin[f]<<endl;
                   IndiemtbLop(FirstLTC,ds,dsmh); 
                }
                else if(f==11){
                   clrscr();
                   gotoxy(10, 10);
                   cout << "Ban da chon: " << features_admin[f]<<endl;
                   InbangdiemtongketLop(FirstLTC,ds,dsmh); 
                }
            }
        } // end admin
    } // end while main

    // Giai phong bo nho truoc khi thoat
    ClearLTC(FirstLTC);
    ClearDS_Lop(ds);
    ClearStackLTC(rootLTC);
    ClearTree(dsmh);
    ClearStackMH(undostackMH);
    clrscr();
    gotoxy(10, 10);
    cout << "Tam biet!\n";
    return 0;
}
//g++ main.cpp MonHoc.cpp LopSinhVien.cpp console.cpp CTDL.cpp menu.cpp -o main