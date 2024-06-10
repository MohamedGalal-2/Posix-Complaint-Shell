#include <windows.h>
#include "../Header Files/cd.h"

// Change to the user's home directory
void changeToHomeDirectory()
{
    char homeDir[MAX_PATH];
    // Get the user's home directory from the environment variable
    if (GetEnvironmentVariableA("USERPROFILE", homeDir, MAX_PATH) > 0)
    {
        // Attempt to change the directory to the home directory
        if (!SetCurrentDirectoryA(homeDir))
        {
            fprintf(stderr, "Error: Unable to change directory to %s\n", homeDir);
        }
    }
    else
    {
        fprintf(stderr, "Error: Unable to get user's home directory\n");
    }
}

// Replace tilde with the user's home directory
bool processPathWithTilde(char* path)
{
    char* tildePos = strchr(path, '~');
    char homeDir[MAX_PATH];

    // Get the user's home directory from the environment variable
    if (GetEnvironmentVariableA("USERPROFILE", homeDir, MAX_PATH) > 0)
    {
        // Calculate the new path length
        int newPathLen = strlen(homeDir) + strlen(tildePos + 1);
        if (newPathLen >= MAX_PATH)
        {
            fprintf(stderr, "Error: New path exceeds maximum length\n");
            return false;
        }

        // Construct the new path
        char newPath[MAX_PATH];
        strncpy(newPath, path, tildePos - path);
        strcpy(newPath + (tildePos - path), homeDir);
        strcat(newPath, tildePos + 1);
        strcpy(path, newPath);

        return true;
    }
    else
    {
        fprintf(stderr, "Error: Unable to get user's home directory\n");
        return false;
    }
}

// Strip trailing double quote from the path if present
void stripTrailingQuote(char* path)
{
    int len = strlen(path);
    if (path[len - 1] == '"')
    {
        path[len - 1] = '\0';
    }
}

// Change directory command implementation
void cd(char* path)
{
    // If path is NULL or empty, change to the user's home directory
    if (path == NULL || *path == '\0')
    {
        changeToHomeDirectory();
        return;
    }

    // Replace double slashes with single slashes
    for (int i = 0; path[i] != '\0'; ++i)
    {
        if (path[i] == '\\' && path[i + 1] == '\\')
        {
            path[i] = '/';
        }
    }

    // Replace forward slashes with backslashes
    for (int i = 0; path[i] != '\0'; ++i)
	{
		if (path[i] == '/')
		{
			path[i] = '\\';
		}
	}

    char* currentDir = (char*)malloc(MAX_PATH);
    if (currentDir != NULL)
    {
        _getcwd(currentDir, MAX_PATH);
    }

    // Check if the path starts with "-L" (follow symbolic link)
    bool followLink = false;
    if (strncmp(path, "-L", 2) == 0)
    {
        followLink = true;
        path += 2;
        while (*path == ' ') path++; // Remove leading spaces
    }

    // Check if the path is enclosed in double quotes
    bool quoted = false;
    if (*path == '"')
    {
        quoted = true;
        path++;
    }

    trimWhitespace(path);

    // Process path if it contains a tilde
    if (strchr(path, '~') != NULL)
    {
        if (!processPathWithTilde(path))
        {
            return;
        }
    }

    // Strip trailing double quote if present
    stripTrailingQuote(path);

    // Check if the path has a slash at the end of it
    while (path[strlen(path) - 1] == '\\')
    {
        path[strlen(path) - 1] = '\0';
    }

    // Change to the provided directory only if it's not the current directory
    if (!strcmp(currentDir, path))
    {
		return;
    }
    else if (!SetCurrentDirectoryA(path))
    {
        printf("%s\n", path);
        fprintf(stderr, "Error: Unable to change directory to %s\n", path);
    }
}
