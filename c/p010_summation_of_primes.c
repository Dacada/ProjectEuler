#include "euler.h"
#include <stdio.h>
#include <stdlib.h>

/*
 * The sum of the primes below 10 is 2 + 3 + 5 + 7 = 17.
 *
 * Find the sum of all the primes below two million.
 */

static const NUM_TYPE limit = 2000000;

static int run(void) {
  NUM_TYPE result = 0;
  
  size_t count;
  NUM_TYPE *primes = primes_sieve(limit, &count);
  for (size_t i=0; i<count; i++) {
    result += primes[i];
  }
  
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
