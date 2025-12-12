#include <iostream>
#include <cmath>
#include <limits>
#include <vector>
#include <bitset>

/**
 * van Emde Boas树实现示例程序
 * 
 * 本程序演示了《算法导论》第20章van Emde Boas树的概念和操作
 * van Emde Boas树是一种高效的数据结构，用于存储0到u-1范围内的整数，
 * 支持INSERT、DELETE、MINIMUM、MAXIMUM、SUCCESSOR、PREDECESSOR等操作，
 * 所有操作的时间复杂度均为O(log log u)。
 */

class VanEmdeBoasTree {
private:
    int u;                      // universe size (集合大小)
    int min;                    // 最小值
    int max;                    // 最大值
    VanEmdeBoasTree* summary;   // 摘要结构
    std::vector<VanEmdeBoasTree*> cluster; // 簇数组

public:
    // 构造函数
    VanEmdeBoasTree(int universe_size);

    // 析构函数
    ~VanEmdeBoasTree();

    // 获取宇宙大小
    int universeSize() const { return u; }

    // 获取最小值
    int minimum() const { return min; }

    // 获取最大值
    int maximum() const { return max; }

    // 检查值是否存在
    bool member(int x);

    // 插入值
    void insert(int x);

    // 删除值
    void remove(int x);

    // 查找后继
    int successor(int x);

    // 查找前驱
    int predecessor(int x);

    // 打印树结构
    void print();

private:
    // 高位函数
    int high(int x) const {
        return x / static_cast<int>(std::sqrt(u));
    }

    // 低位函数
    int low(int x) const {
        return x % static_cast<int>(std::sqrt(u));
    }

    // 索引函数
    int index(int x, int y) const {
        return x * static_cast<int>(std::sqrt(u)) + y;
    }

    // 创建空的vEB树
    static VanEmdeBoasTree* makeEmptyVEBTree(int u);

    // 打印节点信息
    void printNode(int depth = 0);
};

// 构造函数
VanEmdeBoasTree::VanEmdeBoasTree(int universe_size) : u(universe_size), min(-1), max(-1), summary(nullptr) {
    std::cout << "创建大小为 " << u << " 的van Emde Boas树" << std::endl;
    
    if (u > 2) {
        int sqrt_u = static_cast<int>(std::sqrt(u));
        cluster.resize(sqrt_u);
        for (int i = 0; i < sqrt_u; i++) {
            cluster[i] = nullptr;
        }
        summary = nullptr;
    }
}

// 析构函数
VanEmdeBoasTree::~VanEmdeBoasTree() {
    if (u > 2) {
        delete summary;
        for (int i = 0; i < static_cast<int>(cluster.size()); i++) {
            delete cluster[i];
        }
    }
}

// 检查值是否存在
bool VanEmdeBoasTree::member(int x) {
    std::cout << "  检查元素 " << x << " 是否存在..." << std::endl;
    
    if (x == min || x == max) {
        std::cout << "    元素 " << x << " 是最小值或最大值，存在" << std::endl;
        return true;
    } else if (u <= 2) {
        std::cout << "    基础情况，元素 " << x << " 不存在" << std::endl;
        return false;
    } else {
        int cluster_index = high(x);
        int pos = low(x);
        std::cout << "    检查簇 " << cluster_index << " 中位置 " << pos << std::endl;
        
        if (cluster[cluster_index] != nullptr) {
            bool result = cluster[cluster_index]->member(pos);
            std::cout << "    元素 " << x << (result ? " 存在" : " 不存在") << std::endl;
            return result;
        } else {
            std::cout << "    簇 " << cluster_index << " 为空，元素 " << x << " 不存在" << std::endl;
            return false;
        }
    }
}

