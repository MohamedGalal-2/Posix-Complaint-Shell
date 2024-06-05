/* Includes Section */
#include "..\Header Files\\shell.h"

/* Function Definition Section */

/**
  * @brief  Displays a welcome message in the console with instructions.
  * @param  None
  * @return void
  * @note   This function prints a welcome message in cyan color with instructions
  *         on how to use the POSIX shell and provides some basic ASCII art.
  */
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

/**
  * @brief  Displays the username, computer name, and current path in the console.
  * @param  None
  * @return void
  * @note   This function retrieves the username, computer name, and current path
  *         from the environment variables and displays them in the console.
  */
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
    printf("$ ");
}

/**
  * @brief  Enables raw input mode for the console.
  * @param  None
  * @return void
  * @note   This function disables echo input, line input, and processed input
  *         to allow for raw input mode in the console.
  */
void enableRawMode()
{
    // Get handle to standard input
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);

    // Get current console mode
    DWORD mode;
    GetConsoleMode(hStdin, &mode);

    // Disable echo, line input, and input processing
    mode &= ~(ENABLE_ECHO_INPUT | ENABLE_LINE_INPUT | ENABLE_PROCESSED_INPUT);

    // Set modified console mode
    SetConsoleMode(hStdin, mode);
}

/**
  * @brief  Disables raw input mode for the console.
  * @param  None
  * @return void
  * @note   This function enables echo input, line input, and processed input
  *         to reset the console mode to its default state.
  */
void disableRawMode()
{
    // Get handle to standard input
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);

    // Get current console mode
    DWORD mode;
    GetConsoleMode(hStdin, &mode);

    // Enable echo, line input, and input processing
    mode |= (ENABLE_ECHO_INPUT | ENABLE_LINE_INPUT | ENABLE_PROCESSED_INPUT);

    // Set modified console mode
    SetConsoleMode(hStdin, mode);
}

/**
  * @brief  Moves the cursor back by one position in the console.
  * @param  None
  * @return void
  * @note   This function moves the cursor back by one position in the console
  *         to handle backspace input.
  */
static void moveCursorBack() 
{
    printf("\b \b");
}

/**
  * @brief  Gets user input from the console and processes it.
  * @param  None
  * @return void
  * @note   This function reads user input character by character and processes
  *         it to handle backspace, enter, and tab characters. It also prevents
  *         buffer overflow and processes the command once the user hits enter.
  */
static void get_Input()
{
    // Get handle to standard input
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);

    char buffer[128]; // Buffer to store user input
    DWORD bytesRead;
    char ch;
    int index = 0;

    enableRawMode(); // Enable raw input mode

    while (1)
    {
        yellow(); // Set text color to yellow
        info(); // Display user prompt
        reset(); // Reset text color

        index = 0; // Reset the buffer index for each new command

        while (1)
        {
            ReadConsole(hStdin, &ch, 1, &bytesRead, NULL); // Read input character by character

            // Filter out tab characters
            if (ch == '\t')
            {
                continue;
            }

            // Handle backspace
            if (ch == '\b' || ch == 127)
            {
                if (index > 0)
                {
                    index--;
                    moveCursorBack(); // Move cursor back one position
                }
                continue;
            }

            // Check for Enter key to process the command
            if (ch == '\r')
            {
                buffer[index] = '\0'; // Null-terminate the buffer
                printf("\n"); // Move to a new line
                commandCheck(buffer); // Process the command
                break;
            }

            // Echo the character and add to buffer
            putchar(ch);
            buffer[index++] = ch;

            // Prevent buffer overflow
            if (index >= 127)
            {
                buffer[127] = '\0'; // Null-terminate the buffer
                printf("\nCommand too long: %s\n", buffer); // Print error message
                break;
            }
        }
    }

    disableRawMode(); // Reset the console mode
}

/**
  * @brief  Initializes the shell by displaying a welcome message and getting user input.
  * @param  None
  * @return void
  * @note   This function serves as the entry point for the shell application.
  */
void shell_Init()
{
    display_welcome_message();
    get_Input();
}