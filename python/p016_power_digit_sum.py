#!/usr/bin/python2
#-*- encoding:utf-8 -*-

"""
2**15 = 32768 and the sum of its digits is 3 + 2 + 7 + 6 + 8 = 26.

What is the sum of the digits of the number 2**1000?
"""

import euler

def main():
    with euler.TimeWrapper():
        result = sum([int(n) for n in str(2**1000)])
        print result

if __name__ == '__main__':
    main()
