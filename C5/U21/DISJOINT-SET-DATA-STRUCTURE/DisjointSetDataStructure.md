# 不相交集合数据结构 (Disjoint-Set Data Structure)

> 📘 _《算法导论》第21章学习指南_

## 🎯 1. 简介

**不相交集合数据结构**(Disjoint-Set Data Structure)，也被称为**并查集**(Union-Find Set)，是一种用于处理不相交集合合并与查询问题的树型数据结构。它支持三种基本操作：

1. **MAKE-SET(x)** - 创建一个只包含元素x的新集合
2. **UNION(x, y)** - 将包含元素x和y的两个集合合并为一个集合
3. **FIND-SET(x)** - 返回包含元素x的集合的代表元素（通常是根节点）

### 1.1 历史背景

不相交集合数据结构的概念最早由 Bernard A. Galler 和 Michael J. Fischer 在1964年提出。他们不仅提出了这种数据结构，还对其进行了详细的分析。后来，Robert Tarjan 在1975年证明了该数据结构在特定操作序列下的时间复杂度上界。

### 1.2 应用场景

不相交集合数据结构在计算机科学中有广泛的应用：

- **图论算法**：Kruskal最小生成树算法
- **网络连通性**：判断网络中节点间的连通性
- **图像处理**：连通区域标记
- **编译器设计**：寄存器分配中的变量冲突检测
- **社交网络分析**：朋友圈识别

## 📚 2. 基本概念

### 2.1 不相交集合的性质

不相交集合具有以下重要性质：

1. **互斥性**：任意两个集合要么完全相同，要么没有任何公共元素
2. **完整性**：所有元素都必须属于某个集合
3. **代表性**：每个集合都有一个代表元素，通常选择根节点作为代表

### 2.2 集合的表示方法

不相交集合通常用树的形式来表示：

- 每个集合用一棵有根树表示
- 树中的每个节点存储集合中的一个元素
- 每个节点还有一个指向其父节点的指针
- 根节点是集合的代表元素，其父节点指向自身

例如，假设有三个集合：
- S₁ = {0, 1, 2}
- S₂ = {3, 4}
- S₃ = {5, 6, 7, 8}

可以用如下树结构表示：

```
S₁:     S₂:     S₃:
  0       3       5
 / \       \     /|\
1   2       4   6 7 8
```

## 🔧 3. 基本操作详解

### 3.1 MAKE-SET操作

MAKE-SET(x)操作创建一个只包含元素x的新集合：

```cpp
void makeSet(int x) {
    parent[x] = x;
    rank[x] = 0;
}
```

这个操作的时间复杂度是O(1)。

### 3.2 FIND-SET操作

FIND-SET(x)操作返回包含元素x的集合的代表元素。实现时，沿着父节点指针向上查找，直到找到根节点：

```cpp
int findSet(int x) {
    if (parent[x] != x) {
        return findSet(parent[x]);
    }
    return parent[x];
}
```

### 3.3 UNION操作

UNION(x, y)操作将包含元素x和y的两个集合合并。首先需要找到两个元素所在集合的代表元素，然后将其中一个树的根节点作为另一个树的子节点：

```cpp
void unionSets(int x, int y) {
    int rootX = findSet(x);
    int rootY = findSet(y);
    
    if (rootX != rootY) {
        parent[rootY] = rootX;
    }
}
```

## ⚡ 4. 优化策略

虽然基本操作已经可以工作，但通过两种优化策略可以显著提高性能：

### 4.1 按秩合并 (Union by Rank)

在按秩合并中，我们总是将秩较小的树连接到秩较大的树下。这里的"秩"可以看作是树的高度上界。

```cpp
void unionSets(int x, int y) {
    int rootX = findSet(x);
    int rootY = findSet(y);
    
    if (rootX != rootY) {
        if (rank[rootX] < rank[rootY]) {
            parent[rootX] = rootY;
        } else if (rank[rootX] > rank[rootY]) {
            parent[rootY] = rootX;
        } else {
            parent[rootY] = rootX;
            rank[rootX]++;
        }
    }
}
```

### 4.2 路径压缩 (Path Compression)

在路径压缩中，我们在执行FIND-SET操作时，将查找路径上的每个节点直接连接到根节点：

```cpp
int findSet(int x) {
    if (parent[x] != x) {
        parent[x] = findSet(parent[x]);  // 递归进行路径压缩
    }
    return parent[x];
}
```

## 📊 5. 时间复杂度分析

### 5.1 单独使用一种优化

如果只使用按秩合并或只使用路径压缩，各操作的时间复杂度为：

- MAKE-SET: O(1)
- UNION: O(log n)
- FIND-SET: O(log n)

