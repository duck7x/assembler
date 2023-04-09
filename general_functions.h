#ifndef GENERAL_FUNCTIONS_H /* Prevents recursive includes */
#define GENERAL_FUNCTIONS_H

#include "utils.h"

/* Characters in common use*/
#define NEWLINE '\n'
#define SPACE ' '
#define COMMA ','
#define COLON ':'
#define RIGHT_BRACKET ')'
#define LEFT_BRACKET '('

/* File modes */
#define READ "r"
#define WRITE "w"
#define APPEND "a"

#define INPUT_SUFFIX ".as" /* Suffix of the assembler files */
#define POST_PRE_ASSEMBLER_SUFFIX ".am" /* Suffix of the files created by pre-assembler */
#define MAX_LINE_LENGTH 80 /* maximum allowed characters in a line */
#define ReadLine(FILE, LINE) fscanf(FILE, "%[^\n] ", LINE) /* Reading a line from file */
#define StringsEqual(FIRST, SECOND) strcmp(FIRST, SECOND) == 0 /* Check if wo strings are equal */

/*  Function to handle error messages throughout the assembler phases.
    Gets an error message, prints it and the line number.
    Also sets the global variable has_errors to TRUE.
    INPUT:  error_message is a string representing an error that occurred
    OUTPUT: This function doesn't return anything.
*/
void handle_error(char *error_message);

/*  Function to handle warning messages throughout the assembler phases.
    Gets a warning message, prints it and the line number.
    INPUT:  warning_message is a string representing a warning that occurred
    OUTPUT: This function doesn't return anything.
*/
void handle_warning(char *warning_message);

/*  Gets two strings, and checks if the second is the prefix of the first.
    INPUT:  str is the string we want to check
            prefix is the string of the prefix we want to check
    OUTPUT: TRUE if str starts with prefix
            FALSE if str doesn't start with prefix
*/
int starts_with(char *str, char *prefix);

/*  Gets a string and a characters.
    Returns the index of the character in the string which is right before the given delimiter.
    INPUT:  str is the string we're searching through.
            delimiter is the character we're searching for.
    OUTPUT: An int representing the index in the character.
            -1 if the character doesn't appear in the string at all.
*/
int get_index_till_delimiter(char* str, char delimiter);

/*  Like split method (in python for example),
    gets a string and splits it into sub-strings according to the given delimiter.
    INPUT:  str representing a string.
            delimiter character to split the string by.
    OUTPUT: a linked list of all substrings of this string, divided by the delimiter (delimiter not included).
*/
LinkedList_t split_string(char* str, char delimiter);

/*  Gets a string, returns a clean and stripped version of the string
    Meaning there are no trailing spaces at the start and end of the returned string
    All consecutive whitespaces are squeezed together into one space (' ') character.
    INPUT:  str - the string that should be cleaned.
    OUTPUT: str - the cleaned string.
*/
char* get_clean_and_stripped_string(char* str);

/*  Gets a string.
    Squeezes all consecutive whitespaces together into one space (' ') character.
    INPUT:  str - the string that should be cleaned.
    OUTPUT: str - the cleaned string.
*/
char* clean_multiple_whitespaces(char* str);

/*  Gets a string.
    Returns the string without any whitespaces in it
    INPUT:  str - the string that should be cleaned.
    OUTPUT: str - the cleaned string.
*/
char* get_string_without_whitespaces(char* str);

/*  Gets a string.
    Removes any trailing whitespaces at the start or end of the given string.
    INPUT:  str - the string to clean up.
    OUTPUT: str - the cleaned up string.
*/
char* get_stripped_string(char* str);

/*  Gets a file and a string, writes that string into that file.
    INPUT:  file - the destination file we want to write to
            string - the string we want to add to the file
    OUTPUT: This function doesn't return anything.
*/
void write_string_to_file(FILE* file, char* string);

#endif
