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
#include "commonHelpers.h"
#include <string.h>
#include "accountTicketingUI.h"
#include <ctype.h>
#include "ticket.h"



int loadTickets(struct Ticket* ticket, int Ticket_Size)
{
	int Records_Loaded = 0, Ticket_Index = 0, Message_Index = 0, Number_of_Records = 0, Value_of_fgetc = 0;
	FILE* Ticket_File = NULL;

	Ticket_File = fopen("tickets.txt", "r");
	if (Ticket_File != NULL)
	{
		do
		{
			Value_of_fgetc = fgetc(Ticket_File);
			if (Value_of_fgetc != EOF)
			{
				if ((char)Value_of_fgetc == '\n')
					Number_of_Records++;
			}
		} while (feof(Ticket_File) == 0);

		rewind(Ticket_File);

		for (Ticket_Index = 0; Ticket_Index < Ticket_Size && Ticket_Index < Number_of_Records; Ticket_Index++)
		{
			fscanf(Ticket_File, "%d|%d|%d|%[^|]|%d", &ticket[Ticket_Index].tick_num, &ticket[Ticket_Index].acc_num, &ticket[Ticket_Index].ticket, ticket[Ticket_Index].sub_ticket, &ticket[Ticket_Index].number);

			for (Message_Index = 0; Message_Index < ticket[Ticket_Index].number; Message_Index++)
			{
				fscanf(Ticket_File, "|%c|%[^|]|%[^|]", &ticket[Ticket_Index].Ticket[Message_Index].acc_type, ticket[Ticket_Index].Ticket[Message_Index].name, ticket[Ticket_Index].Ticket[Message_Index].detail);
			}
			
			fgetc(Ticket_File);

			Records_Loaded++;
		}
	}
	else
	{
		printf("Failed to open file/n");
	}

	fclose(Ticket_File);

	return Records_Loaded;
}

int saveTickets(struct Ticket* ticket, int Ticket_Size)
{
	int Records_Saved = 0, Ticket_Index = 0, Message_Index = 0;
	FILE* Ticket_File = NULL;

	Ticket_File = fopen("tickets.txt", "w");
	if (Ticket_File != NULL)
	{
		for (Ticket_Index = 0; Ticket_Index < Ticket_Size; Ticket_Index++)
		{
			if (ticket[Ticket_Index].acc_num != 0)
			{
				fprintf(Ticket_File, "%d|%d|%d|%s|%d|", ticket[Ticket_Index].tick_num, ticket[Ticket_Index].acc_num, ticket[Ticket_Index].ticket, ticket[Ticket_Index].sub_ticket, ticket[Ticket_Index].number);

				for (Message_Index = 0; Message_Index < ticket[Ticket_Index].number; Message_Index++)
				{
					fprintf(Ticket_File, "%c|%s|%s|", ticket[Ticket_Index].Ticket[Message_Index].acc_type, ticket[Ticket_Index].Ticket[Message_Index].name, ticket[Ticket_Index].Ticket[Message_Index].detail);
				}

				fprintf(Ticket_File, "\n");

				Records_Saved++;
			}
	}
}
	else
	{
	printf("Failed to open file/n");
	}

	fclose(Ticket_File);

	return Records_Saved;
}

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
			if (ticket[a].ticket == Ticket_Status && ticket[a].number == Number_of_Messages)
			{
				printf("%06d %5d %-15s %s %-30s %5d\n", ticket[a].tick_num, ticket[a].acc_num, ticket[a].Ticket->name, z, ticket[a].sub_ticket, ticket[a].number);
			}

		}
	}
	else if (Ticket_Status == 1 && Number_of_Messages == 2)
	{
		for (a = 0; a < Max_Tickets; a++)
		{
			if (ticket[a].ticket == Ticket_Status)
			{
				printf("%06d %5d %-15s %s %-30s %5d\n", ticket[a].tick_num, ticket[a].acc_num, ticket[a].Ticket->name, z, ticket[a].sub_ticket, ticket[a].number);
			}

		}
	}
	else if (Ticket_Status == 0 && Number_of_Messages == 2)
	{
		for (a = 0; a < Max_Tickets; a++)
		{
			if (ticket[a].ticket == Ticket_Status && ticket[a].tick_num != 0)
			{
				printf("%06d %5d %-15s %s %-30s %5d\n", ticket[a].tick_num, ticket[a].acc_num, ticket[a].Ticket->name, y, ticket[a].sub_ticket, ticket[a].number);
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

	ticket->acc_num = account.ACC_NUM;
	ticket->number = 1;
	ticket->ticket = 1;
	ticket->Ticket->acc_type = account.ACC_TYPE;
	strcpy(ticket->Ticket->name, account.Info.FULL_NAME);

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

			else if (ticket->number == 20)
			{
				printf("\nERROR: Message limit has been reached, call ITS Support!\n");
			}

			else
			{
				printf("\nEnter the ticket message details (150 chars. maximum). Press the ENTER key to submit:\n");
				getCString(x, 1, 150);
				strcpy(ticket->Ticket[ticket->number].detail, x);
				strcpy(ticket->Ticket[ticket->number].name, ticket->Ticket[0].name);
				ticket->Ticket[ticket->number].acc_type = ticket->Ticket[0].acc_type;
				ticket->number++;
			}
		}

		else if (a == 2)
		{
			if (ticket->ticket == 0)
			{
				printf("\nERROR: Ticket is closed - new messages are not permitted.\n");
			}

			else if (ticket->number == 20)
			{
				printf("\nERROR: Message limit has been reached, call ITS Support!\n");
			}

			else
			{
				printf("\nEnter the ticket message details (150 chars. maximum). Press the ENTER key to submit:\n");
				getCString(x, 1, 150);
				strcpy(ticket->Ticket[ticket->number].detail, x);
				strcpy(ticket->Ticket[ticket->number].name, account_login->Info.FULL_NAME);
				ticket->Ticket[ticket->number].acc_type = account_login->ACC_TYPE;
				ticket->number++;
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
