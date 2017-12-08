#!/usr/bin/python2

"""
It was proposed by Christian Goldbach that every odd composite
number can be written as the sum of a prime and twice a square.

9 = 7 + 2x1^2
15 = 7 + 2x2^2
21 = 3 + 2x3^2
25 = 7 + 2x3^2
27 = 19 + 2x2^2
33 = 31 + 2x1^2

It turns out that the conjecture was false.

What is the smallest odd composite that cannot be written as the sum
of a prime and twice a square?
"""

from __future__ import division

import itertools
import subprocess
import math
import euler

def main():
    with euler.TimeWrapper():
        for n in itertools.count(35,2):
            if euler.is_prime(n):
                continue
            if n % 15 == 0:
                continue
            passed = False
            for pn in euler.primes_sieve(n):
                r = math.sqrt((n-pn)/2)
                if r == int(r):
                    passed = True
                    break
            if not passed:
                print int(n)
                return

if __name__ == "__main__":
    main()
