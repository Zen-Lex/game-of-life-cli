// #pragma once

#include <string>
#include <vector>
#include <ncurses.h>
#include <unistd.h>

#include "headers/project.hpp"

#define COLOR_RESET "\033[0m"
#define MENU 1
#define SELECT_ITEM 2

using namespace std;

void init_menu();
void print_menu();
void change_file();
void go_to_menu();

vector<string> options_list;
int cursor_pos = 0;

void init_menu() {
	options_list.push_back("Run");
	options_list.push_back("Rules");
	options_list.push_back("Change file");
	options_list.push_back("Options");
	options_list.push_back("Exit");

	init_pair(MENU, COLOR_WHITE, COLOR_BLACK);
	init_pair(SELECT_ITEM, COLOR_MAGENTA, COLOR_BLACK);
}

void print_menu() {
	erase();
	move(0, 0);

	options_list.at(0).assign("Run (current file: " + FILENAME + ")");

	for (int i = 0; i < options_list.size(); ++i) {
		if (i == cursor_pos) {
			attron(COLOR_PAIR(SELECT_ITEM));
			mvprintw(i, 0, ("> " + options_list.at(i)).c_str());
			attroff(COLOR_PAIR(SELECT_ITEM));
		}
		else {
			mvprintw(i, 0, ("  " + options_list.at(i)).c_str());
		}
	}
	refresh();
}

void change_file() {
	char str[80];
	erase();
	move(0, 0);

	printw("Please enter a new path to a .rle or .txt file: ");
	curs_set(1);
	refresh();

	getstr(str);
	curs_set(0);

	set_filename(str);
	mvprintw(3, 0, "File '%s' saved", str);
	refresh();

	mvprintw(4, 0, "Press any key to go back.");
	getch();
}

void go_to_menu() {
	int c = 0;

	do {
		print_menu();
		c = getch();

		if (c == KEY_UP && cursor_pos >= 1) {
			--cursor_pos;
		}
		else if (c == KEY_DOWN && cursor_pos < options_list.size() - 1) {
			++cursor_pos;
		}
		else if (c == KEY_ENTER || c == 10) {
			switch (cursor_pos) {
				case 0:
					init_simulation();
					break;

				case 1:
					// print_rules();
					break;

				case 2:
					change_file();
					break;

				case 3:
					// change_options();
					break;

				case 4:
					end_simulation();
					break;
				
				default:
					break;
			}
		}

	}
	while (true);
}