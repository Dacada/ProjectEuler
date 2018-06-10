#include "euler.h"
#include <stdio.h>
#include <stdlib.h>

/*
 * The nth term of the sequence of triangle numbers is given by, tn =
 * (1/2)*n*(n+1); so the first ten triangle numbers are:
 *
 * 1, 3, 6, 10, 15, 21, 28, 36, 45, 55, ...
 *
 * By converting each letter in a word to a number corresponding to
 * its alphabetical position and adding these values we form a word
 * value. For example, the word value for SKY is 19 + 11 + 25 = 55 =
 * t10. If the word value is a triangle number then we shall call the
 * word a triangle word.
 *
 * Using words.txt (right click and 'Save Link/Target As...'), a 16K
 * text file containing nearly two-thousand common English words, how
 * many are triangle words?
 */

#define TRIANGLESLEN 4096
bool triangles[TRIANGLESLEN];

 void init_is_triangle() {
   for (NUM_TYPE n = 0; n<TRIANGLESLEN; n++) {
     triangles[n] = false;
   }

   for (NUM_TYPE n = 0, t = 0; t < TRIANGLESLEN; n++, t = (n*(n+1))/2) {
     triangles[t] = true;
   }
 }

bool is_triangle(NUM_TYPE n) {
  return triangles[n];
}

static int run(void) {
  NUM_TYPE result = 0, sum = 0;
  char *input = read_url("https://projecteuler.net/project/resources/p042_words.txt");

  init_is_triangle();
  for (int i=0;; i++) {
    char c = input[i];
    if (c == '\0') {
      break;
    }
    if (c == '"') {
      continue;
    }

    if (c == ',') {
      if (is_triangle(sum)) {
        result++;
      }
      sum = 0;
    } else {
      sum += c - 0x40;
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
