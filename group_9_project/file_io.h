// PROG71985 - Fall 2022
// Jonathan Ward

// interface to save/load data file

#pragma once
#include "sl_list.h"
#include <stdbool.h>
#include <stdio.h>

#define MAX_FILE_NAME    150

bool copyFile(char* originalFileName, char* newFileName);
bool backupDataFile(char* dataFileName);
bool clearDataFile(char* dataFileName);

bool loadDataFromFile(LIST* list, char* dataFileName);
bool saveDataToFile(LIST* list, char* dataFileName);

void printListToStream(LIST* list, FILE* stream);
void readListFromStream(LIST* list, FILE* stream);
void printEventToStream(EVENT* event, FILE* stream);
EVENT readEventFromStream(FILE* stream);
