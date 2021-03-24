#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>  
#include "gameplay.h"
#include "struct.h"

void deleting(char *pointer, bool *pointerBO, char number)
{
	int amount_of_deleting_numbers = (number - 48) * 10;
	srand(time(NULL));
	for (int i = 0; i < amount_of_deleting_numbers; i++)
	{
		int current = rand() % 90;

		if ((*(pointer + current)) == ' ' || (current + 1) % 10 == 0)
		{
			amount_of_deleting_numbers++;
		}
		else
		{
			(*(pointer + current)) = ' ';
			(*(pointerBO + current)) = false;
		}
	}

}

void write_out(char *pointer)
{

	for (int i = 0; i < 90; i++)
	{
		if (i == 30 || i == 60)
		{
			printf("-------------\n");
		}
		if (i % 10 == 0 || i % 10 == 3 || i % 10 == 6 || i % 10 == 9)
		{
			printf("|");
		}
		printf("%c", (*(pointer + i)));

	}

}

void writeInTheBoard(char *pointer, int vertical, int horizontal, char number, bool *pointerBO)
{
	if ((*(pointerBO + vertical + 10 * horizontal)) == true)
	{
		printf("Nie mozna nadpisywac wartosci. \n");
	}
	else
	{
		(*(pointer + vertical + 10 * horizontal)) = number;
	}

}

void generateBoard(char *pointer, bool *pointerBO, char number)
{
	for (int i = 0; i < 90; i++)
	{

		if ((i + 1) % 10 == 0)
		{
			(*(pointer + i)) = '\n';
			(*(pointerBO + i)) = true;
		}
		else
		{
			(*(pointer + i)) = ' ';
			(*(pointerBO + i)) = false;
		}

	}

	srand(time(NULL));
	int hint = rand() % 9 + 49;
	(*pointer) = hint;
	(*pointerBO) = true;

	char temporary_table[90];
	char *temporary_pointer = &temporary_table;

	for (int i = 0; i < 90; i++)
	{
		(*(temporary_pointer + i)) = (*(pointer + i));
	}
	solve_it(0, 0, pointer, temporary_pointer);
	for (int i = 0; i < 90; i++)
	{
		(*(pointer + i)) = (*(temporary_pointer + i));
		(*(pointerBO + i)) = true;

	}

	deleting(pointer, pointerBO, number);


}
bool check_empty_spaces(char *pointer)
{

	for (int j = 0; j < 90; j++)
	{
		if (*((pointer)+j) == ' ')
		{
			return true;
		}
	}
	return false;

}
void contactWithUser(char *pointer, bool *pointerBO, char *number_of_file)
{
	reading(pointer, pointerBO, number_of_file);
	char letter = '\n';
	while (letter != 'z')
	{

		if (letter == '\n')
		{
			printf("Witamy w sudoku, przy pierwszym uruchomieniu programu prosimy o wygenerowanie pierwotnego sudoku, wpisz \n a, aby wczytac z pliku ostatnia gre, \n g, aby wygenerowac gre, \n r tryb rozwiazywania ,\n s, aby sprawdzic, \n h, aby uzyskac 1 podpowiedz,\n c, aby komputer rozwiazal,\n z, aby zakonczyc\n");
			write_out(pointer);
		}

		letter = getchar();
		if (letter != '\n')
		{
			system("cls");
		}
		if (letter == 'r')
		{
			write_out(pointer);
			char number = '0';
			int vertical = 0;
			int horizontal = 0;
			printf("Podaj wspolrzedna x(od 0 do 8): ");
			scanf("%d", &vertical);
			printf("\nPodaj wspolrzedna y(od 0 do 8): ");
			scanf("%d", &horizontal);
			printf("Wpisz cyfre: ");
			number = getchar();
			number = getchar();
			system("cls");
			if (number == ' ' || number > '0' && number <= '9')
			{
				writeInTheBoard(pointer, vertical, horizontal, number, pointerBO);
			}
			else
			{
				printf("Nie mozna nadpisac tej wartosci.\n");
			}
		}
		if (letter == 'c' || letter == 'h')
		{

			bool empty_spaces = check_empty_spaces(pointer);
			if (empty_spaces)
			{
	
				
					if (checking(pointer))
					{
						char helping_table[9][10];
						char *helping_pointer = &helping_table;
						for (int i = 0; i < 90; i++)
						{
							(*(helping_pointer + i)) = (*(pointer + i));
						}
						if (solve_it(0, 0, pointer, helping_pointer))
						{
							if (letter == 'c')
							{
								for (int i = 0; i < 90; i++)
								{
									(*(pointer + i)) = (*(helping_pointer + i));
								}
								if (check_empty_spaces(pointer))
								{
									printf("Masz bledy w tablicy. Usun je, aby kontynuowac(nadpisz spacja).\n");
								}
							}

							if (letter == 'h')
							{
								int i = 0;
								while ((*(pointer + i)) == (*(helping_pointer + i)))
								{
									i++;
								}
								(*(pointer + i)) = (*(helping_pointer + i));
								(*(pointerBO + i)) = true;
							}

						}
						




					}
					else
					{
						printf("Masz bledy w wypelnieniu. Usun je, aby kontynuowac(nadpisz spacja).\n");
					}

				
			}
			else
			{
				printf("Brak pustych miejsc. Usun je, aby kontynuowac.\n");

			}



		}


		if (letter == 'a')
		{
			reading(pointer, pointerBO, number_of_file);
		}

		if (letter == 'g')
		{
			printf("Wybierz poziom trudnosci: (w sudoku bedzie brakowac 10* wiecej cyfr niz wpiszesz)\n");
			char number = '0';
			number = getchar();
			number = getchar();
			if (number > '0' && number < '9')
			{
				generateBoard(pointer, pointerBO, number);
			}
			else
			{
				printf("To nie cyfra!\n");
			}
		}
		if (letter == 's')
		{
			if (checking(pointer))
			{
				printf("Prawidlowe wypelnienie.\n");
			}
			else
			{
				printf("Zle wypelnienie.\n");
			}
		}
	}
}