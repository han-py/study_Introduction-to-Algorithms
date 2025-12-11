# 活动选择问题 (Activity Selection Problem)

## 1. 算法简介

活动选择问题(Activity Selection Problem)是贪心算法中的一个经典问题。问题的描述如下：

> 给定n个活动的集合S={a₁,a₂,...,aₙ}，每个活动aᵢ都有一个开始时间sᵢ和一个结束时间fᵢ，其中0≤sᵢ<fᵢ<∞。如果被选中，活动aᵢ发生在半开时间区间[sᵢ,fᵢ)期间。如果有两个活动aᵢ和aⱼ满足区间[sᵢ,fᵢ)和[sⱼ,fⱼ)不重叠，则称它们是兼容的。在活动选择问题中，希望选出一个由互相兼容的活动组成的最大集合。

这是一个典型的贪心算法应用场景，通过每次选择结束时间最早的活动，可以获得全局最优解。

## 2. 算法思想

活动选择问题采用贪心策略：每次选择结束时间最早且与已选活动兼容的活动。

### 2.1 贪心选择性质

我们可以通过数学证明，选择结束时间最早的活动总能导致一个最优解。这是贪心算法能够解决问题的关键性质。

### 2.2 最优子结构

当我们做出贪心选择后（选择结束时间最早的活动），剩下的问题就变成了在一个更小的活动集合上求解活动选择问题，这体现了最优子结构性质。

## 3. 算法步骤

### 3.1 迭代贪心算法

1. **排序阶段**：将所有活动按照结束时间非递减顺序排列
2. **初始化**：选择第一个活动（结束时间最早的活动）
3. **迭代选择**：对于剩余的活动，如果某个活动的开始时间不早于上一个选中活动的结束时间，则选择该活动
4. **终止条件**：遍历完所有活动后算法结束

### 3.2 递归贪心算法

1. **排序阶段**：将所有活动按照结束时间非递减顺序排列
2. **基础情况**：如果没有更多活动可选，返回空集合
3. **递归选择**：选择与当前活动兼容的第一个活动，然后递归地在剩余活动中选择
4. **合并结果**：将当前选择的活动与递归结果合并

## 4. 算法图解示例

假设有以下11个活动：

| 活动编号 | 开始时间 | 结束时间 |
|---------|---------|---------|
| a₁      | 1       | 4       |
| a₂      | 3       | 5       |
| a₃      | 0       | 6       |
| a₄      | 5       | 7       |
| a₅      | 3       | 9       |
| a₆      | 5       | 9       |
| a₇      | 6       | 10      |
| a₈      | 8       | 11      |
| a₉      | 8       | 12      |
| a₁₀     | 2       | 14      |
| a₁₁     | 12      | 16      |

### 4.1 排序后

按结束时间排序后的活动列表：

| 活动编号 | 开始时间 | 结束时间 |
|---------|---------|---------|
| a₁      | 1       | 4       |
| a₂      | 3       | 5       |
| a₄      | 5       | 7       |
| a₇      | 6       | 10      |
| a₈      | 8       | 11      |
| a₉      | 8       | 12      |
| a₃      | 0       | 6       |
| a₅      | 3       | 9       |
| a₆      | 5       | 9       |
| a₁₀     | 2       | 14      |
| a₁₁     | 12      | 16      |

### 4.2 选择过程

1. 选择a₁（结束时间最早）：[1,4)
2. 寻找下一个兼容活动，选择a₂（开始时间3≥结束时间4？否）
3. 选择a₄（开始时间5≥结束时间4？是）
4. 寻找下一个兼容活动，选择a₇（开始时间6≥结束时间7？否）
5. 选择a₈（开始时间8≥结束时间7？是）
6. 寻找下一个兼容活动，选择a₁₁（开始时间12≥结束时间11？是）

最终选中的活动集合为：{a₁, a₄, a₈, a₁₁}

## 5. 伪代码实现

### 5.1 迭代贪心算法

