#include "euler.h"
#include <stdio.h>
#include <stdlib.h>

/*
 * If the numbers 1 to 5 are written out in words: one, two, three,
 * four, five, then there are 3 + 3 + 5 + 4 + 4 = 19 letters used in
 * total.
 *
 * If all the numbers from 1 to 1000 (one thousand) inclusive were
 * written out in words, how many letters would be used?
 *
 * NOTE: Do not count spaces or hyphens. For example, 342 (three
 * hundred and forty-two) contains 23 letters and 115 (one hundred and
 * fifteen) contains 20 letters. The use of "and" when writing out
 * numbers is in compliance with British usage.
 */

static int run(void) {
  NUM_TYPE result = 0;

  int numbers[91];
  numbers[0] = 4; /*zero*/   numbers[10] = 3; /*ten*/
  numbers[1] = 3; /*one*/    numbers[11] = 6; /*eleven*/
  numbers[2] = 3; /*two*/    numbers[12] = 6; /*twelve*/     numbers[20] = 6; /*twenty*/
  numbers[3] = 5; /*three*/  numbers[13] = 8; /*thirteen*/   numbers[30] = 6; /*thirty*/
  numbers[4] = 4; /*four*/   numbers[14] = 8; /*fourteen*/   numbers[40] = 5; /*forty*/
  numbers[5] = 4; /*five*/   numbers[15] = 7; /*fifteen*/    numbers[50] = 5; /*fifty*/
  numbers[6] = 3; /*six*/    numbers[16] = 7; /*sixteen*/    numbers[60] = 5; /*sixty*/
  numbers[7] = 5; /*seven*/  numbers[17] = 9; /*seventeen*/  numbers[70] = 7; /*seventy*/
  numbers[8] = 5; /*eight*/  numbers[18] = 8; /*eighteen*/   numbers[80] = 6; /*eighty*/
  numbers[9] = 4; /*nine*/   numbers[19] = 8; /*nineteen*/   numbers[90] = 6; /*ninety*/

  int thousand = 8;
  int hundred = 7;
  int and = 3;
  
  for (int hundreds = 0; hundreds < 10; hundreds++) {
    for (int tenths = 0; tenths < 10; tenths++) {
      for (int units = 0; units < 10; units++) {
	if (hundreds != 0) {
	  result += numbers[hundreds] + hundred;
	  if (tenths != 0 || units != 0) {
	    result += and;
	  }
	}

	if (tenths == 1 && units != 0) {
	  result += numbers[tenths*10+units];
	} else {
	  if (tenths != 0) {
	    result += numbers[tenths*10];
	  }
	  if (units != 0) {
	    result += numbers[units];
	  }
	}
      }
    }
  }

  result += numbers[1];
  result += thousand;
  
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
