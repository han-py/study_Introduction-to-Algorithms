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
 */

class BTreeNode {
public:
    int t;                           // 最小度数（阶数）
    std::vector<int> keys;           // 存储关键字
    std::vector<BTreeNode*> children;// 存储子节点指针
    bool leaf;                       // 是否为叶节点
    int n;                           // 当前关键字数量

    // 构造函数
    BTreeNode(int _t, bool _leaf);

    // 遍历以该节点为根的子树
    void traverse();

    // 搜索关键字k
    BTreeNode* search(int k);

    // 分裂满子节点
    void splitChild(int i, BTreeNode* y);

    // 插入关键字到非满节点
    void insertNonFull(int k);

    // 从子树中删除关键字
    void remove(int k);

    // 从叶节点中删除关键字
    void removeFromLeaf(int idx);

    // 从内部节点中删除关键字
    void removeFromNonLeaf(int idx);

    // 获取前驱关键字
    int getPredecessor(int idx);

    // 获取后继关键字
    int getSuccessor(int idx);

    // 填充子节点的关键字数量
    void fill(int idx);

    // 从左兄弟借关键字
    void borrowFromPrev(int idx);

    // 从右兄弟借关键字
    void borrowFromNext(int idx);

    // 合并子节点
    void merge(int idx);

    // 获取节点中关键字的索引
    int findKey(int k);
    
    // 打印节点信息（用于调试）
    void printNode();
};

class BTree {
private:
    BTreeNode* root;  // 根节点
    int t;            // 最小度数

public:
    // 构造函数
    BTree(int _t) {
        root = nullptr;
        t = _t;
    }

    // 遍历B树
    void traverse() {
        if (root != nullptr) {
            std::cout << "B树遍历结果: ";
            root->traverse();
            std::cout << std::endl;
        } else {
            std::cout << "B树为空" << std::endl;
        }
    }

    // 搜索关键字
    BTreeNode* search(int k) {
        return (root == nullptr) ? nullptr : root->search(k);
    }

    // 插入关键字
    void insert(int k);

    // 删除关键字
    void remove(int k);
    
    // 打印B树结构
    void printTree();
};

// BTreeNode构造函数
BTreeNode::BTreeNode(int _t, bool _leaf) {
    t = _t;
    leaf = _leaf;
    keys.resize(2 * t - 1);
    children.resize(2 * t);
    n = 0;
}

// 遍历节点
void BTreeNode::traverse() {
    int i;
    for (i = 0; i < n; i++) {
        if (!leaf)
            children[i]->traverse();
        std::cout << " " << keys[i];
    }

    // 打印最后一个子树
    if (!leaf)
        children[i]->traverse();
}

// 搜索关键字
BTreeNode* BTreeNode::search(int k) {
    int i = 0;
    while (i < n && k > keys[i])
        i++;

    if (keys[i] == k)
        return this;

    if (leaf)
        return nullptr;

    return children[i]->search(k);
}

// 查找关键字的索引
int BTreeNode::findKey(int k) {
    int idx = 0;
    while (idx < n && keys[idx] < k)
        ++idx;
    return idx;
}

// 插入关键字到B树
void BTree::insert(int k) {
    std::cout << "正在插入关键字 " << k << std::endl;
    
    if (root == nullptr) {
        // 创建根节点
        std::cout << "创建新的根节点" << std::endl;
        root = new BTreeNode(t, true);
        root->keys[0] = k;
        root->n = 1;
    } else {
        // 如果根节点满了，树的高度增加
        if (root->n == 2 * t - 1) {
            std::cout << "根节点已满，需要分裂" << std::endl;
            BTreeNode* s = new BTreeNode(t, false);
            s->children[0] = root;
            
            // 分裂旧的根节点
            s->splitChild(0, root);
            
            // 新根节点有两个子节点，决定进入哪一个
            int i = 0;
            if (s->keys[0] < k)
                i++;
            s->children[i]->insertNonFull(k);
            
            root = s;
            std::cout << "根节点分裂完成" << std::endl;
        } else {
            root->insertNonFull(k);
        }
    }
}

