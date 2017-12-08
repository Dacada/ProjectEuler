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

static void swap(char* s, int a, int b) {
  char temp = s[a];
  s[a] = s[b];
  s[b] = temp;
}

static int permute(char* str, int len) {
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

static int to_int(char string[], int start, int end) {
  int result = 0;
  for (int i=start; i<end; i++) {
    result = result*10 + (string[i]-'0');
  }
  return result;
}

static int run(void) {
  NUM_TYPE result = 0;
  char elements[] = "123456789";
  const size_t maxnum = 100000;
  bool numbers[maxnum];

  for (int i=0; i<maxnum; i++) numbers[i] = false;
  
  while (true) {
    permute(elements, 9);
    if (strcmp(elements, "987654321") == 0) break;

    for (int i = 1; i <= 7; i++) {
      for (int j = i+1; j <= 8; j++) {
	int a = to_int(elements,0,i);
	int b = to_int(elements,i,j);
	int c = to_int(elements,j,9);
	if (a * b == c) {
	  numbers[c] = true;
	}
      }
    }
  }

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
