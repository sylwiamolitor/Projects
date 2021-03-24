#pragma once
#ifndef _OPERACJE_NA_ELEMENTACH_H
#define _OPERACJE_NA_ELEMENTACH_H

#include "Header.h"


/**Funkcja dodaje lub usuwa obiekt o podanych przez uzytkownika parametrach.
@param pHead wskaznik na liste wskaznikow na obiekty
@param nazwa nazwa obiektu
@param rok_powstania rok powstania obiektu
@param autor autor obiektu
@param cena cena obiektu
@param zmienna1 parametr nr 1 charakterystyczny dla podanej klasy
@param zmienna2 parametr nr 2 charakterystyczny dla podanej klasy
@param dodaj_czy_usun wynosi 1, jesli uzytkownik chce dodac obiekt albo 0 jesli chce usunac obiekt
*/
void dodaj_lub_usun_element(Lista *pHead, std::string nazwa, std::string rok_powstania, std::string autor, std::string cena, std::string zmienna1, std::string zmienna2,bool dodaj_czy_usun);




#endif