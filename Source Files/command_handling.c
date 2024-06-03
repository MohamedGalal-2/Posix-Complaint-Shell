/* Includes Section */
#include "..\Header Files\command_handling.h"

/* Function Definition Section */


int ifExist(char buffer[128])
{
	// List of commands
	char command[][10] = {"exit", "echo", "type", "help", "ls", "pwd", "cd", "mkdir", "rmdir", "rm", "cp", "mv", "cat", "more", "date", "who", "ps", "clear", "exit", "touch", "chmod", "chown", "chgrp", "ln", "wc", "grep", "sort", "uniq", "cut", "paste", "join", "comm", "diff", "tar", "gzip", "gunzip", "zip", "unzip", "head", "tail", "tr", "sed", "awk", "find", "xargs", "kill"};
	
	int i = 0;
	int flag = 0; 

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

void commandCheck(char buffer[128])
{
	char Command[128];
	char Argument[128];

	// get the command
	strcpy(Command, getCommand(buffer));

	// check if the command exists
	int flag = ifExist(Command);

	if (flag == 1)		// if the command exists
	{
		handleBuiltIns(Command, buffer);
	}
	else if (flag == 2) // if the command is empty
	{
		
	}
	else				// if the command does not exist
	{
		buffer = removeNewLine(buffer);
		printf("%s: ", buffer);
		red();
		printf("command");
		reset();
		printf(" not found\n");
	}
}
