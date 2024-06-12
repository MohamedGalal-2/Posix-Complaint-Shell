#include "../Header Files/ls.h"

// Function to trim white spaces till the first character found
char* trim(const char* str)
{
    if (str == NULL)
	{
		return NULL;
	}

    char* temp = (char*)str;

    // Skip leading white spaces
	while (isspace(*temp))
	{
        temp++;
	}

	return temp;
}

// Funciton to parse the argument and flags
int parseFlagsAndPath(char* argument, int* showAll, int* classify, int* classAll, char* path)
{
    *showAll = 0;
    *classify = 0;
    *classAll = 0;
    path[0] = '\0';
    char tempArg[1024];
    strcpy(tempArg, argument);
    int flag = 0;

    // Trim the leading and trailing spaces
    trimWhitespace(argument);

    if (argument == NULL || strlen(argument) == 0)
    {
        return 0;
    }

    char* token = strtok(argument, "");
    trimWhitespace(token);
    token = strtok(token, " ");

    // Check if flags are provided
    while (token != NULL && token[0] == '-')
    {
        if (strcmp(token, "-af") == 0)
        {
            *classAll = 1;
            flag = 1;
        }
        else if (strcmp(token, "-a") == 0)
        {
            *showAll = 1;
            flag = 1;
        }
        else if (strcmp(token, "-f") == 0)
        {
            *classify = 1;
            flag = 1;
        }

        // Get the path after the flag
        token = strtok(NULL, "");
    }

    int i = 0;
    if (flag == 1)
    {
        // Remove the flags from the argument
        while (tempArg[i] != ' ' && tempArg[i] != '\0')
		{
			i++;
		}

        for (int j = 0; tempArg[i] != '\0'; i++, j++)
        {
            tempArg[j] = tempArg[i];
        }
    }
    else
    {
		token = tempArg;
	}

    trimWhitespace(token);

    // Remove double quotes from the path and trim white spaces
    remove_quotes(token);
    trimWhitespace(token);

    if (token == NULL || strlen(token) == 0)
	{
		return 0;
	}

    // Add double quotes to the path if it contains spaces
    if (strchr(token, ' ') != NULL)
	{
		snprintf(path, MAX_PATH, "\"%s\"", token);
	}
	else
	{
		strcpy(path, token);
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

// Perform the ls operation
void ls(const char* path, int showAll, int classify, int classAll)
{
    // Check if the path is NULL or empty
    if (path == NULL || path[0] == '\0')
    {
        // Use the current directory if no path is provided
        path = ".";
    }

    char trimmedPath[MAX_PATH];
    strcpy(trimmedPath, trim(path));

    // Process path if it contains a tilde
    if (trimmedPath[0] == '~')
    {
        // Get the user's home directory
        char homeDir[MAX_PATH];
        if (GetEnvironmentVariableA("USERPROFILE", homeDir, MAX_PATH) > 0)
        {
            // Concatenate the home directory with the remaining path
            char newPath[MAX_PATH];
            snprintf(newPath, MAX_PATH, "%s%s", homeDir, trimmedPath + 1); // Skip the '~' character
            // Call ls with the new path
            ls(newPath, showAll, classify, classAll);
            return;
        }
        else
        {
            fprintf(stderr, "Error: Unable to get user's home directory\n");
            return;
        }
    }

    // Extract the full path if it's enclosed in double quotes
    char extractedPath[MAX_PATH];
    int i = 0;
    int j = 0;

    if (trimmedPath[i] == '"')
    {
        i++; // Skip the opening quote
        while (trimmedPath[i] != '\0' && j < MAX_PATH - 1)
        {
            if (trimmedPath[i] == '"')
            {
                i++; // Skip the closing quote
                break;
            }
            extractedPath[j] = trimmedPath[i];
            i++;
            j++;
        }
        extractedPath[j] = '\0'; // Null-terminate the string
    }
    else
    {
        strncpy(extractedPath, trimmedPath, MAX_PATH);
        extractedPath[MAX_PATH - 1] = '\0'; // Ensure null termination
    }

    // Construct the search path
    char searchPath[MAX_PATH + 1];
    snprintf(searchPath, sizeof(searchPath), "%s\\*.*", extractedPath);

    // Use _findfirst and _findnext to iterate through the directory contents
    struct _finddata_t fileinfo;
    intptr_t handle = _findfirst(searchPath, &fileinfo);

    if (handle == -1)
    {
        fprintf(stderr, "Unable to list directory contents. Error Code: %d\n", errno);
        return;
    }

    do
    {
        if (classAll)
        {
            // Print all the files and add a slash for directories
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
        else if (!showAll && (fileinfo.name[0] == '.'))
        {
            continue;
        }
        else if (classify)
        {
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
        else
        {
            printf("%s", fileinfo.name);
        }

        printf("\n");
    } while (_findnext(handle, &fileinfo) == 0);

    _findclose(handle);
}