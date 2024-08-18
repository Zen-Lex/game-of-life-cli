#ifndef BOOL_GRID_HPP
#define BOOL_GRID_HPP

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

using namespace std;

class GridB {
private:
    int GRID_LIMIT = 1000;
    int x_offset = 0;
    int y_offset = 0;
    int step_count = 0;

    bool off_limits(int r, int c);

public:
    GridB();

    void update_offset(char c);
    void printGridB(vector<bool> bool_grid, bool run_state, int x_max, int y_max);
    vector<bool> compute_next_step(vector<bool> bool_grid, int grid_size);

    int get_step_count() const { return step_count; }
    void set_step_count(int count) { step_count = count; }
	void decrease_step_count() {--step_count; }
	void increase_step_count() {++step_count; }
};

#endif
