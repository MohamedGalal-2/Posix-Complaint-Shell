#ifndef CLEAR_H
#define CLEAR_H

#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

// Function to clear the console screen
void clear_screen();

#endif // CLEAR_H
