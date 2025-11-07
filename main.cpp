#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>
#include <cstring>
#include <iostream>

using namespace std;
using namespace ftxui;

enum MenuState { MAIN_MENU, ADMIN_MENU, STUDENT_MENU, TEACHER_MENU };

int main() {
    auto screen = ScreenInteractive::TerminalOutput();
    MenuState menu_state = MAIN_MENU;
    char selected_role[20] = "";

    // ===== MAIN MENU BUTTONS =====
    auto admin_btn = Button(" Admin ", [&] { strcpy(selected_role, "Admin"); menu_state = ADMIN_MENU; });
    auto student_btn = Button(" Student ", [&] { strcpy(selected_role, "Student"); menu_state = STUDENT_MENU; });
    auto teacher_btn = Button(" Teacher ", [&] { strcpy(selected_role, "Teacher"); menu_state = TEACHER_MENU; });
    auto exit_btn = Button(" Exit ", [&] { strcpy(selected_role, "Exit"); screen.Exit(); });

    auto main_container = Container::Vertical({
        admin_btn,
        student_btn,
        teacher_btn,
        exit_btn,
    });

    // ===== BACK BUTTON (shared across menus) =====
    auto back_btn_admin = Button(" ← Back ", [&] { menu_state = MAIN_MENU; strcpy(selected_role, ""); });
    auto back_btn_student = Button(" ← Back ", [&] { menu_state = MAIN_MENU; strcpy(selected_role, ""); });
    auto back_btn_teacher = Button(" ← Back ", [&] { menu_state = MAIN_MENU; strcpy(selected_role, ""); });

    // ===== ADMIN MENU =====
    auto admin_container = Container::Vertical({
        Button(" Manage Subjects ", [] { cout << "Admin: Manage Subjects\n"; }),
        Button(" Manage Classes ", [] { cout << "Admin: Manage Classes\n"; }),
        Button(" Manage Students ", [] { cout << "Admin: Manage Students\n"; }),
        Button(" Approve Auto Delete ", [] { cout << "Admin: Auto Delete\n"; }),
        back_btn_admin,
    });

    // ===== STUDENT MENU =====
    auto student_container = Container::Vertical({
        Button(" Register / Cancel Course ", [] { cout << "Student: Register\n"; }),
        Button(" View Personal Transcript ", [] { cout << "Student: View Transcript\n"; }),
        back_btn_student,
    });

    // ===== TEACHER MENU =====
    auto teacher_container = Container::Vertical({
        Button(" Input Grades ", [] { cout << "Teacher: Input Grades\n"; }),
        Button(" View Class Students ", [] { cout << "Teacher: View Students\n"; }),
        back_btn_teacher,
    });

    // ===== RENDERER (UI for each screen) =====
    auto layout = Renderer([&] {
        if (menu_state == MAIN_MENU) {
            return vbox({
                       text("QUAN LY THEO HE TIN CHI") | bold | center | color(Color::Red3),
                       separator(),
                       main_container->Render(),
                       separator(),
                       text("Use Arrow Keys or Mouse to Select") | dim | center
                   }) |
                   borderDouble | center;
        }

        if (menu_state == ADMIN_MENU) {
            return vbox({
                       text("ADMIN MENU") | bold | center | color(Color::BlueLight),
                       separator(),
                       admin_container->Render(),
                       separator(),
                       text("Press ← Back to return") | dim | center
                   }) |
                   border | center;
        }

        if (menu_state == STUDENT_MENU) {
            return vbox({
                       text("STUDENT MENU") | bold | center | color(Color::Green),
                       separator(),
                       student_container->Render(),
                       separator(),
                       text("Press ← Back to return") | dim | center
                   }) |
                   border | center;
        }

        if (menu_state == TEACHER_MENU) {
            return vbox({
                       text("TEACHER MENU") | bold | center | color(Color::Cyan),
                       separator(),
                       teacher_container->Render(),
                       separator(),
                       text("Press ← Back to return") | dim | center
                   }) |
                   border | center;
        }

        return text("Invalid menu") | color(Color::Red);
    });

    // ===== ROUTE INPUT EVENTS TO CORRECT CONTAINER =====
    auto main = CatchEvent(layout, [&](Event event) {
        if (menu_state == MAIN_MENU) return main_container->OnEvent(event);
        if (menu_state == ADMIN_MENU) return admin_container->OnEvent(event);
        if (menu_state == STUDENT_MENU) return student_container->OnEvent(event);
        if (menu_state == TEACHER_MENU) return teacher_container->OnEvent(event);
        return false;
    });

    // ===== LOOP =====
    screen.Loop(main);

    cout << "\nYou selected: " << selected_role << endl;
    return 0;
}
