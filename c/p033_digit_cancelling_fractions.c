#include "euler.h"
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/*
 * The fraction 49/98 is a curious fraction, as an inexperienced
 * mathematician in attempting to simplify it may incorrectly believe
 * that 49/98 = 4/8, which is correct, is obtained by cancelling the
 * 9s.
 *
 * We shall consider fractions like, 30/50 = 3/5, to be trivial examples.
 *
 * There are exactly four non-trivial examples of this type of
 * fraction, less than one in value, and containing two digits in the
 * numerator and denominator.
 *
 * If the product of these four fractions is given in its lowest
 * common terms, find the value of the denominator.
 */

typedef struct {
  NUM_TYPE numerator;
  NUM_TYPE denominator;
} fraction_t;

static void get_digits(int a, int b, int digitsA[], int digitsB[], int ndigits) {
  for (int i=0; i<ndigits; i++) {
    int dv;
    if (i == 0) dv = 1;
    else dv = 10*i;
    
    digitsA[i] = (a/dv)%10;
    digitsB[i] = (b/dv)%10;
  }
}

static bool share_digit(int a, int b) {
  int digitsA[2];
  int digitsB[2];
  get_digits(a, b, digitsA, digitsB, 2);

  for (int i=0; i<2; i++) {
    for (int j=0; j<2; j++) {
      if (digitsA[i] == digitsB[j]) return true;
    }
  }

  return false;
}

static void remove_digit(int a, int b, int *newA, int *newB) {
  int dA[2];
  int dB[2];
  get_digits(a, b, dA, dB, 2);

  if (dA[0] == dB[0]) {
    *newA = dA[1];
    *newB = dB[1];
  } else if (dA[0] == dB[1]) {
    *newA = dA[1];
    *newB = dB[0];
  } else if (dA[1] == dB[0]) {
    *newA = dA[0];
    *newB = dB[1];
  } else if (dA[1] == dB[1]) {
    *newA = dA[0];
    *newB = dB[0];
  }
}

static void fraction_simplify(fraction_t *f) {
  int g = gcd(f->numerator, f->denominator);
  f->numerator /= g;
  f->denominator /= g;
}

static void fraction_multiply(fraction_t *a, fraction_t *b) {
  a->numerator *= b->numerator;
  a->denominator *= b->denominator;

  fraction_simplify(a);
}

static int run(void) {
  fraction_t *found[4];
  int found_i = 0;

  for (int i = 10; i<99; i++) {
    if (i % 10 == 0) continue;
    for (int j = i+1; j<100; j++) {
      if (j % 10 == 0) continue;
      if (!share_digit(i, j)) continue;
      
      int a,b;
      remove_digit(i, j, &a, &b);
      if (b == 0) continue;
      
      double k = ((double)i)/((double)j);
      k *= 100000.0;
      k = round(k);
      k /= 100000.0;

      double c = ((double)a)/((double)b);
      c *= 100000.0;
      c = round(c);
      c /= 100000.0;

      if (k == c) {
	fraction_t *f = malloc(sizeof(fraction_t));
	f->numerator = i;
	f->denominator = j;
	found[found_i++] = f;
      }
    }
  }

  fraction_t *result = malloc(sizeof(fraction_t));
  result->numerator = 1;
  result->denominator = 1;
  for (int i=0; i<4; i++) {
    fraction_multiply(result, found[i]);
  }
  
  printf("%"NUM_TYPE_PRINTF"\n", result->denominator);
  return 0;
}

int main(void) {
  int exit_code = time_wrapper(run);
  if (exit_code != 0) {
    perror("error");
  }

  return EXIT_SUCCESS;
}
