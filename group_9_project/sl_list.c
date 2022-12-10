// PROG71985 - Fall 2022 - Group Project
// Group 9: Jonathan Ward, Drasti Patel, Komalpreet Kaur
// Jonathan Ward - based on examples from Prof. Steve Hendrikse

// implementation of singly-linked list data structure

#include "sl_list.h"

LIST createList(void)
{
    LIST newlist = { 0 };
    return newlist;
}

void disposeList(LIST* list)
{
    NODE* tmp;

    NODE* current = list->head;
    while (current != NULL)
    {
        tmp = current;
        current = getNextNode(current);
        disposeNode(tmp);
    }
}

bool addEventToList(LIST* list, EVENT eventToAdd)
{
    NODE* newNode = createNode(eventToAdd);

    if (list->head == NULL)    // if list is empty
    {
        setNextNode(newNode, list->head);
        list->head = newNode;
    }
    else
    {
        NODE* current = list->head;

        while (getNextNode(current) != NULL)
        {
            current = getNextNode(current);
        }

        setNextNode(current, newNode);
    }
    return true;
}

// This should only be used with compareFullEvent(), compareEventTimeAndDate(),
// or compareEventDate() (for all-day events).  It will simply delete the first
// event it finds that matches whatever criterion is given, so unique critera 
// are best to avoid unexpected behaviour.  
bool removeEventFromList(LIST* list, EVENT* eventToDelete,
        bool (*compareEvents)(EVENT* left, EVENT* right))
{
    bool found = false;
    NODE* current = list->head;

    if (compareEvents(&current->data, eventToDelete))
    {
        if (getNextNode(current) == NULL)
            list->head = NULL;
        else
            list->head = getNextNode(current);

        disposeNode(current);
        return found;
    }
    NODE* prev = NULL;    // needed to re-link after deleting
    while (current != NULL)
    {
        if (compareEvents(&current->data, eventToDelete))
            break;

        prev = current;
        current = getNextNode(current);
    }
    if (current != NULL)
        found = true;

    setNextNode(prev, getNextNode(current));    // unlink current node
    disposeNode(current);

    return found;
}

int getCurrentCount(LIST* list)
{
    int count = 0;

    if (list->head != NULL)    // skip to return 0 if list empty
    {
        NODE* current = list->head;
        do
        {
            count++;
            current = getNextNode(current);
        } while (current != NULL);
    }
    return count;
}

void displayList(LIST* list)
{
    if (list->head != NULL)
    {
        NODE* current = list->head;
        do
        {
            displayEvent(&current->data);
            current = getNextNode(current);
        } while (current != NULL);
    }
}

EVENT* searchListForEvent(LIST* list, EVENT* eventToCompare,
        bool (*compareEvents)(EVENT* left, EVENT* right))
{
    EVENT* notFoundEvent = NULL;

    if (list->head == NULL)
        return notFoundEvent;

    NODE* current = list->head;
    do
    {
        if (compareEvents(eventToCompare, getEventFromNode(current)))
            return getEventFromNode(current);

        current = getNextNode(current);
    } while (current != NULL);

    return notFoundEvent;
}

EVENT* searchListForEventByTimeRange(LIST* list, TIME* start, TIME* end)
{
    EVENT* notFoundEvent = NULL;

    if (list->head == NULL)
        return notFoundEvent;

    NODE* current = list->head;
    do
    {
        if (eventWithinTimeRange(getEventFromNode(current), start, end))
            return getEventFromNode(current);

        current = getNextNode(current);
    } while (current != NULL);

    return notFoundEvent;
}
