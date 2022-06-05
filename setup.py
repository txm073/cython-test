from setuptools import setup
from pybind11.setup_helpers import Pybind11Extension

ext_modules = [
    Pybind11Extension("cppmath", ["maths.cpp"])
]

setup(name="cppmath", ext_modules=ext_modules)