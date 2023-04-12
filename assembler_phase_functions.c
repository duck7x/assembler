#include "assembler_phase_functions.h"

/* General functions */

/* TODO: Add documentation */
LinkedCommandList_t create_action_names_list() {
    LinkedCommandList_t actions_names_list;

    actions_names_list = create_linked_command_list();

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
int is_valid_line(char *line) {
    if (is(starts_with(line, COMMENT_PREFIX)))
        return FALSE;
    if (strlen(get_string_without_whitespaces(line)) == 0)
        return FALSE;
    return TRUE;
}

/* TODO: Add documentation */
int is_legal_number(char *str) {
    int i;

    if(!isdigit(str[0]) && str[0] != MINUS && str[0] != PLUS)
        return FALSE;

    for (i = 1; i < strlen(str); i++) {
        if(!isdigit(str[i]))
            return FALSE;
    }
    return TRUE;
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
        num = atoi(copy_substring(str, 1, (int)strlen(str)));
    } else if (str[0] == PLUS) {
        num = atoi(copy_substring(str, 1, (int)strlen(str)));
    } else {
        num = atoi(str);
    }

    if (is(negative))
        num = (~num) + 1;

    set_binary_string_from_num(num, binary_string, start);
}

/* Labels related functions */

/*  Gets a string representing a line.
    Checks if it's a data storage instruction by using the starts_with function to check if the line starts with
    Either DATA_PREFIX or STRING_PREFIX.
*/
int is_data_storage(char *line){
    if (starts_with(line, DATA_PREFIX) || starts_with(line, STRING_PREFIX))
        return TRUE;
    return FALSE;
}

/*  Gets a string representing a line.
    Checks if it's an extern instruction by using the starts_with function to check if the line starts with EXTERN_PREFIX.
*/
int is_extern(char *line) {
    if (starts_with(line, EXTERN_PREFIX))
        return TRUE;
    return FALSE;
}

/*  Gets a string representing a line.
    Checks if it's an entry instruction by using the starts_with function to check if the line starts with ENTRY_PREFIX.
*/
int is_entry(char *line) {
    if (starts_with(line, ENTRY_PREFIX))
        return TRUE;
    return FALSE;
}

/*  Gets a string representing a line.
    Checks if it's an extern or entry instruction by using the is_extern and is_entry functions.
*/
int is_extern_or_entry(char *line) {
    if (is(is_extern(line)) || is(is_entry(line)))
        return TRUE;
    return FALSE;
}

/*  Gets a string representing a line and a linked list representing the data image of the assembler.
    Ensures the syntax is correct according to:
        No space after the .data instruction prefix.
        All given data are legal numbers.
        Correct amount placement of commas.
    If syntax is not right, returns ERROR.
    Otherwise, goes through all numbers in the instruction (by splitting the line by comma delimiter)
    And adds its binary representation to the given data image list.
    Returns the amount of data that was added by returning the length of the list of the split line.
*/
int handle_data_type(char *line, LinkedList_t data_memory_list) {
    char *data, *curr_string, *binary_string;
    Node_t curr_node;
    LinkedList_t split_data;

    data = copy_substring(line, 5, (int)strlen(line));

    if (!isSpace(data[0])) {
        handle_error("Illegal instruction");
        return ERROR;
    }

    data = get_string_without_whitespaces(data);
    split_data = split_string(data, COMMA);
    curr_node = get_head(split_data);

    while (curr_node != NULL) {
        curr_string = get_node_value(curr_node);

        if (strlen(curr_string) == 0) {
            handle_error("Incorrect commas in data");
            return ERROR;
        }

        if (is_not(is_legal_number(curr_string))) {
            handle_error("Illegal number in .data instruction");
            return ERROR;
        }

        binary_string = copy_string(DEFAULT_EMPTY_WORD);
        set_binary_string_from_string(curr_string, binary_string, 13);
        add_value_to_list(binary_string, data_memory_list);
        curr_node = get_next_node(curr_node);
    }

    return get_list_length(split_data);
}

