#ifndef CD_H
#define CD_H

#include <Windows.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <direct.h>
#include "parser.h"


#define MAX_PATH 260  // Define the maximum path length

// Function declarations

/**
  * @brief  Changes the current directory to the specified path.
  * @param  path The path to change the directory to. If NULL or empty, changes to the home directory.
  * @return true if the directory was successfully changed, false otherwise.
  */
void cd(char* path);

/**
 * @brief Changes the current directory to the user's home directory.
 */
void changeToHomeDirectory();

/**
 * @brief Processes the given path, replacing any tilde (~) with the user's home directory.
 * @param path The path containing a tilde to process.
 * @return true if the path was successfully processed, false otherwise.
 */
bool processPathWithTilde(char* path);

/**
 * @brief Strips the trailing double quote from the path if it is present.
 * @param path The path to strip the trailing double quote from.
 */
void stripTrailingQuote(char* path);

#endif // CD_H
