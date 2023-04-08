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

void print_assembler_phase(void) {
    printf("This is the assembler phase (printed by assembler phase functions)\n");
}

/* TODO: Add documentation */
LinkedCommandList_t create_action_names_list() {
    LinkedCommandList_t actions_names_list;

    actions_names_list = create_linked_command_list();

    /* TODO: Instead of setting numbers, generate them */
    add_to_commands_list(create_command_node("mov", "0000", 2, "0,1,3", "1,3"), actions_names_list);
    add_to_commands_list(create_command_node("cmp", "0001", 2, "0,1,3", "0,1,3"), actions_names_list);
    add_to_commands_list(create_command_node("add", "0010", 2, "0,1,3", "1,3"), actions_names_list);
    add_to_commands_list(create_command_node("sub", "0011", 2, "0,1,3", "1,3"), actions_names_list);
    add_to_commands_list(create_command_node("not", "0100", 1, "", "1,3"), actions_names_list);
    add_to_commands_list(create_command_node("clr", "0101", 1, "", "1,3"), actions_names_list);
    add_to_commands_list(create_command_node("lea", "0110", 2, "1", "1,3"), actions_names_list);
    add_to_commands_list(create_command_node("inc", "0111", 1, "", "1,3"), actions_names_list);
    add_to_commands_list(create_command_node("dec", "1000", 1, "", "1,3"), actions_names_list);
    add_to_commands_list(create_command_node("jmp", "1001", 1, "", "1,2,3"), actions_names_list);
    add_to_commands_list(create_command_node("bne", "1010", 1, "", "1,2,3"), actions_names_list);
    add_to_commands_list(create_command_node("red", "1011", 1, "", "1,3"), actions_names_list);
    add_to_commands_list(create_command_node("prn", "1100", 1, "", "0,1,3"), actions_names_list);
    add_to_commands_list(create_command_node("jsr", "1101", 1, "", "1,2,3"), actions_names_list);
    add_to_commands_list(create_command_node("rts", "1110", 0, "", ""), actions_names_list);
    add_to_commands_list(create_command_node("stop", "1111", 0, "", ""), actions_names_list);

    return actions_names_list;
}

/* TODO: Add documentation */
void handle_error(char *error_message, int line_number, int *has_errors) {
    *has_errors = TRUE;
    printf("ERROR: %s on line %d\n", error_message, line_number);
}

