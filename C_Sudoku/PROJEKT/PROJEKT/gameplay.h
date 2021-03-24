#pragma once
#ifndef _GAMEPLAY_H
#define _GAMEPLAY_H

/**Funkcja usuwa 10 razy wiecej cyfr od podanej od uzytkownika liczby z wygenerowanej tablicy sudoku
@param pointer wskaznik na tablice sudoku
@param pointerBO wskaznik na tablice bool(ktora zawiera informacje czy mozna nadpisac cyfre)
@param number liczba podana przez uzytkownika
*/
void deleting(char *pointer, bool *pointerBO, char number);

/**Funkcja wypisuje na ekranie konsoli sudoku
@param pointer wskaznik na tablice sudoku
*/
void write_out(char *pointer);

/**Funkcja wpisuje podana przez uzytkownika cyfre do danego miejsca
@param pointer wskaznik na tablice sudoku
@param vertical pionowa wspolrzedna miejsca wpisania cyfry
@param horizontal pozioma wspolrzedna miejsca wpisania cyfry
@param number liczba podana przez uzytkownika
@param pointerBO wskaznik na tablice bool(ktora zawiera informacje czy mozna nadpisac cyfre)
*/
void writeInTheBoard(char *pointer, int vertical, int horizontal, char number, bool *pointerBO);

/**Funkcja generuje przykladowe sudoku o poziomie trudnosci podanym przez uzytkownika
@param pointer wskaznik na tablice sudoku
@param pointerBO wskaznik na tablice bool(ktora zawiera informacje czy mozna nadpisac cyfre)
@param number liczba podana przez uzytkownika
*/
void generateBoard(char *pointer, bool *pointerBO, char number);

/**Funkcja sprawdza, czy sa jakies puste miejsca w sudoku
@param pointer wskaznik na tablice sudoku
@return true gdy istnieja wolne miejsca
@return false gdy nie istnieja wolne miejsca
*/
bool check_empty_spaces(char *pointer);

/**Funkcja umozliwia kontakt z uzytkownikiem
@param pointer wskaznik na tablice sudoku
@param pointerBO wskaznik na tablice bool(ktora zawiera informacje czy mozna nadpisac cyfre)
@param number_of_file nazwa pliku
*/
void contactWithUser(char *pointer, bool *pointerBO, char *number_of_file);

#endif