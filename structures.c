#include "structures.h"

/* Structures struct definitions */

/* TODO: Add documentation */
struct Allocator {
    int number_of_allocated_elements;
    void* ptr_list[LAST_ALLOCATION_INDEX+1];
} Allocator;

/*  Represents pairs of key and value
    Helps to create dictionary-like objects
*/
struct Pair{
    char* key;
    char* value;
} Pair;

/*  Dictionary-like object
    Holds a list of key-value pairs
*/
struct Table{
    int current_table_size;
    int number_of_pairs;
    Pair_t pair_table[CURRENT_MAX_TABLE_SIZE];
} Table;

/*  Represents a node in a strings linked list.
    value - the string itself
    next - the next node in the list
*/
struct Node{
    char* value;
    Node_t next;
} Node;

/*  A strings linked list
    Head - start of list
    Tail - end of list
    list_length - amount of strings in the list
*/
struct LinkedList {
    Node_t head;
    Node_t tail;
    int list_length;
} LinkedList;

/*  Represents a node in a labels linked list.
    name - the label's name
    type - the label's type
    value - the label's value
    next - the next label node in the list
*/
struct LabelNode{
    char* name;
    char* type;
    int value;
    LabelNode_t next;
} LabelNode;

/*  A labels linked list
    Head - start of list
    Tail - end of list
    list_length - amount of strings in the list
*/
struct LinkedLabelsList {
    LabelNode_t head;
    LabelNode_t tail;
    int list_length;
} LinkedLabelsList;

/*  Represents a node in a commands linked list.
    command - the command's name
    code - the command's opt code
    operands - amount of operands the command should have
    source_operand_types - allowed source operand types
    destination_operand_types - allowed destination operand types
    next - the next command node in the list
*/
struct CommandNode{
    char* command;
    char* code;
    int operands;
    char* source_operand_types;
    char* destination_operand_types;
    CommandNode_t next;
} CommandNode;

/*  A commands linked list
    Head - start of list
    Tail - end of list
    list_length - amount of strings in the list
*/
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

/*  Creates a pair object out of the given key (string) and value (string).
    Allocates the required memory and stores a copy of those string in the relevant fields
    of the newly created Pair_t struct.
*/
Pair_t create_pair(char* key, char* value) {
    Pair_t pair = allocate(sizeof(Pair));
    pair->key = copy_string(key);
    pair->value = copy_string(value);
    return pair;
}

/*  Gets a Pair_t struct.
    Returns the key field of that pair.
*/
char* get_pair_key(Pair_t p) {
    return p->key;
}

/*  Gets a Pair_t struct.
    Returns the value field of that pair.
*/
char* get_pair_value(Pair_t p) {
    return p->value;
}

/* TODO: delete this */
void print_pair(Pair_t p) {
    printf("%s -> %s\n", p->key, p->value);
}

/* Table methods */

/*  Creates an empty table object.
    Allocates the required memory, sets the table size and sets the number of pairs to 0.
*/
Table_t create_table() {
    Table_t table = allocate(sizeof(Table));
    table->current_table_size = CURRENT_MAX_TABLE_SIZE;
    table->number_of_pairs = 0;
    return table;
}

/*  Gets a table object, a string representing a key and a string representing a value.
    Creates a pair out of the given key and value, using the create_pair function.
    Then, adds that pair to the given table.
*/
void add_to_table(Table_t t, char* key, char* value) {
    Pair_t pair;
    pair = create_pair(key, value);
    t->pair_table[t->number_of_pairs++] = pair;
}

/*  Gets a table object and a string representing a key.
    Using a for loop, goes through the pairs in the given table and checks if they have the given key.
    If so, return the value of that pair.
    If such key is not found, return NULL.
*/
char* get_value_from_table(Table_t t, char* key) {
    int i;
    for (i=0; i < t->number_of_pairs; i++) {
        if (!strcmp(t->pair_table[i]->key, key)) {
            return t->pair_table[i]->value;
        }
    }
    return NULL;
}

