#include "euler.h"
#include <stdio.h>
#include <stdlib.h>

/*
 * The prime factors of 13195 are 5, 7, 13 and 29.
 *
 * What is the largest prime factor of the number 600851475143?
 */

static int run(void) {
  size_t count;
  NUM_TYPE *factors;

  factors = factorize(600851475143, &count);
  if (factors == NULL) {
    return 1;
  }

  NUM_TYPE result = factors[count - 1];

  free(factors);
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
