# 栈（Stack）

## 1. 定义

栈（Stack）是一种特殊的线性表，只允许在表的一端进行插入和删除操作。这一端被称为栈顶（Top），另一端被称为栈底（Bottom）。栈遵循后进先出（Last In First Out, LIFO）的原则，即最后进入的元素最先被访问或删除。

## 2. 栈的基本操作

栈支持以下几种基本操作：

1. **Push（入栈）**：将元素添加到栈顶
2. **Pop（出栈）**：移除并返回栈顶元素
3. **Top/Peek（查看栈顶）**：返回栈顶元素但不移除它
4. **IsEmpty（判断是否为空）**：检查栈是否为空
5. **IsFull（判断是否已满）**：检查栈是否已满（对于有固定容量的栈）

## 3. 栈的特性

1. **LIFO原则**：后进先出，最后入栈的元素最先出栈
2. **操作受限**：只能在栈顶进行插入和删除操作
3. **递归性质**：栈具有天然的递归特性，非常适合解决递归问题

## 4. 栈的实现方式

栈可以用两种主要方式实现：

1. **数组实现（顺序栈）**：使用数组存储元素，通过索引跟踪栈顶位置
2. **链表实现（链式栈）**：使用链表存储元素，链表头部作为栈顶

## 5. 算法图解示例

### 5.1 入栈操作示意图

```
入栈元素 5:

栈顶 -> |   |      栈顶 -> | 5 |
        |   |              |   |
        |   |              |   |
        |___|              |___|
栈底                        栈底
```

### 5.2 出栈操作示意图

```
出栈前:               出栈后:

栈顶 -> | 5 |      栈顶 -> |   |
        | 3 |              | 3 |
        | 1 |              | 1 |
        |___|              |___|
栈底                        栈底
```

## 6. 伪代码实现

```
// 栈的抽象数据类型定义
ADT Stack:
    Data:
        同一线性表，具有相同数据类型的元素集合
        
    Operation:
        // 初始化栈
        InitStack(&S)
        
        // 销毁栈
        DestroyStack(&S)
        
        // 清空栈
        ClearStack(&S)
        
        // 判断栈是否为空
        StackEmpty(S)
        
        // 返回栈中元素个数
        StackLength(S)
        
        // 若栈不空，则用e返回栈顶元素
        GetTop(S, &e)
        
        // 插入元素e为新的栈顶元素
        Push(&S, e)
        
        // 若栈不空，则删除栈顶元素，并用e返回其值
        Pop(&S, &e)
        
        // 从栈底到栈顶依次对栈中每个元素进行访问
        StackTraverse(S, visit())
        
    endADT
```

## 7. C++代码实现

```cpp
#include <iostream>
#include <stdexcept>

class Stack {
private:
    int* array;           // 存储栈元素的数组
    int capacity;         // 栈的容量
    int topIndex;         // 指向栈顶元素的索引

public:
    // 构造函数
    explicit Stack(int size) : capacity(size), topIndex(-1) {
        if (size <= 0) {
            throw std::invalid_argument("栈容量必须为正整数");
        }
        array = new int[size];
    }

    // 析构函数
    ~Stack() {
        delete[] array;
    }

    // 拷贝构造函数
    Stack(const Stack& other) : capacity(other.capacity), topIndex(other.topIndex) {
        array = new int[capacity];
        for (int i = 0; i <= topIndex; i++) {
            array[i] = other.array[i];
        }
    }

    // 赋值操作符重载
    Stack& operator=(const Stack& other) {
        if (this != &other) {
            delete[] array;
            capacity = other.capacity;
            topIndex = other.topIndex;
            array = new int[capacity];
            for (int i = 0; i <= topIndex; i++) {
                array[i] = other.array[i];
            }
        }
        return *this;
    }

    // 入栈操作
    void push(int value) {
        if (isFull()) {
            throw std::overflow_error("栈已满，无法执行入栈操作");
        }
        array[++topIndex] = value;
        std::cout << "元素 " << value << " 已入栈" << std::endl;
    }

    // 出栈操作
    int pop() {
        if (isEmpty()) {
            throw std::underflow_error("栈为空，无法执行出栈操作");
        }
        int value = array[topIndex--];
        std::cout << "元素 " << value << " 已出栈" << std::endl;
        return value;
    }

    // 查看栈顶元素但不移除它
    int top() const {
        if (isEmpty()) {
            throw std::underflow_error("栈为空，无法获取栈顶元素");
        }
        return array[topIndex];
    }

    // 检查栈是否为空
    bool isEmpty() const {
        return topIndex == -1;
    }

    // 检查栈是否已满
    bool isFull() const {
        return topIndex == capacity - 1;
    }

    // 获取栈中元素的数量
    int size() const {
        return topIndex + 1;
    }

    // 获取栈的容量
    int getCapacity() const {
        return capacity;
    }

    // 打印栈中所有元素（从栈顶到栈底）
    void display() const {
        if (isEmpty()) {
            std::cout << "栈为空" << std::endl;
            return;
        }

        std::cout << "栈中元素（从栈顶到栈底）: ";
        for (int i = topIndex; i >= 0; i--) {
            std::cout << array[i] << " ";
        }
        std::cout << std::endl;
    }
};
```

