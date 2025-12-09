//
// Created by HaPpY on 2025/12/9.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <deque>

/**
 * 结果结构体，用于存储最大子数组的信息
 */
struct SubarrayResult {
    int left_index;   // 最大子数组的左边界索引
    int right_index;  // 最大子数组的右边界索引
    long long max_sum;      // 最大子数组的和
    int length;       // 子数组长度
    
    // 构造函数
    SubarrayResult(int left, int right, long long sum, int len) 
        : left_index(left), right_index(right), max_sum(sum), length(len) {}
};

/**
 * 方法一：暴力解法
 * 遍历所有长度至少为k的子数组，找出最大和
 * 
 * @param arr 输入数组
 * @param k 最少元素个数
 * @return 最大子数组结果
 * 
 * 📌 算法原理:
 * 1. 遍历所有长度至少为k的子数组
 * 2. 计算每个子数组的和
 * 3. 记录遇到的最大和
 * 
 * ⏱️ 时间复杂度: O(n³)
 * 💾 空间复杂度: O(1)
 */
SubarrayResult maxSubarraySumAtLeastKBruteForce(const std::vector<int>& arr, int k) {
    int n = arr.size();
    long long max_sum = LLONG_MIN;
    int left_index = 0;
    int right_index = 0;
    
    std::cout << "🔍 暴力解法开始执行（k=" << k << "）：" << std::endl;
    
    // 遍历所有长度至少为k的子数组
    for (int i = 0; i <= n - k; i++) {
        for (int j = i + k - 1; j < n; j++) {
            long long sum = 0;
            // 计算子数组 arr[i..j] 的和
            for (int l = i; l <= j; l++) {
                sum += arr[l];
            }
            
            std::cout << "   子数组 [" << i << ", " << j << "] 长度: " << (j-i+1) 
                      << ", 和: " << sum << std::endl;
            
            // 更新最大和
            if (sum > max_sum) {
                max_sum = sum;
                left_index = i;
                right_index = j;
                std::cout << "   🎯 发现新的最大和: " << max_sum << std::endl;
            }
        }
    }
    
    int length = right_index - left_index + 1;
    return SubarrayResult(left_index, right_index, max_sum, length);
}

/**
 * 方法二：优化的暴力解法
 * 利用前缀和避免重复计算子数组和
 * 
 * @param arr 输入数组
 * @param k 最少元素个数
 * @return 最大子数组结果
 * 
 * 📌 算法原理:
 * 1. 预计算前缀和数组
 * 2. 利用前缀和快速计算任意子数组的和
 * 3. 遍历所有长度至少为k的子数组
 * 
 * ⏱️ 时间复杂度: O(n²)
 * 💾 空间复杂度: O(n)
 */
SubarrayResult maxSubarraySumAtLeastKOptimizedBruteForce(const std::vector<int>& arr, int k) {
    int n = arr.size();
    long long max_sum = LLONG_MIN;
    int left_index = 0;
    int right_index = 0;
    
    // 计算前缀和数组
    std::vector<long long> prefix_sum(n + 1, 0);
    for (int i = 0; i < n; i++) {
        prefix_sum[i + 1] = prefix_sum[i] + arr[i];
    }
    
    std::cout << "🔍 优化暴力解法开始执行（k=" << k << "）：" << std::endl;
    
    // 遍历所有长度至少为k的子数组
    for (int i = 0; i <= n - k; i++) {
        for (int j = i + k - 1; j < n; j++) {
            // 利用前缀和计算子数组和
            long long sum = prefix_sum[j + 1] - prefix_sum[i];
            
            std::cout << "   子数组 [" << i << ", " << j << "] 长度: " << (j-i+1) 
                      << ", 和: " << sum << std::endl;
            
            // 更新最大和
            if (sum > max_sum) {
                max_sum = sum;
                left_index = i;
                right_index = j;
                std::cout << "   🎯 发现新的最大和: " << max_sum << std::endl;
            }
        }
    }
    
    int length = right_index - left_index + 1;
    return SubarrayResult(left_index, right_index, max_sum, length);
}

/**
 * 方法三：滑动窗口 + Kadane 算法
 * 对于每个长度l（l≥k），使用滑动窗口找到最大和，然后取所有长度的最大值
 * 
 * @param arr 输入数组
 * @param k 最少元素个数
 * @return 最大子数组结果
 * 
 * 📌 算法原理:
 * 1. 对于每个可能的长度l（从k到n）
 * 2. 使用滑动窗口找到长度为l的最大子数组和
 * 3. 在所有长度的结果中取最大值
 * 
 * ⏱️ 时间复杂度: O(n²)
 * 💾 空间复杂度: O(1)
 */
