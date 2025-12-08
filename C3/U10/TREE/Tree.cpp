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
    TreeNode* rightSibling;      // 指向右侧相邻的兄弟节点的指针
    
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
        return new BinaryTreeNode(key);
    }
    
    /**
     * 设置根节点
     * @param node 新的根节点
     */
    void setRoot(BinaryTreeNode* node) {
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
            inorderTraversal(node->left);
            std::cout << node->key << " ";
            inorderTraversal(node->right);
        }
    }
    
    /**
     * 前序遍历（根-左-右）
     * @param node 遍历的起始节点
     */
    void preorderTraversal(BinaryTreeNode* node) const {
        if (node) {
            std::cout << node->key << " ";
            preorderTraversal(node->left);
            preorderTraversal(node->right);
        }
    }
    
    /**
     * 后序遍历（左-右-根）
     * @param node 遍历的起始节点
     */
    void postorderTraversal(BinaryTreeNode* node) const {
        if (node) {
            postorderTraversal(node->left);
            postorderTraversal(node->right);
            std::cout << node->key << " ";
        }
    }
    
    /**
     * 层序遍历（广度优先遍历）
     */
    void levelOrderTraversal() const {
        if (!root) return;
        
        std::queue<BinaryTreeNode*> q;
        q.push(root);
        
        while (!q.empty()) {
            BinaryTreeNode* current = q.front();
            q.pop();
            
            std::cout << current->key << " ";
            
            // 将左右子节点加入队列
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
        return new TreeNode(key);
    }
    
    /**
     * 设置根节点
     * @param node 新的根节点
     */
    void setRoot(TreeNode* node) {
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
     * @param node 遍历的起始节点
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
            
            // 将所有兄弟节点依次输出
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
     * 计算以指定节点为根的子树的高度
     * @param node 子树的根节点
     * @return 子树的高度
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
     * 计算以指定节点为根的子树的节点数量
     * @param node 子树的根节点
     * @return 子树的节点数量
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
    
    /**
     * 查找具有指定键值的节点
     * @param node 搜索起始节点
     * @param key 要查找的键值
     * @return 找到的节点指针，未找到返回nullptr
     */
    TreeNode* searchNode(TreeNode* node, int key) const {
        if (!node) return nullptr;
        
        if (node->key == key) {
            return node;
        }
        
        // 在子节点中查找
        TreeNode* result = searchNode(node->leftChild, key);
        if (result) {
            return result;
        }
        
        // 在兄弟节点中查找
        return searchNode(node->rightSibling, key);
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
    
    // 演示节点查找
    TreeNode* found = rootedTree.searchNode(rootedTree.getRoot(), 7);
    if (found) {
        std::cout << "找到了节点7" << std::endl;
    } else {
        std::cout << "未找到节点7" << std::endl;
    }
    
    return 0;
}