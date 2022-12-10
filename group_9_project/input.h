// PROG71985 - Fall 2022 - Group Project
// Group 9: Jonathan Ward, Drasti Patel, Komalpreet Kaur
// Jonathan Ward - based on examples from Prof. Steve Hendrikse

// interface for common user input routines

#pragma once
#include <stdbool.h>
#include <stdio.h>

void removeNewLineFromString(char* string);
bool removeDisallowedChars(char* string, char* disallowed);

int countOfCharInString(char* string, char c);

bool stringIsNumeric(char* string);

bool getStringInput(char* response, size_t max);
bool getIntegerInput(int* response);
bool getDoubleInput(double* response);
int getDoubleInputWithEscape(double* userInput, char finished, char cancel);
bool tokenizeToInteger(char* str, char* delim, int* integer);

char returnSingleChar(void);
bool yes(void);
