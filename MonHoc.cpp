#include "MonHoc.h"
#include <fstream>
#include <sstream>
#include <cstring>
#include <algorithm>

using namespace std;

// -------------------- HÀM AVL --------------------
int GetHeight(treeMH t) { 
    return t ? t->height : 0; 
}

int GetBalance(treeMH t) { 
    return t ? (GetHeight(t->left) - GetHeight(t->right)) : 0; 
}

treeMH RotateRight(treeMH y) {
    treeMH x = y->left;
    treeMH T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(GetHeight(y->left), GetHeight(y->right)) + 1;
    x->height = max(GetHeight(x->left), GetHeight(x->right)) + 1;

    return x;
}

treeMH RotateLeft(treeMH x) {
    treeMH y = x->right;
    treeMH T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(GetHeight(x->left), GetHeight(x->right)) + 1;
    y->height = max(GetHeight(y->left), GetHeight(y->right)) + 1;

    return y;
}

treeMH CheckandRotation(treeMH t) {
    if (!t) return nullptr;

    t->height = 1 + max(GetHeight(t->left), GetHeight(t->right));
    int balance = GetBalance(t);

    if (balance > 1 && GetBalance(t->left) >= 0)
        return RotateRight(t);

    if (balance < -1 && GetBalance(t->right) <= 0)
        return RotateLeft(t);

    if (balance > 1 && GetBalance(t->left) < 0) {
        t->left = RotateLeft(t->left);
        return RotateRight(t);
    }

    if (balance < -1 && GetBalance(t->right) > 0) {
        t->right = RotateRight(t->right);
        return RotateLeft(t);
    }

    return t;
}

treeMH Insert(treeMH t, MonHoc mh) {
    if (!t) {
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
    else return t;

    return CheckandRotation(t);
}

treeMH XoaMH(treeMH &t, char MAMH[]) {
    if (!t) return nullptr;

    if (strcmp(MAMH, t->mh.MAMH) < 0)
        t->left = XoaMH(t->left, MAMH);
    else if (strcmp(MAMH, t->mh.MAMH) > 0)
        t->right = XoaMH(t->right, MAMH);
    else {
        if (!t->left && !t->right) { delete t; return nullptr; }
        else if (!t->left) { treeMH temp = t->right; delete t; return temp; }
        else if (!t->right) { treeMH temp = t->left; delete t; return temp; }
        else {
            treeMH minRight = t->right;
            while (minRight->left) minRight = minRight->left;
            t->mh = minRight->mh;
            t->right = XoaMH(t->right, minRight->mh.MAMH);
        }
    }
    return CheckandRotation(t);
}

// -------------------- HÀM FILE --------------------
void LuuMonHoc(treeMH t, string filename) {
    ofstream f(filename, ios::app);
    if (!t) {
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

// -------------------- HÀM HỖ TRỢ --------------------
bool checkMH(treeMH t, MonHoc mh) {
    if (!t) return false;
    if (strcmp(mh.MAMH, t->mh.MAMH) == 0) return true;
    if (strcmp(mh.MAMH, t->mh.MAMH) < 0) return checkMH(t->left, mh);
    return checkMH(t->right, mh);
}

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

void SuaMH(treeMH &t, MonHoc mh) {
    if (!t) { cout << "Khong tim thay mon hoc de sua\n"; return; }

    if (strcmp(mh.MAMH, t->mh.MAMH) < 0) SuaMH(t->left, mh);
    else if (strcmp(mh.MAMH, t->mh.MAMH) > 0) SuaMH(t->right, mh);
    else {
        while (true) {
            cout << "1.Ten MH 2.STCLT 3.STCTH 4.Thoat\nLua chon: ";
            int choice; cin >> choice;
            if (choice < 1 || choice > 4) { cout << "Lua chon khong hop le\n"; continue; }
            if (choice == 1) { cin.ignore(); cout << "Nhap ten moi: "; cin.getline(t->mh.TENMH,51); }
            else if (choice == 2) { cout << "Nhap STCLT moi: "; cin >> t->mh.STCLT; }
            else if (choice == 3) { cout << "Nhap STCTH moi: "; cin >> t->mh.STCTH; }
            else return;
        }
    }
}

void InDSMH(treeMH t) {
    if (!t) return;
    InDSMH(t->left);
    cout << "Ma MH: " << t->mh.MAMH << ", Ten MH: " << t->mh.TENMH << endl;
    InDSMH(t->right);
}

bool timMonHoc(treeMH t, char mamh[]) {
    if (!t) return false;
    if (strcmp(t->mh.MAMH, mamh) == 0) return true;
    return strcmp(mamh, t->mh.MAMH) < 0 ? timMonHoc(t->left,mamh) : timMonHoc(t->right,mamh);
}
