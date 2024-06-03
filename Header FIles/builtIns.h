/*File Guard*/
#pragma once
#ifndef _BUILTINS_H
#define _BUILTINS_H


/* Includes Section */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <io.h> 
#include "command_handling.h"


/* Functions Prototype Section */
void echo(char* argument);
int handleBuiltIns(char* command, char* argument);

#endif // _BUILTINS_H