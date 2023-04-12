#ifndef ASSEMBLER_PHASE_FUNCTIONS_H /* Prevents recursive includes */
#define ASSEMBLER_PHASE_FUNCTIONS_H

#include <stdio.h>
#include <ctype.h>
#include "general_functions.h"

#define DEFAULT_EMPTY_WORD "00000000000000" /* TODO: Add documentation */


#define EXTERN_DEFAULT_VALUE 0 /* TODO: Add documentation */

#define MEMORY_SIZE 256 /* TODO: Add documentation */
#define FIRST_AVAILABLE_ADDRESS 100 /* TODO: Add documentation */

#define COMMENT_PREFIX ";" /* TODO: Add documentation */

#define SOURCE 5 /* TODO: Add documentation */
#define DESTINATION 11 /* TODO: Add documentation */

/* Instructions */
#define DATA_PREFIX ".data"
#define STRING_PREFIX ".string"
#define EXTERN_PREFIX ".extern"
#define ENTRY_PREFIX ".entry"

/* Label types */
#define DATA_TYPE "data"
#define EXTERN_TYPE "extern"
#define CODE_TYPE "code"
#define ENTRY_TYPE "entry"

/* Address types */
#define IMMEDIATE 0
#define DIRECT 1
#define JUMP 2
#define REGISTER 3

/* File suffixes */
#define OBJECT_FILE_SUFFIX ".ob"
#define EXTERNALS_FILE_SUFFIX ".ext"
#define ENTRIES_FILE_SUFFIX ".ent"

/* Machine code translation */
#define ZERO '.' /* TODO: Add documentation */
#define ONE '/' /* TODO: Add documentation */

#define IsRegister(STRING) (strlen(STRING) == 2 && STRING[0] == 'r' && STRING[1] <= '7' && STRING[1] >= '0') /* TODO: Add documentation */

/* UNSORTED */
LinkedCommandList_t create_action_names_list(); /* TODO: Add documentation */

int is_data_storage(char *line); /* TODO: Add documentation */
int is_extern_or_entry(char *line); /* TODO: Add documentation */
int is_extern(char *line); /* TODO: Add documentation */
int is_entry(char *line); /* TODO: Add documentation */
void set_binary_string_from_num(unsigned int num, char *binary_string, int start); /* TODO: Add documentation */
void set_binary_string_from_string(char *str, char *binary_string, int start); /* TODO: Add documentation */
int handle_data_type(char *line, LinkedList_t memory_list); /* TODO: Add documentation */
int handle_string_type(char *line, LinkedList_t memory_list); /* TODO: Add documentation */
int calculate_words_for_line(CommandNode_t command_node, char *relevant_line_bit); /* TODO: Add documentation */
int handle_first_word(CommandNode_t command_node, char *relevant_line_bit, char memory_slot[]); /* TODO: Add documentation */
int handle_all_but_first_words(CommandNode_t command_node, char *relevant_line_bit, Table_t *extern_memory_table, LabelsLinkedList_t *symbol_table, char *memory_array[], int ic); /* TODO: Add documentation */
int is_valid_line(char *line); /* TODO: Add documentation */


/* SORTED */

/* Labels related functions */

/*  Gets a linked list, representing a line split by colons
    Checks if the linked list represents a line that starts with a label
    INPUT:  split_line - a line split by a colon delimiter.
    OUTPUT: TRUE if the given list represent a line starting with a label
            FALSE if the given list does not represent a line starting with a label
*/
int starts_with_label(LinkedList_t split_line);

/*  Gets a labels list, a line split, a string representing label type and an int representing label value.
    Ensure the label defined by the line is valid.
    If it is, adds its details to the given labels list.
    If it isn't, handles the error.
    INPUT:  labels_list - linked labels list representing all labels that had been defined in the file.
            split_line  - a linked list representing the current line split by the colon delimiter.
            type        - the new label's type.
            value       - the new label's value.
    OUTPUT: This function doesn't return anything.
*/
void add_label(LabelsLinkedList_t labels_list, LinkedList_t split_line, char *type, int value);

/*  Gets a labels list and a string representing label name.
    Marks the given label in the given list as entry type.
    If the given label is not found in the given list, handles the error.
    INPUT:  symbol_table    - linked labels list representing all labels that had been defined in the file.
            label_name      - a string representing a label to be marked as entry
    OUTPUT: This function doesn't return anything.
*/
void mark_label_as_entry(LabelsLinkedList_t symbol_table, char* label_name);

/*  Gets a labels list and an in counter.
    Adds the given counter to the values of all data labels in the given list.
    This is one of the last steps of phase 1 of the assembler.
    INPUT:  symbol_table    - linked labels list representing all labels that had been defined in the file.
            ic              - an int representing the instructions counter.
    OUTPUT: This function doesn't return anything.
*/
void update_symbol_table(LabelsLinkedList_t symbol_table, int ic);

