#!/usr/bin/python2
#-*- encoding:utf-8 -*-

"""
The first two consecutive numbers to have two distinct prime
factors are:

14 = 2 x 7
15 = 3 x 5

The first three consecutive numbers to have three distinct prime
factors are:

644 = 2^2 x 7 x 23
645 = 3 x 5 x 43
646 = 2 x 17 x 19.

Find the first four consecutive integers to have four distinct prime
factors. What is the first of these numbers?
"""

import itertools
import subprocess
import euler

def main():
    with euler.TimeWrapper():
        limit = 1000000 #guess
        sieve = [()]*limit #This sieve contians tuples of prime factors
        sieve[0] = None
        sieve[1] = None
        for i in xrange(2,limit):
            if len(sieve[i]) == 4 and\
               len(sieve[i+1]) == 4 and\
               len(sieve[i+2]) == 4 and\
               len(sieve[i+3]) == 4:
                print i
                return
            if not sieve[i]:
                for j in xrange(i*2, limit, i):
                    sieve[j] += (i,)

if __name__ == "__main__":
    main()

