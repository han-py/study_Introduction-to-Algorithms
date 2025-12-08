#include <iostream>
#include <vector>
#include <queue>

/**
 * 有根树的表示
 * 根据《算法导论》第10章内容实现
 * 
 * 本程序实现了两种有根树的表示方法：
 * 1. 二叉树表示法：每个节点最多有两个子节点
 * 2. 左孩子右兄弟表示法：可以表示任意有根树
 */

// 二叉树节点结构
struct BinaryTreeNode {
    int key;                 // 节点存储的数据
    BinaryTreeNode* parent;  // 指向父节点的指针
    BinaryTreeNode* left;    // 指向左子节点的指针
    BinaryTreeNode* right;   // 指向右子节点的指针
    
    /**
     * 构造函数
     * @param k 节点的键值
     */
    BinaryTreeNode(int k) : key(k), parent(nullptr), left(nullptr), right(nullptr) {}
};

// 任意有根树节点结构（左孩子右兄弟表示法）
struct TreeNode {
    int key;                    // 节点存储的数据
    TreeNode* parent;           // 指向父节点的指针
    TreeNode* leftChild;        // 指向最左边的孩子节点的指针
    TreeNode* rightSibling;     // 指向右侧相邻的兄弟节点的指针
    
    /**
     * 构造函数
     * @param k 节点的键值
     */
    TreeNode(int k) : key(k), parent(nullptr), leftChild(nullptr), rightSibling(nullptr) {}
};

// 二叉树类
class BinaryTree {
private:
    BinaryTreeNode* root;  // 指向根节点的指针
    
public:
    /**
     * 构造函数，初始化空树
     */
    BinaryTree() : root(nullptr) {}
    
    /**
     * 析构函数，释放整棵树的内存
     */
    ~BinaryTree() {
        destroyTree(root);
    }
    
    /**
     * 递归销毁整棵树
     * @param node 要销毁的节点
     */
    void destroyTree(BinaryTreeNode* node) {
        if (node) {
            std::cout << "销毁节点: " << node->key << std::endl;
            destroyTree(node->left);
            destroyTree(node->right);
            delete node;
        }
    }
    
    /**
     * 创建一个新的二叉树节点
     * @param key 节点的键值
     * @return 指向新创建节点的指针
     */
    BinaryTreeNode* createNode(int key) {
        std::cout << "创建节点: " << key << std::endl;
        return new BinaryTreeNode(key);
    }
    
    /**
     * 设置根节点
     * @param node 新的根节点
     */
    void setRoot(BinaryTreeNode* node) {
        std::cout << "设置根节点为: " << (node ? std::to_string(node->key) : "nullptr") << std::endl;
        root = node;
        if (root) {
            root->parent = nullptr;
        }
    }
    
    /**
     * 获取根节点
     * @return 指向根节点的指针
     */
    BinaryTreeNode* getRoot() const {
        return root;
    }
    
