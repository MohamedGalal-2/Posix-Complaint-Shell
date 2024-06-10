#include "..\Header Files\builtIns.h"

/* Global Variables Section */
int followLinks = 1;			// Default behavior is to follow symbolic links

/*Functions Definition Section */

int parseFlagsAndPath(char* argument, int* showAll, int* classify, int* classAll, char* path)
{
	*showAll = 0;
	*classify = 0;
	*classAll = 0;
	path[0] = '\0';

	// Trim the leading and trailing spaces
	trimWhitespace(argument);

	if (argument == NULL || strlen(argument) == 0)
	{
		return 0;
	}

	char* token = strtok(argument, " ");

	// Check if flags are provided
	while (token != NULL && token[0] == '-')
	{
		if (strcmp(token, "-af") == 0)
		{
			*classAll = 1;
		}
		else if (strcmp(token, "-a") == 0)
		{
			*showAll = 1;
		}
		else if (strcmp(token, "-f") == 0)
		{
			*classify = 1;
		}

		// Move to the next token
		token = strtok(NULL, " ");
	}

	// Process the remaining part of the argument as the path
	if (token != NULL)
	{
		strcpy(path, token);
	}

	// Check if the path is a ~
	if (path[0] == '~')
	{
		// Get the user's home directory
		char homeDir[MAX_PATH];
		if (GetEnvironmentVariableA("USERPROFILE", homeDir, MAX_PATH) > 0)
		{
			// Concatenate the home directory with the remaining path
			char newPath[MAX_PATH];
			snprintf(newPath, MAX_PATH, "%s%s", homeDir, path + 1); // Skip the '~' character
			// Call ls with the new path
			ls(newPath, *showAll, *classify, *classAll);
			return 0;
		}
		else
		{
			fprintf(stderr, "Error: Unable to get user's home directory\n");
			return 0;
		}
	}
	else if (strlen(path) == 0)
	{
		_getcwd(path, MAX_PATH);
	}

	return 0;
}

void runFile(const char* fileName)
{
	// Use system command to execute the file
	int result = system(fileName);

	// Check the result of the system command
	if (result == -1)
	{
		// Failed to execute the file
		fprintf(stderr, "Failed to run file: %s\n", fileName);
	}
	else {
		// File executed successfully
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
		if (strcmp(currentCommand, "cat") == 0 || strcmp(currentCommand, "ls") == 0 || strcmp(currentCommand, "echo") == 0 || strcmp(currentCommand, "type") == 0 || strcmp(currentCommand, "cd") == 0 || strcmp(currentCommand, "pwd") == 0 || strcmp(currentCommand, "help") == 0 || strcmp(currentCommand, "exit") == 0)
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
			// Command not found
			cyan();
			printf("bash: type: ");
			red();
			printf("%s:", currentCommand);
			reset();
			printf(" not found\n");
		}

		free(currentCommand);
	}

	// Free memory allocated for tokens
	freeTokens(tokens, tokenCount);
}

bool checkForGreaterThan(const char* input)
{
	bool inside_quotes = false;

	if (input == NULL)
	{
		return false;
	}

	for (int i = 0; input[i] != '\0'; i++) 
	{
		if (input[i] == '"') 
		{
			inside_quotes = !inside_quotes;
		}
		else if (input[i] == '>' && !inside_quotes) {
			return true; // '>' operand found outside of double quotes
		}
	}

	return false; // '>' operand not found outside of double quotes
}

void echoFile(const char* argument)
{
	// Extracting filename after the '>' operand
	const char* ptr = argument;
	while (*ptr != '\0' && *ptr != '>') {
		ptr++;
	}

	// Move past '>'
	ptr++;
	while (*ptr != '\0' && (*ptr == ' ' || *ptr == '\t')) {
		ptr++; // Skip spaces and tabs
	}

	const char* filename = ptr;

	// Opening file for writing
	FILE* file = fopen(filename, "w");
	if (file == NULL) {
		printf("Error: Unable to open file %s for writing.\n", filename);
		return;
	}

	// Writing content to the file

	// Skip double quotes if present
	if (*argument == '\"')
	{
		argument++;
		while (*argument != '\"' && *argument != '\0') {
			fprintf(file, "%c", *argument);
			argument++;
		}
	}
	else
	{
		// print the argument till the > operand
		while (*argument != '>' && *argument != '\0')
		{
			fprintf(file, "%c", *argument);
			argument++;
		}
	}

	// Closing the file
	fclose(file);
}

