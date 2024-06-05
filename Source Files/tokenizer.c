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
    char* token = strtok(input, " \n"); // Tokenize based on space and newline
    int count = 0;

    while (token != NULL && count < maxTokens - 1)
    {
        tokens[count] = _strdup(token); // Duplicate token and store in array
        if (tokens[count] == NULL)
        {
            return; // Return if memory allocation fails
        }

        count++;
        token = strtok(NULL, " \n");
    }

    // Null-terminate the array
    tokens[count] = NULL;

    *tokenCount = count;
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