# 聚合分析 (Aggregate Analysis)

> 📘 _算法导论第17.1节学习指南_

## 🎯 1. 简介

**聚合分析**(Aggregate Analysis)是摊还分析(Amortized Analysis)的第一种方法，也是最直观的方法。在摊还分析中，我们分析数据结构操作序列的平均时间，而不是单个操作的最坏情况时间。

聚合分析特别适用于这样的场景：
- 大多数操作都很便宜
- 少数操作可能很昂贵
- 昂贵操作相对稀少

通过聚合分析，我们可以得到更紧密的界，而不是仅仅使用最坏情况分析。

## 🤔 2. 为什么要使用摊还分析？

考虑一个简单的例子：动态数组的插入操作。

如果我们只看单次操作的最坏情况：
- 大部分插入操作：O(1)
- 扩容时的插入操作：O(n)

如果我们说每次操作都是O(n)，这是过于悲观的估计。

通过摊还分析，我们可以得到更准确的估计：**摊还代价为O(1)**。

## 📚 3. 聚合分析定义

聚合分析的核心思想是：

> 对于n个操作的序列，如果最坏情况下总时间为T(n)，那么每个操作的**摊还代价**(amortized cost)为T(n)/n。

这种方法的关键在于：
1. 不涉及概率（与平均情况分析不同）
2. 保证最坏情况下每个操作的平均性能
3. 通过分析整个操作序列来"均摊"成本

## 🔍 4. 经典示例详解

### 4.1 栈操作

考虑一个支持以下操作的栈：
- **PUSH(S, x)**：将元素x压入栈顶，实际代价为1
- **POP(S)**：弹出栈顶元素，实际代价为1
- **MULTIPOP(S, k)**：弹出栈顶k个元素（或栈中所有元素），实际代价为min(s, k)，其中s为栈中元素个数

#### 4.1.1 单独分析的局限性

如果单独分析每个操作：
- PUSH: O(1)
- POP: O(1)
- MULTIPOP: O(n) （最坏情况）

#### 4.1.2 聚合分析方法

考虑n个操作的序列：
1. 每个元素最多被PUSH一次：总PUSH代价 ≤ n
2. 每个元素最多被POP一次（无论是通过POP还是MULTIPOP）：总POP代价 ≤ n
3. 因此，总实际代价 ≤ 2n

所以每个操作的摊还代价为 **O(1)**！

### 4.2 二进制计数器自增

考虑一个k位二进制计数器，初始值为0。支持INCREMENT操作：
```
INCREMENT(A)
i = 0
while i < A.length and A[i] == 1
    A[i] = 0
    i = i + 1
if i < A.length
    A[i] = 1
```

#### 4.2.1 单独分析的局限性

单次INCREMENT操作最坏情况下需要翻转k位，所以单次操作为O(k)。

n次操作的最坏情况分析：O(nk)

#### 4.2.2 聚合分析方法

让我们分析第i位翻转的频率：
- A[0]：每次INCREMENT都会翻转（频率：n）
- A[1]：每隔一次INCREMENT翻转（频率：n/2）
- A[2]：每隔四次INCREMENT翻转（频率：n/4）
- A[i]：每隔2^i次INCREMENT翻转（频率：n/2^i）

总翻转次数：
```
T(n) = n/2^0 + n/2^1 + n/2^2 + ... + n/2^(k-1)
     = n × (1 + 1/2 + 1/4 + ... + 1/2^(k-1))
     = n × (2 - 1/2^(k-1))
     < 2n
```

因此，n次INCREMENT操作的总时间为O(n)，每次操作的摊还代价为**O(1)**。

### 4.3 动态数组扩容

考虑一个动态数组，当数组满时将其容量扩大一倍。

#### 4.3.1 成本分析

设初始容量为1：
- 第1个元素：直接插入，代价1
- 第2个元素：需要扩容，复制1个元素，代价1+1=2
- 第3,4个元素：直接插入，代价各1
- 第5个元素：需要扩容，复制4个元素，代价1+4=5
- ...

#### 4.3.2 聚合分析方法

对于n次插入操作：
1. 插入元素本身的代价：n
2. 复制元素的代价：
   - 第1次扩容：复制1个元素
   - 第2次扩容：复制2个元素
   - 第3次扩容：复制4个元素
   - ...
   - 第j次扩容：复制2^(j-1)个元素

总复制代价：
```
1 + 2 + 4 + ... + 2^⌊lg n⌋ = 2^(⌊lg n⌋+1) - 1 < 2n
```

因此，总代价为n + 2n = 3n = O(n)，摊还代价为**O(1)**。

## 💻 5. C++ 实现详解

### 5.1 栈操作实现

