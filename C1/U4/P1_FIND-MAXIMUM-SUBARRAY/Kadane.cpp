//
// Created by HaPpY on 2025/12/9.
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
    
    // 构造函数
    SubarrayResult(int left, int right, int sum) : left_index(left), right_index(right), max_sum(sum) {}
};

/**
 * 使用 Kadane 算法寻找最大子数组（仅返回最大和）
 * 这是最简单的 Kadane 算法版本，只计算最大和而不追踪子数组位置
 * 
 * @param arr 输入数组
 * @return 最大子数组的和
 * 
 * 📌 算法原理:
 * Kadane 算法的核心思想是动态规划：
 * - 对于数组中的每一个元素，我们决定是把它加入到当前子数组中，还是以它为起点开始一个新的子数组
 * - 我们维护两个变量：
 *   1. max_current：以当前元素结尾的最大子数组和
 *   2. max_global：到目前为止见过的最大子数组和
 */
int kadaneSimple(const std::vector<int>& arr) {
    // 初始化当前最大值和全局最大值为第一个元素
    int max_current = arr[0];
    int max_global = arr[0];
    
    std::cout << "🔍 算法开始执行：" << std::endl;
    std::cout << "   初始状态 -> 当前最大值: " << max_current << ", 全局最大值: " << max_global << std::endl;
    
    // 从第二个元素开始遍历数组
    for (size_t i = 1; i < arr.size(); i++) {
        std::cout << "   处理元素 arr[" << i << "] = " << arr[i] << std::endl;
        
        // 决定是将当前元素加入现有子数组，还是以当前元素开始新的子数组
        // 如果当前元素比(当前子数组和+当前元素)更大，说明前面的子数组是负贡献，应该舍弃
        max_current = std::max(arr[i], max_current + arr[i]);
        std::cout << "   更新后 -> 当前最大值: " << max_current << std::endl;
        
        // 更新全局最大值
        if (max_current > max_global) {
            max_global = max_current;
            std::cout << "   🎯 发现新的最大值: " << max_global << std::endl;
        }
    }
    
    return max_global;
}

/**
 * 使用 Kadane 算法寻找最大子数组（返回完整结果，包括位置信息）
 * 这是 Kadane 算法的增强版本，不仅能计算最大和，还能追踪最大子数组的位置
 * 
 * @param arr 输入数组
 * @return 包含最大子数组位置和和值的结构体
 * 
 * 📌 算法原理:
 * 在简单版本的基础上，我们增加了位置追踪功能：
 * - temp_left：临时记录当前子数组的起始位置
 * - left_index, right_index：记录最大子数组的起始和结束位置
 */
