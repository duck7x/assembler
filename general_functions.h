#ifndef GENERAL_FUNCTIONS_H
#define GENERAL_FUNCTIONS_H

#include <stdio.h>
#include "utils.h"

#define NEWLINE '\n'
#define isEndOfLine(CHAR) (CHAR == EOF || CHAR == '\n')

int starts_with(char *str, char *prefix);
int get_index_till_delimiter(char* str, char delimiter);
LinkedList_t split_string(char* str, char delimiter);
char* get_string_without_whitespaces(char* str);
char* get_stripped_string(char* str);
char* get_next_line(FILE* file, char* line);
void write_line_to_file(FILE* file, char* line); /* TODO: Maybe change name to "append_chunk_to_file */

#endif
