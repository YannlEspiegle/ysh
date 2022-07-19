#ifndef MAP_H_
#define MAP_H_

#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#define TAILLE_TABLE 100

extern int ysh_set(char*, char*); // adds (or change the value of) a (key, value)
                                  // pair into the table of variables
extern char *ysh_get(char*); // returns the value binded with a certain key
                             // if key isn't present, returns ""
extern int ysh_unset(char*); // deletes a variable from memory

unsigned int hash(char *);
struct node *elem(char *, int);

struct node *new_n(char *, char *);
void add_kv(char *, char *, int);
void change_val(struct node *, char *);

#endif // MAP_H_
