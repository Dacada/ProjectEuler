#include "euler.h"
#include <stdio.h>
#include <stdlib.h>

/*
 * If p is the perimeter of a right angle triangle with integral
 * length sides, {a,b,c}, there are exactly three solutions for p =
 * 120.
 *
 * {20,48,52}, {24,45,51}, {30,40,50}
 *
 * For which value of p <= 1000, is the number of solutions maximised?
 */

static int run(void) {
  static int solutions[1001];
  
  for (int a = 1; a < 1000; a++) {
    for (int b = 1; b < 1000; b++) {
      for (int c = 1; c < 1000; c++) {
	int p = a+b+c;
	if (p < 1001 && a*a + b*b == c*c) {
	  solutions[p]++;
	}
      }
    }
  }

  int max_p = 0;
  int curr_max = 0;
  for (int i=0; i<1001; i++) {
    if (solutions[i] > curr_max) {
      max_p = i;
      curr_max = solutions[i];
    }
  }

  NUM_TYPE result = max_p;
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