```
ITERATIVE-ACTIVITY-SELECTOR(s, f)
1.  n = s.length
2.  let A be a new empty set
3.  A = A ∪ {a₁}
4.  j = 1
5.  for i = 2 to n
6.      if sᵢ ≥ fⱼ
7.          A = A ∪ {aᵢ}
8.          j = i
9.  return A
```

### 5.2 递归贪心算法

```
RECURSIVE-ACTIVITY-SELECTOR(s, f, k, n)
1.  m = k + 1
2.  while m ≤ n and sₘ < fₖ
3.      m = m + 1
4.  if m ≤ n
5.      return {aₘ} ∪ RECURSIVE-ACTIVITY-SELECTOR(s, f, m, n)
6.  else return ∅
```

## 6. C++代码实现

### 6.1 迭代贪心算法实现

```cpp
/**
 * 迭代贪心算法实现活动选择问题
 * 选择最多数量的兼容活动
 * 
 * @param activities 活动集合
 * @return 选中的活动集合
 */
std::vector<Activity> iterativeActivitySelection(std::vector<Activity>& activities) {
    // 步骤1：按结束时间排序
    std::sort(activities.begin(), activities.end(), compareActivities);
    
    // 存储选中的活动
    std::vector<Activity> selected;
    
    // 步骤2：选择第一个活动
    selected.push_back(activities[0]);
    int lastSelectedIndex = 0;
    
    std::cout << "选择活动 " << activities[0].id << " (时间: " << activities[0].startTime 
              << "-" << activities[0].finishTime << ")" << std::endl;
    
    // 步骤3：按贪心策略选择后续活动
    for (int i = 1; i < activities.size(); i++) {
        // 如果当前活动的开始时间不早于上一个选中活动的结束时间，则选择该活动
        if (activities[i].startTime >= activities[lastSelectedIndex].finishTime) {
            selected.push_back(activities[i]);
            lastSelectedIndex = i;
            std::cout << "选择活动 " << activities[i].id << " (时间: " << activities[i].startTime 
                      << "-" << activities[i].finishTime << ")" << std::endl;
        }
    }
    
    return selected;
}
```

### 6.2 递归贪心算法实现

```cpp
/**
 * 递归贪心算法实现活动选择问题
 * 
 * @param activities 按结束时间排序的活动集合
 * @param k 上一个选中的活动索引
 * @param n 活动总数
 * @return 选中的活动集合
 */
std::vector<Activity> recursiveActivitySelection(const std::vector<Activity>& activities, int k, int n) {
    // 寻找第一个与活动k兼容的活动
    int m = k + 1;
    while (m < n && activities[m].startTime < activities[k].finishTime) {
        m++;
    }
    
    // 如果找到了兼容活动
    if (m < n) {
        std::cout << "选择活动 " << activities[m].id << " (时间: " << activities[m].startTime 
                  << "-" << activities[m].finishTime << ")" << std::endl;
        
        // 递归选择后续活动
        std::vector<Activity> result = recursiveActivitySelection(activities, m, n);
        result.push_back(activities[m]);
        return result;
    } else {
        // 没有更多兼容活动
        return std::vector<Activity>();
    }
}

/**
 * 递归贪心算法的包装函数
 * 
 * @param activities 活动集合
 * @return 选中的活动集合
 */
std::vector<Activity> recursiveActivitySelectionWrapper(std::vector<Activity>& activities) {
    // 按结束时间排序
    std::sort(activities.begin(), activities.end(), compareActivities);
    
    // 创建结果容器
    std::vector<Activity> selected;
    
    // 选择第一个活动
    std::cout << "选择活动 " << activities[0].id << " (时间: " << activities[0].startTime 
              << "-" << activities[0].finishTime << ")" << std::endl;
    selected.push_back(activities[0]);
    
    // 递归选择其余活动
    std::vector<Activity> recursiveResult = recursiveActivitySelection(activities, 0, activities.size());
    
    // 将递归结果添加到选中活动中
    for (int i = recursiveResult.size() - 1; i >= 0; i--) {
        selected.push_back(recursiveResult[i]);
    }
    
    return selected;
}
```

