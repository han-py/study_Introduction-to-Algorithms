#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;

// 红黑树节点颜色枚举
enum Color { RED, BLACK };

// 红黑树节点结构
struct Node {
    int data;
    Color color;
    Node *left, *right, *parent;
    
    // 初始化节点
    Node(int data) {
        this->data = data;
        left = right = parent = nullptr;
        this->color = RED; // 新节点默认为红色
    }
};

// 红黑树类
class RedBlackTree {
private:
    Node *root;
    
    // 打印节点信息的辅助函数
    void printNodeInfo(Node *node, const string &description) {
        if (node == nullptr) {
            cout << "  " << description << ": nullptr" << endl;
            return;
        }
        
        cout << "  " << description << ": " << node->data 
             << " (" << (node->color == RED ? "R" : "B") << ")";
        if (node->parent) {
            cout << ", Parent: " << node->parent->data;
        } else {
            cout << ", Parent: nullptr";
        }
        cout << endl;
    }
    
    // 左旋操作
    void rotateLeft(Node *&node) {
        cout << "  Left rotate at node " << node->data << endl;
        
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
    }
    
    // 右旋操作
    void rotateRight(Node *&node) {
        cout << "  Right rotate at node " << node->data << endl;
        
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
    }
    
    // 修复插入后违反的红黑树性质
    void fixInsertViolation(Node *&node) {
        cout << "\n开始修复红黑树性质，当前节点: " << node->data << endl;
        
        Node *parent = nullptr;
        Node *grandparent = nullptr;
        
        while ((node != root) && (node->color != BLACK) && 
               (node->parent->color == RED)) {
            
            parent = node->parent;
            grandparent = parent->parent;
            
            printNodeInfo(parent, "Parent");
            printNodeInfo(grandparent, "Grandparent");
            
            /*  Case : 当父节点是祖父节点的左孩子 */
            if (parent == grandparent->left) {
                Node *uncle = grandparent->right;
                printNodeInfo(uncle, "Uncle");
                
                /* Case 1: 叔叔节点是红色，只需要重新着色 */
                if (uncle != nullptr && uncle->color == RED) {
                    cout << "  情况1: 叔叔节点是红色，重新着色" << endl;
                    grandparent->color = RED;
                    parent->color = BLACK;
                    uncle->color = BLACK;
                    node = grandparent;
                }
                
                else {
                    /* Case 2: node是父节点的右孩子，需要左旋 */
                    if (node == parent->right) {
                        cout << "  情况2: 当前节点是父节点的右孩子，对父节点左旋" << endl;
                        rotateLeft(parent);
                        node = parent;
                        parent = node->parent;
                    }
                    
                    /* Case 3: node是父节点的左孩子，需要右旋 */
                    cout << "  情况3: 对祖父节点右旋" << endl;
                    rotateRight(grandparent);
                    swap(parent->color, grandparent->color);
                    node = parent;
                }
            }
            
            /* Case : 当父节点是祖父节点的右孩子 */
            else {
                Node *uncle = grandparent->left;
                printNodeInfo(uncle, "Uncle");
                
                /* Case 1: 叔叔节点是红色，只需要重新着色 */
                if ((uncle != nullptr) && (uncle->color == RED)) {
                    cout << "  情况1: 叔叔节点是红色，重新着色" << endl;
                    grandparent->color = RED;
                    parent->color = BLACK;
                    uncle->color = BLACK;
                    node = grandparent;
                }
                
                else {
                    /* Case 2: node是父节点的左孩子，需要右旋 */
                    if (node == parent->left) {
                        cout << "  情况2: 当前节点是父节点的左孩子，对父节点右旋" << endl;
                        rotateRight(parent);
                        node = parent;
                        parent = node->parent;
                    }
                    
                    /* Case 3: node是父节点的右孩子，需要左旋 */
                    cout << "  情况3: 对祖父节点左旋" << endl;
                    rotateLeft(grandparent);
                    swap(parent->color, grandparent->color);
                    node = parent;
                }
            }
            
            cout << "  完成本轮修复\n" << endl;
        }
        
        cout << "设置根节点为黑色" << endl;
        root->color = BLACK;
        cout << "红黑树性质修复完成\n" << endl;
    }
    
public:
    // 构造函数
    RedBlackTree() { 
        root = nullptr; 
    }
    
