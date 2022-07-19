#include "map.h"

// structure for the doubled linked lists of the table
struct node {
  char *key, *val;
  struct node *next;
  struct node *prev;
};

// the main table
struct node *table[TAILLE_TABLE];

extern int ysh_set(char *key, char *val) {
  int h = hash(key) % TAILLE_TABLE;

  struct node *tmp;
  if ((tmp = elem(key, h)))
    change_val(tmp, val);
  else
    add_kv(key, val, h);
  return 0;
}

extern char *ysh_get(char *key) {
  int h = hash(key) % TAILLE_TABLE;
  struct node *n;
  if ((n = elem(key, h)))
    return n->val;
  return "";
}

extern int ysh_unset(char *key) {
  int h = hash(key) % TAILLE_TABLE;
  struct node *n;
  if ((n = elem(key, h))) {

    if (!n->prev) { // if n is the head
      table[h] = n->next;
      if (n->next) // here we take care of the singleton case
        n->next->prev = NULL;
    }
    else if (!n->next) { // if n is the last
      n->prev->next = NULL;
    } else { // if in the middle
      n->prev->next = n->next;
      n->next->prev = n->prev;
    }

    free(n);
  }
  return 0;
}

// hashes a string using the djb2 hashing algorithm
unsigned int hash(char *s) {
  unsigned long hash = 5381;
  int c;

  while ((c = *s++))
    hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

  return hash;
}

// returns the pointer of the element we search or NULL if not present
struct node *elem(char *key, int h) {
  struct node *cur = table[h];
  while (cur) {
    if (cur->key == key)
      return cur;
    cur = cur->next;
  }
  return NULL;
}

// internal functions for ysh_set

struct node *new_n(char *k, char *v) {
  struct node *n = (struct node *)malloc(sizeof(struct node));
  n->key = k;
  n->val = v;
  n->next = n->prev = NULL;
  return n;
}

void add_kv(char *key, char *val, int h) {
  struct node *n = new_n(key, val);

  if (table[h])
    n->next = table[h];
  table[h] = n;
}

void change_val(struct node *n, char *val) { n->val = val; }
