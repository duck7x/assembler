#ifndef UTILS_H
#define UTILS_H

#include <stdlib.h>
#include <string.h>

#define LAST_ALLOCATION_INDEX 999
#define CURRENT_MAX_TABLE_SIZE 1000
#define TRUE 1
#define FALSE 0
#define is(VAR) (VAR == TRUE)
#define isSpace(CHAR) (CHAR == ' ' || CHAR == '\t')

typedef struct Allocator *Allocator_t;
typedef struct Pair *Pair_t;
typedef struct Table *Table_t;
extern Allocator_t global_allocator;

Allocator_t create_allocator();
Table_t create_table();
Pair_t create_pair(char* key, char* value);
void* allocate(int size_of);
void free_all();
void free_all_and_allocator();
char* copy_string(char* str);
char* get_value(Table_t t, char* key);
void add_to_table(Table_t t, char* key, char* value);
void add_to_table_if_not_exists(Table_t t, char* key, char* value);

#endif