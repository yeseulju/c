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
#include "commonHelpers.h"
#include <string.h>
#include "accountTicketingUI.h"
#include <ctype.h>
#include "ticket.h"

void TicketHeader(void)
{
	printf("------ ----- --------------- ------ ------------------------------ --------\n");
	printf("Ticket Acct# Full Name       Status Subject                        Messages\n");
	printf("------ ----- --------------- ------ ------------------------------ --------\n");

	return;
}

void MessageHeader(const struct Ticket ticket)
{
	char a[30] = "ACTIVE";
	char b[30] = "CLOSED";

	if (ticket.ticket == 1)
	{
		printf("\n================================================================================\n");
		printf("%06d (%s) Re: %s\n", ticket.tick_num, a, ticket.sub_ticket);
		printf("================================================================================\n");
	}

	else
	{
		printf("\n================================================================================\n");
		printf("%06d (%s) Re: %s\n", ticket.tick_num, b, ticket.sub_ticket);
		printf("================================================================================\n");
	}
	return;
}

void DisplayTicket(const struct Ticket ticket[], int Ticket_Status, int Number_of_Messages, int Max_Tickets)
{
	int a = 0;
	char z[10] = "ACTIVE", y[10] = "CLOSED";

	 
	if (Ticket_Status == 1 && Number_of_Messages == 1)
	{
		for (a = 0; a < Max_Tickets; a++)
		{
			if (ticket[a].ticket == Ticket_Status && ticket[a].num == Number_of_Messages)
			{
				printf("%06d %5d %-15s %s %-30s %5d\n", ticket[a].tick_num, ticket[a].acc_num, ticket[a].Ticket->name, z, ticket[a].sub_ticket, ticket[a].num);
			}

		}
	}
	else if (Ticket_Status == 1 && Number_of_Messages == 2)
	{
		for (a = 0; a < Max_Tickets; a++)
		{
			if (ticket[a].ticket == Ticket_Status)
			{
				printf("%06d %5d %-15s %s %-30s %5d\n", ticket[a].tick_num, ticket[a].acc_num, ticket[a].Ticket->name, z, ticket[a].sub_ticket, ticket[a].num);
			}

		}
	}
	else if (Ticket_Status == 0 && Number_of_Messages == 2)
	{
		for (a = 0; a < Max_Tickets; a++)
		{
			if (ticket[a].ticket == Ticket_Status && ticket[a].tick_num != 0)
			{
				printf("%06d %5d %-15s %s %-30s %5d\n", ticket[a].tick_num, ticket[a].acc_num, ticket[a].Ticket->name, y, ticket[a].sub_ticket, ticket[a].num);
			}

		}
	}
	
	printf("------ ----- --------------- ------ ------------------------------ --------");

	return;
}

void DisplayMessage(const struct Ticket ticket, int Number_of_Messages)
{
	int a = 0;
	char z[10] = "CUSTOMER", y[10] = "AGENT";

	for (a = 0; a <= Number_of_Messages; a++)
	{
		if (ticket.Ticket[a].acc_type == 'C')
		{
			printf("%s (%s):\n   %s\n\n", z, ticket.Ticket[a].name, ticket.Ticket[a].detail);
		}
		else if (ticket.Ticket[a].acc_type == 'A')
		{
		
			printf("%s (%s):\n   %s\n\n", y, ticket.Ticket[a].name, ticket.Ticket[a].detail);
			
		}
	}
	pauseExecution();

	return;
}

