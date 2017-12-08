#include "euler.h"
#include <stdio.h>
#include <stdlib.h>

/*
 * The number, 197, is called a circular prime because all rotations
 * of the digits: 197, 971, and 719, are themselves prime.
 *
 * There are thirteen such primes below 100: 2, 3, 5, 7, 11, 13, 17,
 * 31, 37, 71, 73, 79, and 97.
 *
 * How many circular primes are there below one million?
 */

static int get_rotations(NUM_TYPE n, NUM_TYPE rotations[]) {
  int i = 0;
  NUM_TYPE rot = n;

  NUM_TYPE mult;
  if (n >= 0 && n < 9) {
    rotations[0] = n;
    return 1;
  } else if (n >= 10 && n <= 99) {
    mult = 10;
  } else if (n >= 100 && n <= 999) {
    mult = 100;
  } else if (n >= 1000 && n <= 9999) {
    mult = 1000;
  } else if (n >= 10000 && n <= 99999) {
    mult = 10000;
  } else if (n >= 100000 && n <= 999999) {
    mult = 100000;
  } else if (n >= 1000000 && n <= 9999999) {
    mult = 1000000;
  } else {
    mult = 10000000;
  }

  do {
    rotations[i++] = rot;
    rot = rot/10 + ((rot%10)*mult);
  } while (rot != n);

  return i;
}

static int run(void) {
  NUM_TYPE result = 0;

  size_t nprimes;
  NUM_TYPE *primes_array = primes_sieve(1000000, &nprimes);

  for (size_t i=0; i<nprimes; i++) {
    NUM_TYPE prime = primes_array[i];
    NUM_TYPE rotations[7];
    int nrotations = get_rotations(prime, rotations);

    bool is_circular = true;
    for (int j=0; j<nrotations; j++) {
      NUM_TYPE rot = rotations[j];
      if (!is_prime(rot)) {
	is_circular = false;
	break;
      }
    }

    if (is_circular) {
      result++;
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
