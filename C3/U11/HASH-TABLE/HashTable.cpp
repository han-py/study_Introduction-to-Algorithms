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
#ifdef ACM_LOCAL
    freopen("data.in", "r", stdin);
    freopen("data.out", "w", stdout);
#endif
    
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