/*  Gets a table object, a string representing a key and a string representing a value.
    Using the get_value_from_table function, checks if the key already exists in the given table.
    If not, creates a pair out of the given key and value, using the create_pair function
    and adds that pair to the given table.
*/
void add_to_table_if_not_exists(Table_t t, char* key, char* value) {
    if (get_value_from_table(t, key)) {
        return;
    }
    add_to_table(t, key, value);
}

/*  Gets a table object.
    Returns the number of pairs it currently hold.
*/
int get_number_of_pairs(Table_t t) {
    return t->number_of_pairs;
}

/*  Gets a table object.
    Returns the array of pairs that table holds.
*/
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

/*  Gets a string representing a value.
    Creates a new node object with the given string as its value and NULL as its next.
    Returns the newly created node.
*/
Node_t create_node(char* value) {
    Node_t node = allocate(sizeof(Node));
    node->value = value;
    node->next = NULL;
    return node;
}

/*  Gets a Node_t struct.
    Returns the value field of that node.
*/
char* get_node_value(Node_t node) {
    return node->value;
}

/*  Gets a Node_t struct.
    Returns the next field of that node.
*/
Node_t get_next_node(Node_t node) {
    return node->next;
}

/* LinkedList methods */

/*  Creates an empty linked list object.
    Allocates the required memory,
    Sets the list head and tail to NULL
    And sets the list's length to 0.
*/
LinkedList_t create_linked_list() {
    LinkedList_t list = allocate(sizeof(LinkedList));
    list->head = NULL;
    list->tail = NULL;
    list->list_length = 0;
    return list;
}

/*  Gets a linked list object, and a node object.
    If the list is empty, the given node is set as the list's head.
    Otherwise, it is set as the list's tail's next.
    Either way, the given node is set as the list's tail.
    Also, raises the value of the list length by one.
*/
void add_node_to_list(Node_t node, LinkedList_t list) {
    if (list->list_length == 0) {
        list->head = node;
    } else {
        list->tail->next = node;
    }
    list->tail = node;
    list->list_length++;
}

/*  Gets a linked list object.
    Returns the current list length.
*/
int get_list_length(LinkedList_t list) {
    return list->list_length;
}

/*  Gets a linked list object.
    Goes through it via a for lop and concatenates each value to all of its previous values (using concatenate_strings)
    Returns the concatenated string.
*/
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

/*  Gets a LinkedList_t struct.
    Returns the head field of that list.
*/
Node_t get_head(LinkedList_t list) {
    return list->head;
}

