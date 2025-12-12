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
                          left(this), right(this) {}
};

// 斐波那契堆类
class FibonacciHeap {
private:
    FibonacciNode* min;     // 指向最小节点的指针
    int n;                  // 堆中节点总数
    std::vector<FibonacciNode*> rank; // 用于辅助合并的数组

public:
    // 构造函数
    FibonacciHeap() : min(nullptr), n(0) {}

    // 析构函数
    ~FibonacciHeap() {
        clear();
    }

    // 插入关键字
    FibonacciNode* insert(int key);

    // 查找最小关键字
    FibonacciNode* minimum() { return min; }

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
};

// 插入关键字
FibonacciNode* FibonacciHeap::insert(int key) {
    std::cout << "插入关键字 " << key << std::endl;
    
    FibonacciNode* node = new FibonacciNode(key);
    if (min == nullptr) {
        min = node;
    } else {
        insertToRootList(node);
        if (key < min->key) {
            min = node;
        }
    }
    n++;
    std::cout << "插入完成，堆中节点总数: " << n << std::endl;
    return node;
}

// 将节点插入根列表
void FibonacciHeap::insertToRootList(FibonacciNode* node) {
    node->left = min;
    node->right = min->right;
    min->right->left = node;
    min->right = node;
}

// 将节点从兄弟列表中移除
void FibonacciHeap::removeFromList(FibonacciNode* node) {
    node->left->right = node->right;
    node->right->left = node->left;
}

// 抽取最小关键字
FibonacciNode* FibonacciHeap::extractMin() {
    std::cout << "抽取最小关键字..." << std::endl;
    
    FibonacciNode* z = min;
    if (z != nullptr) {
        // 将z的每个子节点添加到根列表中
        if (z->child != nullptr) {
            FibonacciNode* child = z->child;
            do {
                FibonacciNode* next = child->right;
                child->parent = nullptr;
                insertToRootList(child);
                child = next;
            } while (child != z->child);
        }

        // 从根列表中移除z
        removeFromList(z);
        
        // 如果z是唯一节点
        if (z == z->right) {
            min = nullptr;
        } else {
            min = z->right;
            consolidate();
        }
        
        n--;
        std::cout << "抽取完成，最小关键字: " << z->key << "，剩余节点数: " << n << std::endl;
    }
    return z;
}

// 合并两个节点
void FibonacciHeap::link(FibonacciNode* y, FibonacciNode* x) {
    std::cout << "  链接节点 " << y->key << " 到节点 " << x->key << std::endl;
    
    // 从根列表中移除y
    removeFromList(y);
    y->parent = x;

    // 将y作为x的子节点
    if (x->child == nullptr) {
        x->child = y;
        y->left = y;
        y->right = y;
    } else {
        y->left = x->child;
        y->right = x->child->right;
        x->child->right->left = y;
        x->child->right = y;
    }
    
    x->degree++;
    y->mark = false;
}

// 维护最小节点指针
void FibonacciHeap::consolidate() {
    std::cout << "  合并相同度数的树..." << std::endl;
    
    int maxDegree = static_cast<int>(std::log2(n)) + 1;
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

    // 遍历根列表中的每个节点
    for (FibonacciNode* w : rootList) {
        FibonacciNode* x = w;
        int d = x->degree;
        
        while (A[d] != nullptr) {
            FibonacciNode* y = A[d];
            if (x->key > y->key) {
                std::swap(x, y);
            }
            link(y, x);
            A[d] = nullptr;
            d++;
        }
        A[d] = x;
    }

    // 重建根列表，更新最小节点
    min = nullptr;
    for (int i = 0; i <= maxDegree; i++) {
        if (A[i] != nullptr) {
            if (min == nullptr) {
                min = A[i];
                min->left = min;
                min->right = min;
            } else {
                insertToRootList(A[i]);
                if (A[i]->key < min->key) {
                    min = A[i];
                }
            }
        }
    }
}

