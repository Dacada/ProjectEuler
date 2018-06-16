#include "euler.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

/*
 *
 * It was proposed by Christian Goldbach that every odd composite number can be
 * written as the sum of a prime and twice a square.
 *
 * 9 = 7 + 2x1^2
 * 15 = 7 + 2x2^2
 * 21 = 3 + 2x3^2
 * 25 = 7 + 2x3^2
 * 27 = 19 + 2x2^2
 * 33 = 31 + 2x1^2
 *
 * It turns out that the conjecture was false.
 *
 * What is the smallest odd composite that cannot be written as the sum of a
 * prime and twice a square?
 */

static int run(void) {
  for (NUM_TYPE n = 35;; n+=2) {
    if (is_prime(n)) {
      continue;
    }
    if (n % 15 == 0) {
      continue;
    }

    bool passed = false;
    size_t count;
    NUM_TYPE *primes = primes_sieve(n, &count);
    for (size_t i=0; i<count; i++) {
      NUM_TYPE pn = primes[i];
      double r = sqrt(((double)n-pn)/2);
      if (r == (NUM_TYPE)r) {
        passed = true;
        break;
      }
    }
    if (!passed) {
      printf("%"NUM_TYPE_PRINTF"\n", n);
      return 0;
    }
  }
}

int main(void) {
  int exit_code = time_wrapper(run);
  if (exit_code != 0) {
    perror("error");
  }

  return EXIT_SUCCESS;
}
