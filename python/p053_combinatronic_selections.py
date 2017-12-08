#!/usr/bin/python2
#-*- encoding:utf-8 -*-

"""
There are exactly ten ways of selecting three from five, 12345:

123, 124, 125, 134, 135, 145, 234, 235, 245, and 345

In combinatorics, we use the notation, 5C3 = 10.

In general,

          n!
nCr = ----------
       r!(n-r)!
Where r <= n, n! = n x (n-1) x ... x 3 x 2 x 1, and 0! = 1.

It is not until n = 23, that a value exceeds one-million: 23C10 =
1144066.

How many, not necessarily distinct, values of nCr, for 1 <= n <= 100,
are greater than one-million?
"""

import euler
import math

def nCr(n,r):
    return math.factorial(n)/(math.factorial(r)*math.factorial(n-r))

def main():
    with euler.TimeWrapper():
        result = 0
        for n in range(1,101):
            for r in range(1,n+1):
                if nCr(n,r) > 1000000:
                    result += 1
        print result

if __name__ == '__main__':
    main()
