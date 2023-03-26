//-----------------------------------------------
// cacher.c
// Jack Toggenburger
//
// An implementation of a cache simulator in c
//
//-----------------------------------------------

#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "cache.h"
#include "clock_cache.h"

#define ITEMS "N:FLC"
#define BUFF_SIZE LINE_MAX

int main(int argc, char **argv) {

  if (argc < 2) {
    fprintf(stderr, "usage: %s [-N size] <policy>\n", argv[0]);
    return EXIT_FAILURE;
  }

  int opt = 0;

  // size of the cache
  int size = -1;

  // policies
  bool fifo = false;
  bool lru = false;
  bool clock = false;

  while ((opt = getopt(argc, argv, ITEMS)) != -1) {
    switch (opt) {

    case 'N':
      size = atoi(optarg);
      break;
    case 'F':
      fifo = true;
      break;
    case 'L':
      lru = true;
      break;
    case 'C':
      clock = true;
      break;
    }
  }

  // check inputs
  if (size < 1) {
    fprintf(stderr, "invalid cache size: %d\n", size);
    return EXIT_FAILURE;
  }

  if ((fifo + lru + clock) != 1) {
    fprintf(stderr, "invalid number of flags used: %d\n", (fifo + lru + clock));
    return EXIT_FAILURE;
  }

  // activate our correct cache implementation

  if (fifo) {

    cache_t *cache = cache_new(size);
    char buff[BUFF_SIZE];

    // read from stdin until EOF
    while (fgets(buff, BUFF_SIZE, stdin)) {

      // replace new line with \0
      buff[strcspn(buff, "\n")] = 0;

      // insert into our cache
      insert_fifo(cache, buff);
    }

    // print our stats for misses
    cache_print(cache);

    cache_delete(&cache);
    return EXIT_SUCCESS;
  }

  if (lru) {

    cache_t *cache = cache_new(size);
    char buff[BUFF_SIZE];

    // read from stdin until EOF
    while (fgets(buff, BUFF_SIZE, stdin)) {

      // replace new line with \0
      buff[strcspn(buff, "\n")] = 0;

      // insert into our cache
      insert_lru(cache, buff);
    }

    // print our stats for misses
    cache_print(cache);

    cache_delete(&cache);
    return EXIT_SUCCESS;
  }

  if (clock) {

    clockCache_t *cache = clockCache_new(size);
    char buff[BUFF_SIZE];

    // read from stdin until EOF
    while (fgets(buff, BUFF_SIZE, stdin)) {

      // replace new line with \0
      buff[strcspn(buff, "\n")] = 0;

      // insert into our cache
      insert_clock(cache, buff);
    }

    // print our stats for misses
    clock_print(cache);

    clockCache_delete(&cache);
    return EXIT_SUCCESS;
  }

  return EXIT_FAILURE;
}
