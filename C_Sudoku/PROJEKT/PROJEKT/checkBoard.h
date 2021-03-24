#pragma once
#ifndef _CHECKBOARD_H
#define _CHECKBOARD_H

/**Funkcja sprawdza, czy tablica sudoku jest dobrze wypelniona
@param pointer wskaznik na tablice sudoku
@return true, gdy prawidlowo wypelnione
@return false, gdy zle wypelnione
*/
bool checking(char *pointer);

/**Funkcja sprawdza, czy kolumny sudoku sa dobrze wypelnione
@param pointer wskaznik na tablice sudoku
@return true, gdy prawidlowo wypelnione
@return false, gdy zle wypelnione
*/
bool checkingColumns(char *pointer);

/**Funkcja sprawdza, czy wiersze sudoku sa dobrze wypelnione
@param pointer wskaznik na tablice sudoku
@return true, gdy prawidlowo wypelnione
@return false, gdy zle wypelnione
*/
bool checkingRows(char *pointer);

/**Funkcja sprawdza, czy kwadraty w sudoku sa dobrze wypelnione
@param pointer wskaznik na tablice sudoku
@return true, gdy prawidlowo wypelnione
@return false, gdy zle wypelnione
*/
bool checkingSquares(char *pointer);


#endif