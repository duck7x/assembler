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
Allocator_t global_allocator;

Allocator_t create_allocator(); /* DONE */
Table_t create_table();  /* DONE */
Pair_t create_pair(Allocator_t allocator, char* key, char* value);  /* DONE */
void* allocate(Allocator_t allocator_ptr, int size_of); /* DONE */
void free_all(Allocator_t allocator_ptr); /* DONE */
void free_all_and_allocator(Allocator_t allocator_ptr); /* DONE */
char* copy_string(Allocator_t allocator, char* str);  /* DONE */
char* get_value(Table_t t, char* key);  /* DONE */
void add_to_table(Allocator_t allocator, Table_t t, char* key, char* value);  /* DONE */
void add_to_table_if_not_exists(Allocator_t allocator, Table_t t, char* key, char* value);  /* DONE */