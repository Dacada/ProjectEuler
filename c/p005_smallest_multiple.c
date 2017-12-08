#include "euler.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

/*
 * 2520 is the smallest number that can be divided by each of the
 * numbers from 1 to 10 without any remainder.
 * 
 * What is the smallest positive number that is evenly divisible by
 * all of the numbers from 1 to 20?
 *
 *
 * The resulting number N must contain the prime factors of all
 * numbers from 1 to 20. Each prime factor must be repeated as many
 * times as possible without going over 20. For example, 2 must be
 * repeated 4 times since 2**4==16 but 2**5==32. Mathematically: 4 ==
 * log(20)/log(2)
 */

static int run(void) {
  const NUM_TYPE max_divisor = 20;
  
  double log_max_divisor = log((double)max_divisor);
  NUM_TYPE result = 1;
  bool check = true;
  NUM_TYPE limit = (NUM_TYPE)sqrt((double)max_divisor);

  size_t primes_count;
  NUM_TYPE *primes = primes_sieve(max_divisor, &primes_count);
  for (NUM_TYPE prime_i=0; prime_i<primes_count; prime_i++) {
    NUM_TYPE prime = primes[prime_i];
    NUM_TYPE exponent = 1;
    if (check) {
      if (prime <= limit) {
	exponent = (NUM_TYPE)(log_max_divisor/log((double)prime));
      } else {
	check = false;
      }
    }
    result *= (NUM_TYPE)(pow((double)prime, (double)exponent));
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
