#include <pybind11/pybind11.h>
#include "probstructs/probstructs.h"

namespace py = pybind11;

PYBIND11_MODULE(probstructs, m) {
    using namespace probstructs;

    m.doc() = R"pbdoc(
        ProbStructs collection of probabilistic data structures.

        C++: https://probstructs.readthedocs.io/en/stable/
    )pbdoc";

    py::class_<CountMinSketch<uint32_t>> cmsketch_class(
        m,
        "CountMinSketch",
        R"pbdoc(
            Count–min sketch (CM sketch) is a probabilistic data structure that serves as a frequency table of events in a stream of data.

            It uses hash functions to map events to frequencies, but unlike a hash table uses only sub-linear space, at the expense of
            overcounting some events due to collisions.

            C++: https://probstructs.readthedocs.io/en/stable/classes.html#clscountminsketch
        )pbdoc"
    );

    cmsketch_class
        .def(
            py::init<uint32_t, uint8_t>(),
            R"pbdoc(
                Create CM sketch with width {width} and depth {depth}.
            )pbdoc",
            py::arg("width"),
            py::arg("depth")
        )
        .def(
            "inc",
            &CountMinSketch<uint32_t>::inc,
            R"pbdoc(
                Increase counter for {key} by {delta}.
            )pbdoc",
            py::arg("key"),
            py::arg("delta")
        )
        .def(
            "get",
            &CountMinSketch<uint32_t>::get,
            R"pbdoc(
                Get count for {key}.
            )pbdoc",
            py::arg("key")
        )
    ;

    py::class_<ExponentialHistorgram<uint32_t>> eh_class(
        m,
        "ExponentialHistorgram",
        R"pbdoc(
            Exponential histogram (EH) is a probabilistic data structure that serves as a frequency counter for
            specific elements in the last N elements from stream.

            C++: https://probstructs.readthedocs.io/en/stable/classes.html#exponentialhistorgram
        )pbdoc"
    );
    eh_class
        .def(
            py::init<uint32_t>(),
            R"pbdoc(
                Create exponential histogram for last {window} elements.
            )pbdoc",
            py::arg("window")
        )
        .def(
            "inc",
            &ExponentialHistorgram<uint32_t>::inc,
            R"pbdoc(
                Increase counter by {delta} when on the position {tick} in the stream.
            )pbdoc",
            py::arg("tick"),
            py::arg("delta")
        )
        .def(
            "get",
            &ExponentialHistorgram<uint32_t>::get,
            R"pbdoc(
                Get the counter for last {window} elements when on the position {tick} in the stream.
            )pbdoc",
            py::arg("window"),
            py::arg("tick")
        )
    ;

    py::class_<ExponentialCountMinSketch<uint32_t>> ecmsketch_class(
        m,
        "ExponentialCountMinSketch",
        R"pbdoc(
            Exponential count-min sketch (ECM-Sketch) combines CM-Sketch with EH to count number of different elements in the last N elements in the stream.

            C++: https://probstructs.readthedocs.io/en/stable/classes.html#exponentialcountminsketch
        )pbdoc"
    );
    ecmsketch_class
        .def(
            py::init<uint32_t, uint8_t, uint32_t>(),
            R"pbdoc(
                Create ECM-Sketch with width {width}, depth {depth} to count elmenets in the last {window} elements.
            )pbdoc",
            py::arg("width"),
            py::arg("depth"),
            py::arg("window")
        )
        .def(
            "inc",
            &ExponentialCountMinSketch<uint32_t>::inc,
            R"pbdoc(
                Increase counter for {key} by {delta} when on the position {tick} in the stream.
            )pbdoc",
            py::arg("key"),
            py::arg("tick"),
            py::arg("delta")
        )
        .def(
            "get",
            &ExponentialCountMinSketch<uint32_t>::get,
            R"pbdoc(
                Get counter for {key}for last {window} elements when on the position {tick} in the stream.
            )pbdoc",
            py::arg("key"),
            py::arg("window"),
            py::arg("tick")
        )
        ;


    py::class_<Hash> hash_class(m, "Hash", R"pbdoc(
        Hashing function - MurMurHash3

        C++: https://probstructs.readthedocs.io/en/stable/classes.html#hash
    )pbdoc");
    hash_class
        .def(
            py::init<uint32_t>(),
            R"pbdoc(
                Create hashing function with {seed}.
            )pbdoc",
            py::arg("seed")
        )
        .def(
            "hash",
            &Hash::hash,
            R"pbdoc(
                Hash {key}.
            )pbdoc",
            py::arg("key")
        );

    m.attr("__version__") = "0.2.6";
}
