// PROG71985 - Fall 2022 - Group Project
// Group 9: Jonathan Ward, Drasti Patel, Komalpreet Kaur
// Jonathan Ward - based on examples from Prof. Steve Hendrikse

// declarations for singly-linked list data structure

#pragma once
#include "sl_node.h"

typedef struct List
{
    NODE* head;
} LIST;

LIST createList(void);
void disposeList(LIST* list);

bool addEventToList(LIST* list, EVENT eventToAdd);
bool removeEventFromList(LIST* list, EVENT* eventToDelete,
        bool (*compareEvents)(EVENT* left, EVENT* right));

int getCurrentCount(LIST* list);
void displayList(LIST* list);

EVENT* searchListForEvent(LIST* list, EVENT* eventToCompare, 
        bool (*compareEvents)(EVENT* left, EVENT* right));

EVENT* searchListForEventByTimeRange(LIST* list, TIME* start, TIME* end);
