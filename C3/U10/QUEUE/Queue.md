# 队列（Queue）

## 1. 定义

队列（Queue）是一种特殊的线性表，只允许在表的一端进行插入操作，在另一端进行删除操作。允许插入的一端称为队尾（Rear），允许删除的一端称为队首（Front）。队列遵循先进先出（First In First Out, FIFO）的原则，即最早进入队列的元素最先被访问或删除。

## 2. 队列的基本操作

队列支持以下几种基本操作：

1. **Enqueue（入队）**：将元素添加到队尾
2. **Dequeue（出队）**：移除并返回队首元素
3. **Front（查看队首）**：返回队首元素但不移除它
4. **Rear（查看队尾）**：返回队尾元素但不移除它
5. **IsEmpty（判断是否为空）**：检查队列是否为空
6. **IsFull（判断是否已满）**：检查队列是否已满（对于有固定容量的队列）

## 3. 队列的特性

1. **FIFO原则**：先进先出，最先入队的元素最先出队
2. **操作受限**：只能在队首进行删除操作，在队尾进行插入操作
3. **顺序性**：保持元素进入队列的顺序

## 4. 队列的实现方式

队列可以用多种方式实现：

1. **数组实现（顺序队列）**：使用数组存储元素，通过索引跟踪队首和队尾位置
2. **循环数组实现（循环队列）**：使用数组实现，但通过模运算实现循环利用空间
3. **链表实现（链式队列）**：使用链表存储元素，链表头部作为队首，链表尾部作为队尾

## 5. 算法图解示例

### 5.1 入队操作示意图

```
入队元素 5:

队首 -> | 3 | 1 |   |   |   | <- 队尾    队首 -> | 3 | 1 | 5 |   |   | <- 队尾
```

### 5.2 出队操作示意图

```
出队前:                          出队后:

队首 -> | 3 | 1 | 5 |   |   |    队首 -> | 1 | 5 |   |   |   |
```

### 5.3 循环队列示意图

```
循环队列（容量为5）:

队首 -> | 7 | 3 | 1 | 5 | 9 | <- 队尾    队首 -> | 7 | 3 | 1 | 5 | 9 | <- 队尾
         ^                   ^              ^     ^     ^
         |                   |              |     |     |
      frontIndex         rearIndex      front rear   新元素插入位置

出队两个元素后:

队首 -> |   |   | 1 | 5 | 9 | <- 队尾
               ^     ^
               |     |
            front  rear

再入队两个元素后:

队首 -> |11 |13 | 1 | 5 | 9 | <- 队尾
               ^     ^
               |     |
            front  rear
```

## 6. 伪代码实现

```
// 队列的抽象数据类型定义
ADT Queue:
    Data:
        同一线性表，具有相同数据类型的元素集合
        
    Operation:
        // 初始化队列
        InitQueue(&Q)
        
        // 销毁队列
        DestroyQueue(&Q)
        
        // 清空队列
        ClearQueue(&Q)
        
        // 判断队列是否为空
        QueueEmpty(Q)
        
        // 返回队列中元素个数
        QueueLength(Q)
        
        // 若队列不空，则用e返回队首元素
        GetHead(Q, &e)
        
        // 插入元素e为新的队尾元素
        EnQueue(&Q, e)
        
        // 若队列不空，则删除队首元素，并用e返回其值
        DeQueue(&Q, &e)
        
        // 从队首到队尾依次对队列中每个元素进行访问
        QueueTraverse(Q, visit())
        
    endADT
```

## 7. C++代码实现

