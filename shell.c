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

/*
  3 main function in shell:
  1) read a command
  2) parse the command
  3) execute the command
*/
char *lsh_read_command(void);
char **lsh_parse_command(char *);
int lsh_execute(char **);
/*
    Function declarations for builtin shell commands:
*/
int lsh_cd(char **args);
int lsh_help(char **args);
int lsh_exit(char **args);
int lsh_pwd (char **args);


/*
  List total commands in Shell
*/
int builtin_sum();
char *builtin_str[] = {
  "help",
  "exit",
  "pwd"
};

/*
  Function pointer used for pointing to function of implemented command
*/

int (*builtin_func[]) (char **) =
{
  &lsh_help,
  &lsh_exit,
  &lsh_pwd,
  &lsh_cd
};

/*
  MAIN FILE --------------------------------------------------------------------
*/
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

//  Compare args with builtin_str to determine what command is
  for(int i =0;i < builtin_sum(); i++ )
  {
    if(strcmp(args[0],builtin_str[i]) == 0)
      return (*builtin_func[i])(args);
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


/*
    builtin_sum: Total commands in Shells
*/

int builtin_sum()
{
  return sizeof(builtin_str) / sizeof(char *);
}

/*
  lsh_help: command provides information for user
*/
int lsh_help(char **args)
{
  int i;
  printf("*-----------------------------------------------------*\n");
  printf("*         Welcome to Hai Dang Hoang's Shell           *\n");
  printf("*   Type command line and arguments, and hit enter .  *\n");
  printf("*-----------------------------------------------------*\n");
  printf("The following command line built in Shell: \n");
  for(i =0;i < builtin_sum(); i++)
      printf("[%d]%s\n",i+1,builtin_str[i]);
  return 1;
}
/*
  lsh_exit: command exit the Shell
*/

int lsh_exit(char **args)
{
    return 0;
}

/*
  lsh_pwd: command get current directory.
  Using char *getenv(char *args): searches for the environment string
  pointed to by args and returns the associated value to the string
  Return -1: for error and return 1 for success command
*/

int lsh_pwd(char **args)
{
  char * env;
  if((env = getenv("PWD")) == NULL)
  {
    fprintf(stderr,"%s: Fail pwd \n",args[0]);
    return -1;
  }
  else
    printf("%s \n",env);
  return 1;
}
/*
  lsh_cd: command changes directory
*/

int lsh_cd(char **args)
{
  if (args[1] == NULL) {
    fprintf(stderr, "lsh: expected argument to \"cd\"\n");
  } else {
    if (chdir(args[1]) != 0) {
      perror("lsh");
    }
  }
  return 1;
}
