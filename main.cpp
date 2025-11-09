#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>
#include <iostream>
#include <cstring>

using namespace std;
using namespace ftxui;

// ----------------- Cấu trúc lớp tín chỉ -----------------
struct LopTinChi {
    int MALOPTC;
    char MAMH[11];
    char NienKhoa[10];
    int Hocky;
    int Nhom;
    int sosvmin, sosvmax;
    bool huylop;
    LopTinChi() {
        MALOPTC = 0; MAMH[0]=0; NienKhoa[0]=0;
        Hocky=0; Nhom=0; sosvmin=0; sosvmax=0; huylop=false;
    }
};

struct nodeLTC {
    LopTinChi ltc;
    nodeLTC* next;
    nodeLTC(LopTinChi data) { ltc=data; next=nullptr; }
};
typedef nodeLTC* PTRLTC;

void initializeLTC(PTRLTC &First) { First=nullptr; }
PTRLTC createNodeLopTinChi(LopTinChi data){ return new nodeLTC(data); }
void insertLopTinChi(PTRLTC &First, LopTinChi data){
    PTRLTC p=createNodeLopTinChi(data);
    if(!First) First=p;
    else {
        PTRLTC tmp=First;
        while(tmp->next) tmp=tmp->next;
        tmp->next=p;
    }
}
bool isEmpty(PTRLTC &First){ return First==nullptr; }
int deleteFirst(PTRLTC &First){
    if(isEmpty(First)) return 0;
    PTRLTC p=First; First=p->next; delete p; return 1;
}
int deleteAfter(PTRLTC p){
    if(!p || !p->next) return 0;
    PTRLTC q=p->next; p->next=q->next; delete q; return 1;
}
int deleteLopTinChi(PTRLTC &First, int MALTC){
    if(isEmpty(First)) return 0;
    if(First->ltc.MALOPTC==MALTC) return deleteFirst(First);
    PTRLTC p;
    for(p=First; p->next && p->next->ltc.MALOPTC!=MALTC; p=p->next);
    if(p->next) return deleteAfter(p);
    return 0;
}
PTRLTC searchLopTinChi(PTRLTC &First,int MALTC){
    PTRLTC p=First;
    while(p){
        if(p->ltc.MALOPTC==MALTC) return p;
        p=p->next;
    }
    return nullptr;
}
void editLopTinChi(PTRLTC &First,int MALTC){
    PTRLTC p=searchLopTinChi(First,MALTC);
    if(!p){ cout<<"Khong tim thay lop tin chi\n"; return; }
    cout<<"Nhap Nien Khoa moi: "; cin.getline(p->ltc.NienKhoa,10);
    cout<<"Nhap Hoc Ky moi: "; cin>>p->ltc.Hocky; cin.ignore();
    cout<<"Nhap Nhom moi: "; cin>>p->ltc.Nhom; cin.ignore();
    cout<<"Nhap svmin svmax moi: "; cin>>p->ltc.sosvmin>>p->ltc.sosvmax; cin.ignore();
    int h; cout<<"Huy lop? (0=khong,1=co): "; cin>>h; cin.ignore(); p->ltc.huylop=(h==1);
}
void showLopTinChi(PTRLTC &First){
    if(!First){ cout<<"Danh sach rong\n"; return; }
    PTRLTC p=First;
    cout<<"=== DANH SACH LOP TIN CHI ===\n";
    while(p){
        cout<<"Ma LTC: "<<p->ltc.MALOPTC
            <<", MH: "<<p->ltc.MAMH
            <<", NK: "<<p->ltc.NienKhoa
            <<", HK: "<<p->ltc.Hocky
            <<", Nhom: "<<p->ltc.Nhom
            <<", Min/Max: "<<p->ltc.sosvmin<<"/"<<p->ltc.sosvmax
            <<", Huy: "<<p->ltc.huylop<<endl;
        p=p->next;
    }
}

