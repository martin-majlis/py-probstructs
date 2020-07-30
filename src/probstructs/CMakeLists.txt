set(CMAKE_CXX_STANDARD 17)

set(HEADER_LIST "${ECMSketch_SOURCE_DIR}/src/prob_structs.h")

add_library(prob_structs_library probstructs.cpp probstructs.h MurmurHash3.cpp MurmurHash3.h)
