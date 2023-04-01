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
    /* TODO: ERROR HANDLING - ensure legit label name! */
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
    int len = strlen(str);
    char *curr_operand;
    LinkedList_t split;

    split = split_string(str, '(');
    if (get_list_length(split) != 2) {
        return FALSE;
    }

    if (!is_legal_label_name(get_node_value(get_head(split)))) {
        return FALSE;
    }

    if (str[len - 1] != ')') {
        return FALSE;
    }

    split = split_string(copy_substring(get_node_value(get_tail(split)), 0, len-2), ',');
    if(get_list_length(split) != 2) {
        return FALSE;
    }

    curr_operand = get_node_value(get_head(split));
    if (is_not(is_immediate_address_type(curr_operand)) && is_not(is_direct_address_type(curr_operand)) && is_not(is_direct_register_type(curr_operand))) {
        return FALSE;
    }

    curr_operand = get_node_value(get_tail(split));
    if (is_not(is_immediate_address_type(curr_operand)) && is_not(is_direct_address_type(curr_operand)) && is_not(is_direct_register_type(curr_operand))) {
        return FALSE;
    }

    return TRUE;
}

/* TODO: Add documentation */
int get_address_type(char *operand) {
    int type = -1;
    if (is(is_immediate_address_type(operand))) {
        type = IMMEDIATE;
    } else if (is(is_direct_address_type(operand))) {
        type = DIRECT;
    } else if (is(is_direct_register_type(operand))) {
        type = REGISTER;
    } else if (is_jump_address_type(operand)) {
        type = JUMP;
    } else {
        /* TODO: ERROR HANDLING - illegal operand thingie! */
        printf("ERROR: illegal operand thingie!"); /* TODO: Change this */
    }
    return type;
}

/* TODO: write this */
/* TODO: Add documentation */
int handle_first_word(CommandNode_t command_node, char *relevant_line_bit, char memory_slot[]) {
    char *operands_string, *opcode;
    int operands_num, i, l = 1, operand_type;
    LinkedList_t split_operands;

    printf("DEBUG: Handling command:\n"); /* TODO: delete this */
    print_commands_node(command_node);/* TODO: delete this */

    if(command_node == NULL) {  /* Step 12 */
        /* TODO: ERROR HANDLING - illegal command! */
        return -1;
    }

    operands_string = get_stripped_string(clean_multiple_whitespaces(copy_substring(relevant_line_bit, strlen(get_command_node_command(command_node)), strlen(relevant_line_bit))));
    split_operands = split_string(operands_string, ',');
    operands_num = get_command_node_operands(command_node);
    opcode = get_command_node_code(command_node);
    if (get_list_length(split_operands) != operands_num) {
        /* TODO: ERROR HANDLING - wrong amount of operands specified */
        return -1;
    }

    printf("DEBUG: line is [%s] and operands_string is [%s]\n", relevant_line_bit, operands_string); /* TODO: delete this */

    for (i = 0; i < operands_num; i ++) {
        /* Understand l lengths according to operands */
    }

    /* Encode and add first word to memory array */
    for (i = 7; i >= 4 ; i--) {
        memory_slot[i] = opcode[i-4];
    }
    if (operands_num == 1) {
        operand_type = get_address_type(operands_string);
        /* TODO: ensure type fits command */
        if (operand_type == JUMP) {
            memory_slot[11] = 1;
            l += 2; /* TODO: Ensure! */
            /* handle 10-13 by jump params */
            split_operands = split_string(get_node_value(get_tail(split_string(copy_substring(operands_string, 0,
                                                                                              strlen(operands_string - 2)), '('))), ',');
            operand_type = get_address_type(get_node_value(get_head(split_operands)));
            memory_slot[3] = '0' + (operand_type / 2);
            memory_slot[2] = '0' + (operand_type % 2);
            operand_type = get_address_type(get_node_value(get_tail(split_operands)));
            memory_slot[1] = '0' + (operand_type / 2);
            memory_slot[0] = '0' + (operand_type % 2);

            if (memory_slot[3] != memory_slot [1] || memory_slot[2] != memory_slot[0])
                l += 1;
            
        } else {
            l += 1;
            /* handle 2-3 by params */
            memory_slot[11] = '0' + (operand_type / 2);
            memory_slot[10] = '0' + (operand_type % 2);
        }
    } else if (operands_num == 2) {
        l += 2;
        for (i = 0; i <= 3; i++) {
            memory_slot[i] = '0';
        }
        split_operands = split_string(get_string_without_whitespaces(operands_string), ',');
        /* 4,5 bits according to first operand */
        operand_type = get_address_type(get_node_value(get_head(split_operands)));
        memory_slot[11] = '0' + (operand_type / 2);
        memory_slot[10] = '0' + (operand_type % 2);
        /* 2,3 bits according to second operand */
        operand_type = get_address_type(get_node_value(get_head(split_operands)));
        memory_slot[9] = '0' + (operand_type / 2);
        memory_slot[8] = '0' + (operand_type % 2);
    }

    printf("DEBUG: Memory slot is %s\n", memory_slot); /* TODO: delete this */

    return l;
}
