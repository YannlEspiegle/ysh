#include "main.h"
#include "commands.h"
#include <signal.h>
#include <stdio.h>
#include <time.h>

int main(int argc, char *argv[]) {
  ysh_loop();

  return EXIT_SUCCESS;
}

void ysh_loop() {
  char *line;
  char **args;
  int status;

  do {
    printf("> ");
    line = ysh_read_line();
    args = ysh_get_args(line);
    status = ysh_execute(args);

    free(line);
    free(args);
  } while (status);
}

char *ysh_read_line(void) {
  size_t bufsize = YSH_RL_BUFSIZE;
  char *buffer = malloc(sizeof(char) * bufsize);

  if (!buffer) {
    fprintf(stderr, "ysh : allocation error");
    exit(EXIT_FAILURE);
  }

  int c, i = 0;

  while (1) {
    if ((c = getchar()) == EOF || c == '\n') {
      buffer[i] = '\0';
      return buffer;
    } else {
      buffer[i] = c;
    }
    i++;

    // If we have exceeded the buffer, reallocate.
    if (i >= bufsize) {
      bufsize += YSH_RL_BUFSIZE;
      buffer = realloc(buffer, bufsize);
      if (!buffer) {
        fprintf(stderr, "ysh: allocation error\n");
        exit(EXIT_FAILURE);
      }
    }
  }
}

char **ysh_get_args(char *line) {
  size_t bufsize = YSH_ARGS_BUFSIZE;
  char **tokens = malloc(sizeof(char *) * bufsize);

  if (!tokens) {
    fprintf(stderr, "ysh : allocation error");
    exit(EXIT_FAILURE);
  }

  char *token = strtok(line, YSH_ARGS_DELIM);
  int i = 0;
  while (token != NULL) {
    tokens[i] = token;
    i++;

    // reallocate
    if (i >= bufsize) {
      bufsize += YSH_ARGS_BUFSIZE;
      tokens = realloc(tokens, bufsize);

      if (!tokens) {
        fprintf(stderr, "ysh : allocation error");
        exit(EXIT_FAILURE);
      }
    }
    token = strtok(NULL, YSH_ARGS_DELIM);
  }
  tokens[i] = NULL;
  return tokens;
}

int ysh_execute(char **args) {
  if (args[0] == NULL)
    return 1;
  for (int i = 0; i < NB_BUILTINS; i++) {
    if (strcmp(args[0], builtin_str[i]) == 0)
      return (*builtin_func[i])(args);
  }

  return ysh_launch(args);
}

pid_t pid;

void INTHandler_kill(int signum) {
  kill(pid, signum);
}

int ysh_launch(char **args) {
  int status;

  pid = fork();
  if (pid == 0) {
    if (execvp(args[0], args) == -1) {
      perror("ysh");
    }
    exit(EXIT_FAILURE);
  } else if (pid < 0) {
    perror("ysh");
  } else {
    do {
      signal(SIGINT, INTHandler_kill);
      waitpid(pid, &status, WUNTRACED);
    } while (!WIFEXITED(status) && !WIFSIGNALED(status));
  }

  return 1;
}

