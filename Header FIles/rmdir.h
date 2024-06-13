#ifndef RMDIR_H
#define RMDIR_H

#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <direct.h>
#include <ctype.h>
#include "parser.h"

// Function to remove a directory at the specified path
// Returns 0 on success, -1 on failure

/**
  * @brief  Remove a directory at the specified path
  * @param  path The path to remove the directory from
  * @return 0 on success, -1 on failure
  */
int _remove_Dir(const char* path);

#endif // RMDIR_H
