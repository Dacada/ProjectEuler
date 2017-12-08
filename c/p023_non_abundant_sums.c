#include "euler.h"
#include <stdio.h>
#include <stdlib.h>

/*
 * A perfect number is a number for which the sum of its proper
 * divisors is exactly equal to the number. For example, the sum of
 * the proper divisors of 28 would be 1 + 2 + 4 + 7 + 14 = 28, which
 * means that 28 is a perfect number.
 *
 * A number n is called deficient if the sum of its proper divisors is
 * less than n and it is called abundant if this sum exceeds n.
 *
 * As 12 is the smallest abundant number, 1 + 2 + 3 + 4 + 6 = 16, the
 * smallest number that can be written as the sum of two abundant
 * numbers is 24. By mathematical analysis, it can be shown that all
 * integers greater than 28123 can be written as the sum of two
 * abundant numbers. However, this upper limit cannot be reduced any
 * further by analysis even though it is known that the greatest
 * number that cannot be expressed as the sum of two abundant numbers
 * is less than this limit.
 *
 * Find the sum of all the positive integers which cannot be written
 * as the sum of two abundant numbers.
 */

static int run(void) {
  NUM_TYPE result=0;

  const size_t upper_bound = 28124;
  
  // Get abundant numbers up to the given upper bound.
  bool abundant_numbers[upper_bound]; // if(array[n]) n is abundant
  for (size_t i=0; i<upper_bound; i++) abundant_numbers[i] = false;
  for (size_t n=12; n<upper_bound; n++) {
    if (sum_divisors(n) > n) {
      abundant_numbers[n] = true;
    }
  }

  // Get all sums of 2 abundant numbers up to the given upper bound.
  bool abundant_numbers_sums[upper_bound];
  for (size_t i=0; i<upper_bound; i++) abundant_numbers_sums[i] = false;
  for (size_t i=0; i<upper_bound; i++) {
    if (abundant_numbers[i]) {
      for (size_t j=0; j<upper_bound; j++) {
	if (abundant_numbers[j]) {
	  NUM_TYPE sum = i + j;
	  if (sum < upper_bound)
	    abundant_numbers_sums[sum] = true;
	}
      }
    }
  }

  // Get sum of all indexes set to false in abundnt_numbers_sums
  for (size_t i=0; i<upper_bound; i++) {
    if (!abundant_numbers_sums[i]) {
      result += i;
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
