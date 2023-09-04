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
#include <stdio.h>
#include "account.h"
#include "commonHelpers.h"
#include <string.h>
#include "accountTicketingUI.h"
#include <ctype.h>

int loadAccounts(struct Account* account, int Account_Size)
{
	int Records_Loaded = 0, Account_Index = 0, Number_of_Records = 0, Value_of_fgetc = 0;
	FILE *Account_File = NULL;

	Account_File = fopen("accounts.txt", "r");
	if (Account_File != NULL)
	{
		do 
		{
			Value_of_fgetc = fgetc(Account_File);
			if (Value_of_fgetc != EOF) 
			{
				if ((char)Value_of_fgetc == '\n')
					Number_of_Records++;
			}
		} while (feof(Account_File) == 0);

		rewind(Account_File);

		for (Account_Index = 0; Account_Index < Account_Size && Account_Index < Number_of_Records; Account_Index++)
		{
			fscanf(Account_File, "%d~%c~%[^~]~%d~%lf~%[^\n~]", &account[Account_Index].ACC_NUM, &account[Account_Index].ACC_TYPE, account[Account_Index].Info.FULL_NAME, &account[Account_Index].Info.BIRTH_YEAR, &account[Account_Index].Info.HOUSE_INCOME, account[Account_Index].Info.CUS_RES);

			if (account[Account_Index].ACC_TYPE == 'A')
			{
				fscanf(Account_File, "~%[^~]~%[^\n]", account[Account_Index].Settings.USER_LOGIN, account[Account_Index].Settings.PASS_LOGIN);
				
				Records_Loaded++;
			}
			else
			{
				Records_Loaded++;
			}
		}
	}
	else
	{
		printf("Failed to open file/n");
	}
	
	fclose(Account_File);

	return Records_Loaded;
}

int saveAccounts(struct Account* account, int Account_Size)
{
	int Records_Saved = 0, Account_Index = 0;
	FILE* Account_File = NULL;


	Account_File = fopen("accounts.txt", "w");
	if (Account_File != NULL)
	{
		for (Account_Index = 0; Account_Index < Account_Size; Account_Index++)
		{
			if (account[Account_Index].ACC_NUM != 0)
			{
				fprintf(Account_File, "%d~%c~%s~%d~%.2lf~%s", account[Account_Index].ACC_NUM, account[Account_Index].ACC_TYPE, account[Account_Index].Info.FULL_NAME, account[Account_Index].Info.BIRTH_YEAR, account[Account_Index].Info.HOUSE_INCOME, account[Account_Index].Info.CUS_RES);

				if (account[Account_Index].ACC_TYPE == 'A')
				{
					fprintf(Account_File, "~%s~%s\n", account[Account_Index].Settings.USER_LOGIN, account[Account_Index].Settings.PASS_LOGIN);

					Records_Saved++;
				}
				else
				{
					fprintf(Account_File, "\n");

					Records_Saved++;
				}
			}
		}
	}
	else
	{
		printf("Failed to open file/n");
	}

	fclose(Account_File);

	return Records_Saved;
}

