#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bst.h"
#include "node.h"

// extern variable for stats
uint64_t branches = 0;

// creates an empty BST, aka a wrapper for NULL
Node *bst_create(void) { return NULL; }

// deletes the tree using a post-order traversal
// credit: Professor Long, Lecture-18-Trees-and-BST.pdf, slide 76
void bst_delete(Node **root) {
  if (*root) {
    bst_delete(&(*root)->left);
    bst_delete(&(*root)->right);
    node_delete(root);
  }
  return;
}

// returns the height of a tree (the longest distance from the root to a node)
// credit: Professor Long, Lecture-18-Trees-and-BST.pdf, slide 55
uint32_t bst_height(Node *root) {
  if (root) {
    return 1 + fmax(bst_height(root->left), bst_height(root->right));
  }
  // otherwise the tree is empty
  return 0;
}

// returns the size of a tree (number of nodes)
uint32_t bst_size(Node *root) {
  if (root) {
    return 1 + bst_size(root->left) + bst_size(root->right);
  }
  // otherwise the tree is empty
  return 0;
}

// finds if a node is in root, returns NULL if not
Node *bst_find(Node *root, char *item) {
  if (root) {
    // if they are the same
    if (strcmp(root->item, item) == 0) {
      return root;
    }

    // if oldspeak is greater than, go to the left
    if (strcmp(root->item, item) > 0) {
      return bst_find(root->left, item);
    } else { // if oldspeak is less than, go right
      return bst_find(root->right, item);
    }
    return root;
  }
  // if root is empty, return NULL
  return NULL;
}

Node *bst_min(Node *root) {

  Node *curr = root;

  while (curr->left != NULL) {
    curr = curr->left;
  }

  return curr;
}

Node *bst_remove(Node *root, char *item) {

  if (root) {

    if (strcmp(item, root->item) < 0) {
      root->left = bst_remove(root->left, item);
    }

    else if (strcmp(item, root->item) > 0) {
      root->right = bst_remove(root->right, item);
    }

    else {

      if (root->left == NULL) {

        Node *temp = node_create(root->right->item);
        temp->left = root->right->left;
        temp->right = root->right->right;
        node_delete(&root);
        return temp;
      }

      else if (root->right == NULL) {

        Node *temp = node_create(root->left->item);
        temp->left = root->left->left;
        temp->right = root->left->right;
        node_delete(&root);
        return temp;
      }

      root->item = bst_min(root->right)->item;
      root->right = bst_remove(root->right, root->item);
    }
  }

  return root;
}

// inserts a node into root, will not insert a duplicate
// credit: Professor Long, Lecture-18-Trees-and-BST.pdf, slide 62
Node *bst_insert(Node *root, char *item) {
  if (root) {
    // the oldspeak is already in the tree
    if (strcmp(root->item, item) == 0) {
      return root;
    }

    // see if the new node needs to go to the left or right
    if (strcmp(root->item, item) > 0) { // og is > 0
      root->left = bst_insert(root->left, item);
    } else {
      root->right = bst_insert(root->right, item);
    }
    return root;
  }
  return node_create(item);
}

// prints out a binary tree using in order traversal
// credit: Professor Long, Lecture-18-Trees-and-BST.pdf, slide 21
void bst_print(Node *root) {
  if (root) {
    bst_print(root->left);
    node_print(root);
    bst_print(root->right);
  }
  return;
}
