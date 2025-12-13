#include <iostream>
#include <conio.h>      
#include <windows.h>    
#include <cstdio>
#include <cstring>
#include <limits>
#include <iomanip>
#include "mylib.h"
#include "menu.h"
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
const int linenum = 5; 
void drawBangDiem(PTRDK arr[], int count, int highlight, DS_LOPSV &dslop, int index) {
    
    SetColor(14);
    SetBold(true);
    cout << "\n              -==== BANG DIEM LOP TIN CHI ====- \n";
    cout << left << setw(5) << "STT" << setw(15) << "MASV" << setw(25) << "HO"<<
    setw(15) << "TEN" << setw(10) << "DIEM" << endl;
    SetBold(false);
    SetColor(2);
    cout << "------------------------------------------------------------------------\n";
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
void BangDiem_Interact(PTRDK arr[], int count, DS_LOPSV &dslop) {
    clrscr();
    int highlight = 0;
    int index = 0;
   

    draw: drawBangDiem(arr, count, highlight, dslop,index);

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
            
            DrawBox(0, 17, 50, 3, 5);
            gotoxy(2, 18);
            cout << "Nhap diem moi cho SV " << arr[highlight]->dk.MASV << " (-1 de bo qua): ";
            if (!(cin >> diem)) {
                cin.clear(); cin.ignore(9999, '\n');
                ClearBox(0, 17, 50, 3);
                continue;
            }
            if (diem >= 0 && diem <= 10)  {arr[highlight]->dk.DIEM = diem;  ClearBox(0, 17, 50, 3); }
            else {
                gotoxy(7,22);
                SetColor(4);
                cout << "- Diem khong hop le! -";
                ResetColor();
                _getch(); 
                gotoxy(7,22); cout << string(30, ' ');
                ClearBox(0, 17, 50, 3);
                continue;
            }
            if (diem == -1) {
                ClearBox(0, 29, 60, 3); 
                continue;
            }
            ClearBox(0, 29, 60, 3);

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
        int currentPage = index / linenum + 1;
        int totalPage   = (count + linenum - 1) / linenum;
        gotoxy(15, 15);
        SetBold(true);
        SetColor(9);
        cout << " Trang " << currentPage << "/" << totalPage << "   " << "  ESC de thoat.";
        SetBold(false);
        ResetColor();

        
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


