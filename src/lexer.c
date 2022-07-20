#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define YSH_RL_BUFSIZE 100

char whitespaces[] = " \t\r\n\v";
char symbols[] = "&()|<>";

// start_tok and end_tok are changed to get the position of the token
// the int result indicates which type of token it is
int get_token(char **pstart, char *end_string, char **start_tok,
              char **end_tok) {
  char *cur;
  cur = *pstart;
  for (; cur < end_string && strchr(whitespaces, *cur); cur++)
    ;

  if (start_tok)
    *start_tok = cur;
  int ret = *cur;
  switch (*cur) {
  case 0: // end of string
    break;
  case '|':
  case '(':
  case ')':
  case ';':
  case '<':
    cur++;
    break;
  case '>':
    cur++;
    if (*cur == '>') {
      ret = '+';
      cur++;
    }
    break;
  default:
    ret = 'a';
    while (cur < end_string && !strchr(whitespaces, *cur) && !strchr(symbols, *cur))
      cur++;
    break;
  }
  if (end_tok)
    *end_tok = cur;

  while (cur < end_string && strchr(whitespaces, *cur))
    cur++;
  *pstart = cur; // set the start for the future call to get_token
  return ret;
}
