#ifndef ASSEMBLER_PHASE_FUNCTIONS_H
#define ASSEMBLER_PHASE_FUNCTIONS_H


#include <stdio.h>
#include "general_functions.h"

#define DATA_PREFIX ".data" /* TODO: Add documentation */
#define STRING_PREFIX ".string" /* TODO: Add documentation */
#define EXTERN_PREFIX ".extern" /* TODO: Add documentation */
#define ENTRY_PREFIX ".entry" /* TODO: Add documentation */

void print_assembler_phase(void); /* TODO: delete this */
int starts_with_label(char *line); /* TODO: Add documentation */
int is_data_storage(char *line); /* TODO: Add documentation */
int add_label(int dc); /* TODO: Add documentation */
int is_extern_or_entry(char *line); /* TODO: Add documentation */
int is_extern(char *line); /* TODO: Add documentation */
#endif