## 7. 算法分析

### 7.1 时间复杂度

- **排序阶段**：O(n log n)，使用快速排序或其他高效排序算法
- **迭代选择阶段**：O(n)，只需遍历一次活动列表
- **递归选择阶段**：O(n)，每个活动最多被访问一次
- **总体时间复杂度**：O(n log n)

### 7.2 空间复杂度

- **排序所需空间**：O(log n)，排序算法所需的辅助空间
- **存储选中活动**：O(k)，k为选中活动的数量
- **递归调用栈**：O(n)，最坏情况下递归深度为n
- **总体空间复杂度**：O(n)

### 7.3 稳定性

该算法不是稳定排序算法，因为活动的相对顺序会根据结束时间发生改变。

## 8. 算法特点

### 8.1 迭代算法 vs 递归算法

| 特性 | 迭代算法 | 递 归算法 |
|-----|---------|----------|
| 实现难度 | 简单 | 中等 |
| 内存使用 | 较少(O(1)栈空间) | 较多(O(n)栈空间) |
| 可读性 | 清晰直观 | 逻辑稍复杂 |
| 性能 | 更好 | 略差(函数调用开销) |

### 8.2 优点

1. **简单高效**：算法思路清晰，易于理解和实现
2. **时间复杂度低**：O(n log n)的时间复杂度在大多数情况下是可以接受的
3. **贪心策略有效**：局部最优选择能导致全局最优解
4. **实用性强**：可以解决许多现实生活中的调度问题

### 8.3 缺点

1. **仅考虑活动数量**：只关注选择活动的数量，不考虑活动的重要性或其他权重因素
2. **无法处理复杂约束**：对于有复杂约束条件的问题，基本算法可能不适用

## 9. 适用场景

1. **会议安排**：在会议室资源有限的情况下，安排尽可能多的会议
2. **任务调度**：在CPU资源有限的情况下，调度尽可能多的任务
3. **教室安排**：为不同课程安排教室，使得同一教室能容纳更多课程
4. **资源分配**：在有限的资源下，分配给更多的项目使用

## 10. 与其他算法比较

| 算法类型 | 时间复杂度 | 空间复杂度 | 特点 |
|---------|-----------|-----------|------|
| 贪心算法(活动选择) | O(n log n) | O(n) | 简单高效，适合解决调度问题 |
| 动态规划 | O(n³) | O(n²) | 可以处理带权重的活动选择问题 |
| 回溯法 | O(2ⁿ) | O(n) | 可以找出所有可行解，但时间复杂度过高 |

## 11. 优化方案

### 11.1 加权活动选择问题

基本的活动选择问题只考虑活动数量，但在实际应用中，不同活动可能有不同的价值或权重。这时可以使用动态规划方法来解决加权活动选择问题。

### 11.2 在线活动选择

在某些场景下，活动信息不是一次性给出，而是随着时间逐步到达。这种情况下可以设计在线算法来处理。

### 11.3 多资源活动选择

在实际情况中，活动可能需要多种资源，这就变成了多维资源约束下的活动选择问题，可以使用更复杂的算法来解决。

## 12. 总结

活动选择问题是贪心算法的经典应用之一，它展示了如何通过贪心策略有效地解决优化问题。该算法的核心思想是每次选择结束时间最早的活动，这样能为后续活动留出最多的时间空间。

通过本文的介绍，我们不仅学习了活动选择问题的基本概念和算法实现，还了解了其时间复杂度分析、适用场景以及与其他算法的比较。掌握这类贪心算法对于解决实际生活中的调度和优化问题具有重要意义。

在实际应用中，我们可以根据具体需求对基本算法进行改进和扩展，以适应各种复杂的约束条件。无论是使用迭代还是递归的方式实现，都能得到正确的结果，选择哪种实现方式取决于具体的应用场景和性能要求。