/*  Gets a data memory list, an instruction counter and a memory array.
    Adds all items in the data memory list to the end of the given memory array and returns the updated ic value.
    INPUT:  data_memory_list    - A linked list representing the data image of the assembler.
            ic                  - An int representing the current instruction counter.
            memory_array        - An array of strings, representing the code image of the assembler.
    OUTPUT: Returns the updated ic value, after adding all the data image to the code image.
*/
int add_data_symbols_to_memory(LinkedList_t data_memory_list, int ic, char *memory_array[]);

/*  Gets a string representing a label name, and checks if it's a legal label name.
    INPUT:  str - the label name that needs to be checked.
    OUTPUT: TRUE if the given string is a legal label name,
            FALSE if the given string is not a legal label name.
*/
int is_legal_label_name(char *str);

/* Address type / operands related functions */

/*  Gets a string representing the operands bit of a code line.
    Returns a list in which each member represents a single operand from the given string.
    INPUT:  operands_string - a string representing the operands bit of a code line.
    OUTPUT: A linked list of the split operands.
*/
LinkedList_t get_split_operands(char *operands_string);

/*  Gets a string representing an operand,
    Checks if the address type of that operand is of immediate address type.
    INPUT:  str - a string representing an operand.
    OUTPUT: TRUE if the operand is of immediate address type,
            FALSE if the operand is not of immediate address type.
*/
int is_immediate_address_type (char *str);

/*  Gets a string representing an operand,
    Checks if the address type of that operand is of direct address type.
    INPUT:  str - a string representing an operand.
    OUTPUT: TRUE if the operand is of direct address type,
            FALSE if the operand is not of direct address type.
*/
int is_direct_address_type (char *str);

/*  Gets a string representing an operand,
    Checks if the address type of that operand is of direct register address type.
    INPUT:  str - a string representing an operand.
    OUTPUT: TRUE if the operand is of direct register address type,
            FALSE if the operand is not of direct register address type.
*/
int is_direct_register_type (char *str);

/*  Gets a string representing an operand,
    Checks if the address type of that operand is of jump address type.
    INPUT:  str - a string representing an operand.
    OUTPUT: TRUE if the operand is of jump address type,
            FALSE if the operand is not of jump address type.
*/
int is_jump_address_type(char *str);

/*  Gets a string representing an operand.
    Returns an int value representing the address type of that operand.
    INPUT:  str - a string representing an operand.
    OUTPUT: An int between 0 and 3 representing the address type of the given operand:
            IMMEDIATE   0
            DIRECT      1
            JUMP        2
            REGISTER    3
            If the given operand doesn't match any of the 4 address types, the function returns -1.
*/
int get_address_type(char *operand);

/*  Gets a linked list, which should contain exactly 2 operands as its content.
    Checks if any of them has non-register type.
    INPUT:  split_operands - a linked list of the 2 operands to check.
    OUTPUT: FALSE if both operands are of direct register address type,
            TRUE if any of the operands is not of direct register address type.
*/
int has_non_register_operands(LinkedList_t split_operands);

void set_immediate_type_code(char *memory_bit, char *operand); /* TODO: Add documentation */
void set_direct_type_code(char *memory_bit, char *operand, Table_t *extern_memory_table ,LabelsLinkedList_t *symbol_table, int ic); /* TODO: Add documentation */
void set_jump_type_code(char *memory_array[], int ic, char *operand, Table_t *extern_memory_table, LabelsLinkedList_t *symbol_table); /* TODO: Add documentation */
void set_register_type_code(char *memory_bit, char *operand, int start); /* TODO: Add documentation */
void set_operand_code(char *operand_string, int source_or_dest, Table_t *extern_memory_table, LabelsLinkedList_t *symbol_table, char *memory_array[], int ic); /* TODO: Add documentation */

/* Files related functions */

/*  Gets a string representing a file name
    And an array, representing the assembler memory image.
    Writes the machine code, according to the given memory array, to the given file name with .ob suffix.
    INPUT:  file_name       - the name of the output file (not including the suffix).
            memory_array    - the array representing the memory image. Contains all the binary words
                              that needs to be translated and added to the destination file.
    OUTPUT: This function doesn't return anything.
*/
void write_object_file(char* file_name, char *memory_array[]);

/*
    INPUT:
    OUTPUT: This function doesn't return anything.
*/
void create_externals_file(char* file_name, Table_t external_memory_table); /* TODO: Add documentation */

/*
    INPUT:
    OUTPUT: This function doesn't return anything.
*/
void create_entries_file(char* file_name, LabelsLinkedList_t symbol_table); /* TODO: Add documentation */

#endif
