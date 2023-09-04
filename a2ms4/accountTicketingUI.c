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
#include "accountTicketingUI.h"
#include <string.h>
#include "ticket.h"

void displayAccountDetailHeader(void)
{
	printf("Acct# Acct.Type Full Name       Birth Income      Country    Login      Password\n");
	printf("----- --------- --------------- ----- ----------- ---------- ---------- --------\n");
	
	return;
}

void displayAccountDetailRecord(const struct Account account)
{
	int i = 0, j = 0;
	char a[10] = "AGENT";
	char b[10] = "CUSTOMER";
	char c[30] = "";

	for (i = 0, j = 1; account.Settings.PASS_LOGIN[i] != '\0'; i++, j++)
	{
		c[i] = account.Settings.PASS_LOGIN[i];

		if (j % 2 == 0)
			c[i] = '*';
	}

	if (account.ACC_TYPE == 'A')
		printf("%05d %-9s %-15s %5d %11.2lf %-10s %-10s %8s\n", account.ACC_NUM, a, account.Info.FULL_NAME, account.Info.BIRTH_YEAR, account.Info.HOUSE_INCOME, account.Info.CUS_RES, account.Settings.USER_LOGIN, c);
	else
		printf("%05d %-9s %-15s %5d %11.2lf %-10s %-10s %8s\n", account.ACC_NUM, b, account.Info.FULL_NAME, account.Info.BIRTH_YEAR, account.Info.HOUSE_INCOME, account.Info.CUS_RES, account.Settings.USER_LOGIN, c);

	return;
}

void pauseExecution(void)
{
	printf("<< ENTER key to Continue... >>");
	clearStandardInputBuffer();
	getchar();
}

void pauseExecution1(void)
{
	printf("<< ENTER key to Continue... >>");
	clearStandardInputBuffer();
}

void displayAllAccountDetailRecords(const struct Account account[], int elements)
{
	int a = 0;
	
	printf("\n");

	displayAccountDetailHeader();
	
	for (a = 0; a < elements; a++)
	{
		if (account[a].ACC_NUM != 0)
		{
			displayAccountDetailRecord(account[a]);
		}
	}	
	printf("\n");
	pauseExecution1();

	return;
}

int findTicketIndexByAcctNum(int match, const struct Ticket account[], int elements, int prompt)
{
	int a = 0, b = -1, c = 0, d = 0, e = 0;


	if (prompt != 0)
	{
		printf("Enter the account#: ");
		scanf("%d", &c);

		for (a = 0; a < elements; a++)
		{
			if (account[a].acc_num == c)
			{
				b = a;
			}

		}
	}

	else
	{
		for (a = 0, d = 0; a < elements && e == 0; a++, d++)
		{
			if (account[d].acc_num == match)
			{
				b = d;
				e = -1;
			}

		}
	}

	return b;
}

int findTicketIndexByTickNum(int match, const struct Ticket ticket[], int elements, int prompt)
{
	int a = 0, b = -1, c = -1, d = 0, e = 0;

	if (prompt != 0)
	{
		printf("\n\nEnter the ticket number to view the messages or\n0 to return to previous menu: ");
		scanf("%d", &c);
		
		for (a = 0; a < elements; a++)
		{
			if (ticket[a].tick_num == c)
			{
				b = a;
			}

		}

	}
	
	else 
	{

		for (a = 0, d = 0; a < elements && e == 0; a++, d++)
		{
			if (ticket[d].tick_num == match)
			{
				b = d;
				e = -1;
			}
		}
	}
	
	if (c == 0) 
	{
		b = -2;
	}

	return b;
}

