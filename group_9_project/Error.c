// PROG71985 - Fall 2022 - Group Project
// Jonathan Ward - based on examples from Prof. Steve Hendrikse

// simple error handling and exit() wrappers

#include "Error.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// maybe a little paranoid not to just use fprintf
void printError(char* msg)
{
    fputs("Non-fatal error: ", stderr);
    fputs(msg, stderr);
    fputs(", continuing\n", stderr);
}

void exitWithError(char* msg)
{
    fputs("FATAL ERROR: ", stderr);
    fputs(msg, stderr);
    fputs("\n\n", stderr);
    exit(EXIT_FAILURE);
}

// not an error, but there isn't an obvious place for this
void exitSuccessfully(char* msg)
{
    puts(msg);
    puts("\n\n");
    exit(EXIT_SUCCESS);
}
