#pragma once
#ifndef _FILE_SUPPORT_H
#define _FILE_SUPPORT_H

/**Funkcja odczytuje z pliku przykladowe sudoku
@param pointer wskaznik na tablice sudoku
@param pointerBO wskaznik na tablice bool(ktora zawiera informacje czy mozna nadpisac cyfre)
@param number_of_file nazwa pliku
*/
void reading(char *pointer, bool *pointerBO, char *number_of_file);

/**Funkcja zapisuje do pliku przykladowe sudoku
@param pointer wskaznik na tablice sudoku
@param pointerBO wskaznik na tablice bool(ktora zawiera informacje czy mozna nadpisac cyfre)
@param number_of_file nazwa pliku
*/
void saving(char *pointer, bool *pointerBO, char *number_of_file);

/**Funkcja czysci plik do zapisu
@param number_of_file nazwa pliku
*/
void cleaning(char *number_of_file);


#endif