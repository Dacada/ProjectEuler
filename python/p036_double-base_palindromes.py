#!/usr/bin/python2

"""
The decimal number, 585 = 10010010012 (binary), is palindromic in
both bases.

Find the sum of all numbers, less than one million, which are
palindromic in base 10 and base 2.

(Please note that the palindromic number, in either base, may not
include leading zeros.)
"""

import euler

def palindromic(s):
    if len(s) % 2 == 0:
        return s[:len(s)/2] == s[len(s)/2:][::-1]
    else:
        return s[:len(s)/2] == s[len(s)/2+1:][::-1]

def main():
    with euler.TimeWrapper():
        l = []
        for i in range(1000000):
            if palindromic(str(i)) and palindromic(bin(i)[2:]):
                l.append(i)
        result = sum(l)
        print result

if __name__ == '__main__':
    main()
