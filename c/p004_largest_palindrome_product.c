#include "euler.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/*
 * A palindromic number reads the same both ways. The largest
 * palindrome made from the product of two 2-digit numbers is 9009 =
 * 91 x 99.
 * 
 * Find the largest palindrome made from the product of two 3-digit
 * numbers.
 *
 *
 * Palindrome P must be at 6 digits long since 111111=143x777 and
 * 999x999 is also 6 digits long.
 *
 * P = 100000x + 10000y + 1000z + 100z + 10y + x
 *
 * P = 100001x + 10010y + 1100z
 *
 * P = 11(9091x + 910y + 100z)
 *
 * Therefore one of the two numbers must be divisible by 11
 */

static bool is_six_digits(NUM_TYPE n) {
  return n >= 100000 && n <= 999999;
}

static NUM_TYPE nth_digit(NUM_TYPE number, size_t n) {
  static NUM_TYPE powers_of_ten[] = {1, 10, 100, 1000, 10000, 100000};
  return number / powers_of_ten[n] % 10;
}

static bool is_palindrome(NUM_TYPE n) {
  return
    nth_digit(n, 0) == nth_digit(n, 5) &&
    nth_digit(n, 1) == nth_digit(n, 4) &&
    nth_digit(n, 2) == nth_digit(n, 3);
}

static int run(void) {
  NUM_TYPE result = 0;
  NUM_TYPE a = 999; // start from high numbers
  
  while (a >= 100) {
    NUM_TYPE b;
    NUM_TYPE decrease_b;
    
    if (a % 11 == 0) { //one of them must be divisible by 11
      b = 999;
      decrease_b = 1;
    } else {
      b = 990;
      decrease_b = 11;
    }

    while (b >= a) {
      NUM_TYPE r = a*b;
      if (r <= result) {
	break;
      } else if (is_six_digits(r) && is_palindrome(r)) {
	result = r;
      }

      b -= decrease_b;
    }
    a--;
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
