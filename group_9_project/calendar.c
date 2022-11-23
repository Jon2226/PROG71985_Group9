// PROG71985 - Fall 2022 - Group Project
// Group 9: Jonathan Ward, Drasti Patel, Komalpreet Kaur

#include "calendar.h"

bool isLeapYear(int year)
{
    if (year % 4 == 0 && year % 100 != 0 || year % 400 == 0)
        return true;
    else
        return false;
}


