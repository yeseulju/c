/*
	==================================================
	Assignment 2 (Milestone - 4):
	==================================================
	Name   : Yeseul Ju
	ID     : 154673198
	Email  : yju9@myseneca.ca
	Section: NEE
*/


#define _CRT_SECURE_NO_WARNINGS
#include"commonHelpers.h"
#include"account.h"
#include<time.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void clearStandardInputBuffer(void)
{
	while (getchar() != '\n')
	{
		; // On purpose: do nothing
	}
}

int currentYear(void)
{
	time_t currentTime = time(NULL);
	return localtime(&currentTime)->tm_year + 1900;

}



int getInteger(void)
{
	int getInt = 0;
	char newLine = 0;

	do {
		scanf("%d%c", &getInt, &newLine);

		if (newLine == '\n')
			return getInt;
		else
		{
			clearStandardInputBuffer();
			printf("ERROR: Value must be an integer: ");
		}

	} while (newLine != '\n');
	return getInt;
}



int getPositiveInteger(void)
{
	int getInt = 0;

	do
	{
		scanf("%d", &getInt);

		if (getInt < 0)
		{
			clearStandardInputBuffer();
			printf("ERROR: Value must be a positive integer greater than zero: ");
		}
		else {
			return getInt;
		}
	} while (getInt < 0);

	return getInt;
}

double getDouble(void)
{
	double db1 = 0.0;
	char c = 0;


	do
	{
		scanf("%lf%c", &db1, &c);

		if (c != '\n')
		{
			clearStandardInputBuffer();
			printf("ERROR: Value must be a double floating-point number: ");
		}

	} while (c != '\n');

	return db1;
}

double getPositiveDouble(void)
{
	double getDou;
	char wrong;

	do
	{
		scanf("%lf%c", &getDou, &wrong);

		if (wrong != '\n')
		{
			clearStandardInputBuffer();
			printf("ERROR: Value must be a double floating-point number: ");
			//scanf("%lf", &getDou);
		}
		else
		{
			if (getDou > 0)
			{
				return getDou;
			}
			else
				printf("ERROR: Value must be a positive double floating-point number: ");
		}

	} while (wrong != '\n' || getDou <= 0);
	return getDou;

}



int getIntFromRange(int lower, int upper)
{
	int intvalue = 0;
	char newLine = 'a';
	do
	{
		scanf("%d%c", &intvalue, &newLine);
		if (newLine != '\n')
		{
			scanf("%d%c", &intvalue, &newLine);
			printf("ERROR: Value must be an integer: ");
			clearStandardInputBuffer();
		}
		else if (intvalue < lower || intvalue > upper)
		{
			printf("ERROR: Value must be between %d and %d inclusive: ", lower, upper);
		}
	} while (newLine != '\n' || intvalue <lower || intvalue > upper);
	return intvalue;
}




char getCharOption(char str[])
{
	char i[10] = "";
	int reset = 0;
	int check = 0;

	do {

		scanf("%s", i);

		if (i[1] == '\0')
		{
			for (check = 0; str[check] != '\0'; check++)
			{
				if (str[check] == i[0])
					reset = 1;
			}
		}

		if (reset == 1)
			return i[0];
		else
		{
			clearStandardInputBuffer();
			printf("ERROR: Character must be one of [%s]: ", str);
		}

	} while (reset == 0);
	return i[0];
}



void getCString(char* cvalue, int lower, int upper)
{
	int char_num = 0;
	int check = 0;
	char input[50] = "";

	do {
		scanf(" %[^\n]", input);

		{
			for (check = 0; input[check] != '\0'; check++)
			{
				char_num = check + 1;
			}
		}

		if ((char_num != lower) && (lower == upper))
		{
			clearStandardInputBuffer();
			printf("ERROR: String length must be exactly %d chars: ", lower);
		}
		else if (char_num > upper)
		{
			clearStandardInputBuffer();
			printf("ERROR: String length must be no more than %d chars: ", upper);
		}
		else if (char_num < lower)
		{
			clearStandardInputBuffer();
			printf("ERROR: String length must be between %d and %d chars: ", lower, upper);
		}
		else
		{
			for (check = 0; check <= char_num; check++)
			{
				cvalue[check] = input[check];
			}
		}

	} while (char_num < lower || char_num > upper);
	return;
}