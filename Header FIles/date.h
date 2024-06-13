#ifndef DATE_H
#define DATE_H

#include <stdbool.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Function declarations
void display_current_datetime();
void display_formatted_datetime(const char *format);
bool set_system_datetime(int month, int day, int hour, int minute, int year);

#endif // DATE_H
