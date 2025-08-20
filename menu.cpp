#include <iostream>
#include "headers/menu.hpp"

Menu::Menu(GameOfLife& controller_) : controller(controller_), cursor_pos(0) {
    options_list.push_back("Run (current file: " + controller.get_filename() + ")");
    options_list.push_back("Instructions");
    options_list.push_back("Options");
    options_list.push_back("About The Game of Life");

    start_color();
    use_default_colors();
    init_pair(MENU, COLOR_WHITE, -1);
    init_pair(SELECT_ITEM, COLOR_CYAN, -1);
    init_pair(INFO_BAR, COLOR_BLACK, COLOR_WHITE);
}

void Menu::print_menu(std::vector<string> list, int start_pos = 0, bool wiped = true, bool exit = false) {
    cursor_pos = 0;
    list.push_back(exit ? "Exit" : "Return");

    if (wiped) {
        erase();
    }

    do {
        move(start_pos, 0);
        printw("");
    
        for (int i = start_pos; i < start_pos + list.size(); ++i) {
            if (i == cursor_pos + start_pos) {
                attron(COLOR_PAIR(SELECT_ITEM));
                mvprintw(i, 0, ("> " + list.at(i - start_pos)).c_str());
                attroff(COLOR_PAIR(SELECT_ITEM));
            }
            else {
                mvprintw(i, 0, ("  " + list.at(i - start_pos)).c_str());
            }
        }
        refresh();
    }
    while (parse_input(list.size()) == -1);

    erase();
    move(0,0);
}

