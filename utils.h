#ifndef UTILS_H /* Prevents recursive includes */
#define UTILS_H

#include <stdlib.h>
#include <string.h>
#include "structures.h"

/* Boolean values to enable boolean use in code */
#define TRUE 1
#define FALSE 0

#define END_OF_STRING '\0' /* End pf string character*/

/* Boolean usage (similar to python) to make code easier to read */
#define is(VAR) (VAR == TRUE)
#define is_not(VAR) (VAR == FALSE)

#define isSpace(CHAR) (CHAR == ' ' || CHAR == '\t') /* Checks if a character is of space type */

extern int has_errors; /* global variable used to check if the assembler encountered any errors so far */
extern int line_count; /* global variable to track line number, useful mainly for error handling */

/*  Gets a string and creates a copy of it
    INPUT:  str - the string to copy
    OUTPUT: a copy of the given string
*/
char* copy_string(char* str);

/*  Gets a string, a start index and an end index.
    Copies the substring from the start index till the end index of the given string.
    INPUT:  str     - the string to (partially) copy.
            start   - the index where the desired substring begins.
            end     - the index where the desired substring ends.
    OUTPUT:
*/
char* copy_substring(char* str, int start, int end);

/*  Gets two strings and concatenates them.
    INPUT:  first   - the first string
            second  - the second string
    OUTPUT: The concatenated string.
*/
char* concatenate_strings(char* first, char* second);

#endif
