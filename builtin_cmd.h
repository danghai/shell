/*
    Name: Hai Dang Hoang
    Email: goldsea5191@gmail.com

    builtin_cmd.h:
*/

#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/wait.h>
#include <sys/types.h>
#ifndef BUILTIN_CMD_H
#define BUILTIN_CMD_H

/*
    List of builtin commands in Shell
*/
char *builtin_str[] = {
  "cd",
  "ls",
  "exit",
  "help"
};

/*
    Function declarations for builtin shell commands:
*/
int lsh_cd(char **args);
int lsh_help(char **args);
int lsh_exit(char **args);

/*
   Function pointer commands in Shell

int (*builtin_func[]) (char **) = {
//  &lsh_cd,
  &lsh_help,
  &lsh_exit
};
 */
/*
  Support Function
*/

// return total command in Shell

int builtin_sum();

#endif
