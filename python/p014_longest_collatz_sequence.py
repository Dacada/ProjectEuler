#!/usr/bin/python2
#-*- encoding:utf-8 -*-

"""
The following iterative sequence is defined for the set of
positive integers:

n -> n/2 (n is even)
n -> 3n + 1 (n is odd)

Using the rule above and starting with 13, we generate the following
sequence:

13 -> 40 -> 20 -> 10 -> 5 -> 16 -> 8 -> 4 -> 2 -> 1

It can be seen that this sequence (starting at 13 and finishing at 1)
contains 10 terms. Although it has not been proved yet (Collatz
Problem), it is thought that all starting numbers finish at 1.

Which starting number, under one million, produces the longest chain?

NOTE: Once the chain starts the terms are allowed to go above one
million.
"""

import euler

class Collatz:
    def __init__(self):
        self._tried = {1:0}
    def length(self,n):
        loops = 0
        next = n
        
        while next not in self._tried or next != 1:
            next = next/2 if next%2==0 else 3*next+1
            loops += 1
            
        try:
            result = loops + self._tried[next]
        except KeyError:
            result = loops
            
        self._tried[n] = result
        return result

def main():
    with euler.TimeWrapper():
        col = Collatz()
        
        result = 0
        max_len = 0
        for number in xrange(2,1000000):
            l = col.length(number)
            if l > max_len:
                max_len = l
                result = number

        print result

if __name__ == '__main__':
    main()
