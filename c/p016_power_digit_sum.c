#include "euler.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

/*
 * 2**15 = 32768 and the sum of its digits is 3 + 2 + 7 + 6 + 8 = 26.
 *
 * What is the sum of the digits of the number 2**1000?
 */

static int run(void) {
  NUM_TYPE result = 0;

  // Represent 2**1000 as an array of 32 32 bit integers: The most
  // significant number being 1<<8 and the rest 0. 32*31 = 992 bits
  // plus 8 bits to make 1000 bits of zeros. This array is in a big
  // endian format, that is, the most significant number is at index
  // 0.
  static uint32_t numerator[32] = { 1<<8 };

  // We also need a quotient for the divison. Initialized to 0.
  static uint32_t quotient[32];
  
  // The reminder will be small.
  uint32_t remainder = 0;

  // The divisor is small too.
  uint32_t divisor = 10;

  // Keep track of the number of bits in number
  size_t bits = 1001;

  // We'll need to keep dividing until we have nothing left to divide
  while (bits > 0) {
    // Division algorithm
    for (int i=bits-1; i>=0; i--) {
      // Get the bit i of the numerator. Bit 1000th is the 8th bit of
      // the number at index 0.
      int bit = numerator[31-i/32] & (1<<(i%32)); // will be 0 or 1<<N
    
      // Left shift the reminder by one
      remainder <<= 1;
      if (bit) remainder |= 1; // Set LSB of reminder
      // Otherwise leave it clear
    
      if (remainder >= divisor) {
	remainder -= divisor;
	quotient[31-i/32] |= 1<<(i%32); // Set bit i of quotient
      }
    }

    /*
    // Debugging
    printf("bits: %lu\n", bits);
    printf("quotient: ");
    for (int i=0; i<32; i++) {
      printf("%u,", quotient[i]);
    }
    printf("\nremainder: %d\n", remainder);
    getchar();
    */

    // The reminder is the last digit of the decimal representation of
    // the number while the quotient is the rest of digits. Add up the
    // reminder and prepare to divide again the quotient.
    result += remainder;

    // Reset reminder to 0
    remainder = 0;

    // Set quotient as the new numerator and reset quotient to 0.
    for (int i=0; i<32; i++) {
      numerator[i] = quotient[i];
      quotient[i] = 0;
    }

    // Compute the number of bits of the now numerator.
    bits = 0; // To break the loop if we've reached 0
    for (int i=0; i<32; i++) {
      if (numerator[i] != 0) {
	// GCC ONLY (other compilers might have similar builtins?)
	int leading_zeros = __builtin_clz(numerator[i]);
	bits = 32 - leading_zeros; //bits of this number
	bits += 32*(31-i); //add all the bits of the next numbers
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
