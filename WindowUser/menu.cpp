#include <iostream>
#include <conio.h>      
#include <windows.h>    
#include <cstdio>
#include <cstring>
#include <limits>
#include <iomanip>
#include "mylib.h"
#include "menu.h"
#include "LopSinhVien.h"
#include "CTDL.h"
using namespace std;

void drawStaticMenu(const char *title, const char *role, int n)  {
    clrscr();
    SetBGColor(0);
    SetColor(7);
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
    gotoxy(5, 6 + n * 2);
    cout << "(Dung phim ↑ ↓ hoac W/S de di chuyen, Enter de chon)";
}
void drawOptions(const char *options[], int n, int highlight) {
    for (int i = 0; i < n; i++) {
        gotoxy(8, 6 + i * 2);
        cout << string(200, ' ');
        gotoxy(8, 6 + i * 2);
        if (i == highlight) {
            SetBGColor(7); SetColor(0);
            cout << "> " << options[i] << " <";
        } else {
            ResetColor();
            cout << "  " << options[i] << "  ";
        }
        ResetColor();
    }
}


// === menu logic ===
int menu(const char *title, const char *role, const char *options[], int n)  {
    int highlight = 0;
    drawStaticMenu(title, role, n);
    while (true) {
        drawOptions(options, n, highlight);
        int ch = _getch();
        // support both arrow keys and WASD
        if (ch == 224) {
            int arrow = _getch();
            if (arrow == 72) highlight = (highlight - 1 + n) % n; // up
            if (arrow == 80) highlight = (highlight + 1) % n;     // down
        }
        else if (ch == 'w' || ch == 'W') highlight = (highlight - 1 + n) % n;
        else if (ch == 's' || ch == 'S') highlight = (highlight + 1) % n;
        else if (ch == 13) return highlight; // Enter
    }
}

// == Diem ==

int Popup_ChonHanhDong() { // pop up sua diem
    const char* options[2] = { "Sua diem", "Quay lai" };
    int highlight = 0;
    int x = 85;  
    int y = 6;
    DrawBox(83,5,16,5,3);
    while (true) {
        //  popup
        for (int i = 0; i < 2; i++) {
            gotoxy(x, y + i * 2);
            if (i == highlight) {
                SetBGColor(7); SetColor(0);
                cout << "> " << options[i] << " <";
            } else {
                ResetColor();
                cout << "  " << options[i] << "  ";
            }
            ResetColor();
        }
        int ch = _getch();
        if (ch == 224) {
            int arrow = _getch();
            if (arrow == 72) highlight = (highlight - 1 + 2) % 2; // up
            if (arrow == 80) highlight = (highlight + 1) % 2;     // down
        }
        else if (ch == 'w' || ch == 'W') highlight = (highlight - 1 + 2) % 2;
        else if (ch == 's' || ch == 'S') highlight = (highlight + 1) % 2;
        else if (ch == 13) {
            // xoa popup
            //for (int i = 0; i < 2; i++) {
                //gotoxy(x, y + i * 2);
                //cout << string(20, ' ');
            //}
           ClearBox(83,5,16,5);
            return highlight;   // 0 = sua diem, 1 = quay lai
        }
    }
    
}
//                                              |PAGING SYSTEM|
// o=================================================================================================================o
//  - arr[] la mang luu con tro sinh vien, duoc tao tu danh sach lien ket de ho tro 
//  truy cap theo chi so va phan trang O(1)
//  - arr[index] la phan tu dau tien cua trang, arr[index + linenum - 1] la phan tu cuoi trang                                                       
//  - linenum la so phan tu trong mot trang (VD: linenum = 5 thi show 5 sinh vien moi trang)
//  - Qua trang sau index += linenum, quay ve trang truoc index -= linenum
// o=================================================================================================================o

const int linenum = 5; // LINE NUMBER

