# 二叉搜索树 (Binary Search Tree)

## 1. 算法简介

二叉搜索树（Binary Search Tree，BST）是《算法导论》第12章介绍的一种重要数据结构。它是一种特殊的二叉树，其中每个节点都具有一个键值，并且对于任意节点，其左子树中所有节点的键值都小于该节点的键值，其右子树中所有节点的键值都大于或等于该节点的键值。

二叉搜索树支持多种动态集合操作，包括SEARCH（查找）、MINIMUM（最小元素）、MAXIMUM（最大元素）、PREDECESSOR（前驱）、SUCCESSOR（后继）、INSERT（插入）和DELETE（删除）等。因此，我们可以使用一棵二叉搜索树既作为一个字典又可以作为一个优先队列。

二叉搜索树上的基本操作所花费的时间与这棵树的高度成正比。对于有n个节点的一棵完全二叉树来说，这些操作的最坏运行时间为Θ(lg n)。然而，如果这棵树是一条由n个节点组成的线性链，那么同样的操作就要花费Θ(n)的最坏运行时间。

## 2. 算法思想

### 2.1 二叉搜索树的性质

二叉搜索树是一种二叉树，其中每个节点都遵循以下性质：

1. **二叉搜索树性质**：
   - 设x是二叉搜索树中的一个节点
   - 如果y是x左子树中的一个节点，那么y.key ≤ x.key
   - 如果y是x右子树中的一个节点，那么y.key ≥ x.key

换句话说：
- 若任意节点的左子树不空，则左子树上所有节点的值均不大于它的根节点的值
- 若任意节点的右子树不空，则右子树上所有节点的值均不小于它的根节点的值
- 任意节点的左、右子树也分别为二叉搜索树

### 2.2 节点表示

每个节点包含以下属性：
- key：节点的键值
- left：指向左子节点的指针
- right：指向右子节点的指针
- parent：指向父节点的指针

### 2.3 中序遍历性质

二叉搜索树的一个重要性质是：对二叉搜索树进行中序遍历（左-根-右）会按排序顺序访问所有节点。这个性质是二叉搜索树正确性的基础。

## 3. 算法步骤

### 3.1 搜索操作

1. 从根节点开始
2. 比较要查找的键值与当前节点的键值
3. 如果相等，返回当前节点
4. 如果要查找的键值小于当前节点的键值，进入左子树
5. 如果要查找的键值大于当前节点的键值，进入右子树
6. 如果到达空节点，说明未找到，返回nullptr

### 3.2 最小元素和最大元素

- **最小元素**：从根节点开始，沿着左子树一直向下，直到没有左子节点为止
- **最大元素**：从根节点开始，沿着右子树一直向下，直到没有右子节点为止

### 3.3 前驱和后继

- **后继**：对于节点x，其后继是大于x.key的最小键值的节点
  - 如果x的右子树非空，则x的后继是x的右子树中的最小节点
  - 如果x的右子树为空，且x有后继y，则y是x的最低祖先节点，使得x在其左子树中

- **前驱**：对于节点x，其前驱是小于x.key的最大键值的节点
  - 如果x的左子树非空，则x的前驱是x的左子树中的最大节点
  - 如果x的左子树为空，且x有前驱y，则y是x的最低祖先节点，使得x在其右子树中

### 3.4 插入操作

1. 从根节点开始，沿着树向下移动，查找合适的插入位置
2. 比较要插入的键值与当前节点的键值
3. 如果要插入的键值小于当前节点的键值，进入左子树
4. 如果要插入的键值大于等于当前节点的键值，进入右子树
5. 当到达空节点时，将新节点插入此处

### 3.5 删除操作

删除操作稍微复杂一些，需要考虑三种情况：

1. **要删除的节点没有左子节点**：用其右子树替换该节点
2. **要删除的节点没有右子节点**：用其左子树替换该节点
3. **要删除的节点既有左子节点又有右子节点**：
   - 找到该节点的后继（右子树中的最小节点）
   - 用后继节点替换要删除的节点
   - 如果后继节点不是要删除节点的直接子节点，还需要进行额外的调整

