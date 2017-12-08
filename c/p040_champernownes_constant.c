#include "euler.h"
#include <stdio.h>
#include <stdlib.h>

/*
 * An irrational decimal fraction is created by concatenating the
 * positive integers:
 *
 * 0.123456789101112131415161718192021...
 *
 * It can be seen that the 12th digit of the fractional part is 1.
 *
 * If d_n represents the nth digit of the fractional part, find the
 * value of the following expression.
 *
 * d_1 x d_{10} x d_{100} x d_{1000} x d_{10000} x d_{100000} x
 * d_{1000000}
 */

static int count_digits(int number) {
  if (number < 10) return 1;
  else if (number < 100) return 2;
  else if (number < 1000) return 3;
  else if (number < 10000) return 4;
  else if (number < 100000) return 5;
  else if (number < 1000000) return 6;
  else if (number < 10000000) return 7;
  else return 8;
}

static int get_nth_digit(int number, int nth, int length) {
  int div = 1;
  int diff = length - nth;
  while (diff-- > 0) div *= 10;
  return (number / div) % 10;
}

static int run(void) {
  int targets[] = {
    1,
    10,
    100,
    1000,
    10000,
    100000,
    1000000
  };
  
  int targets_i = 0;
  const int targets_len = 7;
  
  int nchar = 0;
  NUM_TYPE result = 1;

  for (int n=1;; n++) {
    int ndigits = count_digits(n);
    for (int i=1; i<=ndigits; i++) {
      nchar++;

      if (targets_i >= targets_len) {
	printf("%"NUM_TYPE_PRINTF"\n", result);
	return 0;
      }

      if (nchar == targets[targets_i]) {
	int digit = get_nth_digit(n, i, ndigits);
	//printf("%d %d, %d\n", digit, n, i);
	result *= digit;
	targets_i++;
      }
    }
  }
}

int main(void) {
  int exit_code = time_wrapper(run);
  if (exit_code != 0) {
    perror("error");
  }

  return EXIT_SUCCESS;
}
