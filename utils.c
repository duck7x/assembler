#include "utils.h"
#include "stdio.h" /* TODO: delete this */

/* TODO: Add documentation */
struct Allocator {
    int number_of_allocated_elements;
    void* ptr_list[LAST_ALLOCATION_INDEX+1];
} Allocator;

/* TODO: Add documentation */
struct Pair{
    char* key;
    char* value;
} Pair;

/* TODO: Add documentation */
struct Table{
    int current_table_size;
    int number_of_pairs;
    Pair_t pair_table[CURRENT_MAX_TABLE_SIZE];
} Table;

/* TODO: Add documentation */
struct Node{
    char* value;
    Node_t next;
} Node;

/* TODO: Add documentation */
struct LinkedList {
    Node_t head;
    Node_t tail;
    int list_length;
} LinkedList;

/* TODO: Add documentation */
Allocator_t create_allocator() {
    Allocator_t allocator = (Allocator_t)malloc(sizeof(Allocator));
    memset(allocator->ptr_list, 0, sizeof(void*) * (LAST_ALLOCATION_INDEX + 1));
    allocator->ptr_list[LAST_ALLOCATION_INDEX] = allocator;
    allocator->number_of_allocated_elements = 0;
    return allocator;
}

/* TODO: Add documentation */
Table_t create_table() {
    Table_t table = allocate(sizeof(Table));
    table->current_table_size = CURRENT_MAX_TABLE_SIZE;
    table->number_of_pairs = 0;
    return table;
}

/* TODO: Add documentation */
Pair_t create_pair(char* key, char* value) {
    Pair_t pair = allocate(sizeof(Pair));
    pair->key = copy_string(key);
    pair->value = copy_string(value);
    return pair;
}

/* TODO: Add documentation */
LinkedList_t create_linked_list() {
    LinkedList_t list = allocate(sizeof(LinkedList));
    list->head = NULL;
    list->tail = NULL;
    list->list_length = 0;
    return list;
}

/* TODO: Add documentation */
Node_t create_node(char* value) {
    Node_t node = allocate(sizeof(Node));
    node->value = value;
    node->next = NULL;
    return node;
}

/* TODO: Add documentation */
char* get_node_value(Node_t node) {
    return node->value;
}

/* TODO: Add documentation */
Node_t get_next_node(Node_t node) {
    return node->next;
}

/* TODO: Add documentation */
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

/* TODO: Add documentation */
Node_t get_head(LinkedList_t list) {
    return list->head;
}

/* TODO: Add documentation */
void* allocate(int size_of) {
    void* new_ptr = malloc(size_of);
    int current_free_allocation_index = global_allocator->number_of_allocated_elements++;
    if (current_free_allocation_index >= LAST_ALLOCATION_INDEX) {
        exit(1);  /* TODO: Handle more gracefully */
    }
    global_allocator->ptr_list[current_free_allocation_index] = new_ptr;
    return new_ptr;
}

/* TODO: Add documentation */
void free_all() {
    int i;
    for (i=0; i < global_allocator->number_of_allocated_elements; i++) {
        free(global_allocator->ptr_list[i]);
        global_allocator->ptr_list[i] = NULL;
    }
}

/* TODO: Add documentation */
void free_all_and_allocator() {
    void* temp;
    printf("Allocated %d stuff\n", global_allocator->number_of_allocated_elements); /* TODO: delete this */
    temp = global_allocator->ptr_list[LAST_ALLOCATION_INDEX];
    free_all();
    global_allocator->ptr_list[LAST_ALLOCATION_INDEX] = NULL;
    free(temp);
    /* TODO: Maybe add free functions to reduce code repetition */
}

/* TODO: Add documentation */
char* copy_string(char* str) {
    char* copied_str = (char*)allocate(sizeof(char)*(strlen(str)+1));
    strcpy(copied_str, str);
    return copied_str;
}

/* TODO: Add documentation */
char* copy_substring(char* str, int start, int end) {
    char* copied_str = (char*)allocate(sizeof(char)*(end - start + 1));
    int i;
    for (i = 0; i < end - start; ++i) {
        copied_str[i] = str[start + i];
    }
    copied_str[i] = '\0';
    return copied_str;
}

/* TODO: Add documentation */
char* concatenate_strings(char* first, char* second) {
    int i, len, first_len, second_len;
    char* concatenated_str;

    first_len = strlen(first);
    second_len = strlen(second);
    len = first_len + second_len;

    concatenated_str = (char*) allocate(sizeof(char) * (len + 1));

    for (i = 0; i < first_len; i++) {
        concatenated_str[i] = first[i];
    }

    for (i = 0; i < second_len; i++) {
        concatenated_str[i+first_len] = second[i];
    }

    concatenated_str[len]='\0';

    return concatenated_str;
}

/* TODO: Add documentation */
char* append_char_to_string(char* str, int c) {
    char *new_str;
    int i;
    new_str = (char*)allocate(sizeof(char) * (strlen(str) + 2));
    memset(new_str, '0', sizeof(char) * (strlen(str) + 2));
    for (i = 0; i < strlen(str) ; i++) {
        new_str[i] = str[i];
    }
    new_str[i++] = c + 0;
    new_str[i] = '\0';
    return new_str;
}

/* TODO: Add documentation */
char* get_value(Table_t t, char* key) {
    int i;
    for (i=0; i < t->number_of_pairs; i++) {
        if (!strcmp(t->pair_table[i]->key, key)) {
            return t->pair_table[i]->value;
        }
    }
    return NULL;
}

/* TODO: Add documentation */
void add_to_table(Table_t t, char* key, char* value) {
    Pair_t pair;
    pair = create_pair(key, value);
    t->pair_table[t->number_of_pairs++] = pair;
}

/* TODO: Add documentation */
void add_to_table_if_not_exists(Table_t t, char* key, char* value) {
    if (get_value(t, key)) {
        return;  /* TODO: Handle better */
    }
    add_to_table(t, key, value);
}