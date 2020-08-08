#include <pybind11/pybind11.h>
#include "probstructs/probstructs.h"

namespace py = pybind11;

PYBIND11_MODULE(probstructs, m) {
    using namespace probstructs;

    m.doc() = R"pbdoc(
        Probstructs
        -----------

        .. currentmodule:: probstructs

        .. autosummary::
           :toctree: _generate

           Hash
           CountMinSketch
           ExponentialHistorgram
           ExponentialCountMinSketch

    )pbdoc";

    py::class_<Hash> hash_class(m, "Hash", "Hashing function");
    hash_class
        .def(
            py::init<uint32_t>(),
            "Create hashing function with {seed}.",
            py::arg("seed")
        )
        .def(
            "hash",
            &Hash::hash,
            "Hash {key}.",
            py::arg("key")
        );

    py::class_<CountMinSketch<uint32_t>> cmsketch_class(
        m,
        "CountMinSketch",
        "Count–min sketch (CM sketch) is a probabilistic data structure that serves as a frequency table of events in a stream of data. It uses hash functions to map events to frequencies, but unlike a hash table uses only sub-linear space, at the expense of overcounting some events due to collisions."
    );

    cmsketch_class
        .def(
            py::init<uint32_t, uint8_t>(),
            "Create CM sketch with width {width} and depth {depth}.",
            py::arg("width"),
            py::arg("depth")
        )
        .def(
            "inc",
            &CountMinSketch<uint32_t>::inc,
            "Increase counter for {key} by {delta}.",
            py::arg("key"),
            py::arg("delta")
        )
        .def(
            "get",
            &CountMinSketch<uint32_t>::get,
            "Get count for {key}.",
            py::arg("key")
        )
    ;

    py::class_<ExponentialHistorgram<uint32_t>> eh_class(
        m,
        "ExponentialHistorgram",
        "Exponential histogram (EH) is a probabilistic data structure that serves as a frequency counter for specific elements in the last N elements from stream."
    );
    eh_class
        .def(
            py::init<uint32_t>(),
            "Create exponential histogram for last {window} elements.",
            py::arg("window")
        )
        .def(
            "inc",
            &ExponentialHistorgram<uint32_t>::inc,
            "Increase counter by {delta} when on the position {tick} in the stream.",
            py::arg("tick"),
            py::arg("delta")
        )
        .def(
            "get",
            &ExponentialHistorgram<uint32_t>::get,
            "Get the counter for last {window} elements when on the position {tick} in the stream.",
            py::arg("window"),
            py::arg("tick")
        )
    ;

    py::class_<ExponentialCountMinSketch<uint32_t>> ecmsketch_class(
        m,
        "ExponentialCountMinSketch",
        "Exponential count-min sketch (ECM-Sketch) combines CM-Sketch with EH to count number of different elements in the last N elements in the stream."
    );
    ecmsketch_class
        .def(
            py::init<uint32_t, uint8_t, uint32_t>(),
            "Create ECM-Sketch with width {width}, depth {depth} to count elmenets in the last {window} elements.",
            py::arg("width"),
            py::arg("depth"),
            py::arg("window")
        )
        .def(
            "inc",
            &ExponentialCountMinSketch<uint32_t>::inc,
            "Increase counter for {key} by {delta} when on the position {tick} in the stream.",
            py::arg("key"),
            py::arg("tick"),
            py::arg("delta")
        )
        .def(
            "get",
            &ExponentialCountMinSketch<uint32_t>::get,
            "Get counter for {key}for last {window} elements when on the position {tick} in the stream.",
            py::arg("key"),
            py::arg("window"),
            py::arg("tick")
        )
        ;

#ifdef VERSION_INFO
    m.attr("__version__") = VERSION_INFO;
#else
    m.attr("__version__") = "dev";
#endif
}