// 分裂子节点y，i是y在子节点数组中的索引
void BTreeNode::splitChild(int i, BTreeNode* y) {
    std::cout << "正在分裂子节点 " << i << std::endl;
    
    // 创建新节点存储y的后t-1个关键字
    BTreeNode* z = new BTreeNode(y->t, y->leaf);
    z->n = t - 1;
    
    std::cout << "创建新节点，将包含 " << (t-1) << " 个关键字" << std::endl;
    
    // 将y的后t-1个关键字复制到z
    for (int j = 0; j < t - 1; j++) {
        z->keys[j] = y->keys[j + t];
        std::cout << "复制关键字 " << y->keys[j + t] << " 到新节点" << std::endl;
    }
    
    // 如果y不是叶节点，复制相关的子指针
    if (!y->leaf) {
        for (int j = 0; j < t; j++) {
            z->children[j] = y->children[j + t];
            std::cout << "复制子节点指针 " << j << " 到新节点" << std::endl;
        }
    }
    
    // 减少y中的关键字数量
    y->n = t - 1;
    std::cout << "原节点关键字数量减少到 " << y->n << std::endl;
    
    // 创建新子节点的空间
    for (int j = n; j >= i + 1; j--) {
        children[j + 1] = children[j];
    }
    
    // 连接新子节点
    children[i + 1] = z;
    std::cout << "将新节点连接为子节点 " << (i+1) << std::endl;
    
    // 移动关键字以腾出空间给从y上移的关键字
    for (int j = n - 1; j >= i; j--) {
        keys[j + 1] = keys[j];
    }
    
    // 从y上移中间关键字到该节点
    keys[i] = y->keys[t - 1];
    std::cout << "将关键字 " << y->keys[t-1] << " 上移到父节点" << std::endl;
    
    // 增加该节点的关键字数量
    n = n + 1;
    std::cout << "父节点关键字数量增加到 " << n << std::endl;
}

// 插入关键字到非满节点
void BTreeNode::insertNonFull(int k) {
    // 初始化索引为最右边的元素
    int i = n - 1;
    
    std::cout << "在非满节点中插入关键字 " << k << std::endl;
    
    if (leaf) {
        std::cout << "当前节点是叶节点" << std::endl;
        // 如果是叶节点，找到插入位置并插入新关键字
        while (i >= 0 && keys[i] > k) {
            keys[i + 1] = keys[i];
            i--;
        }
        
        keys[i + 1] = k;
        n = n + 1;
        std::cout << "关键字 " << k << " 已插入，当前节点有 " << n << " 个关键字" << std::endl;
    } else {
        std::cout << "当前节点是内部节点" << std::endl;
        // 如果不是叶节点，找到要插入的子节点
        while (i >= 0 && keys[i] > k)
            i--;
        
        // 检查是否子节点满了
        if (children[i + 1]->n == 2 * t - 1) {
            std::cout << "子节点已满，需要分裂" << std::endl;
            // 分裂满子节点
            splitChild(i + 1, children[i + 1]);
            
            // 分裂后，中间关键字上移到该节点
            // 确定进入哪个子节点
            if (keys[i + 1] < k)
                i++;
        }
        children[i + 1]->insertNonFull(k);
    }
}

// 删除关键字
void BTree::remove(int k) {
    std::cout << "正在删除关键字 " << k << std::endl;
    
    if (!root) {
        std::cout << "树为空，无法删除" << std::endl;
        return;
    }
    
    root->remove(k);
    
    // 如果根节点没有关键字，使其第一个子节点成为新根节点
    if (root->n == 0) {
        std::cout << "根节点为空，需要调整树结构" << std::endl;
        BTreeNode* tmp = root;
        if (root->leaf)
            root = nullptr;
        else
            root = root->children[0];
        delete tmp;
    }
}

// 从节点中删除关键字
void BTreeNode::remove(int k) {
    int idx = findKey(k);
    
    std::cout << "在节点中查找关键字 " << k << "，索引为 " << idx << std::endl;
    
    // 关键字在当前节点
    if (idx < n && keys[idx] == k) {
        std::cout << "找到要删除的关键字 " << k << std::endl;
        if (leaf) {
            std::cout << "从叶节点删除" << std::endl;
            removeFromLeaf(idx);
        } else {
            std::cout << "从内部节点删除" << std::endl;
            removeFromNonLeaf(idx);
        }
    } else {
        // 关键字不在当前节点
        if (leaf) {
            // 关键字不存在于树中
            std::cout << "关键字 " << k << " 不存在于树中" << std::endl;
            return;
        }
        
        // 标记要查找的关键字是否存在于子树中
        bool flag = ((idx == n) ? true : false);
        
        // 如果子节点的关键字数量小于t，需要填充
        if (children[idx]->n < t) {
            std::cout << "子节点关键字数量不足，需要填充" << std::endl;
            fill(idx);
        }
        
        // 如果最后一个子节点合并了，需要递归到idx-1
        if (flag && idx > n)
            children[idx - 1]->remove(k);
        else
            children[idx]->remove(k);
    }
}

