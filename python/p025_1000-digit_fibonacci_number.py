#!/usr/bin/python2
#-*- encoding:utf-8 -*-

"""
The Fibonacci sequence is defined by the recurrence relation:

F_n = F_{n-1} + F_{n-2} where F_1 = F_2 = 1

Hence the first 12 terms will be:

F_1= 1
F_2 = 1
F_3 = 2
F_4 = 3
F_5 = 5
F_6 = 8
F_7 = 13
F_8 = 21
F_9 = 34
F_10 = 55
F_11 = 89
F_12 = 144

The 12th term, F_12, is the first term to contain three digits.

What is the index of the first term in the Fibonacci sequence to
contain 1000 digits?
"""

import euler

def fibonacci():
    previous = 1
    previous2 = 1
    yield 1
    yield 1
    while True:
        current = previous+previous2
        yield current
        
        previous2 = previous
        previous = current

def main():
    with euler.TimeWrapper():
        for i,n in enumerate(fibonacci()):
            if len(str(n)) == 1000:
                break
        result = i+1
        print result

if __name__ == '__main__':
    main()
