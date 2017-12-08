#include "euler.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

/*
 * A Pythagorean triplet is a set of three natural numbers, a < b < c,
 * for which,
 *
 * a**2 + b**2 = c**2
 *
 * For example, 3**2 + 4**2 = 9 + 16 = 25 = 5**2
 *
 * There exists exactly one Pythagorean triplet for which a + b + c =
 * 1000. Find the product abc.
 */

static int run(void) {
  static const NUM_TYPE s = 1000;

  NUM_TYPE s2 = s/2;
  double mlimit = sqrt((double)s2);
  for (size_t m=2; m<mlimit; m++) {
    if (s2 % m == 0) {
      NUM_TYPE sm = s2/m;
      while (sm % 2 == 0) {
	sm /= 2;
      }
      
      NUM_TYPE k;
      if (m % 2 == 1) {
	k = m + 2;
      } else {
	k = m + 1;
      }

      while (k < 2*m && k <= sm) {
	if (sm % k == 0 && gcd(k, m) == 1) {
	  NUM_TYPE d = s2/(k*m);
	  NUM_TYPE n = k-m;
	  NUM_TYPE a = d*(m*m-n*n);
	  NUM_TYPE b = 2*d*m*n;
	  NUM_TYPE c = d*(m*m+n*n);
	  NUM_TYPE result = a*b*c;
	  printf("%"NUM_TYPE_PRINTF"\n", result);
	  return 0;
	}
	k += 2;
      }
    }
  }
  
  return 1;
}

int main(void) {
  int exit_code = time_wrapper(run);
  if (exit_code != 0) {
    perror("error");
  }

  return EXIT_SUCCESS;
}