void getAccount(struct Account *account)
{
	printf("\nNew Account Data (Account#:%d)\n", account->ACC_NUM);
	printf("----------------------------------------\n");
	printf("Enter the account type (A=Agent | C=Customer): ");
	
	account->ACC_TYPE = getCharOption("AC");

	getPerson(account);

	if (account->ACC_TYPE == 'A')
	{
		getUserLogin(account);
	}

	else
	{
		account->Settings.USER_LOGIN[0] = 0;
		account->Settings.PASS_LOGIN[0] = 0;
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
	account->Info.FULL_NAME[st_arr] = string[st_arr];
	}

	min_year = currentYear() - max_age;
	max_year = currentYear() - min_age;

	printf("Enter birth year (current age must be between %d and %d): ", min_age, max_age);
	
	account->Info.BIRTH_YEAR = getIntFromRange(min_year, max_year);

	printf("Enter the household Income: $");
	
	account->Info.HOUSE_INCOME = getPositiveDouble();

	printf("Enter the country (%d chars max.): ", max_char_p);
	
	getCString(string, min_char_p, max_char_p);
	for (st_arr = 0; string[st_arr] != '\0'; st_arr++)
	{
		account->Info.CUS_RES[st_arr] = toupper(string[st_arr]);
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

		strcpy(account->Settings.USER_LOGIN, "\0");
		getCString(string, min_char_p, max_char_l);
		for (st_arr = 0; string[st_arr] != '\0'; st_arr++)
		{

			d = isspace(account->Settings.USER_LOGIN[st_arr]);
			if (d != 0)
			{
				a = 1;
			}
			else
			{
			strcpy(account->Settings.USER_LOGIN, string);
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
			account->Settings.PASS_LOGIN[st_arr] = string[st_arr];
			b = islower(account->Settings.PASS_LOGIN[st_arr]);
			e = isupper(account->Settings.PASS_LOGIN[st_arr]);
			f = isdigit(account->Settings.PASS_LOGIN[st_arr]);
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
			if (account->Settings.PASS_LOGIN[st_arr] == '!' || account->Settings.PASS_LOGIN[st_arr] == '@' || account->Settings.PASS_LOGIN[st_arr] == '#' || account->Settings.PASS_LOGIN[st_arr] == '$' || account->Settings.PASS_LOGIN[st_arr] == '^' || account->Settings.PASS_LOGIN[st_arr] == '&' || account->Settings.PASS_LOGIN[st_arr] == '*')
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
		printf("\nUpdate Account: %d (%s)\n", account->ACC_NUM, account->Info.FULL_NAME);
		printf("----------------------------------------\n");
		printf("1) Update account type (current value: %c)\n", account->ACC_TYPE);
		printf("2) Person\n");
		printf("3) Login\n");
		printf("0) Done\n");
		printf("Selection: ");

		a = getIntFromRange(low, high);

		if (a == 1)
		{
			printf("\nEnter the account type (A=Agent | C=Customer): ");
			account->ACC_TYPE = getCharOption("AC");

			if (account->ACC_TYPE == 'A')
			{
				printf("\nAgent type accounts require a user login.  Please enter this information now:\n");
				getUserLogin(account);
			}
			else
			{
				for (b = 0; account->Settings.PASS_LOGIN[b] != '\0'; b++)
				{
					account->Settings.PASS_LOGIN[b] = '\0';
				}

				for (b = 0; account->Settings.USER_LOGIN[b] != '\0'; b++)
				{
					account->Settings.USER_LOGIN[b] = '\0';
				}
			}
		}

		if (a == 2)
		{
			updatePerson(account);
		}

		if (a == 3)
		{
			if (account->ACC_TYPE == 'C')
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
		printf("1) Full name (current value: %s)\n", account->Info.FULL_NAME);
		printf("2) Household Income (current value: $%.2lf)\n", account->Info.HOUSE_INCOME);
		printf("3) Country (current value: %s)\n", account->Info.CUS_RES);
		printf("0) Done\n");
		printf("Selection: ");

		a = getIntFromRange(low, high);

		if (a == 1)
		{
			printf("\nEnter the person's full name (%d chars max): ", max);
			for (b = 0; account->Info.FULL_NAME[b] != '\0'; b++)
			{
				account->Info.FULL_NAME[b] = '\0';
			}
			getCString(string, min, max);
			for (b = 0; string[b] != '\0'; b++) 
			{
				account->Info.FULL_NAME[b] = string[b];
			}
		}

		if (a == 2)
		{
			printf("\nEnter the household Income: $");
			c = getPositiveDouble();
			account->Info.HOUSE_INCOME = c;
		}

		if (a == 3)
		{
			printf("\nEnter the country (%d chars max.): ", max);
			for (b = 0; account->Info.CUS_RES[b] != '\0'; b++)
			{
				account->Info.CUS_RES[b] = '\0';
			}
			getCString(string, min, max);
			for (b = 0; string[b] != '\0'; b++)
			{
				account->Info.CUS_RES[b] = toupper(string[b]);
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
		printf("\nUser Login: %s - Update Options\n", account->Settings.USER_LOGIN);
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
				for (b = 0; account->Settings.PASS_LOGIN[b] != '\0'; b++)
				{
					account->Settings.PASS_LOGIN[b] = '\0';
				}
				getCString(string, pass, pass);
				for (b = 0; string[b] != '\0'; b++)
				{
					account->Settings.PASS_LOGIN[b] = string[b];
					d = islower(account->Settings.PASS_LOGIN[b]);
					e = isupper(account->Settings.PASS_LOGIN[b]);
					f = isdigit(account->Settings.PASS_LOGIN[b]);
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
					if (account->Settings.PASS_LOGIN[b] == '!' || account->Settings.PASS_LOGIN[b] == '@' || account->Settings.PASS_LOGIN[b] == '#' || account->Settings.PASS_LOGIN[b] == '$' || account->Settings.PASS_LOGIN[b] == '^' || account->Settings.PASS_LOGIN[b] == '&' || account->Settings.PASS_LOGIN[b] == '*')
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
