#ifndef MKDIR_H
#define MKDIR_H

#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <direct.h>
#include "parser.h"

// Function to create a directory at the specified path
// Returns 0 on success, -1 on failure

/**
  * @brief  Create a directory at the specified path
  * @param  path The path to create the directory at
  * @return 0 on success, -1 on failure
  */
int _make_Dir(const char* path);

#endif // MKDIR_H
