//
// Created by HaPpY on 2025/12/9.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

/**
 * 结果结构体，用于存储最大子数组的信息
 */
struct SubarrayResult {
    int left_index;   // 最大子数组的左边界索移
    int right_index;  // 最大子数组的右边界索引
    int max_sum;      // 最大子数组的和
    
    // 构造函数
    SubarrayResult(int left, int right, int sum) : left_index(left), right_index(right), max_sum(sum) {}
};

/**
 * 寻找非环形数组中的最大子数组（标准 Kadane 算法）
 * 
 * @param arr 输入数组
 * @return 最大子数组结果
 */
SubarrayResult kadane(const std::vector<int>& arr) {
    int max_current = arr[0];
    int max_global = arr[0];
    int left_index = 0;
    int right_index = 0;
    int temp_left = 0;
    
    for (size_t i = 1; i < arr.size(); i++) {
        if (arr[i] > max_current + arr[i]) {
            max_current = arr[i];
            temp_left = i;
        } else {
            max_current = max_current + arr[i];
        }
        
        if (max_current > max_global) {
            max_global = max_current;
            left_index = temp_left;
            right_index = i;
        }
    }
    
    return SubarrayResult(left_index, right_index, max_global);
}

/**
 * 寻找非环形数组中的最小子数组（反向 Kadane 算法）
 * 
 * @param arr 输入数组
 * @return 最小子数组结果
 */
SubarrayResult reverseKadane(const std::vector<int>& arr) {
    int min_current = arr[0];
    int min_global = arr[0];
    int left_index = 0;
    int right_index = 0;
    int temp_left = 0;
    
    for (size_t i = 1; i < arr.size(); i++) {
        if (arr[i] < min_current + arr[i]) {
            min_current = arr[i];
            temp_left = i;
        } else {
            min_current = min_current + arr[i];
        }
        
        if (min_current < min_global) {
            min_global = min_current;
            left_index = temp_left;
            right_index = i;
        }
    }
    
    return SubarrayResult(left_index, right_index, min_global);
}

/**
 * 方法一：暴力解法
 * 遍历所有可能的子数组，包括环形情况
 * 
 * @param arr 输入数组
 * @return 最大子数组结果
 * 
 * 📌 算法原理:
 * 1. 对于环形数组，子数组可能是连续的一段，也可能是跨越首尾的两段
 * 2. 使用三层循环遍历所有可能的情况
 * 3. 计算每种子数组的和，找出最大值
 * 
 * ⏱️ 时间复杂度: O(n³)
 * 💾 空间复杂度: O(1)
 */
SubarrayResult maxSubarraySumCircularBruteForce(std::vector<int>& arr) {
    int n = arr.size();
    int max_sum = INT_MIN;
    int left_index = 0;
    int right_index = 0;
    
    std::cout << "🔍 暴力解法开始执行：" << std::endl;
    
    // 遍历所有可能的子数组
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int sum = 0;
            
            // 计算从 i 到 j 的子数组和（考虑环形）
            if (i <= j) {
                // 非环形情况：从 i 到 j
                for (int k = i; k <= j; k++) {
                    sum += arr[k];
                }
            } else {
                // 环形情况：从 i 到末尾 + 从开头到 j
                for (int k = i; k < n; k++) {
                    sum += arr[k];
                }
                for (int k = 0; k <= j; k++) {
                    sum += arr[k];
                }
            }
            
            std::cout << "   子数组从索引 " << i << " 到 " << j << " 的和: " << sum << std::endl;
            
            // 更新最大和
            if (sum > max_sum) {
                max_sum = sum;
                left_index = i;
                right_index = j;
                std::cout << "   🎯 发现新的最大和: " << max_sum << std::endl;
            }
        }
    }
    
    return SubarrayResult(left_index, right_index, max_sum);
}

