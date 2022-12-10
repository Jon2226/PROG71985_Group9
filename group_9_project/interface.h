// PROG71985 - Fall 2022 - Group Project
// Group 9: Jonathan Ward, Drasti Patel, Komalpreet Kaur

// declarations of user interface functions for calendar application

#pragma once
#include "sl_list.h"

void displayMainMenu(void);
bool runMainMenu(LIST* eventList, char* dataFileName);

void userAddEvent(LIST* eventList);
void userDeleteEvent(LIST* eventList);
void userModifyEvent(LIST* eventList);

void loadFromGivenFile(LIST* eventList);
void saveToGivenFile(LIST* eventList);

bool runRangeMenu(LIST* eventList);
bool runSearchMenu(LIST* eventList);

void displayEventsForDate(LIST* eventList);
void displayEventsForWeek(LIST* eventList);
void displayEventsForMonth(LIST* eventList);
void displayEventsForYear(LIST* eventList);
void displayRange(LIST* eventList);

EVENT_TYPE inputAndReturnEventType(void);
RECURRENCE inputAndReturnRecurrence(void);

bool inputTime(TIME* eventTime);
bool inputDate(TIME* date);
bool inputWeek(TIME* week);
bool inputMonth(TIME* month);
bool inputYear(TIME* year);

void horizontalLine(void);
