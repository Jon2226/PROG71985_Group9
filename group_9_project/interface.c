// PROG71985 - Fall 2022 - Group Project
// Group 9: Jonathan Ward, Drasti Patel, Komalpreet Kaur

// implementation of user interface functions for calendar application

#include "interface.h"
#include "file_io.h"
#include "input.h"
#include "error.h"
#include <stdlib.h>
#include <string.h>

void displayMainMenu(void)
{
    horizontalLine();
    fputs("\t\t\t", stdout);
    displayCurrentDate();
    puts("");    // newline
    horizontalLine();
    puts("Please enter one of the following numbers corresponding to a command.");
    puts("\t1.  Add an event.");
    puts("\t2.  Delete an event.");
    puts("\t3.  Modify an event.");
    puts("\t4.  Display events for a given time period.");
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
        {
            puts("\nError saving data to file.");
            puts("Would you like to exit without saving?  (y/n)");
            if (!yes())
                return true;    // back to menu
        }
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
    EVENT newEvent = createZeroedEvent();
    TIME dateAndTime = createZeroedTime();
    puts("Please enter a number for the type of event to be scheduled.");
    newEvent.type = inputAndReturnEventType();

    while (!inputDate(&dateAndTime))
        puts("Invalid date.  Please try again.");

    puts("Will the event last all day?");
    if (yes())
    {
        newEvent.allDay = true;
    }
    else
    {
        while (!inputTime(&dateAndTime))
            puts("Invalid time.  Please try again.");
        addTimeToEventDate(&newEvent, &dateAndTime);
    }
    puts("Please enter a number for the recurrence of the event.");
    newEvent.recurrence = inputAndReturnRecurrence();

    puts("Please enter a description for this event.");
    while (!getStringInput(newEvent.description, MAX_DESC))
        puts("Invalid input.  Please try again.");

    addEventToList(eventList, newEvent);
    puts("Your event has been added.\n");
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
        puts("Invalid input.  Please try again.");

    if (!loadDataFromFile(eventList, fileName))
        printError("data file absent or unable to load");
}

