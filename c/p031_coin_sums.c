#include "euler.h"
#include <stdio.h>
#include <stdlib.h>

/*
 * In England the currency is made up of pound, £, and pence, p, and
 * there are eight coins in general circulation:
 *
 * 1p, 2p, 5p, 10p, 20p, 50p, Â£1 (100p) and £2 (200p).
 * It is possible to make Â£2 in the following way:
 *
 * 1x£1 + x50p + 2x20p + 1x5p + 1x2p + 31p
 * How many different ways can £2 be made using any number of coins?
 *
 *
 * Solution:
 * https://andrew.neitsch.ca/publications/m496pres1.nb.pdf
 */

static NUM_TYPE ways_change(int value, int coins) {
  static const int coin_types[] = {1,2,5,10,20,50,100,200};
  
  if (coins < 1 || value < 0) {
    return 0;
  } else if (value == 0) {
    return 1;
  } else {
    int coin = coin_types[coins-1];
    return ways_change(value, coins-1) + ways_change(value-coin, coins);
  }
}

static int run(void) {
  NUM_TYPE result = ways_change(200, 8);
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
