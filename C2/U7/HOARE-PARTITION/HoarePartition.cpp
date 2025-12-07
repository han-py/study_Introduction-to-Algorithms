//
// Created by HaPpY on 2025/12/7.
//

#include <iostream>
#include <vector>

/**
 * Hoare划分算法实现
 * 该算法由C.R.Hoare在1960年代初设计，是快速排序的原始划分方案
 * @param arr 待划分的数组
 * @param low 起始索引
 * @param high 结束索引
 * @return 分割点索引
 */
int hoarePartition(std::vector<int>& arr, int low, int high) {
    // 选择第一个元素作为基准
    int pivot = arr[low];
    int i = low - 1;  // 左指针
    int j = high + 1; // 右指针
    
    std::cout << "  执行Hoare划分，范围: [" << low << ", " << high << "], 基准: " << pivot << std::endl;
    
    while (true) {
        // 从左边找到第一个大于等于pivot的元素
        do {
            i++;
        } while (arr[i] < pivot);
        
        // 从右边找到第一个小于等于pivot的元素
        do {
            j--;
        } while (arr[j] > pivot);
        
        // 如果指针相遇或交错，则返回分割点
        if (i >= j) {
            std::cout << "  划分完成，返回分割点: " << j << std::endl;
            return j;
        }
        
        // 交换元素
        std::cout << "  交换 arr[" << i << "]=" << arr[i] << " 和 arr[" << j << "]=" << arr[j] << std::endl;
        std::swap(arr[i], arr[j]);
    }
}

/**
 * 快速排序主函数（使用Hoare划分）
 * @param arr 待排序数组
 * @param low 起始索引
 * @param high 结束索引
 */
void quickSort(std::vector<int>& arr, int low, int high) {
    std::cout << "处理范围: [" << low << ", " << high << "]" << std::endl;
    
    // 打印当前子数组状态
    std::cout << "  当前子数组: ";
    for (int k = low; k <= high; k++) {
        std::cout << arr[k] << " ";
    }
    std::cout << std::endl;
    
    if (low < high) {
        // 使用Hoare划分获取分割点
        int pivotIndex = hoarePartition(arr, low, high);
        
        std::cout << "分割点: " << pivotIndex << std::endl << std::endl;
        
        // 递归排序分割点左右两部分
        // 注意：与Lomuto划分不同，这里递归调用时不需要跳过pivot
        quickSort(arr, low, pivotIndex);
        quickSort(arr, pivotIndex + 1, high);
    } else {
        std::cout << "递归终止" << std::endl << std::endl;
    }
}

/**
 * 快速排序包装函数
 * @param arr 待排序数组
 */
void quickSort(std::vector<int>& arr) {
    if (!arr.empty()) {
        std::cout << "开始Hoare划分快速排序..." << std::endl;
        quickSort(arr, 0, arr.size() - 1);
    }
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
 * 主函数，用于测试Hoare划分算法
 */
int main() {
#ifdef ACM_LOCAL
    freopen("data.in", "r", stdin);
    freopen("data.out", "w", stdout);
#endif
    
    std::vector<int> arr = {10, 7, 8, 9, 1, 5};
    std::cout << "========================================" << std::endl;
    std::cout << "      Hoare划分快速排序算法演示" << std::endl;
    std::cout << "========================================" << std::endl << std::endl;
    
    printArray(arr, "排序前: ");
    std::cout << std::endl;
    
    quickSort(arr);
    
    std::cout << "========================================" << std::endl;
    std::cout << "排序完成!" << std::endl;
    printArray(arr, "排序后: ");
    
    return 0;
}