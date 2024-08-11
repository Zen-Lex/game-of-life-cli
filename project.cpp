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

int main() {
    int x,y,n;
	int x_max, y_max;

	vector<cell> vec_grid = create_grid_from_rle("blinker.rle");
	
	initscr();
	start_color();
	cbreak();
	noecho();
	nodelay(stdscr, TRUE);

	getmaxyx(stdscr, x_max, y_max);
	
	while (true) {
		vec_grid = run(vec_grid, x_max, y_max);
	}

	cout << COLOR_RESET;
	endwin();
	return 0;
}