cmake_minimum_required(VERSION 3.29)
project(DSA)

set(CMAKE_CXX_STANDARD 20)

# algorithms
add_executable(linear_search src/algorithms/linear_search.cpp
        src/algorithms/merge.h
        src/algorithms/quicklomuto.h
        src/algorithms/quickhoare.h
        src/algorithms/heap.h)

# course-labs
add_executable(lab_A1 src/course-labs/A1.cpp src/course-labs/A1.h
        src/course-labs/A2.h
        src/course-labs/B1.h)