/* TODO: Add documentation */
void handle_warning(char *warning_message, int line_number) {
    printf("WARNING: %s on line %d\n", warning_message, line_number);
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
int is_entry(char *line) {
    if (starts_with(line, ENTRY_PREFIX))   /* TODO: Maybe improve this */
        return TRUE;
    return FALSE;
}

/* TODO: Add documentation */
void add_label(LabelsLinkedList_t labels_list, LinkedList_t split_line, char *type, int value, int *has_errors, int line_number) {
    char *label_name = ""; /* TODO: Fix this */

    /* TODO: if there's time - change to switch case */
    if (StringsEqual(type, DATA_TYPE) || StringsEqual(type, CODE_TYPE)) {
        label_name = get_node_value(get_head(split_line));
    } else if (StringsEqual(type,EXTERN_TYPE)) {
        if (get_list_length(split_line) > 2) {
            handle_error("Too many words after label", line_number, has_errors); /* Needs rephrase */
        }
        label_name = get_node_value(get_tail(split_line));
    }

    /* TODO: ERROR HANDLING - Check if labels exists already, and if so, error! */
    /*handle_error("Duplicate label", line_number, has_errors);*/

    if (is_not(is_legal_label_name(label_name))) {
        handle_error("Illegal label name", line_number, has_errors);
        return;
    }

    add_to_labels_list(create_label_node(label_name, type, FIRST_AVAILABLE_ADDRESS + value), labels_list);
}

/* TODO: Add documentation */
void mark_label_as_entry(LabelsLinkedList_t symbol_table, char* label_name) {
    printf("Marking %s as entry!\n", label_name); /* TODO: delete this */
    LabelNode_t curr_label = get_labels_list_head(symbol_table);
    while (curr_label != NULL) {
        if (StringsEqual(get_label_node_name(curr_label), label_name)) {
            set_label_node_type(curr_label, ENTRY_TYPE);
            return;
        }
        curr_label = get_next_label_node(curr_label);
    }
    /* TODO: ERROR HANDLING - label doesn't exist! */
    printf("ERROR: Label %s doesn't exist!\n", label_name); /* TODO: delete this */
}

/* TODO: Rename this */
/* TODO: Add documentation */
void update_symbol_table(LabelsLinkedList_t symbol_table, int ic) {
    LabelNode_t current_label = get_labels_list_head(symbol_table);

    while ((current_label = get_next_label_node(current_label)) != NULL) {
        if (StringsEqual(get_label_node_type(current_label), DATA_TYPE)) {
            set_label_node_value(current_label, get_label_node_value(current_label) + ic);
        }
    }
}

/* TODO: Add documentation */
int add_data_symbols_to_memory(LinkedList_t data_memory_list, int ic, char *memory_array[]) {
    Node_t curr = get_head(data_memory_list);
    while (curr != NULL) {
        memory_array[ic++] = get_node_value(curr);
        curr = get_next_node(curr);
    }
    return ic;
}

/* 2’s complement */
/* TODO: Add documentation */
void set_binary_string_from_num(unsigned int num, char *binary_string, int start) {
    int i;
    for (i = start; num > 0 && i >= 0; i--) {
        binary_string[i] = '0' + num % 2;
        num /= 2;
    }
}

/* 2’s complement */
/* TODO: Add documentation */
void set_binary_string_from_string(char *str, char *binary_string, int start) {
    int i, num, negative = FALSE;
    if (str[0] == MINUS) {
        negative = TRUE;
        num = atoi(copy_substring(str, 1, strlen(str)));
    } else if (str[0] == PLUS) {
        num = atoi(copy_substring(str, 1, strlen(str)));
    } else {
        num = atoi(str);
    }

    if (is(negative))
        num = (~num) + 1;

    set_binary_string_from_num(num, binary_string, start);
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
    char *data, *curr_string, *binary_string;
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
        binary_string = copy_string(DEFAULT_EMPTY_WORD);
        set_binary_string_from_string(curr_string, binary_string, 13);
        add_to_list(create_node(binary_string), memory_list); /* TODO: Might separate to function? */
        curr_node = get_next_node(curr_node);
    }

    return get_list_length(split_data);
}

/* TODO: Write this */
/* TODO: Add documentation */
int handle_string_type(char *line, LinkedList_t memory_list) {
    char *data, *binary_string;
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
        binary_string = copy_string(DEFAULT_EMPTY_WORD);
        set_binary_string_from_num(data[i], binary_string, 13);
        add_to_list(create_node(binary_string), memory_list); /* TODO: Might separate to function? */
    }

    add_to_list(create_node(DEFAULT_EMPTY_WORD), memory_list); /* TODO: Might separate to function? */ /* Adding \0 at the end */

    return strlen(data) - 1;
}

/* write this */
/* TODO: Add documentation */
int is_legal_label_name(char *str) {
    int i, len = strlen(str);

    if (len > 30) {
        return FALSE;
    }

    if (!isalpha(str[0])) {
        return FALSE;
    }

    for (i = 1; i < len; i++) {
        if ((!isalpha(str[i])) && (!isdigit(str[i]))) {
            return FALSE;
        }
    }

    return TRUE;
}

/* TODO: Add documentation */
int is_immediate_address_type (char *str) {
    if (is(starts_with(str, "#"))) {
        return TRUE;
    }
    return FALSE;
}

int is_direct_address_type (char *str) {
    if (is(is_legal_label_name(str))) {
        return TRUE;
    }
    return FALSE;
}

int is_direct_register_type (char *str) {
    if (IsRegister(str)) {
        return TRUE;
    }
    return FALSE;
}

