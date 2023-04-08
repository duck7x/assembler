#ifndef UTILS_H
#define UTILS_H

#include <stdlib.h>
#include <string.h>

#define LAST_ALLOCATION_INDEX 1999 /* TODO: Add documentation */
#define CURRENT_MAX_TABLE_SIZE 1000 /* TODO: Add documentation */
#define TRUE 1 /* TODO: Add documentation */
#define FALSE 0 /* TODO: Add documentation */
#define CHAR_SIZE 8 /* TODO: Add documentation */

#define is(VAR) (VAR == TRUE) /* TODO: Add documentation */
#define is_not(VAR) (VAR == FALSE) /* TODO: Add documentation */
#define isSpace(CHAR) (CHAR == ' ' || CHAR == '\t') /* TODO: Add documentation */

typedef struct Allocator *Allocator_t; /* TODO: Add documentation */
typedef struct Pair *Pair_t; /* TODO: Add documentation */
typedef struct Table *Table_t; /* TODO: Add documentation */
typedef struct Node *Node_t; /* TODO: Add documentation */
typedef struct LinkedList *LinkedList_t; /* TODO: Add documentation */
extern Allocator_t global_allocator; /* TODO: Add documentation */
extern int has_errors; /* TODO: Add documentation */
extern int line_count; /* TODO: Add documentation */

Allocator_t create_allocator(); /* TODO: Add documentation */
Table_t create_table(); /* TODO: Add documentation */
Pair_t create_pair(char* key, char* value); /* TODO: Add documentation */
LinkedList_t create_linked_list(); /* TODO: Add documentation */
Node_t create_node(char* value); /* TODO: Add documentation */
char* get_node_value(Node_t node);  /* TODO: Add documentation */
Node_t get_next_node(Node_t node);  /* TODO: Add documentation */
void add_to_list(Node_t node, LinkedList_t list); /* TODO: Add documentation */
int get_list_length(LinkedList_t list); /* TODO: Add documentation */
void print_list(LinkedList_t list); /* TODO: delete this */
char* get_list_as_string(LinkedList_t list); /* TODO: Add documentation */
Node_t get_head(LinkedList_t list); /* TODO: Add documentation */
Node_t get_tail(LinkedList_t list); /* TODO: Add documentation */
void* allocate(int size_of); /* TODO: Add documentation */
void free_all(); /* TODO: Add documentation */
void free_all_and_allocator(); /* TODO: Add documentation */
char* copy_string(char* str);  /* TODO: maybe move to gf */ /* TODO: Add documentation */
char* copy_substring(char* str, int start, int end);  /* TODO: maybe move to gf */ /* TODO: Add documentation */
char* concatenate_strings(char* first, char* second);  /* TODO: maybe move to gf */ /* TODO: Add documentation */
char* append_char_to_string(char* str, int c);  /* TODO: maybe move to gf */ /* TODO: Add documentation */
char* get_value_from_table(Table_t t, char* key); /* TODO: Add documentation */
void add_to_table(Table_t t, char* key, char* value); /* TODO: Add documentation */
void add_to_table_if_not_exists(Table_t t, char* key, char* value); /* TODO: Add documentation */
int get_number_of_pairs(Table_t t); /* TODO: Add documentation */
Pair_t* get_pair_array(Table_t t); /* TODO: Add documentation */
void print_table(Table_t t); /* TODO: delete this */
char* get_pair_key(Pair_t p); /* TODO: Add documentation */
char* get_pair_value(Pair_t p); /* TODO: Add documentation */
void print_pair(Pair_t p); /* TODO: delete this */

#endif
