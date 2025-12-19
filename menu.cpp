#include <iostream>  
#include <cstdio>
#include <cstring>
#include <limits>
#include <iomanip>
#include "console.h"
#include "menu.h"
using namespace std;





// == Diem ==
int Popup_ChonHanhDong() { // pop up sua diem
    const char* options[2] = { "Sua diem", "Quay lai" };
    int highlight = 0;
    int x = 85;  
    int y = 6;
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
        int ch = getch();
        if (ch == 224) {
            int arrow = getch();
            if (arrow == 72) highlight = (highlight - 1 + 2) % 2; // up
            if (arrow == 80) highlight = (highlight + 1) % 2;     // down
        }
        else if (ch == 'w' || ch == 'W') highlight = (highlight - 1 + 2) % 2;
        else if (ch == 's' || ch == 'S') highlight = (highlight + 1) % 2;
        else if (ch == 13||ch == 10) {
            // xoa popup
            for (int i = 0; i < 2; i++) {
                gotoxy(x, y + i * 2);
                cout << string(20, ' ');
            }
            ResetColor();
            return highlight;   // 0 = sua diem, 1 = quay lai
        }
    }
}

void drawBangDiem(PTRDK arr[], int count, int highlight, DS_LOPSV &dslop) {
    cout << "\n              -==== BANG DIEM LOP TIN CHI ====- \n";
    cout << left << setw(5) << "STT" << setw(15) << "MASV" << setw(25) << "HO"<<
    setw(15) << "TEN" << setw(10) << "DIEM" << endl;
    cout << "--------------------------------------------------------------\n";
    for(int i=0; i<count; i++) {
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
    int highlight = 0;

    clrscr();
    draw: drawBangDiem(arr, count, highlight, dslop);

    while (true) {
        int ch = getch();
        int oldHighlight = highlight;
        if (ch == 224) {
            int arrow = getch();
            if (arrow == 72) highlight = (highlight - 1 + count) % count;
            else if (arrow == 80) highlight = (highlight + 1) % count;
        }
        else if (ch == 'w' || ch == 'W') highlight = (highlight - 1 + count) % count;
        else if (ch == 's' || ch == 'S') highlight = (highlight + 1) % count;
        else if (ch == 13||ch ==10) {
            int choice = Popup_ChonHanhDong();
            if (choice == 1) {clrscr(); goto draw;}

            float diem;
            gotoxy(0, 30);
            cout << "Nhap diem moi cho SV " << arr[highlight]->dk.MASV << " (-1 de bo qua): ";
            if (!(cin >> diem)) {
                cin.clear(); cin.ignore(9999, '\n');
                continue;
            }
            if (diem >= 0 && diem <= 10) {
                arr[highlight]->dk.DIEM = diem;
            }
            int rowY = 4  + highlight;  
            gotoxy(0, rowY);
            SetColor(14);
            cout << setw(5) << (highlight+1)
                 << setw(15) << arr[highlight]->dk.MASV
                 << setw(25) << "..."    
                 << setw(15) << "..."
                 << setw(10) << arr[highlight]->dk.DIEM;
            ResetColor();

            continue;
        }
        else if (ch == 27) return; // esc
        // in lai dong cu
        if (oldHighlight != highlight) {

            {
                int y = 4 + oldHighlight;
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
            {
                int y = 4 + highlight;
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