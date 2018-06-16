#include "euler.h"
#include <stdio.h>
#include <stdlib.h>

/*
 * A permutation is an ordered arrangement of objects. For example,
 * 3124 is one possible permutation of the digits 1, 2, 3 and 4. If
 * all of the permutations are listed numerically or alphabetically,
 * we call it lexicographic order. The lexicographic permutations of
 * 0, 1 and 2 are:
 *
 * 012   021   102   120   201   210
 *
 * What is the millionth lexicographic permutation of the digits 0, 1,
 * 2, 3, 4, 5, 6, 7, 8 and 9?
 */

void swap(char* s, int a, int b) {
  char temp = s[a];
  s[a] = s[b];
  s[b] = temp;
}

int permute(char* str, int len) {
  int key = len-1;
  int newkey = len-1;

  while ((key > 0) && (str[key] <= str[key-1]))
    key--;
  key--;

  if (key < 0)
    return 0;

  newkey = len-1;
  while ((newkey > key) && (str[newkey] <= str[key])){
    newkey--;
  }

  swap(str,key,newkey);

  len--;
  key++;
  while(len>key){
    swap(str,len,key);
    key++;
    len--;
  }

  return 1;
}

static int run(void) {
  char elements[] = "0123456789";
  int count = 0;
  while (++count < 1000000) permute(elements, 10);
  printf("%s", elements);
  printf("\n");
  return 0;
}

int main(void) {
  int exit_code = time_wrapper(run);
  if (exit_code != 0) {
    perror("error");
  }

  return EXIT_SUCCESS;
}