/* write this */
/* TODO: Add documentation */
int is_jump_address_type (char *str) {
    char *curr_operand;
    LinkedList_t split;

    split = split_string(str, '(');
    if (get_list_length(split) != 2) {
        return FALSE;
    }

    if (!is_legal_label_name(get_node_value(get_head(split)))) {
        return FALSE;
    }

    if (str[strlen(str) - 1] != ')') {
        return FALSE;
    }

    curr_operand = get_node_value(get_tail(split));
    split = split_string(copy_substring(curr_operand, 0, strlen(curr_operand)-1), ',');
    if(get_list_length(split) != 2) {
        return FALSE;
    }

    curr_operand = get_node_value(get_head(split));
    if (!(is(is_immediate_address_type(curr_operand)) || is(is_direct_register_type(curr_operand)) || is(is_direct_address_type(curr_operand)))) {
        return FALSE;
    }

    curr_operand = get_node_value(get_tail(split));
    if (!(is(is_immediate_address_type(curr_operand)) || is(is_direct_register_type(curr_operand)) || is(is_direct_address_type(curr_operand)))) {
        return FALSE;
    }
    return TRUE;
}

/* TODO: Add documentation */
int get_address_type(char *operand) {
    int type = -1;
    if (is(is_immediate_address_type(operand))) {
        type = IMMEDIATE;
    } else if (is(is_direct_register_type(operand))) {
        type = REGISTER;
    } else if (is(is_direct_address_type(operand))) {
        type = DIRECT;
    } else if (is_jump_address_type(operand)) {
        type = JUMP;
    } else {
        /* TODO: ERROR HANDLING - illegal operand thingie! */
        printf("ERROR: illegal operand thingie!\n"); /* TODO: Change this */
    }
    return type;
}

/* TODO: Add documentation */
LinkedList_t get_split_operands(char *operands_string) {
    int i;
    LinkedList_t split_operands;

    /* TODO: split operands differently because this way doesn't work well with jump thingies :( */
    /* TODO: This is a quick fix, need to separate to function or redesign */
    for (i = 0; i < strlen(operands_string); i ++) {
        if (operands_string[i] == '(')
            break;
    }
    if (i != strlen(operands_string)) {
        split_operands = create_linked_list();
        add_to_list(create_node(operands_string), split_operands);
    } else
        split_operands = split_string(operands_string, ',');

    return split_operands;
}

/* Assumes a pair of operands in a split thingie */
/* TODO: Add documentation */
int has_non_register_operands(LinkedList_t split_operands) {
    if (get_address_type(get_node_value(get_head(split_operands))) != REGISTER || get_address_type(get_node_value(get_tail(split_operands))) != REGISTER)
        return TRUE;
    return FALSE;
}

/* Assuming line is alright (will be checked separately) */
/* TODO: Add documentation */
int calculate_words_for_line(CommandNode_t command_node, char *relevant_line_bit) {
    char *operands_string;
    int operands_num, i, l = 1, operand_type, non_register_operands = FALSE;
    LinkedList_t split_operands;

    operands_string = get_stripped_string(clean_multiple_whitespaces(copy_substring(relevant_line_bit, strlen(get_command_node_command(command_node)), strlen(relevant_line_bit))));
    operands_num = get_command_node_operands(command_node);

    split_operands = get_split_operands(operands_string);

    if (operands_num == 1) {
        operand_type = get_address_type(operands_string);
        if (operand_type == JUMP) {
            /* Jump handling */
            l += 2; /* TODO: Ensure! */
            split_operands = split_string(get_node_value(get_tail(split_string(copy_substring(operands_string, 0,
                                                                                              strlen(operands_string)-1), '('))), ',');
            l += has_non_register_operands(split_operands);
        } else {
            l += 1;
        }
    } else if (operands_num == 2) {
        split_operands = split_string(get_string_without_whitespaces(operands_string), ',');
        l += 1 + has_non_register_operands(split_operands);
    }

    return l;
}

/* TODO: Add documentation */
void set_immediate_type_code(char *memory_bit, char *operand) {
    set_binary_string_from_string(copy_substring(operand, 1, strlen(operand)), memory_bit, 11);
}

