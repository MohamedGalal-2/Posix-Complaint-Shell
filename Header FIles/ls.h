#ifndef LS_H
#define LS_H
#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <io.h>
#include <direct.h>
#include <Windows.h>
#include <ctype.h>
#include "parser.h"

// Function declarations

char* trim(const char* str);

/**
 * @brief  Parses the flags and path from the given argument.
 * @param  argument The argument to parse.
 * @param  showAll The variable to store the value of the showAll flag.
 * @param  classify The variable to store the value of the classify flag.
 * @param  classAll The variable to store the value of the classAll flag.
 * @param  path The variable to store the path.
 * @return 0 if successful, -1 if an error occurred.
 */
int parseFlagsAndPath(char* argument, int* showAll, int* classify, int* classAll, char* path);

/**
 * @brief Lists the contents of a directory.
 * @param path The path of the directory to list.
 * @param showAll If non-zero, show all files including hidden ones.
 * @param classify If non-zero, append indicators to file names (e.g., '/' for directories).
 * @param classAll If non-zero, classify all files.
 */
void ls(const char* path, int showAll, int classify, int classAll);

#endif // LS_H
