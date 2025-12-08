# 有根树的表示

## 1. 算法简介

有根树（Rooted Tree）是图论中的一种重要数据结构，在《算法导论》第10章中详细介绍了其表示方法。有根树是一种特殊的树结构，其中一个节点被指定为根节点，其他节点都有唯一的父节点，除了根节点没有父节点。从根节点出发，可以到达树中的任何其他节点。

在计算机科学中，有根树常用于表示具有层次结构的数据，如文件系统、组织架构、分类体系等。有根树不仅在理论计算机科学中占有重要地位，也在实际应用中发挥着关键作用，例如在数据库索引、编译器设计、人工智能等领域都有广泛应用。

有根树的核心特性包括：
- 除了根节点外，每个节点都有唯一的一个父节点
- 从根节点到任何其他节点都存在唯一的一条路径
- 树中不存在环路
- 如果树有n个节点，则恰好有n-1条边

## 2. 算法思想

《算法导论》第10章介绍了两种主要的有根树表示方法，它们各有特点和适用场景：

### 2.1 二叉树表示法

二叉树是一种特殊的有根树，其中每个节点最多有两个子节点，通常称为左子节点和右子节点。每个节点包含指向父节点、左子节点和右子节点的指针。

这种表示法的优点是结构简单，实现直观，特别适用于那些每个节点最多只有两个子节点的场景，如表达式树、决策树、二叉搜索树等。

### 2.2 左孩子右兄弟表示法

这是一种用于表示任意有根树的方法，解决了当节点的子节点数目没有固定上限时的存储问题。在这种表示法中，每个节点包含两个指针：
- `left-child`：指向节点最左边的子节点
- `right-sibling`：指向节点右侧相邻的兄弟节点

这种方法的优势在于，对于任意n个节点的有根树，只需要O(n)的存储空间，无论节点有多少个子节点。这种表示法的核心思想是将一个多叉树转化为二叉树的形式来存储，节省了存储空间。

### 2.3 数学表示

从数学角度来看，有根树可以形式化定义为一个三元组T=(V, E, r)，其中：
- V是非空节点集合
- E是边的集合
- r∈V是根节点

对于任意节点v∈V，存在从根节点r到v的唯一路径。

## 3. 算法步骤

### 3.1 二叉树实现步骤

1. 定义节点结构，包含数据和指向父节点、左子节点、右子节点的指针
2. 实现树的基本操作，如创建节点、设置父子关系等
3. 实现遍历算法，如前序、中序、后序和层序遍历
4. 实现辅助功能，如计算树的高度、节点数量等

### 3.2 左孩子右兄弟表示法实现步骤

1. 定义节点结构，包含数据和指向父节点、最左子节点、右侧兄弟节点的指针
2. 实现树的基本操作，包括节点创建和关系建立
3. 实现相应的遍历算法，考虑到特殊的结构特点
4. 实现辅助功能，如高度计算、节点计数等

## 4. 算法图解示例

### 4.1 二叉树表示法

```
       1
      / \
     2   3
    / \
   4   5

节点结构:
节点1: parent=null, left=节点2, right=节点3
节点2: parent=节点1, left=节点4, right=节点5
节点3: parent=节点1, left=null, right=null
节点4: parent=节点2, left=null, right=null
节点5: parent=节点2, left=null, right=null
```

### 4.2 左孩子右兄弟表示法

```
        1
     /  |  \
    2   3   4
   /|   |   |\
  5 6   7   8 9

转换为左孩子右兄弟表示法:
        1
       /
      2 —— 3 —— 4
      |    |    |
      5    7    8
      |         |
      6         9
```

在左孩子右兄弟表示法中：
- 节点1的left-child指向节点2，节点2和3、4之间通过right-sibling连接
- 节点2的left-child指向节点5，节点5和6之间通过right-sibling连接
- 节点3的left-child指向节点7
- 节点4的left-child指向节点8，节点8和9之间通过right-sibling连接

### 4.3 遍历过程图解

以前序遍历为例：

二叉树前序遍历（根-左-右）：
1. 访问节点1（根）
2. 递归遍历节点1的左子树（以节点2为根）
   - 访问节点2
   - 递归遍历节点2的左子树（节点4）
     - 访问节点4
   - 递归遍历节点2的右子树（节点5）
     - 访问节点5
3. 递归遍历节点1的右子树（以节点3为根）
   - 访问节点3

遍历结果：1 2 4 5 3

## 5. 伪代码实现

### 5.1 二叉树节点定义

```
NODE:
    key          // 节点数据
    parent       // 指向父节点的指针
    left         // 指向左子节点的指针
    right        // 指向右子节点的指针
```

### 5.2 左孩子右兄弟表示法节点定义

