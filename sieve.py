import cppmath
import time
import pickle

def timed(fn):
    def call(*args, **kwargs):
        start = time.perf_counter()
        value = fn(*args, **kwargs)
        return value, time.perf_counter() - start
    return call

@timed
def segmented_sieve(n):
    primes = [2, 3, 5, 7]
    start_idx = 1
    while True:   
        p, q = primes[start_idx], primes[start_idx + 1]
        multiples = primes[:start_idx + 1]
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
        start_idx += 1
    return primes

@timed
def segmented_sieve_cpp(n):
    return cppmath.segmented_sieve(int(n))


if __name__ == "__main__":
    n = 1e+9
    print(segmented_sieve_cpp(n)[1])