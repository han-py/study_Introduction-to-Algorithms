//
// Created by HaPpY on 2025/12/7.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

/**
 * 计数排序算法实现
 * 《算法导论》第八章线性时间排序中的计数排序
 * @param arr 待排序的数组
 * @return 排序后的数组
 */
std::vector<int> countingSort(const std::vector<int>& arr) {
    if (arr.empty()) return arr;
    
    std::cout << "开始计数排序..." << std::endl;
    
    // 找到数组中的最大值和最小值
    int maxVal = *std::max_element(arr.begin(), arr.end());
    int minVal = *std::min_element(arr.begin(), arr.end());
    
    std::cout << "数组中的最小值: " << minVal << ", 最大值: " << maxVal << std::endl;
    
    // 计算计数数组的大小
    int range = maxVal - minVal + 1;
    
    std::cout << "计数数组大小: " << range << std::endl;
    
    // 创建计数数组并初始化为0
    std::vector<int> count(range, 0);
    
    // 统计每个元素出现的次数
    std::cout << "统计每个元素出现的次数:" << std::endl;
    for (size_t i = 0; i < arr.size(); i++) {
        count[arr[i] - minVal]++;
        std::cout << "  元素 " << arr[i] << " 出现，计数数组count[" << (arr[i] - minVal) << "] = " << count[arr[i] - minVal] << std::endl;
    }
    
    std::cout << "计数数组内容: ";
    for (int i = 0; i < range; i++) {
        std::cout << count[i] << " ";
    }
    std::cout << std::endl;
    
    // 将计数数组转换为累积计数数组
    // count[i]现在表示小于等于(i + minVal)的元素个数
    std::cout << "计算累积计数数组:" << std::endl;
    for (int i = 1; i < range; i++) {
        count[i] += count[i - 1];
        std::cout << "  count[" << i << "] = count[" << i << "] + count[" << (i-1) << "] = " << count[i] << std::endl;
    }
    
    std::cout << "累积计数数组内容: ";
    for (int i = 0; i < range; i++) {
        std::cout << count[i] << " ";
    }
    std::cout << std::endl;
    
    // 创建输出数组
    std::vector<int> output(arr.size());
    
    // 从右到左遍历原数组，构建排序后的数组
    // 这样可以保证排序的稳定性
    std::cout << "构建输出数组:" << std::endl;
    for (int i = arr.size() - 1; i >= 0; i--) {
        int pos = count[arr[i] - minVal] - 1;
        output[pos] = arr[i];
        count[arr[i] - minVal]--;
        std::cout << "  元素 " << arr[i] << " 放置在位置 " << pos << std::endl;
    }
    
    return output;
}

/**
 * 计数排序算法实现（针对非负整数）
 * 简化版本，假设所有元素都是非负整数
 * @param arr 待排序的数组
 * @param k 数组中元素的最大值
 */
void countingSort(std::vector<int>& arr, int k) {
    int n = arr.size();
    
    std::cout << "开始简化版计数排序，k = " << k << std::endl;
    
    // 创建计数数组和输出数组
    std::vector<int> count(k + 1, 0);
    std::vector<int> output(n);
    
    // 统计每个元素出现的次数
    std::cout << "统计每个元素出现的次数:" << std::endl;
    for (int i = 0; i < n; i++) {
        count[arr[i]]++;
        std::cout << "  元素 " << arr[i] << " 出现，count[" << arr[i] << "] = " << count[arr[i]] << std::endl;
    }
    
    // 将计数数组转换为累积计数数组
    std::cout << "计算累积计数数组:" << std::endl;
    for (int i = 1; i <= k; i++) {
        count[i] += count[i - 1];
        std::cout << "  count[" << i << "] = count[" << i << "] + count[" << (i-1) << "] = " << count[i] << std::endl;
    }
    
    // 构建输出数组（从右到左遍历保证稳定性）
    std::cout << "构建输出数组:" << std::endl;
    for (int i = n - 1; i >= 0; i--) {
        int pos = count[arr[i]] - 1;
        output[pos] = arr[i];
        count[arr[i]]--;
        std::cout << "  元素 " << arr[i] << " 放置在位置 " << pos << std::endl;
    }
    
    // 将排序结果复制回原数组
    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
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
 * 主函数，用于测试计数排序算法
 */
int main() {
#ifdef ACM_LOCAL
    freopen("data.in", "r", stdin);
    freopen("data.out", "w", stdout);
#endif
    
    std::cout << "========================================" << std::endl;
    std::cout << "           计数排序算法演示" << std::endl;
    std::cout << "========================================" << std::endl << std::endl;
    
    // 测试用例1：包含重复元素的数组
    std::vector<int> arr1 = {2, 5, 3, 0, 2, 3, 0, 3};
    std::cout << "测试用例1（包含重复元素）:" << std::endl;
    printArray(arr1, "排序前: ");
    
    std::vector<int> sortedArr1 = countingSort(arr1);
    printArray(sortedArr1, "排序后: ");
    std::cout << std::endl;
    
    // 测试用例2：包含负数的数组
    std::vector<int> arr2 = {4, -2, 2, -8, 3, 1, -2, 0};
    std::cout << "测试用例2（包含负数）:" << std::endl;
    printArray(arr2, "排序前: ");
    
    std::vector<int> sortedArr2 = countingSort(arr2);
    printArray(sortedArr2, "排序后: ");
    std::cout << std::endl;
    
    // 测试用例3：使用简化版本的计数排序
    std::vector<int> arr3 = {2, 5, 3, 0, 2, 3, 0, 3};
    std::cout << "测试用例3（简化版本，已知最大值为5）:" << std::endl;
    printArray(arr3, "排序前: ");
    
    countingSort(arr3, 5);
    printArray(arr3, "排序后: ");
    
    std::cout << std::endl << "========================================" << std::endl;
    std::cout << "计数排序算法演示完成!" << std::endl;
    
    return 0;
}