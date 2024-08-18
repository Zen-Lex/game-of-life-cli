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

vector<bool> parse_line(string line, vector<bool> grid, int size, int line_nb) {

	for (auto it = line.begin(); it < line.end(); ++it) {
		auto c = *it;

		if (c == '!') {
			if (grid.size() < size*size) {
				int start = grid.size();
				for (auto i = start; i < size*size; i++) {
					grid.push_back(false);
				}
			}

			return grid;
		}

		if (c == '$') {
			if (!number.empty()) {
				number.clear();
			}

			if (grid.size() < size*line_nb + 1) {
				int start = grid.size();
				for (auto i = start; i < size*line_nb; i++) {
					grid.push_back(false);
				}
			}

			remain = "";
			continue;
		}
		
		if (c >= '0' && c <= '9') {
			number.append(1, c);
		}
		else if (c == 'b') {
			int start = grid.size();
			for (auto i = start; i < start + stoi(number); i++) {
				grid.push_back(false);
			}

			number.clear();

		}
		else if (c == 'o') {
			int start = grid.size();
			for (auto i = start; i < start + stoi(number); i++) {
				grid.push_back(true);
			}

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
		else {
			grid = parse_line(line, grid);
		}	
	}

	return grid;
}

//convert vec grid to bool grid
vector<bool> vtob_grid(vector<cell> vec_grid) {
	int min_row = vec_grid.at(0).row;
	int max_row = vec_grid.at(0).row;
	int min_column = vec_grid.at(0).column;
	int max_column = vec_grid.at(0).column;

	vector<bool> bool_grid;

	for (auto it = vec_grid.begin(); it < vec_grid.end(); ++it) {
		if (it->row < min_row) {
			min_row = it->row;
		}

		if (it->row > max_row) {
			max_row = it->row;
		}

		if (it->column < min_column) {
			min_column = it->column;
		}

		if (it->column > max_column) {
			max_column = it->column;
		}
	}

	int rows = min_row*-1 + max_row + 1;
	int columns = min_column*-1 + max_column + 1;
	int max_size = max(rows, columns);

	for (int i = 0; i <= max_size*max_size; ++i) {
		if (find(vec_grid.begin(), vec_grid.end(), cell{(i / max_size) - max_size/2, (i % max_size)}) != vec_grid.end()) {
			bool_grid.push_back(true);
		}
		else {
			bool_grid.push_back(false);
		}
	}

	return bool_grid;
}