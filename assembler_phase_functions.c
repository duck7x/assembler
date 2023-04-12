#include "assembler_phase_functions.h"

/* UNSORTED */

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
    int num, negative = FALSE;
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
    split_data = split_string(data, COMMA);
    curr_node = get_head(split_data);

    while (curr_node != NULL) {
        curr_string = get_node_value(curr_node);
        if (strlen(curr_string) == 0) {
            handle_error("Incorrect commas in data");
            return 0;
        }
        binary_string = copy_string(DEFAULT_EMPTY_WORD);
        set_binary_string_from_string(curr_string, binary_string, 13);
        add_value_to_list(binary_string, memory_list); /* TODO: Might separate to function? */
        curr_node = get_next_node(curr_node);
    }

    return get_list_length(split_data);
}

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
        handle_error("Missing quotation marks at the edge of string definition");
        return 0;
    }

    for (i = 1; i < strlen(data) - 1; i++) {
        binary_string = copy_string(DEFAULT_EMPTY_WORD);
        set_binary_string_from_num(data[i], binary_string, 13);
        add_value_to_list(binary_string, memory_list); /* TODO: Might separate to function? */
    }

    add_value_to_list(DEFAULT_EMPTY_WORD, memory_list); /* TODO: Might separate to function? */ /* Adding \0 at the end */

    return strlen(data) - 1;
}

/* Assuming line is alright (will be checked separately) */
/* TODO: Add documentation */
int calculate_words_for_line(CommandNode_t command_node, char *relevant_line_bit) {
    char *operands_string;
    int operands_num, l = 1, operand_type;
    LinkedList_t split_operands;

    if(command_node == NULL) {
        return -1;  /* An error should have already been thrown when handled the first word */
    }

    operands_string = get_clean_and_stripped_string(copy_substring(relevant_line_bit, strlen(get_command_node_command(command_node)), strlen(relevant_line_bit)));
    operands_num = get_command_node_operands(command_node);

    split_operands = get_split_operands(operands_string);

    if (operands_num == 1) {
        operand_type = get_address_type(operands_string);
        if (operand_type == JUMP) {
            /* Jump handling */
            l += 2; /* TODO: Ensure! */
            split_operands = split_string(GetTailValue(split_string(copy_substring(operands_string, 0,
                                                                                              strlen(operands_string)-1), LEFT_BRACKET)), COMMA);
            l += has_non_register_operands(split_operands);
        } else {
            l += 1;
        }
    } else if (operands_num == 2) {
        split_operands = split_string(get_string_without_whitespaces(operands_string), COMMA);
        l += 1 + has_non_register_operands(split_operands);
    }

    return l;
}



/* TODO: Add documentation */
int handle_first_word(CommandNode_t command_node, char *relevant_line_bit, char memory_slot[]) {
    char *operands_string, *opcode;
    int operands_num, i, l = 1, operand_type, non_register_operands = FALSE;
    LinkedList_t split_operands;

    if(command_node == NULL) {  /* Step 12 */
        handle_error("Illegal command");
        return -1;
    }

    operands_string = get_clean_and_stripped_string(copy_substring(relevant_line_bit, strlen(get_command_node_command(command_node)), strlen(relevant_line_bit)));
    operands_num = get_command_node_operands(command_node);
    opcode = get_command_node_code(command_node);

    split_operands = get_split_operands(operands_string);

    if (get_list_length(split_operands) != operands_num) {
        handle_error("Wrong amount of operands specified");
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
            split_operands = split_string(GetTailValue(split_string(copy_substring(operands_string, 0,
                                                                                              strlen(operands_string)-1), LEFT_BRACKET)), COMMA);
            /* TODO: switch to for loop to reduce code redundancy */
            operand_type = get_address_type(GetHeadValue(split_operands));
            if (operand_type != REGISTER)
                non_register_operands = TRUE;
            memory_slot[13-13] = '0' + (operand_type / 2); /* TODO: change to 13 - something */
            memory_slot[13-12] = '0' + (operand_type % 2); /* TODO: change to 13 - something */
            operand_type = get_address_type(GetTailValue(split_operands));
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
        split_operands = split_string(get_string_without_whitespaces(operands_string), COMMA);
        /* TODO: switch to for loop to reduce code redundancy */
        /* 4,5 bits according to first operand */
        operand_type = get_address_type(GetHeadValue(split_operands));
        if (operand_type != REGISTER)
            non_register_operands = TRUE;
        memory_slot[13-5] = '0' + (operand_type / 2);
        memory_slot[13-4] = '0' + (operand_type % 2);
        /* 2,3 bits according to second operand */
        operand_type = get_address_type(GetTailValue(split_operands));
        if (operand_type != REGISTER)
            non_register_operands = TRUE;
        memory_slot[13-3] = '0' + (operand_type / 2);
        memory_slot[13-2] = '0' + (operand_type % 2);
        l += non_register_operands;
    }

    return l;
}

