#ifndef STRUCTURES_H /* Prevents recursive includes */
#define STRUCTURES_H

#include "stdio.h"
#include "utils.h"

#define LAST_ALLOCATION_INDEX 1999 /* TODO: Add documentation */
#define CURRENT_MAX_TABLE_SIZE 1000 /* TODO: Add documentation */

#define GetTailValue(LIST) get_node_value(get_tail(LIST)) /* TODO: Add documentation */
#define GetHeadValue(LIST) get_node_value(get_head(LIST)) /* TODO: Add documentation */

typedef struct Allocator *Allocator_t; /* TODO: Add documentation */
typedef struct Pair *Pair_t; /* Structure containing key-value pairs */
typedef struct Table *Table_t; /* Dictionary-like object, holds key-value pairs */
typedef struct Node *Node_t; /* Represents a node in a strings linked list. */
typedef struct LinkedList *LinkedList_t; /* A strings linked list */
typedef struct LabelNode *LabelNode_t; /* Represents a node in a labels linked list. */
typedef struct LinkedLabelsList *LabelsLinkedList_t; /* A labels linked list */
typedef struct CommandNode *CommandNode_t; /* Represents a node in a commands linked list. */
typedef struct LinkedCommandList *LinkedCommandList_t; /* A commands linked list */

extern Allocator_t global_allocator; /* Global variable used to allocate memory throughout the program */

/* Allocator methods */
Allocator_t create_allocator(); /* TODO: Add documentation */
void* allocate(int size_of); /* TODO: Add documentation */
void free_all(); /* TODO: Add documentation */
void free_all_and_allocator(); /* TODO: Add documentation */

/* Pair methods */

/*  Gets two string (one representing key and the other representing value)
    Creates a pair object out of them.
    INPUT:  key     - a string, the pair's key.
            value   - a string, the pair's value.
    OUTPUT: pair object with the given key and value.
*/
Pair_t create_pair(char* key, char* value);

/*  Gets a pair object and returns the string of the key of that pair
    INPUT:  p - a Pair_t struct.
    OUTPUT: The key field of the given pair.
*/
char* get_pair_key(Pair_t p);

/*  Gets a pair object and returns the string of the value of that pair
    INPUT:  p - a Pair_t struct.
    OUTPUT: The value field of the given pair.
*/
char* get_pair_value(Pair_t p);

void print_pair(Pair_t p); /* TODO: delete this */

/* Table methods */

/*  Creates an empty table object.
    INPUT:  This function doesn't have an input.
    OUTPUT: an empty table object.
*/
Table_t create_table();

/*  Gets a table, a key (string) and a value (string),
    Adds the key and value as a pair to the table.
    INPUT:  t       - a table object.
            key     - a string representing the desired key.
            value   - a string representing the desired value.
    OUTPUT: This function doesn't return anything.
*/
void add_to_table(Table_t t, char* key, char* value);

/*  Gets a table and a string representing a key.
    Searches the table and returns the value in that key's pair.
    If there is no pair with that key in the table, the function returns NULL.
    INPUT:  t   - a table object.
            key - a string representing the desired key.
    OUTPUT: The value (string) that is paired with the given key.
            If the key is not in the table, returns NULL.
*/
char* get_value_from_table(Table_t t, char* key);

/*  Gets a table, a key (string) and a value (string),
    If the table doesn't contain such key already,
    The function adds the key and value as a pair to the table.
    INPUT:  t       - a table object.
            key     - a string representing the desired key
            value   - a string representing the desired value
    OUTPUT: This function doesn't return anything
*/
void add_to_table_if_not_exists(Table_t t, char* key, char* value);

/*  Gets a table object and returns the amount of pairs it hold.
    INPUT:  t - a table object.
    OUTPUT: An int representing the amount of pairs in t.
*/
int get_number_of_pairs(Table_t t);

/*  Gets a table object and returns its pairs array.
    INPUT:  t - a table object.
    OUTPUT: An array of pairs representing all the pairs in the table.
*/
Pair_t* get_pair_array(Table_t t);

void print_table(Table_t t); /* TODO: delete this */

/* Node methods */

/*  Gets a string representing a value.
    Creates a node with this string as its value and a NULL next.
    INPUT:  value - the value for the new node.
    OUTPUT: A node object with the given value.
*/
Node_t create_node(char* value);

