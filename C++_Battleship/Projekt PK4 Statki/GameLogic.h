#pragma once
#ifndef _GAMELOGIC_H
#define _GAMELOGIC_H
#include "Interface.h"
#include <fstream>
#include <list>


class Game_Logic
{	
		bool if_ship_there[10][10];/**@param tablica zawierajaca 1, jesli statek jest na podanym miejscu, 0 gdy go nie ma*/
		bool if_ship_shot[10][10];//@param tablica zawierajaca 1, jesli miejsce bylo trafione, 0 gdy nie bylo*/
	public:
		bool is_ship_there(int x, int y);	/**metoda zwracajaca 1, jesli statek jest na podanym miejscu, 0 gdy go nie ma*/
		bool is_ship_there_shot(int x, int y); /**metoda zwracajaca 1,  jesli miejsce bylo trafione, 0 gdy nie bylo*/
		void set_ship(int x, int y); /**metoda ustawiajaca statek na podanym miejscu*/
		void set_empty(int x, int y); /**metoda ustawiajaca puste mejsce pod zapis*/
		void shoot_ship(int x, int y); /**metoda ustawiajaca statek jako zestrzelony*/


};

class Check_Position : public Game_Logic
{
	public:
		bool Check_If_Ship_Already_There(int y, int x); /**metoda sprawdzajaca czy statek znajduje sie na podanym miejscu*/
		bool Check_If_You_Can_Add_Ship(int y, int x); /**metoda sprawdzajaca czy w dane miejsce mozna dodac statek*/
		
};

class Create_Board : public Check_Position 
{
	
	public:
		Create_Board(); //konstruktor
		bool Check_If_You_Shot_Ship(int y, int x); /**metoda ustawiajaca miejsce na zestrzelone i zwracajaca informacje, czy znajdowal sie tam statek*/
		bool Add_Ship(int y, int x, bool direction, int size); /**metoda dodajaca statek*/
		bool read_file(Create_Board &enemy_board); /**metoda odczytujaca zapis gry z pliku*/
		bool save_to_file(Create_Board enemy_board); /**metoda zapisujaca stan gry do pliku*/
		void AddingShipsByComputer(); /**metoda umozliwiajaca dodawanie statkow przez komputer*/
		void AddingShipsByUser(sf::RenderWindow & window, int base_y, int &licznik1, int &licznik2, int &licznik3, int &licznik4); //metoda umozliwiajaca dodanie statku przez uzytkownika*/
		void clear(); /**metoda czyszczaca plansze pod zapis*/
		

};
class Score : public Check_Position
{
	
		int amount; /**@param amount liczba punktow*/
	public:
		Score() {}; /**konstruktor*/
		virtual void Count(Game_Logic board) = 0; /**metoda liczaca wynik*/
		int GetScore();/**metoda zwracajaca wynik*/
		void SetScore();/**metoda ustawiajaca wynik na 0*/
		void SetScore(int amount);/**metoda ustawiajaca wynik na amount*/
};

class Mine : public Score
{
	
	public:
		Mine() { SetScore(); }; /**konstruktor*/
		void Count(Game_Logic my_board); /**metoda liczaca wynik*/
		
};

class Enemy : public Score
{
	
	public:
		Enemy() { SetScore(); }; /**konstuktor*/
		void Count(Game_Logic enemy_board); /**metoda liczaca wynik*/
	
};
#endif