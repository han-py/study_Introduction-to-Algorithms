# 散列表 (Hash Table)

## 1. 算法简介

散列表（Hash Table），也称为哈希表，是《算法导论》第11章介绍的一种非常重要的数据结构。它是实现字典操作（插入、删除、查找）的一种有效方法。尽管在最坏情况下，散列表中查找一个元素的时间与链表中查找的时间相同，为Θ(n)，但在实际应用中，散列表的性能非常好。在一些合理的假设下，在散列表中查找一个元素的期望时间为O(1)。

散列表是普通数组概念的推广。由于对普通数组可以直接寻址，使得能在O(1)时间内访问数组中的任意位置。如果存储空间允许，我们可以提供一个数组，为每个可能的关键字保留一个位置，以利用直接寻址技术的优势。但当实际存储的关键字数目比全部的可能关键字总数要小时，采用散列表就成为直接数组寻址的一种有效替代，因为散列表使用一个长度与实际存储的关键字数目成比例的数组来存储。

在散列表中，不是直接把关键字作为数组的下标，而是根据关键字计算出相应的下标。这就带来了一个问题：多个关键字可能映射到同一个数组下标，这种情况称为**冲突（collision）**。《算法导论》中介绍了处理冲突的两种主要方法：链接法和开放寻址法。

## 2. 算法思想

### 2.1 直接寻址表

当关键字的全域U比较小时，直接寻址是一种简单有效的技术。假定某应用需要一个动态集合，其关键字取自全域U = {0, 1, ..., m-1}，其中的m不是太大。我们可以使用一个数组T[0..m-1]，使得每个槽对应全域U中的一个关键字。如果不存在关键字为k的元素，则T[k] = NIL。

直接寻址的优点：
- 查找、插入、删除操作的时间复杂度都是O(1)
- 结构简单直观

直接寻址的缺点：
- 当全域U很大时，需要大量的存储空间
- 当实际使用的关键字集合K相对于全域U很小时，会造成大量空间浪费

### 2.2 散列表

散列表通过散列函数h将关键字k映射到槽h(k)中，从而减少了所需的存储空间。散列函数h将关键字全域U映射到散列表T[0..m-1]的槽位中，即h: U → {0, 1, ..., m-1}。

散列表的性能很大程度上取决于散列函数的选择。一个好的散列函数应满足简单性和均匀性：
- **简单性**：应在O(1)时间内计算出关键字的散列值
- **均匀性**：应尽可能均匀地将关键字分布在散列表的槽位中

### 2.3 冲突解决

当两个或多个关键字映射到同一个槽位时，就会产生冲突。有两种主要的冲突解决方法：

#### 2.3.1 链接法（Chaining）

在链接法中，我们将所有散列到同一个槽中的元素放在一个链表中。槽j中存放指向链表的指针，该链表包含所有散列到j中的元素。

#### 2.3.2 开放寻址法（Open Addressing）

在开放寻址法中，所有元素都存放在散列表中。当要插入一个元素时，我们连续地检查散列表的各项，直到找到一个空槽来放置待插入的元素为止。

## 3. 算法步骤

### 3.1 散列表的实现步骤（链接法）

1. 定义散列表结构，包含一个桶数组，每个桶是一个链表
2. 设计散列函数，将关键字映射到桶索引
3. 实现插入操作：计算关键字的哈希值，将其添加到对应桶的链表中
4. 实现查找操作：计算关键字的哈希值，遍历对应桶的链表查找关键字
5. 实现删除操作：计算关键字的哈希值，从对应桶的链表中删除关键字

### 3.2 散列函数设计

1. **除法散列法**：h(k) = k mod m，其中m为桶的数量
2. **乘法散列法**：h(k) = ⌊m(kA mod 1)⌋，其中A为常数(0<A<1)
3. **全域散列法**：从一组精心设计的函数中随机选择一个作为散列函数

## 4. 算法图解示例

### 4.1 链接法示意图

```
散列表 (m=7):

索引  链表
0   → 
1   → (1,"one") → (8,"eight") → (15,"fifteen")
2   → (2,"two") → (9,"nine")
3   → (3,"three")
4   → 
5   → 
6   → 

插入键值对 (1,"one"), (2,"two"), (3,"three"), (8,"eight"), (9,"nine"), (15,"fifteen"):
- h(1) = 1 mod 7 = 1
- h(2) = 2 mod 7 = 2
- h(3) = 3 mod 7 = 3
- h(8) = 8 mod 7 = 1 (与键1冲突)
- h(9) = 9 mod 7 = 2 (与键2冲突)
- h(15) = 15 mod 7 = 1 (与键1和8冲突)
```

### 4.2 查找示意图

