/*
	==================================================
	Assignment 2 (Milestone - 4):
	==================================================
	Name   : Yeseul Ju
	ID     : 154673198
	Email  : yju9@myseneca.ca
	Section: NEE
*/

#ifndef ACCOUNT_TICKETINGUI_H_
#define ACCOUNT_TICKETINGUI_H_
#include "account.h"
#include "ticket.h"

struct AccountTicketingData
{
	struct Account* accounts; 
	const int ACCOUNT_MAX_SIZE; 

	struct Ticket* tickets;
	const int TICKET_MAX_SIZE;
};


void displayAccountDetailHeader(void);

void displayAccountDetailRecord(const struct Account account);

void applicationStartup(struct AccountTicketingData account[]);

int menuLogin(const struct Account account[], int elements);

void menuAgent(struct AccountTicketingData account[], const struct Account* account_login);

int findAccountIndexByAcctNum(int match, const struct Account account[], int elements, int prompt);

int findTicketIndexByAcctNum(int match, const struct Ticket account[], int elements, int prompt);

int findTicketIndexByTickNum(int match, const struct Ticket ticket[], int elements, int prompt);

void displayAllAccountDetailRecords(const struct Account account[], int elements);

void pauseExecution(void); 

void pauseExecution1(void);

#endif
