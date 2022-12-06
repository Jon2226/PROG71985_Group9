// PROG71985 - Fall 2022
// Jonathan Ward

// interface to save/load data file

#pragma once
#include "calendar.h"
#include <stdbool.h>

#define MAX_FILE_NAME    150

bool saveDataToFile(EVENT* e, char* dataFileName);

bool loadDataFromFile(EVENT* e, char* dataFileName);

bool backupDataFile(char* dataFileName);

bool clearDataFile(char* dataFileName);

bool copyFile(char* originalFileName, char* newFileName);
