// PROG71985 - Fall 2022 - Group Project
// Jonathan Ward - based on examples from Prof. Steve Hendrikse

// simple error handling and exit() wrappers

#pragma once

void printError(char* msg);

void exitWithError(char* msg);

// not an error, but there isn't an obvious place for this
void ExitSuccessfully(char* msg);
