#ifndef GAMEOFLIFE_HPP
#define GAMEOFLIFE_HPP

#include <vector>
#include <string>

#include "grid.hpp"

using namespace std;

#define COLOR_RESET "\033[0m"
#define CONTROL_BAR 1

extern int step_count;
extern bool run_state;

// Function declarations
void update_offset(char c);
void printGrid(vector<cell> vec_grid, int x_max, int y_max);
vector<cell> compute_next_step(vector<cell> vec_grid);
bool off_limits(cell cell);

#endif // GAME_OF_LIFE_HPP