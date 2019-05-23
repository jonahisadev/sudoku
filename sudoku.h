#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <signal.h>

// Use x and y coordinates to access the table
#define POINT(x, y) table[((y * 9) + x)]

// Table structure
struct Table_t {
	int* table;
	int* unsovled_cells;
	int unsovled_cells_size;
};
typedef struct Table_t Table;

// Create and load table from file
Table* load_table(const char* filename) {
	Table* table = malloc(sizeof(Table));
	table->table = malloc(sizeof(int) * 9 * 9);
	table->unsovled_cells = malloc(sizeof(int) * 9 * 9);
	table->unsovled_cells_size = 0;

	// Load table
	FILE* f = fopen(filename, "r");
	if (!f) {
		printf("Can't open file '%s'\n", filename);
		exit(1);
	}
	char c;
	int index = 0;
	while ((c = getc(f)) != EOF) {
		if (c == '\n')
			continue;
		
		int val = c - '0';
		if (val == 0)
			table->unsovled_cells[table->unsovled_cells_size++] = index;
		table->table[index++] = c - '0';
	}
	fclose(f);

	return table;
}

// Check if arr contains duplicate ints
bool contains_duplicates(int* arr) {
	for (int i = 0; i < 9; i++) {
		int val = arr[i];

		// Skip zeros
		if (val == 0)
			continue;
		for (int j = 0; j < 9; j++) {
			if (val == arr[j] && j != i) {
				return true;
			}
		}
	}
	
	return false;
}

// Check if row contains duplicates
bool check_row(Table* table, int index) {
	int row_num = index / 9;
	int row[9];
	for (int i = 0; i < 9; i++) {
		row[i] = table->POINT(i, row_num);
	}
	return !contains_duplicates(row);
}

// Check if column contains duplicates
bool check_col(Table* table, int index) {
	int col_num = index % 9;
	int col[9];
	for (int i = 0; i < 9; i++) {
		col[i] = table->POINT(col_num, i);
	}
	return !contains_duplicates(col);
}

// Check if the square contains duplicates
bool check_square(Table* table, int index) {
	int sqr_x = (index % 9) / 3;
	int sqr_y = (index / 9) / 3;
	int sqr[9];

	int sqr_index = 0;
	for (int i = sqr_y * 3; i < (sqr_y + 1) * 3; i++) {
		for (int j = sqr_x * 3; j < (sqr_x + 1) * 3; j++) {
			sqr[sqr_index++] = table->POINT(j, i);
		}
	}
	
	return !contains_duplicates(sqr);
}

// Run above checks on one cell
bool check_cell(Table* table, int index) {
	if (table->table[index] == 0 || table->table[index] > 9)
		return false;
	return check_row(table, index) && check_col(table, index) && check_square(table, index);
}

// Backtrack algorithm
void solve_table(Table* table) {
	bool solved = false;
	int unsolved_index = 0;
	int table_index = 0;

	mainLoop:
	while (!solved) {
		table_index = table->unsovled_cells[unsolved_index];

		// Increment cell until the check works
		while (!check_cell(table, table_index)) {
			if (table->table[table_index] >= 9) {
				table->table[table_index] = 0;
				unsolved_index--;
				table_index = table->unsovled_cells[unsolved_index];
				table->table[table_index]++;
				goto mainLoop;
			}
			table->table[table_index]++;
		}

		unsolved_index++;
		if (unsolved_index >= table->unsovled_cells_size) {
			solved = true;
		}
	}
}

// Print the table
void print_table(Table* table) {
	printf("---------------------\n");
	for (int i = 0; i < 9; i++) {
		printf("| ");
		for (int j = 0; j < 9; j++) {
			printf("%d ", table->POINT(j, i));
		}
		printf("|\n");
	}
	printf("---------------------\n");
}

// Print unsolved cells (DEBUG)
void print_unsolved_cells(Table* table) {
	printf("[ ");
	for (int i = 0; i < table->unsovled_cells_size; i++) {
		printf("%d ", table->unsovled_cells[i]);
	}
	printf("]\n");
}

// Delete table
void free_table(Table* table) {
	free(table->table);
	free(table);
}