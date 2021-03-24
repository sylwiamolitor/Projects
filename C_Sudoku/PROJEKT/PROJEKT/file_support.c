#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>  
#include "file_support.h"
#include "struct.h"

void reading(char *pointer, bool *pointerBO, char *number_of_file)
{
	FILE *file = fopen(number_of_file, "a+");
	for (int i = 0; i < 90; i++)
	{

		fscanf(file, "%c", pointer + i);

	}
	char static_number = '0';
	fscanf(file, "%c", &static_number);

	for (int i = 0; i < 90; i++)
	{
		fscanf(file, "%c", &static_number);
		if (static_number == '1' || static_number == '\n')
		{
			(*(pointerBO + i)) = true;
		}
		if (static_number == '0')
		{
			(*(pointerBO + i)) = false;
		}
	}


	fclose(file);

}


void saving(char *pointer, bool *pointerBO, char *number_of_file)
{
	FILE *file = fopen(number_of_file, "a+");
	for (int i = 0; i < 90; i++)
	{
		fprintf(file, "%c", (*(pointer + i)));
	}

	fprintf(file, "\n");

	for (int i = 0; i < 90; i++)
	{

		if ((*(pointerBO + i)) == true)
		{
			fprintf(file, "1");
		}
		if ((*(pointerBO + i)) == false)
		{
			fprintf(file, "0");
		}
		if ((i + 1) % 10 == 0)
		{
			fprintf(file, "\n");
		}


	}
	fclose(file);

}

void cleaning(char *number_of_file)
{
	FILE *file = fopen(number_of_file, "w");
	fflush(file);
	fclose(file);
}



