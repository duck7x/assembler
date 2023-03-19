#include "utils.h"

struct Allocator {
    int number_of_allocated_elements;
    void* ptr_list[LAST_ALLOCATION_INDEX+1];
};

struct Pair{
    char* key;
    char* value;
};

struct Table{
    int current_table_size;
    int number_of_pairs;
    Pair_t pair_table[CURRENT_MAX_TABLE_SIZE];
};

Allocator_t* create_allocator() {
    Allocator_t* allocator = (Allocator_t*)malloc(sizeof(Allocator_t));
    (*allocator)->ptr_list[LAST_ALLOCATION_INDEX] = allocator;
    return allocator;
}

Table_t* create_table(Allocator_t* allocator) {
    Table_t* table = allocate(allocator, sizeof(Table_t));
    (*table)->current_table_size = CURRENT_MAX_TABLE_SIZE;
    (*table)->number_of_pairs = 0;
    return table;
}

/* Add create pair function */

void* allocate(Allocator_t* allocator_ptr, int size_of) {
    void* new_ptr = malloc(size_of);
    int current_free_allocation_index = (*allocator_ptr)->number_of_allocated_elements++;
    if (current_free_allocation_index >= LAST_ALLOCATION_INDEX) {
        exit(1);  /* Handle more gracefully */
    }
    (*allocator_ptr)->ptr_list[current_free_allocation_index] = new_ptr;
    return new_ptr;
}

void free_all(Allocator_t* allocator_ptr) {
    int i;
    for (i=0; i <= (*allocator_ptr)->number_of_allocated_elements; i++) {
        free((*allocator_ptr)->ptr_list[i]);
        (*allocator_ptr)->ptr_list[i] = 0;  /* change to null */
    }
}

void free_all_and_allocator(Allocator_t* allocator_ptr) {
    free_all(allocator_ptr);
    free((*allocator_ptr)->ptr_list[LAST_ALLOCATION_INDEX]);  /* Need to add null */
    /* Maybe add free functions to reduce code repetition */
}

int get_index_till_delimiter(char* str, char delimiter) {
    char* delimeter_address = strchr(str, delimiter);
    if (delimeter_address) {
        return (int)(delimeter_address-str);
    }
    return -1;
}

char* copy_string(Allocator_t* allocator, char* str) {
    char* copied_str = (char*)allocate(allocator, sizeof(char)*(strlen(str)+1));
    strcpy(copied_str, str);
    return copied_str;
}

void clean_string(char* str) {
    int i;
    int str_len = strlen(str);
    char cleaned_str[str_len];  /* TODO: fix warning */
    int cleaned_str_index = 0;
    memset(cleaned_str, '\0', sizeof(cleaned_str));

    for (i=0; i < str_len; i++) {
        if (!isSpace(str[i])) {
            cleaned_str[cleaned_str_index] = str[i];
            cleaned_str_index++;
        }
    }

    strcpy(str, cleaned_str);
}

void add_to_table(Table_t t, char* key, char* value) {
    Pair_t pair; /*TODO: use create pair here*/
    (*pair).key = key;
    (*pair).value = value;
    (*t).pair_table[(*t).number_of_pairs++] = pair;
}

char* get_value(Table_t t, char* key) {
    int i;
    for (i=0; i < (*t).number_of_pairs; i++) {
        if (strcmp((*(*t).pair_table[i]).key, key)) {
            return (*(*t).pair_table[i]).value;
        }
    }
    return NULL;
}

void add_to_table_if_not_exists(Table_t t, char* key, char* value) {
    if (get_value(t, key)) {
        return;  /* Handle better */
    }
    add_to_table(t, key, value);
}