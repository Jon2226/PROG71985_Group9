// PROG71985 - Fall 2022 - Group Project
// Group 9: Jonathan Ward, Drasti Patel, Komalpreet Kaur

#pragma once
#include "calendar.h"

bool addNewEvent(EVENT*);

bool deleteExistingEvent(EVENT*);

bool modifyEvent(EVENT*);

void displayMainMenu(void);

void displayEvent(EVENT*);

void searchByName(EVENT*);

void displayDay(EVENT*);

void displayWeek(EVENT*);

void displayMonth(EVENT*);

void displayYear(EVENT*);
