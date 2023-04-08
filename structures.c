#include "structures.h"

/* Structures struct definition */
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
struct LabelNode{
    char* name;
    char* type;
    int value;
    LabelNode_t next;
} LabelNode;

/* TODO: Add documentation */
struct LinkedLabelsList {
    LabelNode_t head;
    LabelNode_t tail;
    int list_length;
} LinkedLabelsList;

/* TODO: Add documentation */
struct CommandNode{
    char* command;
    char* code;
    int operands;
    char* source_operand_types;
    char* destination_operand_types;
    CommandNode_t next;
} CommandNode;

/* TODO: Add documentation */
struct LinkedCommandList {
    CommandNode_t head;
    CommandNode_t tail;
    int list_length;
} LinkedCommandList;

/* Structure methods */

/* Allocator methods */
/* TODO: Add documentation */
Allocator_t create_allocator() {
    Allocator_t allocator = (Allocator_t)malloc(sizeof(Allocator));
    memset(allocator->ptr_list, 0, sizeof(void*) * (LAST_ALLOCATION_INDEX + 1));
    allocator->ptr_list[LAST_ALLOCATION_INDEX] = allocator;
    allocator->number_of_allocated_elements = 0;
    return allocator;
}

/* TODO: Add documentation */
void* allocate(int size_of) {
    void* new_ptr = malloc(size_of);
    int current_free_allocation_index = global_allocator->number_of_allocated_elements++;
    if (current_free_allocation_index >= LAST_ALLOCATION_INDEX) {
        printf("ERROR: No free allocation space!\n");
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

/* Pair methods */
/* TODO: Add documentation */
Pair_t create_pair(char* key, char* value) {
    Pair_t pair = allocate(sizeof(Pair));
    pair->key = copy_string(key);
    pair->value = copy_string(value);
    return pair;
}

/* TODO: Add documentation */
char* get_pair_key(Pair_t p) {
    return p->key;
}

/* TODO: Add documentation */
char* get_pair_value(Pair_t p) {
    return p->value;
}

/* TODO: delete this */
void print_pair(Pair_t p) {
    printf("%s -> %s\n", p->key, p->value);
}

/* Table methods */
/* TODO: Add documentation */
Table_t create_table() {
    Table_t table = allocate(sizeof(Table));
    table->current_table_size = CURRENT_MAX_TABLE_SIZE;
    table->number_of_pairs = 0;
    return table;
}

/* TODO: Add documentation */
void add_to_table(Table_t t, char* key, char* value) {
    Pair_t pair;
    pair = create_pair(key, value);
    t->pair_table[t->number_of_pairs++] = pair;
}

/* TODO: Add documentation */
void add_to_table_if_not_exists(Table_t t, char* key, char* value) {
    if (get_value_from_table(t, key)) {
        return;  /* TODO: Handle better */
    }
    add_to_table(t, key, value);
}

/* TODO: Add documentation */
char* get_value_from_table(Table_t t, char* key) {
    int i;
    for (i=0; i < t->number_of_pairs; i++) {
        if (!strcmp(t->pair_table[i]->key, key)) {
            return t->pair_table[i]->value;
        }
    }
    return NULL;
}

/* TODO: Add documentation */
int get_number_of_pairs(Table_t t) {
    return t->number_of_pairs;
}

/* TODO: Add documentation */
Pair_t* get_pair_array(Table_t t) {
    return t->pair_table;
}


/* TODO: delete this */
void print_table(Table_t t) {
    int i;
    for (i=0; i < t->number_of_pairs; i++) {
        print_pair(t->pair_table[i]);
    }
}

/* Node methods */
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

/* LinkedList methods */
/* TODO: Add documentation */
LinkedList_t create_linked_list() {
    LinkedList_t list = allocate(sizeof(LinkedList));
    list->head = NULL;
    list->tail = NULL;
    list->list_length = 0;
    return list;
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

/* TODO: Add documentation */
int get_list_length(LinkedList_t list) {
    return list->list_length;
}

/* TODO: Add documentation */
char* get_list_as_string(LinkedList_t list) {
    Node_t node;
    int i;
    char* list_as_string = "";
    node = list->head;
    for (i = 0; i < list->list_length; i++) {
        list_as_string = (concatenate_strings(list_as_string, node->value));
        node = node->next;
    }
    return list_as_string;
}

/* TODO: Add documentation */
Node_t get_head(LinkedList_t list) {
    return list->head;
}

/* TODO: Add documentation */
Node_t get_tail(LinkedList_t list) {
    return list->tail;
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

/* LabelNode methods */
/* TODO: Add documentation */
LabelNode_t create_label_node(char* name, char* type, int value) {
    LabelNode_t node = allocate(sizeof(LabelNode));
    node->name = name;
    node->type = type;
    node->value = value;
    node->next = NULL;
    return node;
}

/* TODO: Add documentation */
char* get_label_node_type(LabelNode_t node) {
    return node->type;
}

/* TODO: Add documentation */
int get_label_node_value(LabelNode_t node) {
    return node->value;
}

/* TODO: Add documentation */
char* get_label_node_name(LabelNode_t node) {
    return node->name;
}

/* TODO: Add documentation */
LabelNode_t get_next_label_node(LabelNode_t node) {
    if (node == NULL)
        return NULL;
    return node->next;
}

/* TODO: Add documentation */
void set_label_node_value(LabelNode_t node, int new_val) {
    node->value = new_val;
}

/* TODO: Add documentation */
void set_label_node_type(LabelNode_t node, char *new_type) {
    node->type = new_type;
}

/* LinkedLabelsList methods */
/* TODO: Add documentation */
LabelsLinkedList_t create_linked_labels_list() {
    LabelsLinkedList_t list = allocate(sizeof(LinkedLabelsList));
    list->head = NULL;
    list->tail = NULL;
    list->list_length = 0;
    return list;
}


/* TODO: Add documentation */
void add_to_labels_list(LabelNode_t node, LabelsLinkedList_t list) {
    if (list->list_length == 0) {
        list->head = node;
        list->tail = node;
    } else {
        list->tail->next = node;
        list->tail = node;
    }
    list->list_length++;
}

/* TODO: Add documentation */
int get_labels_list_length(LabelsLinkedList_t list) {
    return list->list_length;
}

/* TODO: Add documentation */
LabelNode_t get_labels_list_head(LabelsLinkedList_t list) {
    return list->head;
}

/* TODO: Add documentation */
LabelNode_t search_labels_list(LabelsLinkedList_t list, char* label) {
    LabelNode_t curr = get_labels_list_head(list);

    while(curr != NULL) {
        if (!strcmp(get_label_node_name(curr), label)) {
            return curr;
        }
        curr = get_next_label_node(curr);
    }
    return NULL;
}

/* TODO: DELETE THIS */
void print_labels_list(LabelsLinkedList_t list) {
    LabelNode_t node;
    node = list->head;
    printf("Labels list has %d items: \n", list->list_length);
    printf("Name\tType\tValue\n");
    printf("------------------------\n");
    while(node != NULL) {
        printf("%s\t%s\t%d\n", node->name, node->type, node->value);
        printf("------------------------\n");
        node = node->next;
    }
}

/* CommandNode methods */
/* TODO: Add documentation */
CommandNode_t create_command_node(char* command, char* code, int operands, char* source_operand_types, char* destination_operand_types) {
    CommandNode_t node = allocate(sizeof(CommandNode));

    node->command = command;
    node->code = code;
    node->operands = operands;
    node-> source_operand_types = source_operand_types;
    node->destination_operand_types = destination_operand_types;
    node->next = NULL;

    return node;
}

/* TODO: Add documentation */
char* get_command_node_code(CommandNode_t node) {
    return node->code;
}

/* TODO: Add documentation */
char* get_command_node_command(CommandNode_t node) {
    return node->command;
}

/* TODO: Add documentation */
int get_command_node_operands(CommandNode_t node) {
    return node->operands;
}

/* TODO: Add documentation */
char* get_command_node_source_operand_types(CommandNode_t node) {
    return node->source_operand_types;
}

/* TODO: Add documentation */
char* get_command_node_destination_operand_types(CommandNode_t node) {
    return node->destination_operand_types;
}

/* TODO: Add documentation */
CommandNode_t get_next_command_node(CommandNode_t node) {
    return node->next;
}

/* TODO: delete this */
void print_commands_node(CommandNode_t node) {
    if (node == NULL) {
        printf("NULL\n");
        return;
    }

    printf("command: %s\n", get_command_node_command(node));
    printf("code: %s\n", get_command_node_code(node));
    printf("operands: %d\n", get_command_node_operands(node));
    printf("source_operand_types: %s\n", get_command_node_source_operand_types(node));
    printf("destination_operand_types: %s\n", get_command_node_destination_operand_types(node));
}

/* LinkedCommandList methods */
/* TODO: Add documentation */
LinkedCommandList_t create_linked_command_list() {
    LinkedCommandList_t list = allocate(sizeof(LinkedLabelsList));
    list->head = NULL;
    list->tail = NULL;
    list->list_length = 0;
    return list;
}

/* TODO: Add documentation */
void add_to_commands_list(CommandNode_t node, LinkedCommandList_t list) {
    if (list->list_length == 0) {
        list->head = node;
        list->tail = node;
    } else {
        list->tail->next = node;
        list->tail = node;
    }
    list->list_length++;
}

/* TODO: Add documentation */
int get_commands_list_length(LinkedCommandList_t list) {
    return list->list_length;
}

/* TODO: Add documentation */
CommandNode_t get_commands_list_head(LinkedCommandList_t list) {
    return list->head;
}

/* TODO: Add documentation */
CommandNode_t search_command_list(LinkedCommandList_t list, char* command) {
    CommandNode_t curr = get_commands_list_head(list);

    while(curr != NULL) {
        if (!strcmp(get_command_node_command(curr), command)) {
            return curr;
        }
        curr = get_next_command_node(curr);
    }
    return NULL;
}

/* TODO: delete this */
void print_commands_list(LinkedCommandList_t list) {
    CommandNode_t node;
    node = get_commands_list_head(list);
    printf("Commands list has %d items: \n", get_commands_list_length(list));
    printf("Command\tcode\toperands\tsource_operand_types\tdestination_operand_types\n");
    printf("------------------------\n");

    while(node != NULL) {
        printf("%s\t%s\t%d\t%s\t%s\n", get_command_node_command(node), get_command_node_code(node),
               get_command_node_operands(node), get_command_node_source_operand_types(node),
               get_command_node_destination_operand_types((node)));
        printf("------------------------\n");
        node = get_next_command_node(node);
    }

}