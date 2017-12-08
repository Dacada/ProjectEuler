#include "euler.h"
#include <stdio.h>
#include <stdlib.h>

/*
 * The number 3797 has an interesting property. Being prime itself, it
 * is possible to continuously remove digits from left to right, and
 * remain prime at each stage: 3797, 797, 97, and 7. Similarly we can
 * work from right to left: 3797, 379, 37, and 3.
 *
 * Find the sum of the only eleven primes that are both truncatable
 * from left to right and right to left.
 *
 * NOTE: 2, 3, 5, and 7 are not considered to be truncatable primes.
 */

NUM_TYPE remove_left_digit(NUM_TYPE n, int ndigits) {
  NUM_TYPE mult = 1;
  for (int i=0; i<ndigits; i++) {
    mult *= 10;
  }
  return n-(n/mult)*mult;
}

NUM_TYPE remove_right_digit(NUM_TYPE n) {
  return n/10;
}

NUM_TYPE *all_truncations(NUM_TYPE n, size_t *size) {
  NUM_TYPE *result = malloc(100*sizeof(NUM_TYPE));
  int i = 0;

  NUM_TYPE truncated = remove_right_digit(n);
  while (truncated > 0) {
    result[i++] = truncated;
    truncated = remove_right_digit(truncated);
  }

  int ndigits = i;
  truncated = remove_left_digit(n, ndigits);
  while (truncated > 0) {
    result[i++] = truncated;
    truncated = remove_left_digit(truncated, --ndigits);
  }

  *size = i;
  return result;
}

static int run(void) {
  NUM_TYPE result = 0;
  size_t primes_count;
  NUM_TYPE *primes = primes_sieve(1000000, &primes_count);

  int count = 0;
  bool found_primes[1000001];
  for (int i=0; i<1000001; i++) {
    found_primes[i] = false;
  }
  
  for (int i=primes_count-1; i>=0; i--) {
    NUM_TYPE p = primes[i];
    if (count == 11) break;
    if (found_primes[p]) continue;

    size_t ntruncations;
    NUM_TYPE *truncations = all_truncations(p, &ntruncations);
    bool all_prime = true;
    for (int j=0; j<ntruncations; j++) {
      if (!is_prime(truncations[j])) {
	all_prime = false;
	break;
      }
    }
    if (all_prime) {
      found_primes[p] = true;
      count++;
      result += p;
    }
    free(truncations);
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
