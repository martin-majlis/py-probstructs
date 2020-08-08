set(CMAKE_CXX_STANDARD 11)

set(HEADER_LIST "${PROBSTRUCTS_SOURCE_DIR}/src/prob_structs.h")

add_library(probstructs probstructs.cpp probstructs.h MurmurHash3.cpp MurmurHash3.h)
target_include_directories(probstructs PUBLIC .)