/*  Gets a string representing a line and a linked list representing the data image of the assembler.
    Ensures the syntax is correct according to:
        No space after the .data instruction prefix.
        String is wrapped in quotation marks.
    If syntax is not right, returns ERROR.
    Otherwise, goes through all characters in the instruction (other than the quotation marks) using a for loop
    And adds its binary representation to the given data image list.
    Also adds \0 binary representation to the data image to represent the end of the string.
    Returns the length of the string that was added.
*/
int handle_string_type(char *line, LinkedList_t data_memory_list) {
    char *data, *binary_string;
    int i;

    data = copy_substring(line, 7, (int)strlen(line));

    if (!isSpace(data[0])) {
        handle_error("Illegal instruction");
        return ERROR;
    }

    data = get_string_without_whitespaces(data);

    if (data[0] != '"' || data[strlen(data) - 1] != '"') {
        handle_error("Missing quotation marks at the edge of string definition");
        return ERROR;
    }

    for (i = 1; i < strlen(data) - 1; i++) {
        binary_string = copy_string(DEFAULT_EMPTY_WORD);
        set_binary_string_from_num(data[i], binary_string, 13);
        add_value_to_list(binary_string, data_memory_list);
    }

    add_value_to_list(DEFAULT_EMPTY_WORD, data_memory_list); /* Adding \0 at the end */

    return (int)strlen(data) - 1;
}

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

