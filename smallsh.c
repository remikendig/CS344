#include "smallsh_builtins.h"

#define MAX_ARGS 512
#define COMMAND_MAX_LENGTH 2048

int main (int* argc, char** argv) {
    int i = 0, fg_status = 0, argn = 0, j = 1; //i is for loops, fg_status is for the status command, argn is for the number of command line arguments, j is for other loops
    bool if_sig = false, fg_mode = false; //if_sig is for checking whether the last fg process was terminated by signal, fg_mode is for toggling foreground-only mode
    char line[COMMAND_MAX_LENGTH]; //this is how i'll read in lines
    struct dynarray* args;
    char* token = 0;

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
        //printf("%s\n", dynarray_get(args, 0));
        //fflush(stdout);

        while (token != NULL) {
            token = strtok(NULL, " \n");
            if (token == NULL) {
                break;
            }
            dynarray_insert(args, token);
            //printf("%s\n", dynarray_get(args, (dynarray_size(args) - 1)));
            //fflush(stdout);
        }

        if (line[0] == '#') {
            ;
        } else {
            for (i = 0; i < dynarray_size(args); i++) {
                printf("%s\n", dynarray_get(args, i));
                fflush(stdout);
            }
        }
    }
    
    dynarray_free(args);
    //dynarray_free(processes);

    return 0;
}