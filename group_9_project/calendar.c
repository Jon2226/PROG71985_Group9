// PROG71985 - Fall 2022 - Group Project
// Group 9: Jonathan Ward, Drasti Patel, Komalpreet Kaur

#include "calendar.h"
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

void destroyEvent(EVENT* e)
{

}

void printEventToStream(EVENT* e, FILE* stream)
{

}

void printAllEventsToStream(EVENT* e, FILE* stream)
{

}

EVENT readEventFromStream(FILE* stream)
{
    EVENT e = { 0 };


    return e;
}

void readAllEventsFromStream(EVENT* e, FILE* stream)
{

}

char* getTypeString(EVENT_TYPE type)
{
    switch (type)
    {
    case APPOINTMENT: 
        return "appointment";
    case BIRTHDAY: 
        return "birthday";
    case DEADLINE: 
        return "deadline";
    case TASK: 
        return "task";
    case MEETING: 
        return "meeting";
    case RECREATION: 
        return "recreation";
    case CLASS: 
        return "class";
    case OTHER: 
        return "other";
    default: 
        return NULL;
    }
}

bool isLeapYear(TIME* t)
{
    int year = t->tm_year + INIT_YEAR;
    // every four years (but not on a new century, except every 4 centuries)
    if (year % 4 == 0 && year % 100 != 0 || year % 400 == 0)
        return true;
    else
        return false;
}

bool isValidTime(TIME* t)
{
    if (t->tm_sec < 0 || t->tm_sec > MAX_SEC)
        return false;

    if (t->tm_min < 0 || t->tm_min > MAX_MIN)
        return false;

    if (t->tm_hour < 0 || t->tm_hour > MAX_HOUR)
        return false;

    if (t->tm_mday < 1 || t->tm_mday > daysPerMonth(t))
        return false;

    if (t->tm_mon < 0 || t->tm_mon > MAX_MONTH)
        return false;

    if (t->tm_year < 0)
        return false;

    if (t->tm_wday > SAT || t->tm_wday < SUN)
        return false;

    if (t->tm_yday < 0 || t->tm_yday > MAX_DAY)
        return false;

    return true;
}

int daysPerMonth(TIME* t)
{
    MONTH m = t->tm_mon;
    switch (m)
    {
    case JAN: 
    case MAR: 
    case MAY: 
    case JUL: 
    case AUG: 
    case OCT: 
    case DEC: 
        return THIRTY_ONE;

    case APR: 
    case JUN: 
    case SEP: 
    case NOV: 
        return THIRTY;

    case FEB: 
        if (isLeapYear(t))
            return TWENTY_NINE;
        else
            return TWENTY_EIGHT;

    default: 
        return 0;
    }
}

void displayDate(TIME* t)
{
    
}

void displayTime(TIME* t)
{

}
