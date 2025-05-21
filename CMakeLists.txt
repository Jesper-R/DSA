cmake_minimum_required(VERSION 3.29)
project(DSA)

set(CMAKE_CXX_STANDARD 20)



add_executable(GraphTestOne src/course-labs/c1/GraphPt1.cpp
        src/course-labs/c1/Priorityqueue.h
        src/course-labs/c1/Heap.h
        src/course-labs/c1/GraphOne.h)
