CC = gcc
FLAG = -o
CFLAG = -c

all: shell

shell: shell.c
	$(CC) $(FLAG) shell shell.c

clean: 
	rm shell
