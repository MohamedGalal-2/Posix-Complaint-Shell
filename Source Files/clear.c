#include "../Header Files/clear.h"

// Function to clear the console screen
void clear_screen()
{
    #ifdef _WIN32
        // Windows system
        system("cls");
    #else
        // Unix-like system
        printf("\033[H\033[J");
    #endif
}
