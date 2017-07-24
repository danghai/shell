CC = gcc
FLAG = -o
CFLAG = -c

all: shell

shell: shell.c  builtin_cmd.o
	$(CC) $(FLAG) shell builtin_cmd.o shell.c
builtin_cmd.o: builtin_cmd.c
	$(CC) $(CFLAG) builtin_cmd.c

clean:
	rm  builtin_cmd.o shell
