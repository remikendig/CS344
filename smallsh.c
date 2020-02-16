#include "smallsh_builtins.h"

#define MAX_ARGS 512
#define COMMAND_MAX_LENGTH 2048

int main (int* argc, char** argv) {
    int i = 0, fg_status = 0, argn = 0, j = 1; //i is for loops, fg_status is for the status command, argn is for the number of command line arguments, j is for other loops
    bool if_sig = false, fg_mode = false; //if_sig is for checking whether the last fg process was terminated by signal, fg_mode is for toggling foreground-only mode
    char line[COMMAND_MAX_LENGTH]; //this is how i'll read in lines
    struct dynarray* args;
    char* token = 0;
    //char args[MAX_ARGS][COMMAND_MAX_LENGTH];

    args = dynarray_create();
    //struct dynarray* processes = dynarray_create();

    memset(line, '\0', COMMAND_MAX_LENGTH);

    while (1) {
        printf(":");
        dynarray_free(args);
        args = dynarray_create();

        fgets(line, COMMAND_MAX_LENGTH, stdin);
        token = strtok(line, " \n");

        if (token == NULL) {
            continue;
        }

        dynarray_insert(args, token);

        if (line[0] == '#') {
            ;
        } else {
            printf("%s\n", dynarray_get(args, 0));
            fflush(stdout);
        }
    }

    
    
    dynarray_free(args);
    //dynarray_free(processes);

    return 0;
}