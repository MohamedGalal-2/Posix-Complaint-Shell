/**
  * @file  pwd.c
  * @brief Implementation of the pwd function.
  */

#include "../Header Files/pwd.h"

// Function to print the current working directory
void pwd(int showLogical, int showPhysical) 
{
    char cwd[1024];
    if (showLogical && !showPhysical) 
    {
        _getcwd(cwd, 1024);
    } else if (showPhysical && !showLogical) 
    {
        _fullpath(cwd, ".", 1024);
    } else 
    {
        // Both flags are either not provided or provided together
        _getcwd(cwd, 1024);
    }
    printf("%s\n", cwd);
}
