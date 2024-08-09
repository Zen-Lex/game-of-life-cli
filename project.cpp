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

	/* ifstream readfile("testboard.txt");
	string fileline,xx,yy;

	while (getline(readfile,fileline)) {
		stringstream ss(fileline);
		
		getline(ss,xx,' ');
		getline(ss,yy,' ');

		x = stoi(xx);
		y = stoi(yy);

		grid[x][y] = true;
	} */

	create_grid_from_rle("test.rle");
	
	initscr();
	start_color();
	cbreak();
	noecho();
	nodelay(stdscr, TRUE);

	getmaxyx(stdscr, x_max, y_max);
	
	while (true) {
		run(grid, x_max, y_max);
	}

	cout << COLOR_RESET;
	endwin();
	return 0;
}