#ifndef MAIN_H_
#define MAIN_H_

// libs
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <wait.h>

// prototypes
void ysh_loop(void);
char *ysh_read_line(void);
char **ysh_get_args(char *);
int ysh_launch(char **);
int ysh_execute(char **);

// Constants
#define YSH_RL_BUFSIZE 1024 // read_line buffer

// args parser constants
#define YSH_ARGS_BUFSIZE 64
#define YSH_ARGS_DELIM " \r\t\n\a"


#endif // MAIN_H_
