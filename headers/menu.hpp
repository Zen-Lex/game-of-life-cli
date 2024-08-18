// menu.hpp
#ifndef MENU_HPP
#define MENU_HPP

#include <string>
#include <vector>
#include <ncurses.h>

#include "gameoflife.hpp"
#include "grid.hpp"

#define MENU 1
#define SELECT_ITEM 2

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
        void change_file();

    private:
        void print_menu(std::vector<string> list);
        void change_options();
        int parse_input(int max_cursor_pos);
        void menu_options_at_start(int cursor_pos);
        void menu_options_running(int cursor_pos);
};

#endif // MENU_HPP
