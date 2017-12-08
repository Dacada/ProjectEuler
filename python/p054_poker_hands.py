#!/usr/bin/python2
#-*- encoding:utf-8 -*-

"""
In the card game poker, a hand consists of five cards and are
ranked, from lowest to highest, in the following way:

* High Card: Highest value card.

* One Pair: Two cards of the same value.

* Two Pairs: Two different pairs.

* Three of a Kind: Three cards of the same value.

* Straight: All cards are consecutive values.

* Flush: All cards of the same suit.

* Full House: Three of a kind and a pair.

* Four of a Kind: Four cards of the same value.

* Straight Flush: All cards are consecutive values of same suit.

* Royal Flush: Ten, Jack, Queen, King, Ace, in same suit.

The cards are valued in the order:

2, 3, 4, 5, 6, 7, 8, 9, 10, Jack, Queen, King, Ace.

If two players have the same ranked hands then the rank made up of the
highest value wins; for example, a pair of eights beats a pair of
fives (see example 1 below). But if two ranks tie, for example, both
players have a pair of queens, then highest cards in each hand are
compared (see example 4 below); if the highest cards tie then the next
highest cards are compared, and so on.

Consider the following five hands dealt to two players:

Hand            Player 1            Player 2            Winner
 1           5H 5C 6S 7S KD      2C 3S 8S 8D TD         Player 2
             Pair of Fives       Pair of Eights

 2           5D 8C 9S JS AC      2C 5C 7D 8S QH         Player 1
             Highest card Ace    Highest card Queen

 3           2D 9C AS AH AC      3D 6D 7D TD QD         Player 2
             Three Aces          Flush with Diamonds

 4           4D 6S 9H QH QC      3D 6D 7H QD QS         Player 1
             Pair of Queens      Pair of Queens
             Highest card Nine   Highest card Seven

 5           2H 2D 4C 4D 4S      3C 3D 3S 9S 9D         Player 1
             Full House          Full House
             With Three Fours    With Three Threes

The file, poker.txt, contains one-thousand random hands dealt to two
players. Each line of the file contains ten cards (separated by a
single space): the first five are Player 1's cards and the last five
are Player 2's cards. You can assume that all hands are valid (no
invalid characters or repeated cards), each player's hand is in no
specific order, and in each hand there is a clear winner.

How many hands does Player 1 win?
"""

import euler

def get_ranks(hand):
    """
    High Card: 0
    One Pair: 1
    Two Pairs: 2
    Three of a Kind: 3
    Straight: 4
    Flush: 5
    Full House: 6
    Four of a Kind: 7
    Straight Flush: 8
    Royal Flush: 9
    
    2: 0
    3: 1
    4: 2
    5: 3
    6: 4
    7: 5
    8: 6
    9: 7
    10: 8
    Jack: 9
    Queen: 10
    King: 11
    Ace: 12

    Each hand will be: (best_rank, card_number, (highest, cards))
    """
    could_be_straight = False
    could_be_flush = False
    handnums = sorted([int(hand[n][0].replace('T','10').replace('J','11').replace('Q','12').replace('K','13').replace('A','14')) for n in range(5)])
    if handnums[4]-handnums[3] == handnums[3]-handnums[2] == handnums[2]-handnums[1] == handnums[1]-handnums[0] == 1:
        could_be_straight = True
    #if all same suit
    if len(set([hand[n][1] for n in range(5)])) == 1:
        #royal flush
        if set(handnums) == set(range(10,15)):
            return (9,12,(12,))
        #straight flush
        if could_be_straight:
            return (8,max(handnums)-2,(max(handnums)-2,))
        could_be_flush = True

    #four of a kind or full house
    if len(set(handnums)) == 2:
        num_a,num_b = set(handnums)
        count_a = handnums.count(num_a)
        count_b = handnums.count(num_b)
        num_a -= 2
        num_b -= 2
        if count_a == 4 or count_b == 4: #four of a kind
            if count_a == 4:
                return (7,num_a,(num_b,))
            else:
                return (7,num_b,(num_a,))
        elif count_a == 3 or count_b == 3: #full house
            if count_a == 3:
                return (6,num_a,(num_b,))
            else:
                return (6,num_b,(num_a,))

    #If we get this far it could be a flush
    if could_be_flush:
        return (5,max(handnums)-2,(max(handnums)-2,))

    #if we get this far it could be a straight
    if could_be_straight:
        return (4,max(handnums)-2,(max(handnums)-2,))

    #three of a kind or two pairs
    if len(set(handnums)) == 3:
        num_a,num_b,num_c = set(handnums)
        count_a = handnums.count(num_a)
        count_b = handnums.count(num_b)
        count_c = handnums.count(num_c)
        num_a -= 2
        num_b -= 2
        num_c -= 2
        #three of a kind
        if count_a == 3 or count_b == 3 or count_c == 3:
            if count_a == 3:
                return (3,num_a,tuple(sorted((num_b,num_c),reverse=True)))
            elif count_b == 3:
                return (3,num_b,tuple(sorted((num_a,num_c),reverse=True)))
            else:
                return (3,num_c,tuple(sorted((num_b,num_c),reverse=True)))
        #two pairs
        elif count_a == 1 or count_b == 1 or count_c == 1:
            if count_a == 1:
                return (2,max(num_b,num_c),(num_a,min(num_b,num_c)))
            elif count_b == 1:
                return (2,max(num_a,num_c),(num_b,min(num_a,num_c)))
            else:
                return (2,max(num_a,num_b),(num_c,min(num_a,num_b)))

    #one pair
    if len(set(handnums)) == 4:
        num_a,num_b,num_c,num_d = set(handnums)
        count_a = handnums.count(num_a)
        count_b = handnums.count(num_b)
        count_c = handnums.count(num_c)
        count_d = handnums.count(num_d)
        num_a -= 2
        num_b -= 2
        num_c -= 2
        num_d -= 2
        if count_a == 2:
            return (1,num_a,tuple(sorted((num_b,num_c,num_d),reverse=True)))
        elif count_b == 2:
            return (1,num_b,tuple(sorted((num_a,num_c,num_d),reverse=True)))
        elif count_c == 2:
            return (1,num_c,tuple(sorted((num_a,num_b,num_d),reverse=True)))
        elif count_d == 2:
            return (1,num_d,tuple(sorted((num_a,num_b,num_c),reverse=True)))

    #highest card
    return (0,max(handnums)-2,tuple(sorted([n-2 for n in handnums],reverse=True)))
        
def get_winner(hand1, hand2):
    ranks1 = get_ranks(hand1)
    ranks2 = get_ranks(hand2)

    if ranks1[0] > ranks2[0]:
        return 1
    elif ranks2[0] > ranks1[0]:
        return 2
    
    if ranks1[1] > ranks2[1]:
        return 1
    elif ranks2[1] > ranks1[1]:
        return 2
    
    for i in range(len(ranks1[2])):
        if ranks1[2][i] > ranks2[2][i]:
            return 1
        elif ranks2[2][i] > ranks1[2][i]:
            return 2
        
    raise Exception("Should never happen")

def main():
    text = euler.read_url('https://projecteuler.net/project/resources/p054_poker.txt')
    hands = set([ (tuple(h.split()[:5]), tuple(h.split()[5:])) for h in text.split('\n') if h])
    del text
    
    with euler.TimeWrapper():
        result = 0
        for hand in hands:
            w = get_winner(*hand)
            if w == 1:
                result += 1
        print result

if __name__ == '__main__':
    main()
