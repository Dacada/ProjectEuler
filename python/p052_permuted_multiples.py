#!/usr/bin/python2
#-*- encoding:utf-8 -*-

"""
It can be seen that the number, 125874, and its double, 251748,
contain exactly the same digits, but in a different order.

Find the smallest positive integer, x, such that 2x, 3x, 4x, 5x, and
6x, contain the same digits.
"""

import itertools
import euler

def main():
    with euler.TimeWrapper():
        for n in itertools.count(1):
            if set(str(1*n)) ==\
               set(str(2*n)) ==\
               set(str(3*n)) ==\
               set(str(4*n)) ==\
               set(str(5*n)) ==\
               set(str(6*n)):
                print n
                return

if __name__ == '__main__':
    main()
