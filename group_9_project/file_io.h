// PROG71985 - Fall 2022
// Jonathan Ward

// interface to save/load data file

#pragma once
#include "sl_list.h"
#include <stdbool.h>
#include <stdio.h>

#define MAX_FILE_NAME    150
#define LONGEST_LINE     100

bool copyFile(char* originalFileName, char* newFileName);
bool backupDataFile(char* dataFileName);
void backupExistingData(LIST* list);
bool clearDataFile(char* dataFileName);

bool saveDataToFile(LIST* list, char* dataFileName);
bool loadDataFromFile(LIST* list, char* dataFileName);

void printListToStream(LIST* list, FILE* stream);
bool readListFromStream(LIST* list, FILE* stream);

void printEventToStream(EVENT* event, FILE* stream);
EVENT readEventFromStream(FILE* stream);

void printTimeToStream(TIME* t, FILE* stream);
TIME readTimeFromStream(FILE* stream);