```cpp
class StackWithMultipop {
private:
    std::vector<int> data;
    int totalOperations;     // 总操作数
    int totalActualCost;     // 总实际代价

public:
    void push(int value) {
        data.push_back(value);
        totalOperations++;
        totalActualCost += 1;  // 实际代价为1
    }

    void pop() {
        if (!data.empty()) {
            data.pop_back();
            totalOperations++;
            totalActualCost += 1;  // 实际代价为1
        }
    }

    void multipop(int k) {
        int popCount = std::min(k, (int)data.size());
        for (int i = 0; i < popCount; i++) {
            data.pop_back();
        }
        totalOperations++;
        totalActualCost += popCount;  // 实际代价为popCount
    }
};
```

### 5.2 二进制计数器实现

```cpp
class BinaryCounter {
private:
    std::vector<bool> bits;
    int totalIncrements;
    int totalBitFlips;

public:
    void increment() {
        int flips = 0;
        int i = 0;
        
        // 翻转所有连续的1位为0
        while (i < bits.size() && bits[i] == true) {
            bits[i] = false;
            flips++;
            i++;
        }
        
        // 如果还有剩余位，将第一个0位翻转为1
        if (i < bits.size()) {
            bits[i] = true;
            flips++;
        }
        
        totalIncrements++;
        totalBitFlips += flips;
    }
};
```

### 5.3 动态数组实现

```cpp
class DynamicArray {
private:
    std::vector<int> data;
    int capacity;
    int totalOperations;
    int totalActualCost;

public:
    void push(int value) {
        int cost = 1;  // 插入元素的代价
        
        // 检查是否需要扩容
        if (data.size() == capacity) {
            int oldCapacity = capacity;
            capacity *= 2;  // 扩容为原来的2倍
            
            // 复制元素的代价
            cost += data.size();  // 需要复制所有现有元素
        }
        
        data.push_back(value);
        totalOperations++;
        totalActualCost += cost;
    }
};
```

## 📊 6. 算法分析

### 6.1 时间复杂度

| 操作 | 最坏情况 | 摊还代价 |
|------|----------|----------|
| 栈 PUSH | O(1) | O(1) |
| 栈 POP | O(1) | O(1) |
| 栈 MULTIPOP | O(n) | O(1) |
| 计数器 INCREMENT | O(k) | O(1) |
| 动态数组 PUSH | O(n) | O(1) |

### 6.2 空间复杂度

所有示例的空间复杂度都取决于存储数据结构本身的需求，聚合分析不改变空间复杂度。

## 🎯 7. 关键要点总结

✅ **聚合分析适用场景**：
- 操作序列中大多数操作便宜，少数操作昂贵
- 昂贵操作相对稀少
- 可以分析整个序列的总代价

✅ **聚合分析步骤**：
1. 确定n个操作序列的最坏情况总时间T(n)
2. 每个操作的摊还代价为T(n)/n

✅ **与平均情况分析的区别**：
- 聚合分析：不涉及概率，是真正的最坏情况分析
- 平均情况分析：基于输入的概率分布

✅ **重要结论**：
- 聚合分析给出的是每个操作的平均代价上界
- 个别操作仍可能代价较高
- 适用于分析操作序列的整体性能

## 🧪 8. 运行示例

当你运行提供的 C++ 代码时，你会看到类似以下的输出：

```
🧮 示例1: 栈操作 (包括MULTIPOP)
----------------------------------------
执行 PUSH(1)
  当前栈内容: 1 
执行 PUSH(2)
  当前栈内容: 1 2 
执行 PUSH(3)
  当前栈内容: 1 2 3 
执行 PUSH(4)
  当前栈内容: 1 2 3 4 
执行 PUSH(5)
  当前栈内容: 1 2 3 4 5 
执行 POP - 弹出元素: 5
  当前栈内容: 1 2 3 4 
执行 MULTIPOP(3) - 实际弹出 3 个元素
  弹出元素: 4
  弹出元素: 3
  弹出元素: 2
  当前栈内容: 1 
执行 PUSH(6)
  当前栈内容: 1 6 
执行 PUSH(7)
  当前栈内容: 1 6 7 

栈操作统计:
  总操作数: 9
  总实际代价: 12
  平均代价(摊还代价): 1.33333
```

## 📚 9. 延伸思考

1. **其他摊还分析方法**：
   - 核算法(Accounting Method)
   - 势能法(Potential Method)

2. **实际应用**：
   - STL容器的实现（如vector的扩容策略）
   - 数据库事务处理
   - 内存管理系统

3. **扩展问题**：
   - 如果二进制计数器支持DECREMENT操作，摊还分析会如何变化？
   - 如果动态数组扩容因子不是2而是其他值，分析结果会怎样？

---

💡 **学习建议**:
通过亲手实现和调试代码，你可以更深入地理解聚合分析的核心思想。尝试修改示例参数，观察不同操作序列对摊还代价的影响，这对你掌握摊还分析很有帮助。