## 4. 算法图解示例

### 4.1 二叉搜索树示例

```
        15
      /    \
     6      18
    / \    /  \
   3   7  17  20
  / \   \
 2   4   13
        /
       9
```

### 4.2 搜索过程示例

搜索键值13：
1. 从根节点15开始，13 < 15，进入左子树
2. 到达节点6，13 > 6，进入右子树
3. 到达节点7，13 > 7，进入右子树
4. 到达节点13，找到目标节点

### 4.3 插入过程示例

插入键值10：
1. 从根节点15开始，10 < 15，进入左子树
2. 到达节点6，10 > 6，进入右子树
3. 到达节点7，10 > 7，进入右子树
4. 到达节点13，10 < 13，进入左子树
5. 到达节点9，10 > 9，进入右子树
6. 到达空节点，将新节点10作为节点9的右子节点插入

插入后的树：
```
        15
      /    \
     6      18
    / \    /  \
   3   7  17  20
  / \   \
 2   4   13
        /
       9
        \
         10
```

### 4.4 删除过程示例

删除节点13：
1. 节点13既有左子节点（9）又有右子节点（无），属于情况2
2. 用节点9替换节点13
3. 节点9的左子树（包含节点10）成为节点7的右子树

删除后的树：
```
        15
      /    \
     6      18
    / \    /  \
   3   7  17  20
  / \   \
 2   4   9
        /
       10
```

## 5. 伪代码实现

### 5.1 节点定义

```
NODE:
    key             // 节点键值
    parent          // 指向父节点的指针
    left            // 指向左子节点的指针
    right           // 指向右子节点的指针
```

### 5.2 搜索操作

```
TREE-SEARCH(x, k):
    if x = NIL or k = x.key
        return x
    if k < x.key
        return TREE-SEARCH(x.left, k)
    else
        return TREE-SEARCH(x.right, k)
```

### 5.3 迭代版本搜索

```
ITERATIVE-TREE-SEARCH(x, k):
    while x ≠ NIL and k ≠ x.key
        if k < x.key
            x = x.left
        else
            x = x.right
    return x
```

### 5.4 最小元素

```
TREE-MINIMUM(x):
    while x.left ≠ NIL
        x = x.left
    return x
```

### 5.5 最大元素

```
TREE-MAXIMUM(x):
    while x.right ≠ NIL
        x = x.right
    return x
```

### 5.6 后继

```
TREE-SUCCESSOR(x):
    if x.right ≠ NIL
        return TREE-MINIMUM(x.right)
    y = x.parent
    while y ≠ NIL and x = y.right
        x = y
        y = y.parent
    return y
```

### 5.7 插入

```
TREE-INSERT(T, z):
    y = NIL
    x = T.root
    while x ≠ NIL
        y = x
        if z.key < x.key
            x = x.left
        else
            x = x.right
    z.parent = y
    if y = NIL
        T.root = z  // 树为空
    elseif z.key < y.key
        y.left = z
    else
        y.right = z
```

### 5.8 删除

```
TREE-DELETE(T, z):
    if z.left = NIL
        TRANSPLANT(T, z, z.right)
    elseif z.right = NIL
        TRANSPLANT(T, z, z.left)
    else
        y = TREE-MINIMUM(z.right)
        if y.parent ≠ z
            TRANSPLANT(T, y, y.right)
            y.right = z.right
            y.right.parent = y
        TRANSPLANT(T, z, y)
        y.left = z.left
        y.left.parent = y
```

### 5.9 子树替换

```
TRANSPLANT(T, u, v):
    if u.parent = NIL
        T.root = v
    elseif u = u.parent.left
        u.parent.left = v
    else
        u.parent.right = v
    if v ≠ NIL
        v.parent = u.parent
```

## 6. C++代码实现

