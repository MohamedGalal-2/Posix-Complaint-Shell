/**
  * @file  shell.h
  * @brief Header file for defining the shell and its functionalities.
  */

/* File Guard*/
#pragma once
#ifndef _SHELL_H
#define _SHELL_H

/* Includes Section */
#include "command_handling.h"
#include "parser.h"
#include "colors.h"
#include "builtIns.h"
#include "tokenizer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include <Winnt.h>
#include <lmcons.h>
#include <io.h>

/* Macros Section */


// Structure to store user information
struct user
{
	char username[128];
	char computerName[128];
	char currentPath[MAX_PATH];
};

/* Function Prototypes */

/**
  * @brief  Displays a welcome message in the console with instructions.
  * @param  None
  * @return void
  * @note   This function prints a welcome message in cyan color with instructions
  *         on how to use the POSIX shell and provides some basic ASCII art.
  */
static void display_welcome_message();

/**
  * @brief  Displays the username, computer name, and current path in the console.
  * @param  None
  * @return void
  * @note   This function retrieves the username, computer name, and current path
  *         from the environment variables and displays them in the console.
  */
static void info();

/**
  * @brief  Enables raw mode in the console.
  * @param  None
  * @return void
  * @note   This function disables the echo mode and buffering in the console.
  */
static void enableRawMode();

/**
  * @brief  Disables raw mode in the console.
  * @param  None
  * @return void
  * @note   This function enables the echo mode and buffering in the console.
  */
static void disableRawMode();

/**
  * @brief  Moves the cursor back in the console.
  * @param  None
  * @return void
  * @note   This function moves the cursor back by one character in the console.
  */
static void moveCursorBack();

/**
  * @brief  Reads a single character from the console.
  * @param  None
  * @return char
  * @note   This function reads a single character from the console without waiting for a newline.
  */
static void get_Input();

/**
  * @brief  Initializes the shell.
  * @param  None
  * @return void
  * @note   This function initializes the shell by displaying the welcome message,
  *         enabling raw mode, and displaying the user information.
  */
void shell_Init();

#endif // _SHELL_H