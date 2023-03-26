#pragma once

//-----------------------------------------------
// list.h
//
// Jack Toggenburger
// implementation of a linked list in c
//
//-----------------------------------------------

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// NODE CONSTRUCTORS
// ------------------------------------------------------------------------------
typedef struct node node_t;

node_t *nodeCreate(char *item);

void nodeDelete(node_t **n);

// CONSTRUCTORS
// -----------------------------------------------------------------------------------
typedef struct list list_t;

list_t *list_new(void);

void list_delete(list_t **l);

// LIST FUNCTIONS
// ---------------------------------------------------------------------------------

// returns the number of items in the list
int list_count(list_t *l);

// returns true if item is in list, false otherwise
bool list_contains(list_t *l, char *item);

// remove the front of the list
void list_rfront(list_t *l);

// removes the first occurence of item in list
void list_rfirst(list_t *l, char *item);

// append item to the back of the list
void list_append(list_t *l, char *item);

// prints the list
void list_print(list_t *l);
