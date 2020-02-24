#include "smallsh_helpers.h"

void get_and_parse_input(char*** args, char line[COMMAND_MAX_LENGTH], int* argn) {
    char* token = 0;
    char** args_temp;
    int i = 0;

    fgets(line, COMMAND_MAX_LENGTH, stdin);

    for (i = 0; line[i] != '\0'; i++) { //get number of words in line (for allocation & looping)
        if ((line[i] == ' ') || (line[i] == '\n')) {
            *argn = *argn + 1;
        }
    }

    args_temp = malloc((*argn + 1) * sizeof(char*)); //allocate memory for array of arguments + NULL
    for (i = 0; i <= *argn; i++) {
        args_temp[i] = malloc((COMMAND_MAX_LENGTH + 1) * sizeof(char));
    }

    for (i = 0; i < *argn; i++) { //get those strings set
        memset(args_temp[i], '\0', COMMAND_MAX_LENGTH + 1);
    }

    //below is separating the input and stuffing it in the array
    token = strtok(line, " \n");

    if (token == NULL) {
        return; //basically i guess if there wasn't really any input in a line without there being a newline?
    }

    strcpy(args_temp[0], token); //fun fact that i learned: you can't do args[0] = token if you dynamically allocated memory! definitely didn't learn that the hard way
    i = 1;

    while (token != NULL) { //gets all the input
        token = strtok(NULL, " \n");
        if (token == NULL) {
            break; //checks if token is null BEFORE trying to put it in the array... lol
        }
        strcpy(args_temp[i], token);
        i++;
    }

    args_temp[*argn] = NULL; //terminating NULL for execvp
    *args = args_temp;
}

void check_file_redirect(bool* rd_in, bool* rd_out, char** args, int argn, int* fd_in, int* fd_out) {
    int i = 0;

    for (i = 0; i < argn; i++) {
        if (strcmp(args[i], "<") == 0) {
            *rd_in = true;
            *fd_in = open(args[i + 1], O_RDONLY);
            args[i] = NULL; //so it doesn't go into the execvp
            args[i + 1] = NULL;
        }
        if (strcmp(args[i], ">") == 0) {
            *rd_out = true;
            *fd_out = open(args[i + 1], O_WRONLY | O_TRUNC | O_CREAT, 0600);
            args[i] = NULL; //same as above
            args[i + 1] = NULL;
        }
    }
}