//
// Created by HaPpY on 2025/12/9.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

/**
 * 结果结构体，用于存储最大子数组乘积的信息
 */
struct ProductResult {
    int left_index;    // 最大子数组的左边界索引
    int right_index;   // 最大子数组的右边界索引
    long long max_product;  // 最大子数组的乘积
    
    // 构造函数
    ProductResult(int left, int right, long long product) 
        : left_index(left), right_index(right), max_product(product) {}
};

/**
 * 方法一：暴力解法
 * 遍历所有可能的子数组，计算它们的乘积，找出最大值
 * 
 * @param arr 输入数组
 * @return 最大子数组乘积结果
 * 
 * 📌 算法原理:
 * 1. 使用三层循环遍历所有可能的子数组
 * 2. 对每个子数组计算乘积
 * 3. 记录遇到的最大乘积及其位置
 * 
 * ⏱️ 时间复杂度: O(n³)
 * 💾 空间复杂度: O(1)
 */
ProductResult maxSubarrayProductBruteForce(const std::vector<int>& arr) {
    int n = arr.size();
    long long max_product = LLONG_MIN;
    int left_index = 0;
    int right_index = 0;
    
    std::cout << "🔍 暴力解法开始执行：" << std::endl;
    
    // 遍历所有可能的子数组
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            long long product = 1;
            // 计算子数组 arr[i..j] 的乘积
            for (int k = i; k <= j; k++) {
                product *= arr[k];
            }
            
            std::cout << "   子数组 [" << i << ", " << j << "] 的乘积: " << product << std::endl;
            
            // 更新最大乘积
            if (product > max_product) {
                max_product = product;
                left_index = i;
                right_index = j;
                std::cout << "   🎯 发现新的最大乘积: " << max_product << std::endl;
            }
        }
    }
    
    return ProductResult(left_index, right_index, max_product);
}

/**
 * 方法二：优化的暴力解法
 * 在计算子数组乘积时利用之前计算的结果
 * 
 * @param arr 输入数组
 * @return 最大子数组乘积结果
 * 
 * 📌 算法原理:
 * 1. 使用两层循环遍历所有可能的子数组
 * 2. 在扩展子数组时累乘，避免重复计算
 * 
 * ⏱️ 时间复杂度: O(n²)
 * 💾 空间复杂度: O(1)
 */
ProductResult maxSubarrayProductOptimizedBruteForce(const std::vector<int>& arr) {
    int n = arr.size();
    long long max_product = LLONG_MIN;
    int left_index = 0;
    int right_index = 0;
    
    std::cout << "🔍 优化暴力解法开始执行：" << std::endl;
    
    // 遍历所有可能的起始位置
    for (int i = 0; i < n; i++) {
        long long product = 1;
        // 从起始位置开始逐步扩展子数组
        for (int j = i; j < n; j++) {
            product *= arr[j];  // 累乘下一个元素
            
            std::cout << "   子数组 [" << i << ", " << j << "] 的乘积: " << product << std::endl;
            
            // 更新最大乘积
            if (product > max_product) {
                max_product = product;
                left_index = i;
                right_index = j;
                std::cout << "   🎯 发现新的最大乘积: " << max_product << std::endl;
            }
        }
    }
    
    return ProductResult(left_index, right_index, max_product);
}

/**
 * 方法三：动态规划解法（类似 Kadane 算法的变体）
 * 维护当前位置的最大值和最小值，因为负数的存在可能导致最小值变成最大值
 * 
 * @param arr 输入数组
 * @return 最大子数组乘积结果
 * 
 * 📌 算法原理:
 * 1. 由于负数的存在，最大值和最小值可能会相互转换
 * 2. 在每个位置，我们需要跟踪：
 *    - 以当前位置结尾的最大乘积
 *    - 以当前位置结尾的最小乘积
 * 3. 当遇到负数时，最大值和最小值会交换角色
 * 
 * ⏱️ 时间复杂度: O(n)
 * 💾 空间复杂度: O(1)
 */
