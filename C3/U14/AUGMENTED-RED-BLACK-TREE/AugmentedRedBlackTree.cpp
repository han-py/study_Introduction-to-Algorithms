#include <iostream>
#include <queue>
#include <vector>
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
        cout << "    更新节点 " << node->data << " 的size为 " << node->size << endl;
    }
    
    // 左旋操作
    void rotateLeft(Node *&node) {
        cout << "  执行左旋操作，以节点 " << node->data << " 为中心" << endl;
        
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
        
        cout << "  左旋完成" << endl;
    }
    
    // 右旋操作
    void rotateRight(Node *&node) {
        cout << "  执行右旋操作，以节点 " << node->data << " 为中心" << endl;
        
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
        
        cout << "  右旋完成" << endl;
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
            
            cout << "  当前节点: " << node->data << "(" << (node->color == RED ? "R" : "B") << ")" << endl;
            cout << "  父节点: " << parent->data << "(" << (parent->color == RED ? "R" : "B") << ")" << endl;
            cout << "  祖父节点: " << grandparent->data << "(" << (grandparent->color == RED ? "R" : "B") << ")" << endl;
            
            /*  Case : 当父节点是祖父节点的左孩子 */
            if (parent == grandparent->left) {
                Node *uncle = grandparent->right;
                
                cout << "  叔叔节点: ";
                if (uncle != nullptr) {
                    cout << uncle->data << "(" << (uncle->color == RED ? "R" : "B") << ")" << endl;
                } else {
                    cout << "nullptr" << endl;
                }
                
                /* Case 1: 叔叔节点是红色，只需要重新着色 */
                if (uncle != nullptr && uncle->color == RED) {
                    cout << "  情况1: 叔叔节点是红色，执行重新着色" << endl;
                    grandparent->color = RED;
                    parent->color = BLACK;
                    uncle->color = BLACK;
                    cout << "    祖父节点 " << grandparent->data << " 设为红色" << endl;
                    cout << "    父节点 " << parent->data << " 设为黑色" << endl;
                    cout << "    叔叔节点 " << uncle->data << " 设为黑色" << endl;
                    node = grandparent;
                }
                
                else {
                    /* Case 2: node是父节点的右孩子，需要左旋 */
                    if (node == parent->right) {
                        cout << "  情况2: 当前节点是父节点的右孩子，先对父节点执行左旋" << endl;
                        rotateLeft(parent);
                        node = parent;
                        parent = node->parent;
                        cout << "    旋转后的新节点: " << node->data << endl;
                        if (parent) {
                            cout << "    旋转后的新父节点: " << parent->data << endl;
                        }
                    }
                    
                    /* Case 3: node是父节点的左孩子，需要右旋 */
                    cout << "  情况3: 对祖父节点执行右旋" << endl;
                    rotateRight(grandparent);
                    cout << "  交换父节点和祖父节点的颜色" << endl;
                    swap(parent->color, grandparent->color);
                    node = parent;
                }
            }
            
            /* Case : 当父节点是祖父节点的右孩子 */
            else {
                Node *uncle = grandparent->left;
                
                cout << "  叔叔节点: ";
                if (uncle != nullptr) {
                    cout << uncle->data << "(" << (uncle->color == RED ? "R" : "B") << ")" << endl;
                } else {
                    cout << "nullptr" << endl;
                }
                
                /* Case 1: 叔叔节点是红色，只需要重新着色 */
                if ((uncle != nullptr) && (uncle->color == RED)) {
                    cout << "  情况1: 叔叔节点是红色，执行重新着色" << endl;
                    grandparent->color = RED;
                    parent->color = BLACK;
                    uncle->color = BLACK;
                    cout << "    祖父节点 " << grandparent->data << " 设为红色" << endl;
                    cout << "    父节点 " << parent->data << " 设为黑色" << endl;
                    cout << "    叔叔节点 " << uncle->data << " 设为黑色" << endl;
                    node = grandparent;
                }
                
                else {
                    /* Case 2: node是父节点的左孩子，需要右旋 */
                    if (node == parent->left) {
                        cout << "  情况2: 当前节点是父节点的左孩子，先对父节点执行右旋" << endl;
                        rotateRight(parent);
                        node = parent;
                        parent = node->parent;
                        cout << "    旋转后的新节点: " << node->data << endl;
                        if (parent) {
                            cout << "    旋转后的新父节点: " << parent->data << endl;
                        }
                    }
                    
                    /* Case 3: node是父节点的右孩子，需要左旋 */
                    cout << "  情况3: 对祖父节点执行左旋" << endl;
                    rotateLeft(grandparent);
                    cout << "  交换父节点和祖父节点的颜色" << endl;
                    swap(parent->color, grandparent->color);
                    node = parent;
                }
            }
            
            cout << "  完成本轮修复，进入下一轮检查\n" << endl;
        }
        
        cout << "将根节点设置为黑色" << endl;
        root->color = BLACK;
        cout << "红黑树性质修复完成\n" << endl;
    }
    
    // 递归更新从指定节点到根节点路径上所有节点的size
    void updateSizeToRoot(Node *node) {
        if (node == nullptr) return;
        cout << "  更新从节点 " << node->data << " 到根节点路径上的size值" << endl;
        updateSize(node);
        updateSizeToRoot(node->parent);
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
            
            cout << node->data << "(" << (node->color == RED ? "R" : "B") << ",size=" << node->size << ")" << endl;
            
            // 正确处理子节点的显示
            if (node->left != nullptr || node->right != nullptr) {
                if (node->left) {
                    printTreeHelper(node->left, indent, node->right == nullptr);
                } else {
                    cout << indent;
                    if (node->right) {
                        cout << "|-";
                    } else {
                        cout << "+-";
                    }
                    cout << "nullptr" << endl;
                }
                
                if (node->right) {
                    printTreeHelper(node->right, indent, true);
                } else if (node->left) {
                    cout << indent << "+-nullptr" << endl;
                }
            }
        }
    }
    
