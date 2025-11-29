cmake_minimum_required(VERSION 3.31)
project(study_Introduction_to_Algorithms)

set(CMAKE_CXX_STANDARD 17)

add_definitions(-D ACM_LOCAL)

add_executable(study_Introduction_to_Algorithms
        main.cpp
        U2/INSERTION-SORT/InsertionSort.cpp
)
