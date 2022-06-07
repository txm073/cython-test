import time
_start = time.time()

import prime_sieve
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

def segmented_sieve(n, step_target=100):
    primes = [2, 3, 5, 7]
    start_idx = 1
    count = 1
    step = 1
    while True:   
        step = min(step_target, len(primes) - 1 - start_idx)
        p, q = primes[start_idx], primes[start_idx + step]
        multiples = primes[:start_idx + 1]
        start, end = p * p, q * q - 1
        length = end - start + 1
        segment = [i for i in range(start, end)]
        if "-v" in sys.argv:
            print(f"Segment size: {length}", end="\r")
        marker = [1 for i in range(length)]
        marker[0] = 0

        for m in multiples:
            offset = m * (segment[0] // m) + (0 if segment[0] % m == 0 else m) - segment[0]
            for i in range(0, length, m):
                try:
                    marker[i + offset] = 0
                except IndexError:
                    pass
        
        primes_in_segment = [segment[i] for i in range(len(segment)) if marker[i] == 1]
        if primes_in_segment[-1] >= n:
            for prime in primes_in_segment:
                if prime < n:
                    primes.append(prime)
            break
        else:
            primes.extend(primes_in_segment)
        start_idx += step
        count += 1
    return primes

primes = segmented_sieve(1e+7)
print(f"Found {len(primes)} primes")
with open("output.pkl", "wb") as f:
    pickle.dump(primes, f)
print(f"Finished in {time.time() - _start:2f}s")