/*
    Name: Hai Dang Hoang
    Email: goldsea5191@gmail.com
    Shell.c
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
#include "builtin_cmd.h"

#define COMMAND_BUFSIZE 1024
#define STRTOK_BUFSIZE 64
#define STRTOK_DELIM " \t\r\n\a"

char *lsh_read_command(void);
char **lsh_parse_command(char *);
int lsh_execute(char **);

int main(int argc, char *argv[])
{
  char * cmd, **tokens;
  int status;
  do {
    printf("MY SHELL > ");
    fflush (stdout);
    cmd = lsh_read_command();
    tokens = lsh_parse_command(cmd);
    status = lsh_execute(tokens);
  } while(status !=0);

  exit(EXIT_SUCCESS);
}

/*
    lsh_read_command: Read command line from STDIN until hitting
    `Enter` or EOF
    Return: string command line
*/
char *lsh_read_command()
{
  int position;
  char * cmd = malloc (sizeof(char) *COMMAND_BUFSIZE);
  if(!cmd)
  {
      perror("Error memory allocation -cmd");
      exit(EXIT_FAILURE);
  }

  while(1)
  {
      // Read command line from STDIN
      position = read(STDIN_FILENO,cmd,COMMAND_BUFSIZE);
      if (position == -1)
      {
        perror("Error read command line \n");
        exit (EXIT_FAILURE);
      }
      cmd[position] = '\0';
      return cmd;
  }
}

/*
  lsh_parse_command: Function parse the command into a list of arguments
*/

char **lsh_parse_command(char *cmd)
{
  int position = 0;
  char **tokens = malloc (sizeof(char *) * STRTOK_BUFSIZE);
  char *token;
  if(!tokens)
  {
      perror("Error memory allocation - tokens");
      exit(EXIT_FAILURE);
  }
  token = strtok(cmd, STRTOK_DELIM);        // get the first word
  while(token != NULL)
  {
      tokens[position] = token;             // Store parse string in tokens following position
      position ++;                          // Update new position
      token = strtok(NULL, STRTOK_DELIM );  // NULL must be used to get tokens from the previous string
  }
  tokens[position] = NULL;
  return tokens;
}

/*
  lsh_execute: Function execute the command line from user
*/

int lsh_execute(char **args)
{
//  char **command;
  // An empty command was entered
  if(args[0] == NULL)
    return 1;

  /* Compare args with builtin_str to determine what command is */
  for(int i =0;i < builtin_sum(); i++ )
  {
    if(strcmp(args[0],builtin_str[i]) == 0)
     printf("a");
      //return (*builtin_func[i])(args);
  }

  // Launch command
  pid_t pid, childPid;

  pid = fork();
  switch (pid)
  {
      case -1:
        perror("lsh: Error fork \n");
        exit(EXIT_FAILURE);

      case 0: // Child process
        if(execvp(args[0], args)== -1)
        {
          perror("lsh: Error execvp \n");
          exit(EXIT_FAILURE);
        }
        _exit(EXIT_SUCCESS);
      default:
        childPid = wait(NULL);
        if(childPid == -1)
        {
          perror("lsh: Error wait \n");
          exit(EXIT_FAILURE);
        }
  }

  return 1;
}
