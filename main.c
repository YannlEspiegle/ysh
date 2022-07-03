#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <wait.h>

void ysh_loop(void);
char *ysh_read_line(void);
char **ysh_get_args(char *);
int ysh_launch(char **);

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
    status = ysh_launch(args);

    free(line);
    free(args);
  } while (status);
}

#define YSH_RL_BUFSIZE 1024

char *ysh_read_line(void) {
  size_t bufsize = YSH_RL_BUFSIZE;
  char *buffer = malloc(sizeof(char) * bufsize);

  if (!buffer) {
    fprintf(stderr, "ysh : allocation error");
    exit(EXIT_FAILURE);
  }

  int c, i;

  for (i = 0;; i++) {
    // reallocate if buffer too short
    if (i >= bufsize) {
      bufsize += YSH_RL_BUFSIZE;
      buffer = realloc(buffer, bufsize);
      if (!buffer) {
        fprintf(stderr, "ysh : allocation error");
        exit(EXIT_FAILURE);
      }
    }

    // get the current line
    if ((c = getchar()) == EOF || c == '\n') {
      buffer[i] = c;
      return buffer;
    } else {
      buffer[i] = c;
    }
  }
}

#define YSH_ARGS_BUFSIZE 64
#define YSH_ARGS_DELIM " \r\t\n\a"

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

int ysh_launch(char **args) {
  pid_t pid, wpid;
  int status;

  pid = fork();
  if(pid == 0) {
    if(execvp(args[0], args) == -1) {
      perror("ysh");
    }
    exit(EXIT_FAILURE);
  } else if (pid < 0) {
    perror("ysh");
  } else {
    do {
      wpid = waitpid(pid, &status, WUNTRACED);
    } while (!WIFEXITED(status) && ! WIFSIGNALED(status));
  }

  return 1;
}
