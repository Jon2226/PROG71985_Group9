// PROG71985 - Fall 2022 - Group Project
// Group 9: Jonathan Ward, Drasti Patel, Komalpreet Kaur

// implementation of user interface functions for calendar application

#include "interface.h"
#include "file_io.h"
#include "input.h"
#include "error.h"
#include <string.h>

void displayMainMenu(void)
{
    horizontalLine();
    displayCurrentDate();
    puts("");   // newline
    horizontalLine();
    puts("Please enter one of the following numbers corresponding to a command.");
    puts("\t1.  Add an event.");
    puts("\t2.  Delete an event.");
    puts("\t3.  Modify an event.");
    puts("\t4.  Display events for a given range of time.");
    puts("\t5.  Search for an event.");
    puts("\t6.  Load event data from a given file.");
    puts("\t7.  Save event data to a given file.");
    puts("\t8.  Remove auto-loaded event data to start fresh.");
    puts("\t0.  Save event data and exit the program.\n");
}

bool runMainMenu(LIST* eventList, char* dataFileName)
{
    static bool saved = true;
    char ch = returnSingleChar();
    switch (ch)
    {
    case '1':
        userAddEvent(eventList);
        break;

    case '2':
        userDeleteEvent(eventList);
        break;

    case '3':
        userModifyEvent(eventList);
        break;

    case '4':
        while (runRangeMenu(eventList))
            continue;
        break;

    case '5':
        while (runSearchMenu(eventList))
            continue;
        break;

    case '6':
        loadFromGivenFile(eventList);
        break;

    case '7':
        saveToGivenFile(eventList);
        break;

    case '8':
        *eventList = createList();
        break;

    case '0':
        if (!saveDataToFile(eventList, dataFileName))
            if (!exitWithoutSave())
                return true;

        return false;    // end the program
        break;           // defensive coding

    default:
        puts("Invalid menu entry.  Please try again.");
        break;
    }
    return true;    // re-run menu
}

void userAddEvent(LIST* eventList)
{
    bool allDay = false;
    char description[MAX_DESC] = { 0 };
    TIME startTime = { 0 };

    puts("Please enter a number for the type of event to be scheduled.");
    EVENT_TYPE type = inputAndReturnEventType();
    puts("Please enter the date of the event to be scheduled (YYYY/MM/DD)");
    
    // if all day, skip inputing time
    puts("Please enter a number for the recurrence of the event.");
    RECURRENCE recurrence = inputAndReturnRecurrence();
}

void userDeleteEvent(LIST* eventList)
{


}

void userModifyEvent(LIST* eventList)
{

}

void loadFromGivenFile(LIST* eventList)
{
    char fileName[MAX_FILE_NAME];
    puts("Please enter the name of the file you wish to load.");

    while (!getStringInput(fileName, MAX_FILE_NAME))
        puts("Please try again.");

    if (!loadDataFromFile(eventList, fileName))
        printError("data file absent or unable to load");
}

void saveToGivenFile(LIST* eventList)
{
    char fileName[MAX_FILE_NAME];
    puts("Please enter a name for the save file.");

    while (!getStringInput(fileName, MAX_FILE_NAME))
        puts("Please try again.");

    if (!saveDataToFile(eventList, fileName))
        printError("unable to open data file for save.");
    else
        puts("Event data saved.");
}

bool runRangeMenu(LIST* eventList)
{
    horizontalLine();
    puts("\nPlease enter one of the following numbers.");
    puts("\t1.  Display events for a given day.");
    puts("\t2.  Display events for a given week.");
    puts("\t3.  Display events for a given month.");
    puts("\t4.  Display events for a given year.");
    puts("\t5.  Display all events.");
    //puts("6.\tDisplay events between two given days.");
    puts("\t0.  Return to main menu.\n");

    char ch = returnSingleChar();
    switch (ch)
    {
    case '1':
        break;

    case '2':
        displayWeek(eventList);
        break;

    case '3':
        displayMonth(eventList);
        break;

    case '4':
        displayYear(eventList);
        break;

    case '5':
        displayAllEvents(eventList);
        break;

    //case '6':
    //    break;

    case '0':
        return false;
        break;

    default:
        puts("Invalid menu entry.  Please try again.");
        return true;
        break;
    }
    return true;    // re-run menu
}

void displayWeek(LIST* eventList)
{
    
}

void displayMonth(LIST* eventList)
{
    char month[MAX_DATE_LEN] = { 0 };
    int year = 0;
    puts("%s %d");
    puts("\tMon Tue Wed Thu Fri Sat Sun\t");
}

