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
void set_label_node_value(LabelNode_t node, int new_val) {
    node->value = new_val;
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
    printf("Labels list has %d items: \n", list->list_length);
    printf("Name\tType\tValue\n");
    printf("------------------------\n");
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
Table_t create_action_names_table() {
    Table_t actions_names_table;

    actions_names_table = create_table();
    add_to_table(actions_names_table, "mov", "0");
    add_to_table(actions_names_table, "cmp", "1");
    add_to_table(actions_names_table, "add", "2");
    add_to_table(actions_names_table, "sub", "3");
    add_to_table(actions_names_table, "not", "4");
    add_to_table(actions_names_table, "clr", "5");
    add_to_table(actions_names_table, "lea", "6");
    add_to_table(actions_names_table, "inc", "7");
    add_to_table(actions_names_table, "dec", "8");
    add_to_table(actions_names_table, "jmp", "9");
    add_to_table(actions_names_table, "bne", "10");
    add_to_table(actions_names_table, "red", "11");
    add_to_table(actions_names_table, "prn", "12");
    add_to_table(actions_names_table, "jsr", "13");
    add_to_table(actions_names_table, "rts", "14");
    add_to_table(actions_names_table, "stop", "15");

    return actions_names_table;
}

/* TODO: Add documentation */
void handle_error(LinkedList_t error_list, char *error_message) {
    /* TODO: Might not need a list if we print as we go, maybe a flag is enough and this whole thing is redundant */
    add_to_list(create_node(error_message), error_list);
    printf("ERROR: %s\n", error_message);
}

/* TODO: Add documentation */
int starts_with_label(LinkedList_t split_line) {
    /* TODO: Ensure really a label and not just string thingie with : in it */
    /* TODO: Ensure no space between label and :!! */
    if (get_list_length(split_line) > 1) {
        return TRUE;
    }
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
void add_label(LabelsLinkedList_t labels_list, LinkedList_t split_line, char *type, int value) {
    /* TODO: ERROR HANDLING - Check if labels exists already, and if so, error! */
    char *label_name = ""; /* TODO: Fix this */
    /* TODO: if there's time - change to switch case */
    if (StringsEqual(type, DATA_TYPE) || StringsEqual(type, CODE_TYPE)) {
        label_name = get_node_value(get_head(split_line));
    } else if (StringsEqual(type,EXTERN_TYPE)) {
        /* TODO: ERROR HANDLING - If there's more than one, throw error! */
        label_name = get_node_value(get_tail(split_line));
    }
    add_to_labels_list(create_label_node(label_name, type, value), labels_list);
}

/* TODO: Add documentation */
void update_symbol_table(LabelsLinkedList_t symbol_table, int ic) {
    LabelNode_t current_label = get_labels_list_head(symbol_table);

    while ((current_label = get_next_label_node(current_label)) != NULL) {
        if (StringsEqual(get_label_node_type(current_label), DATA_TYPE)) {
            set_label_node_value(current_label, get_label_node_value(current_label) + ic);
        }
    }
}

/* TODO: Rewrite this */
/* TODO: Add documentation (use my_rotate as reference, maman 11 I think) */
char* dec_to_binary(int num) {
    char binary_array[BITS_AMOUNT];
    int i, num_binary_length = 0, temp;

    for (i = 0; i < BITS_AMOUNT; i++) {
        binary_array[i] = '0';
    }

    i = num;

    while (i != 0){
        num_binary_length ++;
        i /= 2;
    }

    for (i = num_binary_length; i > 0; i--){
        temp = num / pow(2, i - 1);
        binary_array[BITS_AMOUNT - i] = '0' + (temp % 2);
    }

    return copy_string(binary_array);
}

/* TODO: Rewrite this */
/* TODO: Add documentation (use my_rotate as reference, maman 11 I think) */
/* 2’s complement, 14 bits */
char* binary(char *string) {
    char *binary_array;
    int num, i, negative = FALSE;

    if (string[0] == MINUS) {
        negative = TRUE;
        num = atoi(copy_substring(string, 1, strlen(string)));
    } else {
        num = atoi(string);
    }

    binary_array = dec_to_binary(num);

    if (is(negative)) {
        for (i = 0; i < BITS_AMOUNT; i ++) {
            binary_array[i] = binary_array[i] == '0' ? '1' : '0';
        }

        for (i = BITS_AMOUNT - 1; i >= 0; i--) {
            if (binary_array[i] == '1')
                binary_array[i] = '0';
            else {
                binary_array[i] = '1';
                break;
            }
        }
    }

    return copy_string(binary_array);
}

/* TODO: Write this */
/* TODO: Add documentation */
int handle_data_type(char *line, LinkedList_t memory_list) {
    char *data, *curr_string;
    Node_t curr_node;
    LinkedList_t split_data;

    data = copy_substring(line, 5, strlen(line));

    if (!isSpace(data[0])) {
        /* TODO: ERROR HANDLING - this is an error! */
        return 0;
    }

    data = get_string_without_whitespaces(data);
    split_data = split_string(data, ',');
    curr_node = get_head(split_data);

    while (curr_node != NULL) {
        curr_string = get_node_value(curr_node);
        if (strlen(curr_string) == 0) {
            /* TODO: ERROR HANDLING - incorrect commas in data! */
            return 0;
        }
        add_to_list(create_node(binary(curr_string)) ,memory_list); /* TODO: Might separate to function? */
        curr_node = get_next_node(curr_node);
    }

    return get_list_length(split_data);
}

/* TODO: Write this */
/* TODO: Add documentation */
int handle_string_type(char *line, LinkedList_t memory_list) {
    char *data;
    int i;

    data = copy_substring(line, 7, strlen(line));

    if (!isSpace(data[0])) {
        /* TODO: ERROR HANDLING - this is an error! */
        return 0;
    }

    data = get_string_without_whitespaces(data);

    if (data[0] != '"' || data[strlen(data) - 1] != '"') {
        /* TODO: ERROR HANDLING - this is an error! */
        return 0;
    }

    for (i = 1; i < strlen(data) - 1; i++) {
        add_to_list(create_node(dec_to_binary(data[i])) ,memory_list); /* TODO: Might separate to function? */
    }

    add_to_list(create_node(dec_to_binary('\0')) ,memory_list); /* TODO: Might separate to function? */

    return strlen(data) - 2;
}

/* TODO: write this */
/* TODO: Add documentation */
int handle_first_word(LinkedList_t split_by_space, char *command, LinkedList_t memory_list) {
    return 0;
}