/**
 * 方法二：优化的暴力解法
 * 使用前缀和优化子数组和的计算
 * 
 * @param arr 输入数组
 * @return 最大子数组结果
 * 
 * 📌 算法原理:
 * 1. 预计算前缀和数组
 * 2. 利用前缀和快速计算任意子数组的和
 * 3. 遍历所有可能的子数组情况
 * 
 * ⏱️ 时间复杂度: O(n²)
 * 💾 空间复杂度: O(n)
 */
SubarrayResult maxSubarraySumCircularOptimizedBruteForce(std::vector<int>& arr) {
    int n = arr.size();
    int max_sum = INT_MIN;
    int left_index = 0;
    int right_index = 0;
    
    // 计算前缀和数组
    std::vector<int> prefix_sum(n);
    prefix_sum[0] = arr[0];
    for (int i = 1; i < n; i++) {
        prefix_sum[i] = prefix_sum[i-1] + arr[i];
    }
    
    std::cout << "🔍 优化暴力解法开始执行：" << std::endl;
    
    // 遍历所有可能的子数组
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int sum = 0;
            
            // 利用前缀和计算子数组和
            if (i <= j) {
                // 非环形情况
                sum = (i == 0) ? prefix_sum[j] : prefix_sum[j] - prefix_sum[i-1];
            } else {
                // 环形情况：总和减去中间部分的和
                sum = prefix_sum[n-1] - (prefix_sum[i-1] - prefix_sum[j]);
            }
            
            std::cout << "   子数组从索引 " << i << " 到 " << j << " 的和: " << sum << std::endl;
            
            // 更新最大和
            if (sum > max_sum) {
                max_sum = sum;
                left_index = i;
                right_index = j;
                std::cout << "   🎯 发现新的最大和: " << max_sum << std::endl;
            }
        }
    }
    
    return SubarrayResult(left_index, right_index, max_sum);
}

/**
 * 方法三：Kadane 算法 + 数学技巧
 * 利用环形数组的特点：最大子数组要么是普通子数组，要么是跨越首尾的子数组
 * 
 * @param arr 输入数组
 * @return 最大子数组结果
 * 
 * 📌 算法原理:
 * 环形数组中的最大子数组只有两种可能：
 * 1. 普通子数组（不跨越首尾）- 直接使用 Kadane 算法
 * 2. 环形子数组（跨越首尾）- 等价于总和减去最小子数组
 * 
 * 证明：如果最大子数组跨越首尾，那么未被选中的中间部分就是最小子数组
 * 
 * ⏱️ 时间复杂度: O(n)
 * 💾 空间复杂度: O(1)
 */
SubarrayResult maxSubarraySumCircularKadane(std::vector<int>& arr) {
    int n = arr.size();
    
    std::cout << "🔍 Kadane 算法解法开始执行：" << std::endl;
    
    // 情况1：普通的最大子数组（不跨越首尾）
    SubarrayResult normal_max = kadane(arr);
    std::cout << "   普通最大子数组和: " << normal_max.max_sum << std::endl;
    
    // 计算数组总和
    int total_sum = 0;
    for (int i = 0; i < n; i++) {
        total_sum += arr[i];
    }
    std::cout << "   数组总和: " << total_sum << std::endl;
    
    // 情况2：环形最大子数组（跨越首尾）
    // 等价于：总和 - 最小子数组和
    SubarrayResult normal_min = reverseKadane(arr);
    int circular_max = total_sum - normal_min.max_sum;
    std::cout << "   最小子数组和: " << normal_min.max_sum << std::endl;
    std::cout << "   环形最大子数组和: " << circular_max << std::endl;
    
    // 特殊情况：如果所有元素都是负数，环形最大值为0（空数组）
    // 但我们不允许空数组，所以应该返回普通最大值
    if (circular_max == 0) {
        std::cout << "   🔄 特殊情况：所有元素都是负数，返回普通最大值" << std::endl;
        return normal_max;
    }
    
    // 返回两种情况的最大值
    if (normal_max.max_sum >= circular_max) {
        std::cout << "   🎯 普通最大子数组更大: " << normal_max.max_sum << std::endl;
        return normal_max;
    } else {
        std::cout << "   🎯 环形最大子数组更大: " << circular_max << std::endl;
        // 环形情况下的索引需要特殊处理
        return SubarrayResult(normal_max.right_index + 1, normal_max.left_index - 1, circular_max);
    }
}

