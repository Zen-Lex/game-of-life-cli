#ifndef PARSER_HPP
#define PARSER_HPP

#include <vector>
#include <string>

using namespace std;

constexpr int gridSize = 40;

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
vector<cell> create_grid_from_rle(string filename);

#endif // PARSER_HPP