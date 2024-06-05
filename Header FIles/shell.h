/* File Guard*/
#pragma once
#ifndef _SHELL_H
#define _SHELL_H

/* Includes Section */
#include "command_handling.h"
#include "parser.h"
#include "colors.h"
#include "builtIns.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <lmcons.h>
#include <io.h>

/* Function Prototypes */
void display_welcome_message();
void get_Input();
void shell_Init();

#endif // _SHELL_H