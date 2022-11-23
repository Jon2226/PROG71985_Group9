// PROG71985 - Fall 2022 - Group Project
// Group 9: Jonathan Ward, Drasti Patel, Komalpreet Kaur

#pragma once
#include "calendar.h"

bool saveDataToFile(char* dataFileName, EVENT events[], int numEvents);

bool loadDataFromFile(char* dataFileName, EVENT events[], int numEvents);

bool clearDataFile(char* dataFileName);

bool copyFile(char* originalFileName, char* newFileName);