```
NODE:
    key             // 节点数据
    parent          // 指向父节点的指针
    left-child      // 指向最左子节点的指针
    right-sibling   // 指向右侧兄弟节点的指针
```

### 5.3 前序遍历（二叉树）

```
PREORDER-TREE-WALK(x):
    if x ≠ NIL
        print x.key
        PREORDER-TREE-WALK(x.left)
        PREORDER-TREE-WALK(x.right)
```

### 5.4 前序遍历（左孩子右兄弟表示法）

```
PREORDER-TREE-WALK(x):
    if x ≠ NIL
        print x.key
        PREORDER-TREE-WALK(x.left-child)
        PREORDER-TREE-WALK(x.right-sibling)
```

### 5.5 计算树的高度

```
COMPUTE-HEIGHT(x):
    if x = NIL
        return -1
    else
        return 1 + max(COMPUTE-HEIGHT(x.left), COMPUTE-HEIGHT(x.right))
```

## 6. C++代码实现

```cpp
#include <iostream>
#include <vector>
#include <queue>

/**
 * 有根树的表示
 * 根据《算法导论》第10章内容实现
 */

// 二叉树节点结构
struct BinaryTreeNode {
    int key;
    BinaryTreeNode* parent;
    BinaryTreeNode* left;
    BinaryTreeNode* right;
    
    BinaryTreeNode(int k) : key(k), parent(nullptr), left(nullptr), right(nullptr) {}
};

// 任意有根树节点结构（左孩子右兄弟表示法）
struct TreeNode {
    int key;
    TreeNode* parent;
    TreeNode* leftChild;     // 最左边的孩子
    TreeNode* rightSibling;   // 右侧相邻的兄弟
    
    TreeNode(int k) : key(k), parent(nullptr), leftChild(nullptr), rightSibling(nullptr) {}
};

// 二叉树类
class BinaryTree {
private:
    BinaryTreeNode* root;
    
public:
    BinaryTree() : root(nullptr) {}
    
    ~BinaryTree() {
        destroyTree(root);
    }
    
    void destroyTree(BinaryTreeNode* node) {
        if (node) {
            destroyTree(node->left);
            destroyTree(node->right);
            delete node;
        }
    }
    
    /**
     * 创建二叉树节点
     */
    BinaryTreeNode* createNode(int key) {
        return new BinaryTreeNode(key);
    }
    
    /**
     * 设置根节点
     */
    void setRoot(BinaryTreeNode* node) {
        root = node;
        if (root) {
            root->parent = nullptr;
        }
    }
    
    /**
     * 获取根节点
     */
    BinaryTreeNode* getRoot() const {
        return root;
    }
    
    /**
     * 中序遍历
     */
    void inorderTraversal(BinaryTreeNode* node) const {
        if (node) {
            inorderTraversal(node->left);
            std::cout << node->key << " ";
            inorderTraversal(node->right);
        }
    }
    
    /**
     * 前序遍历
     */
    void preorderTraversal(BinaryTreeNode* node) const {
        if (node) {
            std::cout << node->key << " ";
            preorderTraversal(node->left);
            preorderTraversal(node->right);
        }
    }
    
    /**
     * 后序遍历
     */
    void postorderTraversal(BinaryTreeNode* node) const {
        if (node) {
            postorderTraversal(node->left);
            postorderTraversal(node->right);
            std::cout << node->key << " ";
        }
    }
    
    /**
     * 层序遍历
     */
    void levelOrderTraversal() const {
        if (!root) return;
        
        std::queue<BinaryTreeNode*> q;
        q.push(root);
        
        while (!q.empty()) {
            BinaryTreeNode* current = q.front();
            q.pop();
            
            std::cout << current->key << " ";
            
            if (current->left) {
                q.push(current->left);
            }
            if (current->right) {
                q.push(current->right);
            }
        }
        std::cout << std::endl;
    }
};

// 任意有根树类（左孩子右兄弟表示法）
class RootedTree {
private:
    TreeNode* root;
    
public:
    RootedTree() : root(nullptr) {}
    
    ~RootedTree() {
        destroyTree(root);
    }
    
    void destroyTree(TreeNode* node) {
        if (node) {
            // 先销毁所有兄弟节点
            destroyTree(node->rightSibling);
            // 再销毁所有子节点
            destroyTree(node->leftChild);
            // 最后销毁当前节点
            delete node;
        }
    }
    
    /**
     * 创建树节点
     */
    TreeNode* createNode(int key) {
        return new TreeNode(key);
    }
    
    /**
     * 设置根节点
     */
    void setRoot(TreeNode* node) {
        root = node;
        if (root) {
            root->parent = nullptr;
        }
    }
    
    /**
     * 获取根节点
     */
    TreeNode* getRoot() const {
        return root;
    }
    
    /**
     * 前序遍历（深度优先）
     */
    void preorderTraversal(TreeNode* node) const {
        if (node) {
            std::cout << node->key << " ";
            
            // 遍历第一个子节点
            if (node->leftChild) {
                preorderTraversal(node->leftChild);
            }
            
            // 遍历兄弟节点
            if (node->rightSibling) {
                preorderTraversal(node->rightSibling);
            }
        }
    }
    
    /**
     * 后序遍历（深度优先）
     */
    void postorderTraversal(TreeNode* node) const {
        if (node) {
            // 遍历第一个子节点
            if (node->leftChild) {
                postorderTraversal(node->leftChild);
            }
            
            std::cout << node->key << " ";
            
            // 遍历兄弟节点
            if (node->rightSibling) {
                postorderTraversal(node->rightSibling);
            }
        }
    }
    
    /**
     * 层序遍历（广度优先）
     */
    void levelOrderTraversal() const {
        if (!root) return;
        
        std::queue<TreeNode*> q;
        q.push(root);
        
        while (!q.empty()) {
            TreeNode* current = q.front();
            q.pop();
            
            std::cout << current->key << " ";
            
            // 将所有兄弟节点加入队列
            TreeNode* sibling = current->rightSibling;
            while (sibling) {
                std::cout << sibling->key << " ";
                sibling = sibling->rightSibling;
            }
            
            // 将第一个子节点加入队列
            if (current->leftChild) {
                q.push(current->leftChild);
            }
        }
        std::cout << std::endl;
    }
    
    /**
     * 计算树的高度
     */
    int getHeight(TreeNode* node) const {
        if (!node) return -1;
        
        int maxHeight = -1;
        
        // 遍历所有子节点，找出最大高度
        TreeNode* child = node->leftChild;
        while (child) {
            int height = getHeight(child);
            if (height > maxHeight) {
                maxHeight = height;
            }
            child = child->rightSibling;
        }
        
        return maxHeight + 1;
    }
    
    /**
     * 计算节点数量
     */
    int getNodeCount(TreeNode* node) const {
        if (!node) return 0;
        
        int count = 1; // 当前节点
        
        // 计算所有子节点的数量
        TreeNode* child = node->leftChild;
        while (child) {
            count += getNodeCount(child);
            child = child->rightSibling;
        }
        
        // 计算所有兄弟节点的数量
        if (node->rightSibling) {
            count += getNodeCount(node->rightSibling);
        }
        
        return count;
    }
};

int main() {
    std::cout << "=== 有根树的表示演示 ===" << std::endl;
    
    // 演示二叉树
    std::cout << "\n--- 二叉树演示 ---" << std::endl;
    BinaryTree binaryTree;
    
    // 创建节点
    BinaryTreeNode* root = binaryTree.createNode(1);
    BinaryTreeNode* node2 = binaryTree.createNode(2);
    BinaryTreeNode* node3 = binaryTree.createNode(3);
    BinaryTreeNode* node4 = binaryTree.createNode(4);
    BinaryTreeNode* node5 = binaryTree.createNode(5);
    
    // 构建二叉树结构
    //       1
    //      / \
    //     2   3
    //    / \
    //   4   5
    
    binaryTree.setRoot(root);
    root->left = node2;
    node2->parent = root;
    root->right = node3;
    node3->parent = root;
    node2->left = node4;
    node4->parent = node2;
    node2->right = node5;
    node5->parent = node2;
    
    std::cout << "前序遍历: ";
    binaryTree.preorderTraversal(binaryTree.getRoot());
    std::cout << std::endl;
    
    std::cout << "中序遍历: ";
    binaryTree.inorderTraversal(binaryTree.getRoot());
    std::cout << std::endl;
    
    std::cout << "后序遍历: ";
    binaryTree.postorderTraversal(binaryTree.getRoot());
    std::cout << std::endl;
    
    std::cout << "层序遍历: ";
    binaryTree.levelOrderTraversal();
    
    // 演示任意有根树（左孩子右兄弟表示法）
    std::cout << "\n--- 任意有根树演示（左孩子右兄弟表示法） ---" << std::endl;
    RootedTree rootedTree;
    
    // 创建节点
    TreeNode* r = rootedTree.createNode(1);   // 根节点
    TreeNode* n2 = rootedTree.createNode(2);
    TreeNode* n3 = rootedTree.createNode(3);
    TreeNode* n4 = rootedTree.createNode(4);
    TreeNode* n5 = rootedTree.createNode(5);
    TreeNode* n6 = rootedTree.createNode(6);
    TreeNode* n7 = rootedTree.createNode(7);
    
    // 构建树结构
    //        1
    //     /  |  \
    //    2   3   4
    //   /|   |   |\
    //  5 6   7   8 9
    
    rootedTree.setRoot(r);
    
    // 设置节点1的孩子
    r->leftChild = n2;
    n2->parent = r;
    
    // 设置节点2的兄弟（节点3和4）
    n2->rightSibling = n3;
    n3->parent = r;
    n3->rightSibling = n4;
    n4->parent = r;
    
    // 设置节点2的孩子（节点5和6）
    n2->leftChild = n5;
    n5->parent = n2;
    n5->rightSibling = n6;
    n6->parent = n2;
    
    // 设置节点3的孩子（节点7）
    n3->leftChild = n7;
    n7->parent = n3;
    
    // 注意：为了简化演示，这里省略了节点4的孩子（8和9）
    
    std::cout << "前序遍历: ";
    rootedTree.preorderTraversal(rootedTree.getRoot());
    std::cout << std::endl;
    
    std::cout << "后序遍历: ";
    rootedTree.postorderTraversal(rootedTree.getRoot());
    std::cout << std::endl;
    
    std::cout << "层序遍历: ";
    rootedTree.levelOrderTraversal();
    
    std::cout << "树的高度: " << rootedTree.getHeight(rootedTree.getRoot()) << std::endl;
    std::cout << "节点总数: " << rootedTree.getNodeCount(rootedTree.getRoot()) << std::endl;
    
    return 0;
}
```

