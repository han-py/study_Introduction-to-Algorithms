#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

/**
 * B树实现示例程序
 * 
 * 本程序演示了《算法导论》第18章B树的概念和操作
 * B树是一种自平衡的树数据结构，能够保持数据有序，
 * 并允许在对数时间内进行搜索、顺序访问、插入和删除操作。
 * 
 * B树的主要特点：
 * 1. 每个节点可以包含多个关键字（而不是二叉树的单个关键字）
 * 2. 所有叶节点都在同一层
 * 3. 除了根节点外，每个节点都包含至少⌈m/2⌉-1个关键字（其中m是最小度数）
 * 4. 每个节点最多包含m-1个关键字
 */

// B树节点类定义
class BTreeNode {
public:
    int t;                           // 最小度数（阶数）
    std::vector<int> keys;           // 存储关键字的数组
    std::vector<BTreeNode*> children;// 存储子节点指针的数组
    bool leaf;                       // 标识是否为叶节点的布尔值
    int n;                           // 当前节点中关键字的数量

    // 构造函数：创建一个具有指定最小度数和叶节点标志的节点
    BTreeNode(int _t, bool _leaf);

    // 遍历以该节点为根的子树
    void traverse();

    // 在以该节点为根的子树中搜索关键字k
    BTreeNode* search(int k);

    // 分裂满子节点y，i是y在当前节点children数组中的索引
    void splitChild(int i, BTreeNode* y);

    // 在非满节点中插入关键字k
    void insertNonFull(int k);

    // 从以该节点为根的子树中删除关键字k
    void remove(int k);

    // 从叶节点中删除索引为idx的关键字
    void removeFromLeaf(int idx);

    // 从内部节点中删除索引为idx的关键字
    void removeFromNonLeaf(int idx);

    // 获取索引为idx的关键字的前驱（中序遍历意义上的前一个关键字）
    int getPredecessor(int idx);

    // 获取索引为idx的关键字的后继（中序遍历意义上的后一个关键字）
    int getSuccessor(int idx);

    // 填充索引为idx的子节点，确保它至少包含t个关键字
    void fill(int idx);

    // 从左兄弟节点（索引为idx-1）借一个关键字
    void borrowFromPrev(int idx);

    // 从右兄弟节点（索引为idx+1）借一个关键字
    void borrowFromNext(int idx);

    // 合并索引为idx的子节点与其右兄弟节点
    void merge(int idx);

    // 在当前节点的关键字数组中查找关键字k的位置
    int findKey(int k);
    
    // 打印节点信息（用于调试）
    void printNode();
};

// B树类定义
class BTree {
private:
    BTreeNode* root;  // 指向B树根节点的指针
    int t;            // B树的最小度数

public:
    // 构造函数：创建一个具有指定最小度数的空B树
    BTree(int _t) {
        root = nullptr;
        t = _t;
        std::cout << "创建了一个最小度数为 " << t << " 的B树" << std::endl;
        std::cout << "每个节点最少包含 " << (t-1) << " 个关键字" << std::endl;
        std::cout << "每个节点最多包含 " << (2*t-1) << " 个关键字" << std::endl;
    }

    // 遍历整个B树（中序遍历）
    void traverse() {
        std::cout << "\n========== B树遍历 ==========" << std::endl;
        if (root != nullptr) {
            std::cout << "B树遍历结果（中序）: ";
            root->traverse();
            std::cout << std::endl;
        } else {
            std::cout << "B树为空" << std::endl;
        }
        std::cout << "============================" << std::endl;
    }

    // 在B树中搜索关键字k
    BTreeNode* search(int k) {
        std::cout << "正在搜索关键字 " << k << "..." << std::endl;
        BTreeNode* result = (root == nullptr) ? nullptr : root->search(k);
        if (result != nullptr) {
            std::cout << "✓ 找到关键字 " << k << std::endl;
        } else {
            std::cout << "✗ 未找到关键字 " << k << std::endl;
        }
        return result;
    }

    // 向B树中插入关键字k
    void insert(int k);

    // 从B树中删除关键字k
    void remove(int k);
    
    // 打印B树的层次结构
    void printTree();
};

