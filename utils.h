#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define LAST_ALLOCATION_INDEX 999
#define CURRENT_MAX_TABLE_SIZE 1000
#define isSpace(CHAR) (CHAR == ' ' || CHAR == '\t')

typedef struct Allocator *Allocator_t;
typedef struct Pair *Pair_t;
typedef struct Table *Table_t;

Allocator_t* create_allocator();
Table_t* create_table(Allocator_t* allocator);
void* allocate(Allocator_t* allocator_ptr, int size_of);
void free_all(Allocator_t* allocator_ptr);
void free_all_and_allocator(Allocator_t* allocator_ptr);
int get_index_till_delimiter(char* str, char delimiter);
char* copy_string(Allocator_t* allocator, char* str);
void clean_string(char* str);
void add_to_table(Table_t t, char* key, char* value);
char* get_value(Table_t t, char* key);
void add_to_table_if_not_exists(Table_t t, char* key, char* value);