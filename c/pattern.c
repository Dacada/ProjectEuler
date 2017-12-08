#include "euler.h"
#include <stdio.h>
#include <stdlib.h>

/*
 *
 */

static int run(void) {
  NUM_TYPE result;
  
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
