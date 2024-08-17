#include <ncurses.h>
#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <fstream>
#include <string>
#include <sstream> 
#include <vector>
#include <algorithm>

#include "headers/parser.hpp"

using namespace std;

vector<cell> parse_line(string line, vector<cell> grid);
vector<cell> create_grid_from_rle(string filename);

const int x_gridsize = 45;
const int y_gridsize = 45;

int current_row = 0;
int current_column = 0;

string number = "";
string remain = "";

vector<cell> parse_line(string line, vector<cell> grid) {

	for (auto it = line.begin(); it < line.end(); ++it) {
		auto c = *it;

		if (c == '!') {
			return grid;
		}

		if (c == '$') {
			if (!number.empty()) {
				current_row += stoi(number) - 1;
				number.clear();
			}

			current_row++;
			current_column = 0;
			remain = "";
			continue;
		}
		
		if (c >= '0' && c <= '9') {
			number.append(1, c);
		}
		else if (c == 'b') {
			current_column += number.empty() ? 1 : stoi(number);
			number.clear();
		}
		else if (c == 'o') {
			int max_column = current_column + (number.empty() ? 1 : stoi(number));

			for (auto i = current_column; i < max_column; i++) {
				grid.push_back(cell{current_row, i});
			}

			current_column = max_column;
			number.clear();
		}
	}

	return grid;
}

vector<cell> create_grid_from_rle(string filename) {
	string line;
	vector<cell> grid;
	ifstream readfile(filename);

	number = "";
	remain = "";
	current_row = 0;
	current_column = 0;

	while (getline(readfile,line)) {
		stringstream str(line);

		if (line.starts_with('#')) {
			continue;
		}

		if (line.starts_with('x')) {
			// determine_size(line);
		}
		else {
			grid = parse_line(line, grid);
		}	
	}

	return grid;
}