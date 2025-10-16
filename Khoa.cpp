#include<iostream>
#include<cstring>
#include<fstream>
#include<sstream>
using namespace std;

const int MAX_LOPSV = 10000;
const int MAX_LTC=10000;

struct MonHoc
{
    char MAMH[11];
    char TENMH[51];
    int STCLT;
    int STCTH;
};

struct nodeMH //tree
{
    MonHoc mh;
    nodeMH *left;
    nodeMH *right;
    int height;
};

typedef nodeMH* treeMH;

struct SinhVien //node
{
    char MASV[16];
    char HO[51];
    char TEN[11];
    char PHAI[4];
    char SODT[16];
    char Email[50];
};

struct nodeSV
{
    SinhVien sv;
    nodeSV *next;
};

typedef nodeSV* PTRSV;

struct LopSV
{
    char MALOP[16];
    char TENLOP[51];
    PTRSV FristSV=nullptr;
};

struct DS_LOPSV
{
    int n=0;
    LopSV* nodes[MAX_LOPSV];
};

struct DangKy
{
    char MASV[16];
    float DIEM;
    bool huydangky = false;
};

struct nodeDK
{
    DangKy dk;
    nodeDK *next;
};

typedef nodeDK* PTRDK;

struct LopTinChi
{
    int MALOPTC;
    char MAMH[11];
    char NienKhoa[10];
    int Hocky, Nhom, sosvmin, sosvmax;
    bool huylop =false;
    PTRDK dssvdk=nullptr;
};

struct nodeLTC 
{
    LopTinChi ltc;
    nodeLTC* next;
};

typedef nodeLTC* PTRLTC;

struct DS_LTC {
    int n = 0;
    LopTinChi* nodes[MAX_LTC];
};

int height(treeMH t) { 
    return t ? t->height : 0; 
}

int getBalance(treeMH t) { 
    return t ? height(t->left) - height(t->right) : 0; 
}

