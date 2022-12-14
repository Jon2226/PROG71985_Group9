// PROG71985 - Fall 2022 - Group Project
// Group 9: Jonathan Ward, Drasti Patel, Komalpreet Kaur
// Jonathan Ward

#define _CRT_SECURE_NO_WARNINGS

// approx. order of component inheritance (top down): 
// calendar -> event -> slnode -> sllist -> fileio / interface 
// -> main (and error/input wherever needed)

#include "file_io.h"
#include "interface.h"

#define DATA_FILE "event_data.txt"

int main(void)
{
    LIST eventList = createList();

    if (loadDataFromFile(&eventList, DATA_FILE))
        puts("Event data loaded from previous save file.");

    do
        displayMainMenu();
    while (runMainMenu(&eventList, DATA_FILE));

    return 0;
}
