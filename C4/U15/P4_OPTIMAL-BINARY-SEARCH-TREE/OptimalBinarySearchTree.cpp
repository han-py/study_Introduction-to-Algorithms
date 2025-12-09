#include <iostream>
#include <vector>
#include <limits>
#include <iomanip>
#include <algorithm>
#include <string>

using namespace std;

/**
 * 最优二叉搜索树（Optimal Binary Search Tree）问题
 * 
 * 根据《算法导论》第15章动态规划内容实现
 * 
 * 问题定义：
 * 给定n个关键字K = <k1, k2, ..., kn>（已排序：k1 < k2 < ... < kn），
 * 对于每个关键字ki，有一次搜索概率pi；对于1 ≤ i ≤ n+1，还有n+1个"伪关键字"
 * d0, d1, d2, ..., dn表示不在K中的查找值，di表示在ki和k(i+1)之间的值，
 * 每个伪关键字di有搜索概率qi。
 * 
 * 目标：构造一棵二叉搜索树，使得搜索期望代价最小。
 * 
 * 算法思路：
 * 使用动态规划方法解决
 * 1. 对于子数组ki, k(i+1), ..., kj，计算构造最优二叉搜索树的期望搜索代价
 * 2. 通过枚举根节点kr（i ≤ r ≤ j）将问题分解为左右子树的子问题
 * 3. 选择使总代价最小的根节点
 * 
 * 时间复杂度：O(n³)
 * 空间复杂度：O(n²)
 */

/**
 * 打印最优二叉搜索树结构
 * @param root 根节点表
 * @param keys 关键字数组
 * @param i 起始索引
 * @param j 结束索引
 * @param s 缩进字符串，用于显示树的层级结构
 */
void printOptimalBST(const vector<vector<int>>& root, const vector<string>& keys, 
                     int i, int j, const string& s = "") {
    if (i > j) {
        cout << s << "null" << endl;
        return;
    }
    
    int r = root[i][j];
    cout << s << keys[r-1] << endl;
    
    // 修正边界条件检查
    if (r-1 >= i) {
        cout << s << "├─左子树: " << endl;
        printOptimalBST(root, keys, i, r-1, s + "│ ");
    }
    
    if (r+1 <= j) {
        cout << s << "└─右子树: " << endl;
        printOptimalBST(root, keys, r+1, j, s + "  ");
    }
}

/**
 * 构造最优二叉搜索树
 * @param p 成功搜索概率数组（p[1..n]）
 * @param q 失败搜索概率数组（q[0..n]）
 * @param keys 关键字数组
 * @param n 关键字数量
 * @param root 用于记录根节点的二维数组
 * @return 最优二叉搜索树的期望搜索代价
 */
double optimalBST(const vector<double>& p, const vector<double>& q, 
                  const vector<string>& keys, int n, vector<vector<int>>& root) {
    // 创建e表存储子树的期望搜索代价
    vector<vector<double>> e(n+2, vector<double>(n+1, 0.0));
    
    // 创建w表存储概率之和
    vector<vector<double>> w(n+2, vector<double>(n+1, 0.0));
    
    // 初始化root表
    root.assign(n+2, vector<int>(n+1, 0));
    
    cout << "开始计算最优二叉搜索树..." << endl;
    cout << "关键字数量: " << n << endl;
    
    // 初始化边界条件：只包含伪关键字di的子树
    for (int i = 1; i <= n+1; i++) {
        e[i][i-1] = q[i-1];
        w[i][i-1] = q[i-1];
        cout << "  初始化e[" << i << "][" << (i-1) << "] = " << e[i][i-1] 
             << " (只有伪关键字d" << (i-1) << ")" << endl;
    }
    
    // 按照子问题规模（关键字数量）从小到大计算
    for (int len = 1; len <= n; len++) {
        cout << "\n--- 计算包含 " << len << " 个关键字的子树 ---" << endl;
        
        for (int i = 1; i <= n-len+1; i++) {
            int j = i + len - 1;
            e[i][j] = numeric_limits<double>::max();
            w[i][j] = w[i][j-1] + p[j] + q[j];
            
            cout << "  计算子树T[" << i << "," << j << "] (关键字: ";
            for (int t = i; t <= j; t++) {
                cout << keys[t-1];
                if (t < j) cout << ",";
            }
            cout << "; 概率和: " << fixed << setprecision(3) << w[i][j] << ")" << endl;
            
            // 尝试每个可能的根节点
            for (int r = i; r <= j; r++) {
                double t = e[i][r-1] + e[r+1][j] + w[i][j];
                
                cout << "    尝试以 " << keys[r-1] << " 为根: 左子树代价=" << e[i][r-1] 
                     << ", 右子树代价=" << e[r+1][j] << ", 子树概率和=" << w[i][j] 
                     << ", 总代价=" << t << endl;
                
                if (t < e[i][j]) {
                    e[i][j] = t;
                    root[i][j] = r;
                    cout << "    找到更优解: 最小代价更新为 " << e[i][j] 
                         << ", 最优根节点为 " << keys[r-1] << endl;
                }
            }
        }
    }
    
    return e[1][n];
}

/**
 * 打印期望搜索代价表
 * @param e 期望搜索代价表
 * @param n 关键字数量
 */
void printExpectedCostTable(const vector<vector<double>>& e, int n) {
    cout << "\n==================== 期望搜索代价表 ====================" << endl;
    cout << "e[i][j] 表示包含关键字ki到kj的子树的最小期望搜索代价" << endl;
    
    cout << "     ";
    for (int j = 0; j <= n; j++) {
        cout << setw(10) << "j=" + to_string(j);
    }
    cout << "\n";
    
    for (int i = 1; i <= n+1; i++) {
        cout << "i=" << setw(2) << i << " ";
        for (int j = 0; j <= n; j++) {
            if (j < i-1) {
                cout << setw(10) << "-";
            } else {
                cout << setw(10) << fixed << setprecision(3) << e[i][j];
            }
        }
        cout << "\n";
    }
    cout << "=====================================================" << endl;
}

