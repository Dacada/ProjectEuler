#!/usr/bin/python2
#-*- encoding:utf-8 -*-

"""
The number, 1406357289, is a 0 to 9 pandigital number because it
is made up of each of the digits 0 to 9 in some order, but it also has
a rather interesting sub-string divisibility property.

Let d1 be the 1st digit, d2 be the 2nd digit, and so on. In this way,
we note the following:

d_2 d_3 d_4 = 406 is divisible by 2
d_3 d_4 d_5 = 063 is divisible by 3
d_4 d_5 d_6 = 635 is divisible by 5
d_5 d_6 d_7 = 357 is divisible by 7
d_6 d_7 d_8 = 572 is divisible by 11
d_7 d_8 d_9 = 728 is divisible by 13
d_8 d_9 d_10 = 289 is divisible by 17

Find the sum of all 0 to 9 pandigital numbers with this property.
"""

import itertools
import euler

def main():
    with euler.TimeWrapper():
        all_numbers = [ "".join(number) for number in itertools.permutations([str(k) for k in range(10)],10) ]

        result = 0
        for number in all_numbers:
            b1 = int(number[1:4]) % 2 == 0
            b2 = int(number[2:5]) % 3 == 0
            b3 = int(number[3:6]) % 5 == 0
            b4 = int(number[4:7]) % 7 == 0
            b5 = int(number[5:8]) % 11 == 0
            b6 = int(number[6:9]) % 13 == 0
            b7 = int(number[7:10]) % 17 == 0
            if all([b1,b2,b3,b4,b5,b6,b7]):
                result += int(number)
        print result

if __name__ == '__main__':
    main()
