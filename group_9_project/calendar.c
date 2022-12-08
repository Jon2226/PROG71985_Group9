// PROG71985 - Fall 2022 - Group Project
// Group 9: Jonathan Ward, Drasti Patel, Komalpreet Kaur

#include "calendar.h"
#include "error.h"
#include <stdio.h>
#include <string.h>

// implementation of functions for handling time/date information

TIME createTime(void)   // probably won't need this for now
{
    TIME t = { 0 };
    return t;
}

void disposeTime(TIME* t)
{
    // nothing for now
}

int compareTimes(TIME* lhs, TIME* rhs)
{
    time_t left = mktime(lhs);
    time_t right = mktime(rhs);
    
    return (left > right) - (left < right);

    // equivalent to this: 
    //if (left < right)
    //    return -1;
    //else if (left == right)
    //    return 0;
    //else if (left > right)
    //    return 1;
}

bool isLeapYear(TIME* t)
{
    int year = t->tm_year + INIT_YEAR;
    // leap years normally occur every four years (but not on a new century,  
    // except every 4 centuries there is a leap year)
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
        return 31;          // 31 days for most months
        
    case APR: 
    case JUN: 
    case SEP: 
    case NOV: 
        return 30;

    case FEB: 
        if (isLeapYear(t))
            return 29;      // 29 days for February in a leap year
        else
            return 28;      // otherwise just 28

    default: 
        return 0;
    }
}

char* getEventTypeString(EVENT_TYPE type)
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

char* getRepetitionString(REPETITION repetition)
{
    switch (repetition)
    {
    case NONE: 
        return "none";
    case DAILY: 
        return "daily";
    case WEEKLY: 
        return "weekly";
    case MONTHLY: 
        return "monthly";
    case YEARLY: 
        return "yearly";
    case MONTHLY_BY_WEEKDAY: 
        return "monthly (by day of week)";
    case YEARLY_BY_WEEKDAY: 
        return "yearly (by day of week)";
    default:
        return NULL;
    }
}

void displayTime(TIME* t)
{
    char time[MAX_DATE_LEN] = { 0 };
    if (strftime(time, sizeof(time), "%H:%M", t) == 0)
        printError("error generating date");
    else
        fputs(time, stdout);
}

void displayDate(TIME* t)
{
    char date[MAX_DATE_LEN] = { 0 };
    if (strftime(date, sizeof(date), "%Y %b %d", t) == 0)
        printError("error generating date");
    else
        fputs(date, stdout);
}

void displayLongDate(TIME* t)
{
    char date[MAX_DATE_LEN] = { 0 };
    if (strftime(date, sizeof(date), "%Y %B %d (%A)", t) == 0)
        printError("error generating date");
    else 
        fputs(date, stdout);
}

void displayCurrentDate(void)
{
    char date[MAX_DATE_LEN] = { 0 };
    time_t now = time(NULL);
    TIME* pTimeNow = localtime(&now);

    displayLongDate(pTimeNow);
}
