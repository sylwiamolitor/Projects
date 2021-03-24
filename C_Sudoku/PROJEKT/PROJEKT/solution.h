#pragma once
#ifndef _SOLUTION_H
#define _SOLUTION_H

/**Funkcja sprawdza, czy mozna dodac dana cyfre w dane miejsce
@param x wspolrzedna x miejsca dodania
@param y wspolrzedna y miejsca dodania
@param value cyfra do dodania
@param pointer wskaznik na tablice sudoku
@param helping_pointer wskaznik na pomocnicza tablice
@return true jesli mozna dodac
@return false jesli nie mozna dodac
*/
bool can_add(int x, int y, int value, char *pointer, char *helping_pointer);

/**Funkcja umozliwia przejscie w nastepne miejsce tablicy sudoku
@param x wspolrzedna x miejsca dodania
@param y wspolrzedna y miejsca dodania
@param pointer wskaznik na tablice sudoku
@param helping_pointer wskaznik na pomocnicza tablice
@return true jesli koniec tablicy
*/
bool next_area(int x, int y, char *pointer, char *helping_pointer);

/**Funkcja wypelnia sudoku
@param x wspolrzedna x miejsca dodania
@param y wspolrzedna y miejsca dodania
@param pointer wskaznik na tablice sudoku
@param helping_pointer wskaznik na pomocnicza tablice
@return true jesli dodano element
@return false jesli nie dodano elementu
*/
bool solve_it(int x, int y, char *pointer, char *helping_pointer);

#endif