void Menu::change_options() {
    cursor_pos = 0;
    std::vector<std::string> change_options_list;

    change_options_list.push_back("Change file (current: " + controller.get_filename() + ")");
    change_options_list.push_back("Step duration (current: " + to_string(controller.get_duration()) + ")");
    change_options_list.push_back("History size (current: " + to_string(controller.get_history_size()) + ")");

    print_menu(change_options_list); 

    char str[80];
    erase();
    move(0, 0);
    curs_set(1);
    echo();

    switch (cursor_pos) {
        case 0:
            printw("Please enter a new path to a .rle or .txt file: ");
            refresh();

            getstr(str);

            controller.set_filename(str);
            curs_set(0);
            mvprintw(1, 0, "File '%s' saved", str);
            break;

        case 1:
            printw("Please enter a new duration time in sec: ");
            refresh();

            getstr(str);

            controller.set_duration(stof(str));
            curs_set(0);
            mvprintw(1, 0, "A step of the simulation is now %ss.", str);
            break;

        case 2:
            printw("Please enter a new size for the history: ");
            refresh();

            getstr(str);

            controller.set_history_size(stoi(str));
            curs_set(0);
            mvprintw(1, 0, "The history will now saves %s steps.", str);
            break;

        default:
            break;
    }
    
    noecho();
    print_menu({}, 3, false);
    refresh();
    show();
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

int Menu::parse_input_horizontal_scroll(int max_cursor_pos) {
    int c = 0;
    c = getch();

    if (c == KEY_LEFT && cursor_pos >= 1) {
        --cursor_pos;
        return -1;
    }
    else if (c == KEY_RIGHT && cursor_pos < max_cursor_pos) {
        ++cursor_pos;
        return -1;
    }
    else if (c == 27) { //Escape key
        return c;
    }

    return -1;
}

void Menu::print_about() {
    cursor_pos = 0;

    erase();
    move(0, 0);
    
    printw("The Game of Life, also known as Conway's Game of Life or simply Life, is a cellular automaton devised\n"
        "by the British mathematician John Horton Conway in 1970.\n\n"
        "It is a zero-player game, meaning that its evolution is determined by its initial state, requiring no further input.\n"
        "One interacts with the Game of Life by creating an initial configuration and observing how it evolves.\n"
        "It is Turing complete and can simulate a universal constructor or any other Turing machine. (from Wikipedia)\n\n"
        "Conway's Game of Life follows a set of simple rules that determine how the grid evolves over time.\n"
        "Each cell in the grid can either be alive or dead. The following rules apply to each cell based on the state of its eight neighbors:\n\n"
        "  - Underpopulation: Any live cell with fewer than two live neighbors dies.\n"
        "  - Survival: Any live cell with two or three live neighbors survives to the next generation.\n"
        "  - Overpopulation: Any live cell with more than three live neighbors dies.\n"
        "  - Reproduction: Any dead cell with exactly three live neighbors becomes a live cell.\n\n"
        "These rules are applied simultaneously to every cell in the grid,\n"
        "producing the next generation of the grid based on the current state.\n\n"
    );

    print_menu({}, 20, false);
    show();
}

void Menu::print_instructions() {
    std::vector<std::vector<std::string>> instructions_list;
    
    instructions_list.push_back({"Game Controls", "Once the simulation is running, you can control the simulation with the following keys:\n  - 'space': Pause/Resume the simulation.\n  - 'e': Advance to the next step (when paused).\n  - 'q': Go back to the previous step (when paused).\n  - Arrow Keys (or 'wasd'): Move the view of the grid.\n  - 'r: Exit the simulation.\n"});
    instructions_list.push_back({"Return to Menu & Resume Simulation", "At any point during the simulation, you can press the 'r' key to return to the main menu.\nIn the menu, you can change options such as the RLE file being used, the grid history size, or the step duration.\nAfter modifying the settings, you can resume the simulation, and the changes will take effect.\n"});
    instructions_list.push_back({"Loading Patterns", "You can load predefined patterns from RLE files.\nPlace your RLE files in the rle/ directory\nand modify the filename in the simulation settings to load a specific pattern.\n"});
    instructions_list.push_back({"Adjusting Simulation Speed", "You can modify the step duration of the simulation through the settings menu.\nThe default is set in seconds, and the speed will affect how quickly the grid evolves.\n"});
    instructions_list.push_back({"Grid History Size", "You can configure how many previous states of the grid are stored for navigation in the settings.\nThis determines how many steps back you can move in the simulation.\n"});

    print_horizontal_section("Instructions", instructions_list);
    show();
}

void Menu::print_horizontal_section(std::string name, std::vector<std::vector<std::string>> list) {
    int x_screen_size;
    int y_screen_size;
    cursor_pos = 0;
    
    std::string return_info = "'Esc': return";
    std::string prev_info = "< Prev: 'L arrow'";
    std::string next_info = "'R arrow': Next >";
    std::string exit_info = "'R arrow': Return to Menu >";
    
    do {
        if (cursor_pos == list.size()) {
            break;
        }

        getmaxyx(stdscr, x_screen_size, y_screen_size);
        std::string section_name = std::format("{} ({}/{}) - {}", name, cursor_pos+1, list.size(), list[cursor_pos][0]);
        int name_pos = y_screen_size/2 - section_name.size()/2;
        std::string str = return_info + std::string(name_pos - return_info.size() - 1, ' ') + section_name + std::string(name_pos + (section_name.size()%2 == 0 ? 1 : 0), ' ') + "\n";
        
        erase();
        move(0, 0);

        attron(COLOR_PAIR(INFO_BAR));
        printw(str.c_str());
        attroff(COLOR_PAIR(INFO_BAR));
        mvprintw(2, 0, list[cursor_pos][1].c_str());

        if (cursor_pos > 0) {
            mvprintw(x_screen_size-1, 0, prev_info.c_str());
        }
        
        if (cursor_pos < list.size() - 1) {
            int next_pos = y_screen_size - next_info.size() - 1;
            mvprintw(x_screen_size-1, next_pos, next_info.c_str());
        }

        if (cursor_pos == list.size() - 1) {
            int exit_pos = y_screen_size - exit_info.size() - 1;
            mvprintw(x_screen_size-1, exit_pos, exit_info.c_str());
        }
        
        refresh();
    }
    while(parse_input_horizontal_scroll(list.size()) == -1);
}

void Menu::menu_options_at_start(int cursor_pos) {
    switch (cursor_pos) {
        case 0:
            controller.init_simulation();
            break;

        case 1:
            print_instructions();
            break;

        case 2:
            change_options();
            break;

        case 3:
            print_about();
            break;

        default:
            controller.end_simulation();
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
            show();
            break;
            
        case 2:
            print_instructions();
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

void Menu::show() {

    cursor_pos = 0;
    int step_count = controller.get_grid()->get_step_count();

    if (step_count > 0 && options_list.size() == 4) {
        options_list.insert(options_list.begin() + 1, "Reset");
    }
    else if (options_list.size() == 5) {
        options_list.erase(options_list.begin() + 1);
    }

    if (step_count > 0) {
        options_list.at(0).assign("Continue (current file: " + controller.get_filename() + " | Steps:" + to_string(step_count) + ")");
    }
    else {
        options_list.at(0).assign("Run (current file: " + controller.get_filename() + ")");
    }

    print_menu(options_list, 0, true, true);

    if (step_count == 0) {
        menu_options_at_start(cursor_pos);
    }
    else {
        menu_options_running(cursor_pos);
    }
}