/* Includes Section */
#include "..\Header Files\parser.h"

/* Function Definition Section */

char* removeLeadingSpaces(char* str) 
{
	int index = 0, i = 0;

	// Find the index of the first non-space and non-tab character
	while (str[index] == ' ' || str[index] == '\t') {
		index++;
	}

	// Shift the characters to the left
	while (str[index]) {
		str[i++] = str[index++];
	}

	// Null-terminate the string
	str[i] = '\0';

	return str;
}

char* removeNewLine(char *buffer)
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
		return;
	}
	else
	{
		for (int j = 0; j < i; j++)
		{
			returned[j] = buffer[j];
		}

		// Null-terminate the string
		returned[i] = '\0';
	}

	return &(returned[0]);
}

char* getCommand(char *buffer)
{
	// Remove leading spaces
	strcpy(buffer, removeLeadingSpaces(buffer));

	char *command = (char *)malloc(128);
	int i = 0;

	while(buffer[i] != ' ' && buffer[i] != '\n' && buffer[i] != '\t')
	{
		command[i] = buffer[i];
		i++;
	}

	if (NULL == command)
	{
		return;
	}

	// Null-terminate the string
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

		// If there is no argument
		if (buffer[i] == '\n')
		{
			return NULL;
		}
	}
	i++;

	if (NULL == argument)
	{
		return;
	}
	else
	{
		while (buffer[i] != '\0')
		{
			argument[j] = buffer[i];
			i++;
			j++;
		}

		// Null-terminate the string
		argument[j] = '\0';
	}

	return argument;
}