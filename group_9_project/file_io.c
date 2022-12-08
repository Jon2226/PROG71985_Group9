// PROG71985 - Fall 2022
// Jonathan Ward

// implementation of functions to save/load data file

#define _CRT_SECURE_NO_WARNINGS

#include "file_io.h"
#include "input.h"
#include "error.h"

#include <time.h>
#include <stdio.h>
#include <ctype.h>

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

// preserve pre-existing data in event of a sudden crash, with a timestamped
// name for the backup file (also useful for archiving old data)
bool backupDataFile(char* dataFileName)
{
    char backupFileName[MAX_FILE_NAME];
    time_t now = time(NULL);
    const struct tm* pTimeNow = localtime(&now);

    if (strftime(backupFileName, sizeof(backupFileName), 
        "event_data_%F_T%H%M%S%z.txt", pTimeNow) == 0)
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

bool loadDataFromFile(LIST* list, char* dataFileName)
{
    FILE* pDataFile;
    if ((pDataFile = fopen(dataFileName, "r")) == NULL)
        return false;
    
    readListFromStream(list, pDataFile);
    fclose(pDataFile);
    return true;
}

bool saveDataToFile(LIST* list, char* dataFileName)
{
    FILE* pDataFile;
    if ((pDataFile = fopen(dataFileName, "w")) == NULL)
        return false;
    
    printListToStream(list, pDataFile);
    fclose(pDataFile);
    return true;
}

void printListToStream(LIST* list, FILE* stream)
{
    if (list->head != NULL)
    {
        NODE* current = list->head;
        do
        {
            printEventToStream(&current->data, stream);
            current = getNextNode(current);
        } while (current != NULL);
    }
}

void readListFromStream(LIST* list, FILE* stream)
{
    
}


void printEventToStream(EVENT* e, FILE* stream)
{

}

EVENT readEventFromStream(FILE* stream)
{
    EVENT e = { 0 };


    return e;
}
