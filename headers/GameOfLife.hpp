#ifndef GAMEOFLIFE_HPP
#define GAMEOFLIFE_HPP

#include <ncurses.h>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "parser.hpp"
#include "menu.hpp"
#include "timercpp.h"

class Menu;
class Grid;

class GameOfLife {
    private:
        std::string filename = "rle/gosperglidergun.rle";
        float step_duration = 0.2;
        Timer t = Timer();
        std::vector<cell> vec_grid;
        int history_size = 20;
        std::vector<std::vector<cell>> history;
        int x_screen_size, y_screen_size;
        bool stop_sim = false;
        bool run_state = false;

        Menu* menu;
        Grid* grid;

        void run();
        void next();
        void prev();
        void start_timer();
        void stop_timer();

    public:
        GameOfLife();
        ~GameOfLife();
        void init_simulation();
        void end_simulation();
        string get_filename() { return filename; }
        void set_filename(std::string path) { filename = path; }
        float get_duration() { return step_duration; }
        void set_duration(float time) { step_duration = time; }
        int get_history_size() { return history_size; }
        void set_history_size(int size) { history_size = size; }
        Menu get_menu();
        Grid* get_grid();
};

#endif
