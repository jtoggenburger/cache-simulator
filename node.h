#pragma once

typedef struct Node Node;

struct Node {
  char *item;
  Node *left;
  Node *right;
};

Node *node_create(char *item);

void node_delete(Node **n);

void node_print(Node *n);
