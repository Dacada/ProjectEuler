#include "euler.h"
#include <stdio.h>
#include <stdlib.h>

/*
 * You are given the following information, but you may prefer to do
 * some research for yourself.
 *
 *  * 1 Jan 1900 was a Monday.
 *
 *  * Thirty days has September,
 *    April, June and November.
 *    All the rest have thirty-one,
 *    Saving February alone,
 *    Which has twenty-eight, rain or shine.
 *    And on leap years, twenty-nine.
 *
 *  * A leap year occurs on any year evenly divisible by 4, but not on
 *    a century unless it is divisible by 400.
 *
 * How many Sundays fell on the first of the month during the
 * twentieth century (1 Jan 1901 to 31 Dec 2000)?
 */

unsigned day_of_week(unsigned y, unsigned m, unsigned d) {
  static unsigned t[12] = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 };
  y -= m < 3 ? 1 : 0;
  return (y + y/4 - y/100 + y/400 + t[m-1] + d) % 7;
}

static int run(void) {
  NUM_TYPE result = 0;

  for (unsigned year = 1901; year <= 2000; year++) {
    for (unsigned month = 1; month <= 12; month++) {
      if (day_of_week(year, month, 1) == 0) {
	result++;
      }
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
