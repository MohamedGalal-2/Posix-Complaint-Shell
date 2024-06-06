/* Includes Section */
#include "..\Header Files\builtIns.h"

/*Functions Definition Section */


int searchExecutableInPath(const char* command) 
{
	/**
	  * @brief Searches for the executable file in the system's PATH environment variable.
      * @param command The command to search for.
      * @return int Returns 1 if the command is found in the PATH, otherwise returns 0.
      */
	
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

void ls(const char* path, int showAll, int classify) {
	struct _finddata_t fileinfo;
	intptr_t handle;

	char searchPath[MAX_PATH + 1];
	snprintf(searchPath, sizeof(searchPath), "%s\\*.*", path);

	handle = _findfirst(searchPath, &fileinfo);
	if (handle == -1) {
		fprintf(stderr, "Unable to list directory contents. Error Code: %d\n", errno);
		return;
	}

	do {
		// Skip hidden files if showAll is not set
		if (!showAll && (fileinfo.name[0] == '.')) {
			continue;
		}

		// Print the file or directory name
		printf("%s", fileinfo.name);

		// If classify is set, add a slash for directories
		if (classify) {
			if (fileinfo.attrib & _A_SUBDIR) {
				printf("/");
			}
			else {
				printf("*");
			}
		}

		printf("\n");
	} while (_findnext(handle, &fileinfo) == 0);

	_findclose(handle);
}

int parseFlagsAndPath(char* argument, int* showAll, int* classify, char* path) {
	*showAll = 0;
	*classify = 0;
	path[0] = '\0';

	char* token = strtok(argument, " ");
	while (token != NULL) 
	{
		if (strcmp(token, "-a") == 0) 
		{
			*showAll = 1;
		}
		else if (strcmp(token, "-f") == 0) 
		{
			*classify = 1;
		}
		else {
			// Remove double quotes if present
			if (token[0] == '"' && token[strlen(token) - 1] == '"') 
			{
				token[strlen(token) - 1] = '\0';
				token++;
			}
			strncpy(path, token, MAX_PATH);
		}
		token = strtok(NULL, " ");
	}

	// If no path is specified, use the current working directory
	if (strlen(path) == 0) 
	{
		_getcwd(path, MAX_PATH);
	}

	return 1;
}


void runFile(const char* fileName) {
	// Attempt to open the file
	HINSTANCE result = ShellExecute(NULL, "OPEN", fileName, NULL, NULL, SW_SHOWNORMAL);
	if ((int)result <= 32) {
		// Failed to open the file, print error details
		DWORD error = GetLastError();
		fprintf(stderr, "Failed to run file: %s (Error Code: %lu)\n", fileName, error);

		// Print a more descriptive error message based on the error code
		switch (error) {
		case ERROR_FILE_NOT_FOUND:
			fprintf(stderr, "File not found.\n");
			break;
		case ERROR_ACCESS_DENIED:
			fprintf(stderr, "Access denied.\n");
			break;
		default:
			fprintf(stderr, "Unknown error.\n");
			break;
		}
	}
	else {
		// File ran successfully
		printf("File ran successfully: %s\n", fileName);
	}
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
		if (strcmp(currentCommand, "ls") == 0 || strcmp(currentCommand, "echo") == 0 || strcmp(currentCommand, "type") == 0 || strcmp(currentCommand, "cd") == 0 || strcmp(currentCommand, "pwd") == 0 || strcmp(currentCommand, "help") == 0 || strcmp(currentCommand, "exit") == 0)
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
	printf("***********************************************************************\n");
	printf("*************************** POSIX SHELL HELP ***************************\n");
	printf("***********************************************************************\n");
	printf("\n");
	printf("The following commands are built-in to the POSIX shell:\n");
	printf("\n");
	printf("1. echo <string> - Displays the given string.\n");
	printf("2. exit - Exits the shell.\n");
	printf("3. type <command> - Displays the type of the given command.\n");
	printf("4. pwd - Displays the current working directory.\n");
	printf("5. help - Displays help information about the shell.\n");
	printf("6. ls - Lists the contents of the current directory.\n");
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
	else if (strcmp(command, "ls") == 0) {
		int showAll = 0;
		int classify = 0;
		char path[MAX_PATH];

		if (argument != NULL) {
			parseFlagsAndPath(argument, &showAll, &classify, path);
		}
		else {
			_getcwd(path, MAX_PATH);
		}

		ls(path, showAll, classify);
	}
	else
	{
		return 0;
	}
}