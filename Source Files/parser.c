/* Includes Section */
#include "..\Header Files\parser.h"

/* Function Definition Section */


char* removeNewLine(char buffer[])
{
	int i = 0;

	while (buffer[i] != '\n')
	{
		i++;
	}

	char* returned;
	returned = (char*)malloc(i * sizeof(char));

	if (NULL == returned)
	{
		// Memory allocation failed
	}
	else
	{
		for (int j = 0; j < i; j++)
		{
			returned[j] = buffer[j];
		}
		returned[i] = '\0';
	}

	return &(returned[0]);
}

char* getCommand(char *buffer)
{
	char *command = (char *)malloc(128);
	int i = 0;

	while(buffer[i] != ' ' && buffer[i] != '\n')
	{
		command[i] = buffer[i];
		i++;
	}
	command[i] = '\0';
	
	return command;
}

char* getArgument(char *buffer)
{
	char *argument = (char *)malloc(128);
	int i = 0;
	int j = 0;

	while(buffer[i] != ' ')
	{
		i++;
	}
	i++;

	if (NULL == argument)
	{
		// Memory allocation failed
	}
	else
	{
		while (buffer[i] != '\n')
		{
			argument[j] = buffer[i];
			i++;
			j++;
		}
		argument[j] = '\0';
	}

	return argument;
}