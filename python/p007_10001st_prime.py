#!/usr/bin/python2
#-*- encoding:utf-8 -*-

import itertools

"""
By listing the first six prime numbers: 2, 3, 5, 7, 11, and 13, we
can see that the 6th prime is 13.

What is the 10,001st prime number?
"""

import euler

def main():
    with euler.TimeWrapper():
        n = 1
        for prime in itertools.count(3, 2):
            if euler.is_prime(prime):
                n += 1
                if n == 10001:
                    break

        print prime

if __name__ == '__main__':
    main()