// 合并两个斐波那契堆
void FibonacciHeap::unite(FibonacciHeap& other) {
    std::cout << "合并两个斐波那契堆..." << std::endl;
    
    if (other.min == nullptr) {
        return;
    }
    
    if (min == nullptr) {
        min = other.min;
        n = other.n;
        return;
    }

    // 连接两个根列表
    min->right->left = other.min->left;
    other.min->left->right = min->right;
    min->right = other.min;
    other.min->left = min;

    // 更新最小节点
    if (other.min->key < min->key) {
        min = other.min;
    }
    
    n += other.n;
    std::cout << "合并完成，总节点数: " << n << std::endl;
    
    // 清空other堆，避免重复删除节点
    other.min = nullptr;
    other.n = 0;
}

// 减小关键字的值
void FibonacciHeap::decreaseKey(FibonacciNode* x, int k) {
    std::cout << "减小节点关键字从 " << x->key << " 到 " << k << std::endl;
    
    if (k > x->key) {
        std::cout << "新关键字大于原关键字，操作无效" << std::endl;
        return;
    }
    
    x->key = k;
    FibonacciNode* y = x->parent;
    
    if (y != nullptr && x->key < y->key) {
        cut(x, y);
        cascadingCut(y);
    }
    
    if (x->key < min->key) {
        min = x;
    }
    
    std::cout << "关键字减小完成" << std::endl;
}

// 切断父子关系
void FibonacciHeap::cut(FibonacciNode* x, FibonacciNode* y) {
    std::cout << "  切断节点 " << x->key << " 与其父节点 " << y->key << " 的连接" << std::endl;
    
    // 从y的子节点列表中移除x
    if (x->right == x) {
        y->child = nullptr;
    } else {
        x->left->right = x->right;
        x->right->left = x->left;
        if (y->child == x) {
            y->child = x->right;
        }
    }
    
    y->degree--;
    
    // 将x添加到根列表
    insertToRootList(x);
    x->parent = nullptr;
    x->mark = false;
}

// 递归标记和切断
void FibonacciHeap::cascadingCut(FibonacciNode* y) {
    std::cout << "  递归切断节点 " << y->key << std::endl;
    
    FibonacciNode* z = y->parent;
    if (z != nullptr) {
        if (!y->mark) {
            y->mark = true;
        } else {
            cut(y, z);
            cascadingCut(z);
        }
    }
}

// 删除节点
void FibonacciHeap::deleteNode(FibonacciNode* x) {
    std::cout << "删除节点 " << x->key << std::endl;
    
    decreaseKey(x, std::numeric_limits<int>::min());
    extractMin();
    
    std::cout << "节点删除成功" << std::endl;
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
    if (min == nullptr) return;
    
    std::vector<FibonacciNode*> nodes;
    FibonacciNode* current = min;
    do {
        nodes.push_back(current);
        current = current->right;
    } while (current != min);
    
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
    }
    
    min = nullptr;
    n = 0;
}

// 演示斐波那契堆操作
void demonstrateFibonacciHeap() {
    std::cout << "=== 斐波那契堆演示 ===" << std::endl;
    FibonacciHeap fibHeap;
    
    std::cout << "\n--- 插入操作 ---" << std::endl;
    std::vector<FibonacciNode*> nodes;
    int keys[] = {23, 7, 21, 3, 18, 52, 38, 41, 39, 35};
    int n = sizeof(keys)/sizeof(keys[0]);
    
    for (int i = 0; i < n; i++) {
        nodes.push_back(fibHeap.insert(keys[i]));
        if (i % 3 == 2) { // 每插入3个节点打印一次结构
            fibHeap.print();
        }
    }
    
    fibHeap.print();
    
    std::cout << "\n--- 抽取最小关键字 ---" << std::endl;
    FibonacciNode* minNode = fibHeap.extractMin();
    if (minNode != nullptr) {
        std::cout << "抽取的最小关键字: " << minNode->key << std::endl;
        delete minNode;
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
}

int main() {
#ifdef ACM_LOCAL
    freopen("data.in", "r", stdin);
    freopen("data.out", "w", stdout);
#endif
    std::cout << "========================================" << std::endl;
    std::cout << "==== 斐波那契堆算法演示程序 ====" << std::endl;
    std::cout << "========================================" << std::endl;
    
    demonstrateFibonacciHeap();
    
    std::cout << "\n程序执行完毕，感谢使用！" << std::endl;
    return 0;
}