SubarrayResult kadaneWithPosition(const std::vector<int>& arr) {
    // 初始化变量
    int max_current = arr[0];     // 以当前元素结尾的最大子数组和
    int max_global = arr[0];      // 全局最大子数组和
    int left_index = 0;           // 最大子数组的起始位置
    int right_index = 0;          // 最大子数组的结束位置
    int temp_left = 0;            // 临时记录当前子数组的起始位置
    
    std::cout << "\n🔍 增强版 Kadane 算法开始执行：" << std::endl;
    std::cout << "   初始状态 -> 当前最大值: " << max_current 
              << ", 全局最大值: " << max_global 
              << ", 当前子数组: [" << temp_left << ", 0]" << std::endl;
    
    // 从第二个元素开始遍历数组
    for (size_t i = 1; i < arr.size(); i++) {
        std::cout << "   处理元素 arr[" << i << "] = " << arr[i] << std::endl;
        
        // 如果当前元素比(当前子数组和+当前元素)更大
        // 这意味着前面的子数组是负贡献，应该舍弃，从当前元素重新开始
        if (arr[i] > max_current + arr[i]) {
            max_current = arr[i];
            temp_left = i;  // 更新当前子数组的起始位置
            std::cout << "   🔄 重新开始子数组，新起始位置: " << temp_left << std::endl;
        } else {
            // 否则将当前元素加入到现有子数组中
            max_current = max_current + arr[i];
            std::cout << "   ➕ 将元素加入现有子数组" << std::endl;
        }
        
        std::cout << "   当前子数组: [" << temp_left << ", " << i << "], 和值: " << max_current << std::endl;
        
        // 如果当前子数组和大于已知的最大子数组和，则更新最大值和位置
        if (max_current > max_global) {
            max_global = max_current;
            left_index = temp_left;
            right_index = i;
            std::cout << "   🎯 发现新的最大子数组: [" << left_index << ", " << right_index 
                      << "], 和值: " << max_global << std::endl;
        }
    }
    
    return SubarrayResult(left_index, right_index, max_global);
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
 * 主函数，用于测试 Kadane 算法
 */
int main() {
#ifdef ACM_LOCAL
    freopen("data.in", "r", stdin);
    freopen("data.out", "w", stdout);
#endif
    std::cout << "========================================" << std::endl;
    std::cout << "           Kadane 算法详解             " << std::endl;
    std::cout << "========================================" << std::endl;
    
    // 测试用例1：经典的例子
    std::vector<int> arr1 = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    std::cout << "\n📝 测试用例 1:" << std::endl;
    std::cout << "   数组: ";
    printArray(arr1);
    std::cout << std::endl;
    
    // 使用简单版 Kadane 算法
    std::cout << "\n🔷 使用简单版 Kadane 算法（仅计算最大和）:" << std::endl;
    int maxSum1 = kadaneSimple(arr1);
    std::cout << "   最大子数组和: " << maxSum1 << std::endl;
    
    // 使用增强版 Kadane 算法
    std::cout << "\n🔷 使用增强版 Kadane 算法（计算最大和及位置）:" << std::endl;
    SubarrayResult result1 = kadaneWithPosition(arr1);
    std::cout << "   最大子数组: ";
    printSubarray(arr1, result1.left_index, result1.right_index);
    std::cout << std::endl;
    std::cout << "   最大和: " << result1.max_sum << std::endl;
    
    // 测试用例2：全部为负数的数组
    std::vector<int> arr2 = {-5, -2, -8, -1, -4};
    std::cout << "\n\n📝 测试用例 2 (全负数):" << std::endl;
    std::cout << "   数组: ";
    printArray(arr2);
    std::cout << std::endl;
    
    std::cout << "\n🔷 使用增强版 Kadane 算法:" << std::endl;
    SubarrayResult result2 = kadaneWithPosition(arr2);
    std::cout << "   最大子数组: ";
    printSubarray(arr2, result2.left_index, result2.right_index);
    std::cout << std::endl;
    std::cout << "   最大和: " << result2.max_sum << std::endl;
    
    // 测试用例3：全部为正数的数组
    std::vector<int> arr3 = {1, 2, 3, 4, 5};
    std::cout << "\n\n📝 测试用例 3 (全正数):" << std::endl;
    std::cout << "   数组: ";
    printArray(arr3);
    std::cout << std::endl;
    
    std::cout << "\n🔷 使用增强版 Kadane 算法:" << std::endl;
    SubarrayResult result3 = kadaneWithPosition(arr3);
    std::cout << "   最大子数组: ";
    printSubarray(arr3, result3.left_index, result3.right_index);
    std::cout << std::endl;
    std::cout << "   最大和: " << result3.max_sum << std::endl;
    
    std::cout << "\n========================================" << std::endl;
    std::cout << "           算法复杂度分析               " << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "⏱️  时间复杂度: O(n) - 只需要遍历数组一次" << std::endl;
    std::cout << "💾 空间复杂度: O(1) - 只使用了常数个额外变量" << std::endl;
    std::cout << "🧠 算法思想: 动态规划" << std::endl;
    
    std::cout << "\n========================================" << std::endl;
    std::cout << "           算法核心思想总结             " << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "1. 对于每个元素，我们决定是将其加入当前子数组还是以它开始新的子数组" << std::endl;
    std::cout << "2. 如果前面的累积和是负数，那么加上它只会让总和变小，不如重新开始" << std::endl;
    std::cout << "3. 我们始终保持追踪到目前为止见过的最大和" << std::endl;
    std::cout << "4. 这样一遍扫描就能得到最终结果，非常高效" << std::endl;
    
    return 0;
}