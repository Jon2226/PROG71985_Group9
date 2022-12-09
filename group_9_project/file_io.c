// PROG71985 - Fall 2022
// Jonathan Ward

// implementation of functions to save/load data file

#define _CRT_SECURE_NO_WARNINGS

#include "file_io.h"
#include "input.h"
#include "error.h"

#include <time.h>
#include <string.h>
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

// backup pre-existing data in event of a sudden crash, or for archiving
bool backupDataFile(char* dataFileName)
{
    // timestamp file name
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
        // usually this just means there's no previously existing data file
        // so we'll leave out the error message for now
        // printError("unable to create backup data file");
        return false;
    }
    return true;
}

void backupExistingData(LIST* list)
{
    if (getCurrentCount(list) > 0)
    {
        // timestamp file name
        char backupFileName[MAX_FILE_NAME];
        time_t now = time(NULL);
        const struct tm* pTimeNow = localtime(&now);
        if (saveDataToFile(list, backupFileName))
            puts("Previous data saved.");
        else
            // should change this to return false and confirm with user
            puts("Previous data not saved.");
    }
}

bool clearDataFile(char* dataFileName)
{
    // not needed for now

    return true;
}

bool saveDataToFile(LIST* list, char* dataFileName)
{
    backupDataFile(dataFileName);   // so previous data isn't overwritten
    
    FILE* pDataFile;
    if ((pDataFile = fopen(dataFileName, "w")) == NULL)
        return false;
    
    printListToStream(list, pDataFile);
    fclose(pDataFile);
    return true;
}

bool loadDataFromFile(LIST* list, char* dataFileName)
{
    backupExistingData(list);    // in case user neglected to save it

    FILE* pDataFile;
    if ((pDataFile = fopen(dataFileName, "r")) == NULL)
        return false;

    if (!readListFromStream(list, pDataFile));
    {
        fclose(pDataFile);
        return false;
    }
    fclose(pDataFile);
    return true;
}

void printListToStream(LIST* list, FILE* stream)
{
    fprintf(stream, "Total:\n%d\n", getCurrentCount(list));

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

bool readListFromStream(LIST* list, FILE* stream)
{
    char buffer[LONGEST_LINE];
    fgets(buffer, LONGEST_LINE, stream);
    removeNewLineFromString(buffer);
    if (strncmp(buffer, "Total:", 6) != 0)
        printError("possible error in data file");

    *list = createList();    // re-initialize in case data was added

    int numEvents = 0;
    if (fscanf(stream, "%d", &numEvents) != 1)
    {
        printError("unable to get number of events from data file");
        return false;
    }

    for (int i = 0; i < numEvents; i++)
    {
        EVENT e = { 0 };
        e = readEventFromStream(stream);
        if (!addEventToList(list, e))
            printError("unable to add event from file to list");
    }
    return true;
}

void printEventToStream(EVENT* e, FILE* stream)
{
    fprintf(stream, "%d,%d,%d\n", (int)e->allDay, e->type, e->recurrence);
    fprintf(stream, "%s\n", e->description);
    printTimeToStream(&e->startTime, stream);
}

EVENT readEventFromStream(FILE* stream)
{
    int allDay = false;
    EVENT_TYPE type = OTHER;
    RECURRENCE recurrence = NONE;

    char description[LONGEST_LINE] = { 0 };
    fgets(description, LONGEST_LINE, stream);
    removeNewLineFromString(description);

    if ((fscanf(stream, "%d,%d,%d\n", &allDay, &type, &recurrence)) != 3)
    {
        printError("problem reading event data from file.\n");
        allDay = false;
        type = OTHER;
        recurrence = NONE;
    }
    TIME startTime = readTimeFromStream(stream);

    return createEvent((bool)allDay, type, recurrence, description, startTime);
}

void printTimeToStream(TIME* t, FILE* stream)
{
    fprintf(stream,"%d,%d,%d,%d,%d,%d,%d,%d,%d\n", t->tm_sec, t->tm_min, 
        t->tm_hour, t->tm_mday, t->tm_mon, t->tm_year, t->tm_wday, t->tm_yday,
        t->tm_isdst);
} 

TIME readTimeFromStream(FILE* stream)
{
    int sec = 0;
    int min = 0;
    int hour = 0;
    int mday = 1;    // staying within valid range
    int mon = JAN;
    int year = 0;
    int wday = SUN;
    int yday = 0;
    int isdst = -1;    // meaning information unavailable

    if (fscanf(stream, "%d,%d,%d,%d,%d,%d,%d,%d,%d\n", &sec, &min, &hour, 
        &mday, &mon, &year, &wday, &yday, &isdst) != 9)
        printError("problem reading time data from file.");

    return createTime(sec, min, hour, mday, mon, year, wday, yday, isdst);
}