void saveToGivenFile(LIST* eventList)
{
    char fileName[MAX_FILE_NAME];
    puts("Please enter a name for the save file.");

    while (!getStringInput(fileName, MAX_FILE_NAME))
        puts("Invalid input.  Please try again.");

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
    //puts("\t2.  Display events for a given week.");    // not implemented yet
    puts("\t2.  Display events for a given month.");
    puts("\t3.  Display events for a given year.");
    puts("\t4.  Display all events.");
    puts("\t5.  Display events between two given days.");
    puts("\t0.  Return to main menu.\n");

    char ch = returnSingleChar();
    puts("");    // newline
    switch (ch)
    {
    case '1':    // search by date
        displayEventsForDate(eventList);
        break;

    //case '2':
    //    displayEventsForWeek(eventList);
    //    break;

    case '2':
        displayEventsForMonth(eventList);
        break;

    case '3':
        displayEventsForYear(eventList);
        break;

    case '4':    // all events
        displayList(eventList);
        break;

    case '5':    // range of events based on two given dates
        displayRange(eventList);
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

bool runSearchMenu(LIST* eventList)
{
    horizontalLine();
    puts("\nPlease enter a number corresponding to the search parameter you wish to use.");
    puts("\t1.  Event description.");
    puts("\t2.  Event type.");
    puts("\t3.  Event recurrence.");
    puts("\t4.  Time of day.");
    puts("\t0.  Return to main menu.\n");

    EVENT* result = NULL;
    EVENT shellEvent = createZeroedEvent();
    TIME eventTime = createZeroedTime();
    EVENT_TYPE type = OTHER;
    RECURRENCE recurrence = NONE;
    char description[MAX_DESC] = { 0 };

    char ch = returnSingleChar();
    puts("");    // newline
    switch (ch)
    {
    case '1':    // search by event description
        puts("Please enter the description of the event you are searching for.");
        while (!getStringInput(description, MAX_DESC))
            puts("Invalid input.  Please try again.");

        strncpy(shellEvent.description, description, MAX_DESC);
        shellEvent.description[MAX_DESC - 1] = '\0';
        do
        {
            result = searchListForEvent(eventList, &shellEvent, compareEventDescription);
            if (result != NULL)
                displayEvent(result);
        } while (result != NULL);
        break;

    case '2':    // search by event type
        puts("Please enter the number of the event type you are searching for.");
        type = inputAndReturnEventType();
        shellEvent.type = type;
        do
        {
            result = searchListForEvent(eventList, &shellEvent, compareEventType);
            if (result != NULL)
                displayEvent(result);
        } while (result != NULL);
        break;

    case '3':    // search by recurrence
        puts("Please enter the number of the recurrence pattern you are searching for.");
        recurrence = inputAndReturnRecurrence();
        shellEvent.recurrence = recurrence;
        do
        {
            result = searchListForEvent(eventList, &shellEvent, compareEventRecurrence);
            if (result != NULL)
                displayEvent(result);
        } while (result != NULL);
        break;

    case '4':    // search by time of day
        inputTime(&eventTime);
        shellEvent.startTime = copyTime(eventTime);
        do
        {
            result = searchListForEvent(eventList, &shellEvent, compareEventTime);
            if (result != NULL)
                displayEvent(result);
        } while (result != NULL);
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

void displayEventsForDate(LIST* eventList)
{
    puts("Please enter the date you wish to display.");
    TIME date = createZeroedTime();
    while (!inputDate(&date))
        puts("Invalid date.  Please try again.");

    EVENT shellEvent = createZeroedEvent();
    shellEvent.startTime = copyTime(date);
    EVENT* result = NULL;
    do
    {
        result = searchListForEvent(eventList, &shellEvent, compareEventDate);
        if (result != NULL)
            displayEvent(result);
    } while (result != NULL);
}

void displayEventsForWeek(LIST* eventList)
{

}

void displayEventsForMonth(LIST* eventList)
{
    EVENT shellEvent = createZeroedEvent();
    while (!inputMonth(&shellEvent.startTime))
        puts("Invalid month.  Please try again.");

    EVENT* result = NULL;
    do
    {
        result = searchListForEvent(eventList, &shellEvent, compareEventYearAndMonth);
        if (result != NULL)
            displayEvent(result);
    } while (result != NULL);
    
}

void displayEventsForYear(LIST* eventList)
{
    EVENT shellEvent = createZeroedEvent();
    while (!inputYear(&shellEvent.startTime))
        puts("Invalid year.  Please try again.");

    EVENT* result = NULL;
    do
    {
        result = searchListForEvent(eventList, &shellEvent, compareEventYear);
        if (result != NULL)
            displayEvent(result);
    } while (result != NULL);
}

void displayRange(LIST* eventList)
{
    EVENT* result = NULL;
    TIME firstDay = createZeroedTime();
    TIME lastDay = createZeroedTime();

    puts("Beginning of time period to display: ");
    inputTime(&firstDay);
    puts("End of time period to display: ");
    inputTime(&lastDay);

    do
    {
        result = searchListForEventByTimeRange(eventList, &firstDay, &lastDay);
        if (result != NULL)
            displayEvent(result);
    } while (result != NULL);
}

EVENT_TYPE inputAndReturnEventType(void)
{
    // lazy way to print a menu for event type enum
    for (int i = 1; i <= OTHER; i++)
        printf("\t%d.  %s\n", i, getEventTypeString(i));

    int input = 0;
    while (!getIntegerInput(&input) || input < APPOINTMENT || input > OTHER)
        puts("Invalid input.  Please try again.");

    return input;
}

RECURRENCE inputAndReturnRecurrence(void)
{
    // offset by 1 because recurrence enum starts at 0 and menu starts at 1
    for (int i = 0; i <= YEARLY_BY_WEEKDAY; i++)
        printf("\t%d.  %s\n", i + 1, getRecurrenceString(i));

    int input = 0;
    while (!getIntegerInput(&input) || input < (NONE + 1) || input > YEARLY_BY_WEEKDAY)
        puts("Invalid input.  Please try again.");
    
    return input - 1;
}

bool inputTime(TIME* eventTime)
{
    puts("Please input the time (in 24-hour time, with the format HH:MM) of the event.");
    char timeString[SHORT_TIME_LEN] = { 0 };
    while (!getStringInput(timeString, SHORT_TIME_LEN))
        puts("Invalid input.  Please try again.");

    if (!tokenizeToInteger(timeString, "/", &eventTime->tm_hour))
        return false;
    if (!tokenizeToInteger(timeString, "\0", &eventTime->tm_min))
        return false;

    if (!isValidTime(eventTime))
    {
        eventTime->tm_hour = 0;
        eventTime->tm_min = 0;
        return false;
    }
    return true;
}

bool inputDate(TIME* date)
{
    puts("Please input a date (in the format YYYY/MM/DD), or enter 'C' for current date.");
    char dateString[SHORT_DATE_LEN] = { 0 };
    while (!getStringInput(dateString, SHORT_DATE_LEN))
        puts("Invalid input.  Please try again.");

    if (dateString[0] == 'c' || dateString[0] == 'C')
    {
        currentDate(date);
        return true;
    }

    if (!tokenizeToInteger(dateString, "/", &date->tm_year))
        return false;
    if (!tokenizeToInteger(dateString, "/", &date->tm_mon))
        return false;
    if (!tokenizeToInteger(dateString, "\0", &date->tm_mday))
        return false;

    if (!isValidDate(date))
    {
        date->tm_year = 0;
        date->tm_mon = 0;
        date->tm_mday = 0;
        return false;
    }
    return true;
}

bool inputWeek(TIME* week)
{


    if (isValidDate(week))
        return true;
    else
        return false;
}

bool inputMonth(TIME* month)
{
    puts("First, choose the year you want to view events for.");
    while (!inputYear(month))
        puts("Invalid year.  Please try again.");

    char monthName[MAX_MONTH_NAME] = { 0 };
    puts("Now enter the month name.");
    while (!getStringInput(monthName, MAX_MONTH_NAME))
        puts("Invalid input.  Please try again.");

    for (int i = JAN; i <= DEC; i++)
    {
        if (strncmp(monthName, getMonthName(i), MAX_MONTH_NAME) == 0)
        {
            month->tm_mon = i;
            break;
        }
    }

    if (!isValidDate(month))
    {
        month->tm_mon = 0;
        return false;
    }
    return true;
}

bool inputYear(TIME* year)
{
    puts("Please input a year.");
    while (!getIntegerInput(&year->tm_year))
        puts("Invalid input.  Please try again.");

    if (!isValidDate(year))
    {
        year->tm_year = 0;
        return false;
    }
    return true;
}

void horizontalLine(void)
{
    puts("________________________________________________________________________________");
    
    // box-drawing chars don't look very good on non-unicode terminals :(
    //puts("\n────────────────────────────────────────────────────────────────────────────────");
}
