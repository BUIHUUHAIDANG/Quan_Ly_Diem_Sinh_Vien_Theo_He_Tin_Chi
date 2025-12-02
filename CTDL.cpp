#include "LopSinhVien.h"
#include <cstring>
#include <iostream>
#include <algorithm>
#include <fstream>      
#include <sstream>      
#include <string>      
using namespace std;


nodeSV::nodeSV() { next = nullptr; }
LopSV::LopSV() { FirstSV = nullptr; MALOP[0]=0; TENLOP[0]=0; }
DS_LOPSV::DS_LOPSV() { n = 0; for(int i=0;i<MAX_LOPSV;i++) nodes[i]=nullptr; }
nodeDK::nodeDK() { next = nullptr; }
LopTinChi::LopTinChi() {
    MALOPTC = 0; MAMH[0]=0; NienKhoa[0]=0;
    Hocky = 0; Nhom = 0; sosvmin = 0; sosvmax = 0;
    huylop = false; dssvdk = nullptr;
}
nodeLTC::nodeLTC() { next = nullptr; }
nodeLTC::nodeLTC(LopTinChi data) { this->ltc = data; this->next = nullptr; }