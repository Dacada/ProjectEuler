#!/usr/bin/python2

"""
The nth term of the sequence of triangle numbers is given by, tn =
(1/2)*n*(n+1); so the first ten triangle numbers are:

1, 3, 6, 10, 15, 21, 28, 36, 45, 55, ...

By converting each letter in a word to a number corresponding to its
alphabetical position and adding these values we form a word
value. For example, the word value for SKY is 19 + 11 + 25 = 55 =
t10. If the word value is a triangle number then we shall call the
word a triangle word.

Using words.txt (right click and 'Save Link/Target As...'), a 16K text
file containing nearly two-thousand common English words, how many are
triangle words?
"""

import euler

def get_value(word):
    return sum([ ord(c)-64 for c in word ])

def get_all_triangles_until(n):
    r = []
    t = 1
    i = 2
    while t <= n:
        r.append(t)
        t = i*(i+1)/2
        i+=1
    return r

def main():
    with euler.TimeWrapper():
        t = euler.read_url('https://projecteuler.net/project/resources/p042_words.txt')
        words = [ w[1:][:-1] for w in t.split(',') ]

        triangle_numbers = set(get_all_triangles_until(get_value('Z'*max([ len(w) for w in words ]))))

        result = 0
        for word in words:
            if get_value(word) in triangle_numbers:
                result += 1
        print result

if __name__ == '__main__':
    main()
