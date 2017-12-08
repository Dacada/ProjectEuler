#include "euler.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/*
 * Using names.txt (right click and 'Save Link/Target As...'), a 46K
 * text file containing over five-thousand first names, begin by
 * sorting it into alphabetical order. Then working out the
 * alphabetical value for each name, multiply this value by its
 * alphabetical position in the list to obtain a name score.
 *
 * For example, when the list is sorted into alphabetical order,
 * COLIN, which is worth 3 + 15 + 12 + 9 + 14 = 53, is the 938th name
 * in the list. So, COLIN would obtain a score of 938 x 53 = 49714.
 *
 * What is the total of all the name scores in the file?
 */

char names[6000][15]; // This is the table of names where we actually hold them
char *names_ptrs[6000]; // This is the table of pointers to those names for easy sorting.
size_t len_names;

static void parse_names(char *text) {
  enum { expect_first_quote, reading_val, expect_comma } state;
  state = expect_first_quote;

  int text_i=0, name_arr_i=0, name_txt_i=0;

  char c;
  while ((c=text[text_i++]) != '\0') {
    switch (state) {
    case expect_first_quote:
      if (c == '"') state = reading_val;
      break;
      
    case reading_val:
      if (c == '"') state = expect_comma;
      else names[name_arr_i][name_txt_i++] = c;
      break;
      
    case expect_comma:
      if (c == ',') {
	names[name_arr_i++][name_txt_i] = '\0';
	name_txt_i = 0;
	state = expect_first_quote;
      }
      break;
      
    default:
      break;
    }
  }

  len_names = name_arr_i+1; // Actual length. How many names there are.
}

static NUM_TYPE name_score(char *names[], size_t index) {
  char *name = names[index];

  NUM_TYPE score = 0;
  for (int i=0; i<15; i++) {
    if (name[i] == '\0') break;
    score += name[i] - 64;
  }

  return score*(index+1);
}

int cmp(const void *ptr1, const void *ptr2) {
  char *a = *(char *const *)ptr1;
  char *b = *(char *const *)ptr2;
  
  return strcmp(a, b);
}

static int run(void) {
  NUM_TYPE result = 0;

  qsort((void*)names_ptrs, len_names, sizeof(char*), cmp);

  for (int i=0; i<len_names; i++) {
    NUM_TYPE score = name_score(names_ptrs, i);
    result += score;
  }
  
  printf("%"NUM_TYPE_PRINTF"\n", result);
  return 0;
}

int main(void) {
  char *names_txt = read_url("https://projecteuler.net/project/resources/p022_names.txt");
  parse_names(names_txt);
  free(names_txt);

  // names_ptrs[i] is a pointer to the name in names[i]
  for (int i=0; i<len_names; i++) {
    names_ptrs[i] = names[i];
  }
  
  int exit_code = time_wrapper(run);
  if (exit_code != 0) {
    perror("error");
  }

  return EXIT_SUCCESS;
}
