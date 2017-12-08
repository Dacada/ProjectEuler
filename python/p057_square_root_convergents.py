#!/usr/bin/python2
#-*- encoding:utf-8 -*-

"""
It is possible to show that the square root of two can be
expressed as an infinite continued fraction.

sqrt(2) = 1 + 1/(2 + 1/(2 + 1/(2 + ... ))) = 1.414213...

By expanding this for the first four iterations, we get:

1 + 1/2 = 3/2 = 1.5

1 + 1/(2 + 1/2) = 7/5 = 1.4

1 + 1/(2 + 1/(2 + 1/2)) = 17/12 = 1.41666...

1 + 1/(2 + 1/(2 + 1/(2 + 1/2))) = 41/29 = 1.41379...

The next three expansions are 99/70, 239/169, and 577/408, but the
eighth expansion, 1393/985, is the first example where the number of
digits in the numerator exceeds the number of digits in the
denominator.

In the first one-thousand expansions, how many fractions contain a
numerator with more digits than denominator?
"""

from fractions import Fraction as F
import euler
import sys

depths = {}
def sqrt2_den(depth):
    if depth == 0:
        return F(2)
    else:
        try:
            return depths[depth]
        except KeyError:
            result = F(2) + F(1)/sqrt2_den(depth-1)
            depths[depth] = result
            return result

def sqrt2(depth):
    return F(1) + F(1)/sqrt2_den(depth)

def main():
    sys.setrecursionlimit(1020)
    with euler.TimeWrapper():
        result = 0
        for i in reversed(range(1000)):
            n = sqrt2(i)
            if len(str(n.numerator)) > len(str(n.denominator)):
                result += 1
        print result

if __name__ == '__main__':
    main()