ProductResult maxSubarrayProductDP(const std::vector<int>& arr) {
    int n = arr.size();
    if (n == 0) return ProductResult(0, 0, 0);
    
    // 初始化变量
    long long max_ending_here = arr[0];  // 以当前位置结尾的最大乘积
    long long min_ending_here = arr[0];  // 以当前位置结尾的最小乘积
    long long max_so_far = arr[0];       // 到目前为止的最大乘积
    int left_index = 0;                  // 最大子数组的起始位置
    int right_index = 0;                 // 最大子数组的结束位置
    int temp_left = 0;                   // 临时记录当前子数组的起始位置
    
    std::cout << "🔍 动态规划解法开始执行：" << std::endl;
    std::cout << "   初始状态 -> max_ending_here: " << max_ending_here 
              << ", min_ending_here: " << min_ending_here
              << ", max_so_far: " << max_so_far << std::endl;
    
    // 从第二个元素开始遍历
    for (int i = 1; i < n; i++) {
        std::cout << "   处理元素 arr[" << i << "] = " << arr[i] << std::endl;
        
        // 如果当前元素是负数，交换最大值和最小值
        // 因为负数会让大的数变小，小的数变大
        if (arr[i] < 0) {
            std::cout << "   💡 当前元素为负数，交换最大值和最小值" << std::endl;
            std::swap(max_ending_here, min_ending_here);
        }
        
        // 计算以当前位置结尾的最大乘积和最小乘积
        long long temp_max = max_ending_here;
        max_ending_here = std::max((long long)arr[i], max_ending_here * arr[i]);
        min_ending_here = std::min((long long)arr[i], min_ending_here * arr[i]);
        
        std::cout << "   更新后 -> max_ending_here: " << max_ending_here 
                  << ", min_ending_here: " << min_ending_here << std::endl;
        
        // 更新全局最大乘积
        if (max_ending_here > max_so_far) {
            max_so_far = max_ending_here;
            left_index = temp_left;
            right_index = i;
            std::cout << "   🎯 发现新的最大乘积: " << max_so_far 
                      << ", 子数组位置: [" << left_index << ", " << right_index << "]" << std::endl;
        }
        
        // 如果当前元素比之前的乘积更大，重新开始
        if (arr[i] > temp_max * arr[i]) {
            temp_left = i;
            std::cout << "   🔄 重新开始子数组，新起始位置: " << temp_left << std::endl;
        }
    }
    
    return ProductResult(left_index, right_index, max_so_far);
}

/**
 * 方法四：改进的动态规划解法
 * 分别追踪最大值和最小值，不进行交换操作
 * 
 * @param arr 输入数组
 * @return 最大子数组乘积结果
 * 
 * 📌 算法原理:
 * 1. 在每个位置，新的最大值可能是：
 *    - 当前元素本身
 *    - 当前元素与之前最大值的乘积
 *    - 当前元素与之前最小值的乘积（当两者都是负数时）
 * 2. 类似地，新的最小值也可能是上述三种情况之一
 * 
 * ⏱️ 时间复杂度: O(n)
 * 💾 空间复杂度: O(1)
 */
