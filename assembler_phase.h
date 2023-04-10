#ifndef ASSEMBLER_PHASE_H /* Prevents recursive includes */
#define ASSEMBLER_PHASE_H

#include "assembler_phase_functions.h"


/*  Gets an array of files that already passed the pre-assembler phase and their count.
    Runs phase 1 and phase 2 of the assembler on each of those files.
    Once this phase is done, all files in the given array should have been compiled according to the
    Assembler process (unless files that contain any errors).
    INPUT:  files_list  -   an array of string, containing all files that needs to be compiled.
            files_count -   an int representing the amount of files in that array.
    OUTPUT: Returns 0 if all went well
            and -1 if any errors prevented the assembler run (in which case, no files will be created).
*/
int assembler_phase(char** files_list, int files_count);

/*
    INPUT:
    OUTPUT:
*/
int run_assembler_phase_1(char* file_name, LinkedCommandList_t action_names_list, LinkedList_t *data_memory_list, LabelsLinkedList_t *symbol_table, char *memory_array[]); /* TODO: Add documentation */

/*
    INPUT:
    OUTPUT:
*/
int run_assembler_phase_2(char* file_name, LinkedCommandList_t action_names_list, Table_t *extern_memory_table, LabelsLinkedList_t *symbol_table, char *memory_array[]); /* TODO: Add documentation */

/*  Gets a file name, a memory array, a symbol table and an externals memory table.
    Generates files based on the given data with the given file name and relevant suffix:
    Object files    -   .ob file, containing the machine code with the special binary encoding.
    Externals file  -   .ext file, will be created only if there are any external in the code.
                        Contains all external definitions and their line number.
    Entries file    -   .ent file, will be created only if there are any entry labels in the code.
                        Contains all entry labels in the code.
    This is the final step of the assembly and should be used in case there were no errors in all previous steps.
    INPUT:  file_name               -   a string representing the name all create files should have.
            memory_array            -   an array containing all the uncoded machine code (for the object file).
            symbol_table            -   a labels linked list containing all the labels in the file.
            external_memory_table   -   a table containing all info regarding externals used in the file.

    OUTPUT: This function doesn't return anything.
*/
void create_files(char* file_name, char *memory_array[], LabelsLinkedList_t *symbol_table, Table_t *external_memory_table);

/*  Gets a string representing a file name (without suffix).
    Attempts to remove all files that are created by the assembler, according to the expected suffix:
    .am, .ob, .ext and .ent.
    This function should be used in case any phase of the assembler on that file had any errors.
    INPUT:  file_name - a string representing a file on which the assembler had failed.
    OUTPUT: This function doesn't return anything.
*/
void delete_created_files(char *file_name);

#endif
