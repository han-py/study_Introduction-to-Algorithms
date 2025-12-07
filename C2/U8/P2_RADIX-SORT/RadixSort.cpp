//
// Created by HaPpY on 2025/12/7.
//

#include <iostream>
#include <vector>
#include <algorithm>

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
 * 获取数字中指定位上的数字
 * @param num 数字
 * @param digit 位数（从右往左数，从1开始）
 * @return 指定位上的数字
 */
int getDigit(int num, int digit) {
    for (int i = 1; i < digit; i++) {
        num /= 10;
    }
    return num % 10;
}

/**
 * 获取数组中最大数的位数
 * @param arr 数组
 * @return 最大数的位数
 */
int getMaxDigits(const std::vector<int>& arr) {
    int maxVal = *std::max_element(arr.begin(), arr.end());
    int digits = 0;
    while (maxVal > 0) {
        maxVal /= 10;
        digits++;
    }
    return digits;
}

/**
 * 计数排序（针对指定位）
 * @param arr 待排序数组
 * @param digit 位数（从右往左数，从1开始）
 */
void countingSortForRadix(std::vector<int>& arr, int digit) {
    int n = arr.size();
    std::vector<int> output(n);
    std::vector<int> count(10, 0); // 0-9十个数字
    
    std::cout << "    对第 " << digit << " 位进行计数排序" << std::endl;
    
    // 统计当前位上各数字出现的次数
    std::cout << "    统计各数字出现次数: ";
    for (int i = 0; i < n; i++) {
        int d = getDigit(arr[i], digit);
        count[d]++;
        std::cout << "arr[" << i << "]=" << arr[i] << "(第" << digit << "位是" << d << ") ";
    }
    std::cout << std::endl;
    
    std::cout << "    计数数组: ";
    for (int i = 0; i < 10; i++) {
        std::cout << count[i] << " ";
    }
    std::cout << std::endl;
    
    // 计算累积计数
    std::cout << "    计算累积计数: ";
    for (int i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }
    for (int i = 0; i < 10; i++) {
        std::cout << count[i] << " ";
    }
    std::cout << std::endl;
    
    // 构建输出数组（从右到左遍历保证稳定性）
    std::cout << "    构建输出数组: ";
    for (int i = n - 1; i >= 0; i--) {
        int d = getDigit(arr[i], digit);
        int pos = count[d] - 1;
        output[pos] = arr[i];
        count[d]--;
        std::cout << "arr[" << i << "]=" << arr[i] << " 放置在位置 " << pos << " ";
    }
    std::cout << std::endl;
    
    // 将排序结果复制回原数组
    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
    }
}

/**
 * 基数排序算法实现
 * 《算法导论》第八章线性时间排序中的基数排序
 * @param arr 待排序的数组
 */
void radixSort(std::vector<int>& arr) {
    if (arr.empty()) return;
    
    std::cout << "开始基数排序..." << std::endl;
    
    // 获取最大数的位数
    int maxDigits = getMaxDigits(arr);
    std::cout << "数组中最大数的位数: " << maxDigits << std::endl;
    printArray(arr, "原数组: ");
    std::cout << std::endl;
    
    // 对每一位进行计数排序
    for (int digit = 1; digit <= maxDigits; digit++) {
        std::cout << "正在对第 " << digit << " 位进行排序:" << std::endl;
        countingSortForRadix(arr, digit);
        printArray(arr, "    排序后: ");
        std::cout << std::endl;
    }
}

/**
 * 主函数，用于测试基数排序算法
 */
int main() {
#ifdef ACM_LOCAL
    freopen("data.in", "r", stdin);
    freopen("data.out", "w", stdout);
#endif
    
    std::cout << "========================================" << std::endl;
    std::cout << "           基数排序算法演示" << std::endl;
    std::cout << "========================================" << std::endl << std::endl;
    
    // 测试用例
    std::vector<int> arr = {329, 457, 657, 839, 436, 720, 355};
    std::cout << "测试用例:" << std::endl;
    printArray(arr, "排序前: ");
    std::cout << std::endl;
    
    radixSort(arr);
    
    std::cout << "========================================" << std::endl;
    printArray(arr, "最终排序结果: ");
    std::cout << "基数排序算法演示完成!" << std::endl;
    
    return 0;
}