// BTreeNode构造函数实现
BTreeNode::BTreeNode(int _t, bool _leaf) {
    t = _t;
    leaf = _leaf;
    keys.resize(2 * t - 1);      // 关键字数组大小为2t-1
    children.resize(2 * t);       // 子节点指针数组大小为2t
    n = 0;                        // 初始时节点中没有关键字
}

// 遍历节点实现（中序遍历）
void BTreeNode::traverse() {
    // 遍历所有关键字及其对应的子树
    int i;
    for (i = 0; i < n; i++) {
        // 如果不是叶节点，先遍历左边的子树
        if (!leaf)
            children[i]->traverse();
        // 输出当前关键字
        std::cout << " " << keys[i];
    }

    // 遍历最右边的子树（对应于最后一个关键字的右侧）
    if (!leaf)
        children[i]->traverse();
}

// 搜索关键字实现
BTreeNode* BTreeNode::search(int k) {
    // 在当前节点的关键字中查找k的位置
    int i = 0;
    while (i < n && k > keys[i])
        i++;

    // 如果找到了关键字k，返回当前节点
    if (keys[i] == k)
        return this;

    // 如果是叶节点且未找到k，说明k不在树中
    if (leaf)
        return nullptr;

    // 递归搜索对应的子树
    return children[i]->search(k);
}

// 查找关键字索引实现
int BTreeNode::findKey(int k) {
    int idx = 0;
    // 找到第一个大于等于k的关键字位置
    while (idx < n && keys[idx] < k)
        ++idx;
    return idx;
}

// 插入关键字实现
void BTree::insert(int k) {
    std::cout << "\n--- 插入关键字 " << k << " ---" << std::endl;
    
    // 如果树为空，创建根节点
    if (root == nullptr) {
        std::cout << "树为空，创建新的根节点..." << std::endl;
        root = new BTreeNode(t, true);
        root->keys[0] = k;
        root->n = 1;
        std::cout << "✓ 关键字 " << k << " 已插入到根节点" << std::endl;
    } else {
        // 如果根节点已满（包含2t-1个关键字）
        if (root->n == 2 * t - 1) {
            std::cout << "根节点已满（" << root->n << "个关键字），需要分裂..." << std::endl;
            
            // 创建新的根节点
            BTreeNode* s = new BTreeNode(t, false);
            s->children[0] = root;
            
            // 分裂原来的根节点
            s->splitChild(0, root);
            
            // 决定k应该插入到哪个子节点中
            int i = 0;
            if (s->keys[0] < k)
                i++;
            s->children[i]->insertNonFull(k);
            
            // 更新根节点
            root = s;
            std::cout << "✓ 根节点分裂完成，新的根节点已建立" << std::endl;
        } else {
            // 根节点未满，直接插入
            root->insertNonFull(k);
        }
    }
}

// 分裂子节点实现
void BTreeNode::splitChild(int i, BTreeNode* y) {
    std::cout << "  正在分裂第 " << i << " 个子节点..." << std::endl;
    
    // 创建新节点z来存储y的后t-1个关键字
    BTreeNode* z = new BTreeNode(y->t, y->leaf);
    z->n = t - 1;
    
    std::cout << "    创建新节点，将包含 " << (t-1) << " 个关键字" << std::endl;
    
    // 将y的后t-1个关键字复制到z
    for (int j = 0; j < t - 1; j++) {
        z->keys[j] = y->keys[j + t];
        std::cout << "    将关键字 " << y->keys[j + t] << " 复制到新节点" << std::endl;
    }
    
    // 如果y不是叶节点，还需要复制子节点指针
    if (!y->leaf) {
        for (int j = 0; j < t; j++) {
            z->children[j] = y->children[j + t];
            std::cout << "    将子节点指针 " << j << " 复制到新节点" << std::endl;
        }
    }
    
    // 更新y中的关键字数量
    y->n = t - 1;
    std::cout << "    原节点关键字数量更新为 " << y->n << std::endl;
    
    // 为新节点z在当前节点中创建空间
    for (int j = n; j >= i + 1; j--) {
        children[j + 1] = children[j];
    }
    
    // 将新节点z连接为当前节点的子节点
    children[i + 1] = z;
    std::cout << "    将新节点连接为第 " << (i+1) << " 个子节点" << std::endl;
    
    // 将y的中间关键字上移到当前节点
    for (int j = n - 1; j >= i; j--) {
        keys[j + 1] = keys[j];
    }
    
    keys[i] = y->keys[t - 1];
    std::cout << "    将关键字 " << y->keys[t-1] << " 上移到当前节点" << std::endl;
    
    // 更新当前节点的关键字数量
    n = n + 1;
    std::cout << "    当前节点关键字数量更新为 " << n << std::endl;
}