public:
    // 构造函数
    AugmentedRedBlackTree() { 
        root = nullptr; 
    }
    
    // 插入新节点
    void insert(const int &data) {
        cout << "========================================" << endl;
        cout << "插入节点: " << data << endl;
        cout << "========================================" << endl;
        
        Node *node = new Node(data);
        cout << "创建新节点 " << data << "，颜色为红色，初始size为1" << endl;
        
        // 执行正常的BST插入
        cout << "执行BST插入过程:" << endl;
        root = bstInsert(root, node);
        
        // 更新从插入节点到根节点路径上所有节点的size
        cout << "更新节点size:" << endl;
        updateSizeToRoot(node);
        
        // 修复可能违反的红黑树性质
        cout << "修复红黑树性质:" << endl;
        fixInsertViolation(node);
        
        cout << "最终树结构:" << endl;
        printTree();
        cout << "\n" << endl;
    }
    
    // BST插入的辅助函数
    Node* bstInsert(Node *root, Node *node) {
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
        
        // 返回未改变的节点指针
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
        cout << node->data << "(" << (node->color == RED ? "R" : "B") << ",size=" << node->size << ") ";
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
            
            cout << current->data << "(" << (current->color == RED ? "R" : "B") << ",size=" << current->size << ") ";
            
            if (current->left != nullptr)
                q.push(current->left);
                
            if (current->right != nullptr)
                q.push(current->right);
        }
        cout << endl;
    }
    
    // 打印树结构
    void printTree() {
        if (root == nullptr) {
            cout << "空树" << endl;
            return;
        }
        
        cout << "树结构图:" << endl;
        printTreeHelper(root, "", true);
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
    
    // 查找第k小的元素（顺序统计）
    int select(int k) {
        cout << "查找第 " << k << " 小的元素:" << endl;
        if (root == nullptr || k <= 0 || k > root->size) {
            cout << "  无效的秩 k=" << k << "，树的总大小为 " << (root ? root->size : 0) << endl;
            throw invalid_argument("Invalid rank k");
        }
        int result = selectHelper(root, k);
        cout << "  第 " << k << " 小的元素是: " << result << endl;
        return result;
    }
    
    // 查找第k小元素的辅助函数
    int selectHelper(Node *node, int k) {
        if (node == nullptr) {
            throw invalid_argument("Node is null");
        }
        
        int leftSize = (node->left != nullptr) ? node->left->size : 0;
        cout << "  当前节点: " << node->data << ", 左子树大小: " << leftSize << ", 查找第 " << k << " 小" << endl;
        
        if (k == leftSize + 1) {
            cout << "  找到目标节点: " << node->data << endl;
            return node->data;
        } else if (k <= leftSize) {
            cout << "  目标在左子树中" << endl;
            return selectHelper(node->left, k);
        } else {
            cout << "  目标在右子树中" << endl;
            return selectHelper(node->right, k - leftSize - 1);
        }
    }
    
    // 确定元素的秩（元素在排序顺序中的位置）
    int rank(int data) {
        cout << "计算元素 " << data << " 的秩:" << endl;
        int result = rankHelper(root, data);
        cout << "  元素 " << data << " 的秩为: " << result << endl;
        return result;
    }
    
    // 确定元素秩的辅助函数
    int rankHelper(Node *node, int data) {
        if (node == nullptr) {
            cout << "  到达空节点，返回0" << endl;
            return 0;
        }
        
        cout << "  当前节点: " << node->data << ", size=" << node->size << endl;
        
        if (data < node->data) {
            cout << "  目标值 " << data << " 小于当前节点 " << node->data << "，在左子树中查找" << endl;
            return rankHelper(node->left, data);
        } else if (data > node->data) {
            int leftSize = (node->left != nullptr) ? node->left->size : 0;
            cout << "  目标值 " << data << " 大于当前节点 " << node->data << "，在右子树中查找" << endl;
            cout << "  左子树大小: " << leftSize << "，返回 1+" << leftSize << "+右子树中的秩" << endl;
            return 1 + leftSize + rankHelper(node->right, data);
        } else {
            int leftSize = (node->left != nullptr) ? node->left->size : 0;
            cout << "  找到目标节点 " << data << "，其秩为 1+" << leftSize << "=" << (1 + leftSize) << endl;
            return 1 + leftSize;
        }
    }
};

int main() {
#ifdef ACM_LOCAL
    freopen("data.in", "r", stdin);
    freopen("data.out", "w", stdout);
#endif
    AugmentedRedBlackTree tree;
    
    cout << "##################################################" << endl;
    cout << "#                                                #" << endl;
    cout << "#     扩张红黑树示例程序 - 支持顺序统计操作       #" << endl;
    cout << "#                                                #" << endl;
    cout << "##################################################\n" << endl;
    
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
    
    cout << "==================================================" << endl;
    cout << "所有插入操作完成" << endl;
    cout << "==================================================\n" << endl;
    
    tree.inorder();
    tree.levelOrder();
    tree.printTree();
    
    cout << "\n顺序统计操作演示:\n";
    try {
        tree.select(1);
        tree.select(3);
        tree.select(5);
        tree.select(7);
    } catch (const exception& e) {
        cout << "异常: " << e.what() << endl;
    }
    
    cout << "\n秩操作演示:\n";
    tree.rank(1);
    tree.rank(10);
    tree.rank(15);
    tree.rank(30);
    
    cout << "\n搜索测试:\n";
    tree.search(15);
    tree.search(100);
    
    return 0;
}