// 从叶节点中删除关键字
void BTreeNode::removeFromLeaf(int idx) {
    std::cout << "从叶节点删除索引 " << idx << " 的关键字 " << keys[idx] << std::endl;
    
    // 将后面的所有关键字向前移动一位
    for (int i = idx + 1; i < n; ++i)
        keys[i - 1] = keys[i];
    
    // 减少关键字数量
    n--;
    std::cout << "删除完成，当前节点有 " << n << " 个关键字" << std::endl;
}

// 从内部节点中删除关键字
void BTreeNode::removeFromNonLeaf(int idx) {
    int k = keys[idx];
    std::cout << "从内部节点删除关键字 " << k << std::endl;
    
    // 如果左子节点至少有t个关键字
    if (children[idx]->n >= t) {
        std::cout << "左子节点有足够关键字，使用前驱替换" << std::endl;
        int pred = getPredecessor(idx);
        keys[idx] = pred;
        children[idx]->remove(pred);
    }
    // 如果右子节点至少有t个关键字
    else if (children[idx + 1]->n >= t) {
        std::cout << "右子节点有足够关键字，使用后继替换" << std::endl;
        int succ = getSuccessor(idx);
        keys[idx] = succ;
        children[idx + 1]->remove(succ);
    }
    // 合并左右子节点
    else {
        std::cout << "两个子节点关键字都不足，需要合并" << std::endl;
        merge(idx);
        children[idx]->remove(k);
    }
}

// 获取前驱关键字
int BTreeNode::getPredecessor(int idx) {
    std::cout << "获取关键字 " << keys[idx] << " 的前驱" << std::endl;
    
    // 移动到左子树直到到达叶节点
    BTreeNode* cur = children[idx];
    while (!cur->leaf)
        cur = cur->children[cur->n];
    
    // 返回叶节点的最后一个关键字
    std::cout << "前驱关键字是 " << cur->keys[cur->n - 1] << std::endl;
    return cur->keys[cur->n - 1];
}

// 获取后继关键字
int BTreeNode::getSuccessor(int idx) {
    std::cout << "获取关键字 " << keys[idx] << " 的后继" << std::endl;
    
    // 移动到右子树直到到达叶节点
    BTreeNode* cur = children[idx + 1];
    while (!cur->leaf)
        cur = cur->children[0];
    
    // 返回叶节点的第一个关键字
    std::cout << "后继关键字是 " << cur->keys[0] << std::endl;
    return cur->keys[0];
}

// 填充子节点的关键字
void BTreeNode::fill(int idx) {
    std::cout << "填充子节点 " << idx << std::endl;
    
    // 如果前一个子节点有额外的关键字
    if (idx != 0 && children[idx - 1]->n >= t) {
        std::cout << "从前一个兄弟节点借关键字" << std::endl;
        borrowFromPrev(idx);
    }
    // 如果下一个子节点有额外的关键字
    else if (idx != n && children[idx + 1]->n >= t) {
        std::cout << "从后一个兄弟节点借关键字" << std::endl;
        borrowFromNext(idx);
    }
    // 合并子节点
    else {
        if (idx != n) {
            std::cout << "与后一个兄弟节点合并" << std::endl;
            merge(idx);
        } else {
            std::cout << "与前一个兄弟节点合并" << std::endl;
            merge(idx - 1);
        }
    }
}

// 从前一个子节点借用关键字
void BTreeNode::borrowFromPrev(int idx) {
    std::cout << "从前一个兄弟节点(" << (idx-1) << ")借关键字到子节点(" << idx << ")" << std::endl;
    
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
    
    // 将父节点的关键字复制到child
    child->keys[0] = keys[idx - 1];
    std::cout << "将父节点关键字 " << keys[idx - 1] << " 复制到子节点" << std::endl;
    
    // 将sibling的最后一个关键字复制到父节点
    if (!child->leaf)
        child->children[0] = sibling->children[sibling->n];
    
    keys[idx - 1] = sibling->keys[sibling->n - 1];
    std::cout << "将兄弟节点关键字 " << sibling->keys[sibling->n - 1] << " 上移到父节点" << std::endl;
    
    child->n += 1;
    sibling->n -= 1;
    
    std::cout << "借关键字完成" << std::endl;
}

