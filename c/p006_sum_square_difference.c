#include "euler.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

/*
 * The sum of the squares of the first ten natural numbers is,
 *
 * 1**2 + 2**2 + ... + 10**2 = 385
 *
 * The square of the sum of the first ten natural numbers is,
 *
 * (1 + 2 + ... + 10)**2 = 552 = 3025
 *
 * Hence the difference between the sum of the squares of the first
 * ten natural numbers and the square of the sum is 3025 - 385 = 2640.
 * 
 * Find the difference between the sum of the squares of the first one
 * hundred natural numbers and the square of the sum.
 *
 *
 * This can be done with formulas rather than brute force:
 * sum(n) = n*(n+1)/2
 * sum_sq(n) = (2*n+1)*(n+1)*n/6
 */

static int run(void) {
  NUM_TYPE result;

  const NUM_TYPE n = 100;
  NUM_TYPE sum = n*(n+1)/2;
  NUM_TYPE sum_sq = (2*n+1)*(n+1)*n/6;
  result = sum*sum - sum_sq;
  
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
