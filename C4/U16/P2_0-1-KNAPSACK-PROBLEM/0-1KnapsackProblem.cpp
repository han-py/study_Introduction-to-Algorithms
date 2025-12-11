//
// Created by HaPpY on 2025/12/11.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

/**
 * 物品结构体
 */
struct Item {
    int weight;  // 物品重量
    int value;   // 物品价值
    int id;      // 物品编号
    
    Item(int id, int weight, int value) : id(id), weight(weight), value(value) {}
};

/**
 * 方法一：暴力递归解法（指数时间复杂度）
 * 
 * @param items 物品列表
 * @param capacity 背包容量
 * @param n 当前考虑的物品数量
 * @return 最大价值
 */
int knapsackBruteForce(const std::vector<Item>& items, int capacity, int n) {
    // 基本情况：没有物品可选或背包容量为0
    if (n == 0 || capacity == 0) {
        return 0;
    }
    
    // 如果当前物品重量超过背包容量，则不能放入
    if (items[n-1].weight > capacity) {
        return knapsackBruteForce(items, capacity, n-1);
    } else {
        // 返回两种选择的最大值：
        // 1. 不放入当前物品
        // 2. 放入当前物品 + 剩余容量下的最大价值
        int withoutItem = knapsackBruteForce(items, capacity, n-1);
        int withItem = items[n-1].value + knapsackBruteForce(items, capacity - items[n-1].weight, n-1);
        return std::max(withoutItem, withItem);
    }
}

/**
 * 方法二：记忆化递归解法
 * 
 * @param items 物品列表
 * @param capacity 背包容量
 * @param n 当前考虑的物品数量
 * @param memo 记忆化表
 * @return 最大价值
 */
int knapsackMemoization(const std::vector<Item>& items, int capacity, int n, std::vector<std::vector<int>>& memo) {
    // 基本情况：没有物品可选或背包容量为0
    if (n == 0 || capacity == 0) {
        return 0;
    }
    
    // 如果已经计算过该状态，则直接返回结果
    if (memo[n][capacity] != -1) {
        return memo[n][capacity];
    }
    
    // 如果当前物品重量超过背包容量，则不能放入
    if (items[n-1].weight > capacity) {
        memo[n][capacity] = knapsackMemoization(items, capacity, n-1, memo);
    } else {
        // 返回两种选择的最大值：
        // 1. 不放入当前物品
        // 2. 放入当前物品 + 剩余容量下的最大价值
        int withoutItem = knapsackMemoization(items, capacity, n-1, memo);
        int withItem = items[n-1].value + knapsackMemoization(items, capacity - items[n-1].weight, n-1, memo);
        memo[n][capacity] = std::max(withoutItem, withItem);
    }
    
    return memo[n][capacity];
}

/**
 * 方法三：动态规划解法（二维DP表）
 * 
 * @param items 物品列表
 * @param capacity 背包容量
 * @return 最大价值
 */
int knapsackDP(const std::vector<Item>& items, int capacity) {
    int n = items.size();
    
    // 创建DP表，dp[i][w]表示前i个物品在容量为w的背包中的最大价值
    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(capacity + 1, 0));
    
    // 填充DP表
    for (int i = 1; i <= n; i++) {
        for (int w = 0; w <= capacity; w++) {
            // 如果当前物品重量超过背包容量，则不能放入
            if (items[i-1].weight > w) {
                dp[i][w] = dp[i-1][w];
            } else {
                // 返回两种选择的最大值：
                // 1. 不放入当前物品
                // 2. 放入当前物品 + 剩余容量下的最大价值
                int withoutItem = dp[i-1][w];
                int withItem = items[i-1].value + dp[i-1][w - items[i-1].weight];
                dp[i][w] = std::max(withoutItem, withItem);
            }
        }
    }
    
    return dp[n][capacity];
}

/**
 * 方法四：空间优化的动态规划解法（一维DP表）
 * 
 * @param items 物品列表
 * @param capacity 背包容量
 * @return 最大价值
 */
int knapsackDPOptimized(const std::vector<Item>& items, int capacity) {
    int n = items.size();
    
    // 创建一维DP表，dp[w]表示容量为w的背包中的最大价值
    std::vector<int> dp(capacity + 1, 0);
    
    // 填充DP表
    for (int i = 0; i < n; i++) {
        // 注意：必须从后往前遍历，避免重复使用同一个物品
        for (int w = capacity; w >= items[i].weight; w--) {
            dp[w] = std::max(dp[w], dp[w - items[i].weight] + items[i].value);
        }
    }
    
    return dp[capacity];
}

