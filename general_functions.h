#ifndef GENERAL_FUNCTIONS_H
#define GENERAL_FUNCTIONS_H

#include <stdio.h>
#include "utils.h"

#define NEWLINE '\n' /* TODO: Add documentation */
#define SPACE ' ' /* TODO: Add documentation */
#define COMMA ',' /* TODO: Add documentation */
#define COLON ':' /* TODO: Add documentation */
#define COLON ':' /* TODO: Add documentation */
#define COLON ':' /* TODO: Add documentation */
#define RIGHT_BRACKET ')' /* TODO: Add documentation */
#define LEFT_BRACKET '(' /* TODO: Add documentation */
#define READ "r" /* TODO: Add documentation */
#define WRITE "w" /* TODO: Add documentation */
#define APPEND "a" /* TODO: Add documentation */
#define INPUT_SUFFIX ".as" /* TODO: Add documentation */ /* TODO: Maybe move to pre_assembler_functions */
#define POST_PRE_ASSEMBLER_SUFFIX ".am" /* TODO: Add documentation */
#define MAX_LINE_LENGTH 80 /* TODO: Add documentation */
#define ReadLine(FILE, LINE) fscanf(FILE, "%[^\n] ", LINE) /* TODO: Add documentation */
#define StringsEqual(FIRST, SECOND) strcmp(FIRST, SECOND) == 0 /* TODO: Add documentation */
#define BITS_AMOUNT 14 /* TODO: Add documentation */ /* TODO: rename this */


int starts_with(char *str, char *prefix); /* TODO: Add documentation */
int get_index_till_delimiter(char* str, char delimiter); /* TODO: Add documentation */
LinkedList_t split_string(char* str, char delimiter); /* TODO: Add documentation */
char* clean_multiple_whitespaces(char* str); /* TODO: Add documentation */
char* get_string_without_whitespaces(char* str); /* TODO: Add documentation */
char* get_stripped_string(char* str); /* TODO: Add documentation */
char* get_next_line(FILE* file, char* line); /* TODO: Add documentation */
char* get_next_line_stripped(FILE* file, char* line); /* TODO: Add documentation */
void write_line_to_file(FILE* file, char* line); /* TODO: Maybe change name to "append_chunk_to_file */ /* TODO: Add documentation */

#endif
