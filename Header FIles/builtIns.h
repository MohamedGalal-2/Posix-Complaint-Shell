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
#include "command_handling.h"
#include "colors.h"

#define BUFSIZE 4096


/* Functions Prototype Section */
void trimWhitespace(char* str);
void cd(char* path);
void cat(const char* argument);
void ls(const char* path, int showAll, int classify, int classAll);
int parseFlagsAndPath(char* argument, int* showAll, int* classify, char* path);
void runFile(const char* fileName);
bool checkForGreaterThan(const char* input);
void echoFile(const char* argument);
void echo(char* argument);
void type(char* command);
void help(char* command);
void pwd(int showLogical, int showPhysical);
int handleBuiltIns(char* command, char* argument);

#endif // _BUILTINS_H