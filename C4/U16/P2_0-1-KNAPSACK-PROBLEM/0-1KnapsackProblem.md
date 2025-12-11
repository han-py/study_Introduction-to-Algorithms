# 0-1背包问题 (0-1 Knapsack Problem)

## 1. 算法简介

0-1背包问题是动态规划中的一个经典问题，也是《算法导论》中讨论的重要优化问题之一。问题的描述如下：

> 给定n个物品和一个容量为W的背包，每个物品i都有一个重量wᵢ和一个价值vᵢ。在限定的总重量W内，我们选择一些物品装入背包，使得装入背包的物品总价值最大。注意，每个物品只能选择0个或1个（即不能选择部分物品），这就是"0-1"名称的由来。

这是一个NP-hard问题，具有最优子结构性质，适合使用动态规划来解决。

## 2. 算法思想

0-1背包问题的核心思想是：对于每个物品，我们都面临一个选择——放入背包或者不放入背包。我们需要在这两种选择中做出决策，使得最终获得的价值最大。

令K(i,w)表示在前i个物品中选择，且背包容量为w时能获得的最大价值，则有状态转移方程：

```
K(i,w) = max{
    K(i-1,w),                           // 不选择第i个物品
    K(i-1,w-wᵢ) + vᵢ                    // 选择第i个物品（前提是wᵢ≤w）
}
```

边界条件为：
- K(0,w) = 0 （没有物品可选时价值为0）
- K(i,0) = 0 （背包容量为0时价值为0）

## 3. 算法步骤

### 3.1 暴力递归方法

1. 对于每个物品，考虑两种情况：选择该物品或不选择该物品
2. 递归地处理剩余物品和剩余容量
3. 返回两种情况下的最大值
4. 使用基本情况作为递归终止条件

### 3.2 记忆化递归方法

1. 在暴力递归的基础上，使用一个二维数组记录已计算过的状态
2. 在每次递归调用前，先检查该状态是否已计算过
3. 如果已计算过，则直接返回记录的结果
4. 否则，按暴力递归的方法计算，并将结果保存到记忆化表中

### 3.3 动态规划方法

1. 创建一个二维DP表，dp[i][w]表示前i个物品在容量为w的背包中的最大价值
2. 初始化边界条件：第一行和第一列为0
3. 按行填充DP表，每一格根据状态转移方程计算
4. 返回dp[n][W]作为最终结果

### 3.4 空间优化的动态规划方法

1. 观察到DP表中每一行的计算只依赖于上一行
2. 使用一维数组替代二维数组，节省空间
3. 在填充过程中从右向左遍历，避免重复使用同一物品

## 4. 算法图解示例

假设有以下3个物品和容量为50的背包：

| 物品编号 | 重量 | 价值 |
|---------|------|------|
| 1       | 10   | 60   |
| 2       | 20   | 100  |
| 3       | 30   | 120  |

### 4.1 DP表填充过程

我们将逐步填充DP表，其中dp[i][w]表示前i个物品在容量为w的背包中的最大价值：

1. 初始化：dp[0][w] = 0（没有物品可选），dp[i][0] = 0（背包容量为0）

2. 处理物品1（重量10，价值60）：
   - 对于w < 10：dp[1][w] = dp[0][w] = 0
   - 对于w ≥ 10：dp[1][w] = max(dp[0][w], dp[0][w-10] + 60) = 60

3. 处理物品2（重量20，价值100）：
   - 对于w < 20：dp[2][w] = dp[1][w]
   - 对于w ≥ 20：dp[2][w] = max(dp[1][w], dp[1][w-20] + 100)

4. 处理物品3（重量30，价值120）：
   - 对于w < 30：dp[3][w] = dp[2][w]
   - 对于w ≥ 30：dp[3][w] = max(dp[2][w], dp[2][w-30] + 120)

### 4.2 最终结果

通过完整的填表过程，我们得到最大价值为220，最优选择方案为选择物品2和物品3。

## 5. 伪代码实现

### 5.1 暴力递归方法

```
KNAPSACK-BRUTE-FORCE(values, weights, n, W)
1.  if n == 0 or W == 0
2.      return 0
3.  if weights[n-1] > W
4.      return KNAPSACK-BRUTE-FORCE(values, weights, n-1, W)
5.  else
6.      withoutItem = KNAPSACK-BRUTE-FORCE(values, weights, n-1, W)
7.      withItem = values[n-1] + KNAPSACK-BRUTE-FORCE(values, weights, n-1, W-weights[n-1])
8.      return max(withoutItem, withItem)
```

### 5.2 记忆化递归方法

```
KNAPSACK-MEMOIZATION(values, weights, n, W, memo)
1.  if n == 0 or W == 0
2.      return 0
3.  if memo[n][W] != -1
4.      return memo[n][W]
5.  if weights[n-1] > W
6.      memo[n][W] = KNAPSACK-MEMOIZATION(values, weights, n-1, W, memo)
7.  else
8.      withoutItem = KNAPSACK-MEMOIZATION(values, weights, n-1, W, memo)
9.      withItem = values[n-1] + KNAPSACK-MEMOIZATION(values, weights, n-1, W-weights[n-1], memo)
10.     memo[n][W] = max(withoutItem, withItem)
11. return memo[n][W]
```

