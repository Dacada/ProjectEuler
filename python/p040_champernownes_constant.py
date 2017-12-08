#!/usr/bin/python2
#-*- encoding:utf-8 -*-

"""
An irrational decimal fraction is created by concatenating the
positive integers:

0.123456789101112131415161718192021...

It can be seen that the 12th digit of the fractional part is 1.

If d_n represents the nth digit of the fractional part, find the value
of the following expression.

d_1 x d_{10} x d_{100} x d_{1000} x d_{10000} x d_{100000} x d_{1000000}
"""

import itertools
import euler

def main():
    with euler.TimeWrapper():
        targets = [ 10**i for i in range(7) ]
        nchar = 0
        result = 1
        for n in itertools.count(1):
            for i in range(len(str(n))):
                nchar += 1
                if not targets:
                    print result
                    return
                if nchar == targets[0]:
                    #print str(n)[i],n,i
                    result *= int(str(n)[i])
                    targets = targets[1:]

if __name__ == '__main__':
    main()
