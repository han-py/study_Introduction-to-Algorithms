# 优先队列 (Priority Queue)

## 1. 算法简介

优先队列（Priority Queue）是一种抽象数据类型，与普通队列不同，它为每个元素分配一个优先级。在优先队列中，元素的处理顺序由其优先级决定，而不是它们进入队列的顺序。优先级高的元素会优先被处理。

优先队列具有以下特点：
- 每个元素都有一个优先级
- 访问元素时，优先级最高的元素最先被删除
- 通常采用堆数据结构来实现

优先队列分为两种类型：
- 最大优先队列：优先级最大的元素最先被删除
- 最小优先队列：优先级最小的元素最先被删除

## 2. 算法思想

优先队列的核心思想是利用堆这种数据结构来维护元素的优先级顺序。堆是一种特殊的完全二叉树，具有以下性质：
1. 堆是一个完全二叉树
2. 堆具有堆性质：
   - 在最大堆中，每个节点的值都大于或等于其子节点的值
   - 在最小堆中，每个节点的值都小于或等于其子节点的值

通过维护堆的性质，我们可以高效地实现优先队列的各种操作：
- 插入元素：O(log n)
- 提取最大/最小元素：O(log n)
- 获取最大/最小元素：O(1)

## 3. 算法步骤

优先队列的主要操作包括：

### 3.1 插入操作 (INSERT)
1. 将新元素添加到堆的末尾
2. 通过向上调整维护堆的性质

### 3.2 提取最大/最小元素 (EXTRACT-MAX/EXTRACT-MIN)
1. 移除并返回堆顶元素
2. 将堆的最后一个元素移到堆顶
3. 通过向下调整维护堆的性质

### 3.3 获取最大/最小元素 (MAXIMUM/MINIMUM)
1. 直接返回堆顶元素

### 3.4 增加元素优先级 (INCREASE-KEY)
1. 增加指定元素的键值
2. 通过向上调整维护堆的性质

## 4. 算法图解示例

以最大优先队列为例，初始数组为 [15, 13, 9, 5, 12, 8, 7, 4, 0, 6, 2, 1]：

### 4.1 构建最大堆过程
```
初始数组: [15, 13, 9, 5, 12, 8, 7, 4, 0, 6, 2, 1]

构建堆过程:
           15
         /    \
       13      9
      /  \    /  \
     5   12  8    7
    / \  / \ / \
   4  0 6  2 1

经过调整后形成最大堆:
           15
         /    \
       13      9
      /  \    /  \
     5   12  8    7
    / \  / \ / \
   4  0 6  2 1
```

### 4.2 插入元素过程
插入元素10后，需要向上调整以维持堆性质：
```
插入10后:
           15
         /    \
       13      9
      /  \    /  \
     5   12  8    7
    / \  / \ / \ /
   4  0 6  2 1 10

向上调整后:
           15
         /    \
       13      10
      /  \    /  \
     5   12  8    9
    / \  / \ / \ /
   4  0 6  2 1 7
```

## 5. 伪代码实现

```
GET-MAXIMUM(A)
1. return A[1]

EXTRACT-MAX(A)
1. if A.heap-size < 1
2.     error "heap underflow"
3. max = A[1]
4. A[1] = A[A.heap-size]
5. A.heap-size = A.heap-size - 1
6. MAX-HEAPIFY(A, 1)
7. return max

INCREASE-KEY(A, i, key)
1. if key < A[i]
2.     error "new key is smaller than current key"
3. A[i] = key
4. while i > 1 and A[PARENT(i)] < A[i]
5.     exchange A[i] with A[PARENT(i)]
6.     i = PARENT(i)

INSERT(A, key)
1. A.heap-size = A.heap-size + 1
2. A[A.heap-size] = -∞
3. INCREASE-KEY(A, A.heap-size, key)
```

## 6. C++代码实现

