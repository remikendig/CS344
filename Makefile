CC=gcc -g

all: smallsh

smallsh: smallsh.c dynarray.o smallsh_builtins.o smallsh_helpers.o
	$(CC) smallsh.c dynarray.o smallsh_builtins.o smallsh_helpers.o -o smallsh

smallsh_helpers.o: smallsh_helpers.c smallsh_helpers.h
	$(CC) -c smallsh_helpers.c

smallsh_builtins.o: smallsh_builtins.c smallsh_builtins.h
	$(CC) -c smallsh_builtins.c

dynarray.o: dynarray.c dynarray.h
	$(CC) -c dynarray.c

clean:
	rm -f dynarray.o smallsh_builtins.o smallsh_helpers.o smallsh