# Stimulate a simple Shell in C

### 1. Shell operation

LSH is a simple implementation of a shell in C. It demonstrates the basics of how a shell works.
The basic operation of a shell is based on three main thing: 

* `Initialize`: In this step, a typical shell would read and execute its configuration files.
These change aspects of the shell's behavior.

* `Interpret`: Next, the shell reads commands from stdin and executes them

* `Terminate`: After its command are executed, the shell executes any shutdown command, 
frees up any memory, and terminates

Therefore, a simple way to handle commands is with three steps:

```C
char *lsh_read_command(void);	    /* Read: Read the command from standard input*/		
char **lsh_parse_command(char *);   /* Parse: Separate the command string into arguments*/
int lsh_execute(char **);           /* Execute: Run the parsed command */
``` 

These functions are put into the `main` function: 

```C
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
```

### Shell management

The commands of shell are managed by array of string `builtin_str` and function pointer 
`builtin_func`. If you want to contribute and improve or add command the shell, just add 
name the command in `builtin_str`, and  implemented function in `builtin_func` function pointer.
I just simply implement 4 basic operation including:

1. help: Provide information all commands are implemented  
2. exit: exit the Shell
3. pwd: get current directory.
4. cd:  changes directory

```C
/*
  List total commands in Shell
*/
char *builtin_str[] = {
  "help",
  "exit",
  "pwd",
  "cd"
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

```

# [Shell Script](https://github.com/danghai/shell/tree/master/shell_script)

Reference: 

[https://www.shellscript.sh/index.html](https://www.shellscript.sh/index.html)