## 7. 算法分析

### 7.1 时间复杂度

- **节点访问**: O(1) - 直接通过指针访问
- **前序/中序/后序遍历**: O(n) - 需要访问每个节点一次
- **层序遍历**: O(n) - 需要访问每个节点一次
- **树的高度计算**: O(n) - 最坏情况下需要访问所有节点
- **节点计数**: O(n) - 需要访问每个节点一次

### 7.2 空间复杂度

- **存储空间**: O(n) - 需要存储n个节点，每个节点有固定数量的指针
- **遍历递归栈空间**: O(h) - h为树的高度，最坏情况下为O(n)

### 7.3 稳定性

有根树的表示与稳定性无关，因为它关注的是数据结构而非排序算法。

## 8. 算法特点

### 8.1 优点

1. **灵活性**: 可以表示任意形状的树结构
2. **高效访问**: 通过指针可以直接访问父节点、子节点和兄弟节点
3. **内存效率**: 左孩子右兄弟表示法对任意有根树只需要O(n)空间
4. **扩展性强**: 可以轻松添加额外信息，如节点权重、颜色等

### 8.2 缺点

1. **指针管理**: 需要手动管理指针，容易出现内存泄漏
2. **实现复杂**: 相比数组表示法，链式结构实现更复杂
3. **缓存局部性**: 节点在内存中可能不连续，影响缓存性能

