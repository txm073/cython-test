#include <pybind11/pybind11.h>

namespace py = pybind11;

int add(int a, int b) {
    return a + b;
}

float e = 2.718281828459045;

PYBIND11_MODULE(cppmath, module) {
    module.doc() = "C++ math module using PyBind11 to create a shared interface";
    module.def("add", &add, "A function that adds 2 numbers", py::arg("a"), py::arg("b"));
    module.attr("e") = e;
}