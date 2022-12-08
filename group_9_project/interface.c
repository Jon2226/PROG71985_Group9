// PROG71985 - Fall 2022 - Group Project
// Group 9: Jonathan Ward, Drasti Patel, Komalpreet Kaur

// implementation of user interface functions for calendar application

#include "interface.h"
#include "file_io.h"
#include "input.h"
#include "error.h"

void displayMainMenu(void)
{
    displayCurrentDate();
    puts("");   // newline
    // box-drawing chars might cause problems on non-unicode terminals :(
    // (apparently that can still be a problem in 2022)
    //puts("\n────────────────────────────────────────────────────────────────────────────────");
    puts("Please enter one of the following numbers corresponding to a command.");
    puts("\t1.  Add an event.");
    puts("\t2.  Delete an event.");
    puts("\t3.  Modify an event.");
    puts("\t4.  Display a given range of events.");
    puts("\t5.  Search for an event.");
    puts("\t6.  Load event data from a given file.");
    puts("\t0.  Save event data and exit the program.\n");
}

bool runMainMenu(LIST* eventList, char* dataFileName)
{
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

    case '0':
        backupDataFile(dataFileName);
        if (!saveDataToFile(eventList, dataFileName))
            if (!exitWithoutSave())
                return true;

        return false;
        break;          // defensive coding

    default:
        puts("Invalid menu entry.  Please try again.");
        break;
    }
    return true;    // re-run menu
}

void userAddEvent(LIST* eventList)
{
    // allday, type, repetition, (date) start time, description

    bool allDay = false;
    EVENT_TYPE type = -1;
    REPETITION repetition = 0;
    TIME startTime = { 0 };
    char description[MAX_DESC] = { 0 };

    // if all day, no startTime, just day
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

    if (!getStringInput(fileName, MAX_FILE_NAME))
        puts("Please try again.");

    if (!loadDataFromFile(eventList, fileName))
        printError("data file absent or unable to load");
}

void saveToGivenFile(LIST* eventList)
{
    char fileName[MAX_FILE_NAME];
    puts("Please enter a name for the save file.");

    if (!getStringInput(fileName, MAX_FILE_NAME))
        puts("Please try again.");

    if (!saveDataToFile(eventList, fileName))
        printError("unable to open data file for save.");
}

bool runRangeMenu(LIST* eventList)
{
    puts("\nPlease enter one of the following numbers.");
    puts("\t1.  Display all events.");
    puts("\t2.  Display events for a given day.");
    puts("\t3.  Display events for a given week.");
    puts("\t4.  Display events for a given month.");
    puts("\t5.  Display events for a given year.");
    //puts("6.\tDisplay events between two given days.");
    puts("\t0.  Return to main menu.\n");

    char ch = returnSingleChar();
    switch (ch)
    {
    case '1':
        displayDay(eventList);
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

void displayAllEvents(LIST* eventList)
{

}

void displayDay(LIST* eventList)
{
    char day[MAX_DATE_LEN] = { 0 };
    //TIME* d = { 0 };
    //inputDay(d);          // get day from user

    //if (strftime(day, sizeof(day), DATE_FORMAT, d) == 0)
    //    printError("error generating date");

    puts(day);

    // now search events for day and print
}

void displayWeek(LIST* eventList)
{
    // display 7 days vertically... or horizontally
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

void inputDay(TIME* day)
{

}

void inputWeek(TIME* week)
{

}

void inputMonth(TIME* month)
{

}

void inputYear(TIME* year)
{

}

bool runSearchMenu(LIST* eventList)
{
    puts("\nPlease enter a number corresponding to the search parameter you wish to use.");
    puts("\t1.  Event type.");
    puts("\t2.  Event repetition.");
    puts("\t3.  Event description.");
    puts("\t0.  Return to main menu.\n");

    char ch = returnSingleChar();
    switch (ch)
    {
    case '1':
        searchByType(eventList);
        break;

    case '2':
        searchByRepetition(eventList);
        break;

    case '3':
        searchByDescription(eventList);
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

void searchByType(LIST* eventList)
{
    puts("\nPlease enter the number of the event type you are searching for.");
    // lazy way to print a menu for event type enum
    for (int i = 1; i < OTHER; i++)
    {
        printf("\t%d.  %s\n", i, getEventTypeString(i));
    }
    puts("\t0.  Return to search menu.\n");

    int input = 0;
    if (!getIntegerInput(&input))
        puts("Please try again.");

}

void searchByRepetition(LIST* eventList)
{
    puts("\nPlease enter the number of the event type you are searching for.");
    for (int i = 0; i < YEARLY_BY_WEEKDAY; i++)
    {
        printf("\t%d.  %s\n", i, getRepetitionString(i));
    }
    puts("\t-1.  Return to search menu.\n");

    int input = 0;
    if (!getIntegerInput(&input))
        puts("Please try again.");

}

void searchByDescription(LIST* eventList)
{
    char description[MAX_DESC] = { 0 };
    puts("\nPlease enter a word from the description of the event you are searching for.");

    if (!getStringInput(description, MAX_DESC))
        puts("Please try again.");

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
