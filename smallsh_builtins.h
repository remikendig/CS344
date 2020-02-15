#ifndef __SMALLSH_BUILTINS_H
#define __SMALLSH_BUILTINS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>

#include "dynarray.h"

void smallsh_exit(struct dynarray* processes);
void smallsh_cd(char* path);
void smallsh_status(int p_status, bool if_sig);

#endif