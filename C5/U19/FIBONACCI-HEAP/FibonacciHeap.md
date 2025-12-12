# 斐波那契堆 (Fibonacci Heap)

> 📘 _算法导论第19章学习指南_

## 🎯 1. 简介

**斐波那契堆**(Fibonacci Heap)是一种高效的数据结构，主要用于实现优先队列。它是由Michael L. Fredman和Robert E. Tarjan在1984年开发的，并在1987年发表。斐波那契堆的名字来源于其分析中使用的斐波那契数列。

斐波那契堆的主要优势在于其优秀的摊还时间复杂度，特别是在涉及大量插入和合并操作的应用中，比如图算法中的Dijkstra算法和Prim算法。

### 1.1 为什么需要斐波那契堆？

在许多算法中，我们需要频繁地执行以下操作：
1. 插入元素
2. 查找最小元素
3. 合并两个优先队列
4. 减小元素的键值

传统的二叉堆在合并操作上的时间复杂度为O(n)，而斐波那契堆通过延迟工作的方式，将合并操作的时间复杂度降低到O(1)。

### 1.2 斐波那契堆的特点

1. **懒惰操作**：许多工作被推迟到真正需要时才执行
2. **摊还效率**：虽然单次操作可能较慢，但多次操作的平均时间复杂度很好
3. **理论最优**：在理论上达到了很多操作的下界

## 📚 2. 斐波那契堆的结构

### 2.1 基本概念

斐波那契堆是一组最小堆有序树的集合，满足以下性质：

1. **最小堆性质**：每个节点的关键字不大于其子女的关键字
2. **根列表**：堆中所有树的根节点构成一个双向循环链表
3. **指针指向**：堆对象H有一个指针min[H]指向根列表中关键字最小的节点

### 2.2 节点结构

每个节点包含以下字段：
- **key**：节点的关键字
- **degree**：节点的度数（子女的数目）
- **parent**：指向父节点的指针
- **child**：指向某个子女节点的指针
- **left, right**：指向左兄弟和右兄弟的指针
- **mark**：标记位，记录节点是否失去过子女

### 2.3 斐波那契堆的势函数

为了进行摊还分析，我们定义势函数：
```
Φ(H) = t(H) + 2·m(H)
```
其中：
- t(H)是堆中根列表中树的数目
- m(H)是堆中被标记的节点数目

## 🔧 3. 斐波那契堆的操作

### 3.1 创建新的斐波那契堆

```
MAKE-FIB-HEAP()
1. n[H] = 0
2. min[H] = NIL
3. return H
```

时间复杂度：O(1)

### 3.2 插入节点

```
FIB-HEAP-INSERT(H, x)
1. degree[x] = 0
2. p[x] = NIL
3. child[x] = NIL
4. mark[x] = FALSE
5. 将x插入到H的根列表中
6. if min[H] = NIL 或 key[x] < key[min[H]]
7.     min[H] = x
8. n[H] = n[H] + 1
```

时间复杂度：O(1)（实际成本和摊还成本都是O(1)）

### 3.3 查找最小节点

```
FIB-HEAP-MINIMUM(H)
1. return min[H]
```

时间复杂度：O(1)

### 3.4 合并两个斐波那契堆

```
FIB-HEAP-UNION(H1, H2)
1. H = MAKE-FIB-HEAP()
2. min[H] = min[H1]
3. 将H2的根列表连接到H的根列表中
4. if (min[H1] = NIL) or (min[H2] ≠ NIL and key[min[H2]] < key[min[H1]])
5.     min[H] = min[H2]
6. n[H] = n[H1] + n[H2]
7. return H
```

时间复杂度：O(1)（实际成本和摊还成本都是O(1)）

### 3.5 抽取最小节点

这是斐波那契堆中最复杂的操作，包含以下步骤：

1. 将最小节点的所有子女添加到根列表中
2. 从根列表中删除最小节点
3. 调用CONSOLIDATE过程，确保根列表中没有两个度数相同的根
4. 更新min[H]指针

```
FIB-HEAP-EXTRACT-MIN(H)
1. z = min[H]
2. if z ≠ NIL
3.     for each child x of z
4.         将x添加到H的根列表中
5.         p[x] = NIL
6.     从H的根列表中删除z
7.     if z = right[z]
8.         min[H] = NIL
9.     else
10.        min[H] = right[z]
11.        CONSOLIDATE(H)
12.    n[H] = n[H] - 1
13.return z
```

