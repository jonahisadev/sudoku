# Sudoku Solver

This is a simple sudoku solver I made in a night when I was
bored. This utilizes an implementation of the backtracking
algorithm, which is a depth-first brute-force algorithm
that eventually finds the correct solution to the puzzle.

## Usage

Compile with the Makefile: `make`
Run like so: `./sudoku tests/evil.sdk`

There are some test puzzles it can solve, so you can
either do those, or create your own. The program
will probably just hang on a puzzle that can't be solved,
but I don't really know, I didn't test it.