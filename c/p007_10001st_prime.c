#include "euler.h"
#include <stdio.h>
#include <stdlib.h>

/*
 * By listing the first six prime numbers: 2, 3, 5, 7, 11, and 13, we
 * can see that the 6th prime is 13.
 *
 * What is the 10,001st prime number?
 */

static int run(void) {
  NUM_TYPE result;

  NUM_TYPE n = 1;
  for (result=3;; result+=2) {
    if (is_prime(result)) {
      if (++n >= 10001) {
	break;
      }
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