```cpp
#include <iostream>
#include <vector>
#include <climits>

/**
 * 维护最大堆性质
 * @param arr 数组表示的堆
 * @param heapSize 堆的大小
 * @param i 需要维护节点的索引
 */
void maxHeapify(std::vector<int>& arr, int heapSize, int i) {
    int largest = i;          // 初始化最大值为根节点
    int left = 2 * i + 1;     // 左子节点
    int right = 2 * i + 2;    // 右子节点

    // 如果左子节点存在且大于根节点
    if (left < heapSize && arr[left] > arr[largest])
        largest = left;

    // 如果右子节点存在且大于当前最大值
    if (right < heapSize && arr[right] > arr[largest])
        largest = right;

    // 如果最大值不是根节点
    if (largest != i) {
        std::swap(arr[i], arr[largest]);
        // 递归地调整受影响的子树
        maxHeapify(arr, heapSize, largest);
    }
}

/**
 * 构建最大堆
 * @param arr 待构建堆的数组
 * @param n 数组长度
 */
void buildMaxHeap(std::vector<int>& arr, int n) {
    // 从最后一个非叶子节点开始，自底向上构建最大堆
    for (int i = n / 2 - 1; i >= 0; i--)
        maxHeapify(arr, n, i);
}

/**
 * 向最大堆中插入一个元素
 * @param arr 堆数组
 * @param key 要插入的元素
 */
void heapInsert(std::vector<int>& arr, int& heapSize, int key) {
    // 增加堆的大小
    heapSize++;
    if (heapSize > (int)arr.size()) {
        arr.push_back(key);
    } else {
        arr[heapSize - 1] = key;
    }
    
    // 保持最大堆性质
    int i = heapSize - 1;
    while (i > 0 && arr[(i - 1) / 2] < arr[i]) {
        std::swap(arr[i], arr[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

/**
 * 获取最大元素（堆顶元素）
 * @param arr 堆数组
 * @return 堆顶元素
 */
int heapMaximum(const std::vector<int>& arr) {
    if (arr.empty()) {
        std::cerr << "堆为空" << std::endl;
        return INT_MIN;
    }
    return arr[0];
}

/**
 * 提取并删除最大元素（堆顶元素）
 * @param arr 堆数组
 * @param heapSize 堆大小的引用
 * @return 堆顶元素
 */
int heapExtractMax(std::vector<int>& arr, int& heapSize) {
    if (heapSize < 1) {
        std::cerr << "堆下溢" << std::endl;
        return INT_MIN;
    }
    
    int max = arr[0];
    arr[0] = arr[heapSize - 1];
    heapSize--;
    maxHeapify(arr, heapSize, 0);
    return max;
}

/**
 * 增加堆中某个元素的值
 * @param arr 堆数组
 * @param i 要增加元素的索引
 * @param key 新的键值
 */
void heapIncreaseKey(std::vector<int>& arr, int i, int key) {
    if (key < arr[i]) {
        std::cerr << "新的键值比当前键值小" << std::endl;
        return;
    }
    
    arr[i] = key;
    while (i > 0 && arr[(i - 1) / 2] < arr[i]) {
        std::swap(arr[i], arr[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

/**
 * 打印数组元素
 * @param arr 要打印的数组
 * @param msg 打印信息
 */
void printArray(const std::vector<int>& arr, int heapSize, const std::string& msg = "") {
    if (!msg.empty()) {
        std::cout << msg;
    }
    for (int i = 0; i < heapSize; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

/**
 * 主函数，用于测试优先队列（最大堆实现）
 */
int main() {
    // 初始化优先队列
    std::vector<int> priorityQueue = {15, 13, 9, 5, 12, 8, 7, 4, 0, 6, 2, 1};
    int heapSize = priorityQueue.size();
    
    std::cout << "初始优先队列: ";
    printArray(priorityQueue, heapSize);
    std::cout << std::endl;
    
    // 构建最大堆
    buildMaxHeap(priorityQueue, heapSize);
    std::cout << "构建最大堆后: ";
    printArray(priorityQueue, heapSize);
    std::cout << std::endl;
    
    // 获取最大元素
    std::cout << "当前最大元素: " << heapMaximum(priorityQueue) << std::endl << std::endl;
    
    // 提取最大元素
    int maxElement = heapExtractMax(priorityQueue, heapSize);
    std::cout << "提取的最大元素: " << maxElement << std::endl;
    std::cout << "提取后优先队列: ";
    printArray(priorityQueue, heapSize);
    std::cout << std::endl;
    
    // 插入新元素
    int newKey = 10;
    std::cout << "插入新元素 " << newKey << ": ";
    heapInsert(priorityQueue, heapSize, newKey);
    printArray(priorityQueue, heapSize);
    std::cout << std::endl;
    
    // 增加某个元素的值
    std::cout << "将索引1处的元素增加到14: ";
    heapIncreaseKey(priorityQueue, 1, 14);
    printArray(priorityQueue, heapSize);
    std::cout << std::endl;
    
    // 再次提取最大元素
    maxElement = heapExtractMax(priorityQueue, heapSize);
    std::cout << "再次提取的最大元素: " << maxElement << std::endl;
    std::cout << "提取后优先队列: ";
    printArray(priorityQueue, heapSize);
    
    return 0;
}
```

