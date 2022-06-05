#include <pybind11/pybind11.h>

namespace py = pybind11;

int add(int a, int b) {
    return a + b;
}

PYBIND11_MODULE(cppmath, module) {
    module.doc() = "C++ math module using PyBind11 to create a shared interface";
    module.def("add", &add, "A function that adds 2 numbers", py::arg("a"), py::arg("b"));
}