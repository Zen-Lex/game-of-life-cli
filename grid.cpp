#include <ncurses.h>
#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <fstream>
#include <string>
#include <sstream> 
#include <vector>
#include <algorithm>

#include "grid.hpp"

using namespace std;

void parse_line(string line);
void determine_size(string line);
vector<cell> create_grid_from_rle(string filename);

const int x_gridsize = 45;
const int y_gridsize = 45;

int current_row = 0;
int current_column = 0;
string number = "";
string remain = "";

vector<cell> vec_grid;

void parse_line(string line) {
	for (auto it = line.begin(); it < line.end(); ++it) {
		auto c = *it;

		if (c == '!') {
			break;
		}

		if (c == '$') {
			if (!number.empty()) {
				current_row++;
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
				vec_grid.push_back(cell{current_row, i});
			}

			current_column = max_column;
			number.clear();
		}
	}
}


void determine_size(string line) {
	/* line.erase(std::remove(line.begin(), line.end(), ' '), line.end());
	string x_size_str = line.substr(0, line.find(','));
	string y_size_str = line.substr(line.find(',')+1);

	x_gridsize = stoi(x_size_str.substr(2));
	y_gridsize = stoi(y_size_str.substr(2)); */
}

vector<cell> create_grid_from_rle(string filename) {
	ifstream readfile(filename);
	string line;

	while (getline(readfile,line)) {
		stringstream str(line);

		if (line.starts_with('#')) {
			continue;
		}

		if (line.starts_with('x')) {
			// determine_size(line);
		}
		else {
			parse_line(line);
		}	
	}

	return vec_grid;
}