SubarrayResult maxSubarraySumAtLeastKSlidingWindow(const std::vector<int>& arr, int k) {
    int n = arr.size();
    long long max_sum = LLONG_MIN;
    int left_index = 0;
    int right_index = 0;
    int final_length = 0;
    
    std::cout << "🔍 滑动窗口解法开始执行（k=" << k << "）：" << std::endl;
    
    // 对于每个长度l（从k到n）
    for (int l = k; l <= n; l++) {
        std::cout << "   处理长度为 " << l << " 的子数组：" << std::endl;
        
        // 计算第一个长度为l的窗口的和
        long long window_sum = 0;
        for (int i = 0; i < l; i++) {
            window_sum += arr[i];
        }
        
        long long max_window_sum = window_sum;
        int max_window_start = 0;
        
        std::cout << "     窗口 [" << 0 << ", " << (l-1) << "] 和: " << window_sum << std::endl;
        
        // 滑动窗口
        for (int i = l; i < n; i++) {
            // 移除左边元素，添加右边元素
            window_sum = window_sum - arr[i - l] + arr[i];
            
            std::cout << "     窗口 [" << (i-l+1) << ", " << i << "] 和: " << window_sum << std::endl;
            
            if (window_sum > max_window_sum) {
                max_window_sum = window_sum;
                max_window_start = i - l + 1;
                std::cout << "     🎯 长度为 " << l << " 的窗口中发现最大和: " << max_window_sum << std::endl;
            }
        }
        
        // 更新全局最大和
        if (max_window_sum > max_sum) {
            max_sum = max_window_sum;
            left_index = max_window_start;
            right_index = max_window_start + l - 1;
            final_length = l;
            std::cout << "   🎯 发现新的全局最大和: " << max_sum << std::endl;
        }
    }
    
    return SubarrayResult(left_index, right_index, max_sum, final_length);
}

/**
 * 方法四：优化的动态规划解法
 * 使用前缀和 + deque 维护最小前缀和，实现O(n)时间复杂度
 * 
 * @param arr 输入数组
 * @param k 最少元素个数
 * @return 最大子数组结果
 * 
 * 📌 算法原理:
 * 1. 计算前缀和数组
 * 2. 对于每个位置i，我们需要找到前面位置j（j≤i-k）中前缀和最小的那个
 * 3. 使用单调双端队列维护可能的最小前缀和位置
 * 4. 最大子数组和 = prefix_sum[i+1] - min_prefix_sum
 * 
 * ⏱️ 时间复杂度: O(n)
 * 💾 空间复杂度: O(n)
 */
