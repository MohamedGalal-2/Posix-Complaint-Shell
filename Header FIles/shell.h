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
#include <stdbool.h>
#include <conio.h>
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
  * @brief  Moves the cursor one position to the left.
  * @param  None
  * @return void
  * @note   This function moves the cursor one position to the left in the console.
  */
void moveCursorLeft();

/**
  * @brief  Moves the cursor one position to the right.
  * @param  None
  * @return void
  * @note   This function moves the cursor one position to the right in the console.
  */
void moveCursorRight();

/**
  * @brief  Moves the cursor to the start of the line.
  * @param  initialX The initial X position of the cursor.
  * @param  initialY The initial Y position of the cursor.
  * @param  tempIndex The index of the current character in the temp buffer.
  * @return void
  * @note   This function moves the cursor to the start of the line based on the initial
  *         X and Y positions and the temp buffer index.
  */
void moveCursorToStart(int initialX, int initialY, int tempIndex);

/**
  * @brief  Redraws the current line in the console.
  * @param  tempBuffer The temporary buffer containing the current line.
  * @param  initialX The initial X position of the cursor.
  * @param  initialY The initial Y position of the cursor.
  * @param  tempIndex The index of the current character in the temp buffer.
  * @return void
  * @note   This function clears the current line, redraws the content of the temp buffer,
  *         and moves the cursor to the correct position.
  */
static void redrawLine(const char* tempBuffer, int initialX, int initialY, int tempIndex);

/**
  * @brief  Handles the user input in the console.
  * @param  buffer The input buffer.
  * @param  index The index of the current character in the buffer.
  * @return void
  * @note   This function handles the user input character by character and updates
  *         the buffer accordingly. It supports basic editing features like backspace,
  *         arrow keys, and home/end keys.
  */
static void handleInput(char buffer[], int* index);

/** @brief  Gets the user input from the console.
  * @param  None
  * @return void
  * @note   This function reads the user input character by character and handles
  *         the input accordingly. It supports basic editing features like backspace,
  *         arrow keys, and home/end keys.
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