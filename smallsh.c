#include "smallsh_helpers.h"

#define MAX_ARGS 512
#define COMMAND_MAX_LENGTH 2048

int main (int* argc, char** argv) {
    int i = 0, fg_status = 0, argn = 0, j = 1; //i is for loops, fg_status is for the status command, argn is for the number of command line arguments, j is for other loops
    bool if_sig = false, fg_mode = false; //if_sig is for checking whether the last fg process was terminated by signal, fg_mode is for toggling foreground-only mode
    char line[COMMAND_MAX_LENGTH]; //this is how i'll read in lines
    char** args;
    char tmp[COMMAND_MAX_LENGTH];
    char* token = 0;
    struct dynarray* processes = dynarray_create();

    memset(line, '\0', COMMAND_MAX_LENGTH);

    while (1) {
        printf(":");

        fgets(line, COMMAND_MAX_LENGTH, stdin);

        for (i = 0; line[i] != '\0'; i++) {
            if ((line[i] == ' ') || (line[i] == '\n')) {
                argn++;
            }
        }

        args = malloc(argn * sizeof(char*));
        for (i = 0; i < argn; i++) {
            args[i] = malloc((COMMAND_MAX_LENGTH + 1) * sizeof(char));
        }

        for (i = 0; i < argn; i++) {
            memset(args[i], '\0', COMMAND_MAX_LENGTH + 1);
        }

        token = strtok(line, " \n");

        if (token == NULL) {
            return;
        }

        strcpy(args[0], token);
        i = 1;

        while (token != NULL) {
            token = strtok(NULL, " \n");
            if (token == NULL) {
                break;
            }
            strcpy(args[i], token);
            i++;
        }

        if (line[0] == '#') {
            ;
        } else {
            if (strcmp("exit", args[0]) == 0) {
                smallsh_exit(processes); //remember to change this line!
            } else if (strcmp("cd", args[0]) == 0) {
                if (argn == 1) {
                    smallsh_cd(NULL);
                } else {
                    smallsh_cd(args[1]);
                }
            } else if (strcmp("status", args[0]) == 0) {
                smallsh_status(fg_status, if_sig);
            }
        }

        for (i = 0; i < argn; i++) {
            free(args[i]);
        }
        free(args);
        argn = 0;
    }
    
    //dynarray_free(processes);

    return 0;
}