// 在非满节点中插入关键字实现
void BTreeNode::insertNonFull(int k) {
    // 从最右边的关键字开始查找插入位置
    int i = n - 1;
    
    std::cout << "  在非满节点中插入关键字 " << k << std::endl;
    
    // 如果是叶节点
    if (leaf) {
        std::cout << "    当前节点是叶节点" << std::endl;
        // 向右移动所有大于k的关键字
        while (i >= 0 && keys[i] > k) {
            keys[i + 1] = keys[i];
            i--;
        }
        
        // 插入关键字k
        keys[i + 1] = k;
        n = n + 1;
        std::cout << "    ✓ 关键字 " << k << " 已插入，当前节点有 " << n << " 个关键字" << std::endl;
    } else {
        std::cout << "    当前节点是内部节点" << std::endl;
        // 找到应该插入到哪个子树中
        while (i >= 0 && keys[i] > k)
            i--;
        
        // 检查选中的子节点是否已满
        if (children[i + 1]->n == 2 * t - 1) {
            std::cout << "    第 " << (i+1) << " 个子节点已满，需要分裂..." << std::endl;
            // 分裂满的子节点
            splitChild(i + 1, children[i + 1]);
            
            // 如果需要，调整i的值
            if (keys[i + 1] < k)
                i++;
        }
        // 递归插入到选定的子节点中
        children[i + 1]->insertNonFull(k);
    }
}

// 删除关键字实现
void BTree::remove(int k) {
    std::cout << "\n--- 删除关键字 " << k << " ---" << std::endl;
    
    // 如果树为空
    if (!root) {
        std::cout << "✗ 树为空，无法删除" << std::endl;
        return;
    }
    
    // 调用根节点的删除方法
    root->remove(k);
    
    // 如果根节点变空，需要特殊处理
    if (root->n == 0) {
        std::cout << "根节点变空，需要调整树结构..." << std::endl;
        BTreeNode* tmp = root;
        // 如果根节点是叶节点，树变为空
        if (root->leaf)
            root = nullptr;
        // 否则，第一个子节点成为新的根节点
        else
            root = root->children[0];
        delete tmp;
        std::cout << "✓ 树结构调整完成" << std::endl;
    }
}

// 从节点中删除关键字实现
void BTreeNode::remove(int k) {
    // 查找关键字k在当前节点中的位置
    int idx = findKey(k);
    
    std::cout << "  在节点中查找关键字 " << k << "，索引为 " << idx << std::endl;
    
    // 如果关键字k在当前节点中
    if (idx < n && keys[idx] == k) {
        std::cout << "  找到要删除的关键字 " << k << std::endl;
        // 根据节点类型采取不同的删除策略
        if (leaf) {
            std::cout << "    从叶节点删除..." << std::endl;
            removeFromLeaf(idx);
        } else {
            std::cout << "    从内部节点删除..." << std::endl;
            removeFromNonLeaf(idx);
        }
    } else {
        // 关键字k不在当前节点中
        if (leaf) {
            // 如果是叶节点，说明k不在树中
            std::cout << "✗ 关键字 " << k << " 不存在于树中" << std::endl;
            return;
        }
        
        // 标记是否是最后一个子节点
        bool flag = ((idx == n) ? true : false);
        
        // 如果对应的子节点关键字数量不足，需要填充
        if (children[idx]->n < t) {
            std::cout << "    第 " << idx << " 个子节点关键字数量不足，需要填充..." << std::endl;
            fill(idx);
        }
        
        // 递归删除，根据flag决定使用哪个子节点
        if (flag && idx > n)
            children[idx - 1]->remove(k);
        else
            children[idx]->remove(k);
    }
}

