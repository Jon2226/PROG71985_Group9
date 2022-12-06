// PROG71985 - Fall 2022
// Jonathan Ward - based on examples from Prof. Steve Hendrikse

// interface for common user input routines

#pragma once
#include <stdbool.h>
#include <stdio.h>

int countOfCharInString(char* string, char c);

void removeNewLineFromString(char* string);

bool removeDisallowedChars(char* string, char* disallowed);

bool stringIsNumeric(char* string);

bool promptAndGetDoubleInput(char* prompt, double* response);

int promptAndGetDoubleInputWithEscape(char* prompt, double* userInput,
    char finished, char cancel);

bool promptAndGetIntegerInput(char* prompt, int* response);

bool promptAndGetStringInput(char* prompt, char* response, size_t max);

char returnSingleChar(void);
