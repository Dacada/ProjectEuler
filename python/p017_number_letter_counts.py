#!/usr/bin/python2
#-*- encoding:utf-8 -*-

"""
If the numbers 1 to 5 are written out in words: one, two, three,
four, five, then there are 3 + 3 + 5 + 4 + 4 = 19 letters used in
total.

If all the numbers from 1 to 1000 (one thousand) inclusive were
written out in words, how many letters would be used?

NOTE: Do not count spaces or hyphens. For example, 342 (three hundred
and forty-two) contains 23 letters and 115 (one hundred and fifteen)
contains 20 letters. The use of "and" when writing out numbers is in
compliance with British usage.
"""

import euler

def main():
    with euler.TimeWrapper():
        numbers = {
            0: 'zero',   10: 'ten',
            1: 'one',    11: 'eleven',
            2: 'two',    12: 'twelve',     20: 'twenty',
            3: 'three',  13: 'thirteen',   30: 'thirty',
            4: 'four',   14: 'fourteen',   40: 'forty',
            5: 'five',   15: 'fifteen',    50: 'fifty',
            6: 'six',    16: 'sixteen',    60: 'sixty',
            7: 'seven',  17: 'seventeen',  70: 'seventy',
            8: 'eight',  18: 'eighteen',   80: 'eighty',
            9: 'nine',   19: 'nineteen',   90: 'ninety'
        }

        result = 0

        for hundreds in range(10):
            for tenths in range(10):
                for units in range(10):
                    if hundreds != 0:
                        #print numbers[hundreds], 'hundred',
                        result += len(numbers[hundreds]) + len('hundred')
                        if tenths == 0 and units == 0:
                            #print
                            pass
                        else:
                            #print 'and'
                            result += len('and')

                    if tenths == 1 and units > 0:
                        #print numbers[tenths*10+units]
                        result += len(numbers[tenths*10+units])
                    else:
                        if tenths != 0:
                            #print numbers[tenths*10]
                            result += len(numbers[tenths*10])
                        if units != 0:
                            #print numbers[units]
                            result += len(numbers[units])
                            
                    #print
                    
        #print 'one thousand'
        result += len('onethousand')

        print result

if __name__ == '__main__':
    main()