CONSOLIDATE过程：
```
CONSOLIDATE(H)
1. for i = 0 to D(n[H])
2.     A[i] = NIL
3. for each node w in the root list of H
4.     x = w
5.     d = degree[x]
6.     while A[d] ≠ NIL
7.         y = A[d]
8.         if key[x] > key[y]
9.             exchange x ↔ y
10.        FIB-HEAP-LINK(H, y, x)
11.        A[d] = NIL
12.        d = d + 1
13.    A[d] = x
14. min[H] = NIL
15. for i = 0 to D(n[H])
16.    if A[i] ≠ NIL
17.        将A[i]添加到H的根列表中
18.        if min[H] = NIL or key[A[i]] < key[min[H]]
19.            min[H] = A[i]
```

FIB-HEAP-LINK过程：
```
FIB-HEAP-LINK(H, y, x)
1. 从H的根列表中删除y
2. 将y作为x的子女
3. degree[x] = degree[x] + 1
```

摊还时间复杂度：O(D(n))，其中D(n) ≤ log_φ(n)，φ是黄金比例(1+√5)/2

### 3.6 减小关键字

```
FIB-HEAP-DECREASE-KEY(H, x, k)
1. if k > key[x]
2.     error "new key is greater than current key"
3. key[x] = k
4. y = p[x]
5. if y ≠ NIL and key[x] < key[y]
6.     CUT(H, x, y)
7.     CASCADING-CUT(H, y)
8. if key[x] < key[min[H]]
9.     min[H] = x
```

CUT过程：
```
CUT(H, x, y)
1. 从x的子女列表中删除x
2. degree[y] = degree[y] - 1
3. 将x添加到H的根列表中
4. p[x] = NIL
5. mark[x] = FALSE
```

CASCADING-CUT过程：
```
CASCADING-CUT(H, y)
1. z = p[y]
2. if z ≠ NIL
3.     if mark[y] = FALSE
4.         mark[y] = TRUE
5.     else
6.         CUT(H, y, z)
7.         CASCADING-CUT(H, z)
```

摊还时间复杂度：O(1)

### 3.7 删除节点

```
FIB-HEAP-DELETE(H, x)
1. FIB-HEAP-DECREASE-KEY(H, x, -∞)
2. FIB-HEAP-EXTRACT-MIN(H)
```

摊还时间复杂度：O(D(n))

## 📊 4. 时间复杂度分析

| 操作 | 实际时间复杂度 | 摊还时间复杂度 |
|------|---------------|---------------|
| 创建新堆 | O(1) | O(1) |
| 插入 | O(1) | O(1) |
| 查找最小 | O(1) | O(1) |
| 合并 | O(1) | O(1) |
| 抽取最小 | O(D(n)) | O(log n) |
| 减小关键字 | O(D(n)) | O(1) |
| 删除 | O(D(n)) | O(log n) |

其中D(n) ≤ log_φ(n)，φ = (1+√5)/2 ≈ 1.618（黄金比例）

## 💡 5. 斐波那契堆的优势

### 5.1 摊还效率

斐波那契堆最重要的特点是其优秀的摊还时间复杂度：

1. **插入、合并操作**：O(1)摊还时间
2. **查找最小**：O(1)实际时间
3. **抽取最小、删除**：O(log n)摊还时间
4. **减小关键字**：O(1)摊还时间

### 5.2 懒惰操作

斐波那契堆采用懒惰策略，将昂贵的操作推迟到必要时才执行：

1. **延迟合并**：不像二项堆那样立即维护树的结构，而是在抽取最小节点时才进行合并
2. **标记机制**：通过标记位跟踪节点的结构变化，优化减小关键字操作

### 5.3 理论意义

斐波那契堆在理论上具有重要意义：

1. **接近下界**：许多操作达到了理论下界
2. **启发作用**：启发了其他数据结构的设计

## 🧪 6. 示例代码解析

我们的示例代码展示了斐波那契堆的核心概念：

### 6.1 数据结构设计

