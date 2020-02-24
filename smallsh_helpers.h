#ifndef __SMALLSH_HELPERS_H
#define __SMALLSH_HELPERS_H

#include "smallsh_builtins.h"

#define COMMAND_MAX_LENGTH 2048

void get_and_parse_input(char*** args, char line[2048], int* argn);
void check_file_redirect(bool* rd_in, bool* rd_out, char** args, int argn);

#endif