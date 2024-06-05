/**
  * @file  tokenizer.h
  * @brief Header file for tokenizing input strings.
  */

/*File Guard*/
#pragma once
#ifndef _TOKENIZER_H
#define _TOKENIZER_H

/* Includes Section */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Functions Prototype Section */

/**
  * @brief  Tokenizes the input string and stores the tokens in the tokens array.
  * @param  input: The input string to be tokenized.
  * @param  tokens: The array of strings to store the tokens.
  * @param  tokenCount: The number of tokens in the input string.
  * @param  maxTokens: The maximum number of tokens that can be stored in the tokens array.
  * @return void
  * @note   This function tokenizes the input string based on spaces and stores the tokens in the tokens array.
  */
void tokenizeInput(char* input, char** tokens, int* tokenCount, int maxTokens);

/**
  * @brief  Frees the memory allocated for the tokens array.
  * @param  tokens: The array of strings to be freed.
  * @param  tokenCount: The number of tokens in the array.
  * @return void
  * @note   This function frees the memory allocated for each token in the tokens array and then frees the array itself.
  */
void freeTokens(char** tokens, int tokenCount);

#endif // _TOKENIZER_H