/* TODO: Write this */
/* TODO: Add documentation */
void set_direct_type_code(char *memory_bit, char *operand, LabelsLinkedList_t *symbol_table) {
    LabelNode_t label;
    /* Find label in label table */
    label = search_labels_list(*symbol_table, operand);
    if (label == NULL) {
        printf("ERROR: This is an error!\n"); /* TODO: delete this */
        /* TODO: ERROR HANDLING - label not found */
    }
    if (StringsEqual(get_label_node_type(label), EXTERN_TYPE))
        memory_bit[13] = '1';
    else {
        memory_bit[12] = '1';
        set_binary_string_from_num(get_label_node_value(label), memory_bit, 11);
    }
}

/* TODO: Write this */
/* TODO: Add documentation */
void set_jump_type_code(char *memory_array[], int ic, char *operand, LabelsLinkedList_t *symbol_table) {
    LinkedList_t split_operands;
    split_operands = split_string(operand, '(');
    char *temp, *first, *second;
    ic ++;
    temp = get_node_value(get_head(split_operands));
    set_direct_type_code(memory_array[ic], temp, symbol_table);
    /* TODO: This repeats (when two operands)*/
    split_operands = split_string(get_string_without_whitespaces(copy_substring(get_node_value(get_tail(split_operands)), 0, strlen(operand) -
            strlen(temp) - 2)), ',');
    first = get_node_value(get_head(split_operands));
    second = get_node_value(get_tail(split_operands));
    set_operand_code(first, SOURCE, symbol_table, memory_array, ic);
    if (get_address_type(first) != REGISTER || get_address_type(second) != REGISTER) /* TODO: Make this better and not here */
        ic ++;
    set_operand_code(second, DESTINATION, symbol_table, memory_array, ic);
}

/* TODO: Write this */
/* TODO: Add documentation */
void set_register_type_code(char *memory_bit, char *operand, int start) {
    set_binary_string_from_string(copy_substring(operand, 1, 2), memory_bit, start);
}

/* TODO: Add documentation */
void set_operand_code(char *operand_string, int source_or_dest, LabelsLinkedList_t *symbol_table, char *memory_array[], int ic) {
    int operand_type;
    operand_type = get_address_type(operand_string);
    /* TODO: Change to switch */
    if (operand_type == IMMEDIATE)
        set_immediate_type_code(memory_array[ic + 1], operand_string);
    else if (operand_type == DIRECT) {
        set_direct_type_code(memory_array[ic + 1], operand_string, symbol_table);
    }
    else if (operand_type == JUMP)
        set_jump_type_code(memory_array, ic, operand_string, symbol_table);
    else if (operand_type == REGISTER)
        set_register_type_code(memory_array[ic + 1], operand_string, source_or_dest);
}

