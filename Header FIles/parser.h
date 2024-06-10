/**
  * @file   parser.h
  * @brief  Header file for defining functions for parsing user input.
  */

/*File Guard*/
#pragma once
#ifndef _PARSER_H
#define _PARSER_H

/* Includes Section */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


/* Macros Section */
#define MAX_INPUT_LENGTH 256

/* Functions Prototype Section */

/**
  * @brief  Removes leading spaces from the input string.
  * @param  str: The input string.
  * @return char*: The input string without leading spaces.
  * @note   This function removes leading spaces from the input string.
  */
char* removeLeadingSpaces(char* str);

/**
  * @brief  Removes trailing spaces from the input string.
  * @param  str: The input string.
  * @return char*: The input string without trailing spaces.
  * @note   This function removes trailing spaces from the input string.
  */
char* removeLastSpaces(char* str);

/**
  * @brief  Removes new line character from the input string.
  * @param  str: The input string.
  * @return char*: The input string without new line character.
  * @note   This function removes new line character from the input string.
  */
char* removeNewLine(char* str);

/**
  * @brief  Removes the "./" prefix from the input string.
  * @param  str: The input string.
  * @return char*: The input string without the "./" prefix.
  * @note   This function removes the "./" prefix from the input string.
  */
char* removeDotSlash(char* str);

/**
  * @brief Trims leading and trailing whitespace from a string.
  *
  * @param str The string to be trimmed.
  */
void trimWhitespace(char* str);

/**
  * @brief  Extracts the command from the input buffer.
  * @param  buffer: The input buffer.
  * @return char*: The extracted command string.
  * @note   This function extracts the command from the input buffer.
  */
char* getCommand(char* buffer);

/**
  * @brief  Extracts the argument from the input buffer.
  * @param  buffer: The input buffer.
  * @return char*: The extracted argument string.
  * @note   This function extracts the argument from the input buffer.
  */
char* getArgument(char* buffer);

#endif // _PARSER_H