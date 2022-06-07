import time
_start = time.time()

#import prime_sieve
import sys
import random
import pickle

def sieve(n):
    primes = []
    marker = [1] * n
    for i in range(n):
        if marker[i]:
            if i + 2 < n:
                primes.append(i + 2)
            for j in range(i, n, i + 2):
                marker[j] = 0
    return primes

def segmented_sieve(n, step_target=1):
    primes = [2, 3, 5, 7]
    start_idx = 1
    step = 1
    while True:   
        step = min(step_target, len(primes) - 1 - start_idx)
        p, q = primes[start_idx], primes[start_idx + step]
        multiples = primes[:start_idx + step]
        start, end = p * p, q * q - 1
        length = end - start + 1
        
        marker = [1 for i in range(length)]
        marker[0] = 0

        for m in multiples:
            offset = m * (start // m) + (0 if start % m == 0 else m) - start
            for i in range(0, length, m):
                try:
                    marker[i + offset] = 0
                except IndexError:
                    pass
        
        for i in range(length):
            if marker[i] != 1:
                continue
            if start + i < n:
                primes.append(start + i)
            else:
                return primes
        start_idx += step
    return primes

primes = segmented_sieve(1e+7)
print(f"Found {len(primes)} primes")
with open("output.pkl", "wb") as f:
    pickle.dump(primes, f)
print(f"Finished in {time.time() - _start:2f}s")