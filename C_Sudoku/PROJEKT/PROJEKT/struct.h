#pragma once
#ifndef _STRUCT_H
#define _STRUCT_H

/**Tablica sudoku*/
typedef struct
{
	char table_of_numbers[90]; ///< tablica liczb w sudoku
	bool table_of_bool[90]; ///< tablica bool (ktora zawiera informacje, czy mozna nadpisac cyfre)
} sudoku_table;


#endif