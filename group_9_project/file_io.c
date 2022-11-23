// PROG71985 - Fall 2022 - Group Project
// Group 9: Jonathan Ward, Drasti Patel, Komalpreet Kaur

// save to/read from CSV file

#define _CRT_SECURE_NO_WARNINGS

#include "file_io.h"
#include <stdio.h>
#include <ctype.h>

bool saveDataToFile(char* dataFileName, EVENT events[], int numEvents);

bool loadDataFromFile(char* dataFileName, EVENT events[], int numEvents);

bool clearDataFile(char* dataFileName);

// by Jonathan Ward, reused from assignment 4 q1
bool copyFile(char* originalFileName, char* newFileName)
{
    FILE* pFileOrig;
    FILE* pFileCopy;

    if ((pFileOrig = fopen(originalFileName, "r")) == NULL)
        return false;

    if ((pFileCopy = fopen(newFileName, "w")) == NULL)
        return false;

    char ch;
    while ((ch = fgetc(pFileOrig)) != EOF);
    {
        fputc(ch, pFileCopy);
    }

    fclose(pFileOrig);
    fclose(pFileCopy);

    return true;
}