    /**
     * 中序遍历（左-根-右）
     * @param node 遍历的起始节点
     */
    void inorderTraversal(BinaryTreeNode* node) const {
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
    void preorderTraversal(BinaryTreeNode* node) const {
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
    void postorderTraversal(BinaryTreeNode* node) const {
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
        
        std::queue<BinaryTreeNode*> q;
        q.push(root);
        std::cout << "将根节点 " << root->key << " 加入队列" << std::endl;
        
        while (!q.empty()) {
            BinaryTreeNode* current = q.front();
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
     * 打印二叉树结构
     */
    void printTreeStructure() const {
        std::cout << "\n二叉树结构:" << std::endl;
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
    void printTreeHelper(BinaryTreeNode* node, std::string prefix, bool isLast) const {
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

// 任意有根树类（左孩子右兄弟表示法）
class RootedTree {
private:
    TreeNode* root;  // 指向根节点的指针
    
public:
    /**
     * 构造函数，初始化空树
     */
    RootedTree() : root(nullptr) {}
    
    /**
     * 析构函数，释放整棵树的内存
     */
    ~RootedTree() {
        destroyTree(root);
    }
    
    /**
     * 递归销毁整棵树
     * @param node 要销毁的节点
     */
    void destroyTree(TreeNode* node) {
        if (node) {
            std::cout << "销毁节点: " << node->key << std::endl;
            // 先销毁所有兄弟节点
            destroyTree(node->rightSibling);
            // 再销毁所有子节点
            destroyTree(node->leftChild);
            // 最后销毁当前节点
            delete node;
        }
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
     * 获取根节点
     * @return 指向根节点的指针
     */
    TreeNode* getRoot() const {
        return root;
    }
    
    /**
     * 前序遍历（深度优先）
     * @param node 遍历的起始节点
     */
    void preorderTraversal(TreeNode* node) const {
        if (node) {
            std::cout << "访问节点: " << node->key << std::endl;
            
            // 遍历第一个子节点
            if (node->leftChild) {
                std::cout << "进入节点 " << node->key << " 的第一个子节点 " << node->leftChild->key << std::endl;
                preorderTraversal(node->leftChild);
            }
            
            // 遍历兄弟节点
            if (node->rightSibling) {
                std::cout << "进入节点 " << node->key << " 的右侧兄弟节点 " << node->rightSibling->key << std::endl;
                preorderTraversal(node->rightSibling);
            }
        }
    }
    
    /**
     * 后序遍历（深度优先）
     * @param node 遍历的起始节点
     */
    void postorderTraversal(TreeNode* node) const {
        if (node) {
            // 遍历第一个子节点
            if (node->leftChild) {
                std::cout << "进入节点 " << node->key << " 的第一个子节点 " << node->leftChild->key << std::endl;
                postorderTraversal(node->leftChild);
            }
            
            // 遍历兄弟节点
            if (node->rightSibling) {
                std::cout << "进入节点 " << node->key << " 的右侧兄弟节点 " << node->rightSibling->key << std::endl;
                postorderTraversal(node->rightSibling);
            }
            
            std::cout << "访问节点: " << node->key << std::endl;
        }
    }
    
    /**
     * 层序遍历（广度优先）
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
            
            // 将所有兄弟节点依次输出
            TreeNode* sibling = current->rightSibling;
            while (sibling) {
                std::cout << "处理兄弟节点: " << sibling->key << std::endl;
                sibling = sibling->rightSibling;
            }
            
            // 将第一个子节点加入队列
            if (current->leftChild) {
                std::cout << "将节点 " << current->key << " 的第一个子节点 " << current->leftChild->key << " 加入队列" << std::endl;
                q.push(current->leftChild);
            }
        }
        std::cout << std::endl;
    }
    
    /**
     * 计算以指定节点为根的子树的高度
     * @param node 子树的根节点
     * @return 子树的高度
     */
    int getHeight(TreeNode* node) const {
        if (!node) return -1;
        
        std::cout << "计算节点 " << node->key << " 的高度" << std::endl;
        int maxHeight = -1;
        
        // 遍历所有子节点，找出最大高度
        TreeNode* child = node->leftChild;
        while (child) {
            std::cout << "检查子节点 " << child->key << std::endl;
            int height = getHeight(child);
            std::cout << "子节点 " << child->key << " 的高度为 " << height << std::endl;
            if (height > maxHeight) {
                maxHeight = height;
            }
            child = child->rightSibling;
        }
        
        int result = maxHeight + 1;
        std::cout << "节点 " << node->key << " 的高度为 " << result << std::endl;
        return result;
    }
    
    /**
     * 计算以指定节点为根的子树的节点数量
     * @param node 子树的根节点
     * @return 子树的节点数量
     */
    int getNodeCount(TreeNode* node) const {
        if (!node) return 0;
        
        std::cout << "计算节点 " << node->key << " 为根的子树节点数" << std::endl;
        int count = 1; // 当前节点
        std::cout << "当前节点 " << node->key << " 计入统计" << std::endl;
        
        // 计算所有子节点的数量
        TreeNode* child = node->leftChild;
        while (child) {
            std::cout << "统计子节点 " << child->key << " 为根的子树节点数" << std::endl;
            int childCount = getNodeCount(child);
            std::cout << "子节点 " << child->key << " 为根的子树有 " << childCount << " 个节点" << std::endl;
            count += childCount;
            child = child->rightSibling;
        }
        
        // 计算所有兄弟节点的数量
        if (node->rightSibling) {
            std::cout << "统计兄弟节点 " << node->rightSibling->key << " 为根的子树节点数" << std::endl;
            int siblingCount = getNodeCount(node->rightSibling);
            std::cout << "兄弟节点 " << node->rightSibling->key << " 为根的子树有 " << siblingCount << " 个节点" << std::endl;
            count += siblingCount;
        }
        
        std::cout << "以节点 " << node->key << " 为根的子树共有 " << count << " 个节点" << std::endl;
        return count;
    }
    
    /**
     * 查找具有指定键值的节点
     * @param node 搜索起始节点
     * @param key 要查找的键值
     * @return 找到的节点指针，未找到返回nullptr
     */
    TreeNode* searchNode(TreeNode* node, int key) const {
        if (!node) {
            std::cout << "到达空节点，未找到键值 " << key << std::endl;
            return nullptr;
        }
        
        std::cout << "在节点 " << node->key << " 中查找键值 " << key << std::endl;
        if (node->key == key) {
            std::cout << "在节点 " << node->key << " 中找到键值 " << key << std::endl;
            return node;
        }
        
        // 在子节点中查找
        std::cout << "在节点 " << node->key << " 的子节点中查找键值 " << key << std::endl;
        TreeNode* result = searchNode(node->leftChild, key);
        if (result) {
            return result;
        }
        
        // 在兄弟节点中查找
        std::cout << "在节点 " << node->key << " 的兄弟节点中查找键值 " << key << std::endl;
        return searchNode(node->rightSibling, key);
    }
    
    /**
     * 打印树结构
     */
    void printTreeStructure() const {
        std::cout << "\n有根树结构 (左孩子右兄弟表示法):" << std::endl;
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
            
            bool hasLeftChild = (node->leftChild != nullptr);
            bool hasRightSibling = (node->rightSibling != nullptr);
            
            if (hasLeftChild) {
                printTreeHelper(node->leftChild, prefix, !hasRightSibling);
            }
            if (hasRightSibling) {
                printTreeHelper(node->rightSibling, prefix, true);
            }
        }
    }
};

int main() {
#ifdef ACM_LOCAL
    freopen("data.in", "r", stdin);
    freopen("data.out", "w", stdout);
#endif
    std::cout << "=== 有根树的表示演示 ===" << std::endl;
    
    // 演示二叉树
    std::cout << "\n--- 二叉树演示 ---" << std::endl;
    BinaryTree binaryTree;
    
    // 创建节点
    std::cout << "\n1. 创建节点:" << std::endl;
    BinaryTreeNode* root = binaryTree.createNode(1);
    BinaryTreeNode* node2 = binaryTree.createNode(2);
    BinaryTreeNode* node3 = binaryTree.createNode(3);
    BinaryTreeNode* node4 = binaryTree.createNode(4);
    BinaryTreeNode* node5 = binaryTree.createNode(5);
    
    // 构建二叉树结构
    std::cout << "\n2. 构建二叉树结构:" << std::endl;
    std::cout << "       1" << std::endl;
    std::cout << "      / \\" << std::endl;
    std::cout << "     2   3" << std::endl;
    std::cout << "    / \\" << std::endl;
    std::cout << "   4   5" << std::endl;
    
    binaryTree.setRoot(root);
    std::cout << "设置节点 " << node2->key << " 为节点 " << root->key << " 的左子节点" << std::endl;
    root->left = node2;
    node2->parent = root;
    std::cout << "设置节点 " << node3->key << " 为节点 " << root->key << " 的右子节点" << std::endl;
    root->right = node3;
    node3->parent = root;
    std::cout << "设置节点 " << node4->key << " 为节点 " << node2->key << " 的左子节点" << std::endl;
    node2->left = node4;
    node4->parent = node2;
    std::cout << "设置节点 " << node5->key << " 为节点 " << node2->key << " 的右子节点" << std::endl;
    node2->right = node5;
    node5->parent = node2;
    
    binaryTree.printTreeStructure();
    
    std::cout << "\n3. 遍历二叉树:" << std::endl;
    std::cout << "\n前序遍历 (根-左-右): ";
    binaryTree.preorderTraversal(binaryTree.getRoot());
    std::cout << std::endl;
    
    std::cout << "\n中序遍历 (左-根-右): ";
    binaryTree.inorderTraversal(binaryTree.getRoot());
    std::cout << std::endl;
    
    std::cout << "\n后序遍历 (左-右-根): ";
    binaryTree.postorderTraversal(binaryTree.getRoot());
    std::cout << std::endl;
    
    std::cout << "\n层序遍历 (广度优先): ";
    binaryTree.levelOrderTraversal();
    
    // 演示任意有根树（左孩子右兄弟表示法）
    std::cout << "\n--- 任意有根树演示（左孩子右兄弟表示法） ---" << std::endl;
    RootedTree rootedTree;
    
    // 创建节点
    std::cout << "\n1. 创建节点:" << std::endl;
    TreeNode* r = rootedTree.createNode(1);   // 根节点
    TreeNode* n2 = rootedTree.createNode(2);
    TreeNode* n3 = rootedTree.createNode(3);
    TreeNode* n4 = rootedTree.createNode(4);
    TreeNode* n5 = rootedTree.createNode(5);
    TreeNode* n6 = rootedTree.createNode(6);
    TreeNode* n7 = rootedTree.createNode(7);
    
    // 构建树结构
    std::cout << "\n2. 构建树结构:" << std::endl;
    std::cout << "        1" << std::endl;
    std::cout << "     /  |  \\" << std::endl;
    std::cout << "    2   3   4" << std::endl;
    std::cout << "   /|   |   |\\" << std::endl;
    std::cout << "  5 6   7   8 9" << std::endl;
    
    rootedTree.setRoot(r);
    
    // 设置节点1的孩子
    std::cout << "\n3. 建立节点关系:" << std::endl;
    std::cout << "设置节点 " << n2->key << " 为节点 " << r->key << " 的第一个子节点" << std::endl;
    r->leftChild = n2;
    n2->parent = r;
    
    // 设置节点2的兄弟（节点3和4）
    std::cout << "设置节点 " << n3->key << " 为节点 " << n2->key << " 的右侧兄弟节点" << std::endl;
    n2->rightSibling = n3;
    n3->parent = r;
    std::cout << "设置节点 " << n4->key << " 为节点 " << n3->key << " 的右侧兄弟节点" << std::endl;
    n3->rightSibling = n4;
    n4->parent = r;
    
    // 设置节点2的孩子（节点5和6）
    std::cout << "设置节点 " << n5->key << " 为节点 " << n2->key << " 的第一个子节点" << std::endl;
    n2->leftChild = n5;
    n5->parent = n2;
    std::cout << "设置节点 " << n6->key << " 为节点 " << n5->key << " 的右侧兄弟节点" << std::endl;
    n5->rightSibling = n6;
    n6->parent = n2;
    
    // 设置节点3的孩子（节点7）
    std::cout << "设置节点 " << n7->key << " 为节点 " << n3->key << " 的第一个子节点" << std::endl;
    n3->leftChild = n7;
    n7->parent = n3;
    
    // 注意：为了简化演示，这里省略了节点4的孩子（8和9）
    
    rootedTree.printTreeStructure();
    
    std::cout << "\n4. 遍历有根树:" << std::endl;
    std::cout << "\n前序遍历: ";
    rootedTree.preorderTraversal(rootedTree.getRoot());
    std::cout << std::endl;
    
    std::cout << "\n后序遍历: ";
    rootedTree.postorderTraversal(rootedTree.getRoot());
    std::cout << std::endl;
    
    std::cout << "\n层序遍历: ";
    rootedTree.levelOrderTraversal();
    
    std::cout << "\n5. 计算树的属性:" << std::endl;
    std::cout << "\n计算树的高度:" << std::endl;
    std::cout << "树的高度: " << rootedTree.getHeight(rootedTree.getRoot()) << std::endl;
    
    std::cout << "\n计算节点数量:" << std::endl;
    std::cout << "节点总数: " << rootedTree.getNodeCount(rootedTree.getRoot()) << std::endl;
    
    // 演示节点查找
    std::cout << "\n6. 节点查找演示:" << std::endl;
    TreeNode* found = rootedTree.searchNode(rootedTree.getRoot(), 7);
    if (found) {
        std::cout << "找到了节点7" << std::endl;
    } else {
        std::cout << "未找到节点7" << std::endl;
    }
    
    return 0;
}