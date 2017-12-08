#include "euler.h"
#include <stdio.h>
#include <stdlib.h>

/*
 * The sequence of triangle numbers is generated by adding the natural
 * numbers. So the 7th triangle number would be 1 + 2 + 3 + 4 + 5 + 6
 * + 7 = 28. The first ten terms would be:
 *
 * 1, 3, 6, 10, 15, 21, 28, 36, 45, 55, ...
 *
 * Let us list the factors of the first seven triangle numbers:
 *
 *  1: 1
 *  3: 1,3
 *  6: 1,2,3,6
 * 10: 1,2,5,10
 * 15: 1,3,5,15
 * 21: 1,3,7,21
 * 28: 1,2,4,7,14,28
 *
 * We can see that 28 is the first triangle number to have over five
 * divisors.
 *
 * What is the value of the first triangle number to have over five
 * hundred divisors?
 */

static NUM_TYPE number_divisors(NUM_TYPE n) {
  NUM_TYPE total = 1;
  
  size_t count;
  NUM_TYPE *factors = factorize(n, &count);

  NUM_TYPE factors_no_dups[count];
  NUM_TYPE factors_count_dups[count];
  size_t count_no_dups = sorted_array_count_remove_dups(
	factors, count,
	factors_no_dups, factors_count_dups);
  free(factors);

  for (size_t i=0; i<count_no_dups; i++) {
    total *= factors_count_dups[i] + 1;
  }

  return total;
}

static int run(void) {
  NUM_TYPE result = 0;

  for (NUM_TYPE n=0;; n++) {
    result += n;
    if (number_divisors(result) > 500) {
      break;
    }
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
