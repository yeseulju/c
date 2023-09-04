#ifndef COMMON_HELPERS_H_
#define COMMON_HELPERS_H_
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>

int currentYear(void);
int getInteger(void);
int getPositiveInteger(void);
double getDouble(void);
double getPositiveDouble(void);
int getIntFromRange(int lower, int upper);
char getCharOption(char str[]);
void getCString(char* cvalue, int lower, int upper);
void clearStandardInputBuffer(void);
void commonHelpersTest(void);







#endif
