/**
 * @file grep.c
 * @brief Implementation of the grep function and related utilities.
 */

#include "../Header Files/grep.h"

// Helper function to convert a string to lowercase
void to_lowercase(char* str)
{
    for (int i = 0; str[i]; i++)
    {
        str[i] = tolower(str[i]);
    }
}

// Function to check if a word boundary is present
bool is_word_boundary(const char* str, int pos, int len)
{
    if (pos == 0 || isspace(str[pos - 1]) || ispunct(str[pos - 1]))
    {
        if (pos + len == strlen(str) || isspace(str[pos + len]) || ispunct(str[pos + len]))
        {
            return true;
        }
    }
    return false;
}

// Function to search for a string in a file and print matching lines
int grep(const char* filename, const char* search_string, bool ignore_case, bool invert_match, bool count, bool list_files, bool line_number, bool word_regexp, bool only_matching)
{
    // Check for NULL filename or search_string
    if (filename == NULL || search_string == NULL)
    {
        return -1;
    }

    // Open the file for reading
    FILE* file = fopen(filename, "r");
    if (file == NULL)
    {
        perror("Error opening file");
        return -1;
    }

    char line[1024];            // Buffer to hold each line read from file
    int match_count = 0;        // Counter for number of matches found
    char search_str[1024];      // Buffer to hold the search string
    strncpy(search_str, search_string, sizeof(search_str) - 1);
    search_str[sizeof(search_str) - 1] = '\0';

    // Convert search string to lowercase if ignore_case flag is set
    if (ignore_case)
    {
        to_lowercase(search_str);
    }

    int line_num = 0;           // Line number counter
    while (fgets(line, sizeof(line), file) != NULL)
    {
        line_num++;
        char line_copy[1024];   // Copy of the line to work with
        strncpy(line_copy, line, sizeof(line_copy) - 1);
        line_copy[sizeof(line_copy) - 1] = '\0';

        // Convert line to lowercase if ignore_case flag is set
        if (ignore_case)
        {
            to_lowercase(line_copy);
        }

        char* match = strstr(line_copy, search_str);   // Pointer to matched substring
        bool found_match = false;                      // Flag to indicate if match found

        // Search for multiple occurrences of the search string in the line
        while (match != NULL)
        {
            // Check for word boundary if word_regexp flag is set
            if (word_regexp && !is_word_boundary(line_copy, match - line_copy, strlen(search_str)))
            {
                match = strstr(match + 1, search_str);  // Find next occurrence
                continue;                              // Skip this match if not whole word
            }

            found_match = true;    // Set found_match flag to true

            // Print only the matching substring if only_matching flag is set
            if (only_matching)
            {
                // Print the line up to the match
                printf("%.*s", (int)(match - line_copy), line_copy);

                // Print the matching substring in red
                printf(ANSI_COLOR_RED "%.*s" ANSI_COLOR_RESET, (int)strlen(search_str), match);

                // Print the rest of the line after the match
                printf("%s", match + strlen(search_str));
            }

            match = strstr(match + 1, search_str);  // Find next occurrence
        }

        // Invert the found_match flag if invert_match flag is set
        if (invert_match)
        {
            found_match = !found_match;
        }

        // If match found, increment match_count and print the line if needed
        if (found_match)
        {
            match_count++;

            // Print line number if line_number flag is set
            if (!count && !list_files && !only_matching)
            {
                if (line_number)
                {
                    green();
                    printf("%d:", line_num);
                    reset();
                }
                printf("%s", line);
            }
        }
    }

    fclose(file);  // Close the file after processing

    // Print match count if count flag is set
    if (count)
    {
        printf("%d\n", match_count);
    }

    // Print filename if list_files flag is set and matches found
    if (list_files && match_count > 0)
    {
        magenta();
        printf("%s\n", filename);
        reset();
    }
    
    if (invert_match || ignore_case)
    {
        printf("\n");
    }

    return match_count;  // Return the total number of matches found
}

// Function to parse the arguments and flags for the grep function
int parseGrepFlagsAndArgs(char* argument, char* search_string, char* filename, bool* ignore_case, bool* invert_match, bool* count, bool* list_files, bool* line_number, bool* word_regexp, bool* only_matching)
{
    // Initialize all flags and output variables
    *ignore_case = false;
    *invert_match = false;
    *count = false;
    *list_files = false;
    *line_number = false;
    *word_regexp = false;
    *only_matching = false;
    search_string[0] = '\0';
    filename[0] = '\0';

    // Tokenize the argument string
    char* token = strtok(argument, " ");
    while (token != NULL)
    {
        if (token[0] == '-')
        {
            // Process flags starting with '-'
            for (int i = 1; token[i] != '\0'; i++)
            {
                switch (token[i])
                {
                case 'i':
                    *ignore_case = true;
                    break;
                case 'v':
                    *invert_match = true;
                    break;
                case 'c':
                    *count = true;
                    break;
                case 'l':
                    *list_files = true;
                    break;
                case 'n':
                    *line_number = true;
                    break;
                case 'w':
                    *word_regexp = true;
                    break;
                case 'o':
                    *only_matching = true;
                    break;
                default:
                    fprintf(stderr, "Unknown flag: -%c\n", token[i]);
                    return -1;
                }
            }
        }
        else
        {
            // Process search string and filename
            if (search_string[0] == '\0')
            {
                strncpy(search_string, token, 1023);
                search_string[1023] = '\0';
            }
            else if (filename[0] == '\0')
            {
                strncpy(filename, token, 1023);
                filename[1023] = '\0';
            }
            else
            {
                fprintf(stderr, "Unexpected argument: %s\n", token);
                return -1;
            }
        }
        token = strtok(NULL, " ");
    }

    // Check if both search_string and filename are provided
    if (search_string[0] == '\0' || filename[0] == '\0')
    {
        fprintf(stderr, "Usage: grep [flags] search_string filename\n");
        return -1;
    }

    return 0;  // Return success
}
