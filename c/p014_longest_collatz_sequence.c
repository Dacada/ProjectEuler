#include "euler.h"
#include <stdio.h>
#include <stdlib.h>

/*
 * The following iterative sequence is defined for the set of positive
 * integers:
 *
 * n -> n/2 (n is even)
 * n -> 3n + 1 (n is odd)
 *
 * Using the rule above and starting with 13, we generate the
 * following sequence:
 *
 * 13 -> 40 -> 20 -> 10 -> 5 -> 16 -> 8 -> 4 -> 2 -> 1
 *
 * It can be seen that this sequence (starting at 13 and finishing at
 * 1) contains 10 terms. Although it has not been proved yet (Collatz
 * Problem), it is thought that all starting numbers finish at 1.
 *
 * Which starting number, under one million, produces the longest
 * chain?
 *
 * NOTE: Once the chain starts the terms are allowed to go above one
 * million.
 */

hash_table_t *hash_table;

NUM_TYPE collatz_length(NUM_TYPE n) {
  NUM_TYPE loops = 0;
  NUM_TYPE next = n;

  while (hash_table_get(hash_table, next) != 0 || next != 1) {
    next = next%2==0 ? next/2 : 3*next+1;
    loops++;
  }

  NUM_TYPE result = loops + hash_table_get(hash_table, next);

  hash_table_put(hash_table, n, result);
  return result;
}

static int run(void) {
  NUM_TYPE result = 0;
  NUM_TYPE max_length = 0;

  hash_table = hash_table_new(1<<20, 100, 0);
  
  for (int i=2; i<1000000; i++) { 
    NUM_TYPE length = collatz_length(i);
    
    if (length > max_length) {
      result = i;
      max_length = length;
    }
  }

  hash_table_free(hash_table);
  
  printf("%"NUM_TYPE_PRINTF"\n", result);
  return 0;
}

int main(void) {
  int exit_code = time_wrapper(run);
  if (exit_code != 0) {
    perror("error");
  }

  return EXIT_SUCCESS;
}