void echo(const char* argument) {
	// Dealing with empty string or NULL pointer
	if (argument == NULL || *argument == '\0') {
		printf("\n");
		return;
	}

	// Parse flags
	bool escape = false; // Flag for -e option (enable interpretation of backslash escapes)
	bool no_new_line = false; // Flag for -n option (no newline)
	bool showE = false; // Flag for -E option (disable interpretation of backslash escapes)
	bool flags_processed = false;

	// Process flags
	while (*argument == '-' && !flags_processed) {
		argument++; // Skip '-'
		while (*argument != '\0' && *argument != ' ') {
			switch (*argument) {
			case 'e':
				escape = true;
				break;
			case 'n':
				no_new_line = true;
				break;
			case 'E':
				showE = true;
				break;
			default:
				// If we encounter an invalid flag, treat the rest as normal text
				flags_processed = true;
				putchar('-');
				putchar(*argument);
				break;
			}
			argument++;
		}

		// Skip spaces after flags
		while (*argument == ' ')
			argument++;

		// Check if we reached the end of flags
		if (*argument == '\0' || *argument != '-') {
			flags_processed = true;
		}
	}

	// Check if the text is enclosed in double quotes
	bool in_quotes = false;
	if (*argument == '"') {
		const char* end_quote = strchr(argument + 1, '"');
		if (end_quote != NULL) {
			in_quotes = true;
			argument++; // Skip the initial double quote
		}
	}

	// Process and print the argument text
	while (*argument != '\0') {
		if (in_quotes && *argument == '"') {
			// End of quoted text
			in_quotes = false;
			argument++; // Skip the closing double quote
			continue;
		}
		else if (escape && *argument == '\\') {
			argument++;
			switch (*argument) {
			case 'n':
				putchar('\n');
				break;
			case 't':
				putchar('\t');
				break;
			case '\\':
				putchar('\\');
				break;
			default:
				putchar('\\');
				putchar(*argument);
				break;
			}
		}
		else {
			putchar(*argument);
		}
		argument++;
	}

	// Print newline if -n flag is not set
	if (!no_new_line) {
		putchar('\n');
	}
}

void help(char* command)
{
	if (command == NULL || strlen(command) == 0)
	{
		// Print general help information
		printf("\n");
		printf("Usage: help [command]\n");
		printf("\n");
		printf("This is a POSIX-compliant shell.\n");
		printf("\n");
		printf("These shell commands are built-in. Type `help' to see this list.\n");
		printf("\n");
		printf("cd [-L|[-P [-e]] [-@]] [dir]\n");
		printf("    Change the shell working directory.\n");
		printf("\n");
		printf("exit [n]\n");
		printf("    Exit the shell.\n");
		printf("\n");
		printf("echo [-neE] [arg ...]\n");
		printf("    Write arguments to the standard output.\n");
		printf("\n");
		printf("pwd [-LP]\n");
		printf("    Print the current working directory.\n");
		printf("\n");
		printf("type [-afptP] name [name ...]\n");
		printf("    Indicate how each name would be interpreted if used as a command name.\n");
		printf("\n");
		printf("help [-dms] [pattern ...]\n");
		printf("    Display information about built-in commands.\n");
		printf("\n");
		printf("ls [-a -f -af] [file ...]\n");
		printf("    List directory contents.\n");
		printf("\n");
		printf("cat [file] or cat [file] < [file]\n");
		printf("    Concatenate files and print on the standard output.\n");
		printf("\n");
		printf("Supports command piping using the `|` operator.\n");
		printf("\n");
		printf("For more information on a specific command, type `help <command>'.\n");
		printf("\n");
	}
	else {
		// Tokenize the input command string
		char* token = strtok(command, " ");
		while (token != NULL) {
			// Display information about each command token
			if (strcmp(token, "cd") == 0)
			{
				printf("\n");
				printf("cd: cd [-L|[-P [-e]] [-@]] [dir]\n");
				printf("    Change the shell working directory.\n");
				printf("\n");
			}
			else if (strcmp(token, "exit") == 0)
			{
				printf("\n");
				printf("exit: exit [n]\n");
				printf("    Exit the shell.\n");
				printf("\n");
			}
			else if (strcmp(token, "echo") == 0)
			{
				printf("\n");
				printf("echo: echo [-neE] [arg ...]\n");
				printf("    Write arguments to the standard output.\n");
				printf("\n");
			}
			else if (strcmp(token, "pwd") == 0)
			{
				printf("\n");
				printf("pwd: pwd [-LP]\n");
				printf("    Print the current working directory.\n");
				printf("\n");
			}
			else if (strcmp(token, "type") == 0)
			{
				printf("\n");
				printf("type: type [-afptP] name [name ...]\n");
				printf("    Indicate how each name would be interpreted if used as a command name.\n");
				printf("\n");
			}
			else if (strcmp(token, "help") == 0)
			{
				printf("\n");
				printf("help: help [-dms] [pattern ...]\n");
				printf("    Display information about built-in commands.\n");
				printf("\n");
			}
			else if (strcmp(token, "ls") == 0)
			{
				printf("\n");
				printf("ls: ls [-af] [file ...]\n");
				printf("    List directory contents.\n");
				printf("\n");
			}
			else if (strcmp(token, "cat") == 0)
			{
				printf("\n");
				printf("cat [file] or cat [file] < [file]\n");
				printf("    Concatenate files and print on the standard output.\n");
				printf("\n");
			}
			else {
				printf("\n");
				printf("bash: help: %s: no help topics match\n", token);
				printf("\n");
			}

			// Get the next token
			token = strtok(NULL, " ");
		}
	}
}

