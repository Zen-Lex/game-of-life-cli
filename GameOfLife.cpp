// Author: Mario Talevski
#include <ncurses.h>
#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <format>

#define COLOR_RESET "\033[0m"
#define CONTROL_BAR 1

using namespace std;

const int gridSize = 40;
void run(bool grid[gridSize+1][gridSize+1], int x_max, int y_max);
void printGrid(bool grid[gridSize+1][gridSize+1], int x_max, int y_max);
void determineState(bool grid[gridSize+1][gridSize+1]);

int step_count = 0;
bool run_state = true;

void run(bool grid[gridSize+1][gridSize+1], int x_max, int y_max) {
	int c = getch();
    if (c == ' ') {
        run_state = !run_state;

        
    }
    else if (!run_state && c == 'e') {
        printGrid(grid, x_max, y_max);
        determineState(grid);
        step_count++;
    }

    // cout << run_state;
    init_pair(CONTROL_BAR, COLOR_BLACK, COLOR_WHITE);
    // curs_set(1);
    printGrid(grid, x_max, y_max);
    usleep(0.05 * 1000000);

    if (run_state) {
        determineState(grid);
        step_count++;
    }
    // curs_set(0);
}

void printGrid(bool grid[gridSize+1][gridSize+1], int x_max, int y_max){
    int cells_alive = 0;
    string str_action = "  Pause:'space'";
	erase();
	refresh();
	attron(COLOR_PAIR(CONTROL_BAR));
    
    for(int a = 1; a < gridSize; a++) {
        for(int b = 1; b < gridSize; b++) {
        	if(grid[a][b] == true) {
        		mvprintw(a, b, " ");
                cells_alive++;
        	}
        }
    }

    if (!run_state) {
        str_action = "  Prev:\'a\'   Play:\'space\'   Next:\'e\'";
    }

    string str_info = format("Genarations:{}\t# of cells alive:{}", to_string(step_count), cells_alive);
    int l = x_max - str_info.length() - str_action.length();
    str_action.append(l, ' ');
    mvprintw(gridSize, 0, str_action.c_str());
    printw(str_info.c_str());
    attroff(COLOR_PAIR(CONTROL_BAR));

	refresh();
}

void compareGrid (bool gridOne[gridSize+1][gridSize+1], bool gridTwo[gridSize+1][gridSize+1]) {
    for(int a =0; a < gridSize; a++) {
        for(int b = 0; b < gridSize; b++) {
                gridTwo[a][b] = gridOne[a][b];
        }
    }
}

void determineState(bool grid[gridSize+1][gridSize+1]) {
    bool gridTwo[gridSize+1][gridSize+1] = {};
    compareGrid(grid, gridTwo);

    for(int a = 1; a < gridSize; a++) {
        for(int b = 1; b < gridSize; b++) {
            int alive = 0;

            for(int c = -1; c < 2; c++) {
                for(int d = -1; d < 2; d++) {
                    if(!(c == 0 && d == 0)) {
                        if(gridTwo[a+c][b+d]) {
					        ++alive;
				        }
                    }
                }
            }

            if(alive < 2) {
                grid[a][b] = false;
            }
            else if(alive == 3) {
                grid[a][b] = true;
            }
            else if(alive > 3) {
                grid[a][b] = false;
            }
        }
    }
}