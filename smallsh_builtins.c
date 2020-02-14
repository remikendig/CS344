#include "smallsh_builtins.h"
#include <unistd.h>

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

void smallsh_status() {

}