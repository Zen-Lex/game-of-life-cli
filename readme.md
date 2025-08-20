# Conway's Game of Life

## Compile
Compile with `g++-13 -std=c++20 project.cpp gameoflife.cpp grid.cpp menu.cpp parser.cpp -fsanitize=address -lncurses -pthread -o build/project`
Launch with `./build/project`

## Rules
Conway's Game of Life follows a set of simple rules that determine how the grid evolves over time. Each cell in the grid can either be alive or dead. The following rules apply to each cell based on the state of its eight neighbors:

    Underpopulation: Any live cell with fewer than two live neighbors dies.
    Survival: Any live cell with two or three live neighbors survives to the next generation.
    Overpopulation: Any live cell with more than three live neighbors dies.
    Reproduction: Any dead cell with exactly three live neighbors becomes a live cell.

These rules are applied simultaneously to every cell in the grid, producing the next generation of the grid based on the current state.


## Game Controls
Once the simulation is running, you can control the simulation with the following keys:

    - 'space': Pause/Resume the simulation.
    - 'e': Advance to the next step (when paused).
    - 'q': Go back to the previous step (when paused).
    - Arrow Keys (or 'wasd'): Move the view of the grid.
    - 'r: Exit the simulation.

## Custimization

### Loading Patterns

You can load predefined patterns from RLE files. Place your RLE files in the rle/ directory and modify the filename in the simulation settings to load a specific pattern.

### Adjusting Simulation Speed

You can modify the step duration of the simulation through the settings menu. The default is set in seconds, and the speed will affect how quickly the grid evolves.

### Grid History Size

You can configure how many previous states of the grid are stored for navigation in the settings. This determines how many steps back you can move in the simulation.

### Return to Menu & Resume Simulation

At any point during the simulation, you can press the 'r' key to return to the main menu. In the menu, you can change options such as the RLE file being used, the grid history size, or the step duration. After modifying the settings, you can resume the simulation, and the changes will take effect.

## Credits
The algorithm was based on the project of Mario Talevski
https://github.com/MarioTalevski/game-of-life?utm_source=pocket_shared

Readme created with ChatGPT