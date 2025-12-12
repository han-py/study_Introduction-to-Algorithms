# 势能法 (Potential Method)

> 📘 _算法导论第17.3节学习指南_

## 🎯 1. 简介

**势能法**(Potential Method)，也被称为**物理学家方法**(Physicist's Method)，是摊还分析的第三种方法。势能法与核算法类似，但视角不同：

- **核算法**：将信用存储在数据结构的特定对象上
- **势能法**：将势能存储在整个数据结构中

势能法将预付的工作表示为"势能"，可以在需要时释放以支付后续操作的代价。

## 🤔 2. 势能法 vs 其他方法

| 特性 | 聚合分析 | 核算法 | 势能法 |
|------|----------|--------|--------|
| 分析视角 | 整个操作序列 | 单个操作的信用分配 | 整个数据结构的势能 |
| 信用存储 | 无 | 存储在特定对象上 | 存储在整个数据结构中 |
| 数学表达 | 简单直观 | 直观但需要设计不变式 | 形式化但需要设计势函数 |

## 📚 3. 势能法定义

势能法的核心是定义一个**势函数**(Potential Function)：

> Φ(Dᵢ)：将数据结构Dᵢ映射为一个实数，表示与数据结构Dᵢ相关的势能

第i个操作的摊还代价定义为：
> ĉᵢ = cᵢ + Φ(Dᵢ) - Φ(Dᵢ₋₁)

其中：
- cᵢ是第i个操作的实际代价
- Φ(Dᵢ)是操作后数据结构的势能
- Φ(Dᵢ₋₁)是操作前数据结构的势能

n个操作的总摊还代价为：
> ∑(i=1 to n) ĉᵢ = ∑(i=1 to n) cᵢ + Φ(Dₙ) - Φ(D₀)

如果定义势函数使得Φ(Dₙ) ≥ Φ(D₀)，则总摊还代价是总实际代价的上界。

## 🔍 4. 经典示例详解

### 4.1 栈操作

考虑一个支持以下操作的栈：
- **PUSH(S, x)**：将元素x压入栈顶，实际代价为1
- **POP(S)**：弹出栈顶元素，实际代价为1
- **MULTIPOP(S, k)**：弹出栈顶k个元素（或栈中所有元素），实际代价为min(s, k)

#### 4.1.1 势函数设计

我们定义势函数为：
> Φ(Dᵢ) = 栈中元素个数

初始状态Φ(D₀) = 0，且任何时候Φ(Dᵢ) ≥ 0。

#### 4.1.2 操作分析

1. **PUSH操作**：
   - 实际代价：cᵢ = 1
   - 势能变化：Φ(Dᵢ) - Φ(Dᵢ₋₁) = (s+1) - s = 1
   - 摊还代价：ĉᵢ = 1 + 1 = 2

2. **POP操作**：
   - 实际代价：cᵢ = 1
   - 势能变化：Φ(Dᵢ) - Φ(Dᵢ₋₁) = (s-1) - s = -1
   - 摊还代价：ĉᵢ = 1 + (-1) = 0

3. **MULTIPOP操作**：
   - 实际代价：cᵢ = min(s, k) = k'（假设弹出k'个元素）
   - 势能变化：Φ(Dᵢ) - Φ(Dᵢ₋₁) = (s-k') - s = -k'
   - 摊还代价：ĉᵢ = k' + (-k') = 0

因此，n个操作的总摊还代价为O(n)，每个操作的摊还代价为O(1)。

### 4.2 二进制计数器自增

考虑一个k位二进制计数器，初始值为0。支持INCREMENT操作。

#### 4.2.1 势函数设计

我们定义势函数为：
> Φ(Dᵢ) = 计数器中1的个数

初始状态Φ(D₀) = 0，且任何时候Φ(Dᵢ) ≥ 0。

#### 4.2.2 操作分析

假设第i次INCREMENT操作重置了t位（从1变为0），然后将一位从0变为1：

- 实际代价：cᵢ = t + 1（t位重置 + 1位设置）
- 势能变化：Φ(Dᵢ) - Φ(Dᵢ₋₁) = (bᵢ₋₁ - t + 1) - bᵢ₋₁ = 1 - t
- 摊还代价：ĉᵢ = (t + 1) + (1 - t) = 2

因此，n次INCREMENT操作的总摊还代价为2n，每次操作的摊还代价为O(1)。

### 4.3 动态数组扩容

考虑一个动态数组，当数组满时将其容量扩大一倍。

#### 4.3.1 势函数设计

我们定义势函数为：
> Φ(Dᵢ) = 2·numᵢ - sizeᵢ

其中numᵢ是数组中元素个数，sizeᵢ是数组容量。

为了确保Φ(D₀) = 0，我们可以定义：
> Φ(Dᵢ) = 2·numᵢ - sizeᵢ + 1

这样Φ(D₀) = 2·0 - 1 + 1 = 0，且任何时候Φ(Dᵢ) ≥ 0（因为sizeᵢ ≥ numᵢ）。

#### 4.3.2 操作分析

1. **普通PUSH操作**（不触发扩容）：
   - 实际代价：cᵢ = 1
   - 势能变化：Φ(Dᵢ) - Φ(Dᵢ₋₁) = (2·(num+1) - size + 1) - (2·num - size + 1) = 2
   - 摊还代价：ĉᵢ = 1 + 2 = 3

2. **扩容PUSH操作**：
   - 实际代价：cᵢ = 1 + num（插入元素 + 复制所有元素）
   - 势能变化：Φ(Dᵢ) - Φ(Dᵢ₋₁) = (2·(num+1) - 2·num + 1) - (2·num - num + 1) = (2 - num)
   - 摊还代价：ĉᵢ = (1 + num) + (2 - num) = 3

因此，n次PUSH操作的总摊还代价为3n，每次操作的摊还代价为O(1)。

## 💻 5. C++ 实现详解

### 5.1 栈操作实现

```cpp
class StackWithPotential {
private:
    std::stack<int> data;

public:
    /**
     * 势函数: Φ(Di) = 栈中元素个数
     */
    int potentialFunction() const {
        return data.size();
    }

    void push(int value) {
        int oldPotential = potentialFunction();
        data.push(value);
        int newPotential = potentialFunction();
        int potentialChange = newPotential - oldPotential;
        int amortizedCost = 1 + potentialChange;
        // 输出相关信息...
    }

    void pop() {
        if (!data.empty()) {
            int oldPotential = potentialFunction();
            data.pop();
            int newPotential = potentialFunction();
            int potentialChange = newPotential - oldPotential;
            int amortizedCost = 1 + potentialChange;
            // 输出相关信息...
        }
    }
};
```

### 5.2 二进制计数器实现

```cpp
class BinaryCounterWithPotential {
private:
    std::vector<bool> bits;

public:
    /**
     * 势函数: Φ(Di) = 计数器中1的个数
     */
    int potentialFunction() const {
        int count = 0;
        for (bool bit : bits) {
            if (bit) count++;
        }
        return count;
    }

    void increment() {
        int oldPotential = potentialFunction();
        // 执行INCREMENT操作...
        int newPotential = potentialFunction();
        int potentialChange = newPotential - oldPotential;
        int amortizedCost = actualCost + potentialChange;
        // 输出相关信息...
    }
};
```

### 5.3 动态数组实现

```cpp
class DynamicArrayWithPotential {
private:
    std::vector<int> data;
    int capacity;

public:
    /**
     * 势函数: Φ(Di) = 2 * numi - sizei + 1
     */
    int potentialFunction() const {
        return 2 * data.size() - capacity + 1;
    }

    void push(int value) {
        int oldPotential = potentialFunction();
        // 执行PUSH操作，可能触发扩容...
        int newPotential = potentialFunction();
        int potentialChange = newPotential - oldPotential;
        int amortizedCost = actualCost + potentialChange;
        // 输出相关信息...
    }
};
```

## 📊 6. 算法分析

### 6.1 时间复杂度

| 操作 | 实际代价 | 摊还代价 |
|------|----------|----------|
| 栈 PUSH | 1 | 2 |
| 栈 POP | 1 | 0 |
| 栈 MULTIPOP | min(s,k) | 0 |
| 计数器 INCREMENT | 实际翻转位数 | 2 |
| 动态数组 PUSH | 1或1+复制代价 | 3 |

### 6.2 空间复杂度

势能法不改变数据结构的空间复杂度，只是增加了对势能的跟踪。

## 🎯 7. 关键要点总结

✅ **势能法核心思想**：
- 定义势函数来衡量数据结构的"势能"
- 摊还代价 = 实际代价 + 势能变化
- 总摊还代价是总实际代价的上界

✅ **势函数设计原则**：
- Φ(D₀) = 0（初始势能为0）
- Φ(Dᵢ) ≥ 0（任何时候势能非负）
- 势能变化应该能够抵消昂贵操作的额外代价

✅ **势能法优势**：
- 形式化程度高，数学表达清晰
- 不需要显式跟踪信用分配
- 适用于复杂的数据结构分析

✅ **势能法挑战**：
- 需要精心设计合适的势函数
- 需要证明势函数满足必要条件
- 对初学者来说可能较为抽象

## 🧪 8. 运行示例

当你运行提供的 C++ 代码时，你会看到类似以下的输出：

```
🧮 示例1: 栈操作 (包括MULTIPOP)
----------------------------------------
执行 PUSH(1)
  实际代价: 1 (压入元素)
  势能变化: 1 - 0 = 1
  摊还代价: 1 + 1 = 2
  当前栈内容: 1 
  当前势能: 1
执行 PUSH(2)
  实际代价: 1 (压入元素)
  势能变化: 2 - 1 = 1
  摊还代价: 1 + 1 = 2
  当前栈内容: 1 2 
  当前势能: 2

栈操作统计:
  总操作数: 9
  总实际代价: 12
  总摊还代价: 12
  当前势能: 2
  平均实际代价: 1.33333
  平均摊还代价: 1.33333
```

## 📚 9. 延伸思考

1. **势函数设计的艺术**：
   - 不同的势函数可能导致不同的摊还代价分析
   - 好的势函数应该能够准确反映数据结构的状态

2. **实际应用**：
   - 高级数据结构的分析（如斐波那契堆）
   - 复杂算法的摊还分析
   - 数据库和操作系统的性能分析

3. **与其他方法的关系**：
   - 势能法与核算法在数学上是等价的
   - 有些问题用势能法更容易分析，有些则相反

---

💡 **学习建议**:
通过亲手实现和调试代码，你可以更深入地理解势能法的核心思想。重点关注势能如何随着操作而变化，以及如何通过势能变化来平衡昂贵操作的代价。尝试修改示例参数，观察不同操作序列对势能的影响，这对你掌握势能法很有帮助。