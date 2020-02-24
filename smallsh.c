#include "smallsh_sighand.h" //this header files contains all my includes i need
#include <signal.h>

#define MAX_ARGS 512
#define COMMAND_MAX_LENGTH 2048

int main (int* argc, char** argv) {
    int i = 0, fg_status = 0, argn = 0, //i is for loops, fg_status is for the status command, argn is for the number of command line arguments,
    j = 1, in_fd = -1, out_fd = -1, ch_exit = -5;     // j is for other loops, in_fd is for input redirection file descriptor, out_fd is same but output redirection
    bool if_sig = false, fg_mode = false; //if_sig is for checking whether the last fg process was terminated by signal, fg_mode is for toggling foreground-only mode
    char line[COMMAND_MAX_LENGTH]; //this is how i'll read in lines
    char** args; //array of arguments, allocated and freed for each loop
    char* token = 0; //for string tokenization
    struct dynarray* processes = dynarray_create(); //dynamic array for child processes
    pid_t spawn_pid = -2;
    struct sigaction action_sigint = {0}, action_sigtstp = {0};

    void catch_SIGTSTP(int signo) { //trust me, i would love to put this anywhere else, but i need it to access fg_mode flag
        char* msg1 = "Entering foreground-only mode (& is disallowed)\n";
        char* msg2 = "Exiting foreground-only mode (& is re-allowed)\n";
        int msg1_n = 49, msg2_n = 47;

        if (fg_mode == false) {
            write(STDOUT_FILENO, msg1, msg1_n);
            fg_mode = true;
        } else {
            write(STDOUT_FILENO, msg2, msg2_n);
            fg_mode = false;
        }
    }

    action_sigtstp.sa_handler = catch_SIGTSTP;
    sigfillset(&action_sigtstp.sa_mask);
    action_sigtstp.sa_flags = SA_RESTART;

    memset(line, '\0', COMMAND_MAX_LENGTH);

    sigaction(SIGTSTP, &action_sigtstp, NULL);

    while (1) {
        printf(": "); fflush(stdout); //print prompt

        fgets(line, COMMAND_MAX_LENGTH, stdin);

        for (i = 0; line[i] != '\0'; i++) { //get number of words in line (for allocation & looping)
            if ((line[i] == ' ') || (line[i] == '\n')) {
                argn++;
            }
        }

        args = malloc((argn + 1) * sizeof(char*)); //allocate memory for array of arguments + NULL
        for (i = 0; i <= argn; i++) {
            args[i] = malloc((COMMAND_MAX_LENGTH + 1) * sizeof(char));
        }

        for (i = 0; i < argn; i++) { //get those strings set
            memset(args[i], '\0', COMMAND_MAX_LENGTH + 1);
        }

        //below is separating the input and stuffing it in the array
        token = strtok(line, " \n");

        if (token == NULL) {
            continue; //basically i guess if there wasn't really any input in a line without there being a newline?
        }

        strcpy(args[0], token); //fun fact that i learned: you can't do args[0] = token if you dynamically allocated memory! definitely didn't learn that the hard way
        i = 1;

        while (token != NULL) { //gets all the input
            token = strtok(NULL, " \n");
            if (token == NULL) {
                break; //checks if token is null BEFORE trying to put it in the array... lol
            }
            strcpy(args[i], token);
            i++;
        }

        args[argn] = NULL; //terminating NULL for execvp

        if (line[0] == '#') {
            continue; //comments are ignored
        } else {
            if (strcmp("exit", args[0]) == 0) { //these ones are for builtins
                smallsh_exit(processes); //remember to change this line!
            } else if (strcmp("cd", args[0]) == 0) {
                if (argn == 1) {
                    smallsh_cd(NULL); //i'm not really sure what would happen if i tried to put args[1] in if there was no args[1], probably a segfault, so i did this
                } else {
                    smallsh_cd(args[1]);
                }
            } else if (strcmp("status", args[0]) == 0) {
                smallsh_status(fg_status, if_sig);
            } else {
                spawn_pid = fork();
                dynarray_insert(processes, &spawn_pid);
                if (spawn_pid == -1) {
                    perror("child process failed\n");
                    exit(1);
                } else if (spawn_pid == 0) {
                    execvp(args[0], args);
                    exit(0);
                }
                waitpid(spawn_pid, &ch_exit, 0);
                if (WIFEXITED(ch_exit)) {
                    if_sig = false;
                    fg_status = WEXITSTATUS(ch_exit);
                } else {
                    if_sig = true;
                    fg_status = WTERMSIG(ch_exit);
                }
            }
        }

        for (i = 0; i < argn; i++) { //free dynamically allocated memory
            free(args[i]);
        }
        free(args);
        argn = 0; //reset number of arguments
    }
    
    dynarray_free(processes);

    return 0;
}