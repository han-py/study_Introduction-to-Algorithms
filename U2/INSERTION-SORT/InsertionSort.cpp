//
// Created by HaPpY on 2025/11/30.
//

#include <iostream>
#include <vector>

/**
 * 插入排序算法实现
 * @param arr 待排序的整型数组
 */
void insertionSort(std::vector<int>& arr) {
    int n = arr.size();
    // 从第二个元素开始遍历（索引为1）
    for (int i = 1; i < n; i++) {
        int key = arr[i];  // 当前要插入的元素
        int j = i - 1;     // 已排序部分的最后一个元素索引
        
        // 将大于key的元素向后移动
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        // 将key插入到正确位置
        arr[j + 1] = key;
    }
}

/**
 * 打印数组元素
 * @param arr 要打印的数组
 */
void printArray(const std::vector<int>& arr) {
    for (size_t i = 0; i < arr.size(); i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

/**
 * 主函数，用于测试插入排序算法
 */
int main() {
#ifdef ACM_LOCAL
    freopen("data.in", "r", stdin);
    freopen("data.out", "w", stdout);
#endif
    std::vector<int> arr = {5, 2, 4, 6, 1, 3};
    std::cout << "排序前: ";
    printArray(arr);
    
    insertionSort(arr);
    
    std::cout << "排序后: ";
    printArray(arr);
    
    return 0;
}