// 插入值
void VanEmdeBoasTree::insert(int x) {
    std::cout << "\n--- 插入元素 " << x << " ---" << std::endl;
    
    if (min == -1) {
        std::cout << "  树为空，设置 " << x << " 为最小值和最大值" << std::endl;
        min = max = x;
    } else if (x < min) {
        std::cout << "  元素 " << x << " 小于当前最小值 " << min << "，交换它们" << std::endl;
        std::swap(x, min);
    }
    
    if (u > 2) {
        int cluster_index = high(x);
        int pos = low(x);
        std::cout << "  元素 " << x << " 属于簇 " << cluster_index << "，位置 " << pos << std::endl;
        
        if (cluster[cluster_index] == nullptr) {
            std::cout << "    簇 " << cluster_index << " 为空，创建新簇" << std::endl;
            cluster[cluster_index] = makeEmptyVEBTree(static_cast<int>(std::sqrt(u)));
            
            if (summary == nullptr) {
                summary = makeEmptyVEBTree(static_cast<int>(std::sqrt(u)));
            }
            summary->insert(cluster_index);
        }
        
        std::cout << "    在簇 " << cluster_index << " 中插入位置 " << pos << std::endl;
        cluster[cluster_index]->insert(pos);
    }
    
    if (x > max) {
        std::cout << "  更新最大值为 " << x << std::endl;
        max = x;
    }
    
    std::cout << "  ✓ 元素 " << x << " 插入完成" << std::endl;
}

// 删除值
void VanEmdeBoasTree::remove(int x) {
    std::cout << "\n--- 删除元素 " << x << " ---" << std::endl;
    
    if (min == max && x == min) {
        std::cout << "  树中只有一个元素 " << x << "，删除后树变为空" << std::endl;
        min = max = -1;
        return;
    } else if (u <= 2) {
        if (x == 0 && min == 0) {
            min = 1;
        } else if (x == 1 && min == 1) {
            min = 0;
        }
        
        if (min == max) {
            min = max = -1;
        }
        
        std::cout << "  基础情况，删除元素 " << x << " 完成" << std::endl;
        return;
    }
    
    if (x == min) {
        std::cout << "  删除的是最小元素 " << x << std::endl;
        if (summary == nullptr || summary->minimum() == -1) {
            std::cout << "  没有其他元素，树变为空" << std::endl;
            min = max = -1;
            return;
        }
        
        int first_cluster = summary->minimum();
        std::cout << "  从簇 " << first_cluster << " 中找到新的最小值" << std::endl;
        x = index(first_cluster, cluster[first_cluster]->minimum());
        std::cout << "  新的最小值为 " << x << std::endl;
        min = x;
    }
    
    int cluster_index = high(x);
    int pos = low(x);
    std::cout << "  元素 " << x << " 属于簇 " << cluster_index << "，位置 " << pos << std::endl;
    
    if (cluster[cluster_index] != nullptr) {
        std::cout << "    在簇 " << cluster_index << " 中删除位置 " << pos << std::endl;
        cluster[cluster_index]->remove(pos);
        
        if (cluster[cluster_index]->minimum() == -1) {
            std::cout << "    簇 " << cluster_index << " 变为空，从摘要中删除" << std::endl;
            if (summary != nullptr) {
                summary->remove(cluster_index);
            }
            delete cluster[cluster_index];
            cluster[cluster_index] = nullptr;
        }
    }
    
    if (x == max) {
        std::cout << "  删除的是最大元素 " << x << std::endl;
        if (summary == nullptr || summary->minimum() == -1) {
            std::cout << "  没有其他元素，最大值设为最小值 " << min << std::endl;
            max = min;
        } else {
            int last_cluster = summary->maximum();
            std::cout << "  从簇 " << last_cluster << " 中找到新的最大值" << std::endl;
            max = index(last_cluster, cluster[last_cluster]->maximum());
            std::cout << "  新的最大值为 " << max << std::endl;
        }
    }
    
    std::cout << "  ✓ 元素 " << x << " 删除完成" << std::endl;
}

