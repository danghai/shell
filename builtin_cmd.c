/*
    Name: Hai Dang Hoang
    Email: goldsea5191@gmail.com

    builtin_cmd.h:
*/


#include "builtin_cmd.h"


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
      printf("  %s\n",builtin_str[i]);
  return 1;
}
/*
  lsh_exit: command exit the Shell
*/

int lsh_exit(char **args)
{
    return 0;
}
