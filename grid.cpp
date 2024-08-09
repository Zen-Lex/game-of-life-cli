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
void create_grid_from_rle(string filename);

// const int gridSize = 40;
const int x_gridsize = 45;
const int y_gridsize = 45;
bool grid[gridSize+1][gridSize+1] = {};

int current_row = 3;
int current_column = 3;
string number = "";
string remain = "";

void parse_line(string line) {

	while(!line.empty()) {
		line = remain + line;
		auto end_row = line.find('$');

		if (end_row == -1) {
			end_row = line.find('!');
		}

		if (end_row == -1) {
			remain = line;
			break;
		}
		
		for (auto i = 0; i < end_row; i++) {
			auto c = line.at(i);

			if (c >= '0' && c <= '9') {
				number.append(1, c);
			}
			else if (c == 'b' || c == 'o') {
				if (!number.empty()) {
					for (auto j = current_column; j < current_column + stoi(number); j++) {
						grid[current_row][j] = (c == 'b' ? false : true);
					}

					current_column += stoi(number);
					number.clear();
				}
				else {
					grid[current_row][current_column] = (c == 'b' ? false : true);
					current_column++;
				}
			
			}
		}
		if (!number.empty()) {
			current_row++;
			number.clear();
		}
		line = line.substr(end_row + 1);
		current_row++;
		current_column = 3;
		remain = "";
	}
}

void determine_size(string line) {
	/* line.erase(std::remove(line.begin(), line.end(), ' '), line.end());
	string x_size_str = line.substr(0, line.find(','));
	string y_size_str = line.substr(line.find(',')+1);

	x_gridsize = stoi(x_size_str.substr(2));
	y_gridsize = stoi(y_size_str.substr(2)); */
}

void create_grid_from_rle(string filename) {
	ifstream readfile(filename);
	string line;

	while (getline(readfile,line)) {
		stringstream str(line);

		/* if (line.starts_with('#')) {
			continue;
		} */

		if (line.starts_with('x')) {
			// determine_size(line);
		}
		else {
			parse_line(line);
		}
			
	}

	for (int i = 0; i < x_gridsize; i++) {
		for (int j = 0; j < y_gridsize; j++) {
			grid[i][j] ? cout << "0" : cout << ".";
		}
		cout << "\n";
	}
}

/* void parse_rle(bool grid[x_gridsize+1][gridSize+1], string line) {

} */