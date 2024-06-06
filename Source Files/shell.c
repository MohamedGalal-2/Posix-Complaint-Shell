/* Includes Section */
#include "..\Header Files\\shell.h"

/* Function Definition Section */


static void display_welcome_message() 
{
    /**
      * @brief  Displays a welcome message in the console with instructions.
      * @param  None
      * @return void
      * @note   This function prints a welcome message in cyan color with instructions
      *         on how to use the POSIX shell and provides some basic ASCII art.
      */
    
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

static void info()
{
    /**
      * @brief  Displays the username, computer name, and current path in the console.
      * @param  None
      * @return void
      * @note   This function retrieves the username, computer name, and current path
      *         from the environment variables and displays them in the console.
      */

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

void enableRawMode()
{
    /**
      * @brief  Enables raw input mode for the console.
      * @param  None
      * @return void
      * @note   This function disables echo input, line input, and processed input
      *         to allow for raw input mode in the console.
      */
    
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

void disableRawMode()
{
    /**
      * @brief  Disables raw input mode for the console.
      * @param  None
      * @return void
      * @note   This function enables echo input, line input, and processed input
      *         to reset the console mode to its default state.
      */
    
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

void moveCursorLeft() 
{
    /**
	  * @brief  Moves the cursor one position to the left.
	  * @param  None
	  * @return void
	  * @note   This function moves the cursor one position to the left in the console.
	  */

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    COORD cursorPos = csbi.dwCursorPosition;
    if (cursorPos.X > 0) 
    {
        cursorPos.X--;
    }
    else if (cursorPos.Y > 0) 
    {
        cursorPos.Y--;
        cursorPos.X = csbi.dwSize.X - 1;
    }
    SetConsoleCursorPosition(hConsole, cursorPos);
}

void moveCursorRight() 
{
    /**
      * @brief  Moves the cursor one position to the right.
      * @param  None
      * @return void
      * @note   This function moves the cursor one position to the right in the console.
      */

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    COORD cursorPos = csbi.dwCursorPosition;
    if (cursorPos.X < csbi.dwSize.X - 1) 
    {
        cursorPos.X++;
    }
    else 
    {
        cursorPos.Y++;
        cursorPos.X = 0;
    }
    SetConsoleCursorPosition(hConsole, cursorPos);
}

static void moveCursorToStart(int initialX, int initialY, int tempIndex)
{
    /**
      * @brief  Moves the cursor to the start of the line.
      * @param  initialX The initial X position of the cursor.
      * @param  initialY The initial Y position of the cursor.
      * @param  tempIndex The index of the current character in the temp buffer.
      * @return void
      * @note   This function moves the cursor to the start of the line based on the initial
      *         X and Y positions and the temp buffer index.
      */

    COORD cursorCoord;
    cursorCoord.X = initialX - tempIndex; // Adjusted position based on temp buffer index
    cursorCoord.Y = initialY + (cursorCoord.X < 0 ? 1 : 0); // Increment Y if X is negative
    cursorCoord.X = max(cursorCoord.X, 0); // Ensure X is non-negative
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorCoord);
}

static void redrawLine(const char* tempBuffer, int initialX, int initialY, int tempIndex)
{
    /**
      * @brief  Redraws the current line in the console.
      * @param  tempBuffer The temporary buffer containing the current line.
      * @param  initialX The initial X position of the cursor.
      * @param  initialY The initial Y position of the cursor.
      * @param  tempIndex The index of the current character in the temp buffer.
      * @return void
      * @note   This function clears the current line, redraws the content of the temp buffer,
      *         and moves the cursor to the correct position.
      */

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    COORD cursorCoord;
    cursorCoord.X = initialX;
    cursorCoord.Y = initialY + (initialX + strlen(tempBuffer)) / csbi.dwSize.X; // Calculate the new Y position based on line wrapping
    SetConsoleCursorPosition(hConsole, cursorCoord);

    // Clear the current line
    DWORD charsWritten;
    FillConsoleOutputCharacter(hConsole, ' ', csbi.dwSize.X, cursorCoord, &charsWritten);

    // Move cursor back to the initial position
    cursorCoord.X = initialX;
    SetConsoleCursorPosition(hConsole, cursorCoord);

    // Print the buffer content
    printf("%s", tempBuffer);
}



static void handleInput(char buffer[], int* index)
{
    /**
     * @brief  Handles user input character by character.
     * @param  buffer The buffer to store user input.
     * @param  index The index to keep track of the buffer position.
     * @return void
     * @note   This function reads user input character by character and processes
     *         it to handle backspace, enter, and tab characters. It also prevents
     *         buffer overflow and processes the command once the user hits enter.
     */

    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
    DWORD bytesRead;
    INPUT_RECORD irInBuf;
    char tempBuffer[128] = ""; // Temporary buffer to store input
    int tempIndex = 0; // Index for temporary buffer

    while (1) {
        if (ReadConsoleInput(hStdin, &irInBuf, 1, &bytesRead))
        {
            if (irInBuf.EventType == KEY_EVENT && irInBuf.Event.KeyEvent.bKeyDown)
            {
                if (irInBuf.Event.KeyEvent.wVirtualKeyCode == VK_RETURN)
                {
                    printf("\n"); // Print newline when Enter key is pressed
                    buffer[*index] = '\0'; // Null-terminate the buffer
                    commandCheck(buffer); // Execute the command
                    memset(buffer, 0, sizeof(buffer)); // Clear the buffer for next input
                    *index = 0;
                    // Copy the content of tempBuffer to buffer
                    strcpy(buffer, tempBuffer);
                    *index = strlen(tempBuffer);
                    return;
                }
                else if (irInBuf.Event.KeyEvent.uChar.AsciiChar == '\b' || irInBuf.Event.KeyEvent.uChar.AsciiChar == 127) {
                    // Handle backspace
                    if (*index > 0) {
                        (*index)--;
                        // Move cursor back
                        printf("\b");
                        // Print a space to erase the last character visually
                        printf(" ");
                        // Move cursor back again
                        printf("\b");
                        // Shift characters to the left to overwrite the deleted character
                        for (int i = *index; i < strlen(buffer); ++i) {
                            buffer[i] = buffer[i + 1];
                        }
                        // Redraw the line from the current position
                        redrawLine(buffer + *index, *index, 0, 0);
                    }
                }
                else if (irInBuf.Event.KeyEvent.uChar.AsciiChar >= 32 && irInBuf.Event.KeyEvent.uChar.AsciiChar < 127)
                {
                    // Handle printable characters
                    if (tempIndex < sizeof(tempBuffer) - 1)
                    {
                        printf("%c", irInBuf.Event.KeyEvent.uChar.AsciiChar); // Print character
                        tempBuffer[tempIndex] = irInBuf.Event.KeyEvent.uChar.AsciiChar; // Store character in temporary buffer
                        tempIndex++;
                    }
                }
                else if (irInBuf.Event.KeyEvent.wVirtualKeyCode == VK_LEFT)
                {
                    // Handle left arrow key
                    if (tempIndex > 0)
                    {
                        printf("\b"); // Move cursor back
                        tempIndex--;
                    }
                }
                else if (irInBuf.Event.KeyEvent.wVirtualKeyCode == VK_RIGHT)
                {
                    // Handle right arrow key
                    if (tempIndex < strlen(tempBuffer))
                    {
                        printf("%c", tempBuffer[tempIndex]); // Print next character
                        tempIndex++;
                    }
                }
            }
        }
    }
}

static void get_Input()
{
    /**
	  * @brief  Gets user input from the console.
	  * @param  None
	  * @return void
	  * @note   This function reads user input character by character and processes
	  *         it to handle backspace, enter, and tab characters. It also prevents
	  *         buffer overflow and processes the command once the user hits enter.
	  */

    char input[128]; // Buffer to store user input
   
    info(); // Display user prompt

    while (1) {
        fgets(input, sizeof(input), stdin); // Read user input from stdin

        // Replace tab character with space
        for (int i = 0; input[i] != '\0'; ++i) {
            if (input[i] == '\t') {
                input[i] = ' ';
            }
        }

        // Remove trailing newline character, if present
        if (input[strlen(input) - 1] == '\n') {
            input[strlen(input) - 1] = '\0';
        }

        // Call commandCheck() function to check the command
        commandCheck(input);
        break; // Exit loop after processing the command
    }
}

void shell_Init()
{
    /**
      * @brief  Initializes the shell by displaying a welcome message and getting user input.
      * @param  None
      * @return void
      * @note   This function serves as the entry point for the shell application.
      */
    
    display_welcome_message();

    while (1)
    {
        get_Input();
    }

}