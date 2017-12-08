#!/usr/bin/python2

"""
The number 3797 has an interesting property. Being prime itself,
it is possible to continuously remove digits from left to right, and
remain prime at each stage: 3797, 797, 97, and 7. Similarly we can
work from right to left: 3797, 379, 37, and 3.

Find the sum of the only eleven primes that are both truncatable from
left to right and right to left.

NOTE: 2, 3, 5, and 7 are not considered to be truncatable primes.
"""

import math
import euler

def gimme_primes_reversed(n):
    while n >= 2:
        if is_prime(n):
            yield n
        n -= 1

def is_prime(n):
    if n<=1: return False
    if n==2: return True
    for i in range(2,int(math.ceil(math.sqrt(n)))+1):
        if n % i == 0:
            return False
    return True

def all_truncations(n):
    r = []
    s = str(n)
    while s != "":
        r.append(s)
        s = s[1:]
    s = str(n)
    l = len(s)
    s = s[:l-1]
    l = len(s)
    while s != "":
        r.append(s)
        s = s[:l-1]
        l = len(s)
    return [int(i) for i in r]

def one_digit(n):
    return len(str(n)) == 1

def main():
    with euler.TimeWrapper():
        s = set([])
        i = 0
        
        for p in reversed([p for p in euler.primes_sieve(1000000)]):
            if len(s) == 11:
                break
            if p in s:
                continue
            ps = all_truncations(p)
            if all(is_prime(i) for i in ps):
                s.add(p)

        result = sum(s)
        print result

if __name__ == '__main__':
    main()    