```cpp
#include <iostream>
#include <stdexcept>

class Queue {
private:
    int* array;           // 存储队列元素的数组
    int capacity;         // 队列的容量
    int frontIndex;       // 队首索引
    int rearIndex;        // 队尾索引
    int count;            // 队列中元素的数量

public:
    // 构造函数
    explicit Queue(int size) : capacity(size), frontIndex(0), rearIndex(-1), count(0) {
        if (size <= 0) {
            throw std::invalid_argument("队列容量必须为正整数");
        }
        array = new int[size];
    }

    // 析构函数
    ~Queue() {
        delete[] array;
    }

    // 拷贝构造函数
    Queue(const Queue& other) : capacity(other.capacity), frontIndex(other.frontIndex), 
                                rearIndex(other.rearIndex), count(other.count) {
        array = new int[capacity];
        for (int i = 0; i < count; i++) {
            array[i] = other.array[(other.frontIndex + i) % capacity];
        }
        frontIndex = 0;
        rearIndex = count - 1;
    }

    // 赋值操作符重载
    Queue& operator=(const Queue& other) {
        if (this != &other) {
            delete[] array;
            
            capacity = other.capacity;
            frontIndex = other.frontIndex;
            rearIndex = other.rearIndex;
            count = other.count;
            
            array = new int[capacity];
            for (int i = 0; i < count; i++) {
                array[i] = other.array[(other.frontIndex + i) % capacity];
            }
            frontIndex = 0;
            rearIndex = count - 1;
        }
        return *this;
    }

    // 入队操作
    void enqueue(int value) {
        if (isFull()) {
            throw std::overflow_error("队列已满，无法执行入队操作");
        }
        rearIndex = (rearIndex + 1) % capacity;
        array[rearIndex] = value;
        count++;
        std::cout << "元素 " << value << " 已入队" << std::endl;
    }

    // 出队操作
    int dequeue() {
        if (isEmpty()) {
            throw std::underflow_error("队列为空，无法执行出队操作");
        }
        int value = array[frontIndex];
        frontIndex = (frontIndex + 1) % capacity;
        count--;
        std::cout << "元素 " << value << " 已出队" << std::endl;
        return value;
    }

    // 查看队首元素但不移除它
    int front() const {
        if (isEmpty()) {
            throw std::underflow_error("队列为空，无法获取队首元素");
        }
        return array[frontIndex];
    }

    // 查看队尾元素但不移除它
    int rear() const {
        if (isEmpty()) {
            throw std::underflow_error("队列为空，无法获取队尾元素");
        }
        return array[rearIndex];
    }

    // 检查队列是否为空
    bool isEmpty() const {
        return count == 0;
    }

    // 检查队列是否已满
    bool isFull() const {
        return count == capacity;
    }

    // 获取队列中元素的数量
    int size() const {
        return count;
    }

    // 获取队列的容量
    int getCapacity() const {
        return capacity;
    }

    // 打印队列中所有元素（从队首到队尾）
    void display() const {
        if (isEmpty()) {
            std::cout << "队列为空" << std::endl;
            return;
        }

        std::cout << "队列中元素（从队首到队尾）: ";
        for (int i = 0; i < count; i++) {
            std::cout << array[(frontIndex + i) % capacity] << " ";
        }
        std::cout << std::endl;
    }
};
```

## 8. 算法分析

### 8.1 时间复杂度

- **入队（Enqueue）**：O(1) - 只需在队尾添加元素
- **出队（Dequeue）**：O(1) - 只需移除队首元素
- **查看队首（Front）**：O(1) - 直接访问队首元素
- **查看队尾（Rear）**：O(1) - 直接访问队尾元素
- **判断是否为空（IsEmpty）**：O(1) - 只需检查元素计数
- **判断是否已满（IsFull）**：O(1) - 只需比较元素计数和容量

### 8.2 空间复杂度

- **数组实现**：O(n) - 需要预先分配固定大小的数组空间
- **链表实现**：O(n) - 每个节点需要额外的指针空间

## 9. 队列的应用场景

1. **广度优先搜索**：BFS算法的实现
2. **任务调度**：操作系统中的进程调度
3. **缓冲区**：处理异步数据流（如IO缓冲区）
4. **打印机任务队列**：打印任务的排队处理
5. **消息队列**：分布式系统中的消息传递
6. **页面置换算法**：如LRU（最近最少使用）算法
7. **树的层次遍历**：按层级遍历树节点

## 10. 队列在《算法导论》中的相关内容

在《算法导论》第10章中介绍了队列作为一种基本数据结构。队列与栈类似，也是一种动态集合，但实现的是先进先出（FIFO）策略。

