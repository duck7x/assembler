#ifndef ASSEMBLER_TEST_H
#define ASSEMBLER_TEST_H

#include <stdio.h>
#include "utils.h"

void print_new_line(void);
int starts_with(char *str, char *prefix);
int get_index_till_delimiter(char* str, char delimiter); /* DONE */
char* clean_string(char* str);  /* DONE */

#endif