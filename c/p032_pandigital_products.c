#include "euler.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * We shall say that an n-digit number is pandigital if it makes use
 * of all the digits 1 to n exactly once; for example, the 5-digit
 * number, 15234, is 1 through 5 pandigital.
 *
 * The product 7254 is unusual, as the identity, 39 x 186 = 7254,
 * containing multiplicand, multiplier, and product is 1 through 9
 * pandigital.
 *
 * Find the sum of all products whose multiplicand/multiplier/product
 * identity can be written as a 1 through 9 pandigital.
 *
 * HINT: Some products can be obtained in more than one way so be sure
 * to only include it once in your sum.
 */

static int to_int(void *char_array[], int start, int end) {
  int result = 0;
  for (int i=start; i<end; i++) {
    result = result*10 + (*(char*)char_array[i]-'0');
  }
  return result;
}

static int run(void) {
  NUM_TYPE result = 0;
  char elements[] = "123456789";
  const size_t maxnum = 100000;
  bool numbers[maxnum];

  for (int i=0; i<maxnum; i++) numbers[i] = false;

  void *elements_void[9];
  for (int i=0; i<9; i++) {
    elements_void[i] = (void*)elements+i;
  }

  void **permutation;
  permutation_enumerator_t *e = permutation_enumerator_new(elements_void, 9);
  while ((permutation = permutation_enumerator_next(e)) != NULL) {
    for (int i = 1; i <= 7; i++) {
      for (int j = i+1; j <= 8; j++) {
	      int a = to_int(permutation,0,i);
	      int b = to_int(permutation,i,j);
	      int c = to_int(permutation,j,9);
	      if (a * b == c) {
	       numbers[c] = true;
	      }
      }
    }
    free(permutation);
  }
  permutation_enumerator_free(e);

  for (int i=1; i<maxnum; i++) {
    if (numbers[i]) result += i;
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
