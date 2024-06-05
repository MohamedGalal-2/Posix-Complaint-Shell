/* Includes Section */
#include "..\Header Files\builtIns.h"

/*Functions Definition Section */

/**
 * @brief Searches for the executable file in the system's PATH environment variable.
 * @param command The command to search for.
 * @return int Returns 1 if the command is found in the PATH, otherwise returns 0.
 */
int searchExecutableInPath(const char* command) 
{
	// Get the PATH environment variable
	char* path_env;
	size_t size;
	if (_dupenv_s(&path_env, &size, "PATH") != 0 || path_env == NULL) 
	{
		fprintf(stderr, "Error getting PATH environment variable.\n");
		return 0;
	}

	// Tokenize the PATH variable to get individual directories
	char* path_copy = strdup(path_env);
	char* token = strtok(path_copy, ";");
	while (token != NULL) 
	{
		// Concatenate the directory path with the command name
		size_t full_path_len = strlen(token) + strlen(command) + 1;
		char* full_path = (char*)malloc(full_path_len);
		if (full_path == NULL) 
		{
			fprintf(stderr, "Memory allocation failed.\n");
			free(path_copy);
			return 0;
		}
		snprintf(full_path, full_path_len, "%s\\%s", token, command);

		// Check if the concatenated path is an executable file
		if (GetFileAttributes(full_path) != INVALID_FILE_ATTRIBUTES) 
		{
			printf("%s is %s\n", command, full_path);
			free(path_copy);
			free(path_env);
			free(full_path);
			return 1;
		}

		free(full_path);
		token = strtok(NULL, ";");
	}

	free(path_copy);
	free(path_env);
	return 0;
}

void type(char* command) 
{
	// Dealing with null arguments
	if (command == NULL) 
	{
		return;
	}

	// Allocate memory for tokens array
	int maxTokens = 20;
	char** tokens = (char**)malloc(maxTokens * sizeof(char*));
	if (tokens == NULL) 
	{
		fprintf(stderr, "Memory allocation failed for tokens array.\n");
		exit(1);
	}

	// Tokenize the command
	int tokenCount = 0;
	tokenizeInput(command, tokens, &tokenCount, maxTokens);

	// Loop through each token
	for (int i = 0; i < tokenCount; i++) 
	{
		// Ensure currentCommand points to a valid string
		char* currentCommand = strdup(tokens[i]);
		if (currentCommand == NULL) 
		{
			fprintf(stderr, "Memory allocation failed for currentCommand.\n");
			freeTokens(tokens, tokenCount);
			exit(1);
		}

		// Remove leading spaces, new line character, and last spaces for each command
		currentCommand = removeLeadingSpaces(currentCommand);
		currentCommand = removeNewLine(currentCommand);
		currentCommand = removeLastSpaces(currentCommand);

		// Check if the command is empty or null
		if (strcmp(currentCommand, "") == 0 || strcmp(currentCommand, "\0") == 0) 
		{
			free(currentCommand);
			continue; // Skip empty commands
		}

		// Checking if the command is a built-in
		if (strcmp(currentCommand, "echo") == 0 || strcmp(currentCommand, "type") == 0 || strcmp(currentCommand, "cd") == 0 || strcmp(currentCommand, "pwd") == 0 || strcmp(currentCommand, "help") == 0 || strcmp(currentCommand, "exit") == 0) 
		{
			red();
			printf("%s", currentCommand);
			reset();
			printf(" is a shell ");
			red();
			printf("built-in\n");
			reset();
		}
		else 
		{
			// Check if the command is an executable file
			int pathFlag = searchExecutableInPath(currentCommand);
			if (pathFlag == 1) 
			{
				printf("%s", currentCommand);
			}
			else 
			{
				cyan();
				printf("bash: type: ");
				red();
				printf("%s:", currentCommand);
				reset();
				printf(" not found\n");
			}
		}

		free(currentCommand);
	}

	// Free memory allocated for tokens
	freeTokens(tokens, tokenCount);
}

void echo(const char* argument)
{
	// Dealing with empty string or NULL pointer
	if (argument == NULL || *argument == '\0')
	{
		printf("\n");
	}
	else
	{
		char* cleanedArgument = removeNewLine(argument); // Assuming removeNewLine returns a cleaned string
		if (cleanedArgument != NULL)
		{
			printf("%s\n", cleanedArgument);
			free(cleanedArgument); // Free the memory allocated by removeNewLine
		}
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