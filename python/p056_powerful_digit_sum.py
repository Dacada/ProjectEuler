#!/usr/bin/python2
#-*- encoding:utf-8 -*-

"""
A googol (10**100) is a massive number: one followed by one-hundred
zeros; 100**100 is almost unimaginably large: one followed by
two-hundred zeros. Despite their size, the sum of the digits in each
number is only 1.

Considering natural numbers of the form, a**b, where a, b < 100, what
is the maximum digital sum?
"""

import euler

def main():
    with euler.TimeWrapper():
        result = 0
        for a in range(100):
            for b in range(100):
                s = sum([int(n) for n in str(a**b)])
                if s > result:
                    result = s
        print result

if __name__ == '__main__':
    main()
