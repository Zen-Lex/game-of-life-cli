#include <ncurses.h>
#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <fstream>
#include <string>
#include <sstream> 
#include <vector>

#include "headers/GameOfLife.hpp"
#include "headers/grid.hpp"
#include "headers/timercpp.h"

using namespace std;

string FILENAME = "pulsar/fireshipgun.rle";
float STEP_DURATION = 0.1;

Timer t = Timer();
vector<cell> vec_grid;
vector<vector<cell>> history;
int x_screen_size, y_screen_size;

void start();
void stop();
void run();
void next();
void prev();

int main() {
	vec_grid = create_grid_from_rle(FILENAME);
	
	initscr();
	start_color();
	cbreak();
	noecho();
	nodelay(stdscr, FALSE);

	getmaxyx(stdscr, x_screen_size, y_screen_size);

	printGrid(vec_grid, x_screen_size, y_screen_size);
	start();
	
	while(true) {
		run();
	}

	cout << COLOR_RESET;
	endwin();
	return 0;
}

void stop() {
	t.stop();
}

void start() {
	t.setInterval([&]() {
		next();
    }, STEP_DURATION * 1000);
}

void run() {
	int c = getch();

	if (c == ERR) {
        return;
    }

    if (c == ' ') {
        run_state = !run_state;

		if (run_state) {
			start();
		}
		else {
			stop();
		}

		printGrid(vec_grid, x_screen_size, y_screen_size);
    }
    else if (c == 'e') {
        if (run_state) {
            return;
        }

		next();
    }
    else if (c == 'a') {
        if (run_state) {
            return;
        }

		prev();
    }
    else {
		update_offset(c);
		printGrid(vec_grid, x_screen_size, y_screen_size);
	}
}

void next() {
	history.insert(history.begin(), vec_grid);
	history.resize(20);

	vec_grid = compute_next_step(vec_grid);
	++step_count;

	printGrid(vec_grid, x_screen_size, y_screen_size);
}

void prev() {
	if (run_state) {
		return;
	}

	if (history.size() <= 0 || step_count <= 0) {
		return;
	}

	vec_grid = history.at(0);
	history.erase(history.begin());
	--step_count;

	printGrid(vec_grid, x_screen_size, y_screen_size);
}