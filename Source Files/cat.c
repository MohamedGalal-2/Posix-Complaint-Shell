#include "../Header Files/cat.h"

// Reads the content of the input file and writes to the output file or prints to stdout
void cat(const char* argument) 
{
    char* input_file = NULL;
    char* output_file = NULL;
    char* output_symbol = NULL;
    FILE* input_fp = NULL;
    FILE* output_fp = NULL;

    // Check for null argument
    if (argument == NULL) 
    {
        return;
    }

    // Check for empty argument
    if (argument[0] == '\0') 
	{
        return;
	}

    // Find the position of the output redirection symbol '>'
    output_symbol = strchr(argument, '>');
    if (output_symbol != NULL) 
    {
        // Extract input file name
        size_t input_len = output_symbol - argument;
        input_file = (char*)malloc((input_len + 1) * sizeof(char));
        if (input_file == NULL) 
        {
            fprintf(stderr, "Error: Memory allocation failed\n");
            return;
        }
        strncpy(input_file, argument, input_len);
        input_file[input_len] = '\0';
        trimWhitespace(input_file);

        // Extract output file name
        output_file = _strdup(output_symbol + 1); // Skip '>'
        if (output_file == NULL) 
        {
            fprintf(stderr, "Error: Memory allocation failed\n");
            free(input_file);
            return;
        }
        trimWhitespace(output_file);
    }
    else 
    {
        input_file = _strdup(argument);
        if (input_file == NULL) 
        {
            fprintf(stderr, "Error: Memory allocation failed\n");
            return;
        }
        trimWhitespace(input_file);
    }

    // Open input file for reading
    input_fp = fopen(input_file, "r");
    if (input_fp == NULL) 
    {
        fprintf(stderr, "Error: Unable to open input file %s\n", input_file);
        goto cleanup;
    }

    // Open output file for writing if provided, create if it doesn't exist
    if (output_file != NULL) 
    {
        output_fp = fopen(output_file, "w");
        if (output_fp == NULL) 
        {
            fprintf(stderr, "Error: Unable to create or open output file %s\n", output_file);
            goto cleanup;
        }
    }

    // Read from input file and write to output file if provided, else print to stdout
    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), input_fp) != NULL) 
    {
        if (output_fp != NULL) 
        {
            fputs(buffer, output_fp);
        }
        else 
        {
            printf("%s", buffer);
        }
    }

    // Print a new line after the file content
    if (output_fp == NULL) 
    {
        printf("\n");
    }

cleanup:
    // Close files
    if (input_fp != NULL) 
    {
        fclose(input_fp);
    }
    if (output_fp != NULL) 
    {
        fclose(output_fp);
    }

    // Free memory
    free(input_file);
    free(output_file);
}
