#!/usr/bin/python2
#-*- encoding:utf-8 -*-

"""
The fraction 49/98 is a curious fraction, as an inexperienced
mathematician in attempting to simplify it may incorrectly believe
that 49/98 = 4/8, which is correct, is obtained by cancelling the 9s.

We shall consider fractions like, 30/50 = 3/5, to be trivial examples.

There are exactly four non-trivial examples of this type of fraction,
less than one in value, and containing two digits in the numerator and
denominator.

If the product of these four fractions is given in its lowest common
terms, find the value of the denominator.
"""

import fractions
import euler

def share_digit(a,b):
    for d1 in str(a):
        for d2 in str(b):
            if d1 == d2:
                return True
    return False

def remove_common(a,b):
    a = str(a)
    b = str(b)

    if a[0] == b[0]:
        return int(a[1]),int(b[1])
    if a[0] == b[1]:
        return int(a[1]),int(b[0])
    if a[1] == b[0]:
        return int(a[0]),int(b[1])
    if a[1] == b[1]:
        return int(a[0]),int(b[0])

def main():
    with euler.TimeWrapper():
        found = []
        for i in range(10,99):
            l = []
            for j in range(i+1,100):
                if str(i)[1] == "0" and str(j)[1] == "0":
                    continue
                if not share_digit(i,j):
                    continue
                a,b = remove_common(i,j)
                if b == 0:
                    continue
                if float(i)/float(j) == float(a)/float(b):
                    found.append(fractions.Fraction(i,j))
            
        assert len(found) == 4
        result = fractions.Fraction(1,1)
        for f in found:
            result *= f

        print result.denominator

if __name__ == '__main__':
    main()
