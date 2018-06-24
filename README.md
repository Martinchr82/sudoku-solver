# sudoku-solver

Description
----
A simple sudoku solver that uses some basic techniques involving pencil marks as well as the trial and error procedure with backtracking in order to find the solution to the sudoku puzzle. The solver halts if it finds the first solution, or determines that there are no solutions to the given sudoku puzzle.

Usage
----
Clone the repository into your local directory.
Then one may use the CMake to generate the platform-independent project files.
For example, for Unix-like systems
```bash
mkdir build
cd build
cmake ../
make
```
These commands will generate the SudokuSolver library and a SudokuSolverBenchmark executable in build subdirectory.
See the SudokuSolverBenchmark.cxx for the example of usage of the solver library.

The SudokuSolverBenchmark executable will solve the sudoku puzzle hardcoded into its source code if run with no arguments.
If supplied with filename containing sudoku puzzles the program will try to solve each of them.
Additionally the program will output the average time it takes to solve the sudoku puzzle from the given set.
```bash
usage: SudokuSolverBenchmark [filename]
```

The **sets** folder contains some files with sudoku puzzles, found on the internet.