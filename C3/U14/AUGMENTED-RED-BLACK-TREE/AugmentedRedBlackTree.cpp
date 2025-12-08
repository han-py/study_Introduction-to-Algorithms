#include <iostream>
#include <queue>
using namespace std;

// 红黑树节点颜色枚举
enum Color { RED, BLACK };

// 扩张的红黑树节点结构（添加size字段用于顺序统计）
struct Node {
    int data;
    Color color;
    int size; // 以该节点为根的子树的节点数量
    Node *left, *right, *parent;
    
    // 初始化节点
    Node(int data) {
        this->data = data;
        left = right = parent = nullptr;
        this->color = RED; // 新节点默认为红色
        this->size = 1; // 新节点自身计数为1
    }
};

// 扩张的红黑树类（支持顺序统计操作）
class AugmentedRedBlackTree {
private:
    Node *root;
    
    // 更新节点的size值
    void updateSize(Node *node) {
        if (node == nullptr) return;
        
        int leftSize = (node->left != nullptr) ? node->left->size : 0;
        int rightSize = (node->right != nullptr) ? node->right->size : 0;
        node->size = 1 + leftSize + rightSize;
    }
    
    // 左旋操作
    void rotateLeft(Node *&node) {
        Node *rightChild = node->right;
        node->right = rightChild->left;
        
        if (node->right != nullptr)
            node->right->parent = node;
            
        rightChild->parent = node->parent;
        
        if (node->parent == nullptr)
            root = rightChild;
        else if (node == node->parent->left)
            node->parent->left = rightChild;
        else
            node->parent->right = rightChild;
            
        rightChild->left = node;
        node->parent = rightChild;
        
        // 更新size值
        updateSize(node);
        updateSize(rightChild);
    }
    
    // 右旋操作
    void rotateRight(Node *&node) {
        Node *leftChild = node->left;
        node->left = leftChild->right;
        
        if (node->left != nullptr)
            node->left->parent = node;
            
        leftChild->parent = node->parent;
        
        if (node->parent == nullptr)
            root = leftChild;
        else if (node == node->parent->left)
            node->parent->left = leftChild;
        else
            node->parent->right = leftChild;
            
        leftChild->right = node;
        node->parent = leftChild;
        
        // 更新size值
        updateSize(node);
        updateSize(leftChild);
    }
    
    // 修复插入后违反的红黑树性质
    void fixInsertViolation(Node *&node) {
        Node *parent = nullptr;
        Node *grandparent = nullptr;
        
        while ((node != root) && (node->color != BLACK) && 
               (node->parent->color == RED)) {
            
            parent = node->parent;
            grandparent = parent->parent;
            
            /*  Case : 当父节点是祖父节点的左孩子 */
            if (parent == grandparent->left) {
                Node *uncle = grandparent->right;
                
                /* Case 1: 叔叔节点是红色，只需要重新着色 */
                if (uncle != nullptr && uncle->color == RED) {
                    grandparent->color = RED;
                    parent->color = BLACK;
                    uncle->color = BLACK;
                    node = grandparent;
                }
                
                else {
                    /* Case 2: node是父节点的右孩子，需要左旋 */
                    if (node == parent->right) {
                        rotateLeft(parent);
                        node = parent;
                        parent = node->parent;
                    }
                    
                    /* Case 3: node是父节点的左孩子，需要右旋 */
                    rotateRight(grandparent);
                    swap(parent->color, grandparent->color);
                    node = parent;
                }
            }
            
            /* Case : 当父节点是祖父节点的右孩子 */
            else {
                Node *uncle = grandparent->left;
                
                /* Case 1: 叔叔节点是红色，只需要重新着色 */
                if ((uncle != nullptr) && (uncle->color == RED)) {
                    grandparent->color = RED;
                    parent->color = BLACK;
                    uncle->color = BLACK;
                    node = grandparent;
                }
                
                else {
                    /* Case 2: node是父节点的左孩子，需要右旋 */
                    if (node == parent->left) {
                        rotateRight(parent);
                        node = parent;
                        parent = node->parent;
                    }
                    
                    /* Case 3: node是父节点的右孩子，需要左旋 */
                    rotateLeft(grandparent);
                    swap(parent->color, grandparent->color);
                    node = parent;
                }
            }
        }
        
        root->color = BLACK;
    }
    
    // 递归更新从指定节点到根节点路径上所有节点的size
    void updateSizeToRoot(Node *node) {
        if (node == nullptr) return;
        updateSize(node);
        updateSizeToRoot(node->parent);
    }
    
public:
    // 构造函数
    AugmentedRedBlackTree() { 
        root = nullptr; 
    }
    
    // 插入新节点
    void insert(const int &data) {
        Node *node = new Node(data);
        
        // 执行正常的BST插入
        root = bstInsert(root, node);
        
        // 更新从插入节点到根节点路径上所有节点的size
        updateSizeToRoot(node);
        
        // 修复可能违反的红黑树性质
        fixInsertViolation(node);
    }
    
