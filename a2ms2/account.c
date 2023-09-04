/*
	==================================================
	Assignment 2 (Milestone - 2):
	==================================================
	Name   : Yeseul Ju
	ID     : 154673198
	Email  : yju9@myseneca.ca
	Section: NEE
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "account.h"
#include "commonHelpers.h"
#include <string.h>
#include "accountTicketingUI.h"
#include <ctype.h>

void getAccount(struct Account *account)
{
	printf("\nNew Account Data (Account#:%d)\n", account->acc_num);
	printf("----------------------------------------\n");
	printf("Enter the account type (A=Agent | C=Customer): ");
	
	account->acc_type = getCharOption("AC");

	getPerson(account);

	if (account->acc_type == 'A')
	{
		getUserLogin(account);
	}

	else
	{
		account->Settings.login[0] = 0;
		account->Settings.password[0] = 0;
	}
	
	return;
}

void getPerson(struct Account *account)
{
	int st_arr = 0;
	char string[31] = "";
	int min_char_p = 1, max_char_p = 30, min_age = 18, max_age = 110, min_year = 0, max_year = 0;

	printf("\nPerson Data Input\n");
	printf("----------------------------------------\n");
	printf("Enter the person's full name (%d chars max): ", max_char_p);

	getCString(string, min_char_p, max_char_p);
	for (st_arr = 0; string[st_arr] != '\0'; st_arr++)
	{
	account->Info.name[st_arr] = string[st_arr];
	}

	min_year = currentYear() - max_age;
	max_year = currentYear() - min_age;

	printf("Enter birth year (current age must be between %d and %d): ", min_age, max_age);
	
	account->Info.year = getIntFromRange(min_year, max_year);

	printf("Enter the household Income: $");
	
	account->Info.income = getPositiveDouble();

	printf("Enter the country (%d chars max.): ", max_char_p);
	
	getCString(string, min_char_p, max_char_p);
	for (st_arr = 0; string[st_arr] != '\0'; st_arr++)
	{
		account->Info.res[st_arr] = toupper(string[st_arr]);
	}

	return;
}

void getUserLogin(struct Account *account)
{
	int st_arr = 0, a = 0, b = 0, c = 0, d = 0, e = 0, f = 0, g = 0, h = 0, i = 0;
	char string[31] = "";
	int min_char_p = 1, max_char_l = 10, max_char_pw = 8;

	printf("\nUser Login Data Input\n");
	printf("----------------------------------------\n");

	do
	{
		a = 0;

		printf("Enter user login (%d chars max): ", max_char_l);

		strcpy(account->Settings.login, "\0");
		getCString(string, min_char_p, max_char_l);
		for (st_arr = 0; string[st_arr] != '\0'; st_arr++)
		{

			d = isspace(account->Settings.login[st_arr]);
			if (d != 0)
			{
				a = 1;
			}
			else
			{
			strcpy(account->Settings.login, string);
			}

		}
		
		if (a != 0)
		{
			printf("ERROR:  The user login must NOT contain whitespace characters.\n");
		}

	} while (a != 0);
	
	do
	{
		c = 0, g = 0, h = 0, i = 0;

		printf("Enter the password (must be %d chars in length): ", max_char_pw);
		getCString(string, max_char_pw, max_char_pw);
		for (st_arr = 0; string[st_arr] != '\0'; st_arr++)
		{
			account->Settings.password[st_arr] = string[st_arr];
			b = islower(account->Settings.password[st_arr]);
			e = isupper(account->Settings.password[st_arr]);
			f = isdigit(account->Settings.password[st_arr]);
			if (b != 0)
			{
				if (c < 2)
				{
					c++;
				}
			}
			if (e != 0)
			{
				if (g < 2)
				{
					g++;
				}
			}
			if (f != 0)
			{
				if (h < 2)
				{
					h++;
				}
			}
			if (account->Settings.login[st_arr] == '!' || account->Settings.password[st_arr] == '@' || account->Settings.password[st_arr] == '#' || account->Settings.password[st_arr] == '$' || account->Settings.password[st_arr] == '^' || account->Settings.password[st_arr] == '&' || account->Settings.password[st_arr] == '*')
			{
				if (i < 2)
				{
					i++;
				}
			}
		}
	
		if (c + g + h + i != 8)
		{
			printf("SECURITY: Password must contain 2 of each:\n");
			printf("          Digit: 0-9\n");
			printf("          UPPERCASE character\n");
			printf("          lowercase character\n");
			printf("          symbol character: !@#$%%^&*\n");
		}

	} while (c + g + h + i != 8);

	return;
}

void updateAccount(struct Account* account)
{
	int a = 0, low = 0, high = 3, b = 0;

	do
	{
		printf("\nUpdate Account: %d (%s)\n", account->acc_num, account->Info.name);
		printf("----------------------------------------\n");
		printf("1) Update account type (current value: %c)\n", account->acc_type);
		printf("2) Person\n");
		printf("3) Login\n");
		printf("0) Done\n");
		printf("Selection: ");

		a = getIntFromRange(low, high);

		if (a == 1)
		{
			printf("\nEnter the account type (A=Agent | C=Customer): ");
			account->acc_type = getCharOption("AC");

			if (account->acc_type == 'A')
			{
				printf("\nAgent type accounts require a user login.  Please enter this information now:\n");
				getUserLogin(account);
			}
			else
			{
				for (b = 0; account->Settings.password[b] != '\0'; b++)
				{
					account->Settings.password[b] = '\0';
				}

				for (b = 0; account->Settings.login[b] != '\0'; b++)
				{
					account->Settings.login[b] = '\0';
				}
			}
		}

		if (a == 2)
		{
			updatePerson(account);
		}

		if (a == 3)
		{
			if (account->acc_type == 'C')
			{
				printf("\nERROR:  Customer account types don't have user logins!\n");
			}

			else
			{
				updateUserLogin(account);
			}
		}

	} while (a != 0);

	return;
}

void updatePerson(struct Account* account)
{
	int low = 0, high = 3, a = 0, min = 1, max = 30, b = 0;
	double c = 0;
	char string[50] = "";

	do
	{ 
		printf("\nPerson Update Options\n");
		printf("----------------------------------------\n");
		printf("1) Full name (current value: %s)\n", account->Info.name);
		printf("2) Household Income (current value: $%.2lf)\n", account->Info.income);
		printf("3) Country (current value: %s)\n", account->Info.res);
		printf("0) Done\n");
		printf("Selection: ");

		a = getIntFromRange(low, high);

		if (a == 1)
		{
			printf("\nEnter the person's full name (%d chars max): ", max);
			for (b = 0; account->Info.name[b] != '\0'; b++)
			{
				account->Info.name[b] = '\0';
			}
			getCString(string, min, max);
			for (b = 0; string[b] != '\0'; b++) 
			{
				account->Info.name[b] = string[b];
			}
		}

		if (a == 2)
		{
			printf("\nEnter the household Income: $");
			c = getPositiveDouble();
			account->Info.income = c;
		}

		if (a == 3)
		{
			printf("\nEnter the country (%d chars max.): ", max);
			for (b = 0; account->Info.res[b] != '\0'; b++)
			{
				account->Info.res[b] = '\0';
			}
			getCString(string, min, max);
			for (b = 0; string[b] != '\0'; b++)
			{
				account->Info.res[b] = toupper(string[b]);
			}
		}

	} while (a != 0);

	return;
}

void updateUserLogin(struct Account* account)
{
	int a = 0, low = 0, high = 1, pass = 8, b = 0, c = 0, d = 0, e = 0, f = 0, g = 0, h = 0, i = 0;
	char string[50] = "";

	do
	{
		printf("\nUser Login: %s - Update Options\n", account->Settings.login);
		printf("----------------------------------------\n");
		printf("1) Password\n");
		printf("0) Done\n");
		printf("Selection: ");

		a = getIntFromRange(low, high);

		if (a == 1)
		{
			do
			{
				c = 0;

				printf("\nEnter the password (must be %d chars in length): ", pass);
				for (b = 0; account->Settings.password[b] != '\0'; b++)
				{
					account->Settings.password[b] = '\0';
				}
				getCString(string, pass, pass);
				for (b = 0; string[b] != '\0'; b++)
				{
					account->Settings.password[b] = string[b];
					d = islower(account->Settings.password[b]);
					e = isupper(account->Settings.password[b]);
					f = isdigit(account->Settings.password[b]);
					if (d != 0)
					{
						if (c < 2)
						{
							c++;
						}
					}
					if (e != 0)
					{
						if (g < 2)
						{
							g++;
						}
					}
					if (f != 0)
					{
						if (h < 2)
						{
							h++;
						}
					}
					if (account->Settings.password[b] == '!' || account->Settings.password[b] == '@' || account->Settings.password[b] == '#' || account->Settings.password[b] == '$' || account->Settings.password[b] == '^' || account->Settings.password[b] == '&' || account->Settings.password[b] == '*')
					{
						if (i < 2)
						{
							i++;
						}
					}
				}

				if (c + g + h + i != 8)
				{
					printf("SECURITY: Password must contain 2 of each:\n");
					printf("          Digit: 0-9\n");
					printf("          UPPERCASE character\n");
					printf("          lowercase character\n");
					printf("          symbol character: !@#$%%^&*");
				}

			} while (c + g + h + i != 8);
		}

	} while (a != 0);

	return;
}