/*  Gets a labels list, a line split, a string representing label type
    and an int representing label value.
    According to the label type, extracts the label name from the split line.
    Ensures that the label definition is valid:
        If extern type, ensures it defines only a single value.
        Ensures such label doesn't already exist.
        Ensures the label name is valid.
    If the label definition is valid, adds the new label and its content to the given labels list.
    If there are errors in the label definition, handles them.
*/
void add_label(LabelsLinkedList_t labels_list, LinkedList_t split_line, char *type, int value) {
    char *label_name = "";

    if (StringsEqual(type, DATA_TYPE) || StringsEqual(type, CODE_TYPE)) {
        label_name = GetHeadValue(split_line);
    } else if (StringsEqual(type,EXTERN_TYPE)) {
        if (get_list_length(split_line) > 2) {
            handle_error("Too many parameters after extern instruction");
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

/*  Gets a linked labels list representing all labels that had been defined in the file,
    Gets a string representing a label name.
    Using the search_labels_list function, looks for the given label in the labels list.
    If found, marks that label as an entry type.
    If not found, handles the error.
*/
void mark_label_as_entry(LabelsLinkedList_t symbol_table, char* label_name) {
    LabelNode_t label = search_labels_list(symbol_table, label_name);

    if (label == NULL)
        handle_error("Entry label doesn't exist");
    else
        set_label_node_type(label, ENTRY_TYPE);
}

/*  Gets a linked labels list representing all labels that had been defined in the file,
    And an int representing the instructions counter at the end of phase 1 of the assembler.
    Goes through the given list and adds the ic counter to all the data type labels values.
*/
void update_symbol_table(LabelsLinkedList_t symbol_table, int ic) {
    LabelNode_t current_label = get_labels_list_head(symbol_table);

    while ((current_label = get_next_label_node(current_label)) != NULL) {
        if (StringsEqual(get_label_node_type(current_label), DATA_TYPE)) {
            set_label_node_value(current_label, get_label_node_value(current_label) + ic);
        }
    }
}

/*  Gets a linked list representing the data image of the assembler,
    An int representing the current instruction counter,
    And an array of string, representing the code image of the assembler.
    Adds the data image to the end of the code image, while keeping track of the updated instruction counter.
    Returns the updated instructions counter.
*/
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
    int i, len = (int)strlen(str);

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

/*  Gets a string representing the operands bit of a code line
    Returns a list representing all operands in the given string where each member of the list is a single operand.
    The list is generated according to the following logic:
        If there's ( char in the string, this is a jump type operand and the entire string is a single operand.
            In such case, the function returns a list with a single item - the given string.
        Otherwise, it's a regular operand string and can be split (using split_string) by the comma delimiter.
            This should also handle a case where the operands string is empty.
*/
LinkedList_t get_split_operands(char *operands_string) {
    LinkedList_t split_operands;

    if (strchr(operands_string, LEFT_BRACKET) != NULL) {
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
    split = split_string(copy_substring(curr_operand, 0, (int)strlen(curr_operand)-1), COMMA);

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
    int type = ERROR;

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

/*  Gets a string representing a word in the code image and a string representing an immediate address type operand.
    Adjusts the memory bit string to match the given operand with immediate address,
    Using the set_binary_string_from_string, encodes the binary representation of the number to the 12 relevant bits.
*/
void set_immediate_type_code(char *memory_bit, char *operand) {
    set_binary_string_from_string(copy_substring(operand, 1, (int)strlen(operand)), memory_bit, 11);
}

/*  Gets a string representing a word in the code image, a string representing a direct address type operands,
    a table representing all externals used in the code, a labels list representing all labels defined in the code
    and an int representing the instruction counter.
    The operand should be a label, so the function searches it in the labels list.
    If the label is not found, the function handles the error and exits.
    Bits 0 and 1 of the memory bit are set according to the label type.
    If the found label is an extern label, adds this usage of the label to the externals table.
        Also, in such case, the rest of the bits are left untouched.
    If the label found is not an extern label, using the set_binary_string_from_num encodes the binary representation
    of the number to the 12 relevant bits.
*/
void set_direct_type_code(char *memory_bit, char *operand, Table_t *extern_memory_table ,LabelsLinkedList_t *symbol_table, int ic) {
    LabelNode_t label;
    char temp[5];

    label = search_labels_list(*symbol_table, operand);

    if (label == NULL) {
        handle_error("Label doesn't exist for direct type operand");
        return;
    }

    if (StringsEqual(get_label_node_type(label), EXTERN_TYPE)) {
        memory_bit[13] = '1';
        sprintf(temp, "%04d", ic + FIRST_AVAILABLE_ADDRESS);
        add_to_table(*extern_memory_table, temp, get_label_node_name(label));
    }
    else {
        memory_bit[12] = '1';
        set_binary_string_from_num(get_label_node_value(label), memory_bit, 11);
    }
}

/*  Gets a string representing a word in the code image and a string representing a direct register address type operand
    and an int representing the relevant bits (based on the operand being source or destination).
    Adjusts the memory bit string to match the given operand with direct register address,
    Using the set_binary_string_from_string, encodes the binary representation of the number to the relevant bits,
    which are determined by the start parameter.
*/
void set_register_type_code(char *memory_bit, char *operand, int start) {
    set_binary_string_from_string(copy_substring(operand, 1, 2), memory_bit, start);
}

/*  Gets an array representing the code image, an int representing the instructions counter,
    a string representing a jump address type operand,
    a table with all externals used in the code so far,
    and a labels list with all labels defined in the code.
    Sets the next 2 or 3 words in the memory array according to the jump type encoding.
    The first word should be a label, so it is encoded using the set_direct_type_code functions.
    The second (and possibly third) words should be of different address types, and are encoded using set_operand_code function.
    If both of them are of Register type, they're combined to one word. Otherwise, they would be two separate words.
*/
void set_jump_type_code(char *memory_array[], int ic, char *operand, Table_t *extern_memory_table, LabelsLinkedList_t *symbol_table) {
    char *temp, *first, *second;
    LinkedList_t split_operands = split_string(operand, LEFT_BRACKET);

    ic ++;
    temp = GetHeadValue(split_operands);
    set_direct_type_code(memory_array[ic], temp, extern_memory_table, symbol_table, ic);

    split_operands = split_string(get_string_without_whitespaces(copy_substring(GetTailValue(split_operands), 0, (int)strlen(operand) -
            (int)strlen(temp) - 2)), COMMA);
    first = GetHeadValue(split_operands);
    second = GetTailValue(split_operands);

    set_operand_code(first, SOURCE, extern_memory_table, symbol_table, memory_array, ic);
    if (is(has_non_register_operands(split_operands)))
        ic ++;
    set_operand_code(second, DESTINATION, extern_memory_table, symbol_table, memory_array, ic);
}

/*  Gets a string representing an operand, an int representing that operand type (source or destination),
    a table with all externals used in the code so far, a labels list with all labels defined in the code,
    an array representing the code image and an int representing the instructions counter.
    Adjust relevant word(s) in the memory array to match the given operand with its address type,
    using the get_address_type to get the operand's address type and then, according to that, using the
    set_immediate_type_code, set_direct_type_code, set_jump_type_code or set_register_type_code functions, sets the
    relevant words.
    The function assumes that if the given operand is illegal, get_address_type function will handle the error.
*/
void set_operand_code(char *operand_string, int source_or_dest, Table_t *extern_memory_table, LabelsLinkedList_t *symbol_table, char *memory_array[], int ic) {
    int operand_type;

    operand_type = get_address_type(operand_string);

    if (operand_type == IMMEDIATE)
        set_immediate_type_code(memory_array[ic + 1], operand_string);
    else if (operand_type == DIRECT) {
        set_direct_type_code(memory_array[ic + 1], operand_string, extern_memory_table ,symbol_table, ic);
    } else if (operand_type == JUMP)
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

/*  Gets a string representing a file name a table representing all externals used in the code.
    If the table is empty, the function stops without creating any files.
    If it isn't, the function goes through all items in the given table and adds them to the destination file.
*/
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

/*  Gets a string representing a file name and a labels list representing all labels that had been defined in the code.
    Goes through the given list and searches for all entry labels.
    Whenever encountered an entry label - checks if it's the first one.
        If so, creates the destination file and adjusts the has_entries flag.
        Either way, adds the entry label to the destination file along with its value.
*/
void create_entries_file(char* file_name, LabelsLinkedList_t symbol_table) {
    int has_entries = FALSE;
    FILE *dest_file;

    LabelNode_t curr_label = get_labels_list_head(symbol_table);
    while (curr_label != NULL) {
        if (StringsEqual(get_label_node_type(curr_label), ENTRY_TYPE)) {
            if (is_not(has_entries)) {
                dest_file = fopen(concatenate_strings(file_name, ENTRIES_FILE_SUFFIX), WRITE);
                has_entries = TRUE;
            }
            fprintf(dest_file, "%s\t%04d\n", get_label_node_name(curr_label), get_label_node_value(curr_label));
        }
        curr_label = get_next_label_node(curr_label);
    }
}

/* Words related functions */

/* Assuming line is alright (will be checked separately) */
/* TODO: Add documentation */
int calculate_words_for_line(CommandNode_t command_node, char *relevant_line_bit) {
    char *operands_string;
    int operands_num, l = 1, operand_type;
    LinkedList_t split_operands;

    if(command_node == NULL) {
        return ERROR;  /* An error should have already been thrown when handled the first word */
    }

    operands_string = get_clean_and_stripped_string(copy_substring(relevant_line_bit, (int)strlen(get_command_node_command(command_node)), (int)strlen(relevant_line_bit)));
    operands_num = get_command_node_operands(command_node);

    split_operands = get_split_operands(operands_string);

    if (operands_num == 1) {
        operand_type = get_address_type(operands_string);
        if (operand_type == JUMP) {
            /* Jump handling */
            l += 2;
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
        return -ERROR;
    }

    operands_string = get_clean_and_stripped_string(copy_substring(relevant_line_bit, (int)strlen(get_command_node_command(command_node)), strlen(relevant_line_bit)));
    operands_num = get_command_node_operands(command_node);
    opcode = get_command_node_code(command_node);

    split_operands = get_split_operands(operands_string);

    if (get_list_length(split_operands) != operands_num) {
        handle_error("Wrong amount of operands specified");
        return ERROR;
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
        return ERROR;  /* An error should have already been thrown when handled the first word */
    }

    l = calculate_words_for_line(command_node, relevant_line_bit);

    if (operands_num == 0)
        return l;

    operands_string = get_clean_and_stripped_string(copy_substring(relevant_line_bit, (int)strlen(get_command_node_command(command_node)), (int)strlen(relevant_line_bit)));

    if (operands_num == 1) {
        set_operand_code(operands_string, DESTINATION, extern_memory_table, symbol_table, memory_array, ic);
    } else if (operands_num == 2) {
        /* TODO: This repeats (jump) */
        split_operands = split_string(get_string_without_whitespaces(operands_string), COMMA);
        first = GetHeadValue(split_operands);
        second = GetTailValue(split_operands);
        set_operand_code(first, SOURCE, extern_memory_table, symbol_table, memory_array, ic);
        if (is(has_non_register_operands(split_operands)))
            ic ++;
        set_operand_code(second, DESTINATION, extern_memory_table, symbol_table, memory_array, ic);
    }

    return l;
}