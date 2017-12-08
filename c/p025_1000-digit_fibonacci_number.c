#include "euler.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

/*
 * The Fibonacci sequence is defined by the recurrence relation:
 *
 * F_n = F_{n-1} + F_{n-2} where F_1 = F_2 = 1
 *
 * Hence the first 12 terms will be:
 *
 * F_1= 1
 * F_2 = 1
 * F_3 = 2
 * F_4 = 3
 * F_5 = 5
 * F_6 = 8
 * F_7 = 13
 * F_8 = 21
 * F_9 = 34
 * F_10 = 55
 * F_11 = 89
 * F_12 = 144
 * 
 * The 12th term, F_12, is the first term to contain three digits.
 * 
 * What is the index of the first term in the Fibonacci sequence to
 * contain 1000 digits?
 *
 *
 * The nth Fibonacci number is phi**n/sqrt(5).
 * We need the first number greater than 10**999
 *
 * phi**n/sqrt(5) > 10*999
 * n * log(phi) - log(5) * 1/2 > 999 * log(10)
 * n * log(phi) > 999 * log(10) + log(5) / 2
 * n > (999 * log(10) + log(5) / 2) / log(phi)
 *
 * Solution: ceil((999 * log(10) + log(5) / 2) / log(phi))
 */

static int run(void) {
  double phi = 1.0/2.0 + sqrt(5)/2.0;
  NUM_TYPE result = (NUM_TYPE)ceil((999 * log(10) + log(5) / 2) / log(phi));
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
