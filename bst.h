#pragma once

#include "node.h"
#include <stdbool.h>
#include <stdint.h>

Node *bst_create(void);

uint32_t bst_height(Node *root);

uint32_t bst_size(Node *root);

Node *bst_find(Node *root, char *item);

Node *bst_insert(Node *root, char *item);

void bst_print(Node *root);

void bst_delete(Node **root);

Node *bst_remove(Node *root, char *item);
