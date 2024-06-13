/**
  * @file command_handling.c
  * @brief Source file containing functions implementation for handling commands.
  */

/* Includes Section */
#include "..\Header Files\command_handling.h"

/* Function Definition Section */

// Check if the command is a built-in command
int ifExist(char* buffer) 
{
    if (buffer == NULL || strlen(buffer) == 0) 
    {
        return 2;
    }

    // List of commands
    char command[][10] = { "exit", "echo", "type", "help", "ls", "pwd", "cd", "mkdir", "rmdir", "clear", "cat", "grep", "date", "rm", "cp", "mv", "more", "who", "ps", "touch", "chmod", "chown", "chgrp", "ln", "wc", "sort", "uniq", "cut", "paste", "join", "comm", "diff", "tar", "gzip", "gunzip", "zip", "unzip", "head", "tail", "tr", "sed", "awk", "find", "xargs", "kill" };

    int i = 0;
    int flag = 0;

    // Check if its a file run command
    strcpy(buffer, removeLeadingSpaces(buffer));
    if ((buffer[0] == '.' && buffer[1] == '/') || (buffer[0] == '.' && buffer[1] == '\\'))
    {
        return 3;
    }

    while (i < 43)
    {
        if (strcmp(buffer, command[i]) == 0)
        {
            flag = 1;
            break;
        }
        else if (strcmp(buffer, "") == 0)
        {
            flag = 2;
            break;
        }
        i++;
    }

    return flag;
}

// Execute the command
void commandCheck(char* buffer) 
{
    if (buffer == NULL || strlen(buffer) == 0) 
    {
        // Handle empty input gracefully
        return;
    }

    // Tokenize the input buffer based on the semi-colon symbol ';'
    char* token;
    char* commands[10]; // Maximum 10 sequenced commands supported
    int commandCount = 0;

    token = strtok(buffer, ";");
    while (token != NULL) 
    {
        // Remove leading and trailing spaces from the token
        trimWhitespace(token);

        // Store the command in the array
        commands[commandCount++] = token;

        // Get the next token
        token = strtok(NULL, ";");
    }

    // If there are multiple commands separated by ';', execute them as sequenced commands
    if (commandCount > 1) 
    {
        executeCommandsSequentially(commands, commandCount);
    }
    else 
    {
        // Get the command
        char Command[1024];
        strcpy(Command, getCommand(commands[0]));

        // Check if the command exists
        int flag = ifExist(Command);

        if (flag == 1) 
        {
            handleBuiltIns(Command, commands[0]);
        }
        else if (flag == 2) 
        {
            // Do nothing if the buffer is empty
        }
        else if (flag == 3) 
        {
            // Remove ./ from the command
            commands[0] = removeDotSlash(commands[0]);
            // Run the file
            runFile(commands[0]);
        }
        else 
        {
            printf("%s: ", Command);
            red();
            printf("command");
            reset();
            printf(" not found\n");
        }
    }
}

// Execute the commands sequentially
void executeCommandsSequentially(char** commands, int commandCount) 
{
    for (int i = 0; i < commandCount; ++i) 
    {
        char Command[1024];
        strcpy(Command, getCommand(commands[i]));

        // Check if the command exists
        int flag = handleBuiltIns(Command, commands[i]);

        if (flag) 
        {
            printf("%s: ", Command);
            red();
            printf("command");
            reset();
            printf(" not found\n");
        }
    }
}