```
查找键8:
1. 计算哈希值: h(8) = 8 mod 7 = 1
2. 访问桶1: 遍历链表 [(1,"one") → (8,"eight") → (15,"fifteen")]
3. 找到键8，返回值"eight"
```

### 4.3 删除示意图

```
删除键8:
1. 计算哈希值: h(8) = 8 mod 7 = 1
2. 访问桶1: 遍历链表 [(1,"one") → (8,"eight") → (15,"fifteen")]
3. 找到键8，从链表中删除该节点
4. 桶1的新链表: [(1,"one") → (15,"fifteen")]
```

## 5. 伪代码实现

### 5.1 散列表结构定义

```
TABLE:
    bucket[0..m-1]  // 桶数组，每个桶是一个链表
    size            // 当前元素数量
    capacity        // 桶的数量

NODE:
    key             // 关键字
    value           // 值
    next            // 指向链表中下一个节点的指针
```

### 5.2 散列函数

```
HASH(k):
    return k mod m
```

### 5.3 插入操作

```
INSERT(T, k, v):
    index = HASH(k)
    bucket = T.bucket[index]
    // 检查键是否已存在
    for each node in bucket
        if node.key == k
            node.value = v  // 更新值
            return
    // 插入新节点
    newNode = new NODE()
    newNode.key = k
    newNode.value = v
    newNode.next = bucket.head
    bucket.head = newNode
    T.size = T.size + 1
```

### 5.4 查找操作

```
SEARCH(T, k):
    index = HASH(k)
    bucket = T.bucket[index]
    for each node in bucket
        if node.key == k
            return node.value
    error "Key not found"
```

### 5.5 删除操作

```
DELETE(T, k):
    index = HASH(k)
    bucket = T.bucket[index]
    prev = NIL
    current = bucket.head
    while current ≠ NIL
        if current.key == k
            if prev == NIL
                bucket.head = current.next
            else
                prev.next = current.next
            T.size = T.size - 1
            return current.value
        prev = current
        current = current.next
    error "Key not found"
```

## 6. C++代码实现

