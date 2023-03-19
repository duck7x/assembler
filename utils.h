#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define LAST_ALLOCATION_INDEX 999
#define CURRENT_MAX_TABLE_SIZE 1000
#define isSpace(CHAR) (CHAR == ' ' || CHAR == '\t')

typedef struct Allocator *Allocator_t;
typedef struct Pair *Pair_t;
typedef struct Table *Table_t;

void* allocate(Allocator* allocator_ptr, int size_of);
void free_all(Allocator* allocator_ptr);
void free_all_and_allocator(Allocator* allocator_ptr);
Allocator* create_allocator();
int get_index_till_delimiter(char* str, char delimiter);
char* copy_string(Allocator* allocator, char* str);