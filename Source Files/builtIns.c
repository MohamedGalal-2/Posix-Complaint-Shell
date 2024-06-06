/* Includes Section */
#include "..\Header Files\builtIns.h"

/* Global Variables Section */
int followLinks = 1;			// Default behavior is to follow symbolic links

/*Functions Definition Section */

void cd(char* path) {
	// Check if the path is provided
	if (path == NULL || *path == '\0') {
		// Change to user's home directory
		char homeDir[MAX_PATH];
		if (GetEnvironmentVariableA("USERPROFILE", homeDir, MAX_PATH) > 0) {
			// Change directory to the user's home directory
			if (!SetCurrentDirectoryA(homeDir)) {
				fprintf(stderr, "Error: Unable to change directory to %s\n", homeDir);
			}
			else {
				printf("Changed directory to %s\n", homeDir);
			}
		}
		else {
			fprintf(stderr, "Error: Unable to get user's home directory\n");
		}
		return;
	}

	// Check if the path starts with "-L"
	bool followLink = false;
	if (strncmp(path, "-L", 2) == 0) {
		followLink = true;
		// Move past the "-L" argument
		path += 2;
		while (*path == ' ') path++; // Remove leading spaces
	}

	// Check if the path is enclosed in double quotes
	bool quoted = false;
	if (*path == '"') {
		quoted = true;
		// Move past the opening double quote
		path++;
	}

	// Check if the path starts with "~"
	char* tildePos = strchr(path, '~');
	if (tildePos != NULL && (!quoted || tildePos < strchr(path, '"'))) {
		// Replace the "~" with the user's home directory path
		char homeDir[MAX_PATH];
		if (GetEnvironmentVariableA("USERPROFILE", homeDir, MAX_PATH) > 0) {
			// Calculate the new path length
			int newPathLen = strlen(homeDir) + strlen(tildePos + 1);
			if (newPathLen >= MAX_PATH) {
				fprintf(stderr, "Error: New path exceeds maximum length\n");
				return;
			}
			// Construct the new path
			char newPath[MAX_PATH];
			strncpy(newPath, path, tildePos - path);
			strcpy(newPath + (tildePos - path), homeDir);
			strcat(newPath, tildePos + 1);
			strcpy(path, newPath);
		}
		else {
			fprintf(stderr, "Error: Unable to get user's home directory\n");
			return;
		}
	}

	// Strip trailing double quote if present
	int len = strlen(path);
	if (quoted && path[len - 1] == '"') {
		path[len - 1] = '\0';
	}

	// Check if the path is a symbolic link
	if (followLink) {
		printf("Debug: Attempting to resolve symbolic link %s\n", path);
		// Resolve symbolic link
		char targetPath[MAX_PATH];
		DWORD length = GetFullPathNameA(path, MAX_PATH, targetPath, NULL);
		if (length == 0 || length >= MAX_PATH) {
			fprintf(stderr, "Error: Unable to resolve symbolic link %s\n", path);
			return;
		}

		printf("Debug: Resolved symbolic link %s to target %s\n", path, targetPath);

		WIN32_FIND_DATAA findFileData;
		HANDLE hFind = FindFirstFileA(targetPath, &findFileData);
		if (hFind == INVALID_HANDLE_VALUE) {
			fprintf(stderr, "Error: Unable to find file %s\n", targetPath);
			return;
		}
		FindClose(hFind);

		if ((findFileData.dwFileAttributes & FILE_ATTRIBUTE_REPARSE_POINT) != 0) {
			// Symbolic link detected, get the target path
			CHAR target[MAX_PATH];
			DWORD dwResult = GetFinalPathNameByHandleA(hFind, target, MAX_PATH, FILE_NAME_NORMALIZED);
			if (dwResult == 0 || dwResult >= MAX_PATH) {
				fprintf(stderr, "Error: Unable to resolve symbolic link %s\n", path);
				return;
			}
			else {
				printf("Debug: Resolved symbolic link %s to target %s\n", path, target);
			}

			// Change directory to the target
			if (!SetCurrentDirectoryA(target)) {
				fprintf(stderr, "Error: Unable to change directory to %s\n", target);
			}
			else {
				printf("Changed directory to %s\n", target);
			}
		}
		else {
			// Not a symbolic link, change directory to the original path
			if (!SetCurrentDirectoryA(path)) {
				fprintf(stderr, "Error: Unable to change directory to %s\n", path);
			}
			else {
				printf("Changed directory to %s\n", path);
			}
		}
	}
	else {
		// Change directory to the provided path directly
		if (!SetCurrentDirectoryA(path)) {
			fprintf(stderr, "Error: Unable to change directory to %s\n", path);
		}
		else {
			printf("Changed directory to %s\n", path);
		}
	}
}

