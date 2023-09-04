/*
	==================================================
	Assignment 2 (Milestone - 4):
	==================================================
	Name   : Yeseul Ju
	ID     : 154673198
	Email  : yju9@myseneca.ca
	Section: NEE
*/

#ifndef COMMON_HELPERS_H_
#define COMMON_HELPERS_H_

int currentYear(void);

void clearStandardInputBuffer(void);

int getInteger(void);

int getPositiveInteger(void);

double getDouble(void);

double getPositiveDouble(void);

int getIntFromRange(int lower, int upper);

char getCharOption(char str[]);

void getCString(char* cvalue, int lower, int upper);

#endif