void NewTicket(struct Ticket* ticket, const struct Account account)
{
	char z[30] = "", y[150] = "";

	printf("\nNew Ticket (Ticket#:%06d)\n", ticket->tick_num);
	printf("----------------------------------------\n");
	
	printf("Enter the ticket SUBJECT (30 chars. maximum): ");
	getCString(z , 1, 30);
	strcpy(ticket->sub_ticket, z);

	printf("\nEnter the ticket message details (150 chars. maximum). Press the ENTER key to submit:\n");
	getCString(y, 1, 150);
	strcpy(ticket->Ticket->detail, y);

	ticket->acc_num = account.acc_num;
	ticket->num = 1;
	ticket->ticket = 1;
	ticket->Ticket->acc_type = account.acc_type;
	strcpy(ticket->Ticket->name, account.Info.name);

	printf("\n*** New ticket created! ***\n\n");
	pauseExecution();

	return;
}

void TicketUpdate(struct Ticket* ticket, const struct Account* account_login)
{
	int a = 0;
	char z[10] = "ACTIVE", y[10] = "CLOSED", x[150] = "", v = 0;

	do
	{

		printf("\n----------------------------------------\n");
		printf("Ticket %06d - Update Options\n", ticket->tick_num);
		printf("----------------------------------------\n");
		if (ticket->ticket == 1)
		{
			printf("Status  : %s\n", z);
		}
		else 
		{
			printf("Status  : %s\n", y);
		}
		printf("Subject : %s\n", ticket->sub_ticket);
		printf("Acct#   : %d\n", ticket->acc_num);
		printf("Customer: %s\n", ticket->Ticket->name);
		printf("----------------------------------------\n");
		printf("1) Add CUSTOMER message\n");
		printf("2) Add AGENT message\n");
		printf("3) Close ticket\n");
		printf("4) Re-activate ticket\n");
		printf("0) Done\n");
		printf("Selection: ");

		a = getIntFromRange(0, 4);

		if (a == 1)
		{
			if (ticket->ticket == 0)
			{
				printf("\nERROR: Ticket is closed - new messages are not permitted.\n");
			}

			else if (ticket->num == 20)
			{
				printf("\nERROR: Message limit has been reached, call ITS Support!\n");
			}

			else
			{
				printf("\nEnter the ticket message details (150 chars. maximum). Press the ENTER key to submit:\n");
				getCString(x, 1, 150);
				strcpy(ticket->Ticket[ticket->num].detail, x);
				strcpy(ticket->Ticket[ticket->num].name, ticket->Ticket[0].name);
				ticket->Ticket[ticket->num].acc_type = ticket->Ticket[0].acc_type;
				ticket->num++;
			}
		}

		else if (a == 2)
		{
			if (ticket->ticket == 0)
			{
				printf("\nERROR: Ticket is closed - new messages are not permitted.\n");
			}

			else if (ticket->num == 20)
			{
				printf("\nERROR: Message limit has been reached, call ITS Support!\n");
			}

			else
			{
				printf("\nEnter the ticket message details (150 chars. maximum). Press the ENTER key to submit:\n");
				getCString(x, 1, 150);
				strcpy(ticket->Ticket[ticket->num].detail, x);
				strcpy(ticket->Ticket[ticket->num].name, account_login->Info.name);
				ticket->Ticket[ticket->num].acc_type = account_login->acc_type;
				ticket->num++;
			}
		}

		else if (a == 3)
		{
			if (ticket->ticket == 0)
			{
				printf("\nERROR: Ticket is already closed!\n");
			}

			else
			{
				printf("\nAre you sure you CLOSE this ticket? ([Y]es|[N]o): ");
				v = getCharOption("YN");
				
				if (v == 'Y')
				{
					ticket->ticket = 0;
					printf("\n*** Ticket closed! ***\n");
				}
			}
		}

		else if (a == 4)
		{
			if (ticket->ticket == 1)
			{
				printf("\nERROR: Ticket is already active!\n");
			}

			else
			{
				printf("\nAre you sure you want to RE-ACTIVATE this closed ticket? ([Y]es|[N]o): ");
				v = getCharOption("YN");

				if (v == 'Y')
				{
					ticket->ticket = 1;
					printf("\n*** Ticket re-activated! ***\n");
				}
			}
		}

		else
		{
			;
		}

	} while (a != 0);
}