```cpp
#include <iostream>
#include <vector>
#include <list>
#include <functional>
#include <stdexcept>

/**
 * 散列表实现
 * 根据《算法导论》第11章内容实现
 */

// 散列表类模板
template<typename K, typename V>
class HashTable {
private:
    // 桶数组，每个桶是一个链表
    std::vector<std::list<std::pair<K, V>>> buckets;
    size_t size_;  // 当前元素数量
    size_t capacity_;  // 桶的数量
    
    // 哈希函数
    std::hash<K> hashFunction;
    
    // 计算关键字的哈希值并映射到桶索引
    size_t hash(const K& key) const {
        return hashFunction(key) % capacity_;
    }
    
public:
    /**
     * 构造函数
     * @param capacity 散列表的容量（桶的数量）
     */
    explicit HashTable(size_t capacity = 16) 
        : size_(0), capacity_(capacity) {
        buckets.resize(capacity_);
        std::cout << "创建散列表，容量: " << capacity_ << std::endl;
    }
    
    /**
     * 析构函数
     */
    ~HashTable() = default;
    
    /**
     * 获取当前元素数量
     * @return 元素数量
     */
    size_t size() const {
        return size_;
    }
    
    /**
     * 检查散列表是否为空
     * @return 如果为空返回true，否则返回false
     */
    bool empty() const {
        return size_ == 0;
    }
    
    /**
     * 获取装载因子
     * @return 装载因子 α = n/m，其中n是元素数量，m是桶数量
     */
    double loadFactor() const {
        return static_cast<double>(size_) / capacity_;
    }
    
    /**
     * 插入或更新键值对
     * @param key 键
     * @param value 值
     */
    void put(const K& key, const V& value) {
        size_t index = hash(key);
        std::cout << "插入键值对: (" << key << ", " << value << ")，哈希值: " << index << std::endl;
        
        // 查找是否已存在该键
        auto& bucket = buckets[index];
        for (auto& pair : bucket) {
            if (pair.first == key) {
                std::cout << "键 " << key << " 已存在，更新值: " << pair.second << " -> " << value << std::endl;
                pair.second = value;  // 更新值
                return;
            }
        }
        
        // 插入新的键值对
        bucket.emplace_back(key, value);
        size_++;
        std::cout << "成功插入键值对: (" << key << ", " << value << ")" << std::endl;
    }
    
    /**
     * 查找指定键对应的值
     * @param key 键
     * @return 对应的值
     * @throws std::out_of_range 如果键不存在
     */
    V get(const K& key) const {
        size_t index = hash(key);
        std::cout << "查找键: " << key << "，哈希值: " << index << std::endl;
        
        const auto& bucket = buckets[index];
        for (const auto& pair : bucket) {
            if (pair.first == key) {
                std::cout << "找到键 " << key << "，对应值为: " << pair.second << std::endl;
                return pair.second;
            }
        }
        
        std::cout << "未找到键: " << key << std::endl;
        throw std::out_of_range("Key not found");
    }
    
    /**
     * 删除指定键值对
     * @param key 要删除的键
     * @return 如果删除成功返回true，否则返回false
     */
    bool remove(const K& key) {
        size_t index = hash(key);
        std::cout << "删除键: " << key << "，哈希值: " << index << std::endl;
        
        auto& bucket = buckets[index];
        for (auto it = bucket.begin(); it != bucket.end(); ++it) {
            if (it->first == key) {
                std::cout << "找到并删除键值对: (" << it->first << ", " << it->second << ")" << std::endl;
                bucket.erase(it);
                size_--;
                return true;
            }
        }
        
        std::cout << "未找到要删除的键: " << key << std::endl;
        return false;
    }
    
    /**
     * 检查是否存在指定的键
     * @param key 要检查的键
     * @return 如果存在返回true，否则返回false
     */
    bool contains(const K& key) const {
        size_t index = hash(key);
        std::cout << "检查键是否存在: " << key << "，哈希值: " << index << std::endl;
        
        const auto& bucket = buckets[index];
        for (const auto& pair : bucket) {
            if (pair.first == key) {
                std::cout << "键 " << key << " 存在" << std::endl;
                return true;
            }
        }
        
        std::cout << "键 " << key << " 不存在" << std::endl;
        return false;
    }
    
    /**
     * 打印散列表的状态
     */
    void printStatus() const {
        std::cout << "\n=== 散列表状态 ===" << std::endl;
        std::cout << "容量: " << capacity_ << std::endl;
        std::cout << "元素数量: " << size_ << std::endl;
        std::cout << "装载因子: " << loadFactor() << std::endl;
        std::cout << "==================" << std::endl;
    }
    
    /**
     * 打印散列表内容
     */
    void printTable() const {
        std::cout << "\n=== 散列表内容 ===" << std::endl;
        for (size_t i = 0; i < buckets.size(); ++i) {
            std::cout << "桶[" << i << "]: ";
            const auto& bucket = buckets[i];
            if (bucket.empty()) {
                std::cout << "(空)";
            } else {
                for (const auto& pair : bucket) {
                    std::cout << "(" << pair.first << "," << pair.second << ") ";
                }
            }
            std::cout << std::endl;
        }
        std::cout << "==================" << std::endl;
    }
};

int main() {
    std::cout << "=== 散列表演示 ===" << std::endl;
    
    // 创建一个整数到字符串的散列表
    HashTable<int, std::string> hashTable(7);  // 使用7个桶
    
    hashTable.printStatus();
    
    // 插入一些键值对
    std::cout << "\n--- 插入操作 ---" << std::endl;
    hashTable.put(1, "one");
    hashTable.put(2, "two");
    hashTable.put(3, "three");
    hashTable.put(8, "eight");   // 与1冲突 (8 % 7 = 1)
    hashTable.put(15, "fifteen"); // 与1冲突 (15 % 7 = 1)
    hashTable.put(9, "nine");    // 与2冲突 (9 % 7 = 2)
    
    hashTable.printStatus();
    hashTable.printTable();
    
    // 查找操作
    std::cout << "\n--- 查找操作 ---" << std::endl;
    try {
        std::cout << "查找键1: " << hashTable.get(1) << std::endl;
        std::cout << "查找键8: " << hashTable.get(8) << std::endl;
        std::cout << "查找键15: " << hashTable.get(15) << std::endl;
        std::cout << "查找键5: " << hashTable.get(5) << std::endl;  // 不存在
    } catch (const std::out_of_range& e) {
        std::cout << "异常: " << e.what() << std::endl;
    }
    
    // 检查键是否存在
    std::cout << "\n--- 存在性检查 ---" << std::endl;
    std::cout << "键1是否存在: " << (hashTable.contains(1) ? "是" : "否") << std::endl;
    std::cout << "键5是否存在: " << (hashTable.contains(5) ? "是" : "否") << std::endl;
    
    // 更新操作
    std::cout << "\n--- 更新操作 ---" << std::endl;
    hashTable.put(1, "updated_one");  // 更新已存在的键
    std::cout << "更新键1后查找: " << hashTable.get(1) << std::endl;
    
    hashTable.printTable();
    
    // 删除操作
    std::cout << "\n--- 删除操作 ---" << std::endl;
    bool removed = hashTable.remove(8);
    std::cout << "删除键8: " << (removed ? "成功" : "失败") << std::endl;
    
    removed = hashTable.remove(5);
    std::cout << "删除键5: " << (removed ? "成功" : "失败") << std::endl;  // 不存在
    
    hashTable.printStatus();
    hashTable.printTable();
    
    return 0;
}
```

## 7. 算法分析

