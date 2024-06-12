/**
  * @file  echo.c
  * @brief Implementation of the echo function.
  */

#include "../Header Files/echo.h"

// Print the argument to the console
void echo(const char* argument)
{
    // Dealing with empty string or NULL pointer
    if (argument == NULL || *argument == '\0')
    {
        printf("\n");
        return;
    }

    // Parse flags
    bool escape = false; // Flag for -e option (enable interpretation of backslash escapes)
    bool no_new_line = false; // Flag for -n option (no newline)
    bool showE = false; // Flag for -E option (disable interpretation of backslash escapes)
    bool flags_processed = false;

    // Process flags
    while (*argument == '-' && !flags_processed)
    {
        argument++; // Skip '-'
        while (*argument != '\0' && *argument != ' ')
        {
            switch (*argument)
            {
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
        if (*argument == '\0' || *argument != '-')
        {
            flags_processed = true;
        }
    }

    // Check if the text is enclosed in double quotes
    bool in_quotes = false;
    if (*argument == '"')
    {
        const char* end_quote = strchr(argument + 1, '"');
        if (end_quote != NULL)
        {
            in_quotes = true;
            argument++; // Skip the initial double quote
        }
    }

    // Process and print the argument text
    while (*argument != '\0')
    {
        if (in_quotes && *argument == '"')
        {
            // End of quoted text
            in_quotes = false;
            argument++; // Skip the closing double quote
            continue;
        }
        else if (escape && *argument == '\\')
        {
            argument++;
            switch (*argument)
            {
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
        else
        {
            putchar(*argument);
        }
        argument++;
    }

    // Print newline if -n flag is not set
    if (!no_new_line)
    {
        putchar('\n');
    }
}

// Print the argument to a file
void echoFile(const char* argument)
{
    // Extracting filename after the '>' operand
    const char* ptr = argument;
    while (*ptr != '\0' && *ptr != '>')
    {
        ptr++;
    }

    // Move past '>'
    ptr++;
    while (*ptr != '\0' && (*ptr == ' ' || *ptr == '\t'))
    {
        ptr++; // Skip spaces and tabs
    }

    const char* filename = ptr;

    // Opening file for writing
    FILE* file = fopen(filename, "w");
    if (file == NULL)
    {
        printf("Error: Unable to open file %s for writing.\n", filename);
        return;
    }

    // Writing content to the file
    // Skip double quotes if present
    if (*argument == '\"')
    {
        argument++;
        while (*argument != '\"' && *argument != '\0')
        {
            fprintf(file, "%c", *argument);
            argument++;
        }
    }
    else
    {
        // Print the argument till the > operand
        while (*argument != '>' && *argument != '\0')
        {
            fprintf(file, "%c", *argument);
            argument++;
        }
    }

    // Closing the file
    fclose(file);
}
