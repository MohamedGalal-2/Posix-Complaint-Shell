/* Includes Section */
#include "..\Header Files\builtIns.h"

/*Functions Definition Section*/


void echo(char *argument)
{
	// dealing with empty string
	if (argument == NULL)
	{
		printf("\n");
	}
	else
	{
		argument = removeNewLine(argument);
		printf("%s\n", argument);
	}
}

void type(char* command)
{
	// dealing with null arguments
	if (command == NULL)
	{
		return;
	}
	else
	{
		command = removeNewLine(command);
	}

	// checking if the command is a built-in
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
	else if (strcmp(command, "help") == 0)
	{
		red();
		printf("help");
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
	// checking if the command doesn't start with a spaces or a tabs
	else if (command[0] == ' ' || command[0] == '\t' || command[0] == '\0')
	{
		return;
	}
	else
	{
		cyan();
		printf("bash: type: ");
		red();
		printf("%s:", command);
		reset();
		printf(" not found\n");
	}
}

void help()
{
	magenta();
	printf("\n");
	printf("**********************************************************\n");
	printf("*                                                        *\n");
	printf("*            List of available commands                  *\n");
	printf("*                                                        *\n");
	printf("* 1. echo: prints the argument to the standard output    *\n");
	printf("* 2. type: prints the type of the command                *\n");
	printf("* 3. cd: changes the current working directory           *\n");
	printf("* 4. pwd: prints the current working directory           *\n");
	printf("* 5. help: prints the list of available commands         *\n");
	printf("* 6. exit: leaves the shell                              *\n");
	printf("*                                                        *\n");
	printf("**********************************************************\n");
	printf("\n");
	reset();
}

void pwd()
{
	char cwd[1024];
	_getcwd(cwd, 1024);
	printf("%s\n", cwd);
}

int handleBuiltIns(char *command, char *buffer)
{
	char *argument = getArgument(buffer);

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
	else if (strcmp(command, "pwd") == 0)
	{
		pwd();
	}
	else if (strcmp(command, "help") == 0)
	{
		help();
	}
	else
	{
		return 0;
	}
}