    // BST插入的辅助函数
    Node* bstInsert(Node *root, Node *node) {
        // 如果树为空，返回新节点
        if (root == nullptr)
            return node;
            
        // 否则递归向下查找位置
        if (node->data < root->data) {
            root->left = bstInsert(root->left, node);
            root->left->parent = root;
        }
        else if (node->data > root->data) {
            root->right = bstInsert(root->right, node);
            root->right->parent = root;
        }
        
        // 返回未改变的节点指针
        return root;
    }
    
    // 中序遍历
    void inorder() { 
        inorderHelper(root);
        cout << endl;
    }
    
    // 中序遍历辅助函数
    void inorderHelper(Node *node) {
        if (node == nullptr)
            return;
            
        inorderHelper(node->left);
        cout << node->data << "(" << (node->color == RED ? "R" : "B") << ",size=" << node->size << ") ";
        inorderHelper(node->right);
    }
    
    // 层序遍历（便于观察树结构）
    void levelOrder() {
        if (root == nullptr) return;
        
        queue<Node*> q;
        q.push(root);
        
        while (!q.empty()) {
            Node *current = q.front();
            q.pop();
            
            cout << current->data << "(" << (current->color == RED ? "R" : "B") << ",size=" << current->size << ") ";
            
            if (current->left != nullptr)
                q.push(current->left);
                
            if (current->right != nullptr)
                q.push(current->right);
        }
        cout << endl;
    }
    
    // 搜索节点
    bool search(const int &data) {
        return searchHelper(root, data);
    }
    
    // 搜索辅助函数
    bool searchHelper(Node *node, const int &data) {
        if (node == nullptr)
            return false;
            
        if (node->data == data)
            return true;
            
        if (data < node->data)
            return searchHelper(node->left, data);
        else
            return searchHelper(node->right, data);
    }
    
    // 查找第k小的元素（顺序统计）
    int select(int k) {
        if (root == nullptr || k <= 0 || k > root->size) {
            throw invalid_argument("Invalid rank k");
        }
        return selectHelper(root, k);
    }
    
    // 查找第k小元素的辅助函数
    int selectHelper(Node *node, int k) {
        if (node == nullptr) {
            throw invalid_argument("Node is null");
        }
        
        int leftSize = (node->left != nullptr) ? node->left->size : 0;
        
        if (k == leftSize + 1) {
            return node->data;
        } else if (k <= leftSize) {
            return selectHelper(node->left, k);
        } else {
            return selectHelper(node->right, k - leftSize - 1);
        }
    }
    
    // 确定元素的秩（元素在排序顺序中的位置）
    int rank(int data) {
        return rankHelper(root, data);
    }
    
    // 确定元素秩的辅助函数
    int rankHelper(Node *node, int data) {
        if (node == nullptr) {
            return 0;
        }
        
        if (data < node->data) {
            return rankHelper(node->left, data);
        } else if (data > node->data) {
            int leftSize = (node->left != nullptr) ? node->left->size : 0;
            return 1 + leftSize + rankHelper(node->right, data);
        } else {
            int leftSize = (node->left != nullptr) ? node->left->size : 0;
            return 1 + leftSize;
        }
    }
};

int main() {
    AugmentedRedBlackTree tree;
    
    cout << "扩张红黑树示例程序 - 支持顺序统计操作\n";
    cout << "=========================================\n\n";
    
    // 插入一些测试数据
    int values[] = {10, 20, 30, 15, 25, 5, 1};
    int n = sizeof(values)/sizeof(values[0]);
    
    cout << "插入元素: ";
    for (int i = 0; i < n; i++) {
        cout << values[i] << " ";
        tree.insert(values[i]);
    }
    cout << "\n\n";
    
    cout << "中序遍历结果 (显示节点值、颜色和子树大小): ";
    tree.inorder();
    
    cout << "层序遍历结果 (显示节点值、颜色和子树大小): ";
    tree.levelOrder();
    
    cout << "\n顺序统计操作演示:\n";
    try {
        cout << "第1小的元素: " << tree.select(1) << endl;
        cout << "第3小的元素: " << tree.select(3) << endl;
        cout << "第5小的元素: " << tree.select(5) << endl;
        cout << "第7小的元素: " << tree.select(7) << endl;
    } catch (const exception& e) {
        cout << "异常: " << e.what() << endl;
    }
    
    cout << "\n秩操作演示:\n";
    cout << "元素 1 的秩: " << tree.rank(1) << endl;
    cout << "元素 10 的秩: " << tree.rank(10) << endl;
    cout << "元素 15 的秩: " << tree.rank(15) << endl;
    cout << "元素 30 的秩: " << tree.rank(30) << endl;
    
    cout << "\n搜索测试:\n";
    cout << "搜索 15: " << (tree.search(15) ? "找到" : "未找到") << endl;
    cout << "搜索 100: " << (tree.search(100) ? "找到" : "未找到") << endl;
    
    return 0;
}