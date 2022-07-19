#include "commands.h"

char *builtin_str[] = {"cd", "exit"};

int (*builtin_func[]) (char**) = {
    &ysh_cd,
    &ysh_exit
};

int ysh_cd(char **args) {
  if (args[1] == NULL) { // go to $HOME dir
    fprintf(stderr, "lsh: expected argument for \"cd\"");
  } else if (chdir(args[1]) != 0) {
    perror("ysh");
  }
  return 1;
}

int ysh_exit(char **args) { return 0; }