// 从下一个子节点借用关键字
void BTreeNode::borrowFromNext(int idx) {
    std::cout << "从后一个兄弟节点(" << (idx+1) << ")借关键字到子节点(" << idx << ")" << std::endl;
    
    BTreeNode* child = children[idx];
    BTreeNode* sibling = children[idx + 1];
    
    // 将sibling的第一个关键字复制到父节点
    child->keys[(child->n)] = keys[idx];
    std::cout << "将父节点关键字 " << keys[idx] << " 复制到子节点" << std::endl;
    
    // 如果child不是叶节点，将sibling的第一个子节点复制为child的最后一个子节点
    if (!(child->leaf))
        child->children[(child->n) + 1] = sibling->children[0];
    
    // 将sibling的第一个关键字复制到父节点
    keys[idx] = sibling->keys[0];
    std::cout << "将兄弟节点关键字 " << sibling->keys[0] << " 上移到父节点" << std::endl;
    
    // 将sibling的所有关键字向前移动一位
    for (int i = 1; i < sibling->n; ++i)
        sibling->keys[i - 1] = sibling->keys[i];
    
    // 如果sibling不是叶节点，移动所有子指针
    if (!sibling->leaf) {
        for (int i = 1; i <= sibling->n; ++i)
            sibling->children[i - 1] = sibling->children[i];
    }
    
    child->n += 1;
    sibling->n -= 1;
    
    std::cout << "借关键字完成" << std::endl;
}

// 合并子节点
void BTreeNode::merge(int idx) {
    std::cout << "合并子节点 " << idx << " 和 " << (idx+1) << std::endl;
    
    BTreeNode* child = children[idx];
    BTreeNode* sibling = children[idx + 1];
    
    // 将父节点的关键字复制到child
    child->keys[t - 1] = keys[idx];
    std::cout << "将父节点关键字 " << keys[idx] << " 复制到合并节点" << std::endl;
    
    // 将sibling的所有关键字复制到child
    for (int i = 0; i < sibling->n; ++i) {
        child->keys[i + t] = sibling->keys[i];
        std::cout << "复制兄弟节点关键字 " << sibling->keys[i] << " 到合并节点" << std::endl;
    }
    
    // 如果child不是叶节点，复制sibling的所有子指针
    if (!child->leaf) {
        for (int i = 0; i <= sibling->n; ++i) {
            child->children[i + t] = sibling->children[i];
            std::cout << "复制兄弟节点子指针 " << i << " 到合并节点" << std::endl;
        }
    }
    
    // 将父节点中的关键字向后移动一位
    for (int i = idx + 1; i < n; ++i)
        keys[i - 1] = keys[i];
    
    // 将父节点的子指针向后移动一位
    for (int i = idx + 2; i <= n; ++i)
        children[i - 1] = children[i];
    
    // 更新关键字数量
    child->n += sibling->n + 1;
    n--;
    
    std::cout << "合并完成，子节点现在有 " << child->n << " 个关键字" << std::endl;
    
    // 删除sibling
    delete sibling;
}

// 打印节点信息
void BTreeNode::printNode() {
    std::cout << "[";
    for (int i = 0; i < n; i++) {
        std::cout << keys[i];
        if (i < n - 1) std::cout << " ";
    }
    std::cout << "]";
}

// 打印B树结构
void BTree::printTree() {
    if (root == nullptr) {
        std::cout << "B树为空" << std::endl;
        return;
    }
    
    std::cout << "\n=== B树结构 ===" << std::endl;
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
    std::cout << "\n===============" << std::endl;
}

// 演示B树操作
void demonstrateBTree() {
    std::cout << "=== B树演示 ===" << std::endl;
    BTree btree(3); // 创建最小度数为3的B树（即2-3-4树）
    
    std::cout << "\n--- 插入操作 ---" << std::endl;
    int keys[] = {10, 20, 5, 6, 12, 30, 7, 17};
    int n = sizeof(keys)/sizeof(keys[0]);
    
    for (int i = 0; i < n; i++) {
        std::cout << "\n>>> 第 " << (i+1) << " 次插入 <<<" << std::endl;
        btree.insert(keys[i]);
        btree.printTree();
    }
    
    std::cout << "\n--- 遍历操作 ---" << std::endl;
    btree.traverse();
    
    std::cout << "\n--- 搜索操作 ---" << std::endl;
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
    
    std::cout << "\n--- 删除操作 ---" << std::endl;
    int deleteKeys[] = {6, 10};
    for (int i = 0; i < 2; i++) {
        std::cout << "\n>>> 删除关键字 " << deleteKeys[i] << " <<<" << std::endl;
        btree.remove(deleteKeys[i]);
        btree.printTree();
    }
}

int main() {
    demonstrateBTree();
    
    return 0;
}