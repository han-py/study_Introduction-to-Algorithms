//
// Created by HaPpY on 2025/11/30.
//

#include <iostream>
#include <vector>

/**
 * 冒泡排序算法实现
 * @param arr 待排序的整型数组
 */
void bubbleSort(std::vector<int>& arr) {
    int n = arr.size();
    // 外层循环控制排序轮数
    for (int i = 0; i < n - 1; i++) {
        bool swapped = false;
        // 内层循环进行相邻元素比较和交换
        for (int j = 0; j < n - i - 1; j++) {
            // 如果前一个元素大于后一个元素，则交换
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = true;
            }
        }
        // 如果这一轮没有发生交换，说明数组已经有序，可以提前结束
        if (!swapped) {
            break;
        }
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
 * 主函数，用于测试冒泡排序算法
 */
int main() {
#ifdef ACM_LOCAL
    freopen("data.in", "r", stdin);
    freopen("data.out", "w", stdout);
#endif
    std::vector<int> arr = {5, 2, 4, 6, 1, 3};
    std::cout << "排序前: ";
    printArray(arr);
    
    bubbleSort(arr);
    
    std::cout << "排序后: ";
    printArray(arr);
    
    return 0;
}