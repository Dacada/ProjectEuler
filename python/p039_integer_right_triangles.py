#!/usr/bin/python
#-*- encoding:utf-8 -*-

"""
If p is the perimeter of a right angle triangle with integral
length sides, {a,b,c}, there are exactly three solutions for p = 120.

{20,48,52}, {24,45,51}, {30,40,50}

For which value of p <= 1000, is the number of solutions maximised?
"""

import copy
import numpy as np
import euler

A = np.matrix("1 -2 2; 2 -1 2; 2 -2 3")
B = np.matrix("1 2 2; 2 1 2; 2 2 3")
C = np.matrix("-1 2 2; -2 1 2; -2 2 3")
p_limit = 1000

def get_tree(root_triplet):
    if root_triplet.sum() > p_limit:
        return []
    
    A_branch_root = A * root_triplet
    B_branch_root = B * root_triplet
    C_branch_root = C * root_triplet

    #I don't like how this looks but flatten will make it all fine...
    return [root_triplet,get_tree(A_branch_root), get_tree(B_branch_root), get_tree(C_branch_root)]


def flatten(l):
    r = []
    for x in l:
        if type(x) is list:
            r += flatten(x)
        else:
            r.append(x)
    return r


def main():
    with euler.TimeWrapper():
        results = {}
        for i in range(1,1001):
            results[i] = 0
        triplets = flatten(get_tree(np.matrix("3;4;5")))
    
        for triplet in triplets:
            n = 1
            s = 0
            temp = triplet * n
            s = temp.sum()
            while s <= p_limit:
                results[s] += 1
                n += 1
                temp = triplet * n
                s = temp.sum()

        result = 0,0
        for i in results:
            if results[i] > result[0]:
                result = results[i],i
        print result[1]

if __name__ == '__main__':
    main()