    // 插入新节点
    void insert(const int &data) {
        cout << "----------------------------------------" << endl;
        cout << "插入节点: " << data << endl;
        cout << "----------------------------------------" << endl;
        
        Node *node = new Node(data);
        
        // 执行正常的BST插入
        root = bstInsert(root, node);
        
        // 修复可能违反的红黑树性质
        fixInsertViolation(node);
        
        cout << "最终树结构:" << endl;
        printTree();
        cout << "\n" << endl;
    }
    
    // BST插入的辅助函数
    Node* bstInsert(Node *root, Node *node) {
        cout << "BST插入过程:" << endl;
        
        // 如果树为空，返回新节点
        if (root == nullptr) {
            cout << "  树为空，直接插入根节点" << endl;
            return node;
        }
            
        // 否则递归向下查找位置
        if (node->data < root->data) {
            cout << "  节点 " << node->data << " 小于 " << root->data << "，向左子树插入" << endl;
            root->left = bstInsert(root->left, node);
            root->left->parent = root;
        }
        else if (node->data > root->data) {
            cout << "  节点 " << node->data << " 大于 " << root->data << "，向右子树插入" << endl;
            root->right = bstInsert(root->right, node);
            root->right->parent = root;
        }
        else {
            cout << "  节点 " << node->data << " 已存在，不插入重复节点" << endl;
            // 释放已分配的内存
            delete node;
            return root;
        }
        
        return root;
    }
    
    // 中序遍历
    void inorder() { 
        cout << "中序遍历结果: ";
        inorderHelper(root);
        cout << endl;
    }
    
    // 中序遍历辅助函数
    void inorderHelper(Node *node) {
        if (node == nullptr)
            return;
            
        inorderHelper(node->left);
        cout << node->data << "(" << (node->color == RED ? "R" : "B") << ") ";
        inorderHelper(node->right);
    }
    
    // 层序遍历（便于观察树结构）
    void levelOrder() {
        cout << "层序遍历结果: ";
        if (root == nullptr) {
            cout << "空树" << endl;
            return;
        }
        
        queue<Node*> q;
        q.push(root);
        
        while (!q.empty()) {
            Node *current = q.front();
            q.pop();
            
            cout << current->data << "(" << (current->color == RED ? "R" : "B") << ") ";
            
            if (current->left != nullptr)
                q.push(current->left);
                
            if (current->right != nullptr)
                q.push(current->right);
        }
        cout << endl;
    }
    
    // 打印树结构（使用标准的树形结构展示）
    void printTree() {
        if (root == nullptr) {
            cout << "空树" << endl;
            return;
        }

        printTreeHelper(root, "", true);
    }

    // 树结构打印辅助函数
    void printTreeHelper(Node *node, string indent, bool last) {
        if (node != nullptr) {
            cout << indent;
            if (last) {
                cout << "+-";
                indent += "  ";
            } else {
                cout << "|-";
                indent += "| ";
            }

            cout << node->data << "(" << (node->color == RED ? "R" : "B") << ")" << endl;

            if (node->left != nullptr || node->right != nullptr) {
                if (node->left)
                    printTreeHelper(node->left, indent, node->right == nullptr);
                else if (node->right)
                    cout << indent << "+-nullptr" << endl;

                if (node->right)
                    printTreeHelper(node->right, indent, true);
                else if (node->left)
                    cout << indent << "+-nullptr" << endl;
            }
        }
    }
    
    // 搜索节点
    bool search(const int &data) {
        cout << "搜索节点 " << data << ": ";
        bool result = searchHelper(root, data);
        cout << (result ? "找到" : "未找到") << endl;
        return result;
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
};

int main() {
#ifdef ACM_LOCAL
    freopen("data.in", "r", stdin);
    freopen("data.out", "w", stdout);
#endif
    RedBlackTree tree;
    
    cout << "红黑树示例程序" << endl;
    cout << "================" << endl << endl;
    
    // 插入一些测试数据
    int values[] = {10, 20, 30, 15, 25, 5, 1};
    int n = sizeof(values)/sizeof(values[0]);
    
    cout << "插入元素: ";
    for (int i = 0; i < n; i++) {
        cout << values[i] << " ";
    }
    cout << "\n\n";
    
    // 逐个插入并显示过程
    for (int i = 0; i < n; i++) {
        tree.insert(values[i]);
    }
    
    cout << "========================================" << endl;
    cout << "所有插入操作完成" << endl;
    cout << "========================================\n" << endl;
    
    tree.inorder();
    tree.levelOrder();
    tree.printTree();
    
    cout << "\n搜索测试:" << endl;
    tree.search(15);
    tree.search(100);
    
    return 0;
}