### 7.1 时间复杂度

在分析散列表的性能时，我们使用装载因子α = n/m来描述散列表的满载程度，其中n是表中存储的元素数，m是散列表的槽数。

#### 7.1.1 链接法时间复杂度

- **最坏情况**：Θ(n)，所有n个关键字都散列到同一个槽中，退化为链表
- **平均情况**：
  - 成功查找：Θ(1 + α)
  - 不成功查找：Θ(1 + α)
  - 插入：Θ(1 + α)
  - 删除：Θ(1 + α)（假设使用双向链表）

当散列函数能够均匀地将关键字分布在槽中时，α ≈ 1，操作的时间复杂度为Θ(1)。

#### 7.1.2 开放寻址法时间复杂度

- **最坏情况**：Θ(n)，需要检查整个散列表
- **平均情况**（假设均匀散列）：
  - 成功查找：Θ(1 + 1/(1-α))
  - 不成功查找：Θ(1 + 1/(1-α))
  - 插入：Θ(1 + 1/(1-α))

### 7.2 空间复杂度

- **链接法**：O(m + n)，其中m是桶的数量，n是元素数量
- **开放寻址法**：O(m)，所有元素都存储在散列表中

### 7.3 稳定性

散列表本身不涉及排序操作，因此稳定性不是其考虑因素。

## 8. 算法特点

### 8.1 优点

1. **高效性**：在平均情况下，查找、插入和删除操作的时间复杂度都是O(1)
2. **灵活性**：可以存储任意类型的关键字和值
3. **实用性**：在实际应用中表现良好，广泛应用于各种系统中
4. **扩展性**：可以根据需要动态增长

### 8.2 缺点

1. **最坏情况性能差**：在最坏情况下，所有操作的时间复杂度都退化为O(n)
2. **空间开销**：需要额外的存储空间来处理冲突
3. **无序性**：散列表中的元素没有特定的顺序
4. **散列函数依赖**：性能严重依赖于散列函数的质量

## 9. 适用场景

1. **数据库索引**：快速查找记录
2. **缓存系统**：快速访问缓存数据
3. **编译器**：符号表管理
4. **网络路由器**：路由表查找
5. **分布式系统**：一致性哈希
6. **大数据处理**：快速去重和聚合操作

## 10. 与其他数据结构比较

| 数据结构 | 查找时间复杂度 | 插入时间复杂度 | 删除时间复杂度 | 空间复杂度 | 有序性 |
|---------|---------------|---------------|---------------|-----------|--------|
| 散列表(链接法) | O(1)平均,O(n)最坏 | O(1)平均,O(n)最坏 | O(1)平均,O(n)最坏 | O(m+n) | 无序 |
| 散列表(开放寻址) | O(1)平均,O(n)最坏 | O(1)平均,O(n)最坏 | O(1)平均,O(n)最坏 | O(m) | 无序 |
| 二叉搜索树 | O(log n)平均,O(n)最坏 | O(log n)平均,O(n)最坏 | O(log n)平均,O(n)最坏 | O(n) | 有序 |
| 红黑树 | O(log n) | O(log n) | O(log n) | O(n) | 有序 |
| 数组(有序) | O(log n) | O(n) | O(n) | O(n) | 有序 |
| 链表 | O(n) | O(1) | O(n) | O(n) | 无序 |

## 11. 优化方案

### 11.1 动态扩容

当装载因子超过某个阈值时（如0.75），自动增加桶的数量并重新散列所有元素，以维持较低的装载因子。

### 11.2 更好的散列函数

使用更均匀的散列函数，如：
- MurmurHash
- CityHash
- FarmHash

### 11.3 使用开放寻址法的变种

- 线性探测
- 二次探测
- 双重散列

### 11.4 使用更高级的数据结构

- 跳跃表
- B树
- LSM树

## 12. 总结

散列表是计算机科学中最重要的数据结构之一。通过散列函数将关键字映射到表中的位置，散列表能够实现平均情况下O(1)时间复杂度的查找、插入和删除操作。

《算法导论》第11章详细介绍了散列表的理论基础和实现方法，包括直接寻址表、散列函数设计、冲突解决策略等。通过合理选择散列函数和冲突解决方法，散列表在实际应用中表现出色。

在我们的实现中，采用了链接法解决冲突，这是一种简单而有效的方法。通过使用STL的vector和list容器，我们能够专注于算法本身的实现而不必关心底层内存管理。

需要注意的是，散列表的性能很大程度上取决于散列函数的质量。在实际应用中，应当根据具体的数据特征选择或设计合适的散列函数。此外，装载因子对性能有很大影响，适当的动态扩容策略能够维持散列表的良好性能。

总的来说，散列表是一种非常实用的数据结构，在需要快速查找、插入和删除操作的场景中有着广泛的应用。