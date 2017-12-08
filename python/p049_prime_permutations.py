#!/usr/bin/python2
#-*- encoding:utf-8 -*-

"""
The arithmetic sequence, 1487, 4817, 8147, in which each of the
terms increases by 3330, is unusual in two ways: (i) each of the three
terms are prime, and, (ii) each of the 4-digit numbers are
permutations of one another.

There are no arithmetic sequences made up of three 1-, 2-, or 3-digit
primes, exhibiting this property, but there is one other 4-digit
increasing sequence.

What 12-digit number do you form by concatenating the three terms in
this sequence?
"""

from __future__ import division

import itertools
import subprocess
import euler

def is_permutation(a,b,c):
    return sorted(str(a)) == sorted(str(b)) == sorted(str(c))

def main():
    with euler.TimeWrapper():
        primes = [p for p in euler.primes_sieve(10000)]
        primes_set = set(primes)

        for first in primes:
            if first < 1488:
                continue
            for second in xrange(first+1,10000):
                if second not in primes_set:
                    continue
                
                third = second + (second - first)
                if third not in primes_set:
                    continue
                
                if not is_permutation(first,second,third):
                    continue

                print str(first)+str(second)+str(third)
                return

if __name__ == "__main__":
    main()
