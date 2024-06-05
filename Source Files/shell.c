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
  * @brief  Moves the cursor right by one position in the console.
  * @param  None
  * @return void
  * @note   This function moves the cursor right by one position in the console
  *         to handle arrow key input.
  */
static void moveCursorRight() 
{
    printf("\033[1C"); // Move cursor right by one position
}

/**
  * @brief  Moves the cursor back by one position in the console.
  * @param  None
  * @return void
  * @note   This function moves the cursor back by one position in the console
  *         to handle backspace input.
  */
static void moveCursorLeft() 
{
    printf("\033[1D"); // Move cursor left by one position
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
  * @brief  Handles user input character by character.
  * @param  buffer: The input buffer.
  * @param  index: The index of the buffer.
  * @return void
  * @note   This function reads user input character by character and processes
  *         it to handle backspace, enter, and tab characters. It also prevents
  *         buffer overflow and processes the command once the user hits enter.
  */
static void handleInput(char buffer[], int* index) {
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
    DWORD bytesRead;
    INPUT_RECORD irInBuf;
    int inputLength = strlen(buffer); // Track the length of input
    int cursorPosition = 0; // Track the cursor position on the screen
    char tempBuffer[128] = ""; // Temporary buffer to traverse without modifying the real buffer
    int tempIndex = 0; // Temporary index for traversing

    while (1) {
        if (ReadConsoleInput(hStdin, &irInBuf, 1, &bytesRead)) {
            if (irInBuf.EventType == KEY_EVENT && irInBuf.Event.KeyEvent.bKeyDown) {
                switch (irInBuf.Event.KeyEvent.wVirtualKeyCode) {
                case VK_LEFT:
                    if (tempIndex > 0) {
                        moveCursorLeft();
                        tempIndex--;
                        cursorPosition--;
                    }
                    break;
                case VK_RIGHT:
                    if (tempIndex < strlen(tempBuffer)) {
                        moveCursorRight();
                        tempIndex++;
                        cursorPosition++;
                    }
                    break;
                case VK_RETURN:
                    printf("\n");
                    buffer[*index] = '\0'; // Null-terminate the buffer
                    commandCheck(buffer); // Execute the command
                    memset(buffer, 0, sizeof(buffer)); // Clear the buffer for next input
                    *index = 0;
                    // Copy the content of tempBuffer to buffer
                    strcpy(buffer, tempBuffer);
                    *index = strlen(tempBuffer);
                    return;
                default:
                    if (irInBuf.Event.KeyEvent.uChar.AsciiChar == '\b' || irInBuf.Event.KeyEvent.uChar.AsciiChar == 127) {
                        if (tempIndex > 0) {
                            tempIndex--;
                            moveCursorLeft();
                            printf(" "); // Erase the character
                            moveCursorLeft();
                            memmove(&tempBuffer[tempIndex], &tempBuffer[tempIndex + 1], strlen(tempBuffer) - tempIndex);
                        }
                    }
                    else if (irInBuf.Event.KeyEvent.uChar.AsciiChar >= 32 && irInBuf.Event.KeyEvent.uChar.AsciiChar < 127) {
                        if (strlen(tempBuffer) < sizeof(tempBuffer) - 1) { // Check if there is space in the tempBuffer
                            putchar(irInBuf.Event.KeyEvent.uChar.AsciiChar);
                            memmove(&tempBuffer[tempIndex + 1], &tempBuffer[tempIndex], strlen(tempBuffer) - tempIndex);
                            tempBuffer[tempIndex] = irInBuf.Event.KeyEvent.uChar.AsciiChar;
                            tempIndex++;
                            cursorPosition++;
                        }
                    }
                    break;
                }
            }
        }
    }
}

/**
  * @brief  Gets user input from the console and processes it.
  * @param  None
  * @return void
  * @note   This function reads user input character by character and processes
  *         it to handle backspace, enter, and tab characters. It also prevents
  *         buffer overflow and processes the command once the user hits enter.
  */
static void get_Input() {
    char buffer[128] = { 0 }; // Buffer to store user input
    int index = 0;

    enableRawMode(); // Enable raw input mode

    while (1) {
        yellow(); // Set text color to yellow
        info(); // Display user prompt
        reset(); // Reset text color

        index = 0; // Reset the buffer index for each new command

        handleInput(buffer, &index);

        commandCheck(buffer); // Process the command

        memset(buffer, 0, sizeof(buffer)); // Clear the buffer
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