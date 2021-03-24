#include "GameLogic.h"
#include "Interface.h"
#include "GraphicObject.h"
#include <list>
void Mine::Count(Game_Logic my_board)
{
	
	int amount = 0;
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
			if (my_board.is_ship_there(i,j) == true && my_board.is_ship_there_shot(i,j) == true)
				amount++;

	this->SetScore(amount);

}

void Enemy::Count(Game_Logic enemy_board)
{
	int amount = 0;

	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
			if (enemy_board.is_ship_there(i, j) == true && enemy_board.is_ship_there_shot(i, j) == true)
				amount++;
	this->SetScore(amount);
}

bool Game_Logic::is_ship_there(int x, int y)
{
		return if_ship_there[y][x];
}

bool Game_Logic::is_ship_there_shot(int x, int y)
{
	return if_ship_shot[y][x];
}

void Game_Logic::set_ship(int x, int y)
{
	if_ship_shot[y][x] = 0;
	if_ship_there[y][x] = 1;
}

void Game_Logic::set_empty(int x, int y)
{

	if_ship_shot[y][x] = 0;
	if_ship_there[y][x] = 0;
}

void Game_Logic::shoot_ship(int x, int y)
{
	if_ship_shot[y][x] = 1;
}

bool Check_Position::Check_If_Ship_Already_There(int x, int y)
{
	return (is_ship_there(x, y)); //nie ma statku
}

bool Check_Position::Check_If_You_Can_Add_Ship(int x, int y)
{
		int a = x - 1;
		int b = x + 1;
		int c = y - 1;
		int d = y + 1;
		if (a < 0)
			a++;
		if (b > 9)
			b--;
		if (c < 0)
			c++;
		if (d > 9)
			d--;
		if (a < 0 || b >9 || c < 0 || d>9)
			return false;
		if (Check_If_Ship_Already_There(x, y)
			|| Check_If_Ship_Already_There(a, c)
			|| Check_If_Ship_Already_There(x, c)
			|| Check_If_Ship_Already_There(b, c)
			|| Check_If_Ship_Already_There(a, y)
			|| Check_If_Ship_Already_There(b, y)
			|| Check_If_Ship_Already_There(a, d)
			|| Check_If_Ship_Already_There(x, d)
			|| Check_If_Ship_Already_There(b, d))

		{
			return false;

		}
		return true;
}

void Create_Board::clear()
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			set_empty(i, j);
		}
	}
}

Create_Board::Create_Board()
{
	clear();
}

bool Create_Board::Check_If_You_Shot_Ship(int x, int y)
{
	if (is_ship_there(x, y))
	{
		shoot_ship(x, y); //status = zestrzelony
		return true;
	}
}

bool Create_Board::Add_Ship(int x, int y, bool direction, int size)
{


	for (int i = 0; i <size; i++)
	{
		if (!direction)
		{
			if (!Check_If_You_Can_Add_Ship(x, y + i))
				return false;
		}
		else
		{
			if (!Check_If_You_Can_Add_Ship(x + i, y))
				return false;
		}
	}
	for (int i = 0; i <size ; i++)
	{
		if (direction)
		{
			set_ship(x + i, y);
		}
		else
		{
			set_ship(x, y + i);
		}
	}
	return true;
}

bool Create_Board::read_file(Create_Board & enemy_board)
{
	std::ifstream plikWej("Zapis_Rozgrywki.txt");
	try
	{
		if (!plikWej)
			throw 0;
	}
	catch (int e)
	{
		std::cout << "Error: brak pliku z zapisem gry!\n";
		return 0;
	}
	if (plikWej)
	{
		std::string linijka;
		for (int i = 0; i < 10; i++)
		{

			std::getline(plikWej, linijka);
			for (int j = 0; j < 10; j++)
			{
				if (linijka[j] == '1')
					this->set_ship(i, j);
			}//wczytuj do planszy swojej
		}
		std::getline(plikWej, linijka);

		for (int i = 0; i < 10; i++)
		{

			std::getline(plikWej, linijka);
			for (int j = 0; j < 10; j++)
			{
				if (linijka[j] == '1')
					this->shoot_ship(i, j);
			}//wczytuj do planszy swojej
		}
		std::getline(plikWej, linijka);



		for (int i = 0; i < 10; i++)
		{

			std::getline(plikWej, linijka);
			for (int j = 0; j < 10; j++)
			{
				if (linijka[j] == '1')
					enemy_board.set_ship(i, j);
			}
		}

		std::getline(plikWej, linijka);


		for (int i = 0; i < 10; i++)
		{

			std::getline(plikWej, linijka);
			for (int j = 0; j < 10; j++)
			{
				if (linijka[j] == '1')
					enemy_board.shoot_ship(i, j);
			}
		}
		

		plikWej.close();
		return true;
	}
	return false;
}


