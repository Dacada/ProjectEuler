#!/usr/bin/python2
#-*- encoding:utf-8 -*-

"""
Take the number 192 and multiply it by each of 1, 2, and 3:

192 x 1 = 192
192 x 2 = 384
192 x 3 = 576

By concatenating each product we get the 1 to 9 pandigital,
192384576. We will call 192384576 the concatenated product of 192 and
(1,2,3)

The same can be achieved by starting with 9 and multiplying by 1, 2,
3, 4, and 5, giving the pandigital, 918273645, which is the
concatenated product of 9 and (1,2,3,4,5).

What is the largest 1 to 9 pandigital 9-digit number that can be
formed as the concatenated product of an integer with (1,2, ... , n)
where n > 1?
"""

import euler

def mult(n,l):
    r = ""
    for i in l:
        r += str(n*i)
    return int(r)

def is_pandigital(n):
    if len(str(n)) != 9:
        return False
    return all( [str(i) in str(n) for i in range(1,10)] )

def main():
    with euler.TimeWrapper():
        result = 0
        for n in range(2,9+1):
            for i in range(2,456789):
                r = mult(i,range(1,n+1))
                if r > result and is_pandigital(r):
                    print "mult({0}, {1}) = {2}".format(i, n, r)
                    result = r
        print result

if __name__ == '__main__':
    main()
