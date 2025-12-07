//
// Created by HaPpY on 2025/12/7.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

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
 * 随机化分区函数
 * @param arr 待处理数组
 * @param low 起始索引
 * @param high 结束索引
 * @return 分区点索引
 */
int randomizedPartition(std::vector<int>& arr, int low, int high) {
    std::cout << "  对范围 [" << low << ", " << high << "] 进行随机分区" << std::endl;
    
    // 随机选择一个元素作为基准
    static std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
    int randomIndex = low + rng() % (high - low + 1);
    std::cout << "  随机选择索引 " << randomIndex << " 的元素 " << arr[randomIndex] << " 作为基准" << std::endl;
    std::swap(arr[randomIndex], arr[high]);
    
    // 使用标准分区算法
    int pivot = arr[high];
    int i = low - 1;
    
    std::cout << "  使用 " << pivot << " 作为基准进行分区" << std::endl;
    
    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            if (i != j) {
                std::cout << "  交换 arr[" << i << "]=" << arr[i] << " 和 arr[" << j << "]=" << arr[j] << std::endl;
                std::swap(arr[i], arr[j]);
            }
        }
    }
    
    std::cout << "  将基准元素放到正确位置，交换 arr[" << (i+1) << "]=" << arr[i+1] << " 和 arr[" << high << "]=" << arr[high] << std::endl;
    std::swap(arr[i + 1], arr[high]);
    std::cout << "  分区完成，基准元素位置: " << (i+1) << std::endl;
    
    return i + 1;
}

/**
 * 随机选择算法（期望线性时间）
 * 《算法导论》第九章中位数和顺序统计量中的RANDOMIZED-SELECT算法
 * @param arr 待处理数组
 * @param low 起始索引
 * @param high 结束索引
 * @param i 查找第i小的元素（1-based）
 * @return 第i小的元素
 */
int randomizedSelect(std::vector<int>& arr, int low, int high, int i) {
    std::cout << std::endl << "查找范围 [" << low << ", " << high << "] 中第 " << i << " 小的元素" << std::endl;
    
    // 显示当前子数组状态
    std::cout << "  当前子数组: ";
    for (int k = low; k <= high; k++) {
        std::cout << arr[k] << " ";
    }
    std::cout << std::endl;
    
    // 基本情况：数组只有一个元素
    if (low == high) {
        std::cout << "  基本情况：返回唯一元素 arr[" << low << "] = " << arr[low] << std::endl;
        return arr[low];
    }
    
    // 随机化分区
    int pivotIndex = randomizedPartition(arr, low, high);
    int k = pivotIndex - low + 1;  // low到pivotIndex的元素个数
    
    std::cout << "  分区后基准元素为 arr[" << pivotIndex << "] = " << arr[pivotIndex] << std::endl;
    std::cout << "  基准元素是当前范围中第 " << k << " 小的元素" << std::endl;
    
    // 如果基准元素正好是第i小的元素
    if (i == k) {
        std::cout << "  找到了第 " << i << " 小的元素: " << arr[pivotIndex] << std::endl;
        return arr[pivotIndex];
    }
    // 如果第i小的元素在基准元素的左边
    else if (i < k) {
        std::cout << "  第 " << i << " 小的元素在左半部分" << std::endl;
        return randomizedSelect(arr, low, pivotIndex - 1, i);
    }
    // 如果第i小的元素在基准元素的右边
    else {
        std::cout << "  第 " << i << " 小的元素在右半部分" << std::endl;
        return randomizedSelect(arr, pivotIndex + 1, high, i - k);
    }
}

/**
 * 随机选择算法包装函数
 * @param arr 待处理数组
 * @param i 查找第i小的元素（1-based）
 * @return 第i小的元素
 */
int randomizedSelect(std::vector<int>& arr, int i) {
    if (i < 1 || i > (int)arr.size()) {
        std::cerr << "错误：i必须在1到" << arr.size() << "之间" << std::endl;
        return -1;
    }
    std::cout << "开始随机选择算法，查找第 " << i << " 小的元素..." << std::endl;
    printArray(arr, "原数组: ");
    return randomizedSelect(arr, 0, arr.size() - 1, i);
}

/**
 * 主函数，用于测试随机选择算法
 */
int main() {
#ifdef ACM_LOCAL
    freopen("data.in", "r", stdin);
    freopen("data.out", "w", stdout);
#endif
    
    std::cout << "========================================" << std::endl;
    std::cout << "       随机选择算法演示" << std::endl;
    std::cout << "========================================" << std::endl << std::endl;
    
    // 测试用例
    std::vector<int> arr = {3, 2, 9, 0, 7, 5, 4, 8, 6, 1};
    std::cout << "测试数组: ";
    printArray(arr);
    std::cout << std::endl;
    
    // 查找第3小的元素
    std::vector<int> arrCopy = arr;  // 保留原数组用于后续测试
    int result = randomizedSelect(arrCopy, 3);
    std::cout << std::endl << "第3小的元素是: " << result << std::endl << std::endl;
    
    // 查找最小元素
    arrCopy = arr;
    result = randomizedSelect(arrCopy, 1);
    std::cout << "最小元素是: " << result << std::endl << std::endl;
    
    // 查找最大元素
    arrCopy = arr;
    result = randomizedSelect(arrCopy, arr.size());
    std::cout << "最大元素是: " << result << std::endl << std::endl;
    
    // 查找中位数
    arrCopy = arr;
    result = randomizedSelect(arrCopy, (arr.size() + 1) / 2);
    std::cout << "中位数是: " << result << std::endl;
    
    std::cout << std::endl << "========================================" << std::endl;
    std::cout << "随机选择算法演示完成!" << std::endl;
    
    return 0;
}