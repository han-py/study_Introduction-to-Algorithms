//
// Created by HaPpY on 2025/11/30.
//

#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>

/**
 * 结果结构体，用于存储最大子数组的信息
 */
struct SubarrayResult {
    int left_index;   // 最大子数组的左边界索引
    int right_index;  // 最大子数组的右边界索引
    int max_sum;      // 最大子数组的和
};

/**
 * 寻找跨越中点的最大子数组
 * @param arr 输入数组
 * @param low 起始索引
 * @param mid 中点索引
 * @param high 结束索引
 * @return 跨越中点的最大子数组结果
 */
SubarrayResult findMaxCrossingSubarray(const std::vector<int>& arr, int low, int mid, int high) {
    // 找到左半部分的最大和
    int left_sum = INT_MIN;
    int sum = 0;
    int max_left = mid;
    
    for (int i = mid; i >= low; i--) {
        sum += arr[i];
        if (sum > left_sum) {
            left_sum = sum;
            max_left = i;
        }
    }
    
    // 找到右半部分的最大和
    int right_sum = INT_MIN;
    sum = 0;
    int max_right = mid;
    
    for (int j = mid + 1; j <= high; j++) {
        sum += arr[j];
        if (sum > right_sum) {
            right_sum = sum;
            max_right = j;
        }
    }
    
    // 返回跨越中点的最大子数组
    return {max_left, max_right, left_sum + right_sum};
}

/**
 * 使用分治法寻找最大子数组
 * @param arr 输入数组
 * @param low 起始索引
 * @param high 结束索引
 * @return 最大子数组结果
 */
SubarrayResult findMaxSubarray(const std::vector<int>& arr, int low, int high) {
    // 基本情况：只有一个元素
    if (low == high) {
        return {low, high, arr[low]};
    }
    
    // 分治步骤：将数组分成两半
    int mid = (low + high) / 2;
    
    // 递归求解左半部分的最大子数组
    SubarrayResult left_result = findMaxSubarray(arr, low, mid);
    
    // 递归求解右半部分的最大子数组
    SubarrayResult right_result = findMaxSubarray(arr, mid + 1, high);
    
    // 求解跨越中点的最大子数组
    SubarrayResult cross_result = findMaxCrossingSubarray(arr, low, mid, high);
    
    // 返回三者中的最大值
    if (left_result.max_sum >= right_result.max_sum && left_result.max_sum >= cross_result.max_sum) {
        return left_result;
    } else if (right_result.max_sum >= left_result.max_sum && right_result.max_sum >= cross_result.max_sum) {
        return right_result;
    } else {
        return cross_result;
    }
}

/**
 * 打印数组元素
 * @param arr 要打印的数组
 */
void printArray(const std::vector<int>& arr) {
    std::cout << "[";
    for (size_t i = 0; i < arr.size(); i++) {
        std::cout << arr[i];
        if (i < arr.size() - 1) std::cout << ", ";
    }
    std::cout << "]";
}

/**
 * 打印子数组元素
 * @param arr 要打印的数组
 * @param left 左边界索引
 * @param right 右边界索引
 */
void printSubarray(const std::vector<int>& arr, int left, int right) {
    std::cout << "[";
    for (int i = left; i <= right; i++) {
        std::cout << arr[i];
        if (i < right) std::cout << ", ";
    }
    std::cout << "]";
}

/**
 * 主函数，用于测试最大子数组算法
 */
int main() {
#ifdef ACM_LOCAL
    freopen("data.in", "r", stdin);
    freopen("data.out", "w", stdout);
#endif
    std::vector<int> arr = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    
    std::cout << "数组: ";
    printArray(arr);
    std::cout << std::endl;
    
    // 使用分治法寻找最大子数组
    SubarrayResult result = findMaxSubarray(arr, 0, arr.size() - 1);
    
    std::cout << "最大子数组: ";
    printSubarray(arr, result.left_index, result.right_index);
    std::cout << std::endl;
    std::cout << "最大和: " << result.max_sum << std::endl;
    
    return 0;
}