/**
 * 打印物品列表
 * 
 * @param items 物品列表
 */
void printItems(const std::vector<Item>& items) {
    std::cout << "物品列表:" << std::endl;
    std::cout << "编号\t重量\t价值" << std::endl;
    std::cout << "-------------------" << std::endl;
    for (const auto& item : items) {
        std::cout << item.id << "\t" << item.weight << "\t" << item.value << std::endl;
    }
    std::cout << std::endl;
}

/**
 * 打印二维DP表
 * 
 * @param dp DP表
 * @param items 物品列表
 * @param capacity 背包容量
 */
void printDPTable(const std::vector<std::vector<int>>& dp, const std::vector<Item>& items, int capacity) {
    int n = items.size();
    
    std::cout << "DP表 (行表示物品，列表示容量):" << std::endl;
    
    // 打印表头
    std::cout << "物品\\容量";
    for (int w = 0; w <= capacity; w++) {
        std::cout << std::setw(4) << w;
    }
    std::cout << std::endl;
    
    // 打印表内容
    for (int i = 0; i <= n; i++) {
        if (i == 0) {
            std::cout << "  0      ";
        } else {
            std::cout << std::setw(2) << items[i-1].id << "      ";
        }
        
        for (int w = 0; w <= capacity; w++) {
            std::cout << std::setw(4) << dp[i][w];
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

/**
 * 主函数 - 演示0-1背包问题的各种解法
 */
int main() {
#ifdef ACM_LOCAL
    freopen("data.in", "r", stdin);
    freopen("data.out", "w", stdout);
#endif
    std::cout << "==============================================" << std::endl;
    std::cout << "           0-1背包问题演示程序" << std::endl;
    std::cout << "==============================================" << std::endl;
    std::cout << "问题描述：" << std::endl;
    std::cout << "给定n个物品和一个容量为W的背包，每个物品有重量和价值，" << std::endl;
    std::cout << "求在不超过背包容量的前提下，能装入背包的物品的最大价值。" << std::endl;
    std::cout << "==============================================" << std::endl << std::endl;
    
    // 创建示例物品集合（《算法导论》习题示例）
    std::vector<Item> items = {
        Item(1, 10, 60),   // 物品1: 重量10, 价值60
        Item(2, 20, 100),  // 物品2: 重量20, 价值100
        Item(3, 30, 120),  // 物品3: 重量30, 价值120
    };
    
    int capacity = 50;  // 背包容量
    
    // 打印物品列表
    printItems(items);
    std::cout << "背包容量: " << capacity << std::endl << std::endl;
    
    // 方法一：暴力递归解法
    std::cout << "【方法一：暴力递归解法】" << std::endl;
    int result1 = knapsackBruteForce(items, capacity, items.size());
    std::cout << "最大价值: " << result1 << std::endl << std::endl;
    
    // 方法二：记忆化递归解法
    std::cout << "【方法二：记忆化递归解法】" << std::endl;
    std::vector<std::vector<int>> memo(items.size() + 1, std::vector<int>(capacity + 1, -1));
    int result2 = knapsackMemoization(items, capacity, items.size(), memo);
    std::cout << "最大价值: " << result2 << std::endl << std::endl;
    
    // 方法三：动态规划解法
    std::cout << "【方法三：动态规划解法】" << std::endl;
    int result3 = knapsackDP(items, capacity);
    std::cout << "最大价值: " << result3 << std::endl << std::endl;
    
    // 方法四：空间优化的动态规划解法
    std::cout << "【方法四：空间优化的动态规划解法】" << std::endl;
    int result4 = knapsackDPOptimized(items, capacity);
    std::cout << "最大价值: " << result4 << std::endl << std::endl;
    
    // 演示DP表填充过程
    std::cout << "【DP表填充过程演示】" << std::endl;
    int n = items.size();
    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(capacity + 1, 0));
    
    // 填充DP表并显示过程
    for (int i = 1; i <= n; i++) {
        for (int w = 0; w <= capacity; w++) {
            if (items[i-1].weight > w) {
                dp[i][w] = dp[i-1][w];
            } else {
                int withoutItem = dp[i-1][w];
                int withItem = items[i-1].value + dp[i-1][w - items[i-1].weight];
                dp[i][w] = std::max(withoutItem, withItem);
            }
        }
    }
    
    printDPTable(dp, items, capacity);
    
    std::cout << "==============================================" << std::endl;
    std::cout << "           算法执行完毕！" << std::endl;
    std::cout << "==============================================" << std::endl;
    
    return 0;
}