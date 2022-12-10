// PROG71985 - Fall 2022 - Group Project
// Group 9: Jonathan Ward, Drasti Patel, Komalpreet Kaur

#include "calendar.h"
#include "error.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

// implementation of functions for handling time/date information

TIME createTime(int sec, int min, int hour, int mday, int mon, int year, 
    int wday, int yday, int isdst)
{
    TIME t      = { 0 };
    t.tm_sec    = sec;
    t.tm_min    = min;
    t.tm_hour   = hour;
    t.tm_mday   = mday;
    t.tm_mon    = mon;
    t.tm_year   = year;
    t.tm_wday   = wday;
    t.tm_yday   = yday;
    t.tm_isdst  = isdst;

    if (!isValidTime(&t))
        printError("Possible error in assigned time data.");

    return t;
}

// preferable to avoid falling outside valid ranges - as opposed to = { 0 }
TIME createZeroedTime(void)
{
    int sec     = 0;
    int min     = 0;
    int hour    = 0;
    int mday    = 1;    // staying within valid range
    int mon     = JAN;
    int year    = 0;
    int wday    = SUN;
    int yday    = 0;
    int isdst   = -1;    // meaning information unavailable
    return createTime(sec, min, hour, mday, mon, year, wday, yday, isdst);
}

TIME copyTime(TIME t)
{
    return createTime(t.tm_sec, t.tm_min, t.tm_hour, t.tm_mday, t.tm_mon,
        t.tm_year, t.tm_wday, t.tm_yday, t.tm_isdst);
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

bool isValidDate(TIME* t)
{
    if ((t->tm_mday < 1   || t->tm_mday > daysPerMonth(t))
     || (t->tm_mon < 0    || t->tm_mon > MAX_MONTH)
     || (t->tm_wday < SUN || t->tm_wday > SAT)
     || (t->tm_yday < 0   || t->tm_yday > MAX_DAY))
        return false;

    return true;
}

bool isValidTime(TIME* t)
{
    if ((t->tm_sec < 0  || t->tm_sec > MAX_SEC)
     || (t->tm_min < 0  || t->tm_min > MAX_MIN)
     || (t->tm_hour < 0 || t->tm_hour > MAX_HOUR))
        return false;

    return true;
}

bool isValidDateAndTime(TIME* t)
{
    return isValidDate(t) && isValidTime(t);

    /* better to split these functions
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
     */
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

MONTH getMonthEnum(char* monthName)
{
    monthName[0] = tolower(monthName[0]);

    if (strncmp(monthName, "january", MAX_MONTH_NAME))
        return JAN;
    if (strncmp(monthName, "february", MAX_MONTH_NAME))
        return FEB;
    if (strncmp(monthName, "march", MAX_MONTH_NAME))
        return MAR;
    if (strncmp(monthName, "april", MAX_MONTH_NAME))
        return APR;
    if (strncmp(monthName, "may", MAX_MONTH_NAME))
        return MAY;
    if (strncmp(monthName, "june", MAX_MONTH_NAME))
        return JUN;
    if (strncmp(monthName, "july", MAX_MONTH_NAME))
        return JUL;
    if (strncmp(monthName, "august", MAX_MONTH_NAME))
        return AUG;
    if (strncmp(monthName, "september", MAX_MONTH_NAME))
        return SEP;
    if (strncmp(monthName, "october", MAX_MONTH_NAME))
        return OCT;
    if (strncmp(monthName, "november", MAX_MONTH_NAME))
        return NOV;
    if (strncmp(monthName, "december", MAX_MONTH_NAME))
        return DEC;

    return -1;
}

char* getMonthName(MONTH month)
{
    switch (month)
    {
    case JAN: 
        return "January";
    case FEB:
        return "February";
    case MAR:
        return "March";
    case APR:
        return "April";
    case MAY:
        return "May";
    case JUN:
        return "June";
    case JUL:
        return "July";
    case AUG:
        return "August";
    case SEP:
        return "September";
    case OCT:
        return "October";
    case NOV:
        return "November";
    case DEC:
        return "December";
    default: 
        return NULL;
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

char* getRecurrenceString(RECURRENCE recurrence)
{
    switch (recurrence)
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

void currentDate(TIME* t)
{
    time_t now = time(NULL);
    TIME* pTimeNow = localtime(&now);

    t->tm_year  = pTimeNow->tm_year;
    t->tm_mon   = pTimeNow->tm_mon;
    t->tm_mday  = pTimeNow->tm_mday;
}

void currentTime(TIME* t)
{
    time_t now = time(NULL);
    TIME* pTimeNow = localtime(&now);

    t->tm_hour  = pTimeNow->tm_hour;
    t->tm_min   = pTimeNow->tm_min;
    t->tm_sec   = pTimeNow->tm_sec;
}

void currentDateAndTime(TIME* t)
{
    time_t now = time(NULL);
    TIME* pTimeNow = localtime(&now);

    t->tm_year = pTimeNow->tm_year;
    t->tm_mon = pTimeNow->tm_mon;
    t->tm_mday = pTimeNow->tm_mday;
    t->tm_hour = pTimeNow->tm_hour;
    t->tm_min = pTimeNow->tm_min;
    t->tm_sec = pTimeNow->tm_sec;
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
    time_t now = time(NULL);
    TIME* pTimeNow = localtime(&now);

    displayLongDate(pTimeNow);
}
