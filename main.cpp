#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/dom/elements.hpp>
#include <iostream>
#include <cstring>

using namespace std;
using namespace ftxui;

int main() {
    auto screen = ScreenInteractive::TerminalOutput();
    char selected_role[20] = "";

    // ==== MENU CHON ROLE ====
    auto admin_btn = Button(" Admin ", [&] { strcpy(selected_role, "Admin"); screen.Exit(); });
    auto teacher_btn = Button(" Teacher ", [&] { strcpy(selected_role, "Teacher"); screen.Exit(); });
    auto student_btn = Button(" Student ", [&] { strcpy(selected_role, "Student"); screen.Exit(); });
    auto exit_btn = Button(" Exit ", [&] { strcpy(selected_role, "Exit"); screen.Exit(); });

    auto role_container = Container::Vertical({
        admin_btn,
        teacher_btn,
        student_btn,
        exit_btn,
    });

    auto role_layout = Renderer(role_container, [&] {
        return vbox({
            text("CHON VAI TRO DANG NHAP") | bold | center | color(Color::Red3),
            separatorDouble(),
            vbox({
                admin_btn->Render(),
                teacher_btn->Render(),
                student_btn->Render(),
                exit_btn->Render(),
            }) | vcenter | center,
            separator(),
            text("Dung phim mui ten ↑ ↓ va Enter de chon") | dim | center,
        }) | borderDouble | center;
    });

    screen.Loop(role_layout);
    if (strcmp(selected_role, "Exit") == 0)
        return 0;

    // ==== MENU CHINH THEO ROLE ====
    char role_title[100];
    sprintf(role_title, "MENU (%s)", selected_role);

    // Cac nut chuc nang
    auto btn_xemMH = Button("Xem danh sach mon hoc", [] { cout << "Xem danh sach mon hoc\n"; });
    auto btn_dangky = Button("Dang ky / Huy dang ky lop", [] { cout << "Dang ky lop tin chi\n"; });
    auto btn_nhapdiem = Button("Nhap diem", [] { cout << "Nhap diem\n"; });
    auto btn_qlmon = Button("Them / Sua / Xoa mon hoc", [] { cout << "Quan ly mon hoc\n"; });
    auto btn_qlsv = Button("Quan ly sinh vien", [] { cout << "Quan ly sinh vien\n"; });
    auto btn_qlltc = Button("Tao / Huy lop tin chi", [] { cout << "Quan ly lop tin chi\n"; });
    auto btn_autodel = Button("Duyet auto delete lop tin chi", [] { cout << "Auto delete\n"; });
    auto btn_xembangdiem = Button("Xem bang diem tong ket", [] { cout << "Xem bang diem tong ket\n"; });
    auto btn_exit = Button("Exit", [&] { screen.Exit(); });

    // Container cho cac nut
    auto menu_container = Container::Vertical({
        btn_xemMH,
        btn_dangky,
        btn_nhapdiem,
        btn_qlmon,
        btn_qlsv,
        btn_qlltc,
        btn_autodel,
        btn_xembangdiem,
        btn_exit,
    });

    // Renderer giao dien
    auto menu_layout = Renderer(menu_container, [&] {
        return vbox({
            text(role_title) | bold | center | color(Color::Yellow3),
            separatorDouble(),
            vbox({
                // Quyền hạn theo vai trò
                (strcmp(selected_role, "Student") == 0 || strcmp(selected_role, "Teacher") == 0 || strcmp(selected_role, "Admin") == 0)
                    ? btn_xemMH->Render() : filler(),
                (strcmp(selected_role, "Student") == 0 || strcmp(selected_role, "Admin") == 0)
                    ? btn_dangky->Render() : filler(),
                (strcmp(selected_role, "Teacher") == 0 || strcmp(selected_role, "Admin") == 0)
                    ? btn_nhapdiem->Render() : filler(),
                (strcmp(selected_role, "Admin") == 0)
                    ? btn_qlmon->Render() : filler(),
                (strcmp(selected_role, "Admin") == 0)
                    ? btn_qlsv->Render() : filler(),
                (strcmp(selected_role, "Admin") == 0)
                    ? btn_qlltc->Render() : filler(),
                (strcmp(selected_role, "Admin") == 0)
                    ? btn_autodel->Render() : filler(),
                (strcmp(selected_role, "Student") == 0 || strcmp(selected_role, "Teacher") == 0 || strcmp(selected_role, "Admin") == 0)
                    ? btn_xembangdiem->Render() : filler(),
                btn_exit->Render(),
            }) | vcenter | center,
            separator(),
            text("↑↓ de chon, Enter de thuc hien") | dim | center,
        }) | borderDouble | center;
    });

    screen.Loop(menu_layout);

    cout << "\nBan da dang nhap voi vai tro: " << selected_role << endl;
    return 0;
}
