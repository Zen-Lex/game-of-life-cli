#include "headers/bool_grid.hpp"
#include "headers/parser.hpp"

#define COLOR_RESET "\033[0m"
#define CONTROL_BAR 1

GridB::GridB() {
    x_offset = 0;
    y_offset = 0;
    step_count = 0;
}


void GridB::update_offset(char c) {
    if (c == 'd') {
        --x_offset;
    }
    else if (c == 'q') {
        ++x_offset;
    }
    else if (c == 'z') {
        ++y_offset;
    }
    else if (c == 's') {
        --y_offset;
    }
}

void GridB::printGridB(vector<bool> bool_grid, bool run_state, int x_max, int y_max) {
    string str_action = "  Pause:'space'";
    erase();
    
    init_pair(CONTROL_BAR, COLOR_BLACK, COLOR_WHITE);
    attron(COLOR_PAIR(CONTROL_BAR));

    for (auto cell = bool_grid.begin(); cell < bool_grid.end(); ++cell) {
        if (*cell) {
            auto pos = std::distance(bool_grid.begin(), cell);
            mvprintw(pos / (bool_grid.size()/2), pos % (bool_grid.size()), " ");
        }
    }

    if (!run_state) {
        str_action = "  Prev:'a'   Play:'space'   Next:'e'";
    }

    string str_info = format("Quit: '0' | Steps:{} | # of cells alive:{}   ", to_string(step_count), bool_grid.size());
    int l = y_max - str_info.length() - str_action.length();
    mvprintw(x_max - 1, 0, str_action.c_str());
    printw(str_info.c_str());
    attroff(COLOR_PAIR(CONTROL_BAR));

    refresh();
}

vector<bool> GridB::compute_next_step(vector<bool> bool_grid, int grid_size) {
    vector<bool> new_bool_grid = bool_grid;

    for (auto cell = bool_grid.begin(); cell < bool_grid.end(); ++cell) {
        int neighbour = 0;
        int cell_r = distance(bool_grid.begin(), cell) / grid_size;
        int cell_c = distance(bool_grid.begin(), cell) % grid_size;
        
        for (int r = -1; r < 2; ++r) {
            for (int c = -1; c < 2; ++c) {
                
                if (r == 0 && c == 0) {
                    continue;
                }

                if (cell_r + r < 0 || cell_r + r > grid_size) {
                    continue;
                }

                if (cell_c + c < 0 || cell_c + c > grid_size) {
                    continue;
                }

                if (bool_grid.at(cell_r + r*grid_size + cell_c + c)) {
                    ++neighbour;
                }
            }
        }

        if (*cell && (neighbour < 2 || neighbour > 3)) {
            new_bool_grid.at(cell_r*grid_size + cell_c) = false;
            continue;
        }

        if (neighbour == 2 || neighbour == 3) {
             new_bool_grid.at(cell_r + cell_c) = true;
        }
    }
    

    return new_bool_grid;
}

bool GridB::off_limits(int r, int c) {
    int min = (GRID_LIMIT - 1) / -2;
    int max = GRID_LIMIT / 2;
    return !(r > min && r < max && c > min && c < max);
}
