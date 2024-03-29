#include "euler.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

/*
 * Pentagonal numbers are generated by the formula, Pn=n(3n-1)/2. The first ten
 * pentagonal numbers are:
 *
 * 1, 5, 12, 22, 35, 51, 70, 92, 117, 145, ...
 *
 * It can be seen that P4 + P7 = 22 + 70 = 92 = P8. However, their difference,
 * 70 - 22 = 48, is not pentagonal.
 *
 * Find the pair of pentagonal numbers, Pj and Pk, for which their sum and
 * difference are pentagonal and D = |Pk - Pj| is minimised; what is the value
 * of D?
 */

static NUM_TYPE get_pentagon(NUM_TYPE n) {
  return n*(3*n-1)/2;
}
static bool is_pentagon(NUM_TYPE n) {
  double dn = n;
  dn = (1+sqrt(24*dn+1))/6;
  return dn - (NUM_TYPE)dn == 0;
}

static int run(void) {
  for (NUM_TYPE j=1; j<10000; j++) {
    for (NUM_TYPE k=1; k<10000; k++) {
      if (k >= j) break;
      NUM_TYPE Pj = get_pentagon(j);
      NUM_TYPE Pk = get_pentagon(k);
      if (is_pentagon(Pj + Pk) && is_pentagon(Pj - Pk)) {
        printf("%"NUM_TYPE_PRINTF"\n", labs(Pj - Pk));
        return 0;
      }
    }
  }

  return 0;
}

int main(void) {
  int exit_code = time_wrapper(run);
  if (exit_code != 0) {
    perror("error");
  }

  return EXIT_SUCCESS;
}
