#include "euler.h"
#include <stdio.h>
#include <stdlib.h>

/*
 * The decimal number, 585 = 10010010012 (binary), is palindromic in
 * both bases.
 *
 * Find the sum of all numbers, less than one million, which are
 * palindromic in base 10 and base 2.
 *
 * (Please note that the palindromic number, in either base, may not
 * include leading zeros.)
 */

static int get_digits(NUM_TYPE num, int base, int *digits) {
  int i = 0;
  while (num > 0) {
    digits[i++] = num % base;
    num /= base;
  }
  return i;
}

static bool palindrome(int *digits, int ndigits) {
  for (int i=0; i<ndigits/2+1; i++) {
    if (digits[i] != digits[ndigits-i-1]) {
      return false;
    }
  }
  return true;
}

static bool is_palindromic(NUM_TYPE n) {
  int base10digits[100];
  int base2digits[100];
  int ndigits10 = get_digits(n, 10, base10digits);
  int ndigits2 = get_digits(n, 2, base2digits);
  
  return palindrome(base10digits, ndigits10) && palindrome(base2digits, ndigits2);
}

static int run(void) {
  NUM_TYPE result = 0;

  for (NUM_TYPE number = 1; number < 1000000; number++) {
    if (is_palindromic(number)) {
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
