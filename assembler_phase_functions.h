#ifndef ASSEMBLER_PHASE_FUNCTIONS_H
#define ASSEMBLER_PHASE_FUNCTIONS_H

#include <stdio.h>
#include <math.h>
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
#define MEMORY_SIZE 256 /* TODO: Add documentation */
#define FIRST_AVAILABLE_ADDRESS 100 /* TODO: Add documentation */
#define IMMEDIATE 0 /* TODO: Add documentation */
#define DIRECT 1 /* TODO: Add documentation */
#define JUMP 2 /* TODO: Add documentation */
#define REGISTER 3 /* TODO: Add documentation */
#define COMMENT_PREFIX ";" /* TODO: Add documentation */
#define ENTRY_TYPE "entry" /* TODO: Add documentation */

#define IsRegister(STRING) (strlen(STRING) == 2 && STRING[0] == 'r' && STRING[1] <= '7' && STRING[1] >= '0') /* TODO: Add documentation */

typedef struct LabelNode *LabelNode_t; /* TODO: Add documentation */
typedef struct LinkedLabelsList *LabelsLinkedList_t; /* TODO: Add documentation */
typedef struct CommandNode *CommandNode_t; /* TODO: Add documentation */
typedef struct LinkedCommandList *LinkedCommandList_t; /* TODO: Add documentation */

LabelsLinkedList_t create_linked_labels_list(); /* TODO: Add documentation */
LabelNode_t create_label_node(char* name, char* type, int value); /* TODO: Add documentation */
char* get_label_node_name(LabelNode_t node);  /* TODO: Add documentation */
char* get_label_node_type(LabelNode_t node);  /* TODO: Add documentation */
int get_label_node_value(LabelNode_t node);  /* TODO: Add documentation */
LabelNode_t get_next_label_node(LabelNode_t node);  /* TODO: Add documentation */
void set_label_node_value(LabelNode_t node, int new_val); /* TODO: Add documentation */
void set_label_node_type(LabelNode_t node, char *new_type); /* TODO: Add documentation */
void add_to_labels_list(LabelNode_t node, LabelsLinkedList_t list); /* TODO: Add documentation */
int get_labels_list_length(LabelsLinkedList_t list); /* TODO: Add documentation */
LabelNode_t get_labels_list_head(LabelsLinkedList_t list); /* TODO: Add documentation */
CommandNode_t create_command_node(char* command, char* code, int operands, char* source_operand_types, char* destination_operand_types); /* TODO: Add documentation */
char* get_command_node_code(CommandNode_t node); /* TODO: Add documentation */
char* get_command_node_command(CommandNode_t node); /* TODO: Add documentation */
int get_command_node_operands(CommandNode_t node); /* TODO: Add documentation */
char* get_command_node_source_operand_types(CommandNode_t node); /* TODO: Add documentation */
char* get_command_node_destination_operand_types(CommandNode_t node); /* TODO: Add documentation */
CommandNode_t get_next_command_node(CommandNode_t node); /* TODO: Add documentation */
LinkedCommandList_t create_linked_command_list(); /* TODO: Add documentation */
void add_to_commands_list(CommandNode_t node, LinkedCommandList_t list); /* TODO: Add documentation */
int get_commands_list_length(LinkedCommandList_t list); /* TODO: Add documentation */
CommandNode_t get_commands_list_head(LinkedCommandList_t list); /* TODO: Add documentation */
CommandNode_t search_command_list(LinkedCommandList_t list, char* command); /* TODO: Add documentation */
void print_commands_list(LinkedCommandList_t list); /* TODO: Add documentation */
void print_labels_list(LabelsLinkedList_t list); /* TODO: delete this */
void print_assembler_phase(void); /* TODO: delete this */
LinkedCommandList_t create_action_names_list(); /* TODO: Add documentation */
void handle_error(char *error_message, int line_number, int *has_errors); /* TODO: Add documentation */
void handle_warning(char *warning_message, int line_number); /* TODO: Add documentation */
int starts_with_label(LinkedList_t split_line); /* TODO: Add documentation */
int is_data_storage(char *line); /* TODO: Add documentation */
int is_extern_or_entry(char *line); /* TODO: Add documentation */
int is_extern(char *line); /* TODO: Add documentation */
int is_entry(char *line); /* TODO: Add documentation */
void add_label(LabelsLinkedList_t labels_list, LinkedList_t split_line, char *type, int value, int *has_errors, int line_number); /* TODO: Add documentation */
void mark_label_as_entry(LabelsLinkedList_t symbol_table, char* label_name); /* TODO: Add documentation */
void update_symbol_table(LabelsLinkedList_t symbol_table, int ic); /* TODO: Add documentation */
void set_binary_string_from_num(unsigned int num, char *binary_string, int start); /* TODO: Add documentation */
void set_binary_string_from_string(char *str, char *binary_string, int start); /* TODO: Add documentation */
char* dec_to_binary(int num); /* TODO: Add documentation */
char* binary(char *string); /* TODO: Add documentation */
int handle_data_type(char *line, LinkedList_t memory_list); /* TODO: Add documentation */
int handle_string_type(char *line, LinkedList_t memory_list); /* TODO: Add documentation */
int is_legal_label_name(char *str); /* TODO: Add documentation */
int is_immediate_address_type (char *str); /* TODO: Add documentation */
int is_direct_address_type (char *str); /* TODO: Add documentation */
int is_direct_register_type (char *str); /* TODO: Add documentation */
int is_jump_address_type(char *str); /* TODO: Add documentation */
int get_address_type(char *operand); /* TODO: Add documentation */
LinkedList_t get_split_operands(char *operands_string); /* TODO: Add documentation */
int has_non_register_operands(LinkedList_t split_operands); /* TODO: Add documentation */
int calculate_words_for_line(CommandNode_t command_node, char *relevant_line_bit); /* TODO: Add documentation */
int handle_first_word(CommandNode_t command_node, char *relevant_line_bit, char memory_slot[], int line_number, int *has_errors); /* TODO: Add documentation */
int handle_all_but_first_words(CommandNode_t command_node, char *relevant_line_bit, char memory_slot[], int line_number, int *has_errors); /* TODO: Add documentation */
int is_valid_line(char *line); /* TODO: Add documentation */
#endif
