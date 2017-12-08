#!/usr/bin/python2
#-*- encoding:utf-8 -*-

"""
The sum of the primes below 10 is 2 + 3 + 5 + 7 = 17.

Find the sum of all the primes below two million.
"""

import euler

def main():
    limit = 2000000
    with euler.TimeWrapper():
        result = sum([p for p in euler.primes_sieve(limit)])
                    
        print result

if __name__ == '__main__':
    main()
