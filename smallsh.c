#include "smallsh_builtins.h"

#define MAX_ARGS 512
#define COMMAND_MAX_LENGTH 2048

int main (int* argc, char** argv) {
    int i = 0, fg_status = 0, argn = 0; //i is for loops, fg_status is for the status command, argn is for the number of command line arguments
    bool if_sig = false, fg_mode = false; //if_sig is for checking whether the last fg process was terminated by signal, fg_mode is for toggling foreground-only mode
    char line[COMMAND_MAX_LENGTH]; //this is how i'll read in lines
    //char args[MAX_ARGS][COMMAND_MAX_LENGTH];

    struct dynarray* args = dynarray_create();
    struct dynarray* processes = dynarray_create();

    fgets(line, COMMAND_MAX_LENGTH, stdin);
    printf("%s\n", line);
    fflush(stdout);



    dynarray_free(args);
    dynarray_free(processes);

    return 0;
}