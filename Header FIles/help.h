/**
  * @file  help.h
  * @brief Header file for the help function.
  */

#ifndef HELP_H
#define HELP_H

/* Includes Section */
#include <stdio.h>
#include <string.h>

/* Functions Prototype Section */

/**
  * @brief  Provides help information for shell commands.
  * @param  command: The command for which help is requested. If NULL or empty, general help is displayed.
  */
void help(char* command);

#endif // HELP_H