```cpp
#include <iostream>
#include <queue>
#include <stack>
#include <climits>

/**
 * 二叉搜索树实现
 * 根据《算法导论》第12章内容实现
 */

// 二叉搜索树节点结构
struct TreeNode {
    int key;              // 节点存储的数据
    TreeNode* parent;     // 指向父节点的指针
    TreeNode* left;       // 指向左子节点的指针
    TreeNode* right;      // 指向右子节点的指针
    
    /**
     * 构造函数
     * @param k 节点的键值
     */
    TreeNode(int k) : key(k), parent(nullptr), left(nullptr), right(nullptr) {}
};

// 二叉搜索树类
class BinarySearchTree {
private:
    TreeNode* root;  // 指向根节点的指针
    
public:
    /**
     * 构造函数，初始化空树
     */
    BinarySearchTree() : root(nullptr) {
        std::cout << "创建二叉搜索树" << std::endl;
    }
    
    /**
     * 析构函数，释放整棵树的内存
     */
    ~BinarySearchTree() {
        destroyTree(root);
    }
    
    /**
     * 递归销毁整棵树
     * @param node 要销毁的节点
     */
    void destroyTree(TreeNode* node) {
        if (node) {
            std::cout << "销毁节点: " << node->key << std::endl;
            destroyTree(node->left);
            destroyTree(node->right);
            delete node;
        }
    }
    
    /**
     * 获取根节点
     * @return 指向根节点的指针
     */
    TreeNode* getRoot() const {
        return root;
    }
    
    /**
     * 检查树是否为空
     * @return 如果为空返回true，否则返回false
     */
    bool isEmpty() const {
        return root == nullptr;
    }
    
    /**
     * 创建一个新的树节点
     * @param key 节点的键值
     * @return 指向新创建节点的指针
     */
    TreeNode* createNode(int key) {
        std::cout << "创建节点: " << key << std::endl;
        return new TreeNode(key);
    }
    
    /**
     * 设置根节点
     * @param node 新的根节点
     */
    void setRoot(TreeNode* node) {
        std::cout << "设置根节点为: " << (node ? std::to_string(node->key) : "nullptr") << std::endl;
        root = node;
        if (root) {
            root->parent = nullptr;
        }
    }
    
    /**
     * 在二叉搜索树中搜索指定键值的节点
     * @param key 要搜索的键值
     * @return 找到的节点指针，未找到返回nullptr
     */
    TreeNode* search(int key) const {
        std::cout << "在二叉搜索树中搜索键值: " << key << std::endl;
        TreeNode* current = root;
        
        while (current != nullptr && current->key != key) {
            if (key < current->key) {
                std::cout << "键值 " << key << " 小于当前节点 " << current->key << "，向左子树搜索" << std::endl;
                current = current->left;
            } else {
                std::cout << "键值 " << key << " 大于等于当前节点 " << current->key << "，向右子树搜索" << std::endl;
                current = current->right;
            }
        }
        
        if (current) {
            std::cout << "找到键值 " << key << "，位于节点 " << current->key << std::endl;
        } else {
            std::cout << "未找到键值 " << key << std::endl;
        }
        
        return current;
    }
    
    /**
     * 递归版本的搜索操作
     * @param node 搜索起始节点
     * @param key 要搜索的键值
     * @return 找到的节点指针，未找到返回nullptr
     */
    TreeNode* searchRecursive(TreeNode* node, int key) const {
        if (node == nullptr || node->key == key) {
            if (node) {
                std::cout << "递归搜索找到键值 " << key << "，位于节点 " << node->key << std::endl;
            } else {
                std::cout << "递归搜索未找到键值 " << key << std::endl;
            }
            return node;
        }
        
        if (key < node->key) {
            std::cout << "递归搜索: 键值 " << key << " 小于当前节点 " << node->key << "，向左子树搜索" << std::endl;
            return searchRecursive(node->left, key);
        } else {
            std::cout << "递归搜索: 键值 " << key << " 大于等于当前节点 " << node->key << "，向右子树搜索" << std::endl;
            return searchRecursive(node->right, key);
        }
    }
    
    /**
     * 查找最小关键字元素
     * @param node 搜索起始节点
     * @return 最小关键字节点指针
     */
    TreeNode* minimum(TreeNode* node) const {
        if (node == nullptr) {
            std::cout << "树为空，无法查找最小元素" << std::endl;
            return nullptr;
        }
        
        std::cout << "查找最小关键字元素，从节点 " << node->key << " 开始" << std::endl;
        while (node->left != nullptr) {
            std::cout << "向左子树移动到节点 " << node->left->key << std::endl;
            node = node->left;
        }
        
        std::cout << "找到最小关键字元素: " << node->key << std::endl;
        return node;
    }
    
    /**
     * 查找最大关键字元素
     * @param node 搜索起始节点
     * @return 最大关键字节点指针
     */
    TreeNode* maximum(TreeNode* node) const {
        if (node == nullptr) {
            std::cout << "树为空，无法查找最大元素" << std::endl;
            return nullptr;
        }
        
        std::cout << "查找最大关键字元素，从节点 " << node->key << " 开始" << std::endl;
        while (node->right != nullptr) {
            std::cout << "向右子树移动到节点 " << node->right->key << std::endl;
            node = node->right;
        }
        
        std::cout << "找到最大关键字元素: " << node->key << std::endl;
        return node;
    }
    
    /**
     * 查找节点的后继
     * @param node 要查找后继的节点
     * @return 后继节点指针，不存在返回nullptr
     */
    TreeNode* successor(TreeNode* node) const {
        if (node == nullptr) {
            std::cout << "节点为空，无法查找后继" << std::endl;
            return nullptr;
        }
        
        std::cout << "查找节点 " << node->key << " 的后继" << std::endl;
        
        // 如果右子树不为空，则后继是右子树中的最小节点
        if (node->right != nullptr) {
            std::cout << "节点 " << node->key << " 有右子树，后继为其右子树中的最小节点" << std::endl;
            return minimum(node->right);
        }
        
        // 如果右子树为空，则后继是最低的祖先节点，使得该节点在此祖先节点的左子树中
        TreeNode* successorNode = node->parent;
        while (successorNode != nullptr && node == successorNode->right) {
            std::cout << "节点 " << node->key << " 是其父节点 " << successorNode->key << " 的右子节点，继续向上查找" << std::endl;
            node = successorNode;
            successorNode = successorNode->parent;
        }
        
        if (successorNode) {
            std::cout << "节点 " << node->key << " 的后继是 " << successorNode->key << std::endl;
        } else {
            std::cout << "节点 " << node->key << " 没有后继（它是树中的最大节点）" << std::endl;
        }
        
        return successorNode;
    }
    
    /**
     * 查找节点的前驱
     * @param node 要查找前驱的节点
     * @return 前驱节点指针，不存在返回nullptr
     */
    TreeNode* predecessor(TreeNode* node) const {
        if (node == nullptr) {
            std::cout << "节点为空，无法查找前驱" << std::endl;
            return nullptr;
        }
        
        std::cout << "查找节点 " << node->key << " 的前驱" << std::endl;
        
        // 如果左子树不为空，则前驱是左子树中的最大节点
        if (node->left != nullptr) {
            std::cout << "节点 " << node->key << " 有左子树，前驱为其左子树中的最大节点" << std::endl;
            return maximum(node->left);
        }
        
        // 如果左子树为空，则前驱是最低的祖先节点，使得该节点在此祖先节点的右子树中
        TreeNode* predecessorNode = node->parent;
        while (predecessorNode != nullptr && node == predecessorNode->left) {
            std::cout << "节点 " << node->key << " 是其父节点 " << predecessorNode->key << " 的左子节点，继续向上查找" << std::endl;
            node = predecessorNode;
            predecessorNode = predecessorNode->parent;
        }
        
        if (predecessorNode) {
            std::cout << "节点 " << node->key << " 的前驱是 " << predecessorNode->key << std::endl;
        } else {
            std::cout << "节点 " << node->key << " 没有前驱（它是树中的最小节点）" << std::endl;
        }
        
        return predecessorNode;
    }
    
    /**
     * 在二叉搜索树中插入节点
     * @param key 要插入的键值
     */
    void insert(int key) {
        std::cout << "\n插入键值: " << key << std::endl;
        
        TreeNode* newNode = createNode(key);
        TreeNode* parentNode = nullptr;
        TreeNode* currentNode = root;
        
        // 查找插入位置
        while (currentNode != nullptr) {
            parentNode = currentNode;
            if (key < currentNode->key) {
                std::cout << "键值 " << key << " 小于当前节点 " << currentNode->key << "，向左子树移动" << std::endl;
                currentNode = currentNode->left;
            } else {
                std::cout << "键值 " << key << " 大于等于当前节点 " << currentNode->key << "，向右子树移动" << std::endl;
                currentNode = currentNode->right;
            }
        }
        
        // 设置新节点的父节点
        newNode->parent = parentNode;
        
        // 如果树为空，则新节点成为根节点
        if (parentNode == nullptr) {
            setRoot(newNode);
        }
        // 否则将新节点作为父节点的左子节点或右子节点
        else if (key < parentNode->key) {
            std::cout << "将新节点 " << key << " 作为父节点 " << parentNode->key << " 的左子节点" << std::endl;
            parentNode->left = newNode;
        } else {
            std::cout << "将新节点 " << key << " 作为父节点 " << parentNode->key << " 的右子节点" << std::endl;
            parentNode->right = newNode;
        }
        
        std::cout << "成功插入节点 " << key << std::endl;
    }
    
    /**
     * 删除二叉搜索树中的节点
     * @param node 要删除的节点
     */
    void remove(TreeNode* node) {
        if (node == nullptr) {
            std::cout << "节点为空，无法删除" << std::endl;
            return;
        }
        
        std::cout << "\n删除节点: " << node->key << std::endl;
        
        // 情况1：节点没有左子节点
        if (node->left == nullptr) {
            std::cout << "节点 " << node->key << " 没有左子节点，用其右子树替换它" << std::endl;
            transplant(node, node->right);
        }
        // 情况2：节点没有右子节点但有左子节点
        else if (node->right == nullptr) {
            std::cout << "节点 " << node->key << " 没有右子节点，用其左子树替换它" << std::endl;
            transplant(node, node->left);
        }
        // 情况3：节点既有左子节点又有右子节点
        else {
            std::cout << "节点 " << node->key << " 既有左子节点又有右子节点" << std::endl;
            TreeNode* successorNode = minimum(node->right);  // 找到后继节点
            std::cout << "节点 " << node->key << " 的后继是 " << successorNode->key << std::endl;
            
            // 如果后继节点不是要删除节点的直接子节点
            if (successorNode->parent != node) {
                std::cout << "后继节点 " << successorNode->key << " 不是要删除节点 " << node->key << " 的直接子节点" << std::endl;
                transplant(successorNode, successorNode->right);
                successorNode->right = node->right;
                successorNode->right->parent = successorNode;
            }
            
            transplant(node, successorNode);
            successorNode->left = node->left;
            successorNode->left->parent = successorNode;
        }
        
        std::cout << "成功删除节点 " << node->key << std::endl;
        delete node;
    }
    
    /**
     * 用另一棵子树替换一棵子树
     * @param u 被替换的子树的根节点
     * @param v 替换的子树的根节点
     */
    void transplant(TreeNode* u, TreeNode* v) {
        std::cout << "用节点 ";
        if (v) std::cout << v->key;
        else std::cout << "nullptr";
        std::cout << " 替换节点 ";
        if (u) std::cout << u->key;
        else std::cout << "nullptr";
        std::cout << std::endl;
        
        if (u->parent == nullptr) {
            setRoot(v);
        } else if (u == u->parent->left) {
            u->parent->left = v;
        } else {
            u->parent->right = v;
        }
        
        if (v != nullptr) {
            v->parent = u->parent;
        }
    }
    
    /**
     * 中序遍历（左-根-右）
     * @param node 遍历的起始节点
     */
    void inorderTraversal(TreeNode* node) const {
        if (node) {
            std::cout << "进入节点 " << node->key << " 的左子树" << std::endl;
            inorderTraversal(node->left);
            std::cout << "访问节点: " << node->key << std::endl;
            std::cout << "进入节点 " << node->key << " 的右子树" << std::endl;
            inorderTraversal(node->right);
        }
    }
    
    /**
     * 前序遍历（根-左-右）
     * @param node 遍历的起始节点
     */
    void preorderTraversal(TreeNode* node) const {
        if (node) {
            std::cout << "访问节点: " << node->key << std::endl;
            std::cout << "进入节点 " << node->key << " 的左子树" << std::endl;
            preorderTraversal(node->left);
            std::cout << "进入节点 " << node->key << " 的右子树" << std::endl;
            preorderTraversal(node->right);
        }
    }
    
    /**
     * 后序遍历（左-右-根）
     * @param node 遍历的起始节点
     */
    void postorderTraversal(TreeNode* node) const {
        if (node) {
            std::cout << "进入节点 " << node->key << " 的左子树" << std::endl;
            postorderTraversal(node->left);
            std::cout << "进入节点 " << node->key << " 的右子树" << std::endl;
            postorderTraversal(node->right);
            std::cout << "访问节点: " << node->key << std::endl;
        }
    }
    
    /**
     * 层序遍历（广度优先遍历）
     */
    void levelOrderTraversal() const {
        if (!root) {
            std::cout << "树为空" << std::endl;
            return;
        }
        
        std::queue<TreeNode*> q;
        q.push(root);
        std::cout << "将根节点 " << root->key << " 加入队列" << std::endl;
        
        while (!q.empty()) {
            TreeNode* current = q.front();
            q.pop();
            std::cout << "处理节点: " << current->key << std::endl;
            
            // 将左右子节点加入队列
            if (current->left) {
                std::cout << "将节点 " << current->key << " 的左子节点 " << current->left->key << " 加入队列" << std::endl;
                q.push(current->left);
            }
            if (current->right) {
                std::cout << "将节点 " << current->key << " 的右子节点 " << current->right->key << " 加入队列" << std::endl;
                q.push(current->right);
            }
        }
        std::cout << std::endl;
    }
    
    /**
     * 打印二叉搜索树结构
     */
    void printTreeStructure() const {
        std::cout << "\n二叉搜索树结构:" << std::endl;
        if (!root) {
            std::cout << "空树" << std::endl;
            return;
        }
        printTreeHelper(root, "", true);
    }
    
private:
    /**
     * 辅助函数，用于打印树结构
     */
    void printTreeHelper(TreeNode* node, std::string prefix, bool isLast) const {
        if (node) {
            std::cout << prefix;
            if (isLast) {
                std::cout << "└── ";
                prefix += "    ";
            } else {
                std::cout << "├── ";
                prefix += "|   ";
            }
            std::cout << node->key << std::endl;
            
            bool hasLeft = (node->left != nullptr);
            bool hasRight = (node->right != nullptr);
            
            if (hasLeft || hasRight) {
                if (hasLeft) {
                    printTreeHelper(node->left, prefix, !hasRight);
                }
                if (hasRight) {
                    printTreeHelper(node->right, prefix, true);
                }
            }
        }
    }
};

int main() {
    std::cout << "=== 二叉搜索树演示 ===" << std::endl;
    
    BinarySearchTree bst;
    
    // 插入节点
    std::cout << "\n--- 插入操作 ---" << std::endl;
    bst.insert(15);
    bst.insert(6);
    bst.insert(18);
    bst.insert(3);
    bst.insert(7);
    bst.insert(17);
    bst.insert(20);
    bst.insert(2);
    bst.insert(4);
    bst.insert(13);
    bst.insert(9);
    
    bst.printTreeStructure();
    
    // 遍历操作
    std::cout << "\n--- 遍历操作 ---" << std::endl;
    std::cout << "\n中序遍历 (左-根-右): ";
    bst.inorderTraversal(bst.getRoot());
    std::cout << std::endl;
    
    std::cout << "\n前序遍历 (根-左-右): ";
    bst.preorderTraversal(bst.getRoot());
    std::cout << std::endl;
    
    std::cout << "\n后序遍历 (左-右-根): ";
    bst.postorderTraversal(bst.getRoot());
    std::cout << std::endl;
    
    std::cout << "\n层序遍历 (广度优先): ";
    bst.levelOrderTraversal();
    
    // 搜索操作
    std::cout << "\n--- 搜索操作 ---" << std::endl;
    TreeNode* found = bst.search(13);
    if (found) {
        std::cout << "找到了节点 " << found->key << std::endl;
    }
    
    found = bst.search(10);
    if (!found) {
        std::cout << "未找到节点 10" << std::endl;
    }
    
    // 递归搜索
    std::cout << "\n--- 递归搜索操作 ---" << std::endl;
    found = bst.searchRecursive(bst.getRoot(), 7);
    if (found) {
        std::cout << "递归搜索找到了节点 " << found->key << std::endl;
    }
    
    // 最小和最大元素
    std::cout << "\n--- 最小和最大元素 ---" << std::endl;
    TreeNode* minNode = bst.minimum(bst.getRoot());
    if (minNode) {
        std::cout << "最小元素: " << minNode->key << std::endl;
    }
    
    TreeNode* maxNode = bst.maximum(bst.getRoot());
    if (maxNode) {
        std::cout << "最大元素: " << maxNode->key << std::endl;
    }
    
    // 前驱和后继
    std::cout << "\n--- 前驱和后继 ---" << std::endl;
    TreeNode* node13 = bst.search(13);
    if (node13) {
        TreeNode* succ = bst.successor(node13);
        if (succ) {
            std::cout << "节点 " << node13->key << " 的后继: " << succ->key << std::endl;
        }
        
        TreeNode* pred = bst.predecessor(node13);
        if (pred) {
            std::cout << "节点 " << node13->key << " 的前驱: " << pred->key << std::endl;
        }
    }
    
    // 删除操作
    std::cout << "\n--- 删除操作 ---" << std::endl;
    TreeNode* nodeToDelete = bst.search(13);
    if (nodeToDelete) {
        bst.remove(nodeToDelete);
        bst.printTreeStructure();
    }
    
    nodeToDelete = bst.search(15);
    if (nodeToDelete) {
        bst.remove(nodeToDelete);
        bst.printTreeStructure();
    }
    
    return 0;
}
```