treeMH rotateRight(treeMH y) {
    treeMH x = y->left;
    treeMH T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

treeMH rotateLeft(treeMH x) {
    treeMH y = x->right;
    treeMH T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

// -------------------- CHÈN NODE (INSERT AVL) --------------------

treeMH Insert(treeMH t, MonHoc mh) {
    if (t == nullptr) {
        t = new nodeMH;
        t->mh = mh;
        t->left = t->right = nullptr;
        t->height = 1;
        return t;
    }

    if (strcmp(mh.MAMH, t->mh.MAMH) < 0)
        t->left = Insert(t->left, mh);
    else if (strcmp(mh.MAMH, t->mh.MAMH) > 0)
        t->right = Insert(t->right, mh);
    else
        return t; // Mã trùng thì bỏ qua

    // Cập nhật height
    t->height = 1 + max(height(t->left), height(t->right));

    // Cân bằng AVL
    int balance = getBalance(t);

    // Left Left
    if (balance > 1 && strcmp(mh.MAMH, t->left->mh.MAMH) < 0)
        return rotateRight(t);

    // Right Right
    if (balance < -1 && strcmp(mh.MAMH, t->right->mh.MAMH) > 0)
        return rotateLeft(t);

    // Left Right
    if (balance > 1 && strcmp(mh.MAMH, t->left->mh.MAMH) > 0) {
        t->left = rotateLeft(t->left);
        return rotateRight(t);
    }

    // Right Left
    if (balance < -1 && strcmp(mh.MAMH, t->right->mh.MAMH) < 0) {
        t->right = rotateRight(t->right);
        return rotateLeft(t);
    }

    return t;
}

// -------------------- LƯU / ĐỌC FILE --------------------

void LuuMonHoc(treeMH t, string filename) {
    ofstream f(filename);
    if (t == nullptr) {
        f << "#\n";
        return;
    }

    f << t->mh.MAMH << "|"
      << t->mh.TENMH << "|"
      << t->mh.STCLT << "|"
      << t->mh.STCTH << "|"
      << t->height << "\n";

    LuuMonHoc(t->left, filename);
    LuuMonHoc(t->right, filename);
    f.close();
}

treeMH DocMonHoc(string filename) {
    ifstream f(filename);
    if (!f.is_open()) {
        cout << "Khong mo duoc file!\n";
        return nullptr;
    }

    string line;
    treeMH root = nullptr;
    while (getline(f, line)) {
        if (line == "#" || line.empty()) continue;

        stringstream ss(line);
        MonHoc mh;
        string temp;

        getline(ss, temp, '|'); strcpy(mh.MAMH, temp.c_str());
        getline(ss, temp, '|'); strcpy(mh.TENMH, temp.c_str());
        getline(ss, temp, '|'); mh.STCLT = stoi(temp);
        getline(ss, temp, '|'); mh.STCTH = stoi(temp);

        root = Insert(root, mh);
    }

    f.close();
    return root;
}

// -------------------- HÀM KIỂM TRA MÃ MÔN --------------------

bool checkMH(treeMH t, MonHoc mh) {
    if (t == nullptr) return false;
    if (strcmp(mh.MAMH, t->mh.MAMH) == 0) return true;
    if (strcmp(mh.MAMH, t->mh.MAMH) < 0) return checkMH(t->left, mh);
    else return checkMH(t->right, mh);
}

// -------------------- NHẬP MÔN HỌC --------------------

void NhapMonHoc(treeMH &t) {
    t = DocMonHoc("D:\\MonHocdata.txt");

    while (true) {
        MonHoc mh;
        cout << "Nhap ma mon hoc (nhap 0 de thoat): ";
        cin >> mh.MAMH;
        if (strcmp(mh.MAMH, "0") == 0) break;

        if (checkMH(t, mh)) {
            cout << "Ma mon hoc da ton tai. Vui long nhap lai.\n";
            continue;
        }

        cout << "Nhap ten mon hoc: ";
        cin.ignore();
        cin.getline(mh.TENMH, 51);
        cout << "Nhap so tin chi ly thuyet: ";
        cin >> mh.STCLT;
        cout << "Nhap so tin chi thuc hanh: ";
        cin >> mh.STCTH;

        t = Insert(t, mh);

        LuuMonHoc(t, "D:\\MonHocdata.txt");

        cout << "Luu thanh cong!\n\n";
    }
}


void XoaMH (treeMH &t, MonHoc mh) {
    if (t == nullptr) {
        cout <<  "Khong tim thay mon hoc de xoa" << endl;
        return;
    }
    if (strcmp(mh.MAMH, t->mh.MAMH) < 0) {
        XoaMH(t->left, mh);
    } else if (strcmp (mh.MAMH, t->mh.MAMH) > 0) {
        XoaMH(t->right, mh);
    } else {
        treeMH temp = t;
        if (t->left == nullptr) {
            t = t->right;
        } else if (t->right == nullptr) {
            t = t->left;
        } 
        delete temp;
    }
}

void SuaMH (treeMH &t, MonHoc mh) {
    if (t == nullptr) {
        cout <<  "Khong tim thay mon hoc de sua" << endl;
        return;
    }
    if (strcmp(mh.MAMH, t->mh.MAMH) < 0) {
        SuaMH(t->left, mh);
    } else if (strcmp (mh.MAMH, t->mh.MAMH) > 0) {
        SuaMH(t->right, mh);
    } else {
        while (true) {
            cout << "Ban muon sua thong tin gi:" << endl;
            cout << "1. Ten mon hoc" << endl;
            cout << "2. So tin chi ly thuyet" << endl;
            cout << "3. So tin chi thuc hanh" << endl;
            cout << "4. Thoat" << endl;
            int choice;
            cout << "Nhap lua chon cua ban: ";
            cin >> choice;
            if (choice < 1 || choice > 3) {
                cout << "Lua chon khong hop le" << endl;
                continue;
            } else if (choice == 1) {
                cout << "Nhap ten mon hoc moi: ";
                cin.ignore();
                cin.getline(t->mh.TENMH, 51);
                cout << "Sua ten mon hoc thanh cong" << endl;
                continue;
            } else if (choice == 2) {
                cout << "Nhap so tin chi ly thuyet moi: ";
                cin >> t->mh.STCLT;
                cout << "Sua so tin chi ly thuyet thanh cong" << endl;
                continue;
            } else if (choice == 3) {
                cout << "Nhap so tin chi thuc hanh moi: ";
                cin >> t->mh.STCTH;
                cout << "Sua so tin chi thuc hanh thanh cong" << endl;
                continue;
            } else return;
        }
    }
}

//LNR
void InDSMH(treeMH t) {
    if (t != nullptr) {
        InDSMH(t->left);
        cout << "Ma MH: " << t->mh.MAMH << ", Ten MH: " << t->mh.TENMH << endl;
        InDSMH(t->right);
    }
}

bool timMonHoc (treeMH t, char mamh[]) {
    if (t != nullptr) {
        InDSMH(t->left);
        if (strcmp(t->mh.MAMH, mamh) == 0) {
            return true;
        }
        InDSMH(t->right);
    }
    return false;
}

int main () {
    treeMH t = NULL;
    NhapMonHoc(t);
    if (t == nullptr) {
        cout << "Danh sach mon hoc rong." << endl;
    } else {
        InDSMH(t);
    }
    system("pause");
    return 0;
}
