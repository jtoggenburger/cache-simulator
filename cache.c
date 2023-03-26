//-----------------------------------------------
// cache.c
//
// Jack Toggenburger
// A cache simulator in c
//-----------------------------------------------

#include "cache.h"

// normal cache
struct cache {

  Node *seen;     // BST containing seen items
  list_t *memory; // List simulating cache memory

  int size;     // cache size
  int cum_miss; // cumpulsory misses
  int cap_miss; // capacity misses
};

cache_t *cache_new(int size) {

  cache_t *c = malloc(sizeof(cache_t));

  if (c) {
    c->seen = bst_create();
    c->memory = list_new();

    c->size = size;
    c->cum_miss = 0;
    c->cap_miss = 0;
  }

  return c;
}

void cache_delete(cache_t **c) {

  if (*c) {
    bst_delete(&(*c)->seen);
    list_delete(&(*c)->memory);

    free(*c);
    *c = NULL;
  }

  return;
}

void insert_fifo(cache_t *c, char *item) {

  // if item is in the cache, return HIT
  if (list_contains(c->memory, item)) {
    printf("HIT\n");
    return;
  }

  // if cache is full, remove the oldest element
  if (list_count(c->memory) == c->size) {
    list_rfront(c->memory);
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

  list_append(c->memory, item);
  printf("MISS\n");
  return;
}

void insert_lru(cache_t *c, char *item) {

  // if item is in cache, move to end
  if (list_contains(c->memory, item)) {
    list_rfirst(c->memory, item);
    list_append(c->memory, item);
    printf("HIT\n");
    return;
  }

  // if cache is full, remove the least recently used element
  if (list_count(c->memory) == c->size) {
    list_rfront(c->memory);
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

  list_append(c->memory, item);
  printf("MISS\n");
  return;
}

void cache_print(cache_t *c) {
  if (c) {
    printf("%d %d\n", c->cum_miss, c->cap_miss);
  }

  return;
}