/**
 * 方法四：改进的 Kadane 算法
 * 一次遍历同时计算最大子数组和最小子数组
 * 
 * @param arr 输入数组
 * @return 最大子数组结果
 * 
 * 📌 算法原理:
 * 在一次遍历中同时维护：
 * 1. 以当前位置结尾的最大子数组和
 * 2. 以当前位置结尾的最小子数组和
 * 3. 到目前为止的最大子数组和
 * 4. 到目前为止的最小子数组和
 * 
 * ⏱️ 时间复杂度: O(n)
 * 💾 空间复杂度: O(1)
 */
SubarrayResult maxSubarraySumCircularImprovedKadane(std::vector<int>& arr) {
    int n = arr.size();
    if (n == 0) return SubarrayResult(0, 0, 0);
    
    std::cout << "🔍 改进 Kadane 算法解法开始执行：" << std::endl;
    
    // 初始化变量
    int max_ending_here = arr[0];  // 以当前位置结尾的最大子数组和
    int min_ending_here = arr[0];  // 以当前位置结尾的最小子数组和
    int max_so_far = arr[0];       // 到目前为止的最大子数组和
    int min_so_far = arr[0];       // 到目前为止的最小子数组和
    int total_sum = arr[0];        // 数组总和
    
    std::cout << "   初始状态 -> max_ending_here: " << max_ending_here 
              << ", min_ending_here: " << min_ending_here
              << ", max_so_far: " << max_so_far
              << ", min_so_far: " << min_so_far << std::endl;
    
    // 从第二个元素开始遍历
    for (int i = 1; i < n; i++) {
        std::cout << "   处理元素 arr[" << i << "] = " << arr[i] << std::endl;
        
        // 更新总和
        total_sum += arr[i];
        
        // 更新以当前位置结尾的最大子数组和和最小子数组和
        max_ending_here = std::max(arr[i], max_ending_here + arr[i]);
        min_ending_here = std::min(arr[i], min_ending_here + arr[i]);
        
        std::cout << "   更新后 -> max_ending_here: " << max_ending_here 
                  << ", min_ending_here: " << min_ending_here << std::endl;
        
        // 更新全局最大值和最小值
        max_so_far = std::max(max_so_far, max_ending_here);
        min_so_far = std::min(min_so_far, min_ending_here);
        
        std::cout << "   全局 -> max_so_far: " << max_so_far 
                  << ", min_so_far: " << min_so_far << std::endl;
    }
    
    std::cout << "   数组总和: " << total_sum << std::endl;
    
    // 特殊情况：如果所有元素都是负数，max_so_far 就是答案
    if (max_so_far < 0) {
        std::cout << "   🔄 特殊情况：所有元素都是负数，返回最大元素: " << max_so_far << std::endl;
        return kadane(arr);
    }
    
    // 返回普通最大子数组和环形最大子数组的最大值
    int circular_max = total_sum - min_so_far;
    std::cout << "   环形最大子数组和: " << circular_max << std::endl;
    
    if (max_so_far >= circular_max) {
        std::cout << "   🎯 普通最大子数组更大: " << max_so_far << std::endl;
        return kadane(arr);
    } else {
        std::cout << "   🎯 环形最大子数组更大: " << circular_max << std::endl;
        return SubarrayResult(0, 0, circular_max); // 环形情况下索引处理较为复杂
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
 * 打印环形子数组元素
 * @param arr 要打印的数组
 * @param left 左边界索引
 * @param right 右边界索引
 */
void printCircularSubarray(const std::vector<int>& arr, int left, int right) {
    std::cout << "[";
    if (left <= right) {
        // 非环形情况
        for (int i = left; i <= right; i++) {
            std::cout << arr[i];
            if (i < right) std::cout << ", ";
        }
    } else {
        // 环形情况
        for (int i = left; i < (int)arr.size(); i++) {
            std::cout << arr[i] << ", ";
        }
        for (int i = 0; i <= right; i++) {
            std::cout << arr[i];
            if (i < right) std::cout << ", ";
        }
    }
    std::cout << "]";
}

/**
 * 主函数，用于测试环形数组中的最大子数组算法
 */
int main() {
#ifdef ACM_LOCAL
    freopen("data.in", "r", stdin);
    freopen("data.out", "w", stdout);
#endif
    std::cout << "========================================" << std::endl;
    std::cout << "      环形数组中的最大子数组问题       " << std::endl;
    std::cout << "========================================" << std::endl;
    
    // 测试用例1：普通情况
    std::vector<int> arr1 = {1, -2, 3, -2};
    std::cout << "\n📝 测试用例 1:" << std::endl;
    std::cout << "   数组: ";
    printArray(arr1);
    std::cout << " (环形数组)" << std::endl;
    
    // 使用改进的 Kadane 算法（推荐）
    std::cout << "\n🔷 使用改进的 Kadane 算法:" << std::endl;
    SubarrayResult result1 = maxSubarraySumCircularImprovedKadane(arr1);
    std::cout << "   最大子数组: ";
    printCircularSubarray(arr1, result1.left_index, result1.right_index);
    std::cout << std::endl;
    std::cout << "   最大和: " << result1.max_sum << std::endl;
    
    // 测试用例2：环形情况更优
    std::vector<int> arr2 = {5, -3, 5};
    std::cout << "\n\n📝 测试用例 2:" << std::endl;
    std::cout << "   数组: ";
    printArray(arr2);
    std::cout << " (环形数组)" << std::endl;
    
    std::cout << "\n🔷 使用改进的 Kadane 算法:" << std::endl;
    SubarrayResult result2 = maxSubarraySumCircularImprovedKadane(arr2);
    std::cout << "   最大子数组: ";
    printCircularSubarray(arr2, result2.left_index, result2.right_index);
    std::cout << std::endl;
    std::cout << "   最大和: " << result2.max_sum << std::endl;
    
    // 测试用例3：所有元素都是负数
    std::vector<int> arr3 = {-3, -2, -3};
    std::cout << "\n\n📝 测试用例 3:" << std::endl;
    std::cout << "   数组: ";
    printArray(arr3);
    std::cout << " (环形数组)" << std::endl;
    
    std::cout << "\n🔷 使用改进的 Kadane 算法:" << std::endl;
    SubarrayResult result3 = maxSubarraySumCircularImprovedKadane(arr3);
    std::cout << "   最大子数组: ";
    printCircularSubarray(arr3, result3.left_index, result3.right_index);
    std::cout << std::endl;
    std::cout << "   最大和: " << result3.max_sum << std::endl;
    
    std::cout << "\n========================================" << std::endl;
    std::cout << "           算法复杂度分析               " << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "📊 暴力解法:           时间复杂度 O(n³), 空间复杂度 O(1)" << std::endl;
    std::cout << "📊 优化暴力解法:       时间复杂度 O(n²), 空间复杂度 O(n)" << std::endl;
    std::cout << "📊 Kadane 算法:        时间复杂度 O(n),  空间复杂度 O(1)" << std::endl;
    std::cout << "🏆 推荐使用 Kadane 算法，效率最高！" << std::endl;
    
    std::cout << "\n========================================" << std::endl;
    std::cout << "           算法核心思想总结             " << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "1. 环形数组中的最大子数组只有两种可能：" << std::endl;
    std::cout << "   - 普通子数组（不跨越首尾）" << std::endl;
    std::cout << "   - 环形子数组（跨越首尾）" << std::endl;
    std::cout << "2. 环形子数组的最大和等于数组总和减去最小子数组和" << std::endl;
    std::cout << "3. 特殊情况：当所有元素都是负数时，应返回最大的单个元素" << std::endl;
    std::cout << "4. Kadane 算法的巧妙应用使得我们能在 O(n) 时间内解决问题" << std::endl;
    
    return 0;
}