### 5.2 同时使用两种优化

当同时使用按秩合并和路径压缩时，摊还时间复杂度为：

- MAKE-SET: O(1)
- UNION: O(α(n))
- FIND-SET: O(α(n))

其中α(n)是反Ackermann函数，增长极其缓慢。对于任何实际应用中的n值，α(n)都不会超过5。

### 5.3 m次操作序列的复杂度

如果我们执行m次MAKE-SET、UNION和FIND-SET操作序列（其中有n次MAKE-SET操作），则总时间复杂度为：

O(m·α(n))

这几乎是线性的复杂度，非常高效。

## 🧪 6. 示例演示

让我们通过一个具体的例子来演示不相交集合的操作过程。

初始状态（9个元素，编号0-8）：

```
0  1  2  3  4  5  6  7  8
```

每个元素都是自己集合的代表。

执行操作UNION(1, 2)后：

```
1
 \
  2
```

执行操作UNION(3, 4)后：

```
3
 \
  4
```

执行操作UNION(5, 6)后：

```
5
 \
  6
```

执行操作UNION(1, 3)后：

```
  1
 / \
2   3
     \
      4
```

执行操作UNION(1, 5)后：

```
    1
   /|\
  2 3 5
    | |
    4 6
```

## 💡 7. 实现细节

### 7.1 数据结构表示

我们使用两个数组来表示不相交集合：

1. `parent[]`数组：parent[i]表示元素i的父节点
2. `rank[]`数组：rank[i]表示以i为根的树的秩（高度上界）

### 7.2 路径压缩的实现技巧

路径压缩的递归实现简洁明了，但在某些语言中可能导致栈溢出。也可以使用迭代方式实现：

```cpp
int findSetIterative(int x) {
    int root = x;
    // 找到根节点
    while (parent[root] != root) {
        root = parent[root];
    }
    
    // 路径压缩：将路径上的所有节点直接连接到根节点
    while (parent[x] != x) {
        int next = parent[x];
        parent[x] = root;
        x = next;
    }
    
    return root;
}
```

## 🎯 8. 实际应用案例

### 8.1 Kruskal最小生成树算法

Kruskal算法使用不相交集合来检测添加边是否会形成环路：

```cpp
// Kruskal算法的核心部分
sort(edges.begin(), edges.end());  // 按权重排序边
DisjointSet ds(numVertices);

for (auto& edge : edges) {
    int u = edge.source;
    int v = edge.destination;
    
    // 如果两个顶点不属于同一集合，则添加这条边不会形成环路
    if (ds.findSet(u) != ds.findSet(v)) {
        ds.unionSets(u, v);
        mst.addEdge(edge);
    }
}
```

### 8.2 连通分量检测

在无向图中检测连通分量：

```cpp
DisjointSet ds(numVertices);

// 对于图中的每条边(u,v)，合并u和v所在的集合
for (auto& edge : edges) {
    ds.unionSets(edge.u, edge.v);
}

// 统计连通分量的数量
int components = 0;
for (int i = 0; i < numVertices; i++) {
    if (ds.findSet(i) == i) {  // 如果i是根节点
        components++;
    }
}
```

## ⚠️ 9. 实现注意事项

### 9.1 初始化

确保在使用前正确初始化数据结构，每个元素都应该初始化为自己集合的代表。

### 9.2 边界条件

注意处理以下特殊情况：
- 对不存在的元素执行操作
- 对已经在一个集合中的元素执行UNION操作
- 空集合的处理

### 9.3 内存管理

在动态环境中，要注意及时释放不再使用的内存。

## 🧠 10. 总结

不相交集合数据结构是一个强大而优雅的数据结构，具有以下特点：

### 10.1 核心优势

1. **高效性**：通过按秩合并和路径压缩优化，几乎达到了线性时间复杂度
2. **简洁性**：实现相对简单，易于理解和维护
3. **实用性**：在众多算法和实际应用中都有重要作用

### 10.2 学习要点

1. **理解基本概念**：掌握不相交集合的定义和性质
2. **掌握基本操作**：熟练实现MAKE-SET、UNION和FIND-SET操作
3. **理解优化策略**：深刻理解按秩合并和路径压缩的工作原理
4. **熟悉应用场景**：了解在图论算法和其他领域的应用

### 10.3 进一步学习

1. **扩展应用**：研究在更多算法中的应用，如Tarjan的强连通分量算法
2. **性能分析**：深入了解反Ackermann函数和摊还分析
3. **变体实现**：探索其他优化策略和实现方式

通过我们的示例代码，您可以清楚地看到不相交集合数据结构的各种操作是如何实现的，包括基本操作和优化策略。这为深入学习和实践提供了坚实的基础。