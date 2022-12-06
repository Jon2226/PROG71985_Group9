// PROG71985 - Fall 2022 - Group Project
// Group 9: Jonathan Ward, Drasti Patel, Komalpreet Kaur

#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdbool.h>
#include <stdio.h>
#include <time.h>

// for validating times passed as struct tm
#define MAX_SEC             60    // accounting for leap seconds
#define MAX_MIN             59
#define MAX_HOUR            23

#define TWENTY_EIGHT		28
#define TWENTY_NINE			29
#define THIRTY				30
#define THIRTY_ONE			31

#define MAX_DAY            365
#define MAX_MONTH           11

#define INIT_YEAR         1900

#define MAX_DESC            51

typedef enum month
{
    JAN = 0,    // NB: struct tm in time.h starts months at 0
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

// probably unnecessary since mktime sets weekday automatically
typedef enum weekday
{
    SUN = 0,    // consistent with struct tm in time.h
    MON = 1,
    TUE = 2,
    WED = 3,
    THU = 4,
    FRI = 5,
    SAT = 6,
} WEEKDAY;

typedef enum eventType
{
    APPOINTMENT = 1,
    BIRTHDAY = 2,
    DEADLINE = 3,
    TASK = 4,
    MEETING = 5,
    RECREATION = 6,
    CLASS = 7,
    OTHER = 8,
} EVENT_TYPE;

typedef enum repetition
{
    NONE = 0,
    DAILY = 1,
    WEEKLY = 2,
    MONTHLY = 3,
    MONTHLY_WEEKDAY = 4,    // e.g. every second tuesday of any month
    YEARLY_MONTHDAY = 5,    // by day of the month, not day of the year
    YEARLY_WEEKDAY = 6,     // e.g. second monday of every october
} REPETITION;

typedef struct tm TIME;

typedef struct event
{
    bool allDay;
    EVENT_TYPE type;
    REPETITION repetition;    // need I repeat myself?
    TIME startTime;
    char description[MAX_DESC];
} EVENT;

EVENT createEvent(bool allDay, EVENT_TYPE type, REPETITION repetition, 
    TIME startTime, char* description);

EVENT copyEvent(EVENT* e);
EVENT copyEventToNewTime(EVENT* e, TIME* t);
void destroyEvent(EVENT* e);

void printEventToStream(EVENT* e, FILE* stream);
void printAllEventsToStream(EVENT* e, FILE* stream);
EVENT readEventFromStream(FILE* stream);
void readAllEventsFromStream(EVENT* e, FILE* stream);

char* getTypeString(EVENT_TYPE type);

bool isLeapYear(TIME* t);
bool isValidDate(TIME* t);
bool isValidTime(TIME* t);
int daysPerMonth(TIME* t);

void displayDate(TIME* t);
void displayTime(TIME* t);
