#pragma once
//-----------------------------------------------
// Jack Toggenburger
//
// clock_cache.h
// Implementation of a clock cache in c
//-----------------------------------------------

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bst.h"

// CONSTRUCTORS
// -----------------------------------------------------------------------------------
typedef struct data data_t;

data_t *data_new(char *item);

void data_delete(data_t **d);

// clock cache constructor
typedef struct clockCache clockCache_t;

// creates a cache of size
clockCache_t *clockCache_new(int size);

// deletes cache
void clockCache_delete(clockCache_t **c);

// CACHE INSERTION
// --------------------------------------------------------------------------------

// simulates a clock insert into a cache, returns HIT or MISS
void insert_clock(clockCache_t *c, char *item);

// CACHE ACCESS
// -----------------------------------------------------------------------------------

// prints the number of misses for each category
// “<Number of Compulsory Misses> <Number of capacity Misses>"
void clock_print(clockCache_t *c);
