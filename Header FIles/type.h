/**
  * @file  type.h
  * @brief Header file for the type function.
  */

#ifndef TYPE_H
#define TYPE_H

/* Includes Section */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "colors.h"
#include "tokenizer.h"
#include "parser.h"

/* Functions Prototype Section */

/**
  * @brief  Displays the type of shell command.
  * @param  command: The command to be typed.
  */
void type(char* command);

#endif // TYPE_H
