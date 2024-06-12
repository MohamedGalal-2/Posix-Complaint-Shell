/**
  * @file  pwd.h
  * @brief Header file for the pwd function.
  */

#ifndef PWD_H
#define PWD_H

/* Includes Section */
#include <stdio.h>
#include <direct.h>
#include <Windows.h>

/* Functions Prototype Section */

/**
  * @brief  Prints the current working directory.
  * @param  showLogical: If true, shows the logical path.
  * @param  showPhysical: If true, shows the physical path.
  */
void pwd(int showLogical, int showPhysical);

#endif // PWD_H
