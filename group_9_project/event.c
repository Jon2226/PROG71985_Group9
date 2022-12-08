// PROG71985 - Fall 2022 - Group Project
// Group 9: Jonathan Ward, Drasti Patel, Komalpreet Kaur

// implementation of functions to handle event ADT

#include "event.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>

EVENT createEvent(bool allDay, EVENT_TYPE type, REPETITION repetition,
    TIME startTime, char* description)
{
    EVENT e = { 0 };
    e.allDay = allDay;
    e.type = type;
    e.repetition = repetition;
    e.startTime = startTime;

    strncpy(e.description, description, MAX_DESC);
    e.description[MAX_DESC - 1] = '\0';

    return e;
}

void destroyEvent(EVENT* e)
{
    // nothing needed for now
}

EVENT copyEvent(EVENT* e)
{
    return createEvent(e->allDay, e->type, e->repetition, e->startTime,
        e->description);
}

EVENT copyEventToNewTime(EVENT* e, TIME* t)
{
    return createEvent(e->allDay, e->type, e->repetition, *t,
        e->description);
}

bool compareEvent(EVENT* left, EVENT* right)    // check if identical
{
    if (left->allDay == right->allDay
        && left->type == right->type
        && left->repetition == right->repetition
        && mktime(&left->startTime) == mktime(&right->startTime)
        && strcmp(left->description, right->description) == 0)
        return true;
    else
        return false;
}

void displayEvent(EVENT* e)
{
    // allday, type, repetition, (date) start time, description
    char* type = getEventTypeString(e->type);
    type[0] = toupper(type[0]);

    fputs(type, stdout);
    fputs(" on ", stdout);
    displayLongDate(&e->startTime);
    if (e->allDay)
    {
        puts(", lasting all day.");
    }
    else
    {
        fputs(", beginning at ", stdout);
        displayTime(&e->startTime);
    }
    fputs("\n", stdout);

    if (e->repetition != NONE)
    {
        fputs("This event repeats ", stdout);
        fputs(getRepetitionString(e->repetition), stdout);
        fputs(".", stdout);
    }
    fputs("\n", stdout);
}
