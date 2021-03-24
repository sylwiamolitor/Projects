#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>  
#include "checkboard.h"
#include "struct.h"

bool checking(char *pointer)
{
	if (checkingColumns(pointer) && checkingRows(pointer) && checkingSquares(pointer))
	{
		return true;
	}
	else
	{
		return false;
	}

}

bool checkingColumns(char *pointer)
{
	for (int k = 0; k < 9; k++, pointer++)
	{
		for (int i = 0; i < 9; i++, pointer++)
		{
			int counter = 0;
			for (int j = k + 1; j < 9; j++)
			{
				counter++;
				if ((*pointer) == ' ')
				{
					continue;
				}

				if ((*pointer) == (*(pointer + counter * 10)))
				{
					return false;
				}

			}

		}
	}
	return true;
}
bool checkingRows(char *pointer)
{
	for (int k = 0; k < 9; k++, pointer++)
	{
		for (int i = 0; i < 9; i++, pointer++)
		{
			for (int j = 1; j < 9; j++)
			{
				if ((*pointer) == ' ')
				{
					continue;
				}
				if ((*(pointer + j)) == '\n')
				{
					break;
				}
				if ((*pointer) == (*(pointer + j)))
				{
					return false;
				}

			}

		}
	}
	return true;

}
bool checkingSquares(char *pointer)
{
	char *helpingPointer = pointer;
	char *pointer_2 = pointer;
	for (int k = 0; k < 3; k++, pointer_2 + 30)
	{
		for (int a = 0; a < 3; a++, pointer_2 + 3)
		{
			helpingPointer = pointer_2;
			pointer = pointer_2;
			for (int s = 0; s < 3; s++, pointer + 10)
			{
				for (int z = 0; z < 3; z++, pointer++)
				{
					for (int x = s; x < 3; x++)
					{

						for (int y = z; y < 3; y++)
						{
							if ((*pointer) == ' ' || x == s && y == z)
							{
								continue;
							}
							if ((*pointer) == (*(helpingPointer + x * 10 + y)))
							{
								return false;
							}

						}
					}
				}
				pointer = pointer - 3;
			}
		}
	}
	return true;

}