## 8. 算法分析

### 8.1 时间复杂度

- **入栈（Push）**：O(1) - 只需在栈顶添加元素
- **出栈（Pop）**：O(1) - 只需移除栈顶元素
- **查看栈顶（Top）**：O(1) - 直接访问栈顶元素
- **判断是否为空（IsEmpty）**：O(1) - 只需检查栈顶指针
- **判断是否已满（IsFull）**：O(1) - 只需比较栈顶指针和容量

### 8.2 空间复杂度

- **数组实现**：O(n) - 需要预先分配固定大小的数组空间
- **链表实现**：O(n) - 每个节点需要额外的指针空间

## 9. 栈的应用场景

1. **函数调用管理**：程序运行时的函数调用栈
2. **表达式求值**：中缀表达式转后缀表达式及求值
3. **括号匹配**：检查代码中括号是否正确匹配
4. **浏览器历史记录**：后退功能的实现
5. **撤销操作**：文本编辑器的撤销功能
6. **深度优先搜索**：DFS算法的实现
7. **递归算法的迭代实现**：将递归转换为显式的栈操作

## 10. 栈在《算法导论》中的相关内容

在《算法导论》第10章中介绍了栈作为一种基本数据结构。栈是最简单的动态集合之一，实现了后进先出（LIFO）策略。

书中指出，栈的INSERT操作被称为PUSH，DELETE操作被称为POP。虽然栈可以用数组或链表实现，但在任何时刻至多只有栈顶的元素可以被访问。

## 11. 测试示例

```cpp
void demonstrateStackOperations() {
    try {
        std::cout << "=== 栈操作演示 ===" << std::endl;
        
        // 创建一个容量为5的栈
        Stack stack(5);
        std::cout << "创建了一个容量为 " << stack.getCapacity() << " 的栈" << std::endl;

        // 检查栈是否为空
        std::cout << "栈是否为空: " << (stack.isEmpty() ? "是" : "否") << std::endl;

        // 入栈操作
        std::cout << "\n--- 入栈操作 ---" << std::endl;
        stack.push(10);
        stack.push(20);
        stack.push(30);
        stack.display();

        // 查看栈顶元素
        std::cout << "\n--- 查看栈顶元素 ---" << std::endl;
        std::cout << "栈顶元素是: " << stack.top() << std::endl;
        std::cout << "栈的大小: " << stack.size() << std::endl;

        // 继续入栈
        std::cout << "\n--- 继续入栈 ---" << std::endl;
        stack.push(40);
        stack.push(50);
        stack.display();
        std::cout << "栈是否已满: " << (stack.isFull() ? "是" : "否") << std::endl;

        // 尝试在满栈时入栈
        std::cout << "\n--- 尝试在满栈时入栈 ---" << std::endl;
        try {
            stack.push(60);
        } catch (const std::overflow_error& e) {
            std::cout << "捕获异常: " << e.what() << std::endl;
        }

        // 出栈操作
        std::cout << "\n--- 出栈操作 ---" << std::endl;
        stack.pop();
        stack.display();
        stack.pop();
        stack.display();

        // 检查栈的状态
        std::cout << "栈的大小: " << stack.size() << std::endl;
        std::cout << "栈是否为空: " << (stack.isEmpty() ? "是" : "否") << std::endl;
        std::cout << "栈是否已满: " << (stack.isFull() ? "是" : "否") << std::endl;

        // 继续出栈直到栈为空
        std::cout << "\n--- 继续出栈直到栈为空 ---" << std::endl;
        while (!stack.isEmpty()) {
            stack.pop();
            if (!stack.isEmpty()) {
                stack.display();
            }
        }
        std::cout << "栈是否为空: " << (stack.isEmpty() ? "是" : "否") << std::endl;

        // 尝试在空栈时出栈
        std::cout << "\n--- 尝试在空栈时出栈 ---" << std::endl;
        try {
            stack.pop();
        } catch (const std::underflow_error& e) {
            std::cout << "捕获异常: " << e.what() << std::endl;
        }

    } catch (const std::exception& e) {
        std::cerr << "发生错误: " << e.what() << std::endl;
    }
}
```

## 12. 总结

栈作为一种重要的数据结构，在计算机科学中有广泛的应用。它的后进先出特性使其成为解决许多问题的理想工具，特别是那些涉及回溯或嵌套结构的问题。理解和掌握栈的操作对于学习更高级的数据结构和算法至关重要。