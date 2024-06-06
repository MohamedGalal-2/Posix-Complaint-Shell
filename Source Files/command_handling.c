/**
  * @file command_handling.c
  * @brief Source file containing functions implementation for handling commands.
  */

/* Includes Section */
#include "..\Header Files\command_handling.h"

/* Function Definition Section */

int ifExist(char *buffer)
{
    /**
	  * @brief  Checks if a command exists in the list of supported commands.
	  * @param  buffer The buffer containing the command to check.
	  * @return int An integer indicating the existence of the command:
	  *             0 if not found, 1 if found, 2 if buffer is empty.
	  */
    
      // List of commands
    char command[][10] = { "exit", "echo", "type", "help", "ls", "pwd", "cd", "mkdir", "rmdir", "rm", "cp", "mv", "cat", "more", "date", "who", "ps", "clear", "exit", "touch", "chmod", "chown", "chgrp", "ln", "wc", "grep", "sort", "uniq", "cut", "paste", "join", "comm", "diff", "tar", "gzip", "gunzip", "zip", "unzip", "head", "tail", "tr", "sed", "awk", "find", "xargs", "kill" };

    int i = 0;
    int flag = 0;

    // Check if its a file run command
    strcpy(buffer, removeLeadingSpaces(buffer));
    if (buffer[0] == '.' && buffer[1] == '/')
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

void commandCheck(char *buffer)
{
    /**
      * @brief  Parses the user input buffer and determines the appropriate action.
      * @param  buffer The buffer containing the user input.
      * @return void
      * @note   This function extracts the command from the buffer, checks if it exists,
      *         and then either invokes the corresponding built-in function or prints an error message.
      */

    char Command[1024];
    char Argument[1024];

    // Get the command
    strcpy(Command, getCommand(buffer));

    // Check if the command exists
    int flag = ifExist(Command);

    if (flag == 1)
    {
        handleBuiltIns(Command, buffer);
    }
    else if (flag == 2)
    {
        // Do nothing if the buffer is empty
    }
    else if (flag == 3)
	{
		// remove ./ from the command
        buffer = removeDotSlash(buffer);
        // Run the file
		runFile(buffer);
	}
    else
    {
        buffer = removeNewLine(buffer);
        printf("%s: ", Command);
        red();
        printf("command");
        reset();
        printf(" not found\n");
    }
}