// DRAW
void drawBangDiem(PTRDK arr[], int count, int highlight, DS_LOPSV &dslop, int index) {
    
    SetColor(14);
    SetBold(true);
    cout << "\n              -==== BANG DIEM LOP TIN CHI ====- \n";
    SetBold(false);
    SetColor(2);
    cout << left << setw(5) << "STT" << setw(15) << "MASV" << setw(25) << "HO"<<
    setw(15) << "TEN" << setw(10) << "DIEM" << endl;
    
    cout << "----------------------------------------------------------------------------------\n";
    ResetColor();
    int endindex = min(index + linenum, count);
    for(int i=index; i<endindex; i++) {
        if(i == highlight) SetColor(14); else SetColor(7);
        SinhVien *sv = nullptr;
        for(int j = 0; j<dslop.n && !sv; j++) {
            PTRSV q = dslop.nodes[j]->FirstSV;
            while (q!= nullptr) {
                if(strcmp(q->sv.MASV, arr[i]->dk.MASV) == 0) {
                    sv =&q->sv;
                    break;
                }
                q = q->next;
            }
        }
        if(sv) {
            cout << left << setw(5) << (i+1) << setw(15) << sv->MASV<< setw(25) << sv->HO<< setw(15) << sv->TEN
            << setw(10) << fixed << setprecision(2) << arr[i]->dk.DIEM;cout << "\n";
        } else {
            cout << setw(5) << (i+1)<< setw(15) << arr[i]->dk.MASV<< setw(25) << "Khong tim thay"
            << setw(15) << ""<< setw(10) << "----" << endl;
        }
    }
    ResetColor();
}


void drawBangDiemTB(PTRSV arr[], int count, int index, PTRLTC &dsltc,DS_LOPSV &dslop,treeMH &dsmh, LopSV* lop) {
    SetColor(14);
    SetBold(true);
    cout << "\n                 -==== BANG DIEM TRUNG BINH KHOA HOC ====- \n";
    ResetColor();
    cout << "\nLop: ";
    SetColor(10);
    cout << lop->TENLOP << endl;
    SetBold(false);
    SetColor(2);
    cout << left << setw(5) << "STT" << setw(15) << "MASV"
         << setw(25) << "HO" << setw(15) << "TEN" << setw(10) << "DIEM TB" << endl;
    cout << "-------------------------------------------------------------------\n";
    ResetColor();
    int stt = index + 1;
    int endindex = min(index + linenum, count);
    for (int i = index; i < endindex; i++) {
        PTRSV sv = arr[i];
        float diemTB = Tinhdiemtb(sv->sv, dsltc, dsmh);
        cout << left << setw(5) << stt++ << setw(15) << sv->sv.MASV << setw(25) << sv->sv.HO 
            << setw(15) << sv->sv.TEN;
        if (diemTB >= 0) {
            cout << setw(10) << fixed << setprecision(2) << diemTB << endl;
        } else {
            cout <<  setw(10) << "Chua co" << endl;
        }
    }
}

void drawBangDiemTK(PTRSV arr[], int count, int index, PTRLTC &dsltc,DS_LOPSV &dslop,treeMH &dsmh, LopSV* lop, char dsMAMH[200][11], int soMH) {
    SetBold(true);          
    SetColor(14);
    cout << "               -==== BANG DIEM TONG KET ====- ";
    cout << "\nLop: ";
    SetColor(10);
    cout << lop->TENLOP << endl;
    ResetColor();
    SetBold(false);
    cout << left << setw(5) << "STT" << setw(15) << "MASV" << setw(25) << "HO TEN";
    for (int i = 0; i < soMH; i++) cout << setw(8) << dsMAMH[i];
    cout << endl;
 
    int stt = index + 1;
    for (int i = index; i < index + linenum && i < count; i++) {
        PTRSV sv = arr[i];
        float diemMax[200];
        for (int i = 0; i < soMH; i++) diemMax[i] = -1;

        for (PTRLTC cur = dsltc; cur != nullptr; cur = cur->next) {
            if (cur->ltc.huylop) continue;

            for (PTRDK dk = cur->ltc.dssvdk; dk != nullptr; dk = dk->next) {
                if (strcmp(dk->dk.MASV, sv->sv.MASV) == 0) {
                    for (int i = 0; i < soMH; i++) {
                        if (strcmp(dsMAMH[i], cur->ltc.MAMH) == 0) {
                            if (dk->dk.DIEM > diemMax[i]) diemMax[i] = dk->dk.DIEM;
                            break;
                        }
                    }
                }
            }
        }
        char hoten[51];
        strcpy(hoten, sv->sv.HO);
        strcat(hoten, " ");
        strcat(hoten, sv->sv.TEN);
        cout << left << setw(5) << stt++ << setw(15) << sv->sv.MASV << setw(25) << hoten;
        for(int i=0; i< soMH; i++) {
            if(diemMax[i] >= 0) {
                cout << setw(8) << fixed << setprecision(2) << diemMax[i];
            } else {
                cout << setw(8) << "-";
            }
            
        }
        cout << endl;
    }
}

