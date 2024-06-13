#include "../Header Files/date.h"

// Function to display the current date and time
void display_current_datetime()
{
    time_t current_time;
    struct tm *local_time;

    // Get current time
    current_time = time(NULL);

    // Convert to local time representation
    local_time = localtime(&current_time);
    if (local_time == NULL)
    {
        perror("Error getting local time");
        return;
    }

    // Print formatted date and time
    printf("%s", asctime(local_time));
}

// Function to display the date and time in a specific format
void display_formatted_datetime(const char *format)
{
    time_t current_time;
    struct tm *local_time;
    char buffer[1024];

    // Get current time
    current_time = time(NULL);

    // Convert to local time representation
    local_time = localtime(&current_time);
    if (local_time == NULL)
    {
        perror("Error getting local time");
        return;
    }

    // Format the date and time
    strftime(buffer, sizeof(buffer), format, local_time);

    // Print formatted date and time
    printf("%s\n", buffer);
}

// Function to set the system date and time (requires superuser privileges)
bool set_system_datetime(int month, int day, int hour, int minute, int year)
{
    char date_cmd[100];
    sprintf(date_cmd, "sudo date %02d%02d%02d%02d%04d.00", month, day, hour, minute, year);

    // Run the system command to set the date
    int ret = system(date_cmd);

    if (ret == 0)
    {
        printf("System date and time set successfully.\n");
        return true;
    }
    else
    {
        fprintf(stderr, "Failed to set system date and time.\n");
        return false;
    }
}

// Function to check if the date format is valid
bool isValidDateFormat(const char *date_format)
{
	// Check if the date format is valid
	if (strlen(date_format) != 10)
	{
		return false;
	}

	// Check if the date format has valid separators
	if (date_format[2] != '/' || date_format[5] != '/')
	{
		return false;
	}

	// Check if the date format has valid digits
	for (int i = 0; i < 10; i++)
	{
		if (i == 2 || i == 5)
		{
			continue;
		}
		if (!isdigit(date_format[i]))
		{
			return false;
		}
	}

	// Check if the month, day, and year are within valid ranges
	int month = atoi(date_format);
	int day = atoi(date_format + 3);
	int year = atoi(date_format + 6);

	if (month < 1 || month > 12)
	{
		return false;
	}

	if (day < 1 || day > 31)
	{
		return false;
	}

	if (year < 1900 || year > 9999)
	{
		return false;
	}

	return true;
}