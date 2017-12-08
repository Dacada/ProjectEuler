#include "euler.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

/*
 * A unit fraction contains 1 in the numerator. The decimal
 * representation of the unit fractions with denominators 2 to 10 are
 * given:
 *
 * 1/2= 0.5
 * 1/3= 0.(3)
 * 1/4= 0.25
 * 1/5= 0.2
 * 1/6= 0.1(6)
 * 1/7= 0.(142857)
 * 1/8= 0.125
 * 1/9= 0.(1)
 * 1/10= 0.1
 *
 * Where 0.1(6) means 0.166666..., and has a 1-digit recurring
 * cycle. It can be seen that 1/7 has a 6-digit recurring cycle.
 *
 * Find the value of d < 1000 for which 1/d contains the longest
 * recurring cycle in its decimal fraction part.
 */

static NUM_TYPE repeating_decimals(NUM_TYPE p) {
  // We want a k such that 10**k is congruent to 1 modulo p
  // 10**k = 1 (mod p)
  // Discrete logarithm, brute force it!
  
  int power = 1;
  for (NUM_TYPE k=1; k<=p; k++) {
    power = (power * 10) % p;
    if (power == 1) return k;
  }
  return 0;
}

static int run(void) {
  NUM_TYPE result = 0;
  NUM_TYPE max_repeating_decimals = 0;

  size_t primes_size;
  NUM_TYPE *primes = primes_sieve(1000, &primes_size);
  for (size_t i=0; i<primes_size; i++) {
    NUM_TYPE n = primes[i];
    NUM_TYPE m = repeating_decimals(n);
    if (m > max_repeating_decimals) {
      max_repeating_decimals = m;
      result = n;
    }
  }
  free(primes);
  
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
