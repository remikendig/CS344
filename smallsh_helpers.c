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

    for (i = 0; i < argn - 1; i++) {
        if (strcmp(args[i], "<") == 0) {
            *fd_in = open(args[i + 1], O_RDONLY);
            if (*fd_in == -1) {
                perror("failed to open file for input\n");
                exit(1);
            }
            *rd_in = true;
            args[i] = NULL; //so it doesn't go into the execvp
            args[i + 1] = NULL;
        }
        if (strcmp(args[i], ">") == 0) {
            *fd_out = open(args[i + 1], O_WRONLY | O_TRUNC | O_CREAT, 0600);
            if (*fd_out == -1) {
                perror("failed to open file for output\n");
                exit(1);
            }
            *rd_out = true;
            args[i] = NULL; //same as above
            args[i + 1] = NULL;
        }
    }
}

int search_process_array(struct dynarray* processes) {
    int i = 0, idx = -1;
}

void expand_pid(char* arg, int argn) {
    int i = 0, argl = -1, j = -1; //argl is length of argument, j is secondary position in string
    char buf1[2048] = {0}, buf2 = {0};

    argl = strlen(arg);

    for (i = 0; i < argl; i++) {
        if (arg[i] == '$' && (i < (argl - 1)) ) {
            if (arg[i + 1] == '$') {
                if ((i + 1) < (argl - 1)) {

                }
            }
        }
    }
}

void bg_process(char** args, int argn) {
    bool rd_in = false, rd_out = false;
    int in_fd = -2, out_fd = -2, result = -2;

    check_file_redirect(&rd_in, &rd_out, args, argn, &in_fd, &out_fd); //check for file redirection first

    if (rd_in) {
        result = dup2(in_fd, 0); //redirect input from the appropriate file, if necessary
        if (result == -1) {
            perror("dup2 error");
            exit(1);
        }
    } else { //otherwise redirect from /dev/null
        in_fd = open("/dev/null", O_RDONLY); //open /dev/null for reading only
        if (in_fd == -1) {
            perror("failed to open /dev/null\n");
            exit(1);
        }
        result = dup2(in_fd, 0); //redirect
        if (result == -1) {
            perror("dup2 error");
            exit(1);
        }
    }
    if (rd_out) {
        result = dup2(out_fd, 1); //redirect output to appropriate file, if necessary
        if (result == -1) {
            perror("dup2 error\n");
            exit(1);
        }
    } else { //otherwise redirect to /dev/null 
        out_fd = open("/dev/null", O_WRONLY); //open /dev/null for writing only
        if (out_fd == -1) {
            perror("failed to open /dev/null\n");
            exit(1);
        }
        result = dup2(out_fd, 1); //redirect
        if (result == -1) {
            perror("dup2 error\n");
            exit(1);
        }
    }
    execvp(args[0], args); //execute the command with everything appropriately redirected
    exit(0);
}

void fg_process(char** args, int argn) {
    bool rd_in = false, rd_out = false;
    int in_fd = -2, out_fd = -2, result = -2;

    check_file_redirect(&rd_in, &rd_out, args, argn, &in_fd, &out_fd); //check for file redirection

    if (rd_in) { //redirect from input file if necessary
        result = dup2(in_fd, 0);
        if (result == -1) {
            perror("dup2 error");
            exit(1);
        }
    }
    if (rd_out) { //redirect to output file if necessary
        result = dup2(out_fd, 1);
        if (result == -1) {
            perror("dup2 error");
        }
    }
    execvp(args[0], args);
    exit(0);
}

bool check_bg(char** args, int argn, bool fg_mode) {
    bool contains_amp = false;

    if (strcmp(args[argn - 1], "&") == 0) { //check if last argument is ampersand
        contains_amp = true;
    }

    if ((contains_amp == true) & (fg_mode == false)) { //it's only a bg process if the last arg is &
                                                       //and the shell is not in fg only mode
        return true;
    }

    return false;
}