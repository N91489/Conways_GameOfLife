Interactive implementation of Conway's Game of Life using C &amp; SDL

# Overview
This project implements Conway's Game of Life using the Simple DirectMedia Layer (SDL) library. The Game of Life is a cellular automaton devised by the British mathematician John Horton Conway in 1970. It consists of a grid of cells that evolve across discrete time steps according to a set of simple rules based on the states of neighboring cells.

## What is Cellular Automata?
Cellular automata (CA) are discrete, abstract computational systems that have found application in various scientific fields. They consist of a grid of cells, each of which can be in a finite number of states. The state of a cell at the next time step is determined by a set of rules that consider the states of neighboring cells.

### Rules in Conway's Game of Life
The rules of the game are applied to each cell based on its eight neighbors: the cells that are horizontally, vertically, or diagonally adjacent. The state of each cell in the next generation is determined by counting the number of live neighbors.

* Any live cell with fewer than two live neighbors dies (underpopulation).
* Any live cell with two or three live neighbors lives on to the next generation  (survival).
* Any live cell with more than three live neighbors dies (overpopulation).
* Any dead cell with exactly three live neighbors becomes a live cell (reproduction).
***
# Project Features
This SDL implementation of Conway's Game of Life includes several features designed to enhance the user experience

## Simulation Features

* Random Initial Grid: The initial state of the grid is randomly generated, providing a unique starting point for each simulation.

* Pause/Play Functionality: Users can pause and resume the simulation at any time using the `p` key. This allows for detailed inspection of the grid's state at any given moment.
  
* Interactive Grid: Users can `left click` on the grid to toggle the state of individual cells, enabling the creation of custom initial patterns.
  
* Simulation Speed Control: The speed of the simulation can be adjusted using the `up` and `down` arrow keys.

* 2x Scale Simulation: The simulation runs at twice the normal screen resolution, providing a large simulation area that extends beyond the visible screen, enhancing the visual effect. This can also prolong the simulation as cells that move out of the screen can still interact with those on the screen.
 
* Background Music: The application plays background music using SDL's audio functionality, with functionality to loop the audio track seamlessly.

## Efficiency Features
* Adaptive Screen Resolution: The application obtain the screen resolution of the user's display, allowing for adaptive and efficient use of screen memory.

* Dynamic Memory Allocation: The grid is dynamically allocated based on the screen size, ensuring optimal memory usage.
  
* Boolean Grid Efficiency: The grid is implemented using boolean values, leading to less consumption of memory.

* Clean Exit and Memory Management: The application ensures all allocated memory is properly freed upon exit, preventing memory leaks.
***

# Installation and Usage

### 1. Clone & enter repository:

Clone the project using:
```bash
git clone https://github.com/N91489/Conways_GameOfLife.git
```
Enter into the project folder using:
```bash
cd Conways_GameOfLife
```

### 2. Build the project:
Ensure you have `gcc`, `clang`, `minigw` or `cygwin` installed on your system. The provided `Makefile` will handle the compilation and linking with the SDL2 library.
```bash
make build
```

### 3. Run the application:
```bash
./CGol
```
### Controls

|Keys| Functions|
|-|-----------------------------|
|p| Pause/Resume the simulation.|
|Left Mouse Button| Toggle the state of a cell.|
|Up Arrow|Increase the simulation speed.|
|Down Arrow| Decrease the simulation speed.|
|q| Quit the application.|
---
# License
This project is licensed under the MIT License - see the [LICENSE](https://github.com/N91489/Conways_GameOfLife/blob/main/LICENSE) file for details.