void cat(const char* argument) {
	char* input_file = NULL;
	char* output_file = NULL;
	FILE* input_fp = NULL;
	FILE* output_fp = NULL;

	// Find the position of the output redirection symbol '>'
	char* output_symbol = strchr(argument, '>');
	if (output_symbol != NULL) {
		// Extract input file name
		size_t input_len = output_symbol - argument;
		input_file = (char*)malloc((input_len + 1) * sizeof(char));
		strncpy(input_file, argument, input_len);
		input_file[input_len] = '\0';

		// Extract output file name
		output_file = _strdup(output_symbol + 1); // Skip '>'
		trimWhitespace(output_file);
	}
	else {
		input_file = _strdup(argument);
	}

	// Open input file for reading
	input_fp = fopen(input_file, "r");
	if (input_fp == NULL) {
		fprintf(stderr, "Error: Unable to open input file %s\n", input_file);
		goto cleanup;
	}

	// Open output file for writing if provided
	if (output_file != NULL) {
		output_fp = fopen(output_file, "w");
		if (output_fp == NULL) {
			fprintf(stderr, "Error: Unable to open output file %s\n", output_file);
			goto cleanup;
		}
	}

	// Read from input file and write to output file if provided, else print to stdout
	char buffer[1024];
	while (fgets(buffer, sizeof(buffer), input_fp) != NULL) {
		if (output_fp != NULL) {
			fputs(buffer, output_fp);
		}
		else {
			printf("%s", buffer);
		}
	}

cleanup:
	// Close files
	if (input_fp != NULL) {
		fclose(input_fp);
	}
	if (output_fp != NULL) {
		fclose(output_fp);
	}

	// Free memory
	free(input_file);
	free(output_file);
}

void ls(const char* path, int showAll, int classify, int classAll) {
	// Check if the path is NULL or empty
	if (path == NULL || path[0] == '\0') {
		// Use the current directory if no path is provided
		path = ".";
	}
	else if (path[0] == '~') {
		// Get the user's home directory
		char homeDir[MAX_PATH];
		if (GetEnvironmentVariableA("USERPROFILE", homeDir, MAX_PATH) > 0) {
			// Concatenate the home directory with the remaining path
			char newPath[MAX_PATH];
			snprintf(newPath, MAX_PATH, "%s%s", homeDir, path + 1); // Skip the '~' character
			// Call ls with the new path
			ls(newPath, showAll, classify, classAll);
			return;
		}
		else {
			fprintf(stderr, "Error: Unable to get user's home directory\n");
			return;
		}
	}

	// Construct the search path
	char searchPath[MAX_PATH + 1];
	snprintf(searchPath, sizeof(searchPath), "%s\\*.*", path);

	// Use _findfirst and _findnext to iterate through the directory contents
	struct _finddata_t fileinfo;
	intptr_t handle = _findfirst(searchPath, &fileinfo);

	if (handle == -1) {
		fprintf(stderr, "Unable to list directory contents. Error Code: %d\n", errno);
		return;
	}

	do {
		if (classAll)
		{
			// print all the files and add a slash for directories
			printf("%s", fileinfo.name);
			if (fileinfo.attrib & _A_SUBDIR)
			{
				printf("/");
			}
			else
			{
				printf("*");
			}

		}
		else if(!showAll && (fileinfo.name[0] == '.')) 
		{
			continue;
		}
		else if (classify) 
		{
			printf("%s", fileinfo.name);
			if (fileinfo.attrib & _A_SUBDIR) {
				printf("/");
			}
			else {
				printf("*");
			}
			// Print only the file name
		}
		else 
		{
			printf("%s", fileinfo.name);
		}

		printf("\n");
	} while (_findnext(handle, &fileinfo) == 0);

	_findclose(handle);
}

int parseFlagsAndPath(char* argument, int* showAll, int* classify, int* classAll, char* path) {
	*showAll = 0;
	*classify = 0;
	*classAll = 0;
	path[0] = '\0';

	char* token = strtok(argument, " ");
	while (token != NULL) 
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

void trimWhitespace(char* str) 
{
	// Trim leading whitespace
	char* start = str;
	while (*start && isspace((unsigned char)*start)) {
		start++;
	}

	// Move the non-whitespace part to the beginning of the string
	memmove(str, start, strlen(start) + 1);

	// Trim trailing whitespace
	char* end = str + strlen(str) - 1;
	while (end > str && isspace((unsigned char)*end)) {
		end--;
	}

	// Null-terminate the string at the last non-whitespace character
	*(end + 1) = '\0';
}

bool checkForGreaterThan(const char *input) 
{
	bool inside_quotes = false;

	for (int i = 0; input[i] != '\0'; i++) {
		if (input[i] == '"') {
			inside_quotes = !inside_quotes;
		}
		else if (input[i] == '>' && !inside_quotes) {
			return true; // '>' operand found outside of double quotes
		}
	}

	return false; // '>' operand not found outside of double quotes
}

void echoFile(const char *argument) 
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
		printf("ls [-af] [file ...]\n");
		printf("    List directory contents.\n");
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
		return;
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
		else {
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

	else {
		return 0;
	}
}