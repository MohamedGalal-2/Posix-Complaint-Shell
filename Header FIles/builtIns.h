/**
  * @file  builtins.h
  * @brief Header file for defining built-in shell commands.
  */


/*File Guard*/
#pragma once
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
#include "command_handling.h"
#include "colors.h"

/* Functions Prototype Section */
int searchExecutableInPath(const char* command);
void ls(const char* path, int showAll, int classify);
int parseFlagsAndPath(char* argument, int* showAll, int* classify, char* path);
void runFile(const char* fileName);
void echo(char* argument);
void type(char* command);
void help();
void pwd();
int handleBuiltIns(char* command, char* argument);

#endif // _BUILTINS_H