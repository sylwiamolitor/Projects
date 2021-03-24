#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h> 
#include "solution.h"
#include "struct.h"

bool can_add(int x, int y, int value, char *pointer, char *helping_pointer)
{
	for (int i = 0; i < 9; i++)
	{
		if (value == (*(helping_pointer + (x / 3 * 3 + i % 3) + (y / 3 * 3 + i / 3) * 10)) - 48
			|| value == (*(helping_pointer + i + y * 10)) - 48
			|| value == (*(helping_pointer + x + i * 10)) - 48)
		{
			return false;
		}


	}
	return true;

}

bool next_area(int x, int y, char *pointer, char *helping_pointer)
{
	if (x == 8 && y == 8)
	{
		return true;
	}
	else if (x == 8)
	{
		return solve_it(0, (y + 1), pointer, helping_pointer);
	}
	else
	{
		return solve_it((x + 1), y, pointer, helping_pointer);
	}

}

bool solve_it(int x, int y, char *pointer, char *helping_pointer)
{
	if ((*(pointer + x + y * 10)) == ' ')
	{
		for (int i = 1; i < 10; i++)
		{
			if (can_add(x, y, i, pointer, helping_pointer) == true)
			{


				(*(helping_pointer + x + y * 10)) = i + 48;
				if (next_area(x, y, pointer, helping_pointer) == true)
				{
					return true;
				}

			}
		}
		(*(helping_pointer + x + y * 10)) = ' ';
		return false;
	}
	return next_area(x, y, pointer, helping_pointer);
}