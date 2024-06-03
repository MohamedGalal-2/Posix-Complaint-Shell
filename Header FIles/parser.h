/*File Guard*/
#pragma once
#ifndef _PARSER_H
#define _PARSER_H

/* Includes Section */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Functions Prototype Section */
char* removeLeadingSpaces(char* str);
char* removeNewLine(char *buffer);
char* getCommand(char* buffer);
char* getArgument(char* buffer);

#endif // _PARSER_H