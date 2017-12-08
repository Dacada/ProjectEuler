#include "euler.h"
#include <stdio.h>
#include <stdlib.h>

/*
 * If we list all the natural numbers below 10 that are multiples of 3
 * or 5, we get 3, 5, 6 and 9. The sum of these multiples is 23.
 *
 * Find the sum of all the multiples of 3 or 5 below 1000.
 */

static int run(void) {
  NUM_TYPE result = 0;
  
  for (NUM_TYPE n=1; n<1000; n++) {
    if (n % 3 == 0 || n % 5 == 0) {
      result += n;
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