// 查找后继
int VanEmdeBoasTree::successor(int x) {
    std::cout << "  查找元素 " << x << " 的后继..." << std::endl;
    
    if (u <= 2) {
        if (x == 0 && max == 1) {
            std::cout << "    基础情况，元素0的后继是1" << std::endl;
            return 1;
        } else {
            std::cout << "    基础情况，元素 " << x << " 没有后继" << std::endl;
            return -1;
        }
    } else if (min != -1 && x < min) {
        std::cout << "    元素 " << x << " 小于最小值 " << min << "，后继就是最小值" << std::endl;
        return min;
    } else {
        int cluster_index = high(x);
        int pos = low(x);
        int max_low = -1;
        
        if (cluster[cluster_index] != nullptr) {
            max_low = cluster[cluster_index]->maximum();
        }
        
        if (max_low != -1 && pos < max_low) {
            std::cout << "    在簇 " << cluster_index << " 中找到后继" << std::endl;
            int offset = cluster[cluster_index]->successor(pos);
            return index(cluster_index, offset);
        } else {
            int succ_cluster = -1;
            if (summary != nullptr) {
                succ_cluster = summary->successor(cluster_index);
            }
            
            if (succ_cluster == -1) {
                std::cout << "    没有后继簇，元素 " << x << " 没有后继" << std::endl;
                return -1;
            } else {
                std::cout << "    在后继簇 " << succ_cluster << " 中找到最小值作为后继" << std::endl;
                int offset = cluster[succ_cluster]->minimum();
                return index(succ_cluster, offset);
            }
        }
    }
}

// 查找前驱
int VanEmdeBoasTree::predecessor(int x) {
    std::cout << "  查找元素 " << x << " 的前驱..." << std::endl;
    
    if (u <= 2) {
        if (x == 1 && min == 0) {
            std::cout << "    基础情况，元素1的前驱是0" << std::endl;
            return 0;
        } else {
            std::cout << "    基础情况，元素 " << x << " 没有前驱" << std::endl;
            return -1;
        }
    } else if (max != -1 && x > max) {
        std::cout << "    元素 " << x << " 大于最大值 " << max << "，前驱就是最大值" << std::endl;
        return max;
    } else {
        int cluster_index = high(x);
        int pos = low(x);
        int min_low = -1;
        
        if (cluster[cluster_index] != nullptr) {
            min_low = cluster[cluster_index]->minimum();
        }
        
        if (min_low != -1 && pos > min_low) {
            std::cout << "    在簇 " << cluster_index << " 中找到前驱" << std::endl;
            int offset = cluster[cluster_index]->predecessor(pos);
            return index(cluster_index, offset);
        } else {
            int pred_cluster = -1;
            if (summary != nullptr) {
                pred_cluster = summary->predecessor(cluster_index);
            }
            
            if (pred_cluster == -1) {
                if (min != -1 && x > min) {
                    std::cout << "    没有前驱簇，但最小值 " << min << " 是前驱" << std::endl;
                    return min;
                } else {
                    std::cout << "    没有前驱" << std::endl;
                    return -1;
                }
            } else {
                std::cout << "    在前驱簇 " << pred_cluster << " 中找到最大值作为前驱" << std::endl;
                int offset = cluster[pred_cluster]->maximum();
                return index(pred_cluster, offset);
            }
        }
    }
}

// 创建空的vEB树
VanEmdeBoasTree* VanEmdeBoasTree::makeEmptyVEBTree(int u) {
    return new VanEmdeBoasTree(u);
}

// 打印树结构
void VanEmdeBoasTree::print() {
    std::cout << "\n========== van Emde Boas树结构 ==========" << std::endl;
    if (min == -1) {
        std::cout << "树为空" << std::endl;
    } else {
        std::cout << "宇宙大小: " << u << std::endl;
        std::cout << "最小值: " << min << std::endl;
        std::cout << "最大值: " << max << std::endl;
        std::cout << "树结构:" << std::endl;
        printNode();
    }
    std::cout << "=======================================" << std::endl;
}