/*  Gets a node object and returns the string of the value of that node.
    INPUT:  node - a Node_t struct.
    OUTPUT: The value field of the given node.
*/
char* get_node_value(Node_t node);

/*  Gets a node object and returns the node (or NULL) in the next field of that node.
    INPUT:  node - a Node_t struct.
    OUTPUT: The next field of the given node.
*/
Node_t get_next_node(Node_t node);

/* LinkedList methods */

/*  Creates an empty linked list object.
    INPUT:  This function doesn't have an input.
    OUTPUT: An empty linked list object.
*/
LinkedList_t create_linked_list();

/*  Gets a linked list, and a node.
    Adds that node as the next node of the list.
    INPUT:  node    - a node object to be added to the list.
            list    - the list to add the node to.
    OUTPUT: This function doesn't return anything.
*/
void add_node_to_list(Node_t node, LinkedList_t list);

/*  Gets a linked list object and returns that list's current length.
    INPUT:  list - a linked list object.
    OUTPUT: An int representing the length of that list.
*/
int get_list_length(LinkedList_t list);

/*  Gets a linked list object.
    Returns a string of all the items in that list concatenated without any separators.
    INPUT:  list - a linked list object.
    OUTPUT: A string representing all the contents of that list.
*/
char* get_list_as_string(LinkedList_t list);

/*  Gets a linked list object and returns the first node on that list.
    INPUT:  list - a LinkedList_t struct.
    OUTPUT: The head of that list.
*/
Node_t get_head(LinkedList_t list);

/*  Gets a linked list object and returns the last node on that list.
    INPUT:  list - a LinkedList_t struct.
    OUTPUT: The tail of that list.
*/
Node_t get_tail(LinkedList_t list);

void print_list(LinkedList_t list); /* TODO: delete this */

/* LabelNode methods */

/*  Gets two strings representing a name and a type, and an int representing a value.
    Creates a label node with the strings as the label name and type,
    the int as the value and a NULL next.
    INPUT:  name    - a string representing label name.
            type    - a string representing the label type.
            value   - an int representing the label value.
    OUTPUT: A label node object with the given content.
*/
LabelNode_t create_label_node(char* name, char* type, int value);

/*  Gets a label node object and returns the string of the type of that node.
    INPUT:  node - a LabelNode_t struct.
    OUTPUT: The type field of the given node.
*/
char* get_label_node_type(LabelNode_t node);

/*  Gets a label node object and returns the int of the value of that node.
    INPUT:  node - a LabelNode_t struct.
    OUTPUT: The value field of the given node.
*/
int get_label_node_value(LabelNode_t node);

/*  Gets a label node object and returns the string of the name of that node.
    INPUT:  node - a LabelNode_t struct.
    OUTPUT: The name field of the given node.
*/
char* get_label_node_name(LabelNode_t node);

/*  Gets a label node object and returns the label node (or NULL) in the next field of that label node.
    INPUT:  node - a LabelNode_t struct.
    OUTPUT: The next field of the given label node.
*/
LabelNode_t get_next_label_node(LabelNode_t node);

/*  Gets a label node object and an int representing a label value.
    Sets the given node's value to be the given int.
    INPUT:  node    - a LabelNode_t struct.
            new_val - an int representing the new value of the given node.
    OUTPUT: This function doesn't return anything
*/
void set_label_node_value(LabelNode_t node, int new_val);

/*  Gets a label node object and a string representing a label type.
    Sets the given node's type to be the given string.
    INPUT:  node        - a LabelNode_t struct.
            new_type    - a string representing the new type of the given node.
    OUTPUT: This function doesn't return anything
*/
void set_label_node_type(LabelNode_t node, char *new_type);

/* LinkedLabelsList methods */

/*  Creates an empty linked labels list object.
    INPUT:  This function doesn't have an input.
    OUTPUT: An empty linked labels list object.
*/
LabelsLinkedList_t create_linked_labels_list();

/*  Gets a linked labels list, and a label node.
    Adds that label node as the next node of the list.
    INPUT:  node    - a label node object to be added to the list.
            list    - the list to add the label node to.
    OUTPUT: This function doesn't return anything.
*/
void add_to_labels_list(LabelNode_t node, LabelsLinkedList_t list);

/*  Gets a linked labels list object and returns that list's current length.
    INPUT:  list - a linked labels list object.
    OUTPUT: An int representing the length of that list.
*/
int get_labels_list_length(LabelsLinkedList_t list);

