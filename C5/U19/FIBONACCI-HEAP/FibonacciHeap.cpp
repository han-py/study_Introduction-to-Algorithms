#include <iostream>
#include <cmath>
#include <limits>
#include <vector>

/**
 * 斐波那契堆实现示例程序
 * 
 * 本程序演示了《算法导论》第19章斐波那契堆的概念和操作
 * 斐波那契堆是一种高效的优先队列数据结构，支持高效的插入、
 * 查找最小值和合并操作，并且在图算法中有重要应用。
 * 
 * 斐波那契堆的主要特点：
 * 1. 插入操作: O(1) 摊还时间复杂度
 * 2. 合并操作: O(1) 实际时间复杂度
 * 3. 抽取最小节点: O(log n) 摊还时间复杂度
 * 4. 减小关键字: O(1) 摊还时间复杂度
 * 5. 删除节点: O(log n) 摊还时间复杂度
 */

// 斐波那契堆节点结构
struct FibonacciNode {
    int key;                         // 节点的关键字
    int degree;                      // 节点的度数（子节点数量）
    bool mark;                       // 标记位，用于删除操作
    FibonacciNode* parent;           // 指向父节点的指针
    FibonacciNode* child;            // 指向某个子节点的指针
    FibonacciNode* left;             // 指向左兄弟节点的指针
    FibonacciNode* right;            // 指向右兄弟节点的指针

    // 构造函数
    FibonacciNode(int k) : key(k), degree(0), mark(false), 
                          parent(nullptr), child(nullptr), 
                          left(this), right(this) {
        std::cout << "    创建新节点，关键字为 " << k << std::endl;
    }
};

// 斐波那契堆类
class FibonacciHeap {
private:
    FibonacciNode* min;     // 指向最小节点的指针
    int n;                  // 堆中节点总数
    std::vector<FibonacciNode*> rank; // 用于辅助合并的数组

public:
    // 构造函数
    FibonacciHeap() : min(nullptr), n(0) {
        std::cout << "  创建空的斐波那契堆" << std::endl;
    }

    // 析构函数
    ~FibonacciHeap() {
        clear();
    }

    // 插入关键字
    FibonacciNode* insert(int key);

    // 查找最小关键字
    FibonacciNode* minimum() { 
        std::cout << "  查找最小关键字: " << (min ? std::to_string(min->key) : "堆为空") << std::endl;
        return min; 
    }

    // 抽取最小关键字
    FibonacciNode* extractMin();

    // 合并两个斐波那契堆
    void unite(FibonacciHeap& other);

    // 减小关键字的值
    void decreaseKey(FibonacciNode* x, int k);

    // 删除节点
    void deleteNode(FibonacciNode* x);

    // 打印斐波那契堆结构
    void print();

    // 清空堆
    void clear();

    // 获取节点数量
    int size() const { return n; }

private:
    // 将节点插入根列表
    void insertToRootList(FibonacciNode* node);

    // 将节点从兄弟列表中移除
    void removeFromList(FibonacciNode* node);

    // 合并两个节点
    void link(FibonacciNode* y, FibonacciNode* x);

    // 维护最小节点指针
    void consolidate();

    // 切断父子关系
    void cut(FibonacciNode* x, FibonacciNode* y);

    // 递归标记和切断
    void cascadingCut(FibonacciNode* y);

    // 打印节点信息
    void printNode(FibonacciNode* node, int depth = 0);
    
    // 打印根列表
    void printRootList();
};

// 插入关键字
FibonacciNode* FibonacciHeap::insert(int key) {
    std::cout << "\n--- 插入关键字 " << key << " ---" << std::endl;
    
    FibonacciNode* node = new FibonacciNode(key);
    if (min == nullptr) {
        std::cout << "    堆为空，设置为根节点" << std::endl;
        min = node;
    } else {
        std::cout << "    将节点插入根列表" << std::endl;
        insertToRootList(node);
        if (key < min->key) {
            std::cout << "    新节点关键字更小，更新最小节点指针" << std::endl;
            min = node;
        }
    }
    n++;
    std::cout << "  ✓ 插入完成，堆中节点总数: " << n << std::endl;
    return node;
}

// 将节点插入根列表
void FibonacciHeap::insertToRootList(FibonacciNode* node) {
    std::cout << "    执行插入到根列表操作" << std::endl;
    node->left = min;
    node->right = min->right;
    min->right->left = node;
    min->right = node;
}

// 将节点从兄弟列表中移除
void FibonacciHeap::removeFromList(FibonacciNode* node) {
    std::cout << "    从兄弟列表中移除节点" << std::endl;
    node->left->right = node->right;
    node->right->left = node->left;
}

