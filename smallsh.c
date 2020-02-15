#include "smallsh_builtins.h"

#define MAX_ARGS 512
#define COMMAND_MAX_LENGTH 2048

int main (int* argc, char** argv) {
    int n_chars = -5, i = 0, fg_status;
    bool if_sig, fg_mode;
    size_t buf_size = -5;
    char* line = NULL;
    char args[MAX_ARGS][COMMAND_MAX_LENGTH];
    char curdir[1000];
    char buf[1000];

    for (i = 0; i < MAX_ARGS; i++) {
        memset(args[i], '\0', sizeof(args[i]));
    }

    return 0;
}