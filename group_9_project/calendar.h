// PROG71985 - Fall 2022 - Group Project
// Group 9: Jonathan Ward, Drasti Patel, Komalpreet Kaur

// ADTs and functions for handling time/date information

#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdbool.h>
#include <time.h>

// string size limits
#define MAX_TIME_LEN        10
#define MAX_DATE_LEN        30
#define MAX_TYPE_LEN        20
#define MAX_REP_LEN         30

// for validating time values passed as 'struct tm'
#define MAX_SEC             61    // accounting for leap seconds
#define MAX_MIN             59
#define MAX_HOUR            23
#define MAX_MONTH           11
#define MAX_DAY            365    // for day of year

#define INIT_YEAR         1900    // "year 0" in 'struct tm' is 1900

typedef enum Month
{
    JAN = 0,    // because 'struct tm' starts months at 0
    FEB = 1,
    MAR = 2,
    APR = 3,
    MAY = 4,
    JUN = 5,
    JUL = 6,
    AUG = 7,
    SEP = 8,
    OCT = 9,
    NOV = 10,
    DEC = 11,
} MONTH;

// possibly unnecessary since mktime() sets weekday automatically
typedef enum Weekday
{
    SUN = 0,    // consistent with 'struct tm' in <time.h>
    MON = 1,
    TUE = 2,
    WED = 3,
    THU = 4,
    FRI = 5,
    SAT = 6,
} WEEKDAY;

typedef enum EventType
{
    APPOINTMENT     = 1,
    BIRTHDAY        = 2,
    DEADLINE        = 3,
    TASK            = 4,
    MEETING         = 5,
    RECREATION      = 6,
    CLASS           = 7,
    OTHER           = 8,
} EVENT_TYPE;

typedef enum Recurrence    // interval of event recurrence (or 0 for none)
{
    NONE                = 0,
    DAILY               = 1,
    WEEKLY              = 2,
    MONTHLY             = 3,
    YEARLY              = 4,    // by day of month (e.g. Feb 2nd every year)
    MONTHLY_BY_WEEKDAY  = 5,    // e.g. every third tuesday of all months
    YEARLY_BY_WEEKDAY   = 6,    // e.g. second monday of every october
} RECURRENCE;


typedef struct tm TIME;           // broken-down time format from <time.h>

TIME createTime(int sec, int min, int hour, int mday, int mon, int year,
    int wday, int yday, int isdst);
TIME createZeroedTime(void);
TIME copyTime(TIME t);
void disposeTime(TIME* t);

int compareTimes(TIME* lhs, TIME* rhs);
bool isLeapYear(TIME* t);
bool isValidDate(TIME* t);
bool isValidTime(TIME* t);
bool isValidDateAndTime(TIME* t);
int daysPerMonth(TIME* t);

char* getEventTypeString(EVENT_TYPE type);
char* getRecurrenceString(RECURRENCE recurrence);

void displayTime(TIME* t);
void displayDate(TIME* t);
void displayLongDate(TIME* t);
void displayCurrentDate(void);