// 抽取最小关键字
FibonacciNode* FibonacciHeap::extractMin() {
    std::cout << "\n--- 抽取最小关键字 ---" << std::endl;
    
    FibonacciNode* z = min;
    if (z != nullptr) {
        std::cout << "  当前最小节点关键字: " << z->key << std::endl;
        
        // 将z的每个子节点添加到根列表中
        if (z->child != nullptr) {
            std::cout << "  将最小节点的子节点添加到根列表" << std::endl;
            FibonacciNode* child = z->child;
            do {
                FibonacciNode* next = child->right;
                std::cout << "    添加子节点 " << child->key << std::endl;
                child->parent = nullptr;
                insertToRootList(child);
                child = next;
            } while (child != z->child);
        }

        // 从根列表中移除z
        std::cout << "  从根列表中移除最小节点" << std::endl;
        removeFromList(z);
        
        // 如果z是唯一节点
        if (z == z->right) {
            std::cout << "  最小节点是唯一的根节点" << std::endl;
            min = nullptr;
        } else {
            std::cout << "  设置新的候选最小节点并执行合并操作" << std::endl;
            min = z->right;
            consolidate();
        }
        
        n--;
        std::cout << "  ✓ 抽取完成，抽取的关键字: " << z->key << "，剩余节点数: " << n << std::endl;
    } else {
        std::cout << "  堆为空，无法抽取" << std::endl;
    }
    return z;
}

// 合并两个节点
void FibonacciHeap::link(FibonacciNode* y, FibonacciNode* x) {
    std::cout << "    链接操作：将节点 " << y->key << " 链接到节点 " << x->key << std::endl;
    
    // 从根列表中移除y
    removeFromList(y);
    y->parent = x;

    // 将y作为x的子节点
    if (x->child == nullptr) {
        std::cout << "      节点 " << x->key << " 没有子节点，直接设置" << std::endl;
        x->child = y;
        y->left = y;
        y->right = y;
    } else {
        std::cout << "      节点 " << x->key << " 已有子节点，插入到子节点列表" << std::endl;
        y->left = x->child;
        y->right = x->child->right;
        x->child->right->left = y;
        x->child->right = y;
    }
    
    x->degree++;
    y->mark = false;
    std::cout << "    链接完成，节点 " << x->key << " 的度数变为 " << x->degree << std::endl;
}

// 维护最小节点指针
void FibonacciHeap::consolidate() {
    std::cout << "  执行合并操作(CONSOLIDATE)..." << std::endl;
    
    int maxDegree = static_cast<int>(std::log2(n)) + 1;
    std::cout << "    最大可能度数: " << maxDegree << std::endl;
    
    std::vector<FibonacciNode*> A(maxDegree + 1, nullptr);

    // 创建根列表的节点列表
    std::vector<FibonacciNode*> rootList;
    if (min != nullptr) {
        FibonacciNode* current = min;
        do {
            rootList.push_back(current);
            current = current->right;
        } while (current != min);
    }
    
    std::cout << "    根列表中有 " << rootList.size() << " 个节点" << std::endl;

    // 遍历根列表中的每个节点
    for (FibonacciNode* w : rootList) {
        FibonacciNode* x = w;
        int d = x->degree;
        std::cout << "    处理节点 " << x->key << " (度数: " << d << ")" << std::endl;
        
        while (A[d] != nullptr) {
            FibonacciNode* y = A[d];
            std::cout << "      发现度数相同的节点 " << y->key << std::endl;
            
            if (x->key > y->key) {
                std::cout << "      交换节点以确保最小节点在前" << std::endl;
                std::swap(x, y);
            }
            
            link(y, x);
            A[d] = nullptr;
            d++;
            std::cout << "      度数增加到 " << d << std::endl;
        }
        A[d] = x;
        std::cout << "      将节点 " << x->key << " 存储在位置 " << d << std::endl;
    }

    // 重建根列表，更新最小节点
    std::cout << "    重建根列表..." << std::endl;
    min = nullptr;
    for (int i = 0; i <= maxDegree; i++) {
        if (A[i] != nullptr) {
            std::cout << "      处理度数为 " << i << " 的节点 " << A[i]->key << std::endl;
            if (min == nullptr) {
                min = A[i];
                min->left = min;
                min->right = min;
                std::cout << "        设置为新的最小节点" << std::endl;
            } else {
                insertToRootList(A[i]);
                if (A[i]->key < min->key) {
                    std::cout << "        发现更小节点，更新最小节点指针" << std::endl;
                    min = A[i];
                }
            }
        }
    }
    
    std::cout << "  ✓ 合并操作完成" << std::endl;
}