### 5.3 动态规划方法

```
KNAPSACK-DP(values, weights, n, W)
1.  let dp[0..n][0..W] be a new array
2.  for i = 0 to n
3.      for w = 0 to W
4.          if i == 0 or w == 0
5.              dp[i][w] = 0
6.          else if weights[i-1] <= w
7.              dp[i][w] = max(dp[i-1][w], dp[i-1][w-weights[i-1]] + values[i-1])
8.          else
9.              dp[i][w] = dp[i-1][w]
10. return dp[n][W]
```

### 5.4 空间优化的动态规划方法

```
KNAPSACK-DP-OPTIMIZED(values, weights, n, W)
1.  let dp[0..W] be a new array
2.  for i = 0 to n-1
3.      for w = W downto weights[i]
4.          dp[w] = max(dp[w], dp[w-weights[i]] + values[i])
5.  return dp[W]
```

## 6. C++代码实现

### 6.1 暴力递归实现

```cpp
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
```

### 6.2 记忆化递归实现

```cpp
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
```

### 6.3 动态规划实现

```cpp
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
```

### 6.4 空间优化的动态规划实现

```cpp
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
```

## 7. 算法分析

### 7.1 时间复杂度

| 方法 | 时间复杂度 | 说明 |
|------|------------|------|
| 暴力递归 | O(2ⁿ) | 每个物品有两种选择，总共2ⁿ种组合 |
| 记忆化递归 | O(nW) | 总共有nW个状态，每个状态计算一次 |
| 动态规划 | O(nW) | 需要填充n×W的DP表 |
| 空间优化DP | O(nW) | 同样需要计算nW个状态 |

### 7.2 空间复杂度

| 方法 | 空间复杂度 | 说明 |
|------|------------|------|
| 暴力递归 | O(n) | 递归调用栈的深度 |
| 记忆化递归 | O(nW) | 需要n×W的记忆化表 |
| 动态规划 | O(nW) | 需要n×W的DP表 |
| 空间优化DP | O(W) | 只需要大小为W的一维数组 |

### 7.3 稳定性

0-1背包问题不是一个排序算法，因此不涉及稳定性概念。

## 8. 算法特点

### 8.1 优点

1. **适用性强**：可以解决各种资源分配和优化问题
2. **思路清晰**：状态转移方程直观易懂
3. **灵活性高**：容易扩展到其他变种问题
4. **理论完备**：具有坚实的数学基础和完整的理论体系

### 8.2 缺点

1. **时间复杂度高**：对于大数据集，O(nW)的时间复杂度可能仍然较高
2. **空间需求大**：标准DP方法需要O(nW)的空间
3. **仅适用于整数**：重量和容量必须是整数才有较好的效果

## 9. 适用场景

1. **资源分配**：在有限资源下选择最优的投资组合
2. **货物装载**：在载重限制下选择最有价值的货物
3. **项目选择**：在预算限制下选择收益最大的项目组合
4. **文件存储**：在存储空间限制下选择最重要的文件

## 10. 与其他算法比较

| 算法类型 | 时间复杂度 | 空间复杂度 | 特点 |
|---------|-----------|-----------|------|
| 暴力枚举 | O(2ⁿ) | O(n) | 简单但效率极低 |
| 动态规划 | O(nW) | O(nW) | 最常用的方法，效率适中 |
| 贪心算法 | O(n log n) | O(1) | 效率高但不能保证最优解 |
| 分支限界 | O(2ⁿ) | O(n) | 可以剪枝优化但仍为指数时间 |

## 11. 优化方案

### 11.1 空间优化

使用滚动数组或一维数组来减少空间复杂度，从O(nW)优化到O(W)。

### 11.2 时间优化

1. **预处理排序**：按价值密度排序可能有助于早期剪枝
2. **分支限界**：使用上界函数进行剪枝
3. **近似算法**：对于大规模问题可以使用贪心近似算法

### 11.3 平行化处理

对于大规模问题，可以考虑将不同的子问题分配给不同的处理器并行计算。

## 12. 总结

0-1背包问题是动态规划的经典应用之一，它展示了如何通过将复杂问题分解为子问题来解决优化问题。该问题的核心思想是对于每个物品都面临选择或不选择的决策，通过比较两种选择的收益来做出最优决策。

通过本文的介绍，我们学习了0-1背包问题的多种解决方法：
1. **暴力递归方法**：最容易理解但效率最低
2. **记忆化递归方法**：通过缓存中间结果避免重复计算
3. **动态规划方法**：自底向上填充DP表，是实际应用中最常用的方法
4. **空间优化DP方法**：在时间和空间效率之间取得更好的平衡

掌握这类动态规划算法对于解决实际生活中的资源分配和优化问题具有重要意义。在实际应用中，我们可以根据具体需求选择合适的实现方式，并根据问题特点进行相应的优化。