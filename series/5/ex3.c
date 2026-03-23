#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool is_attacked (int* target, int queen_x, int queen_y) {
	return target[0] == queen_x // same row
	    || target[1] == queen_y // same column
	    || abs(target[0] - queen_x) == abs(target[1] - queen_y); // same diagonal
}

int main () {
	int size = 0; // The size of the chessboard (size x size)
	int target[2]; // The target cell to check for being attacked by the queens, represented as (x, y)
	int n_queens = 0; // Number of queens
	
	// Read the state of the chessboard from standard input formatted as follows:
	// N (the size of the chessboard)
	// x y (the coordinates of the target cell)
	// M (the number of queens) -> not really required since we can read until EOF, but it is part of the input format demanded by the problem statement
	// x1 y1 (the coordinates of the first queen)
	// x2 y2 (the coordinates of the second queen)
	// ...
	char input_line[64];
	
	fgets(input_line, sizeof(input_line), stdin); // Read the first line to get the size of the chessboard
	sscanf(input_line, "%d", &size);
	printf("Board size: %d\n", size);
	int (*board)[size] = malloc(size * sizeof(*board)); // Allocate memory for the board after reading the size of the chessboard
	
	fgets(input_line, sizeof(input_line), stdin); // Read the second line to get the target cell coordinates
	sscanf(input_line, "%d %d", &target[0], &target[1]);
	printf("Target: (%d, %d)\n", target[0], target[1]);
	
	fgets(input_line, sizeof(input_line), stdin); // Read the third line to get the number of queens
	sscanf(input_line, "%d", &n_queens);
	printf("Number of queens: %d\n", n_queens);
	int (*queen_coords)[n_queens] = malloc(2 * sizeof(*queen_coords)); // Allocate memory for the queens' coordinates after reading the number of queens
	
	int line_count = 0;
	while (fgets(input_line, sizeof(input_line), stdin) != NULL) {
		sscanf(input_line, "%d %d", &queen_coords[0][line_count], &queen_coords[1][line_count]);
		line_count++;
	}
	// for (int i = 0; i < n_queens; i++) {
	// 	printf("Queen %d: (%d, %d)\n", i + 1, queen_coords[0][i], queen_coords[1][i]);
	// }
	printf("\n");
	
	// Populate the board with the queens' positions
	// Note: Step not required per se as we can already check for attacks using the queen coordinates, however makes it easier to create a helper function to check for attacks as well as recomputing for another target cell if needed or even displaying the board
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			board[i][j] = 0;
		}
	}
	// Place the queens on the board
	for (int i = 0; i < n_queens; i++) {
		int x = queen_coords[0][i];
		int y = queen_coords[1][i];
		board[x][y] = 1;
	}
	// Display the board
	for (int i = 0; i < size; i++) {
		printf (" ");
		for (int j = 0; j < size; j++) {
			if (board[i][j] == 1) printf("Q ");
			else if (i == target[0] && j == target[1]) printf("T ");
			else printf("· ");
		}
		printf("\n");
	}
	printf("\n");

	int count = 0;
	for (int i = 0; i < n_queens; i++) {
		if (is_attacked(target, queen_coords[0][i], queen_coords[1][i]))
			count++;
	}
	printf("Threats: %d\n", count);

	free(board);
	free(queen_coords);
	return 0;
}