int findAccountIndexByAcctNum(int match, const struct Account account[], int elements, int prompt)
{
	int a = 0, b = -1, c = 0, d = 0, e = 0;
	

	if (prompt != 0)
	{
		printf("Enter the account#: ");
		scanf("%d", &c);

		for (a = 0; a < elements; a++)
		{
			if (account[a].ACC_NUM == c)
			{
				b = a;
			}
		
		}
	}

	else
	{
		for (a = 0, d = 0; a < elements && e == 0; a++, d++)
		{
			if (account[d].ACC_NUM == match)
			{
				b = d;
				e = -1;
			}
	
		}
	}

	return b;
}

int menuLogin(const struct Account account[], int elements)
{
	int low = 0, high = 1, a = 0, c = 0, b = 0, d = 0, e = 0;
	char z = 0, y[100] = "", x[100] = "";

	printf("==============================================\n");
	printf("Account Ticketing System - Login\n");
	printf("==============================================\n");
	printf("1) Login to the system\n");
	printf("0) Exit application\n");
	printf("----------------------------------------------\n\n");
	printf("Selection: ");
	
	a = getIntFromRange(low, high);

	if (a == 1)
	{
		for (d = 2; d != -1; d--)
		{
			e = 0;

			printf("\nEnter the account#: ");
			b = getPositiveInteger();
			c = findAccountIndexByAcctNum(b, account, elements, 0);
			if (c != -1)
			{
				e++;
			}
			printf("User Login        : ");
			getCString(y, 1, 100);
			if (strcmp(account[c].Settings.USER_LOGIN, y) == 0)
			{
				e++;
			}
			printf("Password          : ");
			getCString(x, 1, 100);
			if (strcmp(account[c].Settings.PASS_LOGIN, x) == 0)
			{
				e++;
			}
			if (e == 3)
			{
				d = 0;

			}
			if (e != 3)
			{
				printf("INVALID user login/password combination! [attempts remaining:%d]\n", d);
				c = -2;
			}

		}
	}

	else
	{
		printf("\nAre you sure you want to exit? ([Y]es|[N]o): ");
		 
		z = getCharOption("yYnN");

		if (z == 'y' || z == 'Y')
		{
			c = -1;
		}
		else
		{
			c = -3;
		}

	
	}

	return c;
}

