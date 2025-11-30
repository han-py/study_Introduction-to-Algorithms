cmake_minimum_required(VERSION 3.31)
project(study_Introduction_to_Algorithms)

set(CMAKE_CXX_STANDARD 17)

add_definitions(-D ACM_LOCAL)

# 主程序可执行文件
add_executable(study_Introduction_to_Algorithms
        main.cpp
)

# 插入排序独立可执行文件
add_executable(insertion_sort
        U2/INSERTION-SORT/InsertionSort.cpp
)

# 冒泡排序独立可执行文件
add_executable(bubble_sort
        U2/BUBBLE-SORT/BubbleSort.cpp
)

# 最大子数组独立可执行文件
add_executable(find_maximum_subarray
        U4/P1_FIND-MAXIMUM-SUBARRAY/FindMaximumSubarray.cpp
)

# Strassen算法独立可执行文件
add_executable(strassen
        U4/P2_STRASSEN/Strassen.cpp
)