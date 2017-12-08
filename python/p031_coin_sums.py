#!/usr/bin/python2
#-*- encoding:utf-8 -*-

"""
In England the currency is made up of pound, Â£, and pence, p, and
there are eight coins in general circulation:

1p, 2p, 5p, 10p, 20p, 50p, Â£1 (100p) and Â£2 (200p).
It is possible to make Â£2 in the following way:

1xÂ£1 + x50p + 2x20p + 1x5p + 1x2p + 31p
How many different ways can Â£2 be made using any number of coins?


Solution:
https://andrew.neitsch.ca/publications/m496pres1.nb.pdf
"""

import euler

def ways_change(value, coins):
    if coins < 1 or value < 0:
        return 0
    elif value == 0:
        return 1
    else:
        coin = [1,2,5,10,20,50,100,200][coins-1]
        return ways_change(value, coins-1) +\
               ways_change(value-coin, coins)

def main():
    with euler.TimeWrapper():
        result = ways_change(200,8)
        print result

if __name__ == '__main__':
    main()
