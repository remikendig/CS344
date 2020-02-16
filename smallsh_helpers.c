#include "smallsh_helpers.h"

void get_and_parse_input(struct dynarray* args, char line[COMMAND_MAX_LENGTH]) {
    char* token = 0;

    fgets(line, COMMAND_MAX_LENGTH, stdin);
    token = strtok(line, " \n");

    if (token == NULL) {
        return;
    }

    dynarray_insert(args, token);

    while (token != NULL) {
        token = strtok(NULL, " \n");
        if (token == NULL) {
            break;
        }
        dynarray_insert(args, token);
    }
}