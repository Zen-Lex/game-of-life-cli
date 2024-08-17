#ifndef GRID_HPP
#define GRID_HPP

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

#include "parser.hpp"

#define COLOR_RESET "\033[0m"
#define CONTROL_BAR 1

using namespace std;

class Grid {
private:
    int GRID_LIMIT = 1000;
    int x_offset = 0;
    int y_offset = 0;
    int step_count = 0;

    bool off_limits(cell cell);

public:
    Grid();
	~Grid();

    void update_offset(char c);
    void printGrid(vector<cell> vec_grid, bool run_state, int x_max, int y_max);
    vector<cell> compute_next_step(vector<cell> vec_grid);

    int get_step_count() const { return step_count; }
    void set_step_count(int count) { step_count = count; }
	void decrease_step_count() {--step_count; }
	void increase_step_count() {++step_count; }
};

#endif // GRID_HPP
