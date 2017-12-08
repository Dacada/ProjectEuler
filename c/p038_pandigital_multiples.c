#include "euler.h"
#include <stdio.h>
#include <stdlib.h>

/*
 * Take the number 192 and multiply it by each of 1, 2, and 3:
 *
 * 192 x 1 = 192
 * 192 x 2 = 384
 * 192 x 3 = 576
 *
 * By concatenating each product we get the 1 to 9 pandigital,
 * 192384576. We will call 192384576 the concatenated product of 192
 * and (1,2,3)
 *
 * The same can be achieved by starting with 9 and multiplying by 1,
 * 2, 3, 4, and 5, giving the pandigital, 918273645, which is the
 * concatenated product of 9 and (1,2,3,4,5).
 *
 * What is the largest 1 to 9 pandigital 9-digit number that can be
 * formed as the concatenated product of an integer with (1,2, ... ,
 * n) where n > 1?
 */

NUM_TYPE mult(NUM_TYPE n, bool nums[10]) {
  NUM_TYPE result = 0;
  NUM_TYPE mult = 10;
  
  for (int i=0; i<10; i++) {
    if (!nums[i]) continue;
    NUM_TYPE r = n*i;
    NUM_TYPE r_copy = r;
    
    int r_digits = 0;
    while (r > 0) {
      r /= 10;
      r_digits++;
    }
    r = r_copy;

    result = result*mult + r;

    for (int i=0; i<r_digits; i++) {
      mult *= 10;
    }
  }

  return result;
}

bool is_pandigital(NUM_TYPE n) {
  bool nums[10];
  for (int i=0; i<10; i++) {
    nums[i] = false;
  }
  nums[0] = true;

  while (n > 0) {
    int num = n % 10;
    if (nums[num]) return false;
    else nums[num] = true;
    n /= 10;
  }

  for (int i=0; i<10; i++) {
    if (!nums[i]) return false;
  }

  return true;
}

static int run(void) {
  NUM_TYPE result = 0;
  
  for (int n=2; n<=9; n++) {
    for (NUM_TYPE i=2; i<456789; i++) {
      bool nums[10];
      nums[0] = false;
      for (int i=1; i<=n; i++) {
	nums[i] = true;
      }
      for (int i=n+1; i<10; i++) {
	nums[i] = false;
      }
      
      NUM_TYPE r = mult(i, nums);
      
      if (r != 0 && r > result && is_pandigital(r)) {
	result = r;
      }
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
