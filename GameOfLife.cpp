#include "headers/gameoflife.hpp"
#include "headers/grid.hpp"
#include "headers/bool_grid.hpp"
#include "headers/parser.hpp"
#include "headers/menu.hpp"

GameOfLife::GameOfLife() {
    menu = new Menu(*this);
    grid = new Grid();
}

GameOfLife::~GameOfLife() {
    delete menu;
    delete grid;
}

void GameOfLife::init_simulation() {
    stop_sim = false;

    if (grid->get_step_count() == 0) {
        vec_grid.clear();
        history.clear();
        vec_grid = create_grid_from_rle(filename);
        getmaxyx(stdscr, x_screen_size, y_screen_size);
    }

    grid->printGrid(vec_grid, run_state, x_screen_size, y_screen_size);

    if (grid->get_step_count() == 0 || run_state) {
        run_state = true;
        start_timer();
    }
    
    while(!stop_sim) {
        run();
    }

    menu->show();
}

void GameOfLife::end_simulation() {
    stop_timer();
    curs_set(1);
    endwin();
    exit(0);
}

void GameOfLife::stop_timer() {
    t.stop();
}

void GameOfLife::start_timer() {
    t.setInterval([&]() {
        next();
    }, step_duration * 1000);
}

void GameOfLife::run() {
    int c = getch();
    if (c == ERR) {
        return;
    }

    if (c == 'r') { // Quit
        stop_timer();
        stop_sim = true;
    }
    else if (c == ' ') {  // Pause/Resume simulation
        run_state = !run_state;
        if (run_state) {
            start_timer();
        }
        else {
            stop_timer();
        }
        grid->printGrid(vec_grid, run_state, x_screen_size, y_screen_size);
    }
    else if (c == 'e') {  // Next step
        if (!run_state) next();
    }
    else if (c == 'q') {  // Previous step
        if (!run_state) prev();
    }
    else {
        grid->update_offset(c);
        grid->printGrid(vec_grid, run_state, x_screen_size, y_screen_size);
    }
}

void GameOfLife::next() {
    history.insert(history.begin(), vec_grid);
    history.resize(history_size);
    vec_grid = grid->compute_next_step(vec_grid);
    grid->increase_step_count();
    grid->printGrid(vec_grid, run_state, x_screen_size, y_screen_size);
}

void GameOfLife::prev() {
    if (run_state || history.empty() || grid->get_step_count() <= 0) return;
    vec_grid = history.at(0);
    history.erase(history.begin());
    grid->decrease_step_count();
    grid->printGrid(vec_grid, run_state, x_screen_size, y_screen_size);
}

Menu GameOfLife::get_menu() {
    return *menu;
}

Grid* GameOfLife::get_grid() {
    return grid;
}