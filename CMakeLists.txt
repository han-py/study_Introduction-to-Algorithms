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
        C1/U2/INSERTION-SORT/InsertionSort.cpp
)

# 冒泡排序独立可执行文件
add_executable(bubble_sort
        C1/U2/BUBBLE-SORT/BubbleSort.cpp
)

# 最大子数组独立可执行文件
add_executable(find_maximum_subarray
        C1/U4/P1_FIND-MAXIMUM-SUBARRAY/FindMaximumSubarray.cpp
)

# Strassen算法独立可执行文件
add_executable(strassen
        C1/U4/P2_STRASSEN/Strassen.cpp
)

# Coppersmith-Winograd算法独立可执行文件
add_executable(coppersmith_winograd
        C1/U4/P2_STRASSEN/others/Coppersmith-Winograd.cpp
)

# 原始Coppersmith-Winograd算法独立可执行文件
add_executable(cw_original
        C1/U4/P2_STRASSEN/others/CW-original.cpp
)

# 最新算法独立可执行文件
add_executable(newest
        C1/U4/P2_STRASSEN/others/newest.cpp
)

# 最新算法独立可执行文件
add_executable(complete_latest
        C1/U4/P2_STRASSEN/others/complete_latest.cpp
)

# 雇佣问题独立可执行文件
add_executable(employment_issues
        C1/U5/P1_EMPLOYMENT-ISSUES/EmploymentIssues.cpp
)

# 生日悖论问题独立可执行文件
add_executable(birthday_paradox
        C1/U5/P2_BIRTHDAY-PARADOX/BirthdayParadox.cpp
)

# 堆排序独立可执行文件
add_executable(heap_sort
        C2/U6/HEAP-SORT/HeapSort.cpp
)

# 优先队列独立可执行文件
add_executable(priority_queue
        C2/U6/PRIORITY-QUEUE/PriorityQueue.cpp
)

# 快速排序独立可执行文件
add_executable(quick_sort
        C2/U7/QUICK-SORT/QuickSort.cpp
)

# Hoare划分独立可执行文件
add_executable(hoare_partition
        C2/U7/HOARE-PARTITION/HoarePartition.cpp
)