## 7. 算法分析

### 7.1 时间复杂度

二叉搜索树操作的时间复杂度与树的高度h密切相关：

- **搜索操作**: O(h)
- **最小元素**: O(h)
- **最大元素**: O(h)
- **前驱**: O(h)
- **后继**: O(h)
- **插入**: O(h)
- **删除**: O(h)

在最好的情况下（完全平衡的树），高度h = O(lg n)，所有操作的时间复杂度都是O(lg n)。

在最坏的情况下（退化为链表），高度h = O(n)，所有操作的时间复杂度都是O(n)。

### 7.2 空间复杂度

- **存储空间**: O(n)，其中n是树中节点的数量
- **递归栈空间**: O(h)，其中h是树的高度，最坏情况下为O(n)

### 7.3 稳定性

二叉搜索树的操作与稳定性无关，因为它主要用于搜索和排序操作，而不是排序算法。

## 8. 算法特点

### 8.1 优点

1. **高效搜索**: 在平衡状态下，搜索操作的时间复杂度为O(lg n)
2. **排序输出**: 中序遍历可以按排序顺序输出所有元素
3. **动态操作**: 支持动态插入和删除操作
4. **灵活性**: 可以方便地实现各种变种，如AVL树、红黑树等

### 8.2 缺点

1. **性能依赖结构**: 性能严重依赖于树的结构，最坏情况下退化为O(n)
2. **无固定结构**: 没有固定的平衡性保证
3. **额外空间**: 需要额外的指针存储父节点和子节点信息

