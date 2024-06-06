/**
  * @file parser.c
  * @brief Source file containing functions for parsing user input.
  */
 
 /* Includes Section */
#include "..\Header Files\parser.h"

/* Function Definitions */

char* removeLeadingSpaces(char* str) 
{
    /**
      * @brief Removes leading spaces from a string.
      * @param str The string from which leading spaces will be removed.
      * @return char* Pointer to the modified string.
      */

    while (*str == ' ') str++;
    return str;
}

char* removeLastSpaces(char* str) 
{
    /**
      * @brief Removes trailing spaces from a string.
      * @param str The string from which trailing spaces will be removed.
      * @return char* Pointer to the modified string.
      */
    
    char* end = str + strlen(str) - 1;
    while (end > str && *end == ' ') end--;
    *(end + 1) = '\0';
    return str;
}

char* removeNewLine(char* str) 
{
    /**
      * @brief Removes newline character from a string.
      * @param str The string from which newline character will be removed.
      * @return char* Pointer to the modified string.
      */
     
    char* pos;
    if ((pos = strchr(str, '\n')) != NULL) 
    {
        *pos = '\0';
    }
    return str;
}

char* removeDotSlash(char* str)
{
	/**
	  * @brief Removes the "./" prefix from a string.
	  * @param str The string from which the prefix will be removed.
	  * @return char* Pointer to the modified string.
	  */
	
	if (strncmp(str, "./", 2) == 0) 
	{
		return str + 2;
	}
	return str;
}

char* getCommand(char* buffer)
{
    /**
      * @brief Extracts the command from a buffer containing user input.
      * @param buffer The buffer containing user input.
      * @return char* Pointer to the extracted command string. NULL if memory allocation fails.
      */
    
    // Remove leading spaces
    strcpy(buffer, removeLeadingSpaces(buffer));

    // Allocate memory for the command string
    char* command = (char*)malloc(strlen(buffer) + 1); // +1 for null terminator
    if (command == NULL)
    {
        // Memory allocation failed, return NULL
        return NULL;
    }

    // Copy characters until a space or null terminator is encountered
    int i = 0;
    while (buffer[i] != ' ' && buffer[i] != '\0')
    {
        command[i] = buffer[i];
        i++;
    }

    // Null-terminate the command string
    command[i] = '\0';
    return command;
}

char* getArgument(char* buffer) 
{
    /**
      * @brief Extracts the argument from a buffer containing user input.
      * @param buffer The buffer containing user input.
      * @return char* Pointer to the extracted argument string.
      * @note The caller is responsible for freeing the memory allocated for the returned argument string.
      */

    int i = 0;

    // Skip until the first space character or end of line
    while (buffer[i] != ' ' && buffer[i] != '\n' && buffer[i] != '\0') 
    {
        i++;
    }

    // If there is no argument
    if (buffer[i] == '\n' || buffer[i] == '\0') 
    {
        return NULL;
    }

    // Skip leading spaces to locate the start of the argument
    while (buffer[i] == ' ') 
    {
        i++;
    }

    // Calculate the length of the argument
    int length = strlen(buffer + i);

    // Allocate memory for the argument string
    char* argument = (char*)malloc(length + 1);
    if (argument == NULL) 
    {
        return NULL; // Memory allocation failed
    }

    // Copy the argument from the buffer to the allocated memory
    strcpy(argument, buffer + i);

    return argument;
}