#include "sudoku.h"

int main(int argc, char** argv) {
	// Require a file to be passed
	if (argc < 2) {
		printf("Please enter a file to read\n");
		exit(1);
	}

	// Create table object
	Table* table = load_table(argv[1]);

	// Print initial table
	printf("Initial table:\n");
	print_table(table);
	printf("\n");

	// Solve the puzzle
	solve_table(table);

	// Print the solved puzzle
	printf("Solved table:\n");
	print_table(table);
	printf("\n");

	// Clean up
	free_table(table);
	return 0;
}