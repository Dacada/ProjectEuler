#include "euler.h"
#include <stdio.h>
#include <stdlib.h>

/*
 * We shall say that an n-digit number is pandigital if it makes use
 * of all the digits 1 to n exactly once. For example, 2143 is a
 * 4-digit pandigital and is also prime.
 *
 * What is the largest n-digit pandigital prime that exists?
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

static int numbers_one_to_n_str(int n, char *str) {
  for (int i=n; i>0; i--) {
    
  }
}

static int run(void) {
  NUM_TYPE result = 0;

  for (int n = 9; n > 0; n--) {
    char numstr[10];
    char original_numstr[10];
    int numstrlen;
    
    numstrlen = numbers_one_to_n_str(n, numstr);
    strcpy(original_numstr, numstr);
    
    do {
      NUM_TYPE number = atol(numstr);
      if (number > result && is_prime(number)) {
	result = number;
      }
      
      permute(numstr, numstrlen);
    } while (strcmp(original_numstr, numstr) != 0)
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
