#!/usr/bin/python2
#-*- encoding:utf-8 -*-

"""
2520 is the smallest number that can be divided by each of the
numbers from 1 to 10 without any remainder.

What is the smallest positive number that is evenly divisible by all
of the numbers from 1 to 20?


The resulting number N must contain the prime factors of all numbers
from 1 to 20. Each prime factor must be repeated as many times as
possible without going over 20. For example, 2 must be repeated 4
times since 2**4==16 but 2**5==32. Mathematically: 4 == log(20)/log(2)
"""

import math
import euler

def main():
    with euler.TimeWrapper():
        max_divisor = 20
        log_max_divisor = math.log(max_divisor)
        result = 1
        check = True
        limit = int(math.sqrt(max_divisor))

        for prime in euler.primes_sieve(max_divisor):
            exponent = 1
            if check:
                if prime <= limit:
                    exponent = int( log_max_divisor/math.log(prime) )
                else:
                    check = False
            result = result * prime**exponent

        print result

if __name__ == '__main__':
    main()
