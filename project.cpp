#include <ncurses.h>
#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <fstream>
#include <string>
#include <sstream> 
#include <vector>

#include "GameOfLife.hpp"
#include "grid.hpp"

using namespace std;

string FILENAME = "fireshipgun.rle";

int main() {
	int x_screen_size, y_screen_size;

	vector<cell> vec_grid = create_grid_from_rle(FILENAME);
	
	initscr();
	start_color();
	cbreak();
	noecho();
	nodelay(stdscr, TRUE);

	getmaxyx(stdscr, x_screen_size, y_screen_size);
	
	while (true) {
		vec_grid = run(vec_grid, x_screen_size, y_screen_size);
	}

	cout << COLOR_RESET;
	endwin();
	return 0;
}