## 9. 适用场景

1. **数据库索引**: 许多数据库系统使用B树或其变种作为索引结构
2. **文件系统**: 文件系统的目录结构可以使用BST组织
3. **表达式解析**: 编译器中使用BST来表示表达式树
4. **优先队列**: 可以用BST实现优先队列
5. **范围查询**: BST支持高效的范围查询操作

## 10. 与其他数据结构比较

| 数据结构 | 查找时间复杂度 | 插入时间复杂度 | 删除时间复杂度 | 空间复杂度 | 有序性 | 平衡性 |
|---------|---------------|---------------|---------------|-----------|--------|--------|
| 二叉搜索树 | O(h) | O(h) | O(h) | O(n) | 有序 | 无保证 |
| 红黑树 | O(lg n) | O(lg n) | O(lg n) | O(n) | 有序 | 平衡 |
| AVL树 | O(lg n) | O(lg n) | O(lg n) | O(n) | 有序 | 平衡 |
| 散列表 | O(1)平均 | O(1)平均 | O(1)平均 | O(m+n) | 无序 | 无 |
| 数组(有序) | O(lg n) | O(n) | O(n) | O(n) | 有序 | 固定 |

## 11. 优化方案

### 11.1 自平衡二叉搜索树

为了解决普通二叉搜索树可能退化为链表的问题，可以使用自平衡二叉搜索树：

