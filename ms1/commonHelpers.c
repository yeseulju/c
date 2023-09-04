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

	do
	{
		scanf("%d%c", &getInt, &newLine);

		if (newLine != '\n')
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
		scanf("%lf%c", &getDou,&wrong);

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
	char c, wrong;
	int flag = 0;

	do
	{
		wrong = '\0';
		flag = 0;
		scanf("%c%c", &c, &wrong);
		if (wrong == '\n')
		{
			if (strchr(str, c))
				flag = 1;
		}

		else
		{
			clearStandardInputBuffer();
		}
		if (flag == 0)
			printf("ERROR: Character must be one of [%s]: ", str);

	} while (flag == 0);
	return c;
}



void getCString(char* cvalue, int lower, int upper)
{
	char inputString[1000] = { 0 };

	int flag = 0;
	int strLen = 0;

	do
	{

		scanf("%30[^\n]", (char*)&inputString);
		clearStandardInputBuffer();
		strLen = strlen(inputString);

		if (lower == upper)
		{
			if (strLen != lower)
				printf("ERROR: String length must be exactly %d chars: ", lower);
			else
				flag = 1;
		}
		else
		{
			if (strLen < lower)
				printf("ERROR: String length must be between %d and %d chars: ", lower, upper);
			else if (strLen > upper)
				printf("ERROR: String length must be no more than %d chars: ", upper);
			else
				flag = 1;


		}

	} while (flag == 0);
	
	strcpy(cvalue, inputString);
}

