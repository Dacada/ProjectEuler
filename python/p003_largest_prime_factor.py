#!/usr/bin/python2
#-*- encoding:utf-8 -*-

"""
The prime factors of 13195 are 5, 7, 13 and 29.

What is the largest prime factor of the number 600851475143?
"""

import euler

def main():
    with euler.TimeWrapper():
        result = max(euler.factorize(600851475143))
        print result

if __name__ == '__main__':
    main()
