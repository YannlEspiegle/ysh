#ifndef COMMANDS_H_
#define COMMANDS_H_

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define NB_BUILTINS 2

extern int ysh_cd(char**);
extern int ysh_exit(char**);

extern char *builtin_str[];
extern int (*builtin_func[]) (char**);

#endif // COMMANDS_H_
