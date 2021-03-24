#include "Header.h"
#include "Obsluga_menu.h"


#include <iostream>
#include <string>
#include <fstream>
#include <sstream> 




/* Wymagania
- 3 poziomy hierarchii klas
- jedna wspolna klasa bazowa
- uzywanie klas abstrakcyjnych (czysto wirtualnych) "= przekreslone koleczko" to specyfikator
- pelen polimorfizm
- zapis i odczyt do i z pliku (ifstream, ofstream) i przesuniecia bitowego
- */





int main(int argc, char **argv)
{
	Lista ob;
	Lista *pHead = &ob;
	
	std::string nazwa_pliku = "Baza danych.txt"; 
	if (argc >= 2)
	{
		nazwa_pliku = argv[1];
	}

	pHead->pD = nullptr;
	pHead->pM = nullptr;
	pHead->pO = nullptr;
	pHead->pR = nullptr;
	pHead->pS = nullptr;
	pHead->pZ = nullptr;
	odczytaj_z_pliku(pHead, nazwa_pliku);
	obsluga_menu(pHead);
	zapisz_do_pliku(pHead, nazwa_pliku);


}
