#!/usr/bin/python2
#-*- encoding:utf-8 -*-

"""Starting with the number 1 and moving to the right in a clockwise
direction a 5 by 5 spiral is formed as follows:

    21 22 23 24 25
    20  7  8  9 10
    19  6  1  2 11
    18  5  4  3 12
    17 16 15 14 13

It can be verified that the sum of the numbers on the diagonals is
101.

What is the sum of the numbers on the diagonals in a 1001 by 1001
spiral formed in the same way?


We can find the equations followed by the numbers in each of the four
diagonals:

They should be...

     43 44 45 46 47 48 49
     42 21 22 23 24 25 26
     41 20  7  8  9 10 27
     40 19  6  1  2 11 28
     39 18  5  4  3 12 29
     38 17 16 15 14 13 30
     37 36 35 34 33 32 31

nw -> 43
ne -> 49
sw -> 37
se -> 31

nw:
 1 = a*1**2 + b*1 + c
 7 = a*2**2 + b*2 + c
 21 = a*3**2 + b*3 + c
 equation: n = 4*r**2 - 6*r + 3

ne:
 1 = a*1**2 + b*1 + c
 9 = a*2**2 + b*2 + c
 25 = a*3**2 + b*3 + c
 equation: n = 4*r**2 - 4*r + 1

sw:
 1 = a*1**2 + b*1 + c
 5 = a*2**2 + b*2 + c
 17 = a*3**2 + b*3 + c
 equation n = 4*r**2 - 8*r + 5

se:
 1 = a*1**2 + b*1 + c
 3 = a*2**2 + b*2 + c
 13 = a*3**2 + b*3 + c
 equation n = 4*r**2 - 10*r + 7

These take the row number because I'm stupid. But the square size can
be taken from the row number.

1 -> 1
3 -> 2
5 -> 3
n -> (n+1)/2
7 -> (7+1)/2=4
1001 -> (1001+1)/2

So we have to compute each equation from 2 to (1001+1)/2, then add it
all together and add 1.
"""

import euler

def main():
    with euler.TimeWrapper():
        result = 1
        for r in xrange(2,(1001+1)/2+1):
            result += 4*r**2 - 6*r + 3
            result += 4*r**2 - 4*r + 1
            result += 4*r**2 - 8*r + 5
            result += 4*r**2 - 10*r + 7
        print result

if __name__ == '__main__':
    main()