// ----------------- Menu FTXUI -----------------
enum MenuState { ROLE_SELECT, MAIN_MENU, LTC_MENU };
enum Role { ROLE_NONE, ROLE_SINHVIEN, ROLE_GIANGVIEN, ROLE_ADMIN };

struct Permission {
    const char* action;
    bool sinhvien, giangvien, admin;
};
Permission permissionTable[] = {
    {"Xem danh sach mon hoc", true,true,true},
    {"Them / cap nhat / xoa mon hoc", false,false,true},
    {"Tao / cap nhat / huy lop sinh vien", false,false,true},
    {"In danh sach sinh vien", true,true,true},
    {"In bang diem trung binh", true,true,true},
    {"In bang diem tong ket", true,true,true},
    {"Tao / cap nhat / huy lop tin chi", false,false,true},
    {"In danh sach sinh vien da dang ki", true,true,true},
    {"In bang diem cua lop tin chi", true,true,true}
};
int permissionCount=sizeof(permissionTable)/sizeof(permissionTable[0]);
bool checkPermission(Role role, const char* action){
    for(int i=0;i<permissionCount;i++){
        if(strcmp(permissionTable[i].action,action)==0){
            if(role==ROLE_SINHVIEN) return permissionTable[i].sinhvien;
            if(role==ROLE_GIANGVIEN) return permissionTable[i].giangvien;
            if(role==ROLE_ADMIN) return permissionTable[i].admin;
        }
    }
    return false;
}

