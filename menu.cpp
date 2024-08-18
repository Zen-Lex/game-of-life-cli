#include <iostream>
#include "headers/menu.hpp"

Menu::Menu(GameOfLife& controller_) : controller(controller_), cursor_pos(0) {
    options_list.push_back("Run (current file: " + controller.get_filename() + ")");
    options_list.push_back("Rules");
    options_list.push_back("Change file");
    options_list.push_back("Options");
    options_list.push_back("Exit");

    start_color();
    init_pair(MENU, COLOR_WHITE, COLOR_BLACK);
    init_pair(SELECT_ITEM, COLOR_MAGENTA, COLOR_BLACK);
}

void Menu::print_menu(std::vector<string> list) {
    erase();
    move(0, 0);
    printw("");

    for (int i = 0; i < list.size(); ++i) {
        if (i == cursor_pos) {
            attron(COLOR_PAIR(SELECT_ITEM));
            mvprintw(i, 0, ("> " + list.at(i)).c_str());
            attroff(COLOR_PAIR(SELECT_ITEM));
        }
        else {
            mvprintw(i, 0, ("  " + list.at(i)).c_str());
        }
    }
    refresh();
}

void Menu::change_file() {
    char str[80];
    erase();
    move(0, 0);

    printw("Please enter a new path to a .rle or .txt file: ");
    curs_set(1);
    refresh();

    getstr(str);
    curs_set(0);

    controller.set_filename(str);
    mvprintw(3, 0, "File '%s' saved", str);
    refresh();

    mvprintw(4, 0, "Press any key to go back.");
    getch();
}

void Menu::change_options() {
    cursor_pos = 0;
    std::vector<std::string> change_options_list;

    change_options_list.push_back("Step duration (current: " + to_string(controller.get_duration()) + ")");
    change_options_list.push_back("History size (current: " + to_string(controller.get_history_size()) + ")");
    change_options_list.push_back("Return");

    do {
        change_options_list.at(0).assign("Step duration (current: " + to_string(controller.get_duration()) + ")");
        change_options_list.at(1).assign("History size (current: " + to_string(controller.get_history_size()) + ")");
        print_menu(change_options_list);
        
        if (parse_input(change_options_list.size()) == -1) {
            continue;
        }

        char str[80];
        erase();
        curs_set(1);
        move(0, 0);

        switch (cursor_pos) {
            case 0:
                printw("Please enter a new duration time in sec: ");
                refresh();

                getstr(str);

                controller.set_duration(stof(str));
                mvprintw(3, 0, "A step of the simulation is now %ss.", str);
                break;

            case 1:
                printw("Please enter a new size for the history: ");
                refresh();

                getstr(str);

                controller.set_history_size(stoi(str));
                mvprintw(3, 0, "The history will now saves %s steps.", str);
                break;

            case 2:
                curs_set(0);
                show();
                break;

            default:
                break;
        }

        curs_set(0);
        refresh();
        mvprintw(4, 0, "Press any key to go back.");
        getch();

    }
    while (true);
}

int Menu::parse_input(int max_cursor_pos) {
    int c = 0;
    c = getch();

    if (c == KEY_UP && cursor_pos >= 1) {
        --cursor_pos;
        return -1;
    }
    else if (c == KEY_DOWN && cursor_pos < max_cursor_pos - 1) {
        ++cursor_pos;
        return -1;
    }
    else if (c == KEY_ENTER || c == 10) {
        return c;
    }

    return -1;
}

void Menu::menu_options_at_start(int cursor_pos) {
    switch (cursor_pos) {
        case 0:
            controller.init_simulation();
            break;

        case 1:
            // print_rules();
            break;

        case 2:
            change_file();
            break;

        case 3:
            change_options();
            break;

        case 4:
            controller.end_simulation();
            break;

        default:
            break;
        }
}

void Menu::menu_options_running(int cursor_pos) {
    switch (cursor_pos) {
        case 0:
            controller.init_simulation();
            break;

        case 1:
            controller.get_grid()->set_step_count(0);
            controller.init_simulation();
            break;
        case 2:
            // print_rules();
            break;

        case 3:
            change_file();
            break;

        case 4:
            change_options();
            break;

        case 5:
            controller.end_simulation();
            break;

        default:
            break;
        }
}

void Menu::show() {
    cursor_pos = 0;
    int step_count = controller.get_grid()->get_step_count();

    do {
        if (step_count > 0 && options_list.size() == 5) {
            options_list.insert(options_list.begin() + 1, "Reset");
        }

        if (step_count > 0) {
            options_list.at(0).assign("Continue (current file: " + controller.get_filename() + " | Steps:" + to_string(step_count) + ")");
        }
        else {
            options_list.at(0).assign("Run (current file: " + controller.get_filename() + ")");
        }
        print_menu(options_list);
        
        if (parse_input(options_list.size()) == -1) {
            continue;
        }

        if (step_count == 0) {
            menu_options_at_start(cursor_pos);
        }
        else {
            menu_options_running(cursor_pos);
        }
    }
    while (true);
}