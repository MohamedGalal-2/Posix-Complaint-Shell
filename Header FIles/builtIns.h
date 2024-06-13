/**
  * @file  builtins.h
  * @brief Header file for defining built-in shell commands.
  */


/*File Guard*/
#pragma once
#pragma comment(lib, "shlwapi.lib")
#ifndef _BUILTINS_H
#define _BUILTINS_H

/* Includes Section */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <io.h> 
#include <Windows.h>
#include <sys/stat.h>
#include <direct.h>
#include <shellapi.h>
#include <errno.h>
#include <stdbool.h>
#include <shlwapi.h>
#include "parser.h"
#include "command_handling.h"
#include "colors.h"
#include "cat.h"
#include "cd.h"
#include "ls.h"
#include "mkdir.h"
#include "echo.h"
#include "runFile.h"
#include "type.h"
#include "help.h"
#include "pwd.h"
#include "rmdir.h"
#include "grep.h"
#include "clear.h"
#include "date.h"

#define BUFSIZE 4096


/* Functions Prototype Section */

/**
  * @brief  Function to check if '>' is present in the command.
  * @param  input The command to check.
  * @return 1 if '>' is present, 0 otherwise.
  */
bool checkForGreaterThan(const char* input);

/** 
  * @brief  Function to handle built-in shell commands.
  * @param  command The command to handle.
  * @param  buffer The buffer to store the output of the command.
  * @return 1 if the command is a built-in command, 0 otherwise.
  */
int handleBuiltIns(char* command, char* buffer);

#endif // _BUILTINS_H