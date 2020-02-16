#ifndef __SMALLSH_HELPERS_H
#define __SMALLSH_HELPERS_H

#include "smallsh_builtins.h"

#define COMMAND_MAX_LENGTH 2048

void get_and_parse_input(struct dynarray* args, char line[2048]);

#endif