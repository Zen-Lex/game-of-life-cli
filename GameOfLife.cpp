#include <ncurses.h>
#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <format>
#include <algorithm>
#include <map>

#include "headers/grid.hpp"

#define COLOR_RESET "\033[0m"
#define CONTROL_BAR 1

using namespace std;

void update_offset(char c);
void printGrid(vector<cell> vec_grid, int x_max, int y_max);
vector<cell> compute_next_step(vector<cell> vec_grid);
bool off_limits(cell cell);

int GRID_LIMIT = INT32_MAX;

int x_offset = 0;
int y_offset = 0;

int step_count = 0;
bool run_state = true;

void update_offset(char c) {
    if (c == 'd') {
        --x_offset;
    }
    else if (c == 'q') {
        ++x_offset;
    }
    else if (c == 'z') {
        ++y_offset;
    }
    else if (c == 's') {
        --y_offset;
    }
}

void printGrid(vector<cell> vec_grid, int x_max, int y_max) {
    string str_action = "  Pause:'space'";
	erase();
    init_pair(CONTROL_BAR, COLOR_BLACK, COLOR_WHITE);
	attron(COLOR_PAIR(CONTROL_BAR));

    for (auto it = vec_grid.begin(); it < vec_grid.end(); ++it) {
        mvprintw(it->row + y_offset, it->column + x_offset, " ");
    }

    if (!run_state) {
        str_action = "  Prev:\'a\'   Play:\'space\'   Next:\'e\'";
    }

    string str_info = format("Quit: 'esc' | Steps:{} | # of cells alive:{}   ", to_string(step_count), vec_grid.size());
    int l = y_max - str_info.length() - str_action.length();
    str_action.append(l, ' ');
    mvprintw(x_max - 1, 0, str_action.c_str());
    printw(str_info.c_str());
    attroff(COLOR_PAIR(CONTROL_BAR));

	refresh();
	// usleep(10000);

}

vector<cell> compute_next_step(vector<cell> vec_grid) {
    vector<cell> new_vec_grid;
    map<cell, int> potential_new_cells;

    for (auto it = vec_grid.begin(); it < vec_grid.end(); ++it) {
        int neighbour = 0;
        cell tested_cell;

        for (int r = -1; r < 2; ++r) {
            for (int c = -1; c < 2; ++c) {
                if (r == 0 && c == 0) {
                    continue;
                }

                tested_cell = cell{it->row + r, it->column + c};
                auto it_tested_cell = find(vec_grid.begin(), vec_grid.end(), tested_cell);

                if (it_tested_cell == vec_grid.end()) {
                    auto n_cell = potential_new_cells.emplace(tested_cell, 0);
                    ++n_cell.first->second;
                }
                else {
                    ++neighbour;
                }
            }
        }

        if (neighbour == 2 || neighbour == 3 && !off_limits(tested_cell)) {
            new_vec_grid.push_back(*it);
        }
    }

    for (auto it = potential_new_cells.begin(); it != potential_new_cells.end(); ++it) {
        if (it->second == 3 && !off_limits(it->first)) {
            new_vec_grid.push_back(it->first);
        }
    }

    return new_vec_grid;
}

bool off_limits(cell cell) {
    int min = (GRID_LIMIT-1)/-2;
    int max = GRID_LIMIT/2;
    return !(cell.row > min && cell.row < max && cell.column > min && cell.column < max);
}