void pwd(int showLogical, int showPhysical)
{
	char cwd[1024];
	if (showLogical && !showPhysical)
	{
		_getcwd(cwd, 1024);
	}
	else if (showPhysical && !showLogical)
	{
		_fullpath(cwd, ".", 1024);
	}
	else
	{
		// Both flags are either not provided or provided together
		_getcwd(cwd, 1024);
	}
	printf("%s\n", cwd);
}

int handleBuiltIns(char* command, char* buffer)
{
	if (command == NULL || buffer == NULL)
	{
		return 0; // Or any other appropriate error code
	}

	char* argument = getArgument(buffer);

	if (strcmp(command, "help") == 0)
	{
		help(argument);
	}
	else if (strcmp(command, "echo") == 0)
	{
		checkForGreaterThan(argument) ? echoFile(argument) : echo(argument);
	}
	else if (strcmp(command, "exit") == 0)
	{
		if (argument != NULL) {
			int exitCode = atoi(argument);
			exit(exitCode);
		}
		else {
			exit(0);
		}
		// If still running here, exit command didn't exit the process, we'll attempt to exit PowerShell
		system("exit; exit");
		// The first 'exit' command exits the shell, and the second one exits PowerShell
	}
	else if (strcmp(command, "type") == 0) {
		type(argument);
	}
	else if (strcmp(command, "pwd") == 0) {
		int showLogical = 0;
		int showPhysical = 0;

		// Parse the arguments to check for -L and -P flags
		if (argument != NULL) {
			char* token = strtok(argument, " ");
			while (token != NULL) {
				if (strcmp(token, "-L") == 0) {
					showLogical = 1;
				}
				else if (strcmp(token, "-P") == 0) {
					showPhysical = 1;
				}
				token = strtok(NULL, " ");
			}
		}

		// Call pwd function with flags
		pwd(showLogical, showPhysical);
	}
	else if (strcmp(command, "ls") == 0) {
		int showAll = 0;
		int classify = 0;
		int classAll = 0;
		char path[MAX_PATH];

		if (argument != NULL)
		{
			parseFlagsAndPath(argument, &showAll, &classify, &classAll, path);
		}
		else if (argument != NULL && argument[0] == '~')
		{
			// Get the user's home directory
			char homeDir[MAX_PATH];
			if (GetEnvironmentVariableA("USERPROFILE", homeDir, MAX_PATH) > 0)
			{

				// Concatenate the home directory with the remaining path
				char newPath[MAX_PATH];
				snprintf(newPath, MAX_PATH, "%s%s", homeDir, argument + 1); // Skip the '~' character
				// Call ls with the new path
				ls(newPath, showAll, classify, classAll);
				return 0;
			}
			else
			{
				fprintf(stderr, "Error: Unable to get user's home directory\n");
				return 1;
			}
		}
		else
		{
			_getcwd(path, MAX_PATH);
		}

		ls(path, showAll, classify, classAll);
	}
	else if (strcmp(command, "cat") == 0) {
		cat(argument);
	}
	else if (strcmp(command, "cd") == 0)
	{
		cd(argument);
	}

	return 0; // Or any other appropriate return value
}

