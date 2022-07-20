#include "../src/lexer.h"
#include "minunit.h"
#include <stdio.h>
#include <string.h>

int tests_run = 0;

char *test_gettoken() {
  char *s = "   coucou|     & tout le monde";
  char **pstart = &s, *tok, *etok;
  char *end = s + strlen(s);

  char result[] = "coucou";
  int i;

  get_token(pstart, end, &tok, &etok);
  char *cur;
  for (cur = tok, i = 0; cur < etok; cur++, i++) {
    mu_assert("Error gettoken", *cur == result[i]);
  }

  int ret = get_token(pstart, end, &tok, &etok);
  mu_assert("Error gettoken", etok == tok + 1 && *tok == '|' && ret == '|');
  return 0;
}

char *test_endgettoken() {
  char *s = "   coucou  ";
  char **pstart = &s, *tok, *etok;
  char *end = s + strlen(s);

  get_token(pstart, end, &tok, &etok);
  int ret = get_token(pstart, end, &tok, &etok);
  mu_assert("Error gettoken EOstring", ret == 0 && tok == etok);

  return 0;
}

static char *all_tests() {
  mu_run_test(test_gettoken);
  mu_run_test(test_gettoken);
  return 0;
}

int main(void) {
  char *result = all_tests();
  if (result != 0) {
    printf("%s\n", result);
  } else {
    printf("ALL TESTS PASSED\n");
  }

  printf("Tests run: %d\n", tests_run);
  return 0;
}
