/**
  * @file  echo.h
  * @brief Header file for the echo function.
  */

#ifndef ECHO_H
#define ECHO_H

/* Includes Section */
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

/* Functions Prototype Section */

/**
  * @brief  Prints the input to the standard output.
  * @param  argument: The argument string to be printed.
  */
void echo(const char* argument);

/**
  * @brief  Echoes input to a file.
  * @param  argument: The argument string containing the text to echo and the file name.
  */
void echoFile(const char* argument);

#endif // ECHO_H
