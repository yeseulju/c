#ifndef ACCOUNT_H_
#define ACCOUNT_H_

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

struct Account
{
	int number;
	char type;
};

struct Person
{
	char name[31];
	int year;
	double income;
	char country[31];
};

struct UserLogin
{
	char login[11];
	char password[9];
};
void getAccount(struct Account* account);
void getPerson(struct Person* person);
void getUser(struct UserLogin* login);
void commonHelpersTest(void);
void displayAccount(const struct Account account, const struct UserLogin login, const struct Person person);


#endif