/* TODO: Add documentation */
int handle_all_but_first_words(CommandNode_t command_node, char *relevant_line_bit, Table_t *extern_memory_table, LabelsLinkedList_t *symbol_table, char *memory_array[], int ic) {
    int l, operands_num = get_command_node_operands(command_node);
    char *operands_string, *first, *second;
    LinkedList_t split_operands;

    if(command_node == NULL) {
        return -1;  /* An error should have already been thrown when handled the first word */
    }

    l = calculate_words_for_line(command_node, relevant_line_bit);

    if (operands_num == 0)
        return l;

    operands_string = get_clean_and_stripped_string(copy_substring(relevant_line_bit, strlen(get_command_node_command(command_node)), strlen(relevant_line_bit)));

    if (operands_num == 1) {
        set_operand_code(operands_string, DESTINATION, extern_memory_table, symbol_table, memory_array, ic);
    } else if (operands_num == 2) {
        /* TODO: This repeats (jump) */
        split_operands = split_string(get_string_without_whitespaces(operands_string), COMMA);
        first = GetHeadValue(split_operands);
        second = GetTailValue(split_operands);
        set_operand_code(first, SOURCE, extern_memory_table, symbol_table, memory_array, ic);
        if (get_address_type(first) != REGISTER || get_address_type(second) != REGISTER) /* TODO: Make this better and not here */
            ic ++;
        set_operand_code(second, DESTINATION, extern_memory_table, symbol_table, memory_array, ic);
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


/* SORTED */

/* Labels related functions */

/*  Gets a LinkedList_t object which represents a line split by the colon delimiter.
    If the list contains more than 1 item, it means the line attempts to start with a label and so the functions returns TRUE.
    If it has more or less items, the function returns FALSE.
*/
int starts_with_label(LinkedList_t split_line) {
    /* TODO: Ensure really a label and not just string thingie with : in it */
    if (get_list_length(split_line) > 1) {
        return TRUE;
    }
    return FALSE;
}

/* TODO: Add documentation */
void add_label(LabelsLinkedList_t labels_list, LinkedList_t split_line, char *type, int value) {
    char *label_name = ""; /* TODO: Fix this */

    /* TODO: if there's time - change to switch case */
    if (StringsEqual(type, DATA_TYPE) || StringsEqual(type, CODE_TYPE)) {
        label_name = GetHeadValue(split_line);
    } else if (StringsEqual(type,EXTERN_TYPE)) {
        if (get_list_length(split_line) > 2) {
            handle_error("Too many words after label"); /* Needs rephrase */
        }
        label_name = GetTailValue(split_line);
    }

    if(search_labels_list(labels_list, label_name)) {
        handle_error("Duplicate label");
    }

    if (is_not(is_legal_label_name(label_name))) {
        handle_error("Illegal label name");
        return;
    }

    add_to_labels_list(create_label_node(label_name, type, FIRST_AVAILABLE_ADDRESS + value), labels_list);
}

/* TODO: Add documentation */
void mark_label_as_entry(LabelsLinkedList_t symbol_table, char* label_name) {
    LabelNode_t curr_label = get_labels_list_head(symbol_table);
    while (curr_label != NULL) {
        if (StringsEqual(get_label_node_name(curr_label), label_name)) {
            set_label_node_type(curr_label, ENTRY_TYPE);
            return;
        }
        curr_label = get_next_label_node(curr_label);
    }
    handle_error("Entry label doesn't exist");
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

/*  Gets a string representing a label name and runs the following checks:
        Ensures the string doesn't have more than 30 characters.
        Ensures the string starts with an alpha character.
        Ensures all characters in the string are of either alpha pr digit.
    If any of those checks fail, the given string is not a legal label name.
    If all checks pass, then the string is a legal label name.
*/
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

/* Address type functions */

/* TODO: Add documentation */
LinkedList_t get_split_operands(char *operands_string) {
    int i;
    LinkedList_t split_operands;

    if (strlen(operands_string) == 0)
        return create_linked_list();
    /* TODO: split operands differently because this way doesn't work well with jump thingies :( */
    /* TODO: This is a quick fix, need to separate to function or redesign */
    for (i = 0; i < strlen(operands_string); i ++) {
        if (operands_string[i] == LEFT_BRACKET)
            break;
    }
    if (i != strlen(operands_string)) {
        split_operands = create_linked_list();
        add_value_to_list(operands_string, split_operands);
    } else
        split_operands = split_string(operands_string, COMMA);

    return split_operands;
}

/*  Gets a string representing an operand.
    Using the starts_with function, checks if the given string starts with #.
    If so, it's immediate address type and so the function returns TRUE,
    If it doesn't, the operand is not an immediate address type and so function returns FALSE.
*/
int is_immediate_address_type (char *str) {
    if (is(starts_with(str, POUND_SIGN))) {
        return TRUE;
    }
    return FALSE;
}

/*  Gets a string representing an operand.
    Using the is_legal_label_name function, checks if the given string could be a label.
    If so, it's direct address type and so the function returns TRUE,
    If it couldn't, the operand is not a direct address type and so function returns FALSE.
*/
int is_direct_address_type (char *str) {
    if (is(is_legal_label_name(str))) {
        return TRUE;
    }
    return FALSE;
}

/*  Gets a string representing an operand.
    Using the IsRegister macro, checks if the given string is a register name.
    If so, it's direct register address type and so the function returns TRUE,
    If it isn't, the operand is not a direct register address type and so function returns FALSE.
*/
int is_direct_register_type (char *str) {
    if (IsRegister(str)) {
        return TRUE;
    }
    return FALSE;
}

/*  Gets a string representing an operand and runs the following checks:
        Checks if the given string ends with a right bracket.
        Splits the given string with the left bracket delimiter:
            Checks if the split list has exactly two items.
            Checks if the first item of the list could be a label (using is_legal_label_name function)
            Splits the second item of the list by comma:
                Checks if the new split list has exactly two items.
                For each of the items in the new split list,
                Checks if it's one of the other address types (immediate, direct register or direct address).
    If any of those checks fail, the given operand is not of jump address type.
    If all checks pass, then the operand is of jump address type.
*/
int is_jump_address_type (char *str) {
    char *curr_operand;
    LinkedList_t split;

    if (str[strlen(str) - 1] != RIGHT_BRACKET) {
        return FALSE;
    }

    split = split_string(str, LEFT_BRACKET);
    if (get_list_length(split) != 2) {
        return FALSE;
    }

    if (!is_legal_label_name(GetHeadValue(split))) {
        return FALSE;
    }

    curr_operand = GetTailValue(split);
    split = split_string(copy_substring(curr_operand, 0, strlen(curr_operand)-1), COMMA);

    if(get_list_length(split) != 2) {
        return FALSE;
    }

    curr_operand = GetHeadValue(split);
    if (!(is(is_immediate_address_type(curr_operand)) || is(is_direct_register_type(curr_operand)) || is(is_direct_address_type(curr_operand)))) {
        return FALSE;
    }

    curr_operand = GetTailValue(split);
    if (!(is(is_immediate_address_type(curr_operand)) || is(is_direct_register_type(curr_operand)) || is(is_direct_address_type(curr_operand)))) {
        return FALSE;
    }

    return TRUE;
}

/*  Gets a string representing an operand.
    Using the functions is_immediate_address_type, is_direct_register_type, is_direct_address_type, is_jump_address_type
    Checks the type of the operand.
    Returns the relevant type.
    If no type is found, the function notifies and marks the error using handle_error and returns -1.
*/
int get_address_type(char *operand) {
    int type = -1;  /* TODO: Maybe change to ERROR rather than -1 */

    if (is(is_immediate_address_type(operand))) {
        type = IMMEDIATE;
    } else if (is(is_direct_register_type(operand))) {
        type = REGISTER;
    } else if (is(is_direct_address_type(operand))) {
        type = DIRECT;
    } else if (is(is_jump_address_type(operand))) {
        type = JUMP;
    } else {
        handle_error("Illegal operand");
    }

    return type;
}

/*  Gets a linked list object.
    The function assumes the list has exactly 2 items, each containing an operand.
    Using the has_non_register_operands, checks if both of them is of direct register address type.
    If so, returns FALSE.
    Otherwise, returns TRUE.
*/
int has_non_register_operands(LinkedList_t split_operands) {
    if (is(is_direct_register_type(GetHeadValue(split_operands))) && is(is_direct_register_type(GetTailValue(split_operands))))
        return FALSE;
    return TRUE;
}

/* TODO: Add documentation */
void set_immediate_type_code(char *memory_bit, char *operand) {
    set_binary_string_from_string(copy_substring(operand, 1, strlen(operand)), memory_bit, 11);
}

/* TODO: Add documentation */
void set_direct_type_code(char *memory_bit, char *operand, Table_t *extern_memory_table ,LabelsLinkedList_t *symbol_table, int ic) {
    LabelNode_t label;
    char temp[5];
    /* Find label in label table */
    label = search_labels_list(*symbol_table, operand);
    if (label == NULL) {
        handle_error("Label doesn't exist for direct type operand");
    }
    if (StringsEqual(get_label_node_type(label), EXTERN_TYPE)) {
        memory_bit[13] = '1';
        sprintf(temp, "%04d", ic + FIRST_AVAILABLE_ADDRESS);
        add_to_table(*extern_memory_table, temp, get_label_node_name(label));
        /* TODO: Add to extern label list */
    }
    else {
        memory_bit[12] = '1';
        set_binary_string_from_num(get_label_node_value(label), memory_bit, 11);
    }
}

/* TODO: Add documentation */
void set_jump_type_code(char *memory_array[], int ic, char *operand, Table_t *extern_memory_table, LabelsLinkedList_t *symbol_table) {
    LinkedList_t split_operands;
    char *temp, *first, *second;
    split_operands = split_string(operand, LEFT_BRACKET);
    ic ++;
    temp = GetHeadValue(split_operands);
    set_direct_type_code(memory_array[ic], temp, extern_memory_table, symbol_table, ic);
    /* TODO: This repeats (when two operands)*/
    split_operands = split_string(get_string_without_whitespaces(copy_substring(GetTailValue(split_operands), 0, strlen(operand) -
                                                                                                                 strlen(temp) - 2)), COMMA);
    first = GetHeadValue(split_operands);
    second = GetTailValue(split_operands);
    set_operand_code(first, SOURCE, extern_memory_table, symbol_table, memory_array, ic);
    if (get_address_type(first) != REGISTER || get_address_type(second) != REGISTER) /* TODO: Make this better and not here */
        ic ++;
    set_operand_code(second, DESTINATION, extern_memory_table, symbol_table, memory_array, ic);
}

/* TODO: Add documentation */
void set_register_type_code(char *memory_bit, char *operand, int start) {
    set_binary_string_from_string(copy_substring(operand, 1, 2), memory_bit, start);
}

/* If the operand is illegal, the get_address_type function will handle the error */
/* TODO: Add documentation */
void set_operand_code(char *operand_string, int source_or_dest, Table_t *extern_memory_table, LabelsLinkedList_t *symbol_table, char *memory_array[], int ic) {
    int operand_type;
    operand_type = get_address_type(operand_string);
    /* TODO: Change to switch */
    if (operand_type == IMMEDIATE)
        set_immediate_type_code(memory_array[ic + 1], operand_string);
    else if (operand_type == DIRECT) {
        set_direct_type_code(memory_array[ic + 1], operand_string, extern_memory_table ,symbol_table, ic);
    }
    else if (operand_type == JUMP)
        set_jump_type_code(memory_array, ic, operand_string, extern_memory_table, symbol_table);
    else if (operand_type == REGISTER)
        set_register_type_code(memory_array[ic + 1], operand_string, source_or_dest);
}

/* Files related functions */

/*  Gets a string representing a file name and an array representing the assembler memory image.
    Sets the destination file to be the given file name with .ob suffix.
    Using a while loop, goes through the array until reaching "\0" string which represents the end of the array.
    Goes through all characters of each word
        If the character is 0, adds . to the destination file.
        If the character is 1, adds / to the destination file.
    At the end of each word, adds \n to the destination file.

    The function assumes that the first line of the file has already been written in function called earlier in the code.
*/
void write_object_file(char* file_name, char *memory_array[]) {
    int j, i = 0;
    FILE *dest_file;

    dest_file = fopen(concatenate_strings(file_name, OBJECT_FILE_SUFFIX), APPEND);
    while (StringsNotEqual(memory_array[i], "\0")) {
        fprintf(dest_file, "%04d\t", i + FIRST_AVAILABLE_ADDRESS);
        for (j = 0; j < 14 ; j++) {
            if(memory_array[i][j] == '0')
                putc(ZERO, dest_file);
            else
                putc(ONE, dest_file);
        }
        putc(NEWLINE, dest_file);
        i++;
    }

    fclose(dest_file);
}

/* TODO: Add documentation */
void create_externals_file(char* file_name, Table_t external_memory_table) {
    int i, externals_amount;
    FILE *dest_file;
    Pair_t *pairs_array;

    externals_amount = get_number_of_pairs(external_memory_table);

    if (externals_amount == 0)
        return;

    dest_file = fopen(concatenate_strings(file_name, EXTERNALS_FILE_SUFFIX), WRITE);
    pairs_array = get_pair_array(external_memory_table);

    for (i = 0; i < externals_amount; i++) {
        fprintf(dest_file, "%s\t%s\n", get_pair_value(pairs_array[i]), get_pair_key(pairs_array[i]));
    }

    fclose(dest_file);
}

/* TODO: Add documentation */
void create_entries_file(char* file_name, LabelsLinkedList_t symbol_table) {
    int has_entries = FALSE;
    FILE *dest_file;

    LabelNode_t curr_label = get_labels_list_head(symbol_table);
    while (curr_label != NULL) {
        if (StringsEqual(get_label_node_type(curr_label), ENTRY_TYPE)) { /* TODO: Maybe make into a function */
            if (is_not(has_entries)) {
                dest_file = fopen(concatenate_strings(file_name, ENTRIES_FILE_SUFFIX), WRITE);
                has_entries = TRUE;
            }
            fprintf(dest_file, "%s\t%04d\n", get_label_node_name(curr_label), get_label_node_value(curr_label));
        }
        curr_label = get_next_label_node(curr_label);
    }
}
