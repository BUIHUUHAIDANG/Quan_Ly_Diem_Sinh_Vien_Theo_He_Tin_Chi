#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>
#include <cstring>
#include <iostream>

using namespace std;
using namespace ftxui;
// Trang thai menu
enum MenuState { ROLE_SELECT, MAIN_MENU };
enum Role { ROLE_NONE, ROLE_SINHVIEN, ROLE_GIANGVIEN, ROLE_ADMIN };


struct Permission {
    const char *action;
    bool sinhvien;
    bool giangvien;
    bool admin;
};

// Quyen
Permission permissionTable[] = {
    {"Xem danh sach mon hoc",             true,   true,  true },
    {"Them / cap nhat / xoa mon hoc",     false,  false, true },
    {"Tao / cap nhat / huy lop sinh vien",false,  false, true },
    {"In danh sach sinh vien",            true,   true,  true },
    {"In bang diem trung binh",           true,   true,  true },
    {"In bang diem tong ket",             true,   true,  true },
    {"Tao / cap nhat / huy lop tin chi",  false,  false, true },
    {"In danh sach sinh vien da dang ki", true,   true,  true },
    {"In bang diem cua lop tin chi",      true,   true,  true },
};
int permissionCount = sizeof(permissionTable)/sizeof(permissionTable[0]);

bool checkPermission(Role role, const char *action) {
    for (int i = 0; i < permissionCount; i++) {
        if (strcmp(permissionTable[i].action, action) == 0) {
            if (role == ROLE_SINHVIEN) return permissionTable[i].sinhvien;
            if (role == ROLE_GIANGVIEN) return permissionTable[i].giangvien;
            if (role == ROLE_ADMIN)     return permissionTable[i].admin;
        }
    }
    return false;
}

int main() {
    auto screen = ScreenInteractive::TerminalOutput();

    MenuState menu_state = ROLE_SELECT;
    Role currentRole = ROLE_NONE;
    char selected_role[20] = "";
    
    auto btn_sv = Button("  Sinh vien ", [&] {
        currentRole = ROLE_SINHVIEN;
        strcpy(selected_role, "Sinh vien");
        menu_state = MAIN_MENU;
    });
    auto btn_gv = Button("  Giang vien ", [&] {
        currentRole = ROLE_GIANGVIEN;
        strcpy(selected_role, "Giang vien");
        menu_state = MAIN_MENU;
    });
    auto btn_ad = Button("  Admin ", [&] {
        currentRole = ROLE_ADMIN;
        strcpy(selected_role, "Admin");
        menu_state = MAIN_MENU;
    });
    auto btn_exit = Button(" Thoat ", [&] { screen.Exit(); });

    auto role_container = Container::Vertical({
        btn_sv, btn_gv, btn_ad, btn_exit
    });

    
    // MENU CHINH (TUY THEO ROLE)
    
    auto menu_container = Container::Vertical({});
    auto back_btn = Button(" ← Quay lai ", [&] {
        menu_state = ROLE_SELECT;
        currentRole = ROLE_NONE;
        strcpy(selected_role, "");
        menu_container->DetachAllChildren();
    });

    // Render menu dua theo role
    auto updateMenuByRole = [&]() {
        menu_container->DetachAllChildren();
        for (int i = 0; i < permissionCount; i++) {
            if (checkPermission(currentRole, permissionTable[i].action)) {
                menu_container->Add(Button(permissionTable[i].action, [=] {
                    cout << "[Thuc hien]: " << permissionTable[i].action << endl;
                }));
            }
        }
        menu_container->Add(back_btn);
    };

    
    // RENDERER
    
    auto layout = Renderer([&] {
        if (menu_state == ROLE_SELECT) {
            return vbox({
                       text("CHON VAI TRO DANG NHAP") | bold | center | color(Color::Yellow),
                       separator(),
                       role_container->Render(),
                       separator(),
                       text("Dung phim mui ten ↑ ↓ va Enter de chon") | dim | center
                   }) | borderDouble | center;
        }

        if (menu_state == MAIN_MENU) {
            updateMenuByRole();
            return vbox({
                text("🏫 QUAN LY THEO HE TIN CHI 🏫") | bold | center | color(Color::Red3),
                hbox({
                   text("Vai tro: ") | bold,
                   text(selected_role) | color(Color::Green)
               }) | center,
               separator(),
               menu_container->Render(),
               separator(),
               text("← Chon Quay lai de doi vai tro hoac thoat") | dim | center
           }) | border | center;
}

        return text("Trang thai khong hop le") | color(Color::Red);
    });

    
    // Route su kien
    
    auto main = CatchEvent(layout, [&](Event event) {
        if (menu_state == ROLE_SELECT)
            return role_container->OnEvent(event);
        else if (menu_state == MAIN_MENU)
            return menu_container->OnEvent(event);
        return false;
    });

    
    // LOOP
    
    screen.Loop(main);

    cout << "\nBan da chon vai tro: " << selected_role << endl;
    return 0;
}
