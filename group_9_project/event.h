// PROG71985 - Fall 2022 - Group Project
// Group 9: Jonathan Ward, Drasti Patel, Komalpreet Kaur
// Jonathan Ward

// definition of event ADT and functions to handle it

#pragma once
#include "calendar.h"

#define MAX_DESC                51

//// unique identifier for events (should be replaced with non-global)
//int eventIndex = 0;

typedef struct Event
{
    int index;    // unique identifier
    bool allDay;
    EVENT_TYPE type;
    RECURRENCE recurrence;
    char description[MAX_DESC];
    TIME startTime;
} EVENT;

EVENT createEvent(bool allDay, EVENT_TYPE type, RECURRENCE recurrence,
    char* description, TIME startTime);
EVENT createZeroedEvent(void);
void destroyEvent(EVENT* e);
EVENT copyEvent(EVENT e);
EVENT copyEventToDifferentTime(EVENT e, TIME t);
void setEventDescription(EVENT* e, char* description);
void addTimeToEventDate(EVENT* e, TIME* t);
TIME remainingTime(EVENT* e);
void displayRemainingTime(EVENT* e);
void displayEvent(EVENT* e);

// these will be called by function pointer parameters to search/remove
bool compareFullEvent(EVENT* left, EVENT* right);
bool compareEventIndex(EVENT* left, EVENT* right);
bool compareEventAllDay(EVENT* left, EVENT* right);
bool compareEventType(EVENT* left, EVENT* right);
bool compareEventRecurrence(EVENT* left, EVENT* right);
bool compareEventDescription(EVENT* left, EVENT* right);
bool compareEventDate(EVENT* left, EVENT* right);
bool compareEventTime(EVENT* left, EVENT* right);
bool compareEventDateAndTime(EVENT* left, EVENT* right);
bool compareEventYear(EVENT* left, EVENT* right);
bool compareEventYearAndMonth(EVENT* left, EVENT* right);
bool isFirstEventAfterSecond(EVENT* first, EVENT* second);
bool isFirstEventBeforeSecond(EVENT* first, EVENT* second);

bool eventWithinTimeRange(EVENT* e, TIME* start, TIME* end);

// don't need these since we're just passing the above functions as parameters
// for search and remove
//bool (*compareEvents[])(EVENT* left, EVENT* right) = { compareFullEvent, 
//    compareEventAllDay, compareEventType, compareEventRecurrence, 
//    compareEventDescription, compareEventTimeAndDate, compareEventDate };
//
//typedef enum Comparison
//{
//    ALLDAY      = 1, 
//    TYPE        = 2,
//    recurrence  = 3,
//    DESCRIPTION = 4,
//    TIMEANDDATE = 5,
//    DATE        = 6,
//} COMPARISON;
