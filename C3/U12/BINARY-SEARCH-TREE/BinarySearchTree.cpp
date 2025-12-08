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
#ifdef ACM_LOCAL
    freopen("data.in", "r", stdin);
    freopen("data.out", "w", stdout);
#endif
    
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