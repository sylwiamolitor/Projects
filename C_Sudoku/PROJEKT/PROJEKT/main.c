#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>  

#include "checkBoard.h"
#include "file_support.h"
#include "gameplay.h"
#include "solution.h"
#include "struct.h"


int main(int argc, char **argv)
{
	char *number_of_file = "1.txt";
	if (argc >= 2)
	{
		number_of_file = argv[1];
	}

	sudoku_table sudoku;
	char *pointer = malloc(sizeof(sudoku.table_of_numbers));
	bool *pointerBO = malloc(sizeof(sudoku.table_of_bool));

	contactWithUser(pointer, pointerBO, number_of_file);
	cleaning(number_of_file);
	saving(pointer, pointerBO, number_of_file);

	free(pointer);
	free(pointerBO);

}
