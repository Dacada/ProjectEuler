#!/usr/bin/python2
#-*- encoding:utf-8 -*-

"""Starting with 1 and spiralling anticlockwise in the following way,
a square spiral with side length 7 is formed.

    37 36 35 34 33 32 31
    38 17 16 15 14 13 30
    39 18  5  4  3 12 29
    40 19  6  1  2 11 28
    41 20  7  8  9 10 27
    42 21 22 23 24 25 26
    43 44 45 46 47 48 49

It is interesting to note that the odd squares lie along the bottom
right diagonal, but what is more interesting is that 8 out of the 13
numbers lying along both diagonals are prime; that is, a ratio of 8/13
~= 62%.

If one complete new layer is wrapped around the spiral above, a square
spiral with side length 9 will be formed. If this process is
continued, what is the side length of the square spiral for which the
ratio of primes along both diagonals first falls below 10%?


From p28 we can get the equations we need:

n = 4*r**2 - 6*r + 3

n = 4*r**2 - 4*r + 1

n = 4*r**2 - 8*r + 5

n = 4*r**2 - 10*r + 7

spiral_count -> side_lengh: r -> 2r-1

Notice that the second equation can't be prime, and the rest can't be
prime either when r is divisible by the independent term.
"""

import itertools
import euler

def main():
    with euler.TimeWrapper():
        total = 1.0
        primes = 0.0
        for r in itertools.count(2):
                
            sq = 4*r**2
            for i in range(4):
                
                is_composite = False
                if i == 0:
                    if r%3==0:
                        is_composite = True
                    else:
                        n = sq - 6*r + 3
                elif i == 1:
                    #n = sq - 4*r + 1
                    is_composite = True
                elif i == 2:
                    if r%5==0:
                        is_composite = True
                    else:
                        n = sq - 8*r + 5
                else:
                    if r%7==0:
                        is_composite = True
                    else:
                        n = sq - 10*r + 7

                total += 1
                if not is_composite and euler.is_prime(n):
                    primes += 1
                    
            if primes/total < 0.1:
                break

        result = 2*r-1
        print result

if __name__ == '__main__':
    main()
