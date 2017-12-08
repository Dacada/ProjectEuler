#!/usr/bin/python2
#-*- encoding:utf-8 -*-

"""
Starting in the top left corner of a 2x2 grid, and only being able
to move to the right and down, there are exactly 6 routes to the
bottom right corner.

...

How many such routes are there through a 20x20 grid?
"""

import euler

memory = {}
def nroutes(x,y):
    if x==0 and y==0:
        return 1
    else:
        try:
            return memory[(x,y)]
        except KeyError:
            if x == 0:
                result = nroutes(x,y-1)
            elif y == 0:
                result = nroutes(x-1,y)
            else:
                result = nroutes(x-1,y) + nroutes(x,y-1)
            memory[(x,y)] = result
            return result

def main():
    with euler.TimeWrapper():
        result = nroutes(20,20)
        print result

if __name__ == '__main__':
    main()
