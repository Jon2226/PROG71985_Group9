// PROG71985 - Fall 2022 - Group Project
// Group 9: Jonathan Ward, Drasti Patel, Komalpreet Kaur

#include "interface.h"
#include "file_io.h"
#include "input.h"
#include "error.h"

#define DATE_FORMAT "%Y %B %d (%A)"
#define MAX_DATE_LEN    61

void printCurrentDate(void)
{
    char date[MAX_DATE_LEN] = { 0 };
    time_t now = time(NULL);
    const struct tm* pTimeNow = localtime(&now);

    if (strftime(date, sizeof(date), DATE_FORMAT, pTimeNow) == 0)
        printError("error generating date");

    puts(date);
}

void displayMainMenu(void)
{
    printCurrentDate();
    // box-drawing chars might cause problems on non-unicode terminals
    // ...and apparently that could still be a problem in 2022...  :(
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

bool runMainMenu(EVENT* e, char* dataFileName)
{
    char ch = returnSingleChar();
    switch (ch)
    {
    case '1':
        userAddEvent(e);
        break;

    case '2':
        userDeleteEvent(e);
        break;

    case '3':
        userModifyEvent(e);
        break;

    case '4':
        while (runRangeMenu(e))
            continue;
        break;

    case '5':
        while (runSearchMenu(e))
            continue;
        break;

    case '6':
        loadFromGivenFile(e);
        break;

    case '0':
        backupDataFile(dataFileName);
        if (!saveDataToFile(e, dataFileName))
            if (!exitWithoutSave())
                return true;

        return false;
        break;          // defensive coding

    default:
        puts("Invalid menu entry.  Please try again.");
        break;
    }
    return true;
}

void userAddEvent(EVENT* e)
{
    // type menu, repetition menu, allday, start time/date, description


}

void userDeleteEvent(EVENT* e)
{


}

void userModifyEvent(EVENT* e)
{

}

void loadFromGivenFile(EVENT* e)
{
    char fileName[MAX_FILE_NAME];
    char* prompt = "Please enter the name of the file you wish to load.";

    if (!promptAndGetStringInput(prompt, fileName, MAX_FILE_NAME))
        puts("Please try again.");

    if (!loadDataFromFile(e, fileName))
        puts("File not found.");
}

void saveToGivenFile(EVENT* e)
{
    char fileName[MAX_FILE_NAME];
    char* prompt = "Please enter a name for the save file.";

    if (!promptAndGetStringInput(prompt, fileName, MAX_FILE_NAME))
        puts("Please try again.");

    if (!saveDataToFile(e, fileName))
        puts("Unable to save data.");
}

bool runRangeMenu(EVENT* e)
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
        displayDay(e);
        break;

    case '2':
        displayWeek(e);
        break;

    case '3':
        displayMonth(e);
        break;

    case '4':
        displayYear(e);
        break;

    case '5':
        displayAllEvents(e);
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
    return false;
}

void displayEvent(EVENT* e)
{

    printf("");
        
    if (e->allDay)
        puts("All day.");

    // allday, type, repetition, (date) start time, description
}

void displayAllEvents(EVENT* e)
{

}

void displayDay(EVENT* e)
{
    char day[MAX_DATE_LEN] = { 0 };
    //TIME* d = { 0 };
    //inputDay(d);          // get day from user

    //if (strftime(day, sizeof(day), DATE_FORMAT, d) == 0)
    //    printError("error generating date");

    puts(day);

    // now search events for day and print
}

void displayWeek(EVENT* e)
{
    // display 7 days vertically... or horizontally
}

void displayMonth(EVENT* e)
{
    char month[MAX_DATE_LEN] = { 0 };
    int year = 0;
    puts("%s %d");
    puts("\tMon Tue Wed Thu Fri Sat Sun\t");
}

void displayYear(EVENT* e)
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

bool runSearchMenu(EVENT* e)
{
    puts("\nPlease enter a number corresponding to the search parameter you wish to use.");
    puts("\t1.  Event type.");
    puts("\t2.  Event description.");
    puts("\t0.  Return to main menu.\n");

    char ch = returnSingleChar();
    switch (ch)
    {
    case '1':
        while (searchByType(e))
            continue;
        break;

    case '2':
        while (searchByDescription(e))
            continue;
        break;

    case '0':
        return false;
        break;

    default:
        puts("Invalid menu entry.  Please try again.");
        return true;
        break;
    }
    return false;
}

bool searchByType(EVENT* e)
{
    puts("\nPlease enter the number of the event type you are searching for.");
    // lazy way to print a menu for event type enum
    for (int i = 0; i < OTHER; i++)
    {
        printf("\t%d.  %s\n", i, getTypeString(i));
    }
    puts("\t0.  Return to search menu.\n");

    // search events by type

}

bool searchByDescription(EVENT* e)
{
    char description[MAX_DESC] = { 0 };
    char* prompt = "\nPlease enter a word from the description of the event you are searching for.";
    promptAndGetStringInput(prompt, description, MAX_DESC);

    // search events by description

}

bool exitWithoutSave(void)
{
    puts("Would you like to exit without saving?  (y/n)");
    char ch = returnSingleChar();

    if (ch == 'y' || ch == 'Y')
        return true;
    else
        return false;
}
