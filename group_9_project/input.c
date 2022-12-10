// PROG71985 - Fall 2022
// Jonathan Ward - based on examples from Prof. Steve Hendrikse

// implementation of common user input routines

#define _CRT_SECURE_NO_WARNINGS
#include "input.h"
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_STRING_TO_DOUBLE		20
#define MAX_STRING_TO_INT		    12      // more than enough for unsigned long

void removeNewLineFromString(char* string)
{
    for (int i = 0; i < strlen(string); i++)
    {
        if (string[i] == '\n')
            string[i] = '\0';
    }
}

// useful for sanitizing CSV inputs
bool removeDisallowedChars(char* string, char* disallowed)
{
    bool badInput = false;
    for (int i = 0; i < strlen(string); i++)
    {
        for (int j = 0; j < strlen(disallowed); j++)
        {
            if (string[i] == disallowed[j])
            {
                string[i] = '_';
                badInput = true;
            }
        }
    }
    return badInput;    // might be useful to print error if true
}

int countOfCharInString(char* string, char c)
{
    int count = 0;
    for (int i = 0; i < strlen(string); i++)
    {
        if (string[i] == c)
            count++;
    }
    return count;
}

bool stringIsNumeric(char* string)
{
    for (int i = 0; i < strlen(string); i++)
    {
        if (!(isdigit(string[i]) || string[i] == '.' 
            || string[i] == '-' || string[i] == '+'))
            return false;
    }

    // should be at most 1 period, and 1 plus or minus sign at the beginning
    int countOfPlus = countOfCharInString(string, '+');
    int countOfMinus = countOfCharInString(string, '-');
    if (countOfCharInString(string, '.') <= 1 
        && countOfPlus <= 1 && countOfMinus <= 1)
    {
        if (countOfPlus == 1 && countOfMinus == 0 && string[0] == '+')
            return true;
        else if (countOfMinus == 1 && countOfPlus == 0 && string[0] == '-')
            return true;
        else if (countOfMinus == 0 && countOfPlus == 0)
            return true;
        else
            return false;
    }
    else
        return false;
}

bool getStringInput(char* userInput, size_t maxLength)
{
    if (fgets(userInput, (int)maxLength, stdin) == NULL)
        return false;
    removeNewLineFromString(userInput);         // optional

    if (strlen(userInput) > 0)
        return true;
    else
        return false;
}

bool getIntegerInput(int* userInput)
{
    char input[MAX_STRING_TO_INT] = { 0 };
    if (fgets(input, (int)MAX_STRING_TO_INT, stdin) == NULL)
        return false;
    removeNewLineFromString(input);

    if (!stringIsNumeric(input))
        return false;
    else
    {
        *userInput = atoi(input);
        return true;
    }
}

bool getDoubleInput(double* userInput)
{
    char input[MAX_STRING_TO_DOUBLE] = { 0 };
    if (fgets(input, (int)MAX_STRING_TO_DOUBLE, stdin) == NULL)
        return false;
    removeNewLineFromString(input);

    if (!stringIsNumeric(input))
        return false;
    else
    {
        *userInput = atof(input);
        return true;
    }
}

// Special input function to check for non-numeric menu escape codes.
// Returns 0 for success, -1, for failure, 1 for finished, 2 for cancel.  
int getDoubleInputWithEscape(double* userInput,
    char finished, char cancel)
{
    char input[MAX_STRING_TO_DOUBLE] = { 0 };
    fgets(input, (int)MAX_STRING_TO_DOUBLE, stdin);
    removeNewLineFromString(input);

    if (input[0] == finished || tolower(input[0]) == finished)
        return 1;
    if (input[0] == cancel || tolower(input[0]) == cancel)
        return 2;

    if (!stringIsNumeric(input))
        return -1;
    else
    {
        *userInput = (double)atof(input);
        return 0;
    }
}

bool tokenizeToInteger(char* str, char* delim, int* integer)
{
    char* token;
    if ((token = strtok(str, delim)) != NULL && stringIsNumeric(token))
    {
        *integer = atoi(token);
        return true;
    }
    return false;
}

// for collecting single char e.g. for menu inputs, and ignoring everything 
// that comes afterward (e.g. the dangling newline)
char returnSingleChar(void)
{
    char firstChar = getc(stdin);

    char garbage = ' ';
    while (garbage != '\n' && garbage != EOF)
        garbage = getc(stdin);

    return firstChar;
}

bool yes(void)
{
    char ch = returnSingleChar();
    if (ch == 'y' || ch == 'Y')
        return true;
    else
        return false;
}
