#ifndef MENU_HPP
#define MENU_HPP

#include <string>
#include <vector>
#include <ncurses.h>
#include <unistd.h>

#include "project.hpp"

#define COLOR_RESET "\033[0m"
#define MENU 1
#define SELECT_ITEM 2

using namespace std;

extern vector<string> options_list;
extern int cursor_pos;

void init_menu();
void print_menu();
void change_file();
void go_to_menu();

#endif