/*  Gets a LinkedList_t struct.
    Returns the tail field of that list.
*/Node_t get_tail(LinkedList_t list) {
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

/*  Gets two strings representing name and type, and an int representing a value.
    Creates a new label node object with the given strings and int as its contents, and NULL as its next.
    Returns the newly created label node.
*/
LabelNode_t create_label_node(char* name, char* type, int value) {
    LabelNode_t node = allocate(sizeof(LabelNode));
    node->name = name;
    node->type = type;
    node->value = value;
    node->next = NULL;
    return node;
}

/*  Gets a LabelNode_t struct.
    Returns the type field of that label node.
*/
char* get_label_node_type(LabelNode_t node) {
    return node->type;
}

/*  Gets a LabelNode_t struct.
    Returns the value field of that label node.
*/
int get_label_node_value(LabelNode_t node) {
    return node->value;
}

/*  Gets a LabelNode_t struct.
    Returns the name field of that label node.
*/
char* get_label_node_name(LabelNode_t node) {
    return node->name;
}

/*  Gets a LabelNode_t struct.
    Returns the next field of that label node.
*/
LabelNode_t get_next_label_node(LabelNode_t node) {
    if (node == NULL)
        return NULL;
    return node->next;
}

/*  Gets a LabelNode_t struct and an int.
    Sets the node's value to be the given int.
*/
void set_label_node_value(LabelNode_t node, int new_val) {
    node->value = new_val;
}

/*  Gets a LabelNode_t struct and a string.
    Sets the node's type to be the given string.
*/
void set_label_node_type(LabelNode_t node, char *new_type) {
    node->type = new_type;
}

/* LinkedLabelsList methods */


/*  Creates an empty linked labels list object.
    Allocates the required memory,
    Sets the list head and tail to NULL
    And sets the list's length to 0.
*/
LabelsLinkedList_t create_linked_labels_list() {
    LabelsLinkedList_t list = allocate(sizeof(LinkedLabelsList));
    list->head = NULL;
    list->tail = NULL;
    list->list_length = 0;
    return list;
}


/*  Gets a linked labels list object, and a label node object.
    If the list is empty, the given label node is set as the list's head.
    Otherwise, it is set as the list's tail's next.
    Either way, the given label node is set as the list's tail.
    Also, raises the value of the list length by one.
*/
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

/*  Gets a linked labels list object.
    Returns the current list length.
*/
int get_labels_list_length(LabelsLinkedList_t list) {
    return list->list_length;
}

/*  Gets a LabelsLinkedList_t struct.
    Returns the head field of that list.
*/
LabelNode_t get_labels_list_head(LabelsLinkedList_t list) {
    return list->head;
}

/*  Gets a linked labels list object and a string representing a label name.
    Using a while loop, goes through the labels in the given list and checks if they have the given name.
    If so, return that label node.
    If such label is not found, return NULL.
*/
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

/*  Gets some strings representing a command, its code, allowed source and destination operands type
    And an int representing the amount of operands the command should have.
    Creates a new command node object with the given strings and int as its contents, and NULL as its next.
    Returns the newly created command node.
*/
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

/*  Gets a CommandNode_t struct.
    Returns the code field of that command node.
*/
char* get_command_node_code(CommandNode_t node) {
    return node->code;
}

/*  Gets a CommandNode_t struct.
    Returns the command field of that command node.
*/
char* get_command_node_command(CommandNode_t node) {
    return node->command;
}

/*  Gets a CommandNode_t struct.
    Returns the operands field of that command node.
*/
int get_command_node_operands(CommandNode_t node) {
    return node->operands;
}

/*  Gets a CommandNode_t struct.
    Returns the source_operand_types field of that command node.
*/
char* get_command_node_source_operand_types(CommandNode_t node) {
    return node->source_operand_types;
}

/*  Gets a CommandNode_t struct.
    Returns the destination_operand_types field of that command node.
*/
char* get_command_node_destination_operand_types(CommandNode_t node) {
    return node->destination_operand_types;
}

/*  Gets a CommandNode_t struct.
    Returns the next field of that command node.
*/
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

/*  Creates an empty linked commands list object.
    Allocates the required memory,
    Sets the list head and tail to NULL
    And sets the list's length to 0.
*/
LinkedCommandList_t create_linked_command_list() {
    LinkedCommandList_t list = allocate(sizeof(LinkedLabelsList));
    list->head = NULL;
    list->tail = NULL;
    list->list_length = 0;
    return list;
}

/*  Gets a linked commands list object, and a command node object.
    If the list is empty, the given command node is set as the list's head.
    Otherwise, it is set as the list's tail's next.
    Either way, the given command node is set as the list's tail.
    Also, raises the value of the list length by one.
*/
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

/*  Gets a linked commands list object.
    Returns the current list length.
*/
int get_commands_list_length(LinkedCommandList_t list) {
    return list->list_length;
}

/*  Gets a LinkedCommandList_t struct.
    Returns the head field of that list.
*/
CommandNode_t get_commands_list_head(LinkedCommandList_t list) {
    return list->head;
}

/*  Gets a linked commands list object and a string representing a command name.
    Using a while loop, goes through the commands in the given list and checks if they have the given name.
    If so, return that command node.
    If such command is not found, return NULL.
*/
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
