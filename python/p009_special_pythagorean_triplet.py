#!/usr/bin/python2
#-*- encoding:utf-8 -*-

"""
A Pythagorean triplet is a set of three natural numbers, a < b < c,
for which,

a**2 + b**2 = c**2

For example, 3**2 + 4**2 = 9 + 16 = 25 = 5**2

There exists exactly one Pythagorean triplet for which a + b + c =
1000. Find the product abc.
"""

import euler
import math
import itertools

def main():
    s = 1000
    with euler.TimeWrapper():
        done = False
        s2 = s/2
        mlimit = int(math.ceil(math.sqrt(s2)))
        for m in xrange(2,mlimit):
            if s2 % m == 0:
                sm = s2/m
                while sm % 2 == 0:
                    sm /= 2
                if m % 2 == 1:
                    k = m+2
                else:
                    k = m+1
                while k < 2*m and k <= sm:
                    if sm % k == 0 and euler.gcd(k,m) == 1:
                        d = s2/(k*m)
                        n = k-m
                        a = d*(m*m-n*n)
                        b = 2*d*m*n
                        c = d*(m*m+n*n)
                        done = True
                        break
                    k = k+2
            if done:
                break
        result = a*b*c
        print result
        

if __name__ == '__main__':
    main()
