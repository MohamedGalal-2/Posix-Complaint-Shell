#include "..\Header Files\builtIns.h"

/* Functions Definition Section */

// Check if the '>' operand is outside of double quotes
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
        else if (input[i] == '>' && !inside_quotes)
        {
            return true; // '>' operand found outside of double quotes
        }
    }

    return false; // '>' operand not found outside of double quotes
}

// Perform the user's command
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
        if (argument != NULL)
        {
            int exitCode = atoi(argument);
            exit(exitCode);
        }
        else
        {
            exit(0);
        }

        // If still running here, exit command didn't exit the process, we'll attempt to exit PowerShell
        system("exit; exit");
        // The first 'exit' command exits the shell, and the second one exits PowerShell
    }
    else if (strcmp(command, "type") == 0)
    {
        type(argument);
    }
    else if (strcmp(command, "pwd") == 0)
    {
        int showLogical = 0;
        int showPhysical = 0;

        // Parse the arguments to check for -L and -P flags
        if (argument != NULL)
        {
            char* token = strtok(argument, " ");
            while (token != NULL)
            {
                if (strcmp(token, "-L") == 0)
                {
                    showLogical = 1;
                }
                else if (strcmp(token, "-P") == 0)
                {
                    showPhysical = 1;
                }
                token = strtok(NULL, " ");
            }
        }

        // Call pwd function with flags
        pwd(showLogical, showPhysical);
    }
    else if (strcmp(command, "ls") == 0)
    {
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

        // Call ls with the path and flags
        ls(path, showAll, classify, classAll);
    }
    else if (strcmp(command, "cat") == 0)
    {
        cat(argument);
    }
    else if (strcmp(command, "mkdir") == 0)
    {
        _make_Dir(argument);
    }
    else if (strcmp(command, "cd") == 0)
    {
        cd(argument);
    }

    return 0; // Or any other appropriate return value
}
