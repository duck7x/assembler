#ifndef GENERAL_FUNCTIONS_H
#define GENERAL_FUNCTIONS_H

#include <stdio.h>
#include "utils.h"

#define NEWLINE '\n' /* TODO: Add documentation */
#define isEndOfLine(CHAR) (CHAR == EOF || CHAR == '\n') /* TODO: Add documentation */
#define READ "r" /* TODO: Add documentation */
#define WRITE "w" /* TODO: Add documentation */
#define INPUT_SUFFIX ".as" /* TODO: Add documentation */ /* TODO: Maybe move to pre_assembler_functions */


int starts_with(char *str, char *prefix); /* TODO: Add documentation */
int get_index_till_delimiter(char* str, char delimiter); /* TODO: Add documentation */
LinkedList_t split_string(char* str, char delimiter); /* TODO: Add documentation */
char* get_string_without_whitespaces(char* str); /* TODO: Add documentation */
char* get_stripped_string(char* str); /* TODO: Add documentation */
char* get_next_line(FILE* file, char* line); /* TODO: Add documentation */
void write_line_to_file(FILE* file, char* line); /* TODO: Maybe change name to "append_chunk_to_file */ /* TODO: Add documentation */

#endif
