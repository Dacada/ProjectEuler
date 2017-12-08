#!/usr/bin/python2
#-*- encoding:utf-8 -*-

"""
The sum of the squares of the first ten natural numbers is,

1**2 + 2**2 + ... + 10**2 = 385

The square of the sum of the first ten natural numbers is,

(1 + 2 + ... + 10)**2 = 552 = 3025

Hence the difference between the sum of the squares of the first ten
natural numbers and the square of the sum is 3025 - 385 = 2640.

Find the difference between the sum of the squares of the first one
hundred natural numbers and the square of the sum.


This can be done with formulas rather than brute force:
sum(n) = n*(n+1)/2
sum_sq(n) = (2*n+1)*(n+1)*n/6
"""

import euler

def main():
    with euler.TimeWrapper():
        n = 100
        sum = n*(n+1)/2
        sum_sq = (2*n+1)*(n+1)*n/6
        result = sum**2 - sum_sq

        print result

if __name__ == '__main__':
    main()
