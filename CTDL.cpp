#include "CTDL.h"

// =================== CONSTRUCTORS ===================

// nodeSV
nodeSV::nodeSV() {
    next = nullptr;
}

// LopSV
LopSV::LopSV() {
    FirstSV = nullptr;
    MALOP[0] = 0;
    TENLOP[0] = 0;
}

// DS_LOPSV
DS_LOPSV::DS_LOPSV() {
    n = 0;
    for (int i = 0; i < MAX_LOPSV; i++) {
        nodes[i] = nullptr;
    }
}

// nodeDK
nodeDK::nodeDK() {
    next = nullptr;
}

// LopTinChi
LopTinChi::LopTinChi() {
    MALOPTC = 0;
    MAMH[0] = 0;
    NienKhoa[0] = 0;
    Hocky = 0;
    Nhom = 0;
    sosvmin = 0;
    sosvmax = 0;
    huylop = false;
    dssvdk = nullptr;
}

// nodeLTC
nodeLTC::nodeLTC() {
    next = nullptr;
}

nodeLTC::nodeLTC(LopTinChi data) {
    this->ltc = data;
    this->next = nullptr;
}

// =================== UTILITY FUNCTIONS ===================

// Initialize pointer to list of LopTinChi
/*void initializeLTC(PTRLTC &First) {
    First = nullptr;
}

// Create a new nodeLTC with given LopTinChi data
PTRLTC createNodeLopTinChi(LopTinChi data) {
    return new nodeLTC(data);
}*/
