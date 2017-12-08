#!/usr/bin/python2
#-*- encoding:utf-8 -*-

"""
145 is a curious number, as 1! + 4! + 5! = 1 + 24 + 120 = 145.

Find the sum of all numbers which are equal to the sum of the
factorial of their digits.

Note: as 1! = 1 and 2! = 2 are not sums they are not included.
"""

import math
import euler

def main():
    with euler.TimeWrapper():
        factorials = [math.factorial(i) for i in range(10)]
        limit = factorials[9]*9
        result = 0
        for number in xrange(3,limit):
            sum_factorials = sum([factorials[int(c)] for c in str(number)])
            if sum_factorials == number:
                result += number
        print result

if __name__ == '__main__':
    main()    
