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

#define COMMAND_BUFSIZE 1024
#define STRTOK_BUFSIZE 64
#define STRTOK_DELIM " \t\r\n\a"

char *lsh_read_command(void);
char **lsh_parse_command(char *);

int main(int argc, char *argv[])
{
  char * cmd, **tokens;
  do {
    printf("MY SHELL > ");
    fflush (stdout);
    cmd = lsh_read_command();
    tokens = lsh_parse_command(cmd);
    printf("%s \n",tokens[1]);  // for testing
  } while(1);

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
