#!/usr/bin/python2
#-*- encoding:utf-8 -*-

"""
Each character on a computer is assigned a unique code and the
preferred standard is ASCII (American Standard Code for Information
Interchange). For example, uppercase A = 65, asterisk (*) = 42, and
lowercase k = 107.

A modern encryption method is to take a text file, convert the bytes
to ASCII, then XOR each byte with a given value, taken from a secret
key. The advantage with the XOR function is that using the same
encryption key on the cipher text, restores the plain text; for
example, 65 XOR 42 = 107, then 107 XOR 42 = 65.

For unbreakable encryption, the key is the same length as the plain
text message, and the key is made up of random bytes. The user would
keep the encrypted message and the encryption key in different
locations, and without both "halves", it is impossible to decrypt the
message.

Unfortunately, this method is impractical for most users, so the
modified method is to use a password as a key. If the password is
shorter than the message, which is likely, the key is repeated
cyclically throughout the message. The balance for this method is
using a sufficiently long password key for security, but short enough
to be memorable.

Your task has been made easy, as the encryption key consists of three
lower case characters. Using cipher.txt (right click and 'Save
Link/Target As...'), a file containing the encrypted ASCII codes, and
the knowledge that the plain text must contain common English words,
decrypt the message and find the sum of the ASCII values in the
original text.
"""

import euler

english_words = set()
def is_english(text):
    total_words = 0.0
    words_in_dict = 0.0
    for word in text.split(' '):
        total_words += 1
        if word.upper() in english_words:
            words_in_dict += 1
    return words_in_dict/total_words > 0.15

def decrypt(cyphertext,key):
    plaintext = ''
    for i in range(len(cyphertext)):
        plaintext += chr(ord(cyphertext[i]) ^ ord(key[i%3]))

    return plaintext

def main():
    t = euler.read_url('https://projecteuler.net/project/resources/p059_cipher.txt')
    cyphertext = ''.join([chr(int(n)) for n in t.split(',') if n])
    
    with euler.TimeWrapper():
        with open('/usr/share/dict/words','r') as f:
            for line in f:
                english_words.add(line.strip().upper())
        for char1 in range(0x61,0x7B):
            char1 = chr(char1)
            for char2 in range(0x61,0x7B):
                char2 = chr(char2)
                for char3 in range(0x61,0x7B):
                    char3 = chr(char3)
                    plaintext = decrypt(cyphertext,char1+char2+char3)
                    if is_english(plaintext):
                        #print plaintext
                        print sum([ord(c) for c in plaintext])
                        return

if __name__ == '__main__':
    main()