// 从叶节点中删除关键字实现
void BTreeNode::removeFromLeaf(int idx) {
    std::cout << "    从叶节点删除索引 " << idx << " 的关键字 " << keys[idx] << std::endl;
    
    // 将idx后面的所有关键字向前移动一位
    for (int i = idx + 1; i < n; ++i)
        keys[i - 1] = keys[i];
    
    // 减少关键字数量
    n--;
    std::cout << "    ✓ 删除完成，当前节点有 " << n << " 个关键字" << std::endl;
}

// 从内部节点中删除关键字实现
void BTreeNode::removeFromNonLeaf(int idx) {
    int k = keys[idx];
    std::cout << "    从内部节点删除关键字 " << k << "（索引 " << idx << "）" << std::endl;
    
    // 如果左子节点有足够的关键字（至少t个）
    if (children[idx]->n >= t) {
        std::cout << "      左子节点有足够关键字，使用前驱替换..." << std::endl;
        // 使用前驱关键字替换k
        int pred = getPredecessor(idx);
        keys[idx] = pred;
        // 递归删除前驱关键字
        children[idx]->remove(pred);
    }
    // 如果右子节点有足够的关键字（至少t个）
    else if (children[idx + 1]->n >= t) {
        std::cout << "      右子节点有足够关键字，使用后继替换..." << std::endl;
        // 使用后继关键字替换k
        int succ = getSuccessor(idx);
        keys[idx] = succ;
        // 递归删除后继关键字
        children[idx + 1]->remove(succ);
    }
    // 如果两个子节点的关键字数量都不足，需要合并它们
    else {
        std::cout << "      两个子节点关键字都不足，需要合并..." << std::endl;
        merge(idx);
        // 递归删除合并后的关键字
        children[idx]->remove(k);
    }
}

// 获取前驱关键字实现
int BTreeNode::getPredecessor(int idx) {
    std::cout << "      获取关键字 " << keys[idx] << " 的前驱..." << std::endl;
    
    // 移动到左子树，直到到达叶节点
    BTreeNode* cur = children[idx];
    while (!cur->leaf)
        cur = cur->children[cur->n];
    
    // 返回叶节点的最后一个关键字
    std::cout << "      前驱关键字是 " << cur->keys[cur->n - 1] << std::endl;
    return cur->keys[cur->n - 1];
}

// 获取后继关键字实现
int BTreeNode::getSuccessor(int idx) {
    std::cout << "      获取关键字 " << keys[idx] << " 的后继..." << std::endl;
    
    // 移动到右子树，直到到达叶节点
    BTreeNode* cur = children[idx + 1];
    while (!cur->leaf)
        cur = cur->children[0];
    
    // 返回叶节点的第一个关键字
    std::cout << "      后继关键字是 " << cur->keys[0] << std::endl;
    return cur->keys[0];
}

// 填充子节点实现
void BTreeNode::fill(int idx) {
    std::cout << "      填充第 " << idx << " 个子节点..." << std::endl;
    
    // 如果左兄弟节点有额外的关键字（超过t-1个）
    if (idx != 0 && children[idx - 1]->n >= t) {
        std::cout << "        从前一个兄弟节点（索引 " << (idx-1) << "）借关键字..." << std::endl;
        borrowFromPrev(idx);
    }
    // 如果右兄弟节点有额外的关键字（超过t-1个）
    else if (idx != n && children[idx + 1]->n >= t) {
        std::cout << "        从后一个兄弟节点（索引 " << (idx+1) << "）借关键字..." << std::endl;
        borrowFromNext(idx);
    }
    // 否则，合并节点
    else {
        if (idx != n) {
            std::cout << "        与后一个兄弟节点（索引 " << (idx+1) << "）合并..." << std::endl;
            merge(idx);
        } else {
            std::cout << "        与前一个兄弟节点（索引 " << (idx-1) << "）合并..." << std::endl;
            merge(idx - 1);
        }
    }
}