int main(){
    auto screen=ScreenInteractive::TerminalOutput();
    MenuState menu_state=ROLE_SELECT;
    Role currentRole=ROLE_NONE;
    char selected_role[20]="";

    PTRLTC dslopTC; initializeLTC(dslopTC);

    // --- Buttons chọn vai trò ---
    auto btn_sv=Button("Sinh vien",[&]{ currentRole=ROLE_SINHVIEN; strcpy(selected_role,"Sinh vien"); menu_state=MAIN_MENU;});
    auto btn_gv=Button("Giang vien",[&]{ currentRole=ROLE_GIANGVIEN; strcpy(selected_role,"Giang vien"); menu_state=MAIN_MENU;});
    auto btn_ad=Button("Admin",[&]{ currentRole=ROLE_ADMIN; strcpy(selected_role,"Admin"); menu_state=MAIN_MENU;});
    auto btn_exit=Button("Thoat",[&]{ screen.Exit(); });

    auto role_container=Container::Vertical({btn_sv,btn_gv,btn_ad,btn_exit});

    // --- Menu chính ---
    auto menu_container=Container::Vertical({});
    auto back_btn=Button("← Quay lai",[&]{ menu_state=ROLE_SELECT; currentRole=ROLE_NONE; strcpy(selected_role,""); menu_container->DetachAllChildren(); });

    // --- Menu lớp tín chỉ ---
   auto btn_themLTC = Button("➕ Them Lop Tin Chi",[&]{
    screen.Suspend();  // Tạm dừng giao diện FTXUI
    LopTinChi ltc;
    cout << "\n=== THEM LOP TIN CHI ===\n";
    cout << "Nhap Ma Lop TC: "; cin >> ltc.MALOPTC; cin.ignore();
    cout << "Nhap Ma MH: "; cin.getline(ltc.MAMH, 11);
    cout << "Nhap Nien Khoa: "; cin.getline(ltc.NienKhoa, 10);
    cout << "Nhap Hoc Ky: "; cin >> ltc.Hocky; cin.ignore();
    cout << "Nhap Nhom: "; cin >> ltc.Nhom; cin.ignore();
    cout << "Nhap svmin svmax: "; cin >> ltc.sosvmin >> ltc.sosvmax; cin.ignore();
    ltc.huylop = false;
    insertLopTinChi(dslopTC, ltc);
    cout << "✅ Them thanh cong!\n";
    cout << "Nhan Enter de quay lai giao dien...";
    cin.get();
    screen.Resume();   // Quay lại FTXUI
});

auto btn_xoaLTC = Button("🗑 Xoa Lop Tin Chi",[&]{
    screen.Suspend();
    cout << "\n=== XOA LOP TIN CHI ===\n";
    int malop; cout << "Nhap MALOPTC can xoa: "; cin >> malop; cin.ignore();
    if (deleteLopTinChi(dslopTC, malop)) cout << "🗑 Xoa thanh cong!\n";
    else cout << "❌ Khong tim thay lop tin chi co ma " << malop << endl;
    cout << "Nhan Enter de quay lai giao dien...";
    cin.get();
    screen.Resume();
});

auto btn_suaLTC = Button("✏ Hieu Chinh Lop Tin Chi",[&]{
    screen.Suspend();
    cout << "\n=== HIEU CHINH LOP TIN CHI ===\n";
    int malop; cout << "Nhap MALOPTC can hieu chinh: "; cin >> malop; cin.ignore();
    editLopTinChi(dslopTC, malop);
    cout << "Nhan Enter de quay lai giao dien...";
    cin.get();
    screen.Resume();
});

auto btn_inLTC = Button("📜 Hien Thi Danh Sach",[&]{
    screen.Suspend();
    cout << "\n=== DANH SACH LOP TIN CHI ===\n";
    showLopTinChi(dslopTC);
    cout << "Nhan Enter de quay lai giao dien...";
    cin.get();
    screen.Resume();
});

auto btn_backLTC = Button("← Quay lai",[&]{ menu_state = MAIN_MENU; });
// Gom 5 nút này lại trong container:
auto ltc_menu = Container::Vertical({
    btn_themLTC, btn_xoaLTC, btn_suaLTC, btn_inLTC, btn_backLTC
});

    // --- Cập nhật menu theo role ---
    auto updateMenuByRole = [&](){
        menu_container->DetachAllChildren();
        for(int i=0;i<permissionCount;i++){
            if(checkPermission(currentRole, permissionTable[i].action)){
                if(strcmp(permissionTable[i].action,"Tao / cap nhat / huy lop tin chi")==0){
                    menu_container->Add(Button(permissionTable[i].action,[&]{ menu_state=LTC_MENU; }));
                } else {
                    menu_container->Add(Button(permissionTable[i].action,[=]{ cout<<"[Thuc hien]: "<<permissionTable[i].action<<endl; }));
                }
            }
        }
        menu_container->Add(back_btn);
    };

    // --- Renderer ---
    auto layout = Renderer([&]{
        if(menu_state==ROLE_SELECT){
            return vbox({ text("CHON VAI TRO DANG NHAP")|bold|center|color(Color::Yellow),
                          separator(),
                          role_container->Render(),
                          separator(),
                          text("Dung mui ten ↑ ↓ va Enter de chon")|dim|center })|borderDouble|center;
        }
        if(menu_state==MAIN_MENU){
            updateMenuByRole();
            return vbox({ text("🏫 QUAN LY HE TIN CHI 🏫")|bold|center|color(Color::Red3),
                          hbox({ text("Vai tro: ")|bold, text(selected_role)|color(Color::Green)})|center,
                          separator(),
                          menu_container->Render(),
                          separator(),
                          text("← Chon Quay lai de doi vai tro hoac thoat")|dim|center })|border|center;
        }
        if(menu_state==LTC_MENU){
            return vbox({ text("=== QUAN LY LOP TIN CHI ===")|bold|center,
                          ltc_menu->Render(),
                          separator(),
                          text("Dung mui ten ↑ ↓ va Enter de chon")|dim|center })|border|center;
        }
        return text("Trang thai khong hop le")|color(Color::Red);
    });

    // --- CatchEvent ---
    auto main = CatchEvent(layout,[&](Event event){
        if(menu_state==ROLE_SELECT) return role_container->OnEvent(event);
        if(menu_state==MAIN_MENU) return menu_container->OnEvent(event);
        if(menu_state==LTC_MENU) return ltc_menu->OnEvent(event);
        return false;
    });

    // --- Loop ---
    screen.Loop(main);

    cout<<"\nBan da chon vai tro: "<<selected_role<<endl;
    return 0;
}
