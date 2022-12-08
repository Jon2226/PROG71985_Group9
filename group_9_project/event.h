// PROG71985 - Fall 2022 - Group Project
// Group 9: Jonathan Ward, Drasti Patel, Komalpreet Kaur

// definition of event ADT and functions to handle it

#pragma once
#include "calendar.h"

#define MAX_DESC            51

typedef struct event
{
    bool allDay;
    EVENT_TYPE type;
    REPETITION repetition;
    TIME startTime;
    char description[MAX_DESC];
} EVENT;

EVENT createEvent(bool allDay, EVENT_TYPE type, REPETITION repetition,
    TIME startTime, char* description);
void destroyEvent(EVENT* e);
EVENT copyEvent(EVENT* e);
EVENT copyEventToNewTime(EVENT* e, TIME* t);

bool compareEvent(EVENT* lhs, EVENT* rhs);

void displayEvent(EVENT* e);
