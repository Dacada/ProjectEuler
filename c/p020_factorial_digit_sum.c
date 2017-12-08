#include "euler.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

/*
 * n! means n x (n - 1) x ... x 3 x 2 x 1
 *
 * For example, 10! = 10 x 9 x ... x 3 x 2 x 1 = 3628800, and the sum
 * of the digits in the number 10! is 3 + 6 + 2 + 8 + 8 + 0 + 0 = 27.
 *
 * Find the sum of the digits in the number 100!
 */

static int run(void) {
  NUM_TYPE result = 0;

  // First calculate the number 100! and keep it in memory. We replace
  // multiplying by multiples of 10 with multiplying by the number
  // divided by 10. So by 4 instead of 40. A made up upper bound on
  // the number of bits of this number: 1024. Fits in an array of 32
  // 32 bit numbers.

  // Allocate space for the result
  static uint32_t mult_result[32]; // Initialized at 0

  // Allocate space for the multiplicand (starts at 0)
  static uint32_t multiplicand[32];
  multiplicand[31] = 1; // Initialized at 1

  // Iterate over all multiplicands from 1 to 99. We'll do
  // mult_result = mult * multiplicand;
  for (int mult_i = 2; mult_i < 100; mult_i++) { //100 is unnecesary too, just adds two 0s
    
    uint64_t mult;
    if (mult_i % 10 == 0) mult = mult_i/10;
    else mult = mult_i;
    if (mult == 1) continue;

    // Multiply multiplicand by mult.
    uint64_t carry = 0;
    for (int i=31; i>=0; i--) {
      uint64_t tmp_result = mult * (uint64_t)multiplicand[i] + carry;
      carry = (tmp_result & 0xFFFFFFFF00000000) >> 32;
      mult_result[i] = tmp_result & 0x00000000FFFFFFFF;
    }
    
    // discard carry, it should always be 0 at this point (if upper bound is any good)
    if (carry != 0) printf("OMGWTFBBQ!!\n");

    //Update multiplicand = result and result = 0, for the next cycle.
    for (int i=0; i<32; i++) {
      multiplicand[i] = mult_result[i];
      mult_result[i] = 0;
    }
  }

  // now multiplicand == 100!
  // We can reuse an old problem to extract and sum its digits.

  // FROM p16_power_digit_sum.c BUT WITHOUT THE MANY COMENTS
  // TODO: Make this into a function, sum_digits, and add it to euler.c?

  // reuse old variables but with different names
  uint32_t *numerator = multiplicand;
  uint32_t *quotient = mult_result;

  uint32_t remainder;
  uint32_t divisor = 10;

  size_t bits = 0;
  // Compute the number of bits first this time since we don't know it.
  for (int i=0; i<32; i++) {
    if (numerator[i] != 0) {
      int leading_zeros = __builtin_clz(numerator[i]);
      bits = 32 - leading_zeros;
      bits += 32*(31-i);
      break;
    }
  }

  while (bits > 0) {
    // Division algorithm
    for (int i=bits-1; i>=0; i--) {
      int bit = numerator[31-i/32] & (1<<(i%32));
      
      remainder <<= 1;
      if (bit) remainder |= 1;
    
      if (remainder >= divisor) {
	remainder -= divisor;
	quotient[31-i/32] |= 1<<(i%32);
      }
    }

    // Reset variables to keep dividing
    result += remainder;
    remainder = 0;

    for (int i=0; i<32; i++) {
      numerator[i] = quotient[i];
      quotient[i] = 0;
    }

    // New number of bits
    bits = 0;
    for (int i=0; i<32; i++) {
      if (numerator[i] != 0) {
	int leading_zeros = __builtin_clz(numerator[i]);
	bits = 32 - leading_zeros;
	bits += 32*(31-i);
	break;
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