/**
 * 打印根节点表
 * @param root 根节点表
 * @param n 关键字数量
 * @param keys 关键字数组
 */
void printRootTable(const vector<vector<int>>& root, int n, const vector<string>& keys) {
    cout << "\n====================== 根节点表 ======================" << endl;
    cout << "root[i][j] 表示包含关键字ki到kj的最优子树的根节点" << endl;
    
    cout << "     ";
    for (int j = 1; j <= n; j++) {
        cout << setw(10) << "j=" + to_string(j);
    }
    cout << "\n";
    
    for (int i = 1; i <= n; i++) {
        cout << "i=" << setw(2) << i << " ";
        for (int j = 1; j <= n; j++) {
            if (j < i) {
                cout << setw(10) << "-";
            } else {
                if (root[i][j] > 0) {
                    cout << setw(10) << keys[root[i][j]-1];
                } else {
                    cout << setw(10) << "-";
                }
            }
        }
        cout << "\n";
    }
    cout << "=====================================================" << endl;
}

/**
 * 主函数 - 演示最优二叉搜索树算法
 */
int main() {
#ifdef ACM_LOCAL
    freopen("data.in", "r", stdin);
    freopen("data.out", "w", stdout);
#endif
    
    cout << "========================================================" << endl;
    cout << "           最优二叉搜索树（OBST）演示程序" << endl;
    cout << "========================================================" << endl;
    cout << "问题描述：" << endl;
    cout << "给定关键字及其搜索概率，构造期望搜索代价最小的二叉搜索树" << endl;
    cout << "========================================================\n" << endl;
    
    // 示例：《算法导论》图15-9中的例子
    vector<string> keys = {"k1", "k2", "k3", "k4", "k5"};
    vector<double> p = {0, 0.15, 0.10, 0.05, 0.10, 0.20};  // p[1..5]
    vector<double> q = {0.05, 0.10, 0.05, 0.05, 0.05, 0.10}; // q[0..5]
    int n = keys.size();
    
    cout << "【示例】《算法导论》图15-9" << endl;
    cout << "关键字: ";
    for (int i = 0; i < n; i++) {
        cout << keys[i] << "(概率=" << p[i+1] << ")";
        if (i < n-1) cout << ", ";
    }
    cout << endl;
    
    cout << "伪关键字(d0表示小于k1的值, d5表示大于k5的值): ";
    for (int i = 0; i <= n; i++) {
        cout << "d" << i << "(概率=" << q[i] << ")";
        if (i < n) cout << ", ";
    }
    cout << endl;
    
    vector<vector<int>> root;
    double minExpectedCost = optimalBST(p, q, keys, n, root);
    
    // 创建e表用于显示（重新计算一遍以便显示）
    vector<vector<double>> e(n+2, vector<double>(n+1, 0.0));
    vector<vector<double>> w(n+2, vector<double>(n+1, 0.0));
    
    for (int i = 1; i <= n+1; i++) {
        e[i][i-1] = q[i-1];
        w[i][i-1] = q[i-1];
    }
    
    for (int len = 1; len <= n; len++) {
        for (int i = 1; i <= n-len+1; i++) {
            int j = i + len - 1;
            e[i][j] = numeric_limits<double>::max();
            w[i][j] = w[i][j-1] + p[j] + q[j];
            
            for (int r = i; r <= j; r++) {
                double t = e[i][r-1] + e[r+1][j] + w[i][j];
                if (t < e[i][j]) {
                    e[i][j] = t;
                }
            }
        }
    }
    
    printExpectedCostTable(e, n);
    printRootTable(root, n, keys);
    
    cout << "\n最小期望搜索代价: " << fixed << setprecision(3) << minExpectedCost << endl;
    
    cout << "\n最优二叉搜索树结构:" << endl;
    printOptimalBST(root, keys, 1, n);
    
    // 示例2：简化版示例
    cout << "\n\n【示例2】简化版示例" << endl;
    vector<string> keys2 = {"A", "B", "C"};
    vector<double> p2 = {0, 0.2, 0.3, 0.5};  // p[1..3]
    vector<double> q2 = {0.1, 0.1, 0.1, 0.1}; // q[0..3]
    int n2 = keys2.size();
    
    cout << "关键字: ";
    for (int i = 0; i < n2; i++) {
        cout << keys2[i] << "(概率=" << p2[i+1] << ")";
        if (i < n2-1) cout << ", ";
    }
    cout << endl;
    
    cout << "伪关键字: ";
    for (int i = 0; i <= n2; i++) {
        cout << "d" << i << "(概率=" << q2[i] << ")";
        if (i < n2) cout << ", ";
    }
    cout << endl;
    
    vector<vector<int>> root2;
    double minExpectedCost2 = optimalBST(p2, q2, keys2, n2, root2);
    
    cout << "\n最小期望搜索代价: " << fixed << setprecision(3) << minExpectedCost2 << endl;
    
    cout << "\n最优二叉搜索树结构:" << endl;
    printOptimalBST(root2, keys2, 1, n2);
    
    cout << "\n========================================================" << endl;
    cout << "                   算法分析" << endl;
    cout << "========================================================" << endl;
    cout << "时间复杂度: O(n³)" << endl;
    cout << "空间复杂度: O(n²)" << endl;
    cout << "========================================================" << endl;
    
    return 0;
}