// 合并两个斐波那契堆
void FibonacciHeap::unite(FibonacciHeap& other) {
    std::cout << "\n--- 合并两个斐波那契堆 ---" << std::endl;
    std::cout << "  当前堆节点数: " << n << ", 另一个堆节点数: " << other.n << std::endl;
    
    if (other.min == nullptr) {
        std::cout << "  另一个堆为空，无需合并" << std::endl;
        return;
    }
    
    if (min == nullptr) {
        std::cout << "  当前堆为空，直接复制另一个堆" << std::endl;
        min = other.min;
        n = other.n;
        return;
    }

    // 连接两个根列表
    std::cout << "  连接两个根列表" << std::endl;
    min->right->left = other.min->left;
    other.min->left->right = min->right;
    min->right = other.min;
    other.min->left = min;

    // 更新最小节点
    if (other.min->key < min->key) {
        std::cout << "  另一个堆的最小节点更小，更新最小节点指针" << std::endl;
        min = other.min;
    }
    
    n += other.n;
    std::cout << "  ✓ 合并完成，总节点数: " << n << std::endl;
    
    // 清空other堆，避免重复删除节点
    other.min = nullptr;
    other.n = 0;
}

// 减小关键字的值
void FibonacciHeap::decreaseKey(FibonacciNode* x, int k) {
    std::cout << "\n--- 减小节点关键字 ---" << std::endl;
    std::cout << "  将节点 " << x->key << " 的关键字减小到 " << k << std::endl;
    
    if (k > x->key) {
        std::cout << "  ✗ 错误：新关键字大于原关键字，操作无效" << std::endl;
        return;
    }
    
    x->key = k;
    FibonacciNode* y = x->parent;
    
    if (y != nullptr && x->key < y->key) {
        std::cout << "  节点 " << x->key << " 违反了最小堆性质，需要切断" << std::endl;
        cut(x, y);
        cascadingCut(y);
    }
    
    if (x->key < min->key) {
        std::cout << "  节点 " << x->key << " 成为新的最小节点" << std::endl;
        min = x;
    }
    
    std::cout << "  ✓ 关键字减小完成" << std::endl;
}

// 切断父子关系
void FibonacciHeap::cut(FibonacciNode* x, FibonacciNode* y) {
    std::cout << "    切断操作：切断节点 " << x->key << " 与其父节点 " << y->key << " 的连接" << std::endl;
    
    // 从y的子节点列表中移除x
    if (x->right == x) {
        y->child = nullptr;
        std::cout << "      节点 " << y->key << " 失去唯一子节点" << std::endl;
    } else {
        x->left->right = x->right;
        x->right->left = x->left;
        if (y->child == x) {
            y->child = x->right;
        }
        std::cout << "      从节点 " << y->key << " 的子节点列表中移除节点 " << x->key << std::endl;
    }
    
    y->degree--;
    std::cout << "      节点 " << y->key << " 的度数减少到 " << y->degree << std::endl;
    
    // 将x添加到根列表
    std::cout << "      将节点 " << x->key << " 添加到根列表" << std::endl;
    insertToRootList(x);
    x->parent = nullptr;
    x->mark = false;
    std::cout << "      节点 " << x->key << " 的标记重置为false" << std::endl;
}

// 递归标记和切断
void FibonacciHeap::cascadingCut(FibonacciNode* y) {
    std::cout << "    级联切断：处理节点 " << y->key << std::endl;
    
    FibonacciNode* z = y->parent;
    if (z != nullptr) {
        if (!y->mark) {
            std::cout << "      节点 " << y->key << " 首次失去子节点，设置标记" << std::endl;
            y->mark = true;
        } else {
            std::cout << "      节点 " << y->key << " 再次失去子节点，执行切断并继续级联" << std::endl;
            cut(y, z);
            cascadingCut(z);
        }
    } else {
        std::cout << "      节点 " << y->key << " 是根节点，无需进一步处理" << std::endl;
    }
}

// 删除节点
void FibonacciHeap::deleteNode(FibonacciNode* x) {
    std::cout << "\n--- 删除节点 " << x->key << " ---" << std::endl;
    
    std::cout << "  将节点关键字减小到负无穷" << std::endl;
    decreaseKey(x, std::numeric_limits<int>::min());
    std::cout << "  抽取最小节点以完成删除" << std::endl;
    FibonacciNode* extracted = extractMin();
    delete extracted;
    
    std::cout << "  ✓ 节点删除成功" << std::endl;
}

// 打印根列表
void FibonacciHeap::printRootList() {
    std::cout << "    根列表: ";
    if (min == nullptr) {
        std::cout << "(空)";
    } else {
        FibonacciNode* current = min;
        do {
            std::cout << current->key << "(" << current->degree << ") ";
            current = current->right;
        } while (current != min);
    }
    std::cout << std::endl;
}

