#include "../Header Files/mkdir.h"

// Helper function to remove double quotes from the path
void remove_quotes(char* str) 
{
    char* read = str, * write = str;

    if (str == NULL || read == NULL || write == NULL) 
	{
		return;
	}

    while (*read) 
    {
        if (*read != '\"') {
            *write++ = *read;
        }
        read++;
    }
    *write = '\0';
}

// Function to create a directory at the specified path
int _make_Dir(const char* path)
{
    char dir_path[MAX_PATH] = { 0 };
    char temp_path[MAX_PATH] = { 0 };
    char* folder_name = NULL;
    char quoted_path[MAX_PATH] = { 0 };
    int i = 0;

    if (path == NULL)
    {
		return -1;
    }

    // Check if the path is empty or consists only of spaces
    for (i = 0; path[i] != '\0'; i++) 
    {
        if (!isspace(path[i])) 
        {
            break; // Exit loop if non-space character is found
        }
    }
    if (path[i] == '\0') 
    {
        return -1;
    }

    // Copy the input path to a modifiable string
    strncpy(temp_path, path, MAX_PATH - 1);

    // Remove double quotes from the path
    remove_quotes(temp_path);

    trimWhitespace(temp_path);

    // Check if the path contains a backslash or forward slash
    folder_name = strrchr(temp_path, '\\');
    if (!folder_name) 
    {
        folder_name = strrchr(temp_path, '/');
    }

    if (folder_name != NULL) 
    {
        *folder_name = '\0';  // Separate the path from the folder name
        folder_name++;        // Move to the folder name part
        strncpy(dir_path, temp_path, MAX_PATH - 1); // Copy the directory path
    }
    else 
    {
        // If no path is provided, use the current directory
        if (_getcwd(dir_path, sizeof(dir_path)) == NULL) 
        {
            fprintf(stderr, "Error: Unable to get current working directory.\n");
            return -1;
        }
        folder_name = temp_path; // The entire temp_path is the folder name

        // Include the dir_path in double quotes to handle spaces in the path
        snprintf(quoted_path, MAX_PATH, "\"%s\"", temp_path);
    }

    // Create the path if it doesn't exist
    if (!*dir_path) 
    {
        if (!CreateDirectoryA(dir_path, NULL)) 
        {
            DWORD error = GetLastError();
            if (error != ERROR_ALREADY_EXISTS) 
            {
                switch (error) {
                case ERROR_PATH_NOT_FOUND:
                    fprintf(stderr, "Error: A component of the path does not exist.\n");
                    break;
                case ERROR_ACCESS_DENIED:
                    fprintf(stderr, "Error: Permission denied.\n");
                    break;
                case ERROR_FILENAME_EXCED_RANGE:
                    fprintf(stderr, "Error: Pathname is too long.\n");
                    break;
                case ERROR_DIRECTORY:
                    fprintf(stderr, "Error: The specified path is invalid.\n");
                    break;
                case ERROR_WRITE_PROTECT:
                    fprintf(stderr, "Error: The disk is write-protected.\n");
                    break;
                case ERROR_DISK_FULL:
                    fprintf(stderr, "Error: The disk is full.\n");
                    break;
                default:
                    fprintf(stderr, "Error: Unable to create directory (error code %lu).\n", error);
                }
                return -1; // Indicate failure
            }
        }
    }

    // Append folder name to the directory path
    if (folder_name) 
    {
        snprintf(dir_path + strlen(dir_path), MAX_PATH - strlen(dir_path), "\\%s", folder_name);

        // Include the dir_path in double quotes to handle spaces in the path
        snprintf(quoted_path, MAX_PATH, "\"%s\"", dir_path);
    }

    // Create the final directory
    if (!CreateDirectoryA(dir_path, NULL))
    {
        // If the directory creation fails, handle various error conditions
        DWORD error = GetLastError();
        switch (error) 
        {
        case ERROR_ALREADY_EXISTS:
            fprintf(stderr, "Error: Directory already exists.\n");
            break;
        case ERROR_PATH_NOT_FOUND:
            fprintf(stderr, "Error: A component of the path does not exist.\n");
            break;
        case ERROR_ACCESS_DENIED:
            fprintf(stderr, "Error: Permission denied.\n");
            break;
        case ERROR_FILENAME_EXCED_RANGE:
            fprintf(stderr, "Error: Pathname is too long.\n");
            break;
        case ERROR_DIRECTORY:
            fprintf(stderr, "Error: The specified path is invalid.\n");
            break;
        case ERROR_WRITE_PROTECT:
            fprintf(stderr, "Error: The disk is write-protected.\n");
            break;
        case ERROR_DISK_FULL:
            fprintf(stderr, "Error: The disk is full.\n");
            break;
        default:
            fprintf(stderr, "Error: Unable to create directory (error code %lu).\n", error);
        }
        return -1; // Indicate failure
    }

    // Directory created successfully
    return 0; // Indicate success
}
