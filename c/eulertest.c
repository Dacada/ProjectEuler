/*
 * A simple automated test of the euler.c utility.
 */

#include "euler.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

//#define DO_NOT_WAIT
//#define DO_NOT_CURL

int wait_three_seconds(void) {
  #ifndef DO_NOT_WAIT
  sleep(3);
  #endif
  
  return 33;
}

int main(int argc, char *argv[]) {
  NUM_TYPE n;
  printf("This should be about three seconds:\n");
  n = time_wrapper(wait_three_seconds);
  if (n != 33) {
    printf("Error: time_wrapper should've returned 33 but instead returned %"NUM_TYPE_PRINTF".\n", n);
    return EXIT_FAILURE;
  } else if (n == 1) {
    perror("time_wrapper");
    return EXIT_FAILURE;
  }

  if (is_prime(1)) {
    printf("Error: is_prime says 1 is prime.\n");
    return EXIT_FAILURE;
  }

  if (!is_prime(2)) {
    printf("Error: is_prime says that 2 isn't prime.\n");
    return EXIT_FAILURE;
  }

  if (is_prime(444)) {
    printf("Error: is_prime says that 444 is prime.\n");
    return EXIT_FAILURE;
  }

  if (!is_prime(839)) {
    printf("Error: is_prime says that 839 isn't prime.\n");
    return EXIT_FAILURE;
  }

  size_t count = -31;
  NUM_TYPE *factors = factorize(33, &count);
  if (factors == NULL) {
    perror("factorize");
    return EXIT_FAILURE;
  }
  if (count != 2) {
    printf("Error: factorize 33 didn't give 2 results, gave %"NUM_TYPE_PRINTF"\n", count);
    return EXIT_FAILURE;
  }
  if (factors[0] != 3 ||
      factors[1] != 11) {
    printf("Error: 33 didn't factorize into 3 and 11\n");
    return EXIT_FAILURE;
  }

  if ((n = gcd(1008, 1638)) != 126) {
    printf("Error: gcd(1008,1638) should be 126 but got %"NUM_TYPE_PRINTF".\n", n);
    return EXIT_FAILURE;
  }

  // Just make sure it doesn't crash and burn
  for (int i=0; i<3000; i++) {
    factors = factorize(3298458948, &count);
    if (factors == NULL) {
      printf("Failed at: %d\n", i);
      perror("perror");
      break;
    }
  }

  NUM_TYPE *primes = primes_sieve(30, &count);
  if (primes[0] != 2 ||
      primes[1] != 3 ||
      primes[2] != 5 ||
      primes[3] != 7 ||
      primes[4] != 11 ||
      primes[5] != 13 ||
      primes[6] != 17 ||
      primes[7] != 19 ||
      primes[8] != 23 ||
      primes[9] != 29) {
    printf("Error: primes_sieve returned incorrect result");
  }
  free(primes);

  #ifndef DO_NOT_CURL
  char *text = read_url("http://example.com");
  printf("This should look like an HTML document:\n\n");
  printf(text);
  free(text);

  text = read_url("https://projecteuler.net/project/resources/p022_names.txt");
  printf("%d <-- ignore this | downloading a large file test ok\n", text[1]);
  free(text);
  #endif

  n = sum_divisors(56);
  if (n != 64) {
    printf("Error: sum_divisors(56) should be 64 but was %"NUM_TYPE_PRINTF"\n", n);
    return EXIT_FAILURE;
  }
  
  hash_table_t *ht = hash_table_new(100, 3, 31);
  
  if (hash_table_put(ht, 91, 0) == -1)
    perror("hash_table_put0");
  NUM_TYPE result = hash_table_get(ht, 91);
  if (result != 0) {
    printf("Error: hash_table_get should've been 0 but was %"NUM_TYPE_PRINTF"\n", result);
  }
  
  result = hash_table_get(ht, 10);
  if (result != 31) {
    printf("Error: hash_table_get should've been 31 but was %"NUM_TYPE_PRINTF"\n", result);
  }
  
  if (hash_table_put(ht, 63, 111) == -1)
    perror("hash_table_put1");
  if (hash_table_put(ht, 28, 222) == -1)
    perror("hash_table_put2");
  if (hash_table_put(ht, 128, 444) == -1)
    perror("hash_table_put3");
  if (hash_table_put(ht, 263, 555) == -1)
    perror("hash_table_put4");
  
  result = hash_table_get(ht, 63);
  if (result != 111) {
    printf("Error: hash_table_get should've been 111 but was %"NUM_TYPE_PRINTF"\n", result);
  }
  result = hash_table_get(ht, 163);
  if (result != 31) {
    printf("Error: hash_table_get should've been 31 but was %"NUM_TYPE_PRINTF"\n", result);
  }
  result = hash_table_get(ht, 263);
  if (result != 555) {
    printf("Error: hash_table_get should've been 555 but was %"NUM_TYPE_PRINTF"\n", result);
  }
  result = hash_table_get(ht, 28);
  if (result != 222) {
    printf("Error: hash_table_get should've been 222 but was %"NUM_TYPE_PRINTF"\n", result);
  }
  result = hash_table_get(ht, 128);
  if (result != 444) {
    printf("Error: hash_table_get should've been 444 but was %"NUM_TYPE_PRINTF"\n", result);
  }
  result = hash_table_get(ht, 228);
  if (result != 31) {
    printf("Error: hash_table_get should've been 31 but was %"NUM_TYPE_PRINTF"\n", result);
  }
  
  hash_table_free(ht);

  printf("All checks pass.\n");
  return EXIT_SUCCESS;
}
