#!/usr/bin/python2
#-*- encoding:utf-8 -*-

"""
A palindromic number reads the same both ways. The largest
palindrome made from the product of two 2-digit numbers is 9009 = 91 x
99.

Find the largest palindrome made from the product of two 3-digit numbers.


Palindrome P must be at 6 digits long since 111111=143x777 and 999x999
is also 6 digits long.

P = 100000x + 10000y + 1000z + 100z + 10y + x

P = 100001x + 10010y + 1100z

P = 11(9091x + 910y + 100z)

Therefore one of the two numbers must be divisible by 11
"""

import euler

def is_palindrome(n):
    sn = str(n)
    if len(sn) != 6:
        return False
    else:
        return sn[0] == sn[5] and\
               sn[1] == sn[4] and\
               sn[2] == sn[3]
        

def main():
    with euler.TimeWrapper():
        result = 0
        a = 999 #start from high numbers
        while a >= 100:
            if a % 11 == 0: #one of them must be %11==0, if a is all is normal
                b = 999
                decrease_b = 1 #decrease b normally
            else: #if b is we have to ensure we keep it that way
                b = 990 #largest 3-digit and divisible 11
                decrease_b = 11 #keep b divisible by 11

            while b >= a:
                r = a*b
                if r <= result:
                    break
                elif is_palindrome(r):
                    result = r
                b -= decrease_b 
            a -= 1
        print result

if __name__ == '__main__':
    main()
