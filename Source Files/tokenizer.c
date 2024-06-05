/**
  * @file  tokenizer.c
  * @brief Function definitions for tokenizing input strings.
  */

#include "../Header Files/tokenizer.h"

/* Function Definition Section */

/**
  * @brief  Tokenizes an input string and stores the tokens in an array.
  * @param  input The input string to tokenize.
  * @param  tokens An array to store the tokens.
  * @param  tokenCount A pointer to an integer to store the number of tokens.
  * @param  maxTokens The maximum number of tokens the array can hold.
  * @return void
  * @note   This function tokenizes the input string based on space and newline characters
  *         and stores the tokens in the provided array. It null-terminates the array and
  *         updates the token count accordingly.
  */
void tokenizeInput(char* input, char** tokens, int* tokenCount, int maxTokens)
{
    int in_quotes = 0; // Flag to track if currently inside double quotes
    int count = 0; // Counter for tokens
    char* token_start = input; // Pointer to the start of the current token
    char* p = input; // Pointer to iterate through the input string

    // Iterate through the input string
    while (*p != '\0' && count < maxTokens - 1)
    {
        // If current character is a space or newline
        if ((*p == ' ' || *p == '\n') && !in_quotes)
        {
            *p = '\0'; // Replace space or newline with null terminator

            // If the token is not empty, add it to the tokens array
            if (token_start != p)
            {
                tokens[count++] = _strdup(token_start);
                if (tokens[count - 1] == NULL)
                {
                    // Memory allocation failed, free allocated tokens and return
                    for (int i = 0; i < count - 1; i++)
                    {
                        free(tokens[i]);
                    }
                    return;
                }
            }

            // Move to the next token
            token_start = p + 1;
        }
        // If current character is a double quote
        else if (*p == '"')
        {
            in_quotes = !in_quotes; // Toggle the in_quotes flag
            *p = '\0';              // Replace double quote with null terminator

            // If the token is not empty, add it to the tokens array
            if (token_start != p)
            {
                tokens[count++] = _strdup(token_start);
                if (tokens[count - 1] == NULL)
                {
                    // Memory allocation failed, free allocated tokens and return
                    for (int i = 0; i < count - 1; i++)
                    {
                        free(tokens[i]);
                    }
                    return;
                }
            }

            // Move to the next token
            token_start = p + 1;
        }
        p++; // Move to the next character
    }

    // Add the last token if it's not empty
    if (token_start != p)
    {
        tokens[count++] = _strdup(token_start);
        if (tokens[count - 1] == NULL)
        {
            // Memory allocation failed, free allocated tokens and return
            for (int i = 0; i < count - 1; i++)
            {
                free(tokens[i]);
            }
            return;
        }
    }

    // Null-terminate the tokens array
    tokens[count] = NULL;

    *tokenCount = count; // Update the token count
}

/**
  * @brief  Frees the memory allocated for the tokens array.
  * @param  tokens An array of tokens to free.
  * @param  tokenCount The number of tokens in the array.
  * @return void
  * @note   This function frees the memory allocated for each token in the array
  *         and then frees the array itself.
  */
void freeTokens(char** tokens, int tokenCount)
{
    for (int i = 0; i < tokenCount; i++)
    {
        free(tokens[i]); // Free memory for each token
    }
    free(tokens); // Free memory for the array
}