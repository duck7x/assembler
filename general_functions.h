#ifndef GENERAL_FUNCTIONS_H
#define GENERAL_FUNCTIONS_H

#include <stdio.h>
#include "utils.h"

int starts_with(char *str, char *prefix);
int get_index_till_delimiter(char* str, char delimiter);
LinkedList_t split_string(char* str, char delimiter); /* NOT DONE */
char* get_string_without_whitespaces(char* str);

#endif