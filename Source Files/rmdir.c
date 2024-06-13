#include "../Header Files/rmdir.h"

// Function to remove a directory at the specified path
int _remove_Dir(const char* path)
{
    char dir_path[MAX_PATH] = { 0 };
    char temp_path[MAX_PATH] = { 0 };
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
    char* folder_name = strrchr(temp_path, '\\');
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
    }

    // Append folder name to the directory path
    if (folder_name) 
    {
        snprintf(dir_path + strlen(dir_path), MAX_PATH - strlen(dir_path), "\\%s", folder_name);
    }

    // Remove the directory
    if (!RemoveDirectoryA(dir_path))
    {
        // If the directory removal fails, handle various error conditions
        DWORD error = GetLastError();
        switch (error) 
        {
        case ERROR_FILE_NOT_FOUND:
            fprintf(stderr, "Error: Directory not found.\n");
            break;
        case ERROR_PATH_NOT_FOUND:
            fprintf(stderr, "Error: A component of the path does not exist.\n");
            break;
        case ERROR_ACCESS_DENIED:
            fprintf(stderr, "Error: Permission denied.\n");
            break;
        case ERROR_SHARING_VIOLATION:
            fprintf(stderr, "Error: The directory is in use by another process.\n");
            break;
        case ERROR_DIR_NOT_EMPTY:
            fprintf(stderr, "Error: The directory is not empty.\n");
            break;
        case ERROR_WRITE_PROTECT:
            fprintf(stderr, "Error: The disk is write-protected.\n");
            break;
        default:
            fprintf(stderr, "Error: Unable to remove directory (error code %lu).\n", error);
        }
        return -1; // Indicate failure
    }

    // Directory removed successfully
    return 0; // Indicate success
}
