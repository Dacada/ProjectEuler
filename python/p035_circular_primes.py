#!/usr/bin/python2

"""
The number, 197, is called a circular prime because all rotations
of the digits: 197, 971, and 719, are themselves prime.

There are thirteen such primes below 100: 2, 3, 5, 7, 11, 13, 17, 31,
37, 71, 73, 79, and 97.

How many circular primes are there below one million?
"""

import itertools
import euler

def gen_rotations(n):
    current = list(str(n))
    new = current[:]
    
    for _ in xrange(len(current)):
        yield ''.join(new)
        for i in xrange(len(current)-1):
            new[i] = current[i+1]
        new[-1]  = current[0]
        current = new[:]

def main():
    with euler.TimeWrapper():
        primes = set(euler.primes_sieve(1000000))
        result = 0
        for prime in sorted(primes):
            rotations = set([r for r in gen_rotations(prime)])

            is_circular = True
            for rot in rotations:
                if int(rot) not in primes:
                    is_circular = False
                    break

            if is_circular:
                result += 1
        print result

if __name__ == '__main__':
    main()
