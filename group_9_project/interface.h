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

void displayWeek(LIST* eventList);
void displayMonth(LIST* eventList);
void displayYear(LIST* eventList);
void displayAllEvents(LIST* eventList);

EVENT_TYPE inputAndReturnEventType(void);
RECURRENCE inputAndReturnRecurrence(void);

void inputDateAndTime(TIME* time);
void inputDate(TIME* date);
void inputWeek(TIME* week);
void inputMonth(TIME* month);
void inputYear(TIME* year);

bool exitWithoutSave(void);
void horizontalLine(void);
