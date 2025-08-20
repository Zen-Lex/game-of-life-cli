// menu.hpp
#ifndef MENU_HPP
#define MENU_HPP

#include <string>
#include <format>
#include <vector>
#include <ncurses.h>

#include "gameoflife.hpp"
#include "grid.hpp"

#define MENU 1
#define SELECT_ITEM 2
#define INFO_BAR 3

class GameOfLife;

class Menu {
    private:
        GameOfLife& controller;
        std::vector<std::string> options_list;
        int cursor_pos;

    public:
        // Constructor
        Menu(GameOfLife& controller_);

        // Public methods
        void show();

    private:
        void print_menu(std::vector<string> list, int start_pos, bool wiped, bool exit);
        void change_options();
        int parse_input(int max_cursor_pos);
        int parse_input_horizontal_scroll(int max_cursor_pos);
        void menu_options_at_start(int cursor_pos);
        void menu_options_running(int cursor_pos);
        void print_about();
        void print_instructions();
        void print_horizontal_section(std::string name, std::vector<std::vector<std::string>> list);
};

#endif // MENU_HPP
