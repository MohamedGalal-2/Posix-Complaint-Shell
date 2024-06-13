#include "../Header Files/help.h"
#include <stdio.h>
#include <string.h>

void help(char* command)
{
    if (command == NULL || strlen(command) == 0)
    {
        // Print general help information
        printf("\n");
        printf("Usage: help [command]\n");
        printf("\n");
        printf("This is a POSIX-compliant shell.\n");
        printf("\n");
        printf("These shell commands are built-in. Type `help' to see this list.\n");
        printf("\n");
        printf("cd [-L|[-P [-e]] [-@]] [dir]\n");
        printf("    Change the shell working directory.\n");
        printf("\n");
        printf("exit [n]\n");
        printf("    Exit the shell.\n");
        printf("\n");
        printf("echo [-neE] [arg ...]\n");
        printf("    Write arguments to the standard output.\n");
        printf("\n");
        printf("pwd [-LP]\n");
        printf("    Print the current working directory.\n");
        printf("\n");
        printf("type [-afptP] name [name ...]\n");
        printf("    Indicate how each name would be interpreted if used as a command name.\n");
        printf("\n");
        printf("help [-dms] [pattern ...]\n");
        printf("    Display information about built-in commands.\n");
        printf("\n");
        printf("ls [-af] [file ...]\n");
        printf("    List directory contents.\n");
        printf("\n");
        printf("cat [file] or cat [file] < [file]\n");
        printf("    Concatenate files and print on the standard output.\n");
        printf("\n");
        printf("mkdir [-p] directory ...\n");
        printf("    Create directories.\n");
        printf("\n");
        printf("rmdir directory ...\n");
        printf("    Remove directories.\n");
        printf("\n");
        printf("grep [-ivclnwo] pattern [file ...]\n");
        printf("    Search for patterns in files.\n");
        printf("\n");
        printf("clear\n");
        printf("    Clear the terminal screen.\n");
        printf("\n");
        printf("date <format>\n");
        printf("    Display current date and time.\n");
        printf("\n");
        printf("Supports command execution by running files using the `./' operator.\n");
        printf("\n");
        printf("Supports command chaining using the `;' operator.\n");
        printf("\n");
        printf("Supports command piping using the `|` operator.\n");
        printf("\n");
        printf("For more information on a specific command, type `help <command>'.\n");
        printf("\n");
    }
    else
    {
        // Tokenize the input command string
        char* token = strtok(command, " ");
        while (token != NULL)
        {
            // Display information about each command token
            if (strcmp(token, "cd") == 0)
            {
                printf("\n");
                printf("cd: cd [-L|[-P [-e]] [-@]] [dir]\n");
                printf("    Change the shell working directory.\n");
                printf("\n");
            }
            else if (strcmp(token, "exit") == 0)
            {
                printf("\n");
                printf("exit: exit [n]\n");
                printf("    Exit the shell.\n");
                printf("\n");
            }
            else if (strcmp(token, "echo") == 0)
            {
                printf("\n");
                printf("echo: echo [-neE] [arg ...]\n");
                printf("    Write arguments to the standard output.\n");
                printf("\n");
            }
            else if (strcmp(token, "pwd") == 0)
            {
                printf("\n");
                printf("pwd: pwd [-LP]\n");
                printf("    Print the current working directory.\n");
                printf("\n");
            }
            else if (strcmp(token, "type") == 0)
            {
                printf("\n");
                printf("type: type [-afptP] name [name ...]\n");
                printf("    Indicate how each name would be interpreted if used as a command name.\n");
                printf("\n");
            }
            else if (strcmp(token, "help") == 0)
            {
                printf("\n");
                printf("help: help [-dms] [pattern ...]\n");
                printf("    Display information about built-in commands.\n");
                printf("\n");
            }
            else if (strcmp(token, "ls") == 0)
            {
                printf("\n");
                printf("ls: ls [-af] [file ...]\n");
                printf("    List directory contents.\n");
                printf("\n");
            }
            else if (strcmp(token, "cat") == 0)
            {
                printf("\n");
                printf("cat: cat [file] or cat [file] < [file]\n");
                printf("    Concatenate files and print on the standard output.\n");
                printf("\n");
            }
            else if (strcmp(token, "mkdir") == 0)
            {
                printf("\n");
                printf("mkdir: mkdir [-p] directory ...\n");
                printf("    Create directories.\n");
                printf("\n");
            }
            else if (strcmp(token, "rmdir") == 0)
            {
                printf("\n");
                printf("rmdir: rmdir directory ...\n");
                printf("    Remove directories.\n");
                printf("\n");
            }
            else if (strcmp(token, "grep") == 0)
            {
                printf("\n");
                printf("grep: grep [-ivclnwo] pattern [file ...]\n");
                printf("    Search for patterns in files.\n");
                printf("\n");
            }
            else if (strcmp(token, "clear") == 0)
            {
                printf("\n");
                printf("clear\n");
                printf("    Clear the terminal screen.\n");
                printf("\n");
            }
            else if (strcmp(token, "date") == 0)
            {
                printf("\n");
                printf("date: date [<format>]\n");
                printf("    Display current date and time.\n");
                printf("    <format> - Optional argument to specify custom date format.\n");
                printf("\n");
            }
            else
            {
                printf("\n");
                printf("bash: help: %s: no help topics match\n", token);
                printf("\n");
            }

            // Get the next token
            token = strtok(NULL, " ");
        }
    }
}
