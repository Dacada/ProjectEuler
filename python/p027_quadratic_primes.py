#!/usr/bin/python2
#-*- encoding:utf-8 -*-

"""
Euler discovered the remarkable quadratic formula:

n**2 + n + 41

It turns out that the formula will produce 40 primes for the
consecutive values n = 0 to 39. However, when n = 40, 40**2 + 40 + 41
= 40(40 + 1) + 41 is divisible by 41, and certainly when n = 41, 41**2
+ 41 + 41 is clearly divisible by 41.

The incredible formula n**2 - 79*n + 1601 was discovered, which
produces 80 primes for the consecutive values n = 0 to 79. The product
of the coefficients, -79 and 1601, is -126479.

Considering quadratics of the form:

n**2 + a*n + b, where |a| < 1000 and |b| < 1000

(where |n| is the modulus/absolute value of n) e.g. |11| = 11 and |-4|
= 4

Find the product of the coefficients, a and b, for the quadratic
expression that produces the maximum number of primes for consecutive
values of n, starting with n = 0.
"""

import itertools
import math
import euler

def how_many_primes(a,b):
    if not euler.is_prime( abs(b) ):
        return 0
    for n in itertools.count():
        r = n*n + a*n + b
        if not euler.is_prime( abs(r) ):
            return n-1

def main():
    with euler.TimeWrapper():
        result = (0,0,0)
        for i in xrange(-1000,1001):
            for j in xrange(-1000,1001):
                p = how_many_primes(i,j)
                if p > result[0]:
                    result = (p,i,j)

	print result[1]*result[2]
        

if __name__ == "__main__":
        main()
