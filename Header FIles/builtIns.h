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
#include "command_handling.h"
#include "colors.h"

/* Functions Prototype Section */
void echo(char* argument);
void type(char* command);
void help();
void pwd();
int handleBuiltIns(char* command, char* argument);

#endif // _BUILTINS_H