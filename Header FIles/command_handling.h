/* File Guard*/
#pragma once
#ifndef _COMMAND_HANDLING_H_
#define _COMMAND_HANDLING_H_

/* Includes Section */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "colors.h"
#include "parser.h"

/* Functions Prototypes Section */
int ifExist(char buffer[128]);
void commandCheck(char buffer[128]);

#endif // _COMMAND_HANDLING_H_