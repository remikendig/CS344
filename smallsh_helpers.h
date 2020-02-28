#ifndef __SMALLSH_HELPERS_H
#define __SMALLSH_HELPERS_H

#include "smallsh_builtins.h"

#define COMMAND_MAX_LENGTH 2048

void get_and_parse_input(char*** args, char line[2048], int* argn);
void check_file_redirect(bool* rd_in, bool* rd_out, char** args, int argn, int* fd_in, int* fd_out);
int search_process_array(struct dynarray* processes);
void expand_pid(char* arg, int argn);
void bg_process(char** args, int argn);
void fg_process(char** args, int argn);
bool check_bg(char** args, int argn, bool fg_mode);

#endif