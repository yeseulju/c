/*
	==================================================
	Assignment 2 (Milestone - 4):
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
	char FULL_NAME[30];
	int BIRTH_YEAR;
	double HOUSE_INCOME;
	char CUS_RES[30];
};

struct UserLogin
{
	char USER_LOGIN[10];
	char PASS_LOGIN[8];
};

struct Account
{
	int ACC_NUM;
	char ACC_TYPE;

	struct Person Info;
	struct UserLogin Settings;
};

int loadAccounts(struct Account* account, int Account_Size);

int saveAccounts(struct Account* account, int Account_Size);

void getAccount(struct Account* account);

void getPerson(struct Account* account);

void getUserLogin(struct Account* account);

void updateAccount(struct Account* account);

void updatePerson(struct Account* account);

void updateUserLogin(struct Account* account);

#endif