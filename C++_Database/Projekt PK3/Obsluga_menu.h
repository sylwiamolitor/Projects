#pragma once
#ifndef _OBSLUGA_MENU_H
#define _OBSLUGA_MENU_H

#include "Header.h"

#include <iostream>
#include <fstream>

/**Funkcja obsluguje kontakt z uzytkownikiem w menu.
@param pHead wskaznik na liste wskaznikow na obiekty
*/
void obsluga_menu(Lista *pHead);

/**Funkcja zapisuje baze do pliku o podanej nazwie.
@param pHead wskaznik na liste wskaznikow na obiekty
@param nazwa_pliku nazwa pliku, do ktorego bedziemy zapisywac.
*/
void zapisz_do_pliku(Lista *pHead, std::string nazwa_pliku);

/**Funkcja wypisuje baze do okna konsoli.
@param pHead wskaznik na liste wskaznikow na obiekty
*/
void wypisz_baze(Lista *pHead);

/**Funkcja wczytuje podstawowe dane(nazwe, rok, autora, cene) podane przez uzytkownika.
@param pHead wskaznik na liste wskaznikow na obiekty
@param nazwa nazwa obiektu
@param rok_powstania rok powstania obiektu
@param autor autor obiektu
@param cena cena obiektu
*/
void wczytaj_podstawowe_dane(Lista *pHead, std::string &nazwa, std::string &rok_powstania, std::string &autor, std::string &cena);

/**Funkcja odczytuje z pliku o podanej nazwie baze.
@param pHead wskaznik na liste wskaznikow na obiekty
@param nazwa_pliku nazwa pliku, z ktorego bedziemy czytac.
*/
void odczytaj_z_pliku(Lista *pHead, std::string nazwa_pliku);

#endif