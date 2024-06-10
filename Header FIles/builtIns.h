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

#define BUFSIZE 4096


/* Functions Prototype Section */
int parseFlagsAndPath(char* argument, int* showAll, int* classify, int* classAll, char* path);
void runFile(const char* fileName);
bool checkForGreaterThan(const char* input);
void echoFile(const char* argument);
void echo(const char* argument);
void type(char* command);
void help(char* command);
void pwd(int showLogical, int showPhysical);
int handleBuiltIns(char* command, char* buffer);

#endif // _BUILTINS_H