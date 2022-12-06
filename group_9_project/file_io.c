// PROG71985 - Fall 2022
// Jonathan Ward

// implementation of functions to save/load data file

#define _CRT_SECURE_NO_WARNINGS

#include "file_io.h"
#include "input.h"
#include "error.h"
#include <stdio.h>
#include <ctype.h>
#include <time.h>

bool saveDataToFile(EVENT* e, char* dataFileName)
{
    FILE* pDataFile;
    if ((pDataFile = fopen(dataFileName, "w")) == NULL)
    {
        printError("error accessing data file for save.");
        return false;
    }
    printAllEventsToStream(e, pDataFile);
    fclose(pDataFile);
    return true;
}

bool loadDataFromFile(EVENT* e, char* dataFileName)
{
    FILE* pDataFile;
    if ((pDataFile = fopen(dataFileName, "r")) == NULL)
    {
        printError("data file absent or unable to be loaded");
        return false;
    }
    readAllEventsFromStream(e, pDataFile);
    fclose(pDataFile);
    return true;
}

// preserve pre-existing data in event of a sudden crash, with a timestamped
// name for the backup file (also useful for archiving old data)
bool backupDataFile(char* dataFileName)
{
    char backupFileName[MAX_FILE_NAME];
    time_t currentTime = time(NULL);
    const struct tm* pCurrentTimeStruct = localtime(&currentTime);

    if (strftime(backupFileName, sizeof(backupFileName), "flight_data_%F_T%H%M%SUTC%z.txt",
        pCurrentTimeStruct) == 0)
    {
        printError("unable to name backup data file");
        return false;
    }
    else if (!copyFile(dataFileName, backupFileName))
    {
        printError("unable to create backup data file");
        return false;
    }
    return true;
}

bool clearDataFile(char* dataFileName)
{
    // not needed for now

    return true;
}

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
