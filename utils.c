#include "utils.h"
#include "stdio.h" /* TODO: delete this */

struct Allocator {
    int number_of_allocated_elements;
    void* ptr_list[LAST_ALLOCATION_INDEX+1];
} Allocator;

struct Pair{
    char* key;
    char* value;
} Pair;

struct Table{
    int current_table_size;
    int number_of_pairs;
    Pair_t pair_table[CURRENT_MAX_TABLE_SIZE];
} Table;

struct Node{
    char* value;
    Node_t next;
} Node;

struct LinkedList {
    Node_t head;
    Node_t tail;
    int list_length;
} LinkedList;

Allocator_t create_allocator() {
    Allocator_t allocator = (Allocator_t)malloc(sizeof(Allocator));
    memset(allocator->ptr_list, 0, sizeof(void*) * (LAST_ALLOCATION_INDEX + 1));
    allocator->ptr_list[LAST_ALLOCATION_INDEX] = allocator;
    allocator->number_of_allocated_elements = 0;
    return allocator;
}

Table_t create_table() {
    Table_t table = allocate(sizeof(Table));
    table->current_table_size = CURRENT_MAX_TABLE_SIZE;
    table->number_of_pairs = 0;
    return table;
}

Pair_t create_pair(char* key, char* value) {
    Pair_t pair = allocate(sizeof(Pair));
    pair->key = copy_string(key);
    pair->value = copy_string(value);
    return pair;
}

LinkedList_t create_linked_list() {
    LinkedList_t list = allocate(sizeof(LinkedList));
    list->head = NULL;
    list->tail = NULL;
    list->list_length = 0;
    return list;
}

Node_t create_node(char* value) {
    Node_t node = allocate(sizeof(Node));
    node->value = value;
    node->next = NULL;
    return node;
}

void add_to_list(Node_t node, LinkedList_t list) {
    if (list->list_length == 0) {
        list->head = node;
        list->tail = node;
    } else {
        list->tail->next = node;
        list->tail = node;
    }
    list->list_length++;
}

/* TODO: DELETE THIS */
void print_list(LinkedList_t list) {
    Node_t node;
    node = list->head;
    printf("List has %d items: ", list->list_length);
    while(node != NULL) {
        printf("%s -> ", node->value);
        node = node->next;
    }
    printf("NULL\n");
}

void* allocate(int size_of) {
    void* new_ptr = malloc(size_of);
    int current_free_allocation_index = global_allocator->number_of_allocated_elements++;
    if (current_free_allocation_index >= LAST_ALLOCATION_INDEX) {
        exit(1);  /* TODO: Handle more gracefully */
    }
    global_allocator->ptr_list[current_free_allocation_index] = new_ptr;
    return new_ptr;
}

void free_all() {
    int i;
    for (i=0; i < global_allocator->number_of_allocated_elements; i++) {
        free(global_allocator->ptr_list[i]);
        global_allocator->ptr_list[i] = NULL;
    }
}

void free_all_and_allocator() {
    void* temp;
    temp = global_allocator->ptr_list[LAST_ALLOCATION_INDEX];
    free_all();
    global_allocator->ptr_list[LAST_ALLOCATION_INDEX] = NULL;
    free(temp);
    /* TODO: Maybe add free functions to reduce code repetition */
}

char* copy_string(char* str) {
    char* copied_str = (char*)allocate(sizeof(char)*(strlen(str)+1));
    strcpy(copied_str, str);
    return copied_str;
}

char* copy_substring(char* str, int start, int end) {
    char* copied_str = (char*)allocate(sizeof(char)*(end - start + 1));
    int i;
    for (i = 0; i < end - start; ++i) {
        copied_str[i] = str[start + i];
    }
    copied_str[i] = '\0';
    return copied_str;
}

char* get_value(Table_t t, char* key) {
    int i;
    for (i=0; i < t->number_of_pairs; i++) {
        if (!strcmp(t->pair_table[i]->key, key)) {
            return t->pair_table[i]->value;
        }
    }
    return NULL;
}

void add_to_table(Table_t t, char* key, char* value) {
    Pair_t pair;
    pair = create_pair(key, value);
    t->pair_table[t->number_of_pairs++] = pair;
}

void add_to_table_if_not_exists(Table_t t, char* key, char* value) {
    if (get_value(t, key)) {
        return;  /* TODO: Handle better */
    }
    add_to_table(t, key, value);
}