SubarrayResult maxSubarraySumAtLeastKOpmizedDP(const std::vector<int>& arr, int k) {
    int n = arr.size();
    if (n < k) return SubarrayResult(0, 0, 0, 0);
    
    // 计算前缀和数组
    std::vector<long long> prefix_sum(n + 1, 0);
    for (int i = 0; i < n; i++) {
        prefix_sum[i + 1] = prefix_sum[i] + arr[i];
    }
    
    std::cout << "🔍 优化动态规划解法开始执行（k=" << k << "）：" << std::endl;
    std::cout << "   前缀和数组: [";
    for (int i = 0; i <= n; i++) {
        std::cout << prefix_sum[i];
        if (i < n) std::cout << ", ";
    }
    std::cout << "]" << std::endl;
    
    long long max_sum = LLONG_MIN;
    int left_index = 0;
    int right_index = 0;
    int final_length = 0;
    
    // 使用双端队列维护可能的最小前缀和位置
    std::deque<int> dq;
    dq.push_back(0);  // 初始位置0
    
    // 从位置k开始遍历（确保子数组长度至少为k）
    for (int i = k; i <= n; i++) {
        // 移除超出范围的索引（我们只需要j <= i-k的位置）
        while (!dq.empty() && dq.front() < i - k) {
            dq.pop_front();
        }
        
        // 计算以位置i结尾、长度至少为k的最大子数组和
        long long current_sum = prefix_sum[i] - prefix_sum[dq.front()];
        std::cout << "   以位置 " << (i-1) << " 结尾的长度至少为 " << k 
                  << " 的最大子数组和: " << current_sum << std::endl;
        
        if (current_sum > max_sum) {
            max_sum = current_sum;
            right_index = i - 1;
            left_index = dq.front();
            final_length = i - dq.front();
            std::cout << "   🎯 发现新的最大和: " << max_sum 
                      << ", 子数组 [" << left_index << ", " << right_index << "]" << std::endl;
        }
        
        // 维护双端队列的单调性（保持递增）
        while (!dq.empty() && prefix_sum[dq.back()] >= prefix_sum[i - k + 1]) {
            dq.pop_back();
        }
        
        // 添加新的候选位置
        if (i - k + 1 >= 0) {
            dq.push_back(i - k + 1);
        }
    }
    
    return SubarrayResult(left_index, right_index, max_sum, final_length);
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
 * 主函数，用于测试至少包含k个元素的最大子数组算法
 */
int main() {
#ifdef ACM_LOCAL
    freopen("data.in", "r", stdin);
    freopen("data.out", "w", stdout);
#endif
    std::cout << "========================================" << std::endl;
    std::cout << "    至少包含k个元素的最大子数组问题     " << std::endl;
    std::cout << "========================================" << std::endl;
    
    // 测试用例1：普通情况
    std::vector<int> arr1 = {1, 2, 3, -10, 2, 3};
    int k1 = 3;
    std::cout << "\n📝 测试用例 1:" << std::endl;
    std::cout << "   数组: ";
    printArray(arr1);
    std::cout << ", k = " << k1 << std::endl;
    
    // 使用优化的动态规划算法（推荐）
    std::cout << "\n🔷 使用优化的动态规划算法:" << std::endl;
    SubarrayResult result1 = maxSubarraySumAtLeastKOpmizedDP(arr1, k1);
    std::cout << "   最大子数组: ";
    printSubarray(arr1, result1.left_index, result1.right_index);
    std::cout << std::endl;
    std::cout << "   子数组长度: " << result1.length << std::endl;
    std::cout << "   最大和: " << result1.max_sum << std::endl;
    
    // 测试用例2：包含负数的情况
    std::vector<int> arr2 = {-5, -4, -3, 10, 1, 2};
    int k2 = 4;
    std::cout << "\n\n📝 测试用例 2:" << std::endl;
    std::cout << "   数组: ";
    printArray(arr2);
    std::cout << ", k = " << k2 << std::endl;
    
    std::cout << "\n🔷 使用优化的动态规划算法:" << std::endl;
    SubarrayResult result2 = maxSubarraySumAtLeastKOpmizedDP(arr2, k2);
    std::cout << "   最大子数组: ";
    printSubarray(arr2, result2.left_index, result2.right_index);
    std::cout << std::endl;
    std::cout << "   子数组长度: " << result2.length << std::endl;
    std::cout << "   最大和: " << result2.max_sum << std::endl;
    
    // 测试用例3：全负数情况
    std::vector<int> arr3 = {-1, -2, -3, -4, -5};
    int k3 = 2;
    std::cout << "\n\n📝 测试用例 3:" << std::endl;
    std::cout << "   数组: ";
    printArray(arr3);
    std::cout << ", k = " << k3 << std::endl;
    
    std::cout << "\n🔷 使用优化的动态规划算法:" << std::endl;
    SubarrayResult result3 = maxSubarraySumAtLeastKOpmizedDP(arr3, k3);
    std::cout << "   最大子数组: ";
    printSubarray(arr3, result3.left_index, result3.right_index);
    std::cout << std::endl;
    std::cout << "   子数组长度: " << result3.length << std::endl;
    std::cout << "   最大和: " << result3.max_sum << std::endl;
    
    std::cout << "\n========================================" << std::endl;
    std::cout << "           算法复杂度分析               " << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "📊 暴力解法:           时间复杂度 O(n³), 空间复杂度 O(1)" << std::endl;
    std::cout << "📊 优化暴力解法:       时间复杂度 O(n²), 空间复杂度 O(n)" << std::endl;
    std::cout << "📊 滑动窗口解法:       时间复杂度 O(n²), 空间复杂度 O(1)" << std::endl;
    std::cout << "📊 优化动态规划解法:   时间复杂度 O(n),  空间复杂度 O(n)" << std::endl;
    std::cout << "🏆 推荐使用优化动态规划解法，效率最高！" << std::endl;
    
    std::cout << "\n========================================" << std::endl;
    std::cout << "           算法核心思想总结             " << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "1. 问题增加了一个约束条件：子数组长度至少为k" << std::endl;
    std::cout << "2. 暴力解法通过枚举所有满足条件的子数组来解决问题" << std::endl;
    std::cout << "3. 优化解法利用前缀和避免重复计算" << std::endl;
    std::cout << "4. 最优解法使用单调双端队列维护最小前缀和位置，实现线性时间复杂度" << std::endl;
    std::cout << "5. 关键思想：最大子数组和 = 当前前缀和 - 之前最小前缀和" << std::endl;
    
    return 0;
}