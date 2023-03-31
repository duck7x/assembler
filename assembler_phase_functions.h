#ifndef ASSEMBLER_PHASE_FUNCTIONS_H
#define ASSEMBLER_PHASE_FUNCTIONS_H


#include <stdio.h>
#include "general_functions.h"

#define DATA_PREFIX ".data" /* TODO: Add documentation */
#define STRING_PREFIX ".string" /* TODO: Add documentation */
#define EXTERN_PREFIX ".extern" /* TODO: Add documentation */
#define ENTRY_PREFIX ".entry" /* TODO: Add documentation */

typedef struct LabelNode *LabelNode_t; /* TODO: Add documentation */
typedef struct LinkedLabelsList *LabelsLinkedList_t; /* TODO: Add documentation */

LabelsLinkedList_t create_linked_labels_list(); /* TODO: Add documentation */
LabelNode_t create_label_node(char* name, char* type, int value); /* TODO: Add documentation */
char* get_label_node_name(LabelNode_t node);  /* TODO: Add documentation */
char* get_label_node_type(LabelNode_t node);  /* TODO: Add documentation */
int get_label_node_value(LabelNode_t node);  /* TODO: Add documentation */
LabelNode_t get_next_label_node(LabelNode_t node);  /* TODO: Add documentation */
void add_to_labels_list(LabelNode_t node, LabelsLinkedList_t list); /* TODO: Add documentation */
int get_labels_list_length(LabelsLinkedList_t list); /* TODO: Add documentation */
LabelNode_t get_labels_list_head(LabelsLinkedList_t list); /* TODO: Add documentation */
void print_labels_list(LabelsLinkedList_t list); /* TODO: delete this */
void print_assembler_phase(void); /* TODO: delete this */
int starts_with_label(char *line); /* TODO: Add documentation */
int is_data_storage(char *line); /* TODO: Add documentation */
int add_label(int dc); /* TODO: Add documentation */
int is_extern_or_entry(char *line); /* TODO: Add documentation */
int is_extern(char *line); /* TODO: Add documentation */
#endif
