CC=gcc

all: smallsh

smallsh: smallsh.c dynarray.o smallsh_builtins.o
	$(CC) smallsh.c dynarray.o smallsh_builtins.o -o smallsh

smallsh_builtins.o: smallsh_builtins.c smallsh_builtins.h
	$(CC) -c smallsh_builtins.c

dynarray.o: dynarray.c dynarray.h
	$(CC) -c dynarray.c

clean:
	rm -f dynarray.o smallsh_builtins.o smallsh