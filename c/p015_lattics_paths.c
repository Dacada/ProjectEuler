#include "euler.h"
#include <stdio.h>
#include <stdlib.h>

/*
 * Starting in the top left corner of a 2x2 grid, and only being able
 * to move to the right and down, there are exactly 6 routes to the
 * bottom right corner.
 *
 * ...
 *
 * How many such routes are there through a 20x20 grid?
 */

static NUM_TYPE nroutes(size_t x, size_t y) {
  static NUM_TYPE memory[21][21];
  NUM_TYPE result;
  
  if (x == 0 && y == 0) {
    return 1;
  } else {
    if (memory[y][x] != 0) {
      result = memory[y][x];
    } else if (x == 0) {
      result = nroutes(x, y-1);
    } else if (y == 0) {
      result = nroutes(x-1, y);
    } else {
      result = nroutes(x-1, y) + nroutes(x, y-1);
    }
    
    memory[y][x] = result;
    return result;
  }
}

static int run(void) {
  NUM_TYPE result = nroutes(20, 20);
  
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
