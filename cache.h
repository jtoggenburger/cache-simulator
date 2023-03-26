#pragma once
//-----------------------------------------------
//  cache.h
//
//  Jack Toggenburger
//  A cache simulator in c
//-----------------------------------------------

#include "bst.h"
#include "list.h"

// CONSTRUCTORS
// -----------------------------------------------------------------------------------
typedef struct cache cache_t;

// creates a new cache of size
cache_t *cache_new(int size);

// deletes a cache
void cache_delete(cache_t **c);

// CACHE INSERTION
// ---------------------------------------------------------------------------------
// simulates a fifo insert into a cache, returns a HIT or MISS
void insert_fifo(cache_t *c, char *item);

// simulates a LRU insert into a cache, returns HIT or MISS
void insert_lru(cache_t *c, char *item);

// CACHE ACCESS
// -----------------------------------------------------------------------------------

// prints the number of misses for each category
// “<Number of Compulsory Misses> <Number of capacity Misses>"
void cache_print(cache_t *c);
