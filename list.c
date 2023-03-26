//-----------------------------------------------
// list.c
//
// Jack Toggenburger
// implementation of a linked list in c
//
//-----------------------------------------------

#include "list.h"

// Node constructors
// --------------------------------------------------------------------

struct node {
  char *item;
  struct node *next;
};

node_t *nodeCreate(char *item) {

  node_t *n = malloc(sizeof(node_t));

  if (n) {
    n->item = strdup(item);
    n->next = NULL;
  }

  return n;
}

void nodeDelete(node_t **n) {

  if (n && *n) {
    free((*n)->item);
    free(*n);
    *n = NULL;
  }

  return;
}

// List constructors
// --------------------------------------------------------------------
struct list {
  node_t *front;
  int count;
};

list_t *list_new(void) {

  list_t *l = malloc(sizeof(list_t));

  if (l) {
    l->front = NULL;
    l->count = 0;
  }

  return l;
}

void list_delete(list_t **l) {

  if (*l) {

    node_t *curr = (*l)->front;
    node_t *next = curr;

    while (curr != NULL) {
      next = curr->next;
      nodeDelete(&curr);
      curr = next;
    }

    free(*l);
    *l = NULL;
  }

  return;
}

// List functions
// -----------------------------------------------------------------------
int list_count(list_t *l) { return l->count; }

bool list_contains(list_t *l, char *item) {

  node_t *curr = l->front;

  while (curr != NULL) {
    if (strcmp(curr->item, item) == 0) {
      return true;
    }

    curr = curr->next;
  }

  return false;
}

void list_rfront(list_t *l) {

  if (l->front == NULL) {
    return;
  }

  node_t *temp = l->front;
  l->front = l->front->next;

  nodeDelete(&temp);
  l->count--;

  return;
}

void list_rfirst(list_t *l, char *item) {

  node_t *curr = l->front;
  node_t *prev = curr;

  while (curr != NULL) {
    if (strcmp(curr->item, item) == 0) {
      prev->next = curr->next;

      if (curr == l->front) {
        l->front = curr->next;
      }

      nodeDelete(&curr);
      l->count--;
      break;
    }
    prev = curr;
    curr = curr->next;
  }

  return;
}

void list_append(list_t *l, char *item) {

  if (l->front == NULL) {
    l->front = nodeCreate(item);
    l->count++;
    return;
  }

  node_t *curr = l->front;

  while (curr->next != NULL) {
    curr = curr->next;
  }

  curr->next = nodeCreate(item);
  l->count++;
  return;
}

void list_print(list_t *l) {

  node_t *curr = l->front;

  while (curr != NULL) {
    fprintf(stdout, "%s ", curr->item);
    curr = curr->next;
  }

  fprintf(stdout, "\n");

  return;
}