void menuAgent(struct AccountTicketingData account[], const struct Account* account_login)
{
	int low = 0, high = 9, a = 0, b = 0, c = 0, d = 0, e = 0, f = 0, g = 0, h = 0, i = 0, Saved_Records = 0;
	char z = 0;

	do
	{
		printf("\nAGENT: %s (%d)\n", account_login->Info.FULL_NAME, account_login->ACC_NUM);
		printf("==============================================\n");
		printf("Account Ticketing System - Agent Menu\n");
		printf("==============================================\n");
		printf("1) Add a new account\n");
		printf("2) Modify an existing account\n");
		printf("3) Remove an account\n");
		printf("4) List accounts: detailed view\n");
		printf("----------------------------------------------\n");
		printf("5) List new tickets\n");
		printf("6) List active tickets\n");
		printf("7) List closed tickets\n");
		printf("8) Add a new ticket\n");
		printf("9) Manage a ticket\n");
		printf("----------------------------------------------\n");
		printf("0) Logout\n\n");
		printf("Selection: ");

		a = getIntFromRange(low, high);

		if (a == 1)
		{
			b = findAccountIndexByAcctNum(0, account->accounts, account->ACCOUNT_MAX_SIZE, 0);
			
			if (b == -1)
			{
				printf("\nERROR: Account listing is FULL, call ITS Support!\n\n");
				pauseExecution1();
			}
			else
			{
				for (c = 0; c < account->ACCOUNT_MAX_SIZE; c++)
				{
					if (account->accounts[c].ACC_NUM > account->accounts[e].ACC_NUM)
					{
						e = c;
					}
				}

				account->accounts[b].ACC_NUM = (account->accounts[e].ACC_NUM + 1);
				getAccount(&account->accounts[b]);
				printf("\n*** New account added! ***\n\n");
				pauseExecution();
			}
		}

		if (a == 2)
		{
			printf("\n");
			b = findAccountIndexByAcctNum(0, account->accounts, account->ACCOUNT_MAX_SIZE, 1);
			updateAccount(&account->accounts[b]);
		}

		if (a == 3)
		{
			printf("\n");
			b = findAccountIndexByAcctNum(0, account->accounts, account->ACCOUNT_MAX_SIZE, 1);
			
			if (account->accounts[b].ACC_NUM == account_login->ACC_NUM)
			{
				printf("\nERROR: You can't remove your own account!\n\n");
				pauseExecution();
			}
			else
			{
				printf("\n");
				displayAccountDetailHeader();
				displayAccountDetailRecord(account->accounts[b]);
				printf("\nAre you sure you want to remove this record? ([Y]es|[N]o): ");
				z = getCharOption("yYnN");

				if (z == 'Y' || z == 'y')
				{
					do
					{
						f = findTicketIndexByAcctNum(account->accounts[b].ACC_NUM, account->tickets, account->ACCOUNT_MAX_SIZE, 0);
					
						if (f != -1)
						{
							for (i = 0; i < account->tickets[f].number; i++)
							{
								account->tickets[f].Ticket[i].acc_type = 0;
								strcpy(account->tickets[f].Ticket[i].name, "\0");
								strcpy(account->tickets[f].Ticket[i].detail, "\0");
							}
								account->tickets[f].acc_num = 0;
								account->tickets[f].tick_num = 0;
								account->tickets[f].ticket = 0;
								account->tickets[f].number = 0;
								strcpy(account->tickets[f].sub_ticket, "\0");
								
								g++;
						}

					} while (f != -1);
					
					account->accounts[b].ACC_NUM = 0;
					account->accounts[b].ACC_TYPE = '0';
					for (d = 0; account->accounts[b].Info.FULL_NAME[d] != '\0'; d++)
					{
						account->accounts[b].Info.FULL_NAME[d] = '\0';
					}
					account->accounts[b].Info.BIRTH_YEAR = 0;
					account->accounts[b].Info.HOUSE_INCOME = 0;
					for (d = 0; account->accounts[b].Info.CUS_RES[d] != '\0'; d++)
					{
						account->accounts[b].Info.CUS_RES[d] = '\0';
					}
					for (d = 0; account->accounts[b].Settings.USER_LOGIN[d] != '\0'; d++)
					{
						account->accounts[b].Settings.USER_LOGIN[d] = '\0';
					}
					for (d = 0; account->accounts[b].Settings.PASS_LOGIN[d] != '\0'; d++)
					{
						account->accounts[b].Settings.PASS_LOGIN[d] = '\0';
					}
					printf("\n*** Account Removed! (%d ticket(s) removed) ***\n\n", g);
					g = 0;
					pauseExecution();
				}
			}
		}

		if (a == 4)
		{
			displayAllAccountDetailRecords(account->accounts, account->ACCOUNT_MAX_SIZE);
		}

		if (a == 5)
		{
			printf("\n");

			do
			{
				TicketHeader();
				DisplayTicket(account->tickets, 1, 1, account->TICKET_MAX_SIZE);
				b = findTicketIndexByTickNum(0, account->tickets, account->TICKET_MAX_SIZE, 1);

				if (b == -1)
				{
					printf("\nERROR: Invalid ticket number.\n\n");
					pauseExecution();
					printf("\n");
				}

				else if (b == -2)
				{
					;
				}

				else
				{
					MessageHeader(account->tickets[b]);
					DisplayMessage(account->tickets[b], account->tickets[b].number);
					printf("\n");
				}

			} while (b != -2);
		}

		if (a == 6)
		{
			printf("\n");

			do
			{
				TicketHeader();
				DisplayTicket(account->tickets, 1, 2, account->TICKET_MAX_SIZE);
				b = findTicketIndexByTickNum(0, account->tickets, account->TICKET_MAX_SIZE, 1);

				if (b == -1)
				{
					printf("\nERROR: Invalid ticket number.\n\n");
					pauseExecution();
					printf("\n");
				}

				else if (b == -2)
				{
					;
				}

				else
				{
					MessageHeader(account->tickets[b]);
					DisplayMessage(account->tickets[b], account->tickets[b].number);
					printf("\n");
				}

			} while (b != -2);
		}

		if (a == 7)
		{
			printf("\n");

			do
			{
				TicketHeader();
				DisplayTicket(account->tickets, 0, 2, account->TICKET_MAX_SIZE);
				b = findTicketIndexByTickNum(0, account->tickets, account->TICKET_MAX_SIZE, 1);

				if (b == -1 || account->tickets[b].ticket != 0)
				{
					printf("\nERROR: Invalid ticket number.\n\n");
					pauseExecution();
					printf("\n");
				}

				else if (b == -2)
				{
					;
				}

				else
				{
					MessageHeader(account->tickets[b]);
					DisplayMessage(account->tickets[b], account->tickets[b].number);
					printf("\n");
				}

			} while (b != -2);
		}

		if (a == 8)
		{
			printf("\n");

			h = findTicketIndexByTickNum(0, account->tickets, account->TICKET_MAX_SIZE, 0);
			if (h == -1)
			{
				printf("\nERROR: Ticket listing is FULL, call ITS Support!\n");
				pauseExecution();
			}
			b = findAccountIndexByAcctNum(0, account->accounts, account->ACCOUNT_MAX_SIZE, 1);
			if (account->accounts[b].ACC_TYPE == 'A')
			{
				printf("\nERROR: Agent accounts can't have tickets!\n\n");
				pauseExecution();
			}
			else
			{
				printf("\n");
				displayAccountDetailHeader();
				displayAccountDetailRecord(account->accounts[b]);
				printf("\n");
				printf("Add a new ticket for this customer? ([Y]es|[N]o): ");
				z = getCharOption("YN");

				if (z == 'Y')
				{
					for (c = 0; c < account->TICKET_MAX_SIZE; c++)
					{
						if (account->tickets[c].tick_num > account->tickets[e].tick_num)
						{
							e = c;
						}
					}

					account->tickets[h].tick_num = (account->tickets[e].tick_num + 1);

					NewTicket(&account->tickets[h], account->accounts[b]);
					
				}
				else
				{
					;
				}
			}
		}

		if (a == 9)
		{
			printf("\nEnter ticket number: ");
			c = getPositiveInteger();
			b = findTicketIndexByTickNum(c, account->tickets, account->TICKET_MAX_SIZE, 0);

			if (b == -1)
			{
				printf("\nERROR: Invalid ticket number.\n\n");
				pauseExecution();
				printf("\n");
			}
			
			else
			{
				TicketUpdate(&account->tickets[b], account_login);
			}
		}

		if (a == 0)
		{
			printf("\nSaving session modifications...\n");
			Saved_Records = saveAccounts(account->accounts, account->ACCOUNT_MAX_SIZE);
			printf("   %d account(s) saved.\n", Saved_Records);
			Saved_Records = saveTickets(account->tickets, account->TICKET_MAX_SIZE);
			printf("   %d ticket(s) saved.\n", Saved_Records);
			printf("### LOGGED OUT ###\n");
		}

	} while (a != 0);

	return;

}

void applicationStartup(struct AccountTicketingData account[])
{
	int a = 0;
	
	do 
	{
		a = menuLogin(account->accounts, account->ACCOUNT_MAX_SIZE);
		
		if (a == -1)
		{
		printf("\n==============================================\n");
		printf("Account Ticketing System - Terminated\n");
		printf("==============================================");

		}

		else if(a == -2)
		{
			printf("\nERROR:  Access Denied.\n\n");
			pauseExecution();
		}

		else if (a >= 0)
		{
			menuAgent(account, &account->accounts[a]);	
		}
		printf("\n");

	} while (a != -1);

	return;
}


