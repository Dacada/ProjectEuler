#include "euler.h"
#include <string.h>
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

static NUM_TYPE to_num(char string[], int size) {
  int result = 0;
  for (int i=0; i<size; i++) {
    result = result*10 + (string[i]-'0');
  }
  return result;
}

static NUM_TYPE n_pandigital(int n) {
  char elements[n+1];
  char limit[n+1];
  for (int i=0; i<n; i++) {
    elements[i] = '0'+(i+1);
  }
  for (int i=0; i<n; i++) {
    limit[i] = '0'+(n-i);
  }
  elements[n] = limit[n] = 0;

  NUM_TYPE max = 0;
  while (true) {
    NUM_TYPE number = to_num(elements, n);
    
    if (is_prime(number)) {
      if (number > max) {
	max = number;
      }
    }
    
    permute(elements, n);
    if (strcmp(elements, limit) == 0) break;
  }

  return max;
}

static int run(void) {
  for (int i=9; i>0; i--) {
    NUM_TYPE result = n_pandigital(i);
    if (result != 0) {
      printf("%"NUM_TYPE_PRINTF"\n", result);
      break;
    }
  }
  
  return 0;
}

int main(void) {
  int exit_code = time_wrapper(run);
  if (exit_code != 0) {
    perror("error");
  }

  return EXIT_SUCCESS;
}
