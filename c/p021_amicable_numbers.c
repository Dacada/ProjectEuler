#include "euler.h"
#include <stdio.h>
#include <stdlib.h>

/*
 * Let d(n) be defined as the sum of proper divisors of n (numbers
 * less than n which divide evenly into n).  If d(a) = b and d(b) = a,
 * where a =/= b, then a and b are an amicable pair and each of a and
 * b are called amicable numbers.
 *
 * For example, the proper divisors of 220 are 1, 2, 4, 5, 10, 11, 20,
 * 22, 44, 55 and 110; therefore d(220) = 284. The proper divisors of
 * 284 are 1, 2, 4, 71 and 142; so d(284) = 220.
 *
 * Evaluate the sum of all the amicable numbers under 10000.
 *
 *
 * The sum of divisors of a number can be easily found from its prime
 * factors using a formula. The rest is doing the loop in an efficient
 * way.
 */

static int run(void) {
  NUM_TYPE result = 0;

  for (NUM_TYPE a=2; a<10000; a++) {
    NUM_TYPE b = sum_divisors(a);
    if (b > a && sum_divisors(b) == a) {
      result += a + b;
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
