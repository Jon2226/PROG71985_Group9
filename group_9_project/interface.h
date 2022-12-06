// PROG71985 - Fall 2022 - Group Project
// Group 9: Jonathan Ward, Drasti Patel, Komalpreet Kaur

#pragma once
#include "calendar.h"

void printCurrentDate(void);
void displayMainMenu(void);
bool runMainMenu(EVENT* e, char* dataFileName);

void userAddEvent(EVENT* e);
void userDeleteEvent(EVENT* e);
void userModifyEvent(EVENT* e);

void loadFromGivenFile(EVENT* e);
void saveToGivenFile(EVENT* e);

bool runRangeMenu(EVENT* e);
void displayDay(EVENT* e);
void displayWeek(EVENT* e);
void displayMonth(EVENT* e);
void displayYear(EVENT* e);
void displayAllEvents(EVENT* e);

void inputDay(TIME* day);
void inputWeek(TIME* week);
void inputMonth(TIME* month);
void inputYear(TIME* year);

bool runSearchMenu(EVENT* e);
bool searchByType(EVENT* e);
bool searchByDescription(EVENT* e);

bool exitWithoutSave(void);