书中指出，队列的INSERT操作被称为ENQUEUE，DELETE操作被称为DEQUEUE。与栈一样，队列也可以用数组或链表实现，但在任何时刻至多只有队首和队尾的元素可以直接访问。

循环队列是队列的一种重要实现方式，通过模运算巧妙地解决了普通顺序队列中出现的"假溢出"问题，充分利用了数组空间。

## 11. 测试示例

```cpp
void demonstrateQueueOperations() {
    try {
        std::cout << "=== 队列操作演示 ===" << std::endl;
        
        // 创建一个容量为5的队列
        Queue queue(5);
        std::cout << "创建了一个容量为 " << queue.getCapacity() << " 的队列" << std::endl;

        // 检查队列是否为空
        std::cout << "队列是否为空: " << (queue.isEmpty() ? "是" : "否") << std::endl;

        // 入队操作
        std::cout << "\n--- 入队操作 ---" << std::endl;
        queue.enqueue(10);
        queue.enqueue(20);
        queue.enqueue(30);
        queue.display();

        // 查看队首和队尾元素
        std::cout << "\n--- 查看队首和队尾元素 ---" << std::endl;
        std::cout << "队首元素是: " << queue.front() << std::endl;
        std::cout << "队尾元素是: " << queue.rear() << std::endl;
        std::cout << "队列的大小: " << queue.size() << std::endl;

        // 继续入队
        std::cout << "\n--- 继续入队 ---" << std::endl;
        queue.enqueue(40);
        queue.enqueue(50);
        queue.display();
        std::cout << "队列是否已满: " << (queue.isFull() ? "是" : "否") << std::endl;

        // 尝试在满队列时入队
        std::cout << "\n--- 尝试在满队列时入队 ---" << std::endl;
        try {
            queue.enqueue(60);
        } catch (const std::overflow_error& e) {
            std::cout << "捕获异常: " << e.what() << std::endl;
        }

        // 出队操作
        std::cout << "\n--- 出队操作 ---" << std::endl;
        queue.dequeue();
        queue.display();
        queue.dequeue();
        queue.display();

        // 检查队列的状态
        std::cout << "队列的大小: " << queue.size() << std::endl;
        std::cout << "队列是否为空: " << (queue.isEmpty() ? "是" : "否") << std::endl;
        std::cout << "队列是否已满: " << (queue.isFull() ? "是" : "否") << std::endl;

        // 继续出队直到队列为空
        std::cout << "\n--- 继续出队直到队列为空 ---" << std::endl;
        while (!queue.isEmpty()) {
            queue.dequeue();
            if (!queue.isEmpty()) {
                queue.display();
            }
        }
        std::cout << "队列是否为空: " << (queue.isEmpty() ? "是" : "否") << std::endl;

        // 尝试在空队列时出队
        std::cout << "\n--- 尝试在空队列时出队 ---" << std::endl;
        try {
            queue.dequeue();
        } catch (const std::underflow_error& e) {
            std::cout << "捕获异常: " << e.what() << std::endl;
        }

        // 循环队列特性演示
        std::cout << "\n--- 循环队列特性演示 ---" << std::endl;
        Queue circularQueue(4);
        circularQueue.enqueue(100);
        circularQueue.enqueue(200);
        circularQueue.enqueue(300);
        circularQueue.display();
        
        circularQueue.dequeue();
        circularQueue.dequeue();
        circularQueue.display();
        
        // 利用释放的空间继续入队
        circularQueue.enqueue(400);
        circularQueue.enqueue(500);
        circularQueue.enqueue(600);
        circularQueue.display();
        
        std::cout << "队列是否已满: " << (circularQueue.isFull() ? "是" : "否") << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "发生错误: " << e.what() << std::endl;
    }
}
```

## 12. 总结

队列作为一种重要的数据结构，在计算机科学中有广泛的应用。它的先进先出特性使其成为解决许多问题的理想工具，特别是那些涉及顺序处理或广度优先搜索的问题。理解和掌握队列的操作对于学习更高级的数据结构和算法至关重要。

循环队列是对普通顺序队列的重要改进，通过巧妙地使用模运算，解决了空间浪费的问题，提高了空间利用率。在实际应用中，循环队列经常被用来实现各种缓冲区和调度算法。