#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "node.h"

// creates a node
Node *node_create(char *item) {
  Node *n = (Node *)malloc(sizeof(Node));

  n->item = strdup(item);
  n->left = NULL;
  n->right = NULL;
  return n;
}

// deletes a node
void node_delete(Node **n) {
  free((*n)->item);
  free(*n);
  *n = NULL;
  return;
}

void node_print(Node *n) {
  if (n) { // if node is not NULL (root)
    fprintf(stderr, "%s ", n->item);
  }
  return;
}
