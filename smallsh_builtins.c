#include "smallsh_builtins.h"

/*
*   Function: smallsh_exit()
*   Status: INCOMPLETE
*   Purpose: To kill all child processes, foreground and background,
*            and exit the shell.
*   Preconditions: N/A
*   Postconditions: The shell is exited.
*/
void smallsh_exit(struct dynarray* processes) {
    exit(0);
}

/*
*   Function: smallsh_cd()
*   Status: DONE
*   Purpose: To function the same as cd in bash; changes to the directory
*            specified by path, or the path specified by the HOME environment
*            variable if no path is specified.
*   Preconditions: path is a valid string, or NULL.
*   Postconditions: The working directory of the program is changed.
*/
void smallsh_cd(char* path) {
    char homeenv[1000];

    strcpy(homeenv, getenv("HOME"));

    if (path == NULL) {
        chdir(homeenv);
    } else {
        chdir(path);
    }
}

/*
*   Function: smallsh_status()
*   Status: UNTESTED
*   Purpose: To print out the exit status of the last foreground
*            process to run. If no foreground processes have been
*            run, prints out 0. Also specifies whether the process
*            ended or was terminated by a signal.
*   Preconditions: N/A
*   Postconditions: N/A
*/
void smallsh_status(int p_status, bool if_sig) {
    if (if_sig) {
        printf("terminated by signal %d", p_status);
    } else {
        printf("exit status %d", p_status);
    }
}