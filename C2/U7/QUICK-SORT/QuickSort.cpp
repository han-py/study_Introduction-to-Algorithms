//
// Created by HaPpY on 2025/12/7.
//

#include <iostream>
#include <vector>

/**
 * 分区函数，快速排序的核心
 * @param arr 待排序数组
 * @param low 起始索引
 * @param high 结束索引
 * @return 分区点索引
 */
int partition(std::vector<int>& arr, int low, int high) {
    int pivot = arr[high];  // 选择最后一个元素作为基准
    int i = low - 1;  // 较小元素的索引

    for (int j = low; j <= high - 1; j++) {
        // 如果当前元素小于或等于基准
        if (arr[j] <= pivot) {
            i++;  // 较小元素索引增加
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return (i + 1);
}

/**
 * 快速排序主函数
 * @param arr 待排序数组
 * @param low 起始索引
 * @param high 结束索引
 */
void quickSort(std::vector<int>& arr, int low, int high) {
    if (low < high) {
        // 获取分区索引
        int pi = partition(arr, low, high);

        // 分别对基准元素左右两部分进行排序
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

/**
 * 快速排序包装函数
 * @param arr 待排序数组
 */
void quickSort(std::vector<int>& arr) {
    quickSort(arr, 0, arr.size() - 1);
}

/**
 * 打印数组元素
 * @param arr 要打印的数组
 * @param msg 打印信息
 */
void printArray(const std::vector<int>& arr, const std::string& msg = "") {
    if (!msg.empty()) {
        std::cout << msg;
    }
    for (size_t i = 0; i < arr.size(); i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

/**
 * 主函数，用于测试快速排序算法
 */
int main() {
#ifdef ACM_LOCAL
    freopen("data.in", "r", stdin);
    freopen("data.out", "w", stdout);
#endif
    
    std::vector<int> arr = {10, 7, 8, 9, 1, 5};
    std::cout << "========================================" << std::endl;
    std::cout << "           快速排序算法演示" << std::endl;
    std::cout << "========================================" << std::endl << std::endl;
    
    printArray(arr, "排序前: ");
    std::cout << std::endl;
    
    quickSort(arr);
    
    std::cout << "========================================" << std::endl;
    std::cout << "排序完成!" << std::endl;
    printArray(arr, "排序后: ");
    
    return 0;
}