1. **[FibonacciNode](file://C:\Users\HaPpY\Desktop\study_Introduction-to-Algorithms\C5\U19\FIBONACCI-HEAP\FibonacciHeap.cpp#L12-L26) 结构**：表示斐波那契堆的节点
2. **[FibonacciHeap](file://C:\Users\HaPpY\Desktop\study_Introduction-to-Algorithms\C5\U19\FIBONACCI-HEAP\FibonacciHeap.cpp#L29-L42) 类**：表示整个斐波那契堆

### 6.2 核心操作实现

1. **[insert](file://C:\Users\HaPpY\Desktop\study_Introduction-to-Algorithms\C5\U19\FIBONACCI-HEAP\FibonacciHeap.cpp#L52-L64)**：插入节点到根列表
2. **[extractMin](file://C:\Users\HaPpY\Desktop\study_Introduction-to-Algorithms\C5\U19\FIBONACCI-HEAP\FibonacciHeap.cpp#L70-L97)**：抽取最小节点并维护堆性质
3. **[unite](file://C:\Users\HaPpY\Desktop\study_Introduction-to-Algorithms\C5\U19\FIBONACCI-HEAP\FibonacciHeap.cpp#L126-L153)**：合并两个斐波那契堆
4. **[decreaseKey](file://C:\Users\HaPpY\Desktop\study_Introduction-to-Algorithms\C5\U19\FIBONACCI-HEAP\FibonacciHeap.cpp#L156-L176)**：减小节点的关键字值
5. **[deleteNode](file://C:\Users\HaPpY\Desktop\study_Introduction-to-Algorithms\C5\U19\FIBONACCI-HEAP\FibonacciHeap.cpp#L207-L215)**：删除指定节点

### 6.3 辅助函数

1. **[consolidate](file://C:\Users\HaPpY\Desktop\study_Introduction-to-Algorithms\C5\U19\FIBONACCI-HEAP\FibonacciHeap.cpp#L109-L124)**：维护根列表中没有相同度数的树
2. **[cut](file://C:\Users\HaPpY\Desktop\study_Introduction-to-Algorithms\C5\U19\FIBONACCI-HEAP\FibonacciHeap.cpp#L178-L196)**：切断父子关系
3. **[cascadingCut](file://C:\Users\HaPpY\Desktop\study_Introduction-to-Algorithms\C5\U19\FIBONACCI-HEAP\FibonacciHeap.cpp#L198-L205)**：级联切断操作

## 📈 7. 斐波那契堆与其他堆的比较

| 特性 | 二叉堆 | 二项堆 | 斐波那契堆 |
|------|--------|--------|------------|
| 创建 | O(1) | O(1) | O(1) |
| 插入 | O(log n) | O(log n) | O(1) |
| 查找最小 | O(1) | O(log n) | O(1) |
| 抽取最小 | O(log n) | O(log n) | O(log n) |
| 合并 | O(n) | O(log n) | O(1) |
| 减小关键字 | O(log n) | O(log n) | O(1) |
| 删除 | O(log n) | O(log n) | O(log n) |

## 🎯 8. 应用场景

### 8.1 图算法

斐波那契堆在图算法中发挥重要作用：

1. **Dijkstra算法**：用于计算单源最短路径
2. **Prim算法**：用于计算最小生成树
3. **Johnson算法**：用于计算所有节点对之间的最短路径

### 8.2 其他应用

1. **网络流算法**：在网络流算法中作为优先队列使用
2. **贪心算法**：在需要频繁插入和查找最小元素的贪心算法中
3. **调度算法**：在操作系统或任务调度中的优先级队列

## ⚠️ 9. 实现注意事项

### 9.1 内存管理

斐波那契堆涉及大量动态内存分配，需要注意：
- 及时释放不再使用的节点
- 避免内存泄漏
- 考虑使用内存池优化频繁的内存分配

### 9.2 实际性能

虽然斐波那契堆在理论上具有很好的摊还时间复杂度，但在实际应用中：
- 常数因子较大，对于小规模数据可能不如简单数据结构
- 需要额外的存储空间保存标记位和其他指针
- 实现复杂度较高，容易出错

### 9.3 适用场景

斐波那契堆最适合以下场景：
- 需要大量插入和合并操作
- 数据规模较大
- 对渐近时间复杂度敏感而非对常数因子敏感

## 🧠 10. 总结

斐波那契堆是一种理论和实践都很有趣的数据结构，它展示了如何通过懒惰操作和摊还分析来优化数据结构的性能。

### 10.1 核心思想

1. **懒惰操作**：推迟昂贵的操作直到必要时才执行
2. **摊还分析**：通过势能法分析操作序列的整体性能
3. **结构优化**：通过巧妙的数据结构设计优化特定操作

### 10.2 学习价值

1. **算法思维**：学习如何通过延迟工作来优化性能
2. **摊还分析**：掌握一种重要的算法分析技术
3. **数据结构设计**：理解高级数据结构的设计原则

### 10.3 实践建议

1. **动手实现**：通过实际编码加深对斐波那契堆操作的理解
2. **性能测试**：对比不同堆结构在实际应用中的性能表现
3. **应用场景分析**：研究斐波那契堆在图算法中的应用

通过我们的示例代码，您可以清楚地看到斐波那契堆的各种操作是如何实现的，包括插入、抽取最小节点、减小关键字等核心功能。这为深入学习和实践提供了坚实的基础。