/* TODO: write this */
/* TODO: Add documentation */
int handle_first_word(CommandNode_t command_node, char *relevant_line_bit, char memory_slot[], int line_number, int *has_errors) {
    char *operands_string, *opcode;
    int operands_num, i, l = 1, operand_type, non_register_operands = FALSE;
    LinkedList_t split_operands;

    if(command_node == NULL) {  /* Step 12 */
        handle_error("Illegal command", line_number, has_errors);
        return -1;
    }

    operands_string = get_stripped_string(clean_multiple_whitespaces(copy_substring(relevant_line_bit, strlen(get_command_node_command(command_node)), strlen(relevant_line_bit))));
    operands_num = get_command_node_operands(command_node);
    opcode = get_command_node_code(command_node);

    split_operands = get_split_operands(operands_string);

    if (get_list_length(split_operands) != operands_num) {
        handle_error("Wrong amount of operands specified", line_number, has_errors);
        return -1;
    }

    /* Encode and add first word to memory array */
    for (i = 6; i <= 9 ; i++) {
        memory_slot[13-i] = opcode[9-i];
    }

    if (operands_num == 1) {
        operand_type = get_address_type(operands_string);
        /* TODO: split to functions */
        /* TODO: ensure type fits command */
        if (operand_type == JUMP) {
            memory_slot[13-3] = '1'; /* TODO: change to 13 - something */
            l += 2; /* TODO: Ensure! */
            /* handle 10-13 by jump params */
            split_operands = split_string(get_node_value(get_tail(split_string(copy_substring(operands_string, 0,
                                                                                              strlen(operands_string)-1), '('))), ',');
            /* TODO: switch to for loop to reduce code redundancy */
            operand_type = get_address_type(get_node_value(get_head(split_operands)));
            if (operand_type != REGISTER)
                non_register_operands = TRUE;
            memory_slot[13-13] = '0' + (operand_type / 2); /* TODO: change to 13 - something */
            memory_slot[13-12] = '0' + (operand_type % 2); /* TODO: change to 13 - something */
            operand_type = get_address_type(get_node_value(get_tail(split_operands)));
            if (operand_type != REGISTER)
                non_register_operands = TRUE;
            memory_slot[13-11] = '0' + (operand_type / 2); /* TODO: change to 13 - something */
            memory_slot[13-10] = '0' + (operand_type % 2); /* TODO: change to 13 - something */

            l += non_register_operands;
        } else {
            l += 1;
            /* handle 2-3 by params */
            memory_slot[13-3] = '0' + (operand_type / 2); /* TODO: change to 13 - something */
            memory_slot[13-2] = '0' + (operand_type % 2); /* TODO: change to 13 - something */
        }
    } else if (operands_num == 2) {
        l += 1;
        for (i = 0; i <= 3; i++) {
            memory_slot[i] = '0';
        }
        split_operands = split_string(get_string_without_whitespaces(operands_string), ',');
        /* TODO: switch to for loop to reduce code redundancy */
        /* 4,5 bits according to first operand */
        operand_type = get_address_type(get_node_value(get_head(split_operands)));
        if (operand_type != REGISTER)
            non_register_operands = TRUE;
        memory_slot[13-5] = '0' + (operand_type / 2);
        memory_slot[13-4] = '0' + (operand_type % 2);
        /* 2,3 bits according to second operand */
        operand_type = get_address_type(get_node_value(get_tail(split_operands)));
        if (operand_type != REGISTER)
            non_register_operands = TRUE;
        memory_slot[13-3] = '0' + (operand_type / 2);
        memory_slot[13-2] = '0' + (operand_type % 2);
        l += non_register_operands;
    }

    return l;
}

/* TODO: Write this */
/* TODO: Add documentation */
int handle_all_but_first_words(CommandNode_t command_node, char *relevant_line_bit, LabelsLinkedList_t *symbol_table, char *memory_array[], int ic, int line_number, int *has_errors) {
    int l, operands_num = get_command_node_operands(command_node);
    char *operands_string, *first, *second;
    LinkedList_t split_operands;

    l = calculate_words_for_line(command_node, relevant_line_bit);

    if (operands_num == 0)
        return l;

    operands_string = get_stripped_string(clean_multiple_whitespaces(copy_substring(relevant_line_bit, strlen(get_command_node_command(command_node)), strlen(relevant_line_bit))));

    if (operands_num == 1) {
        set_operand_code(operands_string, DESTINATION, symbol_table, memory_array, ic);
    } else if (operands_num == 2) {
        /* TODO: This repeats (jump) */
        split_operands = split_string(get_string_without_whitespaces(operands_string), ',');
        first = get_node_value(get_head(split_operands));
        second = get_node_value(get_tail(split_operands));
        set_operand_code(first, SOURCE, symbol_table, memory_array, ic);
        if (get_address_type(first) != REGISTER || get_address_type(second) != REGISTER) /* TODO: Make this better and not here */
            ic ++;
        set_operand_code(second, DESTINATION, symbol_table, memory_array, ic);
    }

    return l;
}

/* TODO: Add documentation */
int is_valid_line(char *line) {
    if (is(starts_with(line, COMMENT_PREFIX)))
        return FALSE;
    if (strlen(get_string_without_whitespaces(line)) == 0)
        return FALSE;
    return TRUE;
}

/* TODO: Write this */
/* TODO: Add documentation */
void create_files() {
    printf("Create all files!\n"); /* TODO: delete this */
}