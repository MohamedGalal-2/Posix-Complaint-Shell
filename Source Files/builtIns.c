/* Includes Section */
#include "..\Header Files\builtIns.h"

/*Functions Definition Section*/


void echo(char *argument)
{
	printf("%s\n", argument);
}

void type(char* command)
{
	command = strtok(command, " ");

	if(strcmp(command, "echo") == 0)
	{
		red();
		printf("echo");
		reset();
		printf(" is a shell ");
		red();
		printf("built-in\n");
		reset();
	}
	else if (strcmp(command, "type") == 0)
	{
		red();
		printf("type");
		reset();
		printf(" is a shell ");
		red();
		printf("built-in\n");
		reset();
	}
	else if (strcmp(command, "cd") == 0)
	{
		red();
		printf("cd");
		reset();
		printf(" is a shell ");
		red();
		printf("built-in\n");
		reset();
	}
	else if (strcmp(command, "pwd") == 0)
	{
		red();
		printf("pwd");
		reset();
		printf(" is a shell ");
		red();
		printf("built-in\n");
		reset();
	}
	else if (strcmp(command, "exit") == 0)
	{
		red();
		printf("exit");
		reset();
		printf(" is a shell ");
		red();
		printf("built-in\n");
		reset();
	}
	else
	{
		red();
		printf("%s", command);
		reset();
		printf(" not found\n");
	}
}

int handleBuiltIns(char *command, char *argument)
{
	if (strcmp(command, "echo") == 0)
	{
		echo(argument);
	}
	else if (strcmp(command, "exit") == 0)
	{
		exit(0);
	}
	else if (strcmp(command, "type") == 0)
	{
		type(argument);
	}
	else
	{
		return 0;
	}

	return 1;
}