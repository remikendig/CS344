#include "smallsh_builtins.h"

void smallsh_exit() {
    
}

void smallsh_cd(char* path) {
    char homeenv[1000];

    strcpy(homeenv, getenv("HOME"));

    if (path == NULL) {
        chdir(homeenv);
    } else {
        chdir(path);
    }
}

void smallsh_status(int p_status, bool if_sig) {
    if (if_sig) {
        printf("terminated by signal %d", p_status);
    } else {
        printf("exit status %d", p_status);
    }
}