// 从前一个兄弟节点借关键字实现
void BTreeNode::borrowFromPrev(int idx) {
    std::cout << "        从前一个兄弟节点(" << (idx-1) << ")借关键字到子节点(" << idx << ")" << std::endl;
    
    BTreeNode* child = children[idx];
    BTreeNode* sibling = children[idx - 1];
    
    // 将child的所有关键字向后移动一位
    for (int i = child->n - 1; i >= 0; --i)
        child->keys[i + 1] = child->keys[i];
    
    // 如果child不是叶节点，移动所有子指针
    if (!child->leaf) {
        for (int i = child->n; i >= 0; --i)
            child->children[i + 1] = child->children[i];
    }
    
    // 将父节点的关键字复制到child的第一个位置
    child->keys[0] = keys[idx - 1];
    std::cout << "          将父节点关键字 " << keys[idx - 1] << " 复制到子节点" << std::endl;
    
    // 如果child不是叶节点，将sibling的最后一个子节点复制到child的第一个位置
    if (!child->leaf)
        child->children[0] = sibling->children[sibling->n];
    
    // 将sibling的最后一个关键字上移到父节点
    keys[idx - 1] = sibling->keys[sibling->n - 1];
    std::cout << "          将兄弟节点关键字 " << sibling->keys[sibling->n - 1] << " 上移到父节点" << std::endl;
    
    // 更新关键字数量
    child->n += 1;
    sibling->n -= 1;
    
    std::cout << "        ✓ 借关键字完成" << std::endl;
}

// 从后一个兄弟节点借关键字实现
void BTreeNode::borrowFromNext(int idx) {
    std::cout << "        从后一个兄弟节点(" << (idx+1) << ")借关键字到子节点(" << idx << ")" << std::endl;
    
    BTreeNode* child = children[idx];
    BTreeNode* sibling = children[idx + 1];
    
    // 将父节点的关键字复制到child的最后位置
    child->keys[(child->n)] = keys[idx];
    std::cout << "          将父节点关键字 " << keys[idx] << " 复制到子节点" << std::endl;
    
    // 如果child不是叶节点，将sibling的第一个子节点复制到child的最后位置
    if (!(child->leaf))
        child->children[(child->n) + 1] = sibling->children[0];
    
    // 将sibling的第一个关键字上移到父节点
    keys[idx] = sibling->keys[0];
    std::cout << "          将兄弟节点关键字 " << sibling->keys[0] << " 上移到父节点" << std::endl;
    
    // 将sibling的所有关键字向前移动一位
    for (int i = 1; i < sibling->n; ++i)
        sibling->keys[i - 1] = sibling->keys[i];
    
    // 如果sibling不是叶节点，移动所有子指针
    if (!sibling->leaf) {
        for (int i = 1; i <= sibling->n; ++i)
            sibling->children[i - 1] = sibling->children[i];
    }
    
    // 更新关键字数量
    child->n += 1;
    sibling->n -= 1;
    
    std::cout << "        ✓ 借关键字完成" << std::endl;
}

// 合并子节点实现
void BTreeNode::merge(int idx) {
    std::cout << "        合并第 " << idx << " 个子节点和第 " << (idx+1) << " 个子节点..." << std::endl;
    
    BTreeNode* child = children[idx];
    BTreeNode* sibling = children[idx + 1];
    
    // 将父节点的关键字复制到child的中间位置
    child->keys[t - 1] = keys[idx];
    std::cout << "          将父节点关键字 " << keys[idx] << " 复制到合并节点" << std::endl;
    
    // 将sibling的所有关键字复制到child的后半部分
    for (int i = 0; i < sibling->n; ++i) {
        child->keys[i + t] = sibling->keys[i];
        std::cout << "          复制兄弟节点关键字 " << sibling->keys[i] << " 到合并节点" << std::endl;
    }
    
    // 如果child不是叶节点，复制sibling的所有子指针
    if (!child->leaf) {
        for (int i = 0; i <= sibling->n; ++i) {
            child->children[i + t] = sibling->children[i];
            std::cout << "          复制兄弟节点子指针 " << i << " 到合并节点" << std::endl;
        }
    }
    
    // 将父节点中的关键字向前移动
    for (int i = idx + 1; i < n; ++i)
        keys[i - 1] = keys[i];
    
    // 将父节点的子指针向前移动
    for (int i = idx + 2; i <= n; ++i)
        children[i - 1] = children[i];
    
    // 更新关键字数量
    child->n += sibling->n + 1;
    n--;
    
    std::cout << "          合并完成，子节点现在有 " << child->n << " 个关键字" << std::endl;
    
    // 删除sibling节点
    delete sibling;
}

