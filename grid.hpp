#ifndef GRID_HPP
#define GRID_HPP

#include <vector>
#include <string>

using namespace std;

constexpr int gridSize = 40;
extern bool grid[gridSize+1][gridSize+1];

// Function declarations
void parse_line(string line);
void determine_size(string line);
void create_grid_from_rle(string filename);

#endif // GRID_HPP