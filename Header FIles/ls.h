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

int parseFlagsAndPath(char* argument, int* showAll, int* classify, int* classAll, char* path);

/**
 * @brief Lists the contents of a directory.
 *
 * @param path The path of the directory to list.
 * @param showAll If non-zero, show all files including hidden ones.
 * @param classify If non-zero, append indicators to file names (e.g., '/' for directories).
 * @param classAll If non-zero, classify all files.
 */
void ls(const char* path, int showAll, int classify, int classAll);

#endif // LS_H