// 打印节点信息实现
void BTreeNode::printNode() {
    std::cout << "[";
    for (int i = 0; i < n; i++) {
        std::cout << keys[i];
        if (i < n - 1) std::cout << " ";
    }
    std::cout << "]";
}

// 打印B树结构实现
void BTree::printTree() {
    std::cout << "\n========== B树结构 ==========" << std::endl;
    if (root == nullptr) {
        std::cout << "B树为空" << std::endl;
        std::cout << "============================" << std::endl;
        return;
    }
    
    std::queue<BTreeNode*> q;
    q.push(root);
    q.push(nullptr); // 层级分隔符
    
    int level = 0;
    std::cout << "Level " << level << ": ";
    
    while (!q.empty()) {
        BTreeNode* current = q.front();
        q.pop();
        
        if (current == nullptr) {
            std::cout << std::endl;
            level++;
            if (!q.empty()) {
                q.push(nullptr);
                std::cout << "Level " << level << ": ";
            }
        } else {
            current->printNode();
            std::cout << " ";
            
            if (!current->leaf) {
                for (int i = 0; i <= current->n; i++) {
                    if (current->children[i] != nullptr) {
                        q.push(current->children[i]);
                    }
                }
            }
        }
    }
    std::cout << "\n============================" << std::endl;
}

// 演示B树操作
void demonstrateBTree() {
    std::cout << "\n########################################" << std::endl;
    std::cout << "########## B树操作演示程序 #############" << std::endl;
    std::cout << "########################################" << std::endl;
    
    // 创建最小度数为3的B树（即2-3-4树）
    BTree btree(3);
    
    std::cout << "\n--- 插入操作演示 ---" << std::endl;
    int keys[] = {10, 20, 5, 6, 12, 30, 7, 17};
    int n = sizeof(keys)/sizeof(keys[0]);
    
    for (int i = 0; i < n; i++) {
        std::cout << "\n>>> 第 " << (i+1) << " 次插入 <<<" << std::endl;
        btree.insert(keys[i]);
        btree.printTree();
    }
    
    std::cout << "\n--- 遍历操作演示 ---" << std::endl;
    btree.traverse();
    
    std::cout << "\n--- 搜索操作演示 ---" << std::endl;
    int searchKeys[] = {6, 15, 17};
    for (int i = 0; i < 3; i++) {
        std::cout << "\n>>> 搜索关键字 " << searchKeys[i] << " <<<" << std::endl;
        BTreeNode* result = btree.search(searchKeys[i]);
        if (result != nullptr) {
            std::cout << "✓ 找到了关键字 " << searchKeys[i] << std::endl;
        } else {
            std::cout << "✗ 未找到关键字 " << searchKeys[i] << std::endl;
        }
    }
    
    std::cout << "\n--- 删除操作演示 ---" << std::endl;
    int deleteKeys[] = {6, 10};
    for (int i = 0; i < 2; i++) {
        std::cout << "\n>>> 删除关键字 " << deleteKeys[i] << " <<<" << std::endl;
        btree.remove(deleteKeys[i]);
        btree.printTree();
    }
    
    std::cout << "\n########################################" << std::endl;
    std::cout << "########## 演示程序结束 ###############" << std::endl;
    std::cout << "########################################" << std::endl;
}

// 主函数
int main() {
#ifdef ACM_LOCAL
    freopen("data.in", "r", stdin);
    freopen("data.out", "w", stdout);
#endif
    std::cout << "========================================" << std::endl;
    std::cout << "======= B树算法演示程序 =======\n" << std::endl;
    std::cout << "本程序演示了《算法导论》第18章中B树的实现" << std::endl;
    std::cout << "包括B树的插入、删除、搜索等核心操作" << std::endl;
    std::cout << "========================================" << std::endl;
    
    demonstrateBTree();
    
    std::cout << "\n程序执行完毕，感谢使用！" << std::endl;
    return 0;
}