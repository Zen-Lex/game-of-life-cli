#include "headers/gameoflife.hpp"

int main() {
    GameOfLife game;

	initscr();
    start_color();
    cbreak();
    noecho();
    nodelay(stdscr, FALSE);
    keypad(stdscr, TRUE);
    curs_set(0);

    init_pair(MENU, COLOR_WHITE, COLOR_BLACK);
    init_pair(SELECT_ITEM, COLOR_MAGENTA, COLOR_BLACK);

    game.get_menu().show();
	
    return 0;
}