ProductResult maxSubarrayProductImprovedDP(const std::vector<int>& arr) {
    int n = arr.size();
    if (n == 0) return ProductResult(0, 0, 0);
    
    // 初始化变量
    long long max_ending_here = arr[0];  // 以当前位置结尾的最大乘积
    long long min_ending_here = arr[0];  // 以当前位置结尾的最小乘积
    long long max_so_far = arr[0];       // 到目前为止的最大乘积
    int left_index = 0;                  // 最大子数组的起始位置
    int right_index = 0;                 // 最大子数组的结束位置
    int temp_left = 0;                   // 临时记录当前子数组的起始位置
    
    std::cout << "🔍 改进动态规划解法开始执行：" << std::endl;
    std::cout << "   初始状态 -> max_ending_here: " << max_ending_here 
              << ", min_ending_here: " << min_ending_here
              << ", max_so_far: " << max_so_far << std::endl;
    
    // 从第二个元素开始遍历
    for (int i = 1; i < n; i++) {
        std::cout << "   处理元素 arr[" << i << "] = " << arr[i] << std::endl;
        
        // 保存当前的最大值和最小值，因为后面会被更新
        long long temp_max = max_ending_here;
        long long temp_min = min_ending_here;
        
        // 计算三种可能的值
        long long choice1 = arr[i];                    // 当前元素本身
        long long choice2 = temp_max * arr[i];         // 之前最大值与当前元素的乘积
        long long choice3 = temp_min * arr[i];         // 之前最小值与当前元素的乘积
        
        std::cout << "   三种选择: " << choice1 << ", " << choice2 << ", " << choice3 << std::endl;
        
        // 更新以当前位置结尾的最大乘积和最小乘积
        max_ending_here = std::max(choice1, std::max(choice2, choice3));
        min_ending_here = std::min(choice1, std::min(choice2, choice3));
        
        std::cout << "   更新后 -> max_ending_here: " << max_ending_here 
                  << ", min_ending_here: " << min_ending_here << std::endl;
        
        // 更新全局最大乘积和位置
        if (max_ending_here > max_so_far) {
            max_so_far = max_ending_here;
            left_index = temp_left;
            right_index = i;
            std::cout << "   🎯 发现新的最大乘积: " << max_so_far 
                      << ", 子数组位置: [" << left_index << ", " << right_index << "]" << std::endl;
        }
        
        // 更新起始位置
        if (choice1 >= choice2 && choice1 >= choice3) {
            temp_left = i;
            std::cout << "   🔄 重新开始子数组，新起始位置: " << temp_left << std::endl;
        }
    }
    
    return ProductResult(left_index, right_index, max_so_far);
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
 * 主函数，用于测试最大子数组乘积算法
 */
int main() {
#ifdef ACM_LOCAL
    freopen("data.in", "r", stdin);
    freopen("data.out", "w", stdout);
#endif
    std::cout << "========================================" << std::endl;
    std::cout << "        最大子数组乘积问题详解          " << std::endl;
    std::cout << "========================================" << std::endl;
    
    // 测试用例1：包含负数的数组
    std::vector<int> arr1 = {2, 3, -2, 4};
    std::cout << "\n📝 测试用例 1:" << std::endl;
    std::cout << "   数组: ";
    printArray(arr1);
    std::cout << std::endl;
    
    // 使用改进的动态规划算法（推荐）
    std::cout << "\n🔷 使用改进的动态规划算法:" << std::endl;
    ProductResult result1 = maxSubarrayProductImprovedDP(arr1);
    std::cout << "   最大子数组: ";
    printSubarray(arr1, result1.left_index, result1.right_index);
    std::cout << std::endl;
    std::cout << "   最大乘积: " << result1.max_product << std::endl;
    
    // 测试用例2：包含负数的数组
    std::vector<int> arr2 = {-2, 0, -1};
    std::cout << "\n\n📝 测试用例 2:" << std::endl;
    std::cout << "   数组: ";
    printArray(arr2);
    std::cout << std::endl;
    
    std::cout << "\n🔷 使用改进的动态规划算法:" << std::endl;
    ProductResult result2 = maxSubarrayProductImprovedDP(arr2);
    std::cout << "   最大子数组: ";
    printSubarray(arr2, result2.left_index, result2.right_index);
    std::cout << std::endl;
    std::cout << "   最大乘积: " << result2.max_product << std::endl;
    
    // 测试用例3：包含多个负数的数组
    std::vector<int> arr3 = {-2, 3, -4};
    std::cout << "\n\n📝 测试用例 3:" << std::endl;
    std::cout << "   数组: ";
    printArray(arr3);
    std::cout << std::endl;
    
    std::cout << "\n🔷 使用改进的动态规划算法:" << std::endl;
    ProductResult result3 = maxSubarrayProductImprovedDP(arr3);
    std::cout << "   最大子数组: ";
    printSubarray(arr3, result3.left_index, result3.right_index);
    std::cout << std::endl;
    std::cout << "   最大乘积: " << result3.max_product << std::endl;
    
    std::cout << "\n========================================" << std::endl;
    std::cout << "           算法复杂度分析               " << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "📊 暴力解法:       时间复杂度 O(n³), 空间复杂度 O(1)" << std::endl;
    std::cout << "📊 优化暴力解法:   时间复杂度 O(n²), 空间复杂度 O(1)" << std::endl;
    std::cout << "📊 动态规划解法:   时间复杂度 O(n),  空间复杂度 O(1)" << std::endl;
    std::cout << "🏆 推荐使用动态规划解法，效率最高！" << std::endl;
    
    std::cout << "\n========================================" << std::endl;
    std::cout << "           算法核心思想总结             " << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "1. 与最大子数组和问题不同，乘积问题需要同时跟踪最大值和最小值" << std::endl;
    std::cout << "2. 负数的存在使得最大值和最小值可能相互转换" << std::endl;
    std::cout << "3. 在每个位置，新的最大值可能是当前元素、与之前最大值的乘积或与之前最小值的乘积" << std::endl;
    std::cout << "4. 动态规划方法通过保存中间结果避免重复计算，达到线性时间复杂度" << std::endl;
    
    return 0;
}