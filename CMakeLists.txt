cmake_minimum_required(VERSION 3.31)
project(study_Introduction_to_Algorithms)

set(CMAKE_CXX_STANDARD 17)

add_definitions(-D ACM_LOCAL)

# 主程序可执行文件
add_executable(study_Introduction_to_Algorithms
        main.cpp
)

# 插入排序独立可执行文件
add_executable(C1-U2-insertion_sort
        C1/U2/INSERTION-SORT/InsertionSort.cpp
)

# 冒泡排序独立可执行文件
add_executable(C1-U2-bubble_sort
        C1/U2/BUBBLE-SORT/BubbleSort.cpp
)

# 最大子数组独立可执行文件
add_executable(C1-U4-P1_find_maximum_subarray
        C1/U4/P1_FIND-MAXIMUM-SUBARRAY/FindMaximumSubarray.cpp
)

# Kadane算法独立可执行文件
add_executable(C1-U4-P1_kadane
        C1/U4/P1_FIND-MAXIMUM-SUBARRAY/Kadane.cpp
)

# 最大子数组乘积独立可执行文件
add_executable(C1-U4-P1-P1_maximum_subarray_product
        C1/U4/P1_FIND-MAXIMUM-SUBARRAY/VariantIssue/P1_MAXIMUM-SUBARRAY-PRODUCT/MaximumSubarrayProduct.cpp
)

# 环形数组中的最大子数组独立可执行文件
add_executable(C1-U4-P1-P2_maximum_subarray_in_a_circular_array
        C1/U4/P1_FIND-MAXIMUM-SUBARRAY/VariantIssue/P2_MAXIMUM-SUBARRAY-IN-A-CIRCULAR-ARRAY/MaximumSubarrayInACircularArray.cpp
)

# Strassen算法独立可执行文件
add_executable(C1-U4-P2_strassen
        C1/U4/P2_STRASSEN/Strassen.cpp
)

# Coppersmith-Winograd算法独立可执行文件
add_executable(C1-U4-P2_coppersmith_winograd
        C1/U4/P2_STRASSEN/others/Coppersmith-Winograd.cpp
)

# 原始Coppersmith-Winograd算法独立可执行文件
add_executable(C1-U4-P2_cw_original
        C1/U4/P2_STRASSEN/others/CW-original.cpp
)

# 最新算法独立可执行文件
add_executable(C1-U4-P2_newest
        C1/U4/P2_STRASSEN/others/newest.cpp
)

# 最新算法独立可执行文件
add_executable(C1-U4-P2_complete_latest
        C1/U4/P2_STRASSEN/others/complete_latest.cpp
)

# 雇佣问题独立可执行文件
add_executable(C1-U5-P1-employment_issues
        C1/U5/P1_EMPLOYMENT-ISSUES/EmploymentIssues.cpp
)

# 生日悖论问题独立可执行文件
add_executable(C1-U5-P2-birthday_paradox
        C1/U5/P2_BIRTHDAY-PARADOX/BirthdayParadox.cpp
)

# 堆排序独立可执行文件
add_executable(C2-U6-heap_sort
        C2/U6/HEAP-SORT/HeapSort.cpp
)

# 优先队列独立可执行文件
add_executable(C2-U6-priority_queue
        C2/U6/PRIORITY-QUEUE/PriorityQueue.cpp
)

# 快速排序独立可执行文件
add_executable(C2-U7-quick_sort
        C2/U7/QUICK-SORT/QuickSort.cpp
)

# Hoare划分独立可执行文件
add_executable(C2-U7-hoare_partition
        C2/U7/HOARE-PARTITION/HoarePartition.cpp
)

# 计数排序独立可执行文件
add_executable(C2-U8-P1-counting_sort
        C2/U8/P1_COUNTING-SORT/CountingSort.cpp
)

# 基数排序独立可执行文件
add_executable(C2-U8-P2-radix_sort
        C2/U8/P2_RADIX-SORT/RadixSort.cpp
)

# 桶排序独立可执行文件
add_executable(C2-U8-P3-bucket_sort
        C2/U8/P3_BUCKET-SORT/BucketSort.cpp
)

# Randomized选择独立可执行文件
add_executable(C2-U9-randomized_select
        C2/U9/RANDOMIZED-SELECT/RandomizedSelect.cpp
)

# 栈独立可执行文件
add_executable(C3-U10-stack
        C3/U10/STACK/Stack.cpp
)

# 队列独立可执行文件
add_executable(C3-U10-queue
        C3/U10/QUEUE/Queue.cpp
)

# 单向链表独立可执行文件
add_executable(C3-U10-singly_linked_list
        C3/U10/LINKED-LIST/SinglyLinkedListTest.cpp
)

# 双向链表独立可执行文件
add_executable(C3-U10-doubly_linked_list
        C3/U10/LINKED-LIST/DoublyLinkedListTest.cpp
)

# 循环链表独立可执行文件
add_executable(C3-U10-circular_linked_list
        C3/U10/LINKED-LIST/CircularLinkedListTest.cpp
)

# 指针和对象独立可执行文件
add_executable(C3-U10-pointer_and_object
        C3/U10/POINTER-AND-OBJECT/PointerAndObject.cpp
)

# 树独立可执行文件
add_executable(C3-U10-tree
        C3/U10/TREE/Tree.cpp
)

# 散列表独立可执行文件
add_executable(C3-U11-hash_table
        C3/U11/HASH-TABLE/HashTable.cpp
)

# 二叉搜索树独立可执行文件
add_executable(C3-U12-binary_search_tree
        C3/U12/BINARY-SEARCH-TREE/BinarySearchTree.cpp
)

# C3-U13
add_executable(C3-U13-red_black_tree
        C3/U13/RED-BLACK-TREE/RedBlackTree.cpp
)

# C3-U14
add_executable(C3-U14-augmented_red_black_tree
        C3/U14/AUGMENTED-RED-BLACK-TREE/AugmentedRedBlackTree.cpp
)

# 钢条切割独立可执行文件
add_executable(C4-U15-P1-steel_bar_cutting
        C4/U15/P1_STEEL-BAR-CUTTING/SteelBarCutting.cpp
)

# 矩阵链乘独立可执行文件
add_executable(C4-U15-P2-matrix_chain_multiplication
        C4/U15/P2_MATRIX-CHAIN-MULTIPLICATION/MatrixChainMultiplication.cpp
)