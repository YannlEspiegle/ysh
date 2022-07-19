#include <stdio.h>
#include <string.h>
#include "../src/map.h"
#include "minunit.h"

int tests_run = 0;

static char *test_setget() {
    ysh_set("foo", "bonjour");
    mu_assert("Error, get and set", strcmp(ysh_get("foo"), "bonjour") == 0);
    return 0;
}

static char *test_emptyget() {
    mu_assert("Error, get when value not stored", strcmp(ysh_get("bar"), "") == 0);
    return 0;
}

static char *test_unset() {
    ysh_unset("foo");
    mu_assert("Error, unset", strcmp(ysh_get("foo"), "") == 0);
    return 0;
}

static char *test_setget_rename() {
    ysh_set("babar", "salut");
    mu_assert("Error, get and set", strcmp(ysh_get("babar"), "salut") == 0);
    ysh_set("babar", "coucou");
    mu_assert("Error, set rename", strcmp(ysh_get("babar"), "coucou") == 0);
    return 0;
}

static char *all_tests() {
    mu_run_test(test_setget);
    mu_run_test(test_emptyget);
    mu_run_test(test_unset);
    mu_run_test(test_setget_rename);
    return 0;
}

int main(int argc, char *argv[]) {
    char *result = all_tests();
    if(result != 0) {
        printf("%s\n", result);
    } else {
        printf("ALL TESTS PASSED\n");
    }

    printf("Tests run: %d\n", tests_run);
    return 0;
}
