/**
  * @file  type.c
  * @brief Implementation of the type function.
  */

#include "../Header FIles/type.h"

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
        if (strcmp(currentCommand, "rmdir") == 0 || strcmp(currentCommand, "mkdir") == 0 || strcmp(currentCommand, "cat") == 0 || strcmp(currentCommand, "ls") == 0 || strcmp(currentCommand, "echo") == 0 || strcmp(currentCommand, "type") == 0 || strcmp(currentCommand, "cd") == 0 || strcmp(currentCommand, "pwd") == 0 || strcmp(currentCommand, "help") == 0 || strcmp(currentCommand, "exit") == 0)
        {
            red();
            printf("%s", currentCommand);
            reset();
            printf(" is a shell ");
            red();
            printf("built-in\n");
            reset();
        } else 
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
