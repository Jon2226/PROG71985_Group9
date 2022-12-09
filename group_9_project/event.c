// PROG71985 - Fall 2022 - Group Project
// Group 9: Jonathan Ward, Drasti Patel, Komalpreet Kaur

// implementation of functions to handle event ADT

#include "event.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>

EVENT createEvent(bool allDay, EVENT_TYPE type, RECURRENCE recurrence,
    char* description, TIME startTime)
{
    EVENT e = { 0 };
    e.allDay = allDay;
    e.type = type;
    e.recurrence = recurrence;

    strncpy(e.description, description, MAX_DESC);
    e.description[MAX_DESC - 1] = '\0';

    e.startTime = copyTime(startTime);

    return e;
}

// preferable to avoid falling outside valid ranges - as opposed to = { 0 }
EVENT createZeroedEvent(void)
{
    bool allDay = false;
    EVENT_TYPE type = OTHER;
    RECURRENCE recurrence = NONE;
    char description[MAX_DESC] = { 0 };
    TIME startTime = createZeroedTime();
    return createEvent(allDay, type, recurrence, description, startTime);
}

void destroyEvent(EVENT* e)
{
    // nothing needed for now
}

EVENT copyEvent(EVENT e)
{
    return createEvent(e.allDay, e.type, e.recurrence, e.description, 
        e.startTime);
}

EVENT copyEventToNewTime(EVENT e, TIME t)
{
    return createEvent(e.allDay, e.type, e.recurrence, e.description,
        e.startTime);
}

void displayEvent(EVENT* e)
{
    // allday, type, recurrence, (date) start time, description
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

    if (e->recurrence != NONE)
    {
        fputs("This event repeats ", stdout);
        fputs(getRecurrenceString(e->recurrence), stdout);
        fputs(".", stdout);
    }
    fputs("\n\n", stdout);
}

bool compareFullEvent(EVENT* left, EVENT* right)    // check if identical
{
    if (left->allDay == right->allDay
        && left->type == right->type
        && left->recurrence == right->recurrence
        && strcmp(left->description, right->description) == 0
        && mktime(&left->startTime) == mktime(&right->startTime))
        return true;
    else
        return false;
}

bool compareEventAllDay(EVENT* left, EVENT* right)
{
    if (left->allDay == right->allDay)
        return true;
    else
        return false;
}

bool compareEventType(EVENT* left, EVENT* right)
{
    if (left->type == right->type)
        return true;
    else
        return false;
}

bool compareEventRecurrence(EVENT* left, EVENT* right)
{
    if (left->recurrence == right->recurrence)
        return true;
    else
        return false;
}

bool compareEventDescription(EVENT* left, EVENT* right)
{
    if (strcmp(left->description, right->description) == 0)
        return true;
    else
        return false;
}

bool compareEventDate(EVENT* left, EVENT* right)
{
    if (left->startTime.tm_year == right->startTime.tm_year
        && left->startTime.tm_mon == right->startTime.tm_mon
        && left->startTime.tm_mday == right->startTime.tm_mday)
        return true;
    else
        return false;
}

bool compareEventDateAndTime(EVENT* left, EVENT* right)
{
    if (mktime(&left->startTime) == mktime(&right->startTime))
        return true;
    else
        return false;
}

// two separate functions because it's possible the two events are simultaneous
bool isFirstEventAfterSecond(EVENT* first, EVENT* second)
{
    if (mktime(&first->startTime) > mktime(&second->startTime))
        return true;
    else
        return false;
}

bool isFirstEventBeforeSecond(EVENT* first, EVENT* second)
{
    if (mktime(&first->startTime) < mktime(&second->startTime))
        return true;
    else
        return false;
}
