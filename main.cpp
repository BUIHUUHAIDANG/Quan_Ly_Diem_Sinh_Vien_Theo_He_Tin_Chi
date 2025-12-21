#include <iostream>
#include <conio.h>      
#include <windows.h>    
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
// === Draw Menu ===
int main() {
    PTRLTC FirstLTC = nullptr;
    PTRSV FirstSV = nullptr;
    DS_LOPSV dslop;
    treeMH dsmh; 
    SetConsoleOutputCP(CP_UTF8);
    const char *roles[] = {"Sinh vien", "Giang vien", "Admin", "Thoat"};
    const char *features_sinhvien[] = {
        "Xem danh sach mon hoc", // 0
        "Dang ki/Huy dang ki lop tin chi", // 1
        "Xem danh sach lop tin chi", // 2
        "Xem diem trung binh", // m + // 3
        "Xem diem tong ket", // m + // 4
        "← Quay lai"
    };
    const char *features_giangVien[] = {
        "Xem danh sach mon hoc", // 0
        "Xem danh sach sinh vien", // 1
        "Xem danh sach lop tin chi", // 2
        "Xem danh sach sinh vien da dang ki lop tin chi phu trach", // 3 
        "Nhap diem/ Sua diem cua sinh vien", // m + // 4
        "Xem bang diem cua mot lop tin chi", // m // 5
        "Xem bang diem trung binh", // m + // 6
        "Xem bang diem tong ket", // m + // 7
        "← Quay lai"
    };
    const char *features_admin[] = {
        "Xem danh sach mon hoc", // 0
        "Xem danh sach lop tin chi", // 1
        "Xem danh sach lop sinh vien", // 2
        "Them/cap nhat/xoa mon hoc", // 3
        "Them/cap nhat/huy lop tin chi", // 4
        "Xem danh sach sinh vien da dang ki lop tin chi", // 5
        "Xem bang diem cua lop tin chi", // m // 6
        "Them/cap nhat/huy lop sinh vien", // 7
        "Them/cap nhat/xoa sinh vien", // 8
        "Xem danh sach sinh vien", // 9
        "Xem bang diem trung binh", // m + // 10
        "Xem bang diem tong ket", // m + // 11
        "← Quay lai"
    };
    const char *featuresthemcapnhatxoa[] = {"Them", "Cap nhat", "Xoa", "← Quay lai"};
    const char *featuresthemcapnhathuy[] = {"Them", "Cap nhat", "Huy", "← Quay lai"};
    const char *featuresdangkyhuy[] = {"Dang ky LTC", "Huy LTC", "← Quay lai"};

    int n_roles = sizeof(roles) / sizeof(roles[0]);
    int n_features_sinhvien = sizeof(features_sinhvien) / sizeof(features_sinhvien[0]);
    int n_features_giangvien = sizeof(features_giangVien) / sizeof(features_giangVien[0]);
    int n_features_admin = sizeof(features_admin) / sizeof(features_admin[0]);
    int n_featuresthemcapnhatxoa = sizeof(featuresthemcapnhatxoa) / sizeof(featuresthemcapnhatxoa[0]);
    int n_featuresthemcapnhathuy = sizeof(featuresthemcapnhathuy) / sizeof(featuresthemcapnhathuy[0]);
    int n_featuresdangkyhuy = sizeof(featuresdangkyhuy) / sizeof(featuresdangkyhuy[0]);

    while (1) {
        int r = menu("CHON VAI TRO DANG NHAP", "", roles, n_roles);
        if (r == 3) break;

        const char *role = roles[r];
        if (r == 0) { // SINH VIEN
            while (1) {
                int f = menu("🏫 QUAN LY HE TIN CHI 🏫", role, features_sinhvien, n_features_sinhvien);
                if (f == n_features_sinhvien - 1) break;

                clrscr();
                gotoxy(10, 10);
                //cout << "Ban da chon: " << features_sinhvien[f];
                switch(f) {
                    case 1: { // Sinh vien dang ky/huy LTC
                        int g = menu("SINH VIEN DANG KY HUY LOP TIN CHI", role, featuresdangkyhuy, n_featuresdangkyhuy);
                        switch(g) {
                            case 0: {// Dang ki
                                LoadFile_LopSV("LopSinhVien.txt",dslop);
                                LoadFile_LTC("LopTinChi.txt",FirstLTC);
                                dangkyLTC(FirstLTC,dslop);
                                SaveFile_LTC("LopTinChi.txt",FirstLTC);
                                break;
                            }
                            case 1: {// Huy
                                break;
                            }
                            default:
                            break;
                        }
                        break;
                    }
                    case 2:{ // Xem danh sach ltc
                        LoadFile_LTC("LopTinChi.txt",FirstLTC);
                        InDSLTC(FirstLTC);
                        cout << "\n(Nhan phim bat ky de quay lai...)";
                        _getch();
                        break;
                    }

                    case 3: { // In diem tb ca nhan sinh vien
                        LoadFile_LopSV("LopSinhVien.txt", dslop);
                        LoadFile_LTC("LopTinChi.txt",FirstLTC);
                        DocMonHoc("MonHocdata.txt", dsmh);
                        IndiemtbSinhvien(FirstLTC, dslop, dsmh);
                        cout << "\n(Nhan phim bat ky de quay lai...)";
                        _getch();
                        break;
                    }
                    case 4: {
                        LoadFile_LTC("LopTinChi.txt",FirstLTC);
                        LoadFile_LopSV("LopSinhVien.txt", dslop);
                        DocMonHoc("MonHocdata.txt", dsmh);
                        InbangdiemtongketSinhvien(FirstLTC, dslop, dsmh);
                        cout << "\n(Nhan phim bat ky de quay lai...)";
                        _getch();
                        break;
                    }
                    default:
                    break;
                }   
                //gotoxy(10, 12);
                //cout << "(Nhan phim bat ky de quay lai...)";
                //_getch();
            }
        } else if (r == 1) { // GIANG VIEN
            while (1) {
                int f = menu("🏫 QUAN LY HE TIN CHI 🏫", role, features_giangVien, n_features_giangvien);
                if (f == n_features_giangvien - 1) break;

                clrscr();
                gotoxy(10, 10);
                //cout << "Ban da chon: " << features_giangVien[f];
                switch(f) {
                    
                    case 4: { // Nhap diem
                        LoadFile_LopSV("LopSinhVien.txt", dslop);
                        LoadFile_LTC("LopTinChi.txt", FirstLTC);
                        NhapDiem(FirstLTC, dslop);
                        SaveFile_LTC("LopTinChi.txt", FirstLTC);
                        break;
                    }
                    break;
                    case 5:{ // In bang diem cua ltc
                        LoadFile_LopSV("LopSinhVien.txt", dslop);
                        LoadFile_LTC("LopTinChi.txt", FirstLTC);
                        InbangDiemLTC(FirstLTC, dslop);
                        break;
                    }
                    case 6:{
                        LoadFile_LopSV("LopSinhVien.txt", dslop);
                        LoadFile_LTC("LopTinChi.txt",FirstLTC);
                        DocMonHoc("MonHocdata.txt", dsmh);
                        IndiemtbLop(FirstLTC, dslop, dsmh);
                        break;
                    }
                    
                    case 7: {
                        LoadFile_LopSV("LopSinhVien.txt", dslop);
                        LoadFile_LTC("LopTinChi.txt",FirstLTC);
                        DocMonHoc("MonHocdata.txt", dsmh);
                        InbangdiemtongketLop(FirstLTC, dslop, dsmh);
                        cout << "\n(Nhan phim bat ky de quay lai...)";
                        _getch();
                        break;
                    }
                    default:
                    break;
                }   
            }
        } else if (r == 2) { // ADMIN
            while (1) {
                int f = menu("🏫 QUAN LY HE TIN CHI 🏫", role, features_admin, n_features_admin);
                   
                if (f == n_features_admin - 1) {
                     
                    break;
                }
                    

                clrscr();
                gotoxy(10, 10);
                //cout << "Ban da chon: " << features_admin[f] << "\n";
                switch(f) {
                    case 0:{ // Xem danh sach mon hoc
                        DocMonHoc("MonHocdata.txt", dsmh);
                        InDSMH(dsmh);
                       cout << "\n(Nhan phim bat ky de quay lai...)";
                        _getch();
                        //return 0;
                        break;
                    }
                    case 1: { // Xem danh sach LTC
                        LoadFile_LTC("LopTinChi.txt",FirstLTC);
                        InDSLTC(FirstLTC);
                        cout << "\n(Nhan phim bat ky de quay lai...)";
                        _getch();
                        break;
                    }
                    case 2: { // Xem danh sach lopsv
                        LoadFile_LopSV("LopSinhVien.txt",dslop);
                        InDSLSV(dslop);
                        cout << "\n(Nhan phim bat ky de quay lai...)";
                        _getch();
                        break;
                    }
                    case 3: { // Them/cap nhat/xoa mon hoc
                        int g = menu("   QUAN LY MON HOC",role, featuresthemcapnhatxoa, n_featuresthemcapnhatxoa);
                        switch(g) {
                            case 0: { // them
                                NhapMonHoc(dsmh);
                                LuuMonHoc(dsmh, "MonHocdata.txt");
                                break;
                            }
                            case 1: 
                            break;
                            case 2:
                            break;
                        }
                        break;
                    }
                    case 4: { // Them/cap nhat/huy lop tin chi
                        int g = menu("  QUAN LY LOP TIN CHI",role, featuresthemcapnhathuy, n_featuresthemcapnhathuy);
                        switch(g) {
                            case 0: { // them
                                NhapLTC(FirstLTC);
                                SaveFile_LTC("LopTinChi.txt",FirstLTC);
                                break;
                            }
                            case 1: 
                            break;
                            case 2: 
                            break;
                        }
                        break;
                    }
                    case 5: { // Xem sinh vien da dang ki lop tin chi
                        int maloptc;
                        cout << "\nNhap ma lop tin chi: "; 
                        cin >> maloptc;
                        cin.ignore();
                        LoadFile_LTC("LopTinChi.txt",FirstLTC);
                        LoadFile_LopSV("LopSinhVien.txt",dslop);
                        InDSSVDK(FirstLTC,maloptc,dslop);
                        cout << "\n(Nhan phim bat ky de quay lai...)";
                        _getch();
                        break;
                    }
                    case 6:
                        //InbangDiemLTC(nodeLTC* dsltc, DS_LOPSV dslop);
                        break;
                    case 7: { //Them/cap nhat/huy lop sinh vien
                        int g = menu("  QUAN LY LOP SINH VIEN",role, featuresthemcapnhathuy, n_featuresthemcapnhathuy);
                        switch(g) {
                            case 0: { // them
                                NhapLopSV(dslop);
                                SaveFile_LopSV("LopSinhVien.txt",dslop);
                                break;
                            }
                            case 1: 
                            break;
                            case 2: 
                            break;
                            
                        }
                        break;
                    }
                    case 8: {// Them/edit/xoa sinh vien
                        int g = menu("   QUAN LI SINH VIEN",role, featuresthemcapnhatxoa, n_featuresthemcapnhatxoa);
                        switch(g) {
                            case 0: { // them
                                NhapSV(dslop);
                                SaveFile_LopSV("LopSinhVien.txt",dslop);
                                break;
                            }
                            case 1: 
                            break;
                            case 2: 
                            break;
                            
                        }
                        break;
                    }
                    case 9: { // Xem danh sach sinh vien
                        char malop[16];
                        cout << "\nNhap ma lop: "; 
                        cin.getline(malop,16); 
                        
                        LoadFile_LopSV("LopSinhVien.txt",dslop);
                        InDSSV(dslop,malop);
                        cout << "\n(Nhan phim bat ky de quay lai...)";
                        _getch();
                        break;
                    }
                    case 10:
                        //IndiemtbLop(PTRLTC dsltc, DS_LOPSV dslop, treeMH dsmh);
                    break;
                    case 11:
                        //InbangdiemtongketLop(PTRLTC dsltc, DS_LOPSV dslop, treeMH dsmh);
                    break;
                    default:
                    break;
                    
                }   
            }
        }
    }

    clrscr();
    gotoxy(10, 10);
    cout << "Tam biet!\n";
    return 0;
}

// g++ main.cpp menu.cpp CTDL.cpp LopSinhVien.cpp MonHoc.cpp -o main.exe


