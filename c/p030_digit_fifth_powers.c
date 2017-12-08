#include "euler.h"
#include <stdio.h>
#include <stdlib.h>

/*
 * Surprisingly there are only three numbers that can be written as
 * the sum of fourth powers of their digits:
 *
 * 1634 = 1**4 + 6**4 + 3**4 + 4**4
 * 8208 = 8**4 + 2**4 + 0**4 + 8**4
 * 9474 = 9**4 + 4**4 + 7**4 + 4**4
 *
 * As 1 = 1**4 is not a sum it is not included.
 *
 * The sum of these numbers is 1634 + 8208 + 9474 = 19316.
 *
 * Find the sum of all the numbers that can be written as the sum of
 * fifth powers of their digits.
 *
 *
 * The solution can't have 7 or more digits.
 */

static NUM_TYPE sum_digits_power_five(NUM_TYPE number) {
  NUM_TYPE div = number;
  NUM_TYPE sum = 0;

  while (div > 0) {
    NUM_TYPE digit = div % 10;
    sum += digit*digit*digit*digit*digit;
    div /= 10;
  }

  return sum;
}

static int run(void) {
  NUM_TYPE result = 0;
  NUM_TYPE number = 2;

  while (number < 1000000) { // 7 digits
    if (sum_digits_power_five(number) == number) {
      result += number;
    }
    number++;
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