// 打印节点信息
void VanEmdeBoasTree::printNode(int depth) {
    for (int i = 0; i < depth; i++) {
        std::cout << "  ";
    }
    
    std::cout << "节点 (u=" << u << ", min=" << min << ", max=" << max << ")";
    
    if (u > 2) {
        std::cout << " [";
        bool first = true;
        for (int i = 0; i < static_cast<int>(cluster.size()); i++) {
            if (cluster[i] != nullptr) {
                if (!first) std::cout << ", ";
                std::cout << i;
                first = false;
            }
        }
        std::cout << "]";
    }
    std::cout << std::endl;
    
    if (u > 2) {
        for (int i = 0; i < static_cast<int>(cluster.size()); i++) {
            if (cluster[i] != nullptr) {
                for (int j = 0; j < depth + 1; j++) {
                    std::cout << "  ";
                }
                std::cout << "簇 " << i << ":" << std::endl;
                cluster[i]->printNode(depth + 2);
            }
        }
        
        if (summary != nullptr) {
            for (int j = 0; j < depth + 1; j++) {
                std::cout << "  ";
            }
            std::cout << "摘要:" << std::endl;
            summary->printNode(depth + 2);
        }
    }
}

// 演示van Emde Boas树操作
void demonstrateVanEmdeBoasTree() {
    std::cout << "=== van Emde Boas树演示 ===" << std::endl;
    
    // 创建大小为16的van Emde Boas树 (2^4)
    VanEmdeBoasTree veb(16);
    
    std::cout << "\n--- 插入操作 ---" << std::endl;
    int keys[] = {2, 3, 5, 7, 11, 13, 15};
    int n = sizeof(keys)/sizeof(keys[0]);
    
    for (int i = 0; i < n; i++) {
        veb.insert(keys[i]);
        if (i % 3 == 2) { // 每插入3个节点打印一次结构
            veb.print();
        }
    }
    
    veb.print();
    
    std::cout << "\n--- 成员检查操作 ---" << std::endl;
    int searchKeys[] = {3, 4, 11, 16};
    for (int i = 0; i < 4; i++) {
        bool result = veb.member(searchKeys[i]);
        std::cout << "元素 " << searchKeys[i] << (result ? " 存在" : " 不存在") << std::endl;
    }
    
    std::cout << "\n--- 后继操作 ---" << std::endl;
    int succKeys[] = {2, 5, 11, 15};
    for (int i = 0; i < 4; i++) {
        int result = veb.successor(succKeys[i]);
        if (result != -1) {
            std::cout << "元素 " << succKeys[i] << " 的后继是 " << result << std::endl;
        } else {
            std::cout << "元素 " << succKeys[i] << " 没有后继" << std::endl;
        }
    }
    
    std::cout << "\n--- 前驱操作 ---" << std::endl;
    int predKeys[] = {2, 5, 11, 15};
    for (int i = 0; i < 4; i++) {
        int result = veb.predecessor(predKeys[i]);
        if (result != -1) {
            std::cout << "元素 " << predKeys[i] << " 的前驱是 " << result << std::endl;
        } else {
            std::cout << "元素 " << predKeys[i] << " 没有前驱" << std::endl;
        }
    }
    
    std::cout << "\n--- 删除操作 ---" << std::endl;
    int deleteKeys[] = {3, 11};
    for (int i = 0; i < 2; i++) {
        std::cout << "\n>>> 删除元素 " << deleteKeys[i] << " <<<" << std::endl;
        veb.remove(deleteKeys[i]);
        veb.print();
    }
}

int main() {
#ifdef ACM_LOCAL
    freopen("data.in", "r", stdin);
    freopen("data.out", "w", stdout);
#endif
    std::cout << "========================================" << std::endl;
    std::cout << "=== van Emde Boas树算法演示程序 ===" << std::endl;
    std::cout << "========================================" << std::endl;
    
    demonstrateVanEmdeBoasTree();
    
    std::cout << "\n程序执行完毕，感谢使用！" << std::endl;
    return 0;
}