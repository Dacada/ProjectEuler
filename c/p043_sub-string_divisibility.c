#include "euler.h"
#include <stdio.h>
#include <stdlib.h>

/*
 The number, 1406357289, is a 0 to 9 pandigital number because it is made up of
 each of the digits 0 to 9 in some order, but it also has a rather interesting
 sub-string divisibility property.

 Let d1 be the 1st digit, d2 be the 2nd digit, and so on. In this way, we note
 the following:

 d_2 d_3 d_4 = 406 is divisible by 2
 d_3 d_4 d_5 = 063 is divisible by 3
 d_4 d_5 d_6 = 635 is divisible by 5
 d_5 d_6 d_7 = 357 is divisible by 7
 d_6 d_7 d_8 = 572 is divisible by 11
 d_7 d_8 d_9 = 728 is divisible by 13
 d_8 d_9 d_10 = 289 is divisible by 17

 Find the sum of all 0 to 9 pandigital numbers with this property.
 */

int get_num3(void **array, int start) {
  return (*(char*)array[0+start]-'0')*100 +
         (*(char*)array[1+start]-'0')*10 +
         (*(char*)array[2+start]-'0');
}

NUM_TYPE get_num10(void **array) {
  NUM_TYPE result = 0;
  for (int i=0; i<10; i++) {
    result = result*10 + *(char*)array[i]-'0';
  }
  return result;
}

static int run(void) {
  NUM_TYPE result = 0;
  char *number = "0123456789";
  void *number_void[10];
  for (int i=0; i<10; i++) {
    number_void[i] = (void*)number+i;
  }

  permutation_enumerator_t *e = permutation_enumerator_new(number_void, 10);
  void **permutation;
  while ((permutation = permutation_enumerator_next(e)) != NULL) {
    if (get_num3(permutation, 1) % 2 == 0 &&
        get_num3(permutation, 2) % 3 == 0 &&
        get_num3(permutation, 3) % 5 == 0 &&
        get_num3(permutation, 4) % 7 == 0 &&
        get_num3(permutation, 5) % 11 == 0 &&
        get_num3(permutation, 6) % 13 == 0 &&
        get_num3(permutation, 7) % 17 == 0) {
      NUM_TYPE n = get_num10(permutation);
      result += n;
    }
    free(permutation);
  }
  permutation_enumerator_free(e);

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
