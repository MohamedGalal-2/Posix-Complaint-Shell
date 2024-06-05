/* Includes Section */
#include "..\Header Files\\shell.h"

/* Function Definition Section */


void display_welcome_message() 
{
    cyan();
    printf("\n");
    printf("**********************************************************\n");
    printf("*           Welcome to the Ultimate POSIX Shell          *\n");
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
    reset();
}

void info() {
    // Retrieving username from environment variable
    char* username = getenv("USERNAME");
    if (username == NULL)
    {
        return;
    }

    // Retrieving computer name from environment variable
    char* computerName = getenv("COMPUTERNAME");
    if (computerName == NULL) 
    {
        return;
    }
    
    // Displaying the username and computer name
    green();
    printf("%s@%s", username, computerName);
    reset();

    printf(":");
    blue();
    printf("~");
    reset();
    printf("$ ");
}

void get_Input()
{
    char buffer[128]; // buffer to store user input
    while (1)
    {
        yellow();
        info();
        reset();
        
        // get the user input character by character until the user presses the enter key
        fgets(buffer, 128, stdin);
       
        commandCheck(buffer);
    }
}

void shell_Init()
{
    display_welcome_message();
    get_Input();
}