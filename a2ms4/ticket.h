/*
	==================================================
	Assignment 2 (Milestone - 4):
	==================================================
	Name   : Yeseul Ju
	ID     : 154673198
	Email  : yju9@myseneca.ca
	Section: NEE
*/

#ifndef TICKET_H_
#define TICKET_H_

struct Message
{
	char acc_type;
	char name[30];
	char detail[150];

};

struct Ticket
{
	int tick_num;
	int acc_num;
	int ticket;
	char sub_ticket[30];
	int number;
	
	struct Message Ticket[20];

};

int loadTickets(struct Ticket* ticket, int Ticket_Size);

int saveTickets(struct Ticket* ticket, int Ticket_Size);

void TicketHeader(void);

void MessageHeader(const struct Ticket ticket);

void DisplayTicket(const struct Ticket ticket[], int Ticket_Status, int Number_of_Messages, int Max_Tickets);

void DisplayMessage(const struct Ticket ticket, int Number_of_Messages);

void NewTicket(struct Ticket* ticket, const struct Account account);

void TicketUpdate(struct Ticket* ticket, const struct Account* account_login);


#endif