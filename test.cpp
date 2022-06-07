#include <cmath>
#include <vector>
#include <string>
#include <iostream>

template <typename T> void printVector(std::vector<T> vec, std::string sep = ", ", std::string end = "\n") {
    for (auto elem : vec) {
        std::cout << elem << sep;
    }
    std::cout << "\n";
}


template <typename T> std::vector<T> slice(std::vector<T> &vec, int start, int end) {
    auto first = vec.begin() + start;
    auto last = vec.begin() + end + 1;
    std::vector<T> slicedVector(first, last);
    return slicedVector;
}

std::vector<double> segmentedSieve(double n) {
    std::vector<double> primes = {2, 3, 5, 7}, multiples;
    int startIndex = 1, step = 1;
    while (true) {
        double p = primes[startIndex], q = primes[startIndex + 1];
        double start = p * p;
        double length = q * q - start;
        multiples = slice(primes, 0, startIndex);
        std::vector<bool> marker = {};
        for (int i = 0; i < length; ++i) {
            marker.push_back(true);
        }
        marker[0] = false;
        for (double m : multiples) {
            double offset = m * std::floor(start / m) + (std::fmod(start, m) == 0 ? 0 : m) - start;
            for (int i = 0; i < length; i += m) {
                if (i + offset < marker.size()) {
                    marker[i + offset] = false;
                } 
            }
        }
        for (int i = 0; i < length; ++i) {
            if (!marker[i]) {
                continue;
            }
            if (start + i < n) {
                primes.push_back(start + i);
            } else {
                return primes;
            }
        }
        startIndex += step;
    }
    return primes;
}

int main(const int argc, const char* argv[]) {
    double n = 100;
    std::vector<double> primes = segmentedSieve(n);
    printVector(primes);
    std::vector<int> vec = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    return 0;
}