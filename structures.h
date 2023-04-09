#ifndef STRUCTURES_H /* Prevents recursive includes */
#define STRUCTURES_H

#include "stdio.h"  /* TODO: delete this if not needed */
#include "utils.h"

#define LAST_ALLOCATION_INDEX 1999 /* TODO: Add documentation */
#define CURRENT_MAX_TABLE_SIZE 1000 /* TODO: Add documentation */

typedef struct Allocator *Allocator_t; /* TODO: Add documentation */
typedef struct Pair *Pair_t; /* TODO: Add documentation */
typedef struct Table *Table_t; /* TODO: Add documentation */
typedef struct Node *Node_t; /* TODO: Add documentation */
typedef struct LinkedList *LinkedList_t; /* TODO: Add documentation */
typedef struct LabelNode *LabelNode_t; /* TODO: Add documentation */
typedef struct LinkedLabelsList *LabelsLinkedList_t; /* TODO: Add documentation */
typedef struct CommandNode *CommandNode_t; /* TODO: Add documentation */
typedef struct LinkedCommandList *LinkedCommandList_t; /* TODO: Add documentation */

extern Allocator_t global_allocator; /* TODO: Add documentation */


/* Allocator methods */
Allocator_t create_allocator(); /* TODO: Add documentation */
void* allocate(int size_of); /* TODO: Add documentation */
void free_all(); /* TODO: Add documentation */
void free_all_and_allocator(); /* TODO: Add documentation */

/* Pair methods */
Pair_t create_pair(char* key, char* value); /* TODO: Add documentation */
char* get_pair_key(Pair_t p); /* TODO: Add documentation */
char* get_pair_value(Pair_t p); /* TODO: Add documentation */
void print_pair(Pair_t p); /* TODO: Add documentation */

/* Table methods */
Table_t create_table(); /* TODO: Add documentation */
void add_to_table(Table_t t, char* key, char* value); /* TODO: Add documentation */
void add_to_table_if_not_exists(Table_t t, char* key, char* value); /* TODO: Add documentation */
char* get_value_from_table(Table_t t, char* key); /* TODO: Add documentation */
int get_number_of_pairs(Table_t t); /* TODO: Add documentation */
Pair_t* get_pair_array(Table_t t); /* TODO: Add documentation */
void print_table(Table_t t); /* TODO: Add documentation */

/* Node methods */
Node_t create_node(char* value); /* TODO: Add documentation */
char* get_node_value(Node_t node); /* TODO: Add documentation */
Node_t get_next_node(Node_t node); /* TODO: Add documentation */

/* LinkedList methods */
LinkedList_t create_linked_list(); /* TODO: Add documentation */
void add_to_list(Node_t node, LinkedList_t list); /* TODO: Add documentation */
int get_list_length(LinkedList_t list); /* TODO: Add documentation */
char* get_list_as_string(LinkedList_t list); /* TODO: Add documentation */
Node_t get_head(LinkedList_t list); /* TODO: Add documentation */
Node_t get_tail(LinkedList_t list); /* TODO: Add documentation */
void print_list(LinkedList_t list); /* TODO: Add documentation */

/* LabelNode methods */
LabelNode_t create_label_node(char* name, char* type, int value); /* TODO: Add documentation */
char* get_label_node_type(LabelNode_t node); /* TODO: Add documentation */
int get_label_node_value(LabelNode_t node); /* TODO: Add documentation */
char* get_label_node_name(LabelNode_t node); /* TODO: Add documentation */
LabelNode_t get_next_label_node(LabelNode_t node); /* TODO: Add documentation */
void set_label_node_value(LabelNode_t node, int new_val); /* TODO: Add documentation */
void set_label_node_type(LabelNode_t node, char *new_type); /* TODO: Add documentation */

/* LinkedLabelsList methods */
LabelsLinkedList_t create_linked_labels_list(); /* TODO: Add documentation */
void add_to_labels_list(LabelNode_t node, LabelsLinkedList_t list); /* TODO: Add documentation */
int get_labels_list_length(LabelsLinkedList_t list); /* TODO: Add documentation */
LabelNode_t get_labels_list_head(LabelsLinkedList_t list); /* TODO: Add documentation */
LabelNode_t search_labels_list(LabelsLinkedList_t list, char* label); /* TODO: Add documentation */
void print_labels_list(LabelsLinkedList_t list); /* TODO: Add documentation */

/* CommandNode methods */
CommandNode_t create_command_node(char* command, char* code, int operands, char* source_operand_types, char* destination_operand_types); /* TODO: Add documentation */
char* get_command_node_code(CommandNode_t node); /* TODO: Add documentation */
char* get_command_node_command(CommandNode_t node); /* TODO: Add documentation */
int get_command_node_operands(CommandNode_t node); /* TODO: Add documentation */
char* get_command_node_source_operand_types(CommandNode_t node); /* TODO: Add documentation */
char* get_command_node_destination_operand_types(CommandNode_t node); /* TODO: Add documentation */
CommandNode_t get_next_command_node(CommandNode_t node); /* TODO: Add documentation */
void print_commands_node(CommandNode_t node); /* TODO: Add documentation */

/* LinkedCommandList methods */
LinkedCommandList_t create_linked_command_list(); /* TODO: Add documentation */
void add_to_commands_list(CommandNode_t node, LinkedCommandList_t list); /* TODO: Add documentation */
int get_commands_list_length(LinkedCommandList_t list); /* TODO: Add documentation */
CommandNode_t get_commands_list_head(LinkedCommandList_t list); /* TODO: Add documentation */
CommandNode_t search_command_list(LinkedCommandList_t list, char* command); /* TODO: Add documentation */
void print_commands_list(LinkedCommandList_t list); /* TODO: Add documentation */

#endif
