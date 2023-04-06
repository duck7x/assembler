#ifndef ASSEMBLER_PHASE_H
#define ASSEMBLER_PHASE_H

#include <stdio.h>
#include "assembler_phase_functions.h"

int assembler_phase(char** files_list); /* TODO: Add documentation */
/*int run_assembler_phase_1(char* file_name, LinkedCommandList_t action_names_list); *//* TODO: Add documentation */
int run_assembler_phase_1(char* file_name, LinkedCommandList_t action_names_list, LinkedList_t data_memory_list, LabelsLinkedList_t symbol_table, char *memory_array[], int *has_errors); /* TODO: Add documentation */
int run_assembler_phase_2(char* file_name, LinkedCommandList_t action_names_list); /* TODO: Add documentation */

#endif
