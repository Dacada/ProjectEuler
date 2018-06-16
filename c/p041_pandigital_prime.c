#include "euler.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/*
 * We shall say that an n-digit number is pandigital if it makes use
 * of all the digits 1 to n exactly once. For example, 2143 is a
 * 4-digit pandigital and is also prime.
 *
 * What is the largest n-digit pandigital prime that exists?
 */

static NUM_TYPE to_num(void **string, int size) {
  int result = 0;
  for (int i=0; i<size; i++) {
    result = result*10 + (*(char*)string[i]-'0');
  }
  return result;
}

static NUM_TYPE n_pandigital(int n) {
  char elements[n];
  for (int i=0; i<n; i++) {
    elements[i] = '0'+(i+1);
  }

  void *elements_void[n];
  for (int i=0; i<n; i++) {
    elements_void[i] = (void*)elements+i;
  }

  permutation_enumerator_t *e = permutation_enumerator_new(elements_void, n);

  void **permutated_elements;
  NUM_TYPE max = 0;
  while ((permutated_elements = permutation_enumerator_next(e)) != NULL) {
    NUM_TYPE number = to_num(permutated_elements, n);

    if (is_prime(number)) {
      if (number > max) {
	      max = number;
      }
    }
    free(permutated_elements);
  }
  permutation_enumerator_free(e);

  return max;
}

static int run(void) {
  for (int i=9; i>0; i--) {
    NUM_TYPE result = n_pandigital(i);
    if (result != 0) {
      printf("%"NUM_TYPE_PRINTF"\n", result);
      break;
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
