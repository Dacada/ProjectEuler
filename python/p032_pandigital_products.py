#!/usr/bin/python2
#-*- encoding:utf-8 -*-

"""
We shall say that an n-digit number is pandigital if it makes use
of all the digits 1 to n exactly once; for example, the 5-digit
number, 15234, is 1 through 5 pandigital.

The product 7254 is unusual, as the identity, 39 x 186 = 7254,
containing multiplicand, multiplier, and product is 1 through 9
pandigital.

Find the sum of all products whose multiplicand/multiplier/product
identity can be written as a 1 through 9 pandigital.

HINT: Some products can be obtained in more than one way so be sure to
only include it once in your sum.
"""

import itertools
import euler

def to_int(t):
    """
    Iterate over t and append all numbers together to make an int
    """
    return int(''.join([str(e) for e in t]))

def divisions(l):
    """
    Yield all possible divisions of l in 3 parts.
    """
    for i in range(1,len(l)-1):
        for j in range(i+1,len(l)):
            yield l[0:i],l[i:j],l[j:len(l)]

def main():
    with euler.TimeWrapper():
        s = set()
        for l in itertools.permutations([1,2,3,4,5,6,7,8,9]):
            for a,b,c in divisions(l):
                ia = to_int(a)
                ib = to_int(b)
                ic = to_int(c)
                if ia*ib == ic:
                    s.add(to_int(c))

        result = sum(s)
        print result
            
if __name__ == "__main__":
    main()
