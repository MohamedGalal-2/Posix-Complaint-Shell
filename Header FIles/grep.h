#ifndef GREP_H
#define GREP_H

#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include "colors.h"

// ANSI color codes for terminal output
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_RESET   "\x1b[0m"


// Function to search for a string in a file and print matching lines
// Supports various grep flags
// Returns the number of matching lines found, or -1 on failure

/**
  * @brief  Search for a string in a file and print matching lines
  * @param  filename The name of the file to search
  * @param  search_string The string to search for
  * @param  ignore_case If true, ignore case distinctions
  * @param  invert_match If true, select non-matching lines
  * @param  count If true, print the count of matching lines
  * @param  list_files If true, print only the names of files with matching lines
  * @param  line_number If true, print line numbers with output lines
  * @param  word_regexp If true, match only whole words
  * @param  only_matching If true, print only the matched parts of matching lines
  * @return The number of matching lines found, or -1 on failure
  */
int grep(const char* filename, const char* search_string, bool ignore_case, bool invert_match, bool count, bool list_files, bool line_number, bool word_regexp, bool only_matching);

// Function to parse the arguments and flags for the grep function
// Returns 0 on success, -1 on failure

/**
  * @brief  Parse the arguments and flags for the grep function
  * @param  argument The argument string to parse
  * @param  search_string The variable to store the search string
  * @param  filename The variable to store the filename
  * @param  ignore_case The variable to store the ignore_case flag
  * @param  invert_match The variable to store the invert_match flag
  * @param  count The variable to store the count flag
  * @param  list_files The variable to store the list_files flag
  * @param  line_number The variable to store the line_number flag
  * @param  word_regexp The variable to store the word_regexp flag
  * @param  only_matching The variable to store the only_matching flag
  * @return 0 if successful, -1 if an error occurred
  */
int parseGrepFlagsAndArgs(char* argument, char* search_string, char* filename, bool* ignore_case, bool* invert_match, bool* count, bool* list_files, bool* line_number, bool* word_regexp, bool* only_matching);

// Helper function to convert a string to lowercase

/**
  * @brief  Convert a string to lowercase
  * @param  str The string to convert to lowercase
  */
void to_lowercase(char* str);

// Helper function to check if a word boundary is present

/**
  * @brief  Check if a word boundary is present
  * @param  str The string to check
  * @param  pos The position in the string to check for a boundary
  * @param  len The length of the search string
  * @return True if a word boundary is present, otherwise false
  */
bool is_word_boundary(const char* str, int pos, int len);

#endif // GREP_H