1. **AVL树**: 严格保持平衡，左右子树高度差不超过1
2. **红黑树**: 近似平衡，保证最长路径不超过最短路径的2倍
3. **伸展树**: 通过旋转操作将频繁访问的节点移到根附近

### 11.2 B树和B+树

对于磁盘存储等外部存储场景，可以使用B树和B+树：

1. **降低高度**: 通过增加节点的子节点数量来降低树的高度
2. **减少IO**: 减少磁盘访问次数
3. **批量操作**: 支持批量插入和删除操作

### 11.3 Treap（树堆）

结合二叉搜索树和堆的特性：

1. **随机化**: 通过随机化键值来保证期望的平衡性
2. **简单实现**: 实现相对简单
3. **期望性能**: 期望时间复杂度为O(lg n)

## 12. 总结

二叉搜索树是计算机科学中最重要的数据结构之一。它通过将数据组织成具有特定性质的二叉树结构，实现了高效的搜索、插入和删除操作。《算法导论》第12章详细介绍了二叉搜索树的理论基础和实现方法，为我们理解和应用这一重要数据结构提供了坚实的基础。

在我们的实现中，提供了完整的二叉搜索树操作接口，包括：

1. **基本操作**: 搜索、插入、删除
2. **辅助操作**: 最小元素、最大元素、前驱、后继
3. **遍历操作**: 中序、前序、后序、层序遍历
4. **调试功能**: 树结构可视化输出

通过详细的执行过程输出，使用者可以清楚地看到每个操作的执行过程，加深对算法的理解。这对于学习和掌握二叉搜索树是非常有帮助的。

需要注意的是，普通二叉搜索树的性能严重依赖于输入数据的顺序。在实际应用中，通常会使用自平衡二叉搜索树（如AVL树、红黑树）来保证较好的性能。这些高级数据结构在后续章节中会有详细介绍。

总的来说，二叉搜索树是一种非常实用的数据结构，在需要维护有序数据集合的场景中有着广泛的应用。通过深入理解其原理和实现，可以为进一步学习更高级的数据结构和算法打下坚实的基础。