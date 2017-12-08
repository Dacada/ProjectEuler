#include "euler.h"
#include <stdio.h>
#include <stdlib.h>

/*
 * Euler discovered the remarkable quadratic formula:
 *
 * n**2 + n + 41
 * 
 * It turns out that the formula will produce 40 primes for the
 * consecutive values n = 0 to 39. However, when n = 40, 40**2 + 40 +
 * 41 = 40(40 + 1) + 41 is divisible by 41, and certainly when n = 41,
 * 41**2 + 41 + 41 is clearly divisible by 41.
 *
 * The incredible formula n**2 - 79*n + 1601 was discovered, which
 * produces 80 primes for the consecutive values n = 0 to 79. The
 * product of the coefficients, -79 and 1601, is -126479.
 *
 * Considering quadratics of the form:
 * 
 * n**2 + a*n + b, where |a| < 1000 and |b| < 1000
 *
 * (where |n| is the modulus/absolute value of n) e.g. |11| = 11 and
 * |-4| = 4
 *
 * Find the product of the coefficients, a and b, for the quadratic
 * expression that produces the maximum number of primes for
 * consecutive values of n, starting with n = 0.
 */

static NUM_TYPE how_many_primes(NUM_TYPE a, NUM_TYPE b) {
  if (!is_prime(b < 0 ? -b : b)) {
    return 0;
  }
  
  for (NUM_TYPE n = 0;; n++) {
    NUM_TYPE r = n*n + a*n + b;
    if (!is_prime(r < 0 ? -r : r)) {
      return n-1;
    }
  }
  
  return 0;
}

static int run(void) {
  NUM_TYPE result, r1 = 0, r2 = 0, r3 = 0;

  for (NUM_TYPE i = -1000; i <= 1000; i++) {
    for (NUM_TYPE j = -1000; j <= 1000; j++) {
      NUM_TYPE p = how_many_primes(i, j);
      if (p > r1) {
	r1 = p;
	r2 = i;
	r3 = j;
      }
    }
  }

  result = r2 * r3;
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
