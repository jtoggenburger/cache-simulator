//-----------------------------------------------
// Jack Toggenburger
//
// clock_cache.c
// Implementation of a clock cache in c
//-----------------------------------------------

#include "clock_cache.h"

struct clockCache {

  Node *seen;           // BST containing seen items
  struct data **memory; // array simulating a cache memory

  int size;     // cache size
  int cum_miss; // cumpulsory misses
  int cap_miss; // capacity misses
  int hand;
};

struct data {
  char *item;
  int value;
};

data_t *data_new(char *item) {

  data_t *d = (data_t *)malloc(sizeof(data_t));

  if (d) {
    d->item = strdup(item);
    d->value = 0;
  }

  return d;
}

void data_delete(data_t **d) {

  if (*d) {
    free((*d)->item);
    free(*d);
    *d = NULL;
  }

  return;
}

clockCache_t *clockCache_new(int size) {

  clockCache_t *c = (clockCache_t *)malloc(sizeof(clockCache_t));

  if (c) {

    c->seen = bst_create();
    c->memory =
        (data_t **)malloc(size * sizeof(data_t *)); // THIS IS UNINITIALIZED

    // set all parts of memory to NULL
    for (int i = 0; i < size; i++) {
      c->memory[i] = NULL;
    }

    c->size = size;
    c->cum_miss = 0;
    c->cap_miss = 0;
    c->hand = 0;
  }

  return c;
}

void clockCache_delete(clockCache_t **c) {

  if (*c) {

    for (int i = 0; i < (*c)->size; i++) {
      if ((*c)->memory[i] != NULL) {
        data_delete(&(*c)->memory[i]);
      }
    }

    free((*c)->memory);

    bst_delete(&(*c)->seen);
    free(*c);
    *c = NULL;
  }

  return;
}

// returns true if item found, false if not
int clock_contains(clockCache_t *c, char *item) {

  for (int i = 0; i < c->size; i++) {
    if (c->memory[i]) {
      if (strcmp(c->memory[i]->item, item) == 0) {
        return i;
      }
    }
  }

  return -1;
}

// removes item at index
void clock_remove(clockCache_t *c, int index) {
  data_delete(&(c->memory[index]));
  return;
}

// returns items value (0, 1) or -1 if not found
int clock_lookup(clockCache_t *c, int index) {

  data_t *d = c->memory[index];

  if (d) {
    return d->value;
  }

  return -1;
}

// modifies the item to value
void clock_modify(clockCache_t *c, int index, int value) {

  c->memory[index]->value = value;

  return;
}

// inserts an item at index
void clock_insert(clockCache_t *c, char *item, int index) {

  if (index > c->size) {
    fprintf(stderr, "ERROR: clock_insert: index is out of bounds\n");
    return;
  }

  c->memory[index] = data_new(item);
  return;
}

void clock_print(clockCache_t *c) {

  printf("%d %d\n", c->cum_miss, c->cap_miss);

  return;
}

void insert_clock(clockCache_t *c, char *item) {

  // if item exists in cache
  int item_index = clock_contains(c, item);
  if (item_index != -1) {

    // set its value to 1
    clock_modify(c, item_index, 1);
    printf("HIT\n");
    return;
  }

  // eviction protocol
  while (true) {

    // if item at clock hand exists
    int item_value = clock_lookup(c, c->hand);
    if (item_value != -1) {

      // if items value is 1, set to 0 and increment
      if (item_value == 1) {
        clock_modify(c, c->hand, 0);
        c->hand = (c->hand + 1) % c->size;
      }

      // if value is 0, evict
      else {
        clock_remove(c, c->hand);
        break;
      }
    }

    else {
      break;
    }
  }

  // determine if compulsory or capacity hit
  if (!bst_find(c->seen, item)) {
    // if item has never been seen before, compulsory hit
    c->cum_miss++;

    // add it to seen items
    c->seen = bst_insert(c->seen, item);

  } else {
    // a capacity miss
    c->cap_miss++;
  }

  clock_insert(c, item, c->hand);
  c->hand = (c->hand + 1) % c->size;
  printf("MISS\n");
  return;
}