// 打印斐波那契堆结构
void FibonacciHeap::print() {
    std::cout << "\n========== 斐波那契堆结构 ==========" << std::endl;
    if (min == nullptr) {
        std::cout << "堆为空" << std::endl;
    } else {
        std::cout << "最小节点: " << min->key << std::endl;
        std::cout << "节点总数: " << n << std::endl;
        std::cout << "堆结构:" << std::endl;
        FibonacciNode* current = min;
        do {
            printNode(current);
            current = current->right;
        } while (current != min);
    }
    std::cout << "==================================" << std::endl;
}

// 打印节点信息
void FibonacciHeap::printNode(FibonacciNode* node, int depth) {
    for (int i = 0; i < depth; i++) {
        std::cout << "  ";
    }
    
    std::cout << "节点: " << node->key 
              << " (度数: " << node->degree 
              << ", 标记: " << (node->mark ? "是" : "否");
    
    if (node->parent != nullptr) {
        std::cout << ", 父节点: " << node->parent->key;
    }
    
    std::cout << ")" << std::endl;
    
    if (node->child != nullptr) {
        FibonacciNode* current = node->child;
        do {
            printNode(current, depth + 1);
            current = current->right;
        } while (current != node->child);
    }
}

// 清空堆
void FibonacciHeap::clear() {
    std::cout << "清空斐波那契堆..." << std::endl;
    if (min == nullptr) {
        std::cout << "堆已为空" << std::endl;
        return;
    }
    
    std::vector<FibonacciNode*> nodes;
    FibonacciNode* current = min;
    do {
        nodes.push_back(current);
        current = current->right;
    } while (current != min);
    
    int deletedCount = 0;
    for (FibonacciNode* node : nodes) {
        // 递归删除子节点
        std::vector<FibonacciNode*> children;
        if (node->child != nullptr) {
            FibonacciNode* child = node->child;
            do {
                children.push_back(child);
                child = child->right;
            } while (child != node->child);
        }
        
        delete node;
        deletedCount++;
    }
    
    min = nullptr;
    n = 0;
    std::cout << "✓ 已删除 " << deletedCount << " 个节点" << std::endl;
}

// 演示斐波那契堆操作
void demonstrateFibonacciHeap() {
    std::cout << "\n########################################" << std::endl;
    std::cout << "########## 斐波那契堆操作演示 ##########" << std::endl;
    std::cout << "########################################" << std::endl;
    
    FibonacciHeap fibHeap;
    
    std::cout << "\n--- 插入操作演示 ---" << std::endl;
    std::vector<FibonacciNode*> nodes;
    int keys[] = {23, 7, 21, 3, 18, 52, 38, 41, 39, 35};
    int n = sizeof(keys)/sizeof(keys[0]);
    
    for (int i = 0; i < n; i++) {
        std::cout << "\n>>> 第 " << (i+1) << " 次插入 <<<" << std::endl;
        nodes.push_back(fibHeap.insert(keys[i]));
        if (i % 3 == 2) { // 每插入3个节点打印一次结构
            fibHeap.print();
        }
    }
    
    fibHeap.print();
    
    std::cout << "\n--- 查找最小关键字 ---" << std::endl;
    FibonacciNode* minNode = fibHeap.minimum();
    if (minNode != nullptr) {
        std::cout << "当前最小关键字: " << minNode->key << std::endl;
    }
    
    std::cout << "\n--- 抽取最小关键字 ---" << std::endl;
    FibonacciNode* extracted = fibHeap.extractMin();
    if (extracted != nullptr) {
        std::cout << "抽取的最小关键字: " << extracted->key << std::endl;
        delete extracted;
    }
    fibHeap.print();
    
    std::cout << "\n--- 减小关键字 ---" << std::endl;
    if (nodes.size() > 5) {
        fibHeap.decreaseKey(nodes[5], 2);
        fibHeap.print();
    }
    
    std::cout << "\n--- 删除节点 ---" << std::endl;
    if (nodes.size() > 3) {
        fibHeap.deleteNode(nodes[3]);
        fibHeap.print();
    }
    
    std::cout << "\n########################################" << std::endl;
    std::cout << "########## 演示程序结束 ###############" << std::endl;
    std::cout << "########################################" << std::endl;
}

int main() {
#ifdef ACM_LOCAL
    freopen("data.in", "r", stdin);
    freopen("data.out", "w", stdout);
#endif
    std::cout << "========================================" << std::endl;
    std::cout << "==== 斐波那契堆算法演示程序 ====" << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "本程序演示了《算法导论》第19章中斐波那契堆的实现" << std::endl;
    std::cout << "包括斐波那契堆的插入、删除、抽取最小节点等核心操作" << std::endl;
    
    demonstrateFibonacciHeap();
    
    std::cout << "\n程序执行完毕，感谢使用！" << std::endl;
    return 0;
}