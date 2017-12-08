import time
import math
import pickle
import itertools
import subprocess32
import requests

class TimeWrapper(object):
    """
    Times the code running inside a with, then prints when exiting the with.
    """
    def __enter__(self):
        self._time_started = time.clock()
    def __exit__(self, type, value, traceback):
        time_passed = time.clock() - self._time_started
        print "{0:.6f}".format(time_passed)
        return False

class PrimesRepeat(object):
    """
    Generates primes in such a way that it can be called multiple
    times with different values and only generate new primes when
    needed.
    """
    def __init__(self):
        self.l = [2]
        self.last = 2
        
    def is_prime(self,n):
        if n == self.last:
            return True
        elif n < self.last:
            return n in self.l
        else:
            for i in itertools.count(self.last+1):
                if is_prime(i):
                    self.l.append(i)
                    #End the loop if i >= n
                    if i == n:
                        self.last = i
                        return True
                    elif i > n:
                        self.last = i
                        return False
                    
    def get_primes_until(self,n):
        self.is_prime(n) #Generate primes until past n if needed
        for i in self.l:
            #End the loop before i gets >= n
            if i >= n:
                return
            yield i

def factorize(n):
    """
    Returns a tuple with all the prime factors of a given number.
    """
    call_output = subprocess32.check_output(['factor',str(n)])
    number,factors = [part.strip() for part in call_output.split(':')]
    if not factors:
        return ()
    factors_tuple = tuple([int(number.strip()) for number in factors.split(' ')])
    return factors_tuple

def is_prime(n):
    """
    Return whether a single number is prime.
    """
    limit = int( math.ceil( math.sqrt(n) ) )
    for i in xrange(2,limit+1):
        if n % i == 0:
            return False
    return True

def gcd(a,b):
    """
    Return the greatest common divisor of two numbers.
    """
    if b == 0:
        return a
    else:
        return gcd(b,a%b)

def primes_sieve(limit):
    """
    Generate primes using a sieve, from 2 to a given limit.
    """
    sieve = [True]*limit
    sieve[0] = False
    sieve[1] = False
    for i in xrange(2,limit):
        if sieve[i]:
            yield i
            for j in xrange(i*2, limit, i):
                sieve[j] = False

def read_url(url):
    """
    Return the raw text from an url.
    """
    r = requests.get(url)
    return r.text

def sum_divisors(n):
    """
    Return the sum of the porper divisors of n
    """
    factors = factorize(n)

    result = 1
    for p in set(factors):
        a = factors.count(p)
        result *= sum([p**ai for ai in range(a+1)])
    
    return result-n
