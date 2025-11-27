#include <iostream>
#include <termios.h>
#include <unistd.h>
#include <cstdio>
#include <cstring>
#include "console.h"
#include "MonHoc.h"
#include "LopSinhVien.h"
#include "CTDL.h"
#include<limits>
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
    DS_LOPSV ds;
    ds.n=0;
    for(int i=0;i<MAX_LOPSV;i++) ds.nodes[i] = nullptr;
    PTRLTC FirstLTC=nullptr;
    stackNode* rootLTC=nullptr;
    loadLopTinChi(FirstLTC, "LopTinChi.txt","DSSVDK.txt");
    loadLopSV(ds, "LopSinhVien.txt", "SinhVien.txt");
    const char *roles[] = {"Sinh vien", "Giang vien", "Admin", "Thoat"};
    const char *features_sinhvien[] = {
        "Xem danh sach mon hoc",
        "Dang ki/Huy dang ki lop tin chi",
        "Xem danh sach lop tin chi da dang ky",
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
        "Xem danh sach sinh vien da dang ki lop tin chi",
        "Xem bang diem cua lop tin chi",
        "Them/cap nhat/huy lop sinh vien",
        "Them sinh vien vao 1 lop",
        "Xem danh sach sinh vien",
        "Xem bang diem trung binh",
        "Xem bang diem tong ket",
        "← Quay lai"
    };
    //function them/xoa/sua LTC
    const char *features_admin_4[] = {
        "Them moi Lop Tin Chi",
        "Cap nhat xoa sua Lop Tin Chi",
        "Hieu chinh Lop Tin Chi",
        "← Quay lai"
    };
    int n_features_admin_4=4;// num of func 6
    //function xem danh sach sinh 
    const char *features_admin_9[] ={
        "Xem danh sach sinh vien(dua vao ma lop) theo thu tu alphabet theo ten",
        "xem danh sach ....",
        "← Quay lai"
    };
    int n_features_admin_9=3;

    const char *featuresdangkyhuy[]={
          "Dang ky LTC",
           "Huy LTC",
            "← Quay lai"
    };
    int n_featuresdangkyhuy=3;

    int n_roles = 4, n_features_sinhvien = 6,n_features_giangvien=9,n_features_admin=13;

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
            // cout << "Ban da chon: " << features_sinhvien[f];
            // gotoxy(10, 12);
            // cout << "(Nhan phim bat ky de quay lai...)";
            // getch();
            if(f==0){
              while(1){
                int g= menu("SINH VIEN DANG KY HUY LOP TIN CHI", role, featuresdangkyhuy, n_featuresdangkyhuy);
                if(g==n_featuresdangkyhuy-1) break;
                if(g==0){
                   clrscr();
                   
                }
                if(g==1){

                }
              }
            }
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
            if(f==4){
              while(1){
                int n = menu("=======THEM/XOA/SUA LOP TIN CHI=======","",features_admin_4,n_features_admin_4);
                if(n==n_features_admin_4-1)break;
                if(n==0){
                    clrscr();
                    LopTinChi ltc = NhapLTC();
                    ltc.MALOPTC = getNextMaLopTinChi(FirstLTC);

                    insertLopTinChi(FirstLTC, ltc);
                    saveLopTinChi(FirstLTC, "LopTinChi.txt","DSSVDK.txt");

                    cout << "\n>>> Da them lop tin chi thanh cong! MA MOI: "<< ltc.MALOPTC;
                    ActionLTC act;
                    act.type=1;
                    act.ltc=ltc;
                    push(rootLTC,act);
                    cout << "\nNhan phim bat ky de quay lai...";
                    getch();
                }
                if(n==1){
                    clrscr();
                   cout << "=== SUA LOP TIN CHI ===\n";

                   int malop;
                   cin.clear();
                   cin.ignore(numeric_limits<streamsize>::max(), '\n');
                   cout << "Nhap Ma Lop TC muon sua: ";
                   cin >> malop;
                   //check
                   cin.ignore(numeric_limits<streamsize>::max(), '\n');

                PTRLTC tmp = searchLopTinChi(FirstLTC, malop);
                if(tmp == nullptr){
                   cout << "Khong tim thay Lop Tin Chi\n";
                   getch();
                   clrscr();
                   continue;
                }

               LopTinChi oldLTC = tmp->ltc;

                if(editLopTinChi(FirstLTC, malop)){
                saveLopTinChi(FirstLTC, "LopTinChi.txt","DSSVDK.txt");
                cout << "\n>>> Sua thong tin lop tin chi thanh cong!";

    
                ActionLTC act;
                act.type = 3;
                act.ltc = oldLTC;   
                push(rootLTC, act);
                }
               else {
               cout << "\n>>> Khong tim thay lop tin chi!";
            }

               cout << "\nNhan phim bat ky de quay lai...";
               getch();
                }
                if(n==2){
                    clrscr();
                    gotoxy(10, 10);
                    cout << "Ban da chon: " << features_admin_4[n];
                    undoLTC(FirstLTC,rootLTC);
                    saveLopTinChi(FirstLTC, "LopTinChi.txt","DSSVDK.txt");
                    gotoxy(10, 12);
                    cout << "(Nhan phim bat ky de quay lai...)";
                    getch();
                }
            }
            }
            if(f==5){
                clrscr();
                cout << "=== DANH SACH SINH VIEN DA DANG KY LOP TIN CHI ===\n";
                PTRLTC pLTC = findLTCByParams(FirstLTC);
                if(pLTC){
                showDanhSachSinhVienDangKy(pLTC->ltc.dssvdk);
                } else {
                 cout << "Khong tim thay lop tin chi voi cac tham so da nhap.\n";
                }
                cout << "\nNhan phim bat ky de quay lai...";
                getch();
}
            
            if(f==6){
                clrscr();
            gotoxy(10, 10);
            cout << "Ban da chon: " << features_admin[f];
            gotoxy(10, 12);
            cout << "(Nhan phim bat ky de quay lai...)";
            getch();
            }
            if(f==7){
           
            }
            if(f==8){
                clrscr();
                gotoxy(10, 10);
                cout << "=== NHAP SINH VIEN VAO LOP ===\n";

                char malop[16];
                cout << "Nhap Ma Lop: ";
                cin.getline(malop, 16);

                LopSV* lop = searchLopSV(ds, malop);
                if(!lop){
                cout << "Khong tim thay lop!\n";
               getch();
               continue;
                }

    
               cout << "Ten lop: " << lop->TENLOP << endl;
               SinhVien sv;
               while(true){
                    cout << "\nNhap ma SV (Enter de dung): ";
                    cin.getline(sv.MASV, 16);
                    if(sv.MASV[0] == '\0') break;

                      cout << "Nhap ho: "; cin.getline(sv.HO, 51);
                      cout << "Nhap ten: "; cin.getline(sv.TEN, 11);
                      cout << "Nhap phai: "; cin.getline(sv.PHAI, 4);
                      cout << "Nhap so dien thoai: "; cin.getline(sv.SODT, 16);
                      cout << "Nhap email: "; cin.getline(sv.Email, 50);

                      insertSinhVien(lop->FirstSV, sv);
                    }

    
            saveLopSV(ds, "LopSV.txt", "SinhVien.txt");

            cout << "\n>>> Da cap nhat danh sach sinh vien vao lop!\n";
            cout << "(Nhan phim bat ky de quay lai...)";
            getch();
             
            }
            if(f==9){
               while(1){
                int n = menu("======= XEM DANH SACH SINH VIEN =======","",features_admin_9,n_features_admin_9);
                if(n==n_features_admin_9-1)break;
                if(n==0){
                  
                 clrscr();
                 cout << "=== XEM DANH SACH SINH VIEN THEO ALPHABET ===\n";

                 char malop[20];
                 cout << "Nhap Ma Lop: ";
                 cin >> malop;
                 cin.ignore();

                 LopSV *lop = searchLopSV(ds, malop);
                 if(!lop){
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
                if(n==1){
                   
                }
            }
            }
        }}
    }
    // don dep LTC,SV truoc khi thoat ra ngoai

    ClearLTC(FirstLTC);
    ClearDS_Lop(ds);
    clrscr();
    gotoxy(10, 10);
    cout << "Tam biet!\n";
    return 0;
}
