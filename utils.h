#ifndef UTILS_H /* Prevents recursive includes */
#define UTILS_H

#include <stdlib.h>
#include <string.h>
#include "structures.h"

#define TRUE 1 /* TODO: Add documentation */
#define FALSE 0 /* TODO: Add documentation */
#define END_OF_STRING '\0' /* TODO: Add documentation */

#define is(VAR) (VAR == TRUE) /* TODO: Add documentation */
#define is_not(VAR) (VAR == FALSE) /* TODO: Add documentation */
#define isSpace(CHAR) (CHAR == ' ' || CHAR == '\t') /* TODO: Add documentation */

extern int has_errors; /* TODO: Add documentation */
extern int line_count; /* TODO: Add documentation */

char* copy_string(char* str);  /* TODO: maybe move to gf */ /* TODO: Add documentation */
char* copy_substring(char* str, int start, int end);  /* TODO: maybe move to gf */ /* TODO: Add documentation */
char* concatenate_strings(char* first, char* second);  /* TODO: maybe move to gf */ /* TODO: Add documentation */
char* append_char_to_string(char* str, int c);  /* TODO: maybe move to gf */ /* TODO: Add documentation */

#endif
