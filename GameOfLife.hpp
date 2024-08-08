#ifndef GAME_OF_LIFE_HPP
#define GAME_OF_LIFE_HPP

#include <vector>
#include <string>

using namespace std;

const int gridSize = 40;
#define COLOR_RESET "\033[0m"
#define CONTROL_BAR 1

extern int step_count;
extern bool run_state;
extern bool grid[gridSize+1][gridSize+1];

// Function declarations
void run(bool grid[gridSize+1][gridSize+1], int x_max, int y_max);
void printGrid(bool grid[gridSize+1][gridSize+1], int x_max, int y_max);
void compareGrid(bool grid[gridSize+1][gridSize+1], bool gridTwo[gridSize+1][gridSize+1]);
void determineState(bool grid[gridSize+1][gridSize+1]);

#endif // GAME_OF_LIFE_HPP