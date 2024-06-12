/* Includes Section */
#include "..\Header Files\\shell.h"

/* Function Definition Section */

// Display welcome message
static void display_welcome_message() 
{
    cyan(); // Set text color to cyan
    printf("\n");
    printf("**********************************************************\n");
    printf("*            Welcome to my simple POSIX Shell            *\n");
    printf("*                                                        *\n");
    printf("*                           _~_                          *\n");
    printf("*                          (o o)                         *\n");
    printf("*                         /  V  \\                        *\n");
    printf("*                        /(  _  )\\                       *\n");
    printf("*                          ^^ ^^                         *\n");
    printf("*                                                        *\n");
    printf("*                                                        *\n");
    printf("*    Type 'help' to see the list of available commands   *\n");
    printf("*          Type 'exit' to leave the shell                *\n");
    printf("*                                                        *\n");
    printf("*                                                        *\n");
    printf("*                Author: Mohamed Galal                   *\n");
    printf("*                                                        *\n");
    printf("**********************************************************\n");
    printf("\n");
    reset(); // Reset text color
}

// Display user information
static void info()
{
    struct user userInfo;

    // Retrieving username from environment variable
    strcpy(userInfo.username, getenv("USERNAME"));

    // Retrieving computer name from environment variable
    strcpy(userInfo.computerName, getenv("COMPUTERNAME"));

    // Retrieving current Path
    _getcwd(userInfo.currentPath, MAX_PATH + 1);

    // Displaying user information
    green();
    printf("%s@%s", userInfo.username, userInfo.computerName);
    reset();

    printf(":");
    blue();
    printf("%s", userInfo.currentPath);
    reset();
    yellow();
    printf("$ ");
    reset();
}

// Get user input
static void get_Input()
{
    char input[1024]; // Buffer to store user input
   
    info(); // Display user prompt

    while (1) 
    {
        fgets(input, sizeof(input), stdin); // Read user input from stdin

        // Replace tab character with space
        for (int i = 0; input[i] != '\0'; ++i) 
        {
            if (input[i] == '\t') 
            {
                input[i] = ' ';
            }
        }

        // Remove trailing newline character, if present
        if (input[strlen(input) - 1] == '\n') 
        {
            input[strlen(input) - 1] = '\0';
        }

        // Call commandCheck() function to check the command
        commandCheck(input);
        break; // Exit loop after processing the command
    }
}

// Initialize the shell
void shell_Init()
{  
    display_welcome_message();

    while (1)
    {
        get_Input();
    }

}