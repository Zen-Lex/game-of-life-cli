#include <ncurses.h>
#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

#include "headers/gameoflife.hpp"
#include "headers/grid.hpp"
#include "headers/menu.hpp"
#include "headers/timercpp.h"

using namespace std;

string FILENAME = "rle/blinker.rle";
float STEP_DURATION = 0.2;
 
Timer t = Timer();
vector<cell> vec_grid;
vector<vector<cell>> history;
int x_screen_size, y_screen_size;
bool stop_sim = false;

void init_simulation();
void start_timer();
void stop_timer();
void run();
void next();
void prev();
void set_filename(string path); //best programer ever AP
void end_simulation();

int main() {
	initscr();
	start_color();
	cbreak();
	noecho();
	nodelay(stdscr, FALSE);
	keypad(stdscr, TRUE);
	curs_set(0);

	init_menu();
	go_to_menu();

	return 0;
}

void init_simulation() {
	stop_sim = false;
	run_state = true;
	step_count = 0;
	vec_grid.clear();
	history.clear();
	vec_grid = create_grid_from_rle(FILENAME);
	getmaxyx(stdscr, x_screen_size, y_screen_size);
	
	printGrid(vec_grid, x_screen_size, y_screen_size);
	start_timer();
	
	while(!stop_sim) {
		run();
	}

	go_to_menu();
}

void end_simulation() {
	stop_timer();

	curs_set(1);
	endwin();
	exit(0);
}

void stop_timer() {
	t.stop();
}

void start_timer() {
	t.setInterval([&]() {
		next();
    }, STEP_DURATION * 1000);
}

void run() {
	int c = getch();

	if (c == ERR) {
        return;
    }

 	if (c == '!') { //Escape key
		stop_timer();
		stop_sim = true;
	}
    else if (c == ' ') {
        run_state = !run_state;

		if (run_state) {
			start_timer();
		}
		else {
			stop_timer();
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

void set_filename(string path) {
	FILENAME = path;
}