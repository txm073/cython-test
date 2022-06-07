#include <vector>
#include <cmath>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

int add(int a, int b) {
    return a + b;
}

template <typename T> std::vector<T> slice(std::vector<T> &vec, int start, int end) {
    auto first = vec.begin() + start;
    auto last = vec.begin() + end + 1;
    std::vector<T> slicedVector(first, last);
    return slicedVector;
}

std::vector<std::size_t> segmentedSieve(std::size_t n) {
    std::vector<std::size_t> primes = {2, 3, 5, 7}, multiples;
    int startIndex = 1;
    while (true) {
        std::size_t p = primes[startIndex], q = primes[startIndex + 1];
        std::size_t start = p * p;
        std::size_t length = q * q - start;
        multiples = slice(primes, 0, startIndex);
        std::vector<bool> marker = {};
        for (int i = 0; i < length; ++i) {
            marker.push_back(true);
        }
        marker[0] = false;
        for (std::size_t m : multiples) {
            std::size_t offset = m * std::floor(start / m) + (std::fmod(start, m) == 0 ? 0 : m) - start;
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
        startIndex += 1;
    }
    return primes;
}

float e = 2.718281828459045;

PYBIND11_MODULE(cppmath, module) {
    module.doc() = "C++ math module using PyBind11 to create a shared interface";
    module.def("add", &add, "A function that adds 2 numbers", py::arg("a"), py::arg("b"));
    module.def("segmented_sieve", &segmentedSieve, "Find prime numbers up to `n` using the segmented sieve of Erotostaenes", py::arg("n"));

    module.attr("e") = e;
}