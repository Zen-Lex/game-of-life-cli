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
    
    use_default_colors();
    init_pair(MENU, COLOR_WHITE, -1);
    init_pair(SELECT_ITEM, COLOR_CYAN, -1);
    init_pair(INFO_BAR, COLOR_BLACK, COLOR_WHITE);

    game.get_menu().show();
	
    return 0;
}
