#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>

#include "smallsh_builtins.h"

#define MAX_ARGS 512
#define COMMAND_MAX_LENGTH 2048

int main (int* argc, char** argv) {
    int n_chars = -5, i = 0;
    size_t buf_size = -5;
    char* line = NULL;
    char args[MAX_ARGS][COMMAND_MAX_LENGTH];

    for (i = 0; i < MAX_ARGS; i++) {
        memset(args[i], '\0', sizeof(args[i]));
    }

    while (1) {
        printf(": ");
        fflush(stdout);
        n_chars = getline(&line, &buf_size, stdin);
        printf("%s", line);
        fflush(stdout);
    }

    return 0;
}