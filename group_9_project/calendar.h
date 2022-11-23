// PROG71985 - Fall 2022 - Group Project
// Group 9: Jonathan Ward, Drasti Patel, Komalpreet Kaur

#pragma once
#include <stdbool.h>

#define SECONDS_PER_MINUTE  60
#define MINUTES_PER_HOUR    60
#define HOURS_PER_DAY       24
#define DAYS_PER_WEEK        7
#define MONTHS_PER_YEAR     12

#define TWENTY_EIGHT		28
#define TWENTY_NINE			29
#define THIRTY				30
#define THIRTY_ONE			31

typedef enum weekday {
    MON = 1,
    TUE = 2,
    WED = 3,
    THU = 4,
    FRI = 5,
    SAT = 6,
    SUN = 7
} WEEKDAY;

typedef enum eventType {
    APPOINTMENT = 1,
    BIRTHDAY = 2,
    DEADLINE = 3,
    TASK = 4,
    MEETING = 5,
    RECREATION = 6,
    CLASS = 7
} EVENT_TYPE;

typedef enum month {
    JAN = 1, 
    FEB = 2, 
    MAR = 3, 
    APR = 4, 
    MAY = 5, 
    JUN = 6, 
    JUL = 7,
    AUG = 8, 
    SEP = 9, 
    OCT = 10, 
    NOV = 11, 
    DEC = 12
} MONTH;

typedef struct event {
    bool allDay;
    int eventType;
    int duration;          // this and other time values in minutes
    int startTime;
    int endTime;
} EVENT;

bool isLeapYear(int year);

bool isValidDate(int date);

bool isValidTime(int time);

bool createEvent(EVENT* e); 

void destroyEvent(EVENT* e);

int getCurrentDay(EVENT* e);