## 7. 算法分析

### 7.1 时间复杂度

| 操作 | 时间复杂度 | 说明 |
|------|------------|------|
| 获取最大元素(MAXIMUM) | O(1) | 直接返回堆顶元素 |
| 插入元素(INSERT) | O(log n) | 需要向上调整维护堆性质 |
| 提取最大元素(EXTRACT-MAX) | O(log n) | 需要向下调整维护堆性质 |
| 增加元素键值(INCREASE-KEY) | O(log n) | 需要向上调整维护堆性质 |
| 构建堆(BUILD-MAX-HEAP) | O(n) | 自底向上构建堆 |

### 7.2 空间复杂度

- 空间复杂度为 O(n)，其中 n 是优先队列中元素的数量
- 除了存储元素的数组外，只需要常数级别的额外空间

### 7.3 稳定性

- 优先队列本身不是一个稳定的排序算法
- 相同优先级的元素处理顺序取决于具体实现

## 8. 算法特点

### 8.1 优点

1. **高效的插入和删除操作**：插入和删除最大/最小元素的时间复杂度均为 O(log n)
2. **快速获取极值**：获取最大/最小元素的时间复杂度为 O(1)
3. **动态性**：可以随时插入新元素或删除已有元素
4. **灵活性**：可以方便地实现最大优先队列或最小优先队列

### 8.2 缺点

1. **不支持随机访问**：不能直接访问中间优先级的元素
2. **不稳定性**：相同优先级元素的处理顺序可能不确定
3. **需要额外的维护操作**：每次插入或删除都需要维护堆性质

## 9. 适用场景

1. **任务调度系统**：根据任务优先级安排执行顺序
2. **图算法**：如 Dijkstra 最短路径算法、Prim 最小生成树算法
3. **事件驱动仿真**：根据事件发生时间处理事件
4. **数据压缩**：如 Huffman 编码算法
5. **操作系统**：进程调度、内存管理等
6. **网络路由算法**：根据路径权重选择最优路径

## 10. 与其他数据结构的比较

| 数据结构 | 插入 | 删除最大值 | 获取最大值 | 空间复杂度 | 特点 |
|----------|------|------------|------------|------------|------|
| 无序数组 | O(1) | O(n) | O(n) | O(n) | 插入快，查询删除慢 |
| 有序数组 | O(n) | O(1) | O(1) | O(n) | 查询快，插入慢 |
| 二叉搜索树 | O(log n) | O(log n) | O(log n) | O(n) | 支持各种操作，但可能退化 |
| 优先队列(堆) | O(log n) | O(log n) | O(1) | O(n) | 最适合只关心最大/最小值的场景 |

## 11. 优化方案

1. **使用斐波那契堆**：对于某些操作（如 DECREASE-KEY）可以达到更好的摊还时间复杂度
2. **批量操作优化**：对于批量插入操作，可以使用 BUILD-MAX-HEAP 方法，时间复杂度为 O(n)
3. **双端优先队列**：同时支持高效获取最大值和最小值
4. **并行化**：在多核环境下可以对堆操作进行并行优化

## 12. 总结

优先队列是一种非常重要的抽象数据类型，它通过堆这种数据结构实现了高效的极值操作。在实际应用中，优先队列被广泛应用于各种算法和系统中，特别是在需要根据优先级处理元素的场景中。

优先队列的核心在于理解堆的性质和维护堆性质的操作。通过合理地利用堆的特性，我们可以实现高效的优先队列，满足各种应用需求。

掌握优先队列不仅有助于理解数据结构的设计思想，也为后续学习更复杂的算法和数据结构打下了坚实的基础。在实际编程中，优先队列往往是解决最优化问题的重要工具之一。