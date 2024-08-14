#ifndef PROJECT_HPP
#define PROJECT_HPP

#include <ncurses.h>
#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

#include "gameoflife.hpp"
#include "grid.hpp"
// #include "timercpp.h"

using namespace std;

extern string FILENAME;
extern float STEP_DURATION;

// extern Timer t;
extern vector<cell> vec_grid;
extern vector<vector<cell>> history;
extern int x_screen_size, y_screen_size;

void init_simulation();
void start_timer();
void stop_timer();
void run();
void next();
void prev();
void set_filename(string path);
void end_simulation();

#endif