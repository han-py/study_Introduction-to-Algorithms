# 链表 (Linked Lists)

本文档详细介绍了《算法导论》第十章中讨论的三种基本链表数据结构的实现：
1. 单向链表 (Singly Linked List)
2. 双向链表 (Doubly Linked List)
3. 循环链表 (Circular Linked List)

## 1. 单向链表 (Singly Linked List)

单向链表是最简单的链表形式，其中每个节点包含数据和指向下一个节点的指针。

### 特点
- 每个节点只包含一个指向后继节点的指针
- 只能从头到尾进行遍历
- 内存开销较小，因为只需要存储一个指针

### 结构定义

```cpp
struct Node {
    T data;
    Node* next;
    
    Node(const T& value) : data(value), next(nullptr) {}
};
```

### 主要操作

#### 插入操作
- `push_front(value)`: 在链表头部插入新元素
- `insert(index, value)`: 在指定位置插入新元素

#### 删除操作
- `pop_front()`: 删除链表头部元素
- `erase(index)`: 删除指定位置的元素

#### 访问操作
- `front()`: 访问链表第一个元素
- `empty()`: 检查链表是否为空
- `getSize()`: 获取链表大小

### 时间复杂度
| 操作 | 时间复杂度 |
|------|------------|
| 在头部插入 | O(1) |
| 在尾部插入 | O(n) |
| 在中间插入 | O(n) |
| 删除头部元素 | O(1) |
| 删除尾部元素 | O(n) |
| 删除中间元素 | O(n) |
| 访问头部元素 | O(1) |
| 访问尾部元素 | O(n) |

## 2. 双向链表 (Doubly Linked List)

双向链表在单向链表的基础上增加了指向前驱节点的指针，使得可以从两个方向遍历链表。

### 特点
- 每个节点包含两个指针：一个指向前驱节点，一个指向后继节点
- 可以从两个方向遍历链表
- 支持高效的头部和尾部操作

### 结构定义

```cpp
struct Node {
    T data;
    Node* next;
    Node* prev;
    
    Node(const T& value) : data(value), next(nullptr), prev(nullptr) {}
};
```

### 主要操作

除了单向链表的所有操作外，还支持：
- `push_back(value)`: 在链表尾部插入新元素
- `pop_back()`: 删除链表尾部元素
- `back()`: 访问链表最后一个元素
- `printReverse()`: 反向打印链表

### 时间复杂度
| 操作 | 时间复杂度 |
|------|------------|
| 在头部插入 | O(1) |
| 在尾部插入 | O(1) |
| 在中间插入 | O(n) |
| 删除头部元素 | O(1) |
| 删除尾部元素 | O(1) |
| 删除中间元素 | O(n) |
| 访问头部元素 | O(1) |
| 访问尾部元素 | O(1) |

## 3. 循环链表 (Circular Linked List)

循环链表是一种特殊的链表，其中最后一个节点指向第一个节点，形成一个环。

### 特点
- 最后一个节点的指针指向第一个节点
- 可以从任意节点开始遍历整个链表
- 适用于需要循环访问数据的场景

### 结构定义

循环链表使用与单向链表相同的节点结构，但在连接方式上有所不同：
```cpp
struct Node {
    T data;
    Node* next;
    
    Node(const T& value) : data(value), next(nullptr) {}
};
```

### 主要操作

循环链表支持的操作与单向链表类似，但需要注意维护循环特性：
- `push_front(value)`: 在链表头部插入新元素
- `push_back(value)`: 在链表尾部插入新元素
- `pop_front()`: 删除链表头部元素
- `insert(index, value)`: 在指定位置插入新元素
- `erase(index)`: 删除指定位置的元素

### 时间复杂度
与单向链表相同，但由于循环特性，在某些特定场景下可能有更好的性能表现。

## 实现细节

所有实现都采用了以下设计原则：

### 模板类设计
所有链表实现都是模板类，可以存储任意类型的数据：
```cpp
template<typename T>
class LinkedList { /* ... */ };
```

### 异常安全
实现了适当的异常处理机制：
- 当对空链表执行非法操作时抛出 `std::runtime_error`
- 当索引超出范围时抛出 `std::out_of_range`

### 内存管理
- 使用构造函数和析构函数自动管理内存
- 提供 `clear()` 方法清空整个链表
- 所有节点通过 `new` 和 `delete` 进行分配和释放

### 优化技巧

#### 双向链表中的双向遍历优化
在双向链表的 `insert()` 和 `erase()` 操作中，根据索引位置选择从头部或尾部开始遍历，以减少遍历步数：

```cpp
if (index < size / 2) {
    // 从头部开始遍历
} else {
    // 从尾部开始遍历
}
```

## 使用示例

以下是使用这些链表的简单示例：

### 单向链表示例
```cpp
SinglyLinkedList<int> sll;
sll.push_front(1);
sll.push_front(2);
sll.insert(1, 3);
sll.print(); // 输出: List: 2 -> 3 -> 1 -> nullptr
```

### 双向链表示例
```cpp
DoublyLinkedList<int> dll;
dll.push_front(1);
dll.push_back(2);
dll.insert(1, 3);
dll.print(); // 输出: List: nullptr <-> 1 <-> 3 <-> 2 <-> nullptr
dll.printReverse(); // 输出: Reverse List: nullptr <-> 2 <-> 3 <-> 1 <-> nullptr
```

### 循环链表示例
```cpp
CircularLinkedList<int> cll;
cll.push_front(1);
cll.push_back(2);
cll.insert(1, 3);
cll.print(); // 输出: Circular List: 1 -> 3 -> 2 -> (back to head)
```

## 应用场景

### 单向链表
- 实现简单的序列容器
- 图算法中的邻接表表示
- 实现其他数据结构（如栈）的基础

### 双向链表
- 实现需要频繁在两端操作的数据结构（如双端队列）
- 浏览器历史记录功能
- LRU缓存实现

### 循环链表
- 多人游戏中的玩家轮流机制
- 操作系统的进程调度
- 圆形缓冲区实现

## 总结

链表作为一种基础而重要的数据结构，提供了数组之外的另一种线性存储方案。相比数组，链表的主要优势在于动态大小和高效的插入/删除操作，劣势在于不支持随机访问和额外的内存开销。

选择合适的链表类型取决于具体的应用场景：
- 如果只需要简单的线性存储且主要在头部操作，单向链表是最佳选择
- 如果需要频繁在两端操作或者反向遍历，应选择双向链表
- 如果应用场景涉及循环访问模式，则循环链表更为合适