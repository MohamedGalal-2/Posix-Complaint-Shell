#ifndef CAT_H
#define CAT_H
#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"

// Function declarations

/**
 * @brief Reads the content of the input file and writes to the output file or prints to stdout.
 *
 * @param argument The input file name with optional output redirection symbol '>'.
 */
void cat(const char* argument);

#endif // CAT_H