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
#include <algorithm>
#include <map>

#include "grid.hpp"

#define COLOR_RESET "\033[0m"
#define CONTROL_BAR 1

using namespace std;

vector<cell> run(vector<cell> vec_grid, int x_max, int y_max);
void printGrid(vector<cell> vec_grid, int x_max, int y_max);
vector<cell> compute_next_step(vector<cell> vec_grid);

int step_count = 0;
bool run_state = true;

vector<cell> run(vector<cell> vec_grid, int x_max, int y_max) {
	int c = getch();
    if (c == ' ') {
        run_state = !run_state;
    }
    else if (!run_state && c == 'e') {
        printGrid(vec_grid, x_max, y_max);
        vec_grid = compute_next_step(vec_grid);
        step_count++;
    }

    // cout << run_state;
    init_pair(CONTROL_BAR, COLOR_BLACK, COLOR_WHITE);
    // curs_set(1);
    printGrid(vec_grid, x_max, y_max);
    usleep(0.1 * 1000000);

    if (run_state) {
        vec_grid = compute_next_step(vec_grid);
        step_count++;
    }
    
    return vec_grid;
}

void printGrid(vector<cell> vec_grid, int x_max, int y_max) {
    string str_action = "  Pause:'space'";
	erase();
	refresh();
	attron(COLOR_PAIR(CONTROL_BAR));

    for (auto it = vec_grid.begin(); it < vec_grid.end(); ++it) {
        mvprintw(it->row + 1, it->column + 1, " ");
    }

    if (!run_state) {
        str_action = "  Prev:\'a\'   Play:\'space\'   Next:\'e\'";
    }

    string str_info = format(" | Steps:{} | # of cells alive:{}", to_string(step_count), vec_grid.size());
    // int l = x_max - str_info.length() - str_action.length();
    // str_action.append(l, ' ');
    mvprintw(0, 0, str_action.c_str());
    printw(str_info.c_str());
    attroff(COLOR_PAIR(CONTROL_BAR));

	refresh();
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

        if (neighbour == 2 || neighbour == 3) {
            new_vec_grid.push_back(*it);
        }
    }

    for (auto it = potential_new_cells.begin(); it != potential_new_cells.end(); ++it) {
        if (it->second == 3) {
            new_vec_grid.push_back(it->first);
        }
    }

    return new_vec_grid;
}