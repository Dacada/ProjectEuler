#include "euler.h"
#include <stdio.h>
#include <stdlib.h>

/*
 * By starting at the top of the triangle below and moving to adjacent
 * numbers on the row below, the maximum total from top to bottom is
 * 23.
 *
 *    3
 *   7 4
 *  2 4 6
 * 8 5 9 3
 *
 * That is, 3 + 7 + 4 + 9 = 23.
 * 
 * Find the maximum total from top to bottom of the triangle below:
 *
 * ...
 *
 * NOTE: As there are only 16384 routes, it is possible to solve this
 * problem by trying every route. However, Problem 67, is the same
 * challenge with a triangle containing one-hundred rows; it cannot be
 * solved by brute force, and requires a clever method! ;o)
 *
 *
 * The clever method is to start from below:
 * 
 * Take the row before the last and for each number, sum the one below
 * it that is greater.
 *
 *    3
 *   7 4
 *  2 4 6
 * 8 5 9 3
 *
 *     03
 *   07  04
 * 10  13  15
 *
 *   03
 * 20  19
 *
 * 23
 *
 * The number that ends up in the top is the largest possible sum.
 */

static int run(void) {
  NUM_TYPE result;

  int pyramid[15][16] = {
    { 75,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
    { 95, 64,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
    { 17, 47, 82,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
    { 18, 35, 87, 10,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
    { 20,  4, 82, 47, 65,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
    { 19,  1, 23, 75,  3, 34,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
    { 88,  2, 77, 73,  7, 63, 67,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
    { 99, 65,  4, 28,  6, 16, 70, 92,  0,  0,  0,  0,  0,  0,  0,  0 },
    { 41, 41, 26, 56, 83, 40, 80, 70, 33,  0,  0,  0,  0,  0,  0,  0 },
    { 41, 48, 72, 33, 47, 32, 37, 16, 94, 29,  0,  0,  0,  0,  0,  0 },
    { 53, 71, 44, 65, 25, 43, 91, 52, 97, 51, 14,  0,  0,  0,  0,  0 },
    { 70, 11, 33, 28, 77, 73, 17, 78, 39, 68, 17, 57,  0,  0,  0,  0 },
    { 91, 71, 52, 38, 17, 14, 91, 43, 58, 50, 27, 29, 48,  0,  0,  0 },
    { 63, 66,  4, 68, 89, 53, 67, 30, 73, 16, 69, 87, 40, 31,  0,  0 },
    {  4, 62, 98, 27, 23,  9, 70, 98, 73, 93, 38, 53, 60,  4, 23,  0 }
  };

  int row = 13;
  int last_row = 14;

  while (last_row != 0) {
    for (int i=0;; i++) {
      if (pyramid[row][i] == 0) break;
      pyramid[row][i] += MAX(pyramid[last_row][i], pyramid[last_row][i+1]);
    }

    row--;
    last_row--;
  }

  result = pyramid[0][0];
  
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