bool Create_Board::save_to_file(Create_Board enemy_board)
{

	std::ofstream plikWyj("Zapis_Rozgrywki.txt");

	if (plikWyj)
	{

		for (int i = 0; i < 10; i++)
		{

			for (int j = 0; j < 10; j++)
			{
				if (this->Check_If_Ship_Already_There(i, j) == 1)
					plikWyj << 1;
				else
					plikWyj << 0;
			}
			plikWyj << std::endl;
		}
		plikWyj << std::endl;

		for (int i = 0; i < 10; i++)
		{

			for (int j = 0; j < 10; j++)
			{
				if (this->is_ship_there_shot(i, j) == 1)
					plikWyj << 1;
				else
					plikWyj << 0;
			}
			plikWyj << std::endl;
		}

		plikWyj << std::endl;


		for (int i = 0; i < 10; i++)
		{

			for (int j = 0; j < 10; j++)
			{
				if (enemy_board.Check_If_Ship_Already_There(i, j) == 1)
					plikWyj << 1;
				else
					plikWyj << 0;
			}
			plikWyj << std::endl;
		}
		plikWyj << std::endl;

		for (int i = 0; i < 10; i++)
		{

			for (int j = 0; j < 10; j++)
			{
				if (enemy_board.is_ship_there_shot(i, j) == 1)
					plikWyj << 1;
				else
					plikWyj << 0;
			}
			plikWyj << std::endl;
		}

		plikWyj.close();
		return true;
	}
	return false;
}

void Create_Board::AddingShipsByComputer()
{
		int licznik1 = 0, licznik2 = 0, licznik3 = 0, licznik4 = 0;
		while (licznik1 < 4 || licznik2 < 3 || licznik3 < 2 || licznik4 < 1)
		{
			int position_x = rand() % 10;
			int position_y = rand() % 10;
			int horizontally_or_else = rand() % 2;
			int size = rand() % 4 + 1;
			if (licznik1 == 4 && size == 1)
				continue;
			if (licznik2 == 3 && size == 2)
				continue;
			if (licznik3 == 2 && size == 3)
				continue;
			if (licznik4 == 1 && size == 4)
				continue;
			if (this->Add_Ship(position_y, position_x, horizontally_or_else, size))
			{
				if (size == 1)
					licznik1++;
				if (size == 2)
					licznik2++;
				if (size == 3)
					licznik3++;
				if (size == 4)
					licznik4++;
			}
		}
}

void Create_Board::AddingShipsByUser(sf::RenderWindow & window, int base_y, int &licznik1,int &licznik2, int &licznik3, int &licznik4)
{
	sf::Mouse mouse;
	int base_x = 580;

	bool dodano = false;
	bool koniec = false;
	while (!koniec || !dodano)
	{
		if (dodano)
		{
			base_x = 0;
			while (base_x < 550 || base_x >1050 || base_y < 100 || base_y>700)
			{
				if (mouse.isButtonPressed(sf::Mouse::Left))
				{
					base_x = mouse.getPosition(window).x;
					base_y = mouse.getPosition(window).y;
				}
			}
			dodano = false;
		}
		if (mouse.isButtonPressed(sf::Mouse::Left))
		{
			float mouse_x = mouse.getPosition(window).x;
			float mouse_y = mouse.getPosition(window).y;

			if (mouse_x > 45 && mouse_x < 445 && mouse_y > 45 && mouse_y < 445 && base_x>550 && base_x < 1050)
			{
				int x = (mouse_x - 45) / 40;
				int y = (mouse_y - 45) / 40;
				if (licznik1 < 4)
				{
					if (base_y > 45 && base_y < 150)
					{

						koniec = this->Add_Ship(y, x, 1, 1);
							

					}
					if (base_y > 175 && base_y < 225)
					{

						koniec = this->Add_Ship(y, x, 0, 1);

					}
					if (koniec)
					{
						licznik1++;
						return;
					}
				}
				if (licznik2 < 3)
				{
					if (base_y > 250 && base_y < 300)
					{

						koniec = this->Add_Ship(y, x, 1, 2);

					}
					if (base_y > 325 && base_y < 375)
					{

						koniec = this->Add_Ship(y, x, 0, 2);
							

					}
					if (koniec)
					{
						licznik2++;
						return;
					}

				}
				if (licznik3 < 2)
				{
					if (base_y > 400 && base_y < 450)
					{

						koniec = this->Add_Ship(y, x, 1, 3);

					}
					if (base_y > 475 && base_y < 525)
					{

						koniec = this->Add_Ship(y, x, 0, 3);

					}
					if (koniec)
					{
						licznik3++;
						return;
					}
				}
				if (licznik4 < 1)
				{
					if (base_y > 550 && base_y < 600)
					{

						koniec =this->Add_Ship(y, x, 1, 4);

					}
					if (base_y > 625 && base_y < 675)
					{

						koniec = this->Add_Ship(y, x, 0, 4);

					}

					if (koniec)
					{
						licznik4++;
						return;
					}
				}
				dodano = true;
				
			}
		}

	}
}

int Score::GetScore()
{
	return this->amount;
}

void Score::SetScore()
{
	this->amount = 0;
}
void Score::SetScore(int amount)
{
	this->amount = amount;
}