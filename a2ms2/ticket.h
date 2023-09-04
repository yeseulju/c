/*
	==================================================
	Assignment 2 (Milestone - 2):
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
	char ticket;
	char sub_ticket[30];
	int num;
	
	struct Message Ticket[20];

};

void TicketHeader(void);

void MessageHeader(const struct Ticket ticket);

void DisplayTicket(const struct Ticket ticket[], int Ticket_Status, int Number_of_Messages, int Max_Tickets);

void DisplayMessage(const struct Ticket ticket, int Number_of_Messages);

void NewTicket(struct Ticket* ticket, const struct Account account);

void TicketUpdate(struct Ticket* ticket, const struct Account* account_login);


#endif