// PAGE INTERACTION

//                                        |BANG DIEM INTERACTION SYSTEM|
// o=================================================================================================================o
//                                     [Page system da duoc comment o tren]
//  - Highlight la dong dang duoc chon (con tro SV) va chi duoc di chuyen trong trang hien tai
//  - Chuyen highlight ve vi tri tuong doi trong trang r = highlight−index
//  - Di chuyen len xuong trong khoang [0, pageSize - 1]                                                  
//  - Truong hop di len nhung dang highlight o phan tu dau: 
//    highlight = index + (highlight - 1 - index + pageSize) % pageSize; , se xuong cuoi trang
//  - Truong hop di xuong nhung dang highlight o phan tu cuoi: 
//    highlight = index + (highlight + 1 - index) % pageSize;, se len dau trang
// o=================================================================================================================o

void BangDiem_Interact(PTRDK arr[], int count, DS_LOPSV &dslop) {
    clrscr();
    int highlight = 0;
    int index = 0;
   
    draw: drawBangDiem(arr, count, highlight, dslop,index);
    // trang
    int currentPage = index / linenum + 1;
    int totalPage   = (count + linenum - 1) / linenum;
    gotoxy(3, 30);
    cout << "(Dung phim ↑ ↓ hoac W/S de di chuyen, → ← hoac A/D de chuyen trang,  Enter de chon)";
    gotoxy(20, 31);
    SetBold(true);
    SetColor(9);
    cout << " Trang " << currentPage << "/" << totalPage << "   " << "  ESC de thoat.";
    SetBold(false);
    ResetColor();

    while (true) { 
        int ch = _getch();
        int oldHighlight = highlight;
        int pageSize  = min(linenum, count - index);
        if (pageSize <= 0) continue;
        if (ch == 224) {
            int arrow = _getch();
            if (arrow == 72) highlight = index + (highlight- 1 - index  + pageSize) % pageSize;
            else if (arrow == 80) highlight = index + (highlight+ 1 - index ) % pageSize;

            else if(arrow == 75) {highlight = index; index = max(0,index-linenum);  clrscr();  goto draw;} // left 
            else if(arrow == 77) {if (index + linenum < count) { index += linenum; highlight = index; clrscr(); goto draw;}} // right
        }
        else if (ch == 'w' || ch == 'W') highlight = index + (highlight- 1 - index  + pageSize) % pageSize; // up
        else if (ch == 's' || ch == 'S') highlight = index + (highlight + 1- index ) % pageSize; // down

        else if(ch == 'a' || ch == 'A') {highlight = index; index = max(0,index-linenum);  clrscr();  goto draw;} // left
        else if(ch == 'd' || ch == 'D') {if (index + linenum < count) { index += linenum; highlight = index; clrscr(); goto draw;}} // right

        else if (ch == 13) {
            int choice = Popup_ChonHanhDong();
            if (choice == 1) {
                clrscr(); 
                goto draw;
            }

            float diem;
            
            DrawBox(0, 17, 60, 3, 5);
            gotoxy(2, 18);
            cout << "Nhap diem moi cho SV " << arr[highlight]->dk.MASV << " (-1 de bo qua): ";
            if (!(cin >> diem)) {
                cin.clear(); cin.ignore(9999, '\n');
                ClearBox(0, 17, 60, 3);
                continue;
            }
            if (diem >= 0 && diem <= 10)  {
                arr[highlight]->dk.DIEM = diem;  
                ClearBox(0, 17, 60, 3); 
            }
            else if (diem == -1) {
                ClearBox(0, 17, 50, 3); 
            }
            else {
                gotoxy(7,22);
                SetColor(4);
                cout << "- Diem khong hop le! -";
                ResetColor();
                ClearBox(0, 17, 60, 3); 
                _getch(); 
                gotoxy(7,22); string(35, ' '); 
            }
            
            //ClearBox(0, 29, 60, 3);

            SinhVien *sv = nullptr;
            for (int j = 0; j < dslop.n && !sv; j++) {
                PTRSV q = dslop.nodes[j]->FirstSV;
                while (q) {
                    if (strcmp(q->sv.MASV, arr[highlight]->dk.MASV) == 0) {
                        sv = &q->sv;
                        break;
                    }
                    q = q->next;
                }
            }
            int y = 4 + (highlight-index);
            gotoxy(0, y);
            SetColor(14);
            if (sv) {
                cout << left << setw(5)  << (highlight + 1) << setw(15) << sv->MASV << setw(25) << sv->HO
                    << setw(15) << sv->TEN << setw(10) << fixed << setprecision(2) << arr[highlight]->dk.DIEM;
            }

            ResetColor();
            continue;
        }
        else if (ch == 27) return; // esc
        if (oldHighlight != highlight) {
            // in lai dong cu
            if (oldHighlight >= index && oldHighlight < index + pageSize) {
                int y = 4 + (oldHighlight - index);
                gotoxy(0, y);
                SetColor(7);

                SinhVien *sv = nullptr;
                for(int j = 0; j < dslop.n && !sv; j++) {
                    PTRSV q = dslop.nodes[j]->FirstSV;
                    while (q) {
                        if (strcmp(q->sv.MASV, arr[oldHighlight]->dk.MASV) == 0) {
                            sv = &q->sv; break;
                        }
                        q = q->next;
                    }
                }
                if (sv) {
                    cout << left << setw(5) << (oldHighlight+1) << setw(15) << sv->MASV << setw(25) << sv->HO << setw(15) << sv->TEN 
                    << setw(10) << fixed << setprecision(2) << arr[oldHighlight]->dk.DIEM;
                }
                ResetColor();
            }
            // in lai dong moi 
            if (highlight >= index && highlight < index + pageSize) {
                int y =4 + (highlight-index);
                gotoxy(0, y);
                SetColor(14);

                SinhVien *sv = nullptr;
                for(int j = 0; j < dslop.n && !sv; j++) {
                    PTRSV q = dslop.nodes[j]->FirstSV;
                    while (q) {
                        if (strcmp(q->sv.MASV, arr[highlight]->dk.MASV) == 0) {
                            sv = &q->sv; break;
                        }
                        q = q->next;
                    }
                }

                if (sv) {
                    cout << left << setw(5) << (highlight+1) << setw(15) << sv->MASV << setw(25) << sv->HO<< setw(15) << sv->TEN
                         << setw(10) << fixed << setprecision(2) << arr[highlight]->dk.DIEM;
                }
                ResetColor();
            }
        }
    }
}
void BangDiemLTC(PTRDK arr[], int count, DS_LOPSV &dslop) {
    clrscr();
    int index = 0;
    draw: drawBangDiem(arr, count, -1, dslop,index);
    int currentPage = index / linenum + 1;
    int totalPage   = (count + linenum - 1) / linenum;
    gotoxy(6, 30);
    cout << "(Dung phim → ← hoac A/D de chuyen trang)";
    gotoxy(20, 31);
    SetBold(true);
    SetColor(9);
    cout << " Trang " << currentPage << "/" << totalPage << "   " << "  ESC de thoat.";
    SetBold(false);
    ResetColor();
    while (true) { 
        int ch = _getch();
        int pageSize  = min(linenum, count - index);
        if (pageSize <= 0) continue;
        if (ch == 224) {
            int arrow = _getch();
            if(arrow == 75) { index = max(0,index-linenum);  clrscr();  goto draw;} // left 
            else if(arrow == 77) {if (index + linenum < count) { index += linenum; ; clrscr(); goto draw;}} // right
        }
        else if(ch == 'a' || ch == 'A') {; index = max(0,index-linenum);  clrscr();  goto draw;} // left
        else if(ch == 'd' || ch == 'D') {if (index + linenum < count) { index += linenum; ; clrscr(); goto draw;}} // right
        else if (ch == 27) return; // esc
    }
}
void BangDiemTB(PTRSV arr[], int count, PTRLTC &dsltc,DS_LOPSV &dslop,treeMH &dsmh, LopSV* lop) {
    int index = 0;
    clrscr();
    draw: drawBangDiemTB(arr, count, index, dsltc, dslop, dsmh, lop);
    int currentPage = index / linenum + 1;
    int totalPage   = (count + linenum - 1) / linenum;
    gotoxy(6, 30);
    cout << "(Dung phim  → ← hoac A/D de chuyen trang)";
    gotoxy(20, 31);
    SetBold(true);
    SetColor(9);
    cout << " Trang " << currentPage << "/" << totalPage << "   " << "  ESC de thoat.";
    SetBold(false);
    ResetColor();
    while (true) { 
        int ch = _getch();
        int pageSize  = min(linenum, count - index);
        if (pageSize <= 0) continue;
        if (ch == 224) {
            int arrow = _getch();
            if(arrow == 75) { index = max(0,index-linenum);  clrscr();  goto draw;} // left 
            else if(arrow == 77) {if (index + linenum < count) { index += linenum; ; clrscr(); goto draw;}} // right
        }
        else if(ch == 'a' || ch == 'A') {; index = max(0,index-linenum);  clrscr();  goto draw;} // left
        else if(ch == 'd' || ch == 'D') {if (index + linenum < count) { index += linenum; ; clrscr(); goto draw;}} // right
        else if (ch == 27) return; // esc
    }
}
void BangDiemTK(PTRSV arr[], int count, PTRLTC &dsltc,DS_LOPSV &dslop,treeMH &dsmh, LopSV* lop) {
    int index = 0;
    char dsMAMH[200][11];
    char malop[16];
    int soMH = 0;
    duyettreeMH(dsmh, dsMAMH, soMH);
    if (soMH == 0) {
        cout << "Danh sach mon hoc rong!\n";
        return;
    }

    clrscr();
    draw: drawBangDiemTK(arr,count,index,dsltc,dslop,dsmh,lop,dsMAMH,soMH);

    int currentPage = index / linenum + 1;
    int totalPage   = (count + linenum - 1) / linenum;
    gotoxy(6, 30);
    cout << "(Dung phim → ← hoac A/D de chuyen trang)";
    gotoxy(20, 31);
    SetBold(true);
    SetColor(9);
    cout << " Trang " << currentPage << "/" << totalPage << "   " << "  ESC de thoat.";
    SetBold(false);
    ResetColor();
    while (true) { 
        int ch = _getch();
        int pageSize  = min(linenum, count - index);
        if (pageSize <= 0) continue;
        if (ch == 224) {
            int arrow = _getch();
            if(arrow == 75) { index = max(0,index-linenum);  clrscr();  goto draw;} // left 
            else if(arrow == 77) {if (index + linenum < count) { index += linenum; ; clrscr(); goto draw;}} // right
        }
        else if(ch == 'a' || ch == 'A') {; index = max(0,index-linenum);  clrscr();  goto draw;} // left
        else if(ch == 'd' || ch == 'D') {if (index + linenum < count) { index += linenum; ; clrscr(); goto draw;}} // right
        else if (ch == 27) return; // esc
    }
}

