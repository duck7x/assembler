#ifndef ASSEMBLER_PHASE_FUNCTIONS_H /* Prevents recursive includes */
#define ASSEMBLER_PHASE_FUNCTIONS_H

#include <stdio.h>
#include <ctype.h>
#include "general_functions.h"

#define DEFAULT_EMPTY_WORD "00000000000000" /* TODO: Add documentation */
#define DATA_PREFIX ".data" /* TODO: Add documentation */
#define STRING_PREFIX ".string" /* TODO: Add documentation */
#define EXTERN_PREFIX ".extern" /* TODO: Add documentation */
#define ENTRY_PREFIX ".entry" /* TODO: Add documentation */
#define DATA_TYPE "data" /* TODO: Add documentation */
#define EXTERN_TYPE "extern" /* TODO: Add documentation */
#define EXTERN_DEFAULT_VALUE 0 /* TODO: Add documentation */
#define CODE_TYPE "code" /* TODO: Add documentation */
#define MINUS '-' /* TODO: Add documentation */
#define PLUS '+' /* TODO: Add documentation */
#define POUND_SIGN "#" /* TODO: Add documentation */
#define MEMORY_SIZE 256 /* TODO: Add documentation */
#define FIRST_AVAILABLE_ADDRESS 100 /* TODO: Add documentation */
#define IMMEDIATE 0 /* TODO: Add documentation */
#define DIRECT 1 /* TODO: Add documentation */
#define JUMP 2 /* TODO: Add documentation */
#define REGISTER 3 /* TODO: Add documentation */
#define COMMENT_PREFIX ";" /* TODO: Add documentation */
#define ENTRY_TYPE "entry" /* TODO: Add documentation */
#define SOURCE 5 /* TODO: Add documentation */
#define DESTINATION 11 /* TODO: Add documentation */
#define OBJECT_FILE_SUFFIX ".ob" /* TODO: Add documentation */
#define EXTERNALS_FILE_SUFFIX ".ext" /* TODO: Add documentation */
#define ENTRIES_FILE_SUFFIX ".ent" /* TODO: Add documentation */

#define IsRegister(STRING) (strlen(STRING) == 2 && STRING[0] == 'r' && STRING[1] <= '7' && STRING[1] >= '0') /* TODO: Add documentation */

/* UNSORTED */
LinkedCommandList_t create_action_names_list(); /* TODO: Add documentation */
int starts_with_label(LinkedList_t split_line); /* TODO: Add documentation */
int is_data_storage(char *line); /* TODO: Add documentation */
int is_extern_or_entry(char *line); /* TODO: Add documentation */
int is_extern(char *line); /* TODO: Add documentation */
int is_entry(char *line); /* TODO: Add documentation */
void add_label(LabelsLinkedList_t labels_list, LinkedList_t split_line, char *type, int value); /* TODO: Add documentation */
void mark_label_as_entry(LabelsLinkedList_t symbol_table, char* label_name); /* TODO: Add documentation */
void update_symbol_table(LabelsLinkedList_t symbol_table, int ic); /* TODO: Add documentation */
int add_data_symbols_to_memory(LinkedList_t data_memory_list, int ic, char *memory_array[]); /* TODO: Add documentation */
void set_binary_string_from_num(unsigned int num, char *binary_string, int start); /* TODO: Add documentation */
void set_binary_string_from_string(char *str, char *binary_string, int start); /* TODO: Add documentation */
int handle_data_type(char *line, LinkedList_t memory_list); /* TODO: Add documentation */
int handle_string_type(char *line, LinkedList_t memory_list); /* TODO: Add documentation */
int is_legal_label_name(char *str); /* TODO: Add documentation */
int calculate_words_for_line(CommandNode_t command_node, char *relevant_line_bit); /* TODO: Add documentation */
int handle_first_word(CommandNode_t command_node, char *relevant_line_bit, char memory_slot[]); /* TODO: Add documentation */
int handle_all_but_first_words(CommandNode_t command_node, char *relevant_line_bit, Table_t *extern_memory_table, LabelsLinkedList_t *symbol_table, char *memory_array[], int ic); /* TODO: Add documentation */
int is_valid_line(char *line); /* TODO: Add documentation */


/* SORTED */

/* Address type / operands related functions */ /* TODO: Rewrite doc title */
LinkedList_t get_split_operands(char *operands_string); /* TODO: Add documentation */

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

/*
    INPUT:
    OUTPUT:
*/
int get_address_type(char *operand); /* TODO: Add documentation */

/*
    INPUT:
    OUTPUT:
*/
void set_immediate_type_code(char *memory_bit, char *operand); /* TODO: Add documentation */

/*
    INPUT:
    OUTPUT:
*/
void set_direct_type_code(char *memory_bit, char *operand, Table_t *extern_memory_table ,LabelsLinkedList_t *symbol_table, int ic); /* TODO: Add documentation */

/*
    INPUT:
    OUTPUT:
*/
void set_jump_type_code(char *memory_array[], int ic, char *operand, Table_t *extern_memory_table, LabelsLinkedList_t *symbol_table); /* TODO: Add documentation */

/*
    INPUT:
    OUTPUT:
*/
void set_register_type_code(char *memory_bit, char *operand, int start); /* TODO: Add documentation */

/*
    INPUT:
    OUTPUT:
*/
void set_operand_code(char *operand_string, int source_or_dest, Table_t *extern_memory_table, LabelsLinkedList_t *symbol_table, char *memory_array[], int ic); /* TODO: Add documentation */

/*
    INPUT:
    OUTPUT:
*/
int has_non_register_operands(LinkedList_t split_operands); /* TODO: Add documentation */

/* Files related functions */
void write_object_file(char* file_name, char *memory_array[]); /* TODO: Add documentation */
void create_externals_file(char* file_name, Table_t external_memory_table); /* TODO: Add documentation */
void create_entries_file(char* file_name, LabelsLinkedList_t symbol_table); /* TODO: Add documentation */

#endif