void displayYear(LIST* eventList)
{

}

void displayAllEvents(LIST* eventList)
{

}

bool runSearchMenu(LIST* eventList)
{
    horizontalLine();
    puts("\nPlease enter a number corresponding to the search parameter you wish to use.");
    puts("\t1.  Event description.");
    puts("\t2.  Event type.");
    puts("\t3.  Event recurrence.");
    puts("\t4.  Event date.");
    puts("\t5.  Event date and time.");
    //puts("\t6.  Find every all-day event.");    // probably not that useful
    puts("\t0.  Return to main menu.\n");

    EVENT* result = NULL;
    EVENT shellEvent = createZeroedEvent();
    char description[MAX_DESC] = { 0 };

    char ch = returnSingleChar();
    puts("");    // newline
    switch (ch)
    {
    case '1':
        puts("Please enter the description of the event you are searching for.");
        while (!getStringInput(description, MAX_DESC))
            puts("Please try again.");

        strncpy(shellEvent.description, description, MAX_DESC);
        shellEvent.description[MAX_DESC - 1] = '\0';

        // keep searching until the end of the list, and display each result
        while (result = searchListForEvent(eventList, &shellEvent,
            compareEventDescription) != NULL)
            displayEvent(result);
        break;

    case '2':
        puts("Please enter the number of the event type you are searching for.");
        EVENT_TYPE type = inputAndReturnEventType();
        shellEvent.type = type;

        while (result = searchListForEvent(eventList, &shellEvent,
            compareEventType) != NULL)
            displayEvent(result);
        break;

    case '3':
        puts("Please enter the number of the recurrence pattern you are searching for.");
        EVENT_TYPE recurrence = inputAndReturnRecurrence();
        shellEvent.recurrence = recurrence;

        while (result = searchListForEvent(eventList, &shellEvent, 
            compareEventRecurrence) != NULL)
            displayEvent(result);
        break;

    case '4':
        puts("Please enter the date you wish to display.");
        TIME eventDate = createZeroedTime();
        inputDate(&eventDate);
        shellEvent.startTime = copyTime(eventDate);
        
        while (result = searchListForEvent(eventList, &shellEvent, 
            compareEventDate) != NULL)
            displayEvent(result);
        break;

    case '5':
        puts("Please enter the date and time you wish to display.");
        TIME eventTime = createZeroedTime();
        inputDateAndTime(&eventTime);
        shellEvent.startTime = copyTime(eventTime);

        while (result = searchListForEvent(eventList, &shellEvent,
            compareEventDateAndTime) != NULL)
            displayEvent(result);
        break;

    case '0':
        return false;
        break;

    default:
        puts("Invalid menu entry.  Please try again.");
        return true;
        break;
    }
    return true;    // re-run menu
}

EVENT_TYPE inputAndReturnEventType(void)
{
    // lazy way to print a menu for event type enum
    for (int i = 1; i <= OTHER; i++)
        printf("\t%d.  %s\n", i, getEventTypeString(i));

    int input = 0;
    while (!getIntegerInput(&input) || input < 1 || input > OTHER)
        puts("Please try again.");

    return input;
}

RECURRENCE inputAndReturnRecurrence(void)
{
    // offset by 1 because recurrence enum starts at 0 and menu starts at 1
    for (int i = 0; i <= YEARLY_BY_WEEKDAY; i++)
        printf("\t%d.  %s\n", i + 1, getRecurrenceString(i));

    int input = 0;
    while (!getIntegerInput(&input) || input < 1 || input > YEARLY_BY_WEEKDAY)
        puts("Please try again.");
    
    return input - 1;
}

void inputDateAndTime(TIME* time)
{

}

void inputDate(TIME* date)
{
    // or input 0 for current date/time
    char day[MAX_DATE_LEN] = { 0 };

    puts("Please input a date (YYYY/MM/DD), or enter 0 for current date.");
}

void inputWeek(TIME* week)
{
    // hmmm
}

void inputMonth(TIME* month)
{

}

void inputYear(TIME* year)
{

}

bool exitWithoutSave(void)
{
    puts("\nWould you like to exit without saving?  (y/n)");
    char ch = returnSingleChar();
    if (ch == 'y' || ch == 'Y')
        return true;
    else
        return false;
}

void horizontalLine(void)
{
    puts("________________________________________________________________________________");
    // box-drawing chars don't look very good on non-unicode terminals :(
    //puts("\n────────────────────────────────────────────────────────────────────────────────");
}
