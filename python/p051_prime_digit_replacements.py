#!/usr/bin/python2
#-*- encoding:utf-8 -*-

"""
By replacing the 1st digit of the 2-digit number *3, it turns out
that six of the nine possible values: 13, 23, 43, 53, 73, and 83, are
all prime.

By replacing the 3rd and 4th digits of 56**3 with the same digit, this
5-digit number is the first example having seven primes among the ten
generated numbers, yielding the family: 56003, 56113, 56333, 56443,
56663, 56773, and 56993. Consequently 56003, being the first member of
this family, is the smallest prime with this property.

Find the smallest prime which, by replacing part of the number (not
necessarily adjacent digits) with the same digit, is part of an eight
prime value family.
"""

import itertools
import euler

def main():
    with euler.TimeWrapper():
        primes = set([n for n in euler.primes_sieve(10000000)])
        
        five_digit_patterns = [
            [True,False,False,False,True],
            [False,True,False,False,True],
            [False,False,True,False,True],
            [False,False,False,True,True]
        ]
        six_digit_patterns = [
            [True,True,False,False,False,True],
            [True,False,True,False,False,True],
            [True,False,False,True,False,True],
            [True,False,False,False,True,True],
            [False,True,True,False,False,True],
            [False,True,False,True,False,True],
            [False,True,False,False,True,True],
            [False,False,True,True,False,True],
            [False,False,True,False,True,True],
            [False,False,False,True,True,True]
        ]
        
        for pattern in five_digit_patterns + six_digit_patterns:
            for fixed in range(1+int('9'*len([_ for _ in pattern if _]))): #0...999
                fixed = str(fixed)
                fixed = '0'*(len([_ for _ in pattern if _])-len(fixed)) + fixed #000...999
                i=0
                filled_pattern = pattern[:]
                while True in filled_pattern:
                    filled_pattern[filled_pattern.index(True)] = fixed[i]
                    i += 1
                #All "fixed" digits set for this try, now let's
                #replace all the False with a single digit 0 to 9 and
                #test for primality
                primes_list = []
                for variable in range(1,10):
                    n = ''
                    for digit in filled_pattern:
                        if not digit:
                            n += str(variable)
                        else:
                            n += str(digit)
                    primes_list.append(n)
                if len( [n for n in primes_list if int(n) in primes] ) == 8:
                    result = min([int(n) for n in primes_list])
                    print result
                    return

if __name__ == '__main__':
    main()
