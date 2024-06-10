#ifndef MKDIR_H
#define MKDIR_H

#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <direct.h>
#include "parser.h"

void remove_quotes(char* str);

// Function to create a directory at the specified path
// Returns 0 on success, -1 on failure
int _make_Dir(const char* path);

#endif // MKDIR_H
