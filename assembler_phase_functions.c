#include "assembler_phase_functions.h"

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
LabelsLinkedList_t create_linked_labels_list() {
    LabelsLinkedList_t list = allocate(sizeof(LinkedLabelsList));
    list->head = NULL;
    list->tail = NULL;
    list->list_length = 0;
    return list;
}

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
    return node->next;
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

/* TODO: DELETE THIS */
void print_labels_list(LabelsLinkedList_t list) {
    LabelNode_t node;
    node = list->head;
    printf("Labels list has %d items: ", list->list_length);
    printf("Name\tType\tValue\n");
    while(node != NULL) {
        printf("%s\t%s\t%d\n", node->name, node->type, node->value);
        printf("------------------------\n");
        node = node->next;
    }
}

void print_assembler_phase(void) {
    printf("This is the assembler phase (printed by assembler phase functions)\n");
}

/* TODO: Add documentation */
int starts_with_label(char *line) {
    LinkedList_t split_line = split_string(line, ':');
    if (get_list_length(split_line) > 1)
        return TRUE;
    return FALSE;
}

/* TODO: Add documentation */
int is_data_storage(char *line){
    if (starts_with(line, DATA_PREFIX) || starts_with(line, STRING_PREFIX))  /* TODO: Maybe improve this */
        return TRUE;
    return FALSE;
}

/* TODO: Add documentation */
int is_extern_or_entry(char *line) {
    if (starts_with(line, EXTERN_PREFIX) || starts_with(line, ENTRY_PREFIX))   /* TODO: Maybe improve this */
        return TRUE;
    return FALSE;
}

/* TODO: Add documentation */
int is_extern(char *line) {
    if (starts_with(line, EXTERN_PREFIX))   /* TODO: Maybe improve this */
        return TRUE;
    return FALSE;
}

/* TODO: Add documentation */
void add_label(LabelsLinkedList_t labels_list, char *line, char *type, int value) {
    /* TODO: ERROR HANDLING - Check if labels exists already, and if so, error! */
    char *label_name = ""; /* TODO: Fix this */
    LinkedList_t split_line = split_string(line, SPACE);
    /* TODO: if there's time - change to switch case */
    if (StringsEqual(type, DATA_TYPE)) {
        label_name = get_node_value(get_head(split_line));
    } else if (StringsEqual(type,EXTERN_TYPE)) {
        /* TODO: ERROR HANDLING - If there's more than one, throw error! */
        label_name = get_node_value(get_tail(split_line));
    }
    add_to_labels_list(create_label_node(label_name, type, value), labels_list);
}
