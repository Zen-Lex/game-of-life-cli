#ifndef GRID_HPP
#define GRID_HPP

#include <vector>
#include <string>

using namespace std;

constexpr int gridSize = 40;
// extern bool grid[gridSize+1][gridSize+1];

struct cell {
	int row;
	int column;

	bool operator==(const cell& other) const {
        return row == other.row && column == other.column;
    }

	bool operator<(const cell& other) const {
        if (row < other.row) {
            return true;
        } else if (row == other.row) {
            return column < other.column;
        } else {
            return false;
        }
    }
};

// Function declarations
vector<cell> parse_line(string line, vector<cell> grid);
void determine_size(string line);
vector<cell> create_grid_from_rle(string filename);

#endif // GRID_HPP