/**
  * @file  runFile.c
  * @brief Implementation of the runFile function.
  */

#include "../Header Files/runFile.h"

void runFile(const char* fileName) 
{
    // Use system command to execute the file
    int result = system(fileName);

    // Check the result of the system command
    if (result == -1) 
    {
        // Failed to execute the file
        fprintf(stderr, "Failed to run file: %s\n", fileName);
    } else 
    {
        // File executed successfully
    }
}
