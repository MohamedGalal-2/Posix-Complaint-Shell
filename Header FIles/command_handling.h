/**
  * @file command_handling.h
  * @brief Header file for defining functions for checking the shell commands.
  */

/* File Guard */
#pragma once
#ifndef _COMMAND_HANDLING_H_
#define _COMMAND_HANDLING_H_

/* Includes Section */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include "builtIns.h"
#include "colors.h" 
#include "parser.h" 
#include "tokenizer.h"

/* Functions Prototypes Section */

/**
  * @brief  Checks if a command exists in the list of supported commands.
  * @param  buffer The buffer containing the command to check.
  * @return int An integer indicating the existence of the command:
  *             0 if not found, 1 if found, 2 if buffer is empty.
  */
int ifExist(char* buffer);

/**
 * @brief Parses the user input buffer and determines the appropriate action.
 * @param buffer The buffer containing the user input.
 * @note This function extracts the command from the buffer, checks if it exists,
 *       and then either invokes the corresponding built-in function or prints an error message.
 */
void commandCheck(char* buffer);

/**
 * @brief Executes the commands in the buffer sequentially.
 * @param commands The array of commands to execute.
 * @param commandCount The number of commands in the array.
 * @note This function executes the commands in the array sequentially.
 */
void executeCommandsSequentially(char** commands, int commandCount);

#endif // _COMMAND_HANDLING_H_


