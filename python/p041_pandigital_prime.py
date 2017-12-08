#!/usr/bin/python2
#-*- encoding:utf-8 -*-

"""
We shall say that an n-digit number is pandigital if it makes use
of all the digits 1 to n exactly once. For example, 2143 is a 4-digit
pandigital and is also prime.

What is the largest n-digit pandigital prime that exists?
"""

import math
import itertools
import euler

def all_combinations_until(n):
    return [ int("".join(number)) for number in itertools.permutations([str(k) for k in range(1,n+1)],n) ]

def main():
    with euler.TimeWrapper():
        numbers = []
        for n in range(1,10):
            numbers += all_combinations_until(n)

        result = 0
        for n in numbers:
            if n > result and euler.is_prime(n):
                result = n
        print result

if __name__ == '__main__':
    main()
