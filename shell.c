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
char *lsh_read_command(void);

int main(int argc, char *argv[])
{
  char * cmd;
  do {
    printf("MY SHELL > ");
    fflush (stdout);
    cmd = lsh_read_command();
    printf("%s \n",cmd);  // for testing
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
      perror("Error memory allocation");
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
