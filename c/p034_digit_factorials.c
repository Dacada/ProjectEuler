#include "euler.h"
#include <stdio.h>
#include <stdlib.h>

/*
 * 145 is a curious number, as 1! + 4! + 5! = 1 + 24 + 120 = 145.
 *
 * Find the sum of all numbers which are equal to the sum of the
 * factorial of their digits.
 *
 * Note: as 1! = 1 and 2! = 2 are not sums they are not included.
 */

static NUM_TYPE factorial(int n) {
  if (n <= 1) return 1;
  else return n*factorial(n-1);
}

static int get_digits(int n, int digits[]) {
  int i;
  
  for (i=0; n > 0; i++) {
    digits[i] = n%10;
    n /= 10;
  }
  
  return i;
}

static int run(void) {
  NUM_TYPE result = 0;
  NUM_TYPE factorials[10];
  for (int i=0; i<10; i++) {
    factorials[i] = factorial(i);
  }
  NUM_TYPE limit = factorials[9]*9;

  for (int number = 3; number < limit; number++) {
    int digits[10];
    int ndigits = get_digits(number, digits);
    
    NUM_TYPE sum_factorials = 0;
    for (int i=0; i<ndigits; i++) {
      sum_factorials += factorials[digits[i]];
    }
    
    if (sum_factorials == number) {
      result += number;
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
