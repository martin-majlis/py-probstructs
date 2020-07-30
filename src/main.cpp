#include <pybind11/pybind11.h>
#include "probstructs/probstructs.h"

int add(int i, int j) {
    return i + j;
}

namespace py = pybind11;

PYBIND11_MODULE(probstructs, m) {
    m.doc() = R"pbdoc(
        Pybind11 example plugin
        -----------------------

        .. currentmodule:: probstructs

        .. autosummary::
           :toctree: _generate

           add
           subtract
    )pbdoc";

    m.def("add", &add, R"pbdoc(
        Add two numbers

        Some other explanation about the add function.
    )pbdoc");

    m.def("subtract", [](int i, int j) { return i - j; }, R"pbdoc(
        Subtract two numbers

        Some other explanation about the subtract function.
    )pbdoc");

    py::class_<Hash> hash_class(m, "Hash");
    hash_class
        .def(py::init<uint32_t>())
        .def("hash", &Hash::hash);

    py::class_<CountMinSketch<uint32_t>> cmsketch_class(m, "CountMinSketch");
    cmsketch_class
        .def(py::init<uint32_t, uint8_t>())
        .def("inc", &CountMinSketch<uint32_t>::inc)
        .def("get", &CountMinSketch<uint32_t>::get)
    ;

    py::class_<ExponentialHistorgram<uint32_t>> eh_class(m, "ExponentialHistorgram");
    eh_class
        .def(py::init<uint32_t>())
        .def("inc", &ExponentialHistorgram<uint32_t>::inc)
        .def("get", &ExponentialHistorgram<uint32_t>::get)
    ;

    py::class_<ExponentialCountMinSketch<uint32_t>> ecmsketch_class(m, "ExponentialCountMinSketch");
    ecmsketch_class
        .def(py::init<uint32_t, uint8_t, uint32_t>())
        .def("inc", &ExponentialCountMinSketch<uint32_t>::inc)
        .def("get", &ExponentialCountMinSketch<uint32_t>::get)
        ;

#ifdef VERSION_INFO
    m.attr("__version__") = VERSION_INFO;
#else
    m.attr("__version__") = "dev";
#endif
}
