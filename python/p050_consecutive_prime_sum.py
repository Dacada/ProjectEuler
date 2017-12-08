#!/usr/bin/python2
#-*- encoding:utf-8 -*-

"""
The prime 41, can be written as the sum of six consecutive primes:

41 = 2 + 3 + 5 + 7 + 11 + 13

This is the longest sum of consecutive primes that adds to a prime
below one-hundred.

The longest sum of consecutive primes below one-thousand that adds to
a prime, contains 21 terms, and is equal to 953.

Which prime, below one-million, can be written as the sum of the most
consecutive primes?
"""

import itertools
import euler

def main():
    with euler.TimeWrapper():
        primes_to_million = [n for n in euler.primes_sieve(int(10**6))]
        primes_set = set(primes_to_million)
        result = None
        for n_terms in itertools.count(start=21):
            first = True
            for starting_index in range(0, len(primes_to_million)-n_terms):
                n=sum(primes_to_million[starting_index:starting_index+n_terms])
                if n > 10**6:
                    if first:
                        print result
                        return
                    else:
                        break
                first = False
                if n in primes_set:
                    result = n

if __name__ == "__main__":
    main()