/*  Gets a linked labels list object and returns the first label node on that list.
    INPUT:  list - a LabelsLinkedList_t struct.
    OUTPUT: The head of that list.
*/
LabelNode_t get_labels_list_head(LabelsLinkedList_t list);

/*  Gets a linked labels list and a string representing a label name.
    Searches the list and returns the label node with that name.
    If there is no node with that name in the list, the function returns NULL.
    INPUT:  list    - a linked labels list object.
            label   - a string representing the desired label name.
    OUTPUT: The label node object with the given label name.
            If there isn't a node in the list with that name, returns NULL.
*/
LabelNode_t search_labels_list(LabelsLinkedList_t list, char* label);

void print_labels_list(LabelsLinkedList_t list); /* TODO: delete this */

/* CommandNode methods */

/*  Gets four strings representing a command name, code and allowed source and destination operand types.
    Also gets a string representing the amount of operands this command should have.
    Creates a command node with the strings and its as its contents and a NULL next.
    INPUT:  command                     - a string representing a command.
            code                        - a string representing a command code.
            operands                    - an int representing the amount of operands the command should have.
            source_operand_types        - a string representing the allowed source operand types.
            destination_operand_types   - a string representing the allowed destination operand types.
    OUTPUT: A command node object with the given content.
*/
CommandNode_t create_command_node(char* command, char* code, int operands, char* source_operand_types, char* destination_operand_types);

/*  Gets a command node object and returns the string of the code of that node.
    INPUT:  node - a CommandNode_t struct.
    OUTPUT: The code field of the given node.
*/
char* get_command_node_code(CommandNode_t node);

/*  Gets a command node object and returns the string of the command of that node.
    INPUT:  node - a CommandNode_t struct.
    OUTPUT: The command field of the given node.
*/
char* get_command_node_command(CommandNode_t node);

/*  Gets a command node object and returns the int of the operands of that node.
    INPUT:  node - a CommandNode_t struct.
    OUTPUT: The operands field of the given node.
*/
int get_command_node_operands(CommandNode_t node);

/*  Gets a command node object and returns the string of the allowed source operands of that node.
    INPUT:  node - a CommandNode_t struct.
    OUTPUT: The source_operand_types field of the given node.
*/
char* get_command_node_source_operand_types(CommandNode_t node);

/*  Gets a command node object and returns the string of the allowed destination operands of that node.
    INPUT:  node - a CommandNode_t struct.
    OUTPUT: The destination_operand_types field of the given node.
*/
char* get_command_node_destination_operand_types(CommandNode_t node);

/*  Gets a command node object and returns the command node (or NULL) in the next field of that command node.
    INPUT:  node - a CommandNode_t struct.
    OUTPUT: The next field of the given command node.
*/
CommandNode_t get_next_command_node(CommandNode_t node);

void print_commands_node(CommandNode_t node); /* TODO: delete this */

/* LinkedCommandList methods */

/*  Creates an empty linked commands list object.
    INPUT:  This function doesn't have an input.
    OUTPUT: An empty linked commands list object.
*/
LinkedCommandList_t create_linked_command_list();

/*  Gets a linked commands list, and a command node.
    Adds that command node as the next node of the list.
    INPUT:  node    - a command node object to be added to the list.
            list    - the list to add the command node to.
    OUTPUT: This function doesn't return anything.
*/
void add_to_commands_list(CommandNode_t node, LinkedCommandList_t list);

/*  Gets a linked commands list object and returns that list's current length.
    INPUT:  list - a linked commands list object.
    OUTPUT: An int representing the length of that list.
*/
int get_commands_list_length(LinkedCommandList_t list);

/*  Gets a linked commands list object and returns the first command node on that list.
    INPUT:  list - a LinkedCommandList_t struct.
    OUTPUT: The head of that list.
*/
CommandNode_t get_commands_list_head(LinkedCommandList_t list);

/*  Gets a linked commands list and a string representing a command name.
    Searches the list and returns the command node with that name.
    If there is no node with that command name in the list, the function returns NULL.
    INPUT:  list    - a linked commands list object.
            command   - a string representing the desired command name.
    OUTPUT: The command node object with the given command name.
            If there isn't a node in the list with that name, returns NULL.
*/
CommandNode_t search_command_list(LinkedCommandList_t list, char* command);

void print_commands_list(LinkedCommandList_t list); /* TODO: delete this */

#endif