## 9. 适用场景

1. **文件系统**: 表示目录和文件的层次结构
2. **组织架构**: 表示公司或机构的层级关系
3. **语法分析**: 编译器中表示程序的语法树
4. **决策树**: 机器学习中的分类模型
5. **DOM树**: 网页文档对象模型

## 10. 与其他表示方法比较

| 表示方法 | 存储空间 | 查找父节点 | 查找子节点 | 适用场景 |
|---------|---------|-----------|-----------|----------|
| 二叉树表示法 | O(n) | O(1) | O(1) | 二叉树结构 |
| 左孩子右兄弟表示法 | O(n) | O(1) | O(1) | 任意有根树 |
| 数组表示法（完全二叉树） | O(n) | O(1) | O(1) | 完全二叉树 |
| 子节点列表表示法 | O(n+m) | O(1) | O(1) | 任意有根树（m为边数） |

## 11. 优化方案

1. **智能指针**: 使用现代C++的智能指针自动管理内存
2. **内存池**: 预先分配大量节点内存，提高分配效率
3. **迭代遍历**: 用栈模拟递归，避免深层递归导致的栈溢出
4. **平衡树**: 在动态插入/删除场景下维持树的平衡性
5. **压缩存储**: 对于稀疏树结构，可考虑压缩存储方案

## 12. 总结

有根树的表示是数据结构中的重要内容，《算法导论》第10章提供了多种表示方法，各有优劣。二叉树是最常见和简单的形式，而左孩子右兄弟表示法则提供了一种优雅的方式来表示任意有根树。

在实际应用中，选择合适的表示方法取决于具体的使用场景和性能要求。理解这些基本表示方法为进一步学习更复杂的数据结构（如平衡树、B树等）奠定了坚实的基础。

通过本实现，我们展示了如何用C++实现这两种表示方法，并提供了常用的遍历算法和辅助函数。这为理解和应用树结构提供了实践基础。