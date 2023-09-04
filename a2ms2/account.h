/*
	==================================================
	Assignment 2 (Milestone - 2):
	==================================================
	Name   : Yeseul Ju
	ID     : 154673198
	Email  : yju9@myseneca.ca
	Section: NEE
*/

#ifndef ACCOUNT_H_
#define ACCOUNT_H_

struct Person
{
	char name[30];
	int year;
	double income;
	char res[30];
};

struct UserLogin
{
	char login[10];
	char password[8];
};

struct Account
{
	int acc_num;
	char acc_type;

	struct Person Info;
	struct UserLogin Settings;
};

void getAccount(struct Account* account);

void getPerson(struct Account* account);

void getUserLogin(struct Account* account);

void updateAccount(struct Account* account);

void updatePerson(struct Account* account);

void updateUserLogin(struct Account* account);

#endif