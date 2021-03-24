

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Interface.h"
#include "GraphicObject.h"
#include "GameLogic.h"
#include <list>
#include <fstream>
//#include <vld.h>


int main()
{ 
	std::list<Button>ButtonList;
	std::list<Button>::iterator iterButton;
	std::list<Button>AdditionalButtons;
	std::list<Button>::iterator iterButton2;
	std::unique_ptr<Create_Board> my_board(new Create_Board());
	std::unique_ptr<Create_Board> enemy_board(new Create_Board());
	if (my_board->read_file((*enemy_board)))
	{
		sf::RenderWindow window(sf::VideoMode(1880, 1000), "Statki!");
		window.clear(sf::Color(0, 0, 0));
		sf::RectangleShape rectangle(sf::Vector2f(225, 100)); 
		rectangle.setPosition(200, 200);
		rectangle.setFillColor(sf::Color(255, 255, 255));
		sf::Font font;
		try
		{
			if(!font.loadFromFile("arial.ttf"))
				throw 0;
		}
		catch (int e)
		{
			std::cout << "Error: brak pliku z czcionka!\n";
		}
		Button przycisk_wyjscia("EXIT", font, 40, sf::Vector2f(1100, 50));
		Button przycisk_nowa_rozgrywka("NOWA ROZGRYWKA", font, 40, sf::Vector2f(1100, 250));
		Button przycisk_wynik_przeciwnika("WYNIK WROGA:", font, 40, sf::Vector2f(1100, 450));
		Button przycisk_twoj_wynik("TWOJ WYNIK:", font, 40, sf::Vector2f(1100, 650));
		Button przycisk_zapisz_gre("ZAPISZ GRE", font, 40, sf::Vector2f(1100, 850));
		Button przycisk_wczytaj("WCZYTAJ", font, 40, sf::Vector2f(550, 750));
		Button przycisk_stworz("STWORZ", font, 40, sf::Vector2f(550, 850));
		Button Wygrana("Wygrales!", font, 40, sf::Vector2f(550, 450));
		Button Przegrana("Przegrales!", font, 40, sf::Vector2f(550, 450));
		Count_Score My_Shoot_Ships("0", font, 40, sf::Vector2f(1700, 450));
		Count_Score Enemy_Shoot_Ships("0", font, 40, sf::Vector2f(1700, 650));
		


		Button pion1("1 PIONOWO", font, 40, sf::Vector2f(550, 100));
		Button poziom1("1 POZIOMO", font, 40, sf::Vector2f(550, 175));
		Button pion2("2 PIONOWO", font, 40, sf::Vector2f(550, 250));
		Button poziom2("2 POZIOMO", font, 40, sf::Vector2f(550, 325));
		Button pion3("3 PIONOWO", font, 40, sf::Vector2f(550, 400));
		Button poziom3("3 POZIOMO", font, 40, sf::Vector2f(550, 475));
		Button pion4("4 PIONOWO", font, 40, sf::Vector2f(550, 550));
		Button poziom4("4 POZIOMO", font, 40, sf::Vector2f(550, 625));

		bool dodawanie = false;

		bool end_of_game = false;

		bool change_of_game = false;

		ButtonList.push_back(przycisk_nowa_rozgrywka);
		ButtonList.push_back(przycisk_twoj_wynik);
		ButtonList.push_back(przycisk_wyjscia);
		ButtonList.push_back(przycisk_wynik_przeciwnika);
		ButtonList.push_back(przycisk_zapisz_gre);
		AdditionalButtons.push_front(Enemy_Shoot_Ships);
		AdditionalButtons.push_front(My_Shoot_Ships);
		int licznik1 = 0;
		int licznik2 = 0;
		int licznik3 = 0;
		int licznik4 = 0;
		

		Board plansza1(font, sf::Vector2f(0, 0));
		std::list<Field> My_squares;
		Board plansza2(font, sf::Vector2f(0, 500));
		std::list<Field> Enemy_squares;
		std::list<Field>::iterator iterBoard;
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				Field small_square1(font, sf::Vector2f(i * 40, j * 40));
				My_squares.push_back(small_square1);
				Field small_square2(font, sf::Vector2f(i * 40, 500 + j * 40));
				Enemy_squares.push_back(small_square2);
			}
		}

		std::list<Ship> my_Ships;
		std::list<Ship> enemy_ships;
		std::list<Ship>::iterator iterShips;
		
		
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				if (my_board->is_ship_there(j, i))
				{
					Ship statki("O", font, sf::Vector2f(i * 40, j * 40));
					if (my_board->is_ship_there_shot(j, i))
						statki.change_Ship("X");

					my_Ships.push_back(statki);
				}
				if (enemy_board->is_ship_there_shot(j, i))
				{

					Ship statki("*", font, sf::Vector2f(i * 40, j * 40 + 500));
					if (enemy_board->is_ship_there(j, i))
						statki.change_Ship("X");
					enemy_ships.push_back(statki);
				}

			}
		}
		Mine Score1 = Mine();
		Enemy Score2 = Enemy();
		
		sf::Event event;
		sf::Mouse mouse;
		while (window.isOpen())
		{

			while (window.pollEvent(event))
			{

				float mouse_x = 0;
				float mouse_y = 0;

				if (event.type == sf::Event::Closed)
					window.close();
				if (mouse.isButtonPressed(sf::Mouse::Left))
				{
					mouse_x = mouse.getPosition(window).x;
					mouse_y = mouse.getPosition(window).y;


					if (change_of_game)
					{
						end_of_game = false;
						Score1.SetScore();
						Score2.SetScore();
						if (mouse_x > 550 && mouse_x < 1050 && mouse_y > 650 && mouse_y < 850) //wczytaj
						{

							my_board->read_file((*enemy_board));
							for (int i = 0; i < 10; i++)
							{
								for (int j = 0; j < 10; j++)
								{
									
									if (my_board->is_ship_there(j, i))
									{
										Ship statki("O", font, sf::Vector2f(i * 40, j * 40));
										if (my_board->is_ship_there_shot(j, i))
											statki.change_Ship("X");

										my_Ships.push_back(statki);
									}
									else if (my_board->is_ship_there_shot(j, i))
									{
										Ship statki("*", font, sf::Vector2f(i * 40, j * 40));
										my_Ships.push_back(statki);
									}
								}
							}

							for (int i = 0; i < 10; i++)
							{
								for (int j = 0; j < 10; j++)
								{

									if (enemy_board->is_ship_there_shot(j, i))
									{

										Ship statki("*", font, sf::Vector2f(i * 40, j * 40 + 500));
										if (enemy_board->is_ship_there(j, i))
											statki.change_Ship("X");
										enemy_ships.push_back(statki);
									}


								}
							}
						}
						if (mouse_x > 550 && mouse_x < 1050 && mouse_y > 850 && mouse_y < 1050) //stworz
						{
						


							AdditionalButtons.push_back(pion1);
							AdditionalButtons.push_back(pion2);
							AdditionalButtons.push_back(pion3);
							AdditionalButtons.push_back(pion4);
							AdditionalButtons.push_back(poziom1);
							AdditionalButtons.push_back(poziom2);
							AdditionalButtons.push_back(poziom3);
							AdditionalButtons.push_back(poziom4);
							dodawanie = true;


						}
						change_of_game = false;
						ButtonList.pop_back();
						ButtonList.pop_back();

					}
					My_Shoot_Ships.setString(std::to_string(Score1.GetScore()));
					Enemy_Shoot_Ships.setString(std::to_string(Score2.GetScore()));
					

					if (dodawanie)
					{
						if (mouse_x > 550 && mouse_x < 1050 && mouse_y >100 && mouse_y < 700)
						{
							my_board->AddingShipsByUser(window, mouse_y, licznik1,licznik2,licznik3,licznik4);

							my_Ships.clear(); 
							
							for (int i = 0; i < 10; i++)
							{
								for (int j = 0; j < 10; j++)
								{
									if (my_board->is_ship_there(j, i))
									{
										Ship statki("O", font, sf::Vector2f(i * 40, j * 40));
										if (my_board->is_ship_there_shot(j, i))
											statki.change_Ship("X");

										my_Ships.push_back(statki);
									}

								}
							}
							if (licznik1 == 4 && licznik2 == 3 && licznik3 == 2 && licznik4 == 1)
							{
								for (int i = 0; i < 8; i++)
									AdditionalButtons.pop_back();
								enemy_board->AddingShipsByComputer();
								dodawanie = false;
								licznik1 = licznik2 = licznik3 = licznik4;
							}
						}
						for (int i = 0; i < 10; i++)
						{
							for (int j = 0; j < 10; j++)
							{

								if (enemy_board->is_ship_there_shot(j, i))
								{

									Ship statki("*", font, sf::Vector2f(i * 40, j * 40 + 500));
									if (enemy_board->is_ship_there(j, i))
										statki.change_Ship("X");
									enemy_ships.push_back(statki);
								}


							}
						}
					}

					if (mouse_x > 45 && mouse_x < 445)
					{

						if (!end_of_game && !change_of_game)
						{			if (mouse_y > 545 && mouse_y < 945)//klikniecie pola zwiazanego ze statkiem przeciwnika
							{
								int x = (mouse_x - 45) / 40;
								int y = (mouse_y - 545) / 40;

								if (enemy_board->Check_If_You_Shot_Ship(y, x))
								{
									Ship hit("X", font, sf::Vector2f(x * 40, y * 40 + 500));
									enemy_ships.push_back(hit);


								}
								else
								{
									Ship hit("*", font, sf::Vector2f(x * 40, y * 40 + 500));
									enemy_ships.push_back(hit);

								}
								enemy_board->shoot_ship(y, x);


								//komputer
								int a = rand() % 10;
								int b = rand() % 10;
								while (my_board->is_ship_there_shot(b, a))
								{
									a = rand() % 10;
									b = rand() % 10;

								}
								if (my_board->is_ship_there(b, a))
								{
									Ship hit("X", font, sf::Vector2f(a * 40, b * 40));
									my_Ships.push_back(hit);
								}
								else
								{
									Ship hit("*", font, sf::Vector2f(a * 40, b * 40));
									my_Ships.push_back(hit);
								}
								my_board->shoot_ship(b, a);


								Score1.Count((*my_board));
								Score2.Count((*enemy_board));

								}
						}
					}
					if(mouse_x >1100 && mouse_x < 1600)//pola przyciskow
					{
						
						if (mouse_y > 50 && mouse_y < 150) //exit
							window.close();
						if (mouse_y > 250 && mouse_y < 350) //nowa gra
						{

							if(end_of_game)
								ButtonList.pop_back();
							ButtonList.push_back(przycisk_wczytaj);
							ButtonList.push_back(przycisk_stworz);
							change_of_game = true;
							my_board->clear();
							enemy_board->clear();
							my_Ships.clear();
							enemy_ships.clear();
	
						}

						if (mouse_y > 850 && mouse_y < 950) //zapisz gre
						{
							my_board->save_to_file((*enemy_board));
						}
						
					}
					if (!end_of_game)
					{
						if (Score2.GetScore() == 20)
						{
							ButtonList.push_back(Wygrana);
							end_of_game = true;
						}if (Score1.GetScore() == 20)
						{
							ButtonList.push_back(Przegrana);
							end_of_game = true;
						}
					}
					AdditionalButtons.pop_front();
					AdditionalButtons.pop_front();
					AdditionalButtons.push_front(My_Shoot_Ships);
					AdditionalButtons.push_front(Enemy_Shoot_Ships);




				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) //wciśnięto klawisz ESC
					window.close(); //zakończ aplikację
			}


			window.draw(plansza1);
			window.draw(plansza2);
			
			for (iterButton = ButtonList.begin(); iterButton != ButtonList.end(); iterButton++)
			{
				window.draw(*iterButton);
			}
			for (iterButton2 = AdditionalButtons.begin(); iterButton2 != AdditionalButtons.end(); iterButton2++)
			{
				window.draw(*iterButton2);
			}
			for (iterBoard = My_squares.begin(); iterBoard != My_squares.end(); iterBoard++)
			{
				window.draw(*iterBoard);
			}
			for (iterBoard = Enemy_squares.begin(); iterBoard != Enemy_squares.end(); iterBoard++)
			{
				window.draw(*iterBoard);
			}
			for (iterShips = my_Ships.begin(); iterShips != my_Ships.end(); iterShips++)
			{
				window.draw(*iterShips);
			}
			for (iterShips = enemy_ships.begin(); iterShips != enemy_ships.end(); iterShips++)
			{
				window.draw(*iterShips);
			}
			
			window.display();
			window.clear();
			
			

		}

		return 0;
	}
}
  