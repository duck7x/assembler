#include "utils.h"

typedef struct {
    int number_of_allocated_elements;
    void* ptr_list[LAST_ALLOCATION_INDEX+1];
} Allocator;

typedef struct {
    char* key;
    char* value;
} Pair;

typedef struct {
    int current_table_size;
    int number_of_pairs;
    Pair pair_table[CURRENT_MAX_TABLE_SIZE];
} Table;

Allocator* create_allocator(){
    Allocator* allocator = (Allocator*)malloc(sizeof(Allocator));
    allocator->ptr_list[LAST_ALLOCATION_INDEX] = allocator;
}

Table* create_table(Allocator* allocator){
    Table* table = allocate(allocator, sizeof(Table));
    table->current_table_size = CURRENT_MAX_TABLE_SIZE;
    table->number_of_pairs = 0;
    return table;
}

/* Add create pair function */

void* allocate(Allocator* allocator_ptr, int size_of){
    void* new_ptr = malloc(size_of);
    int current_free_allocation_index = allocator_ptr->number_of_allocated_elements++;
    if (current_free_allocation_index >= LAST_ALLOCATION_INDEX){
        exit(1);  /* Handle more gracefully */
    }
    allocator_ptr->ptr_list[current_free_allocation_index] = new_ptr;
    return new_ptr;
}

void free_all(Allocator* allocator_ptr){
    for (int i=0; i <= allocator_ptr->number_of_allocated_elements; i++){
        free(allocator_ptr->ptr_list[i]);
        allocator_ptr->ptr_list[i] = 0;  /* change to null */
    }
}

void free_all_and_allocator(Allocator* allocator_ptr){
    free_all(allocator_ptr);
    free(allocator_ptr->ptr_list[LAST_ALLOCATION_INDEX]);  /* Need to add null */
    /* Maybe add free functions to reduce code repetition */
}

int get_index_till_delimiter(char* str, char delimiter){
    char* delimeter_address = strchr(str, delimiter);
    if (delimeter_address){
        return (int)(delimeter_address-str);
    }
    return -1;
}

char* copy_string(Allocator* allocator, char* str){
    char* copied_str = (char*)allocate(allocator, sizeof(char)*(strlen(str)+1));
    strcpy(copy_string, str);
    return copied_str;
}

void add_to_table(Table t, char* key, char* value){
    Pair pair;
    pair.key = key;
    pair.value = value;
    t.pair_table[t.number_of_pairs++] = pair;
}

char* get_value(Table t, char* key){
    for (int i=0; i < t.number_of_pairs; i++){
        if (strcmp(t.pair_table[i].key, key)){
            return t.pair_table[i].value;
        }
    }
    return NULL;
}

void add_to_table_if_not_exists(Table t, char* key, char* value){
    if (get_value(t, key)){
        return;  /* Handle better */
    }
    add_to_table(t, key, value);
}