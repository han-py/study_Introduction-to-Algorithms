#include <iostream>
#include <vector>
#include <climits>
#include <iomanip>

using namespace std;

/**
 * 矩阵链乘法问题 - 计算最小标量乘法次数
 * 
 * 这个函数使用动态规划来解决矩阵链乘法问题。
 * 
 * 基本思路：
 * 1. 对于n个矩阵的链，我们需要决定在哪里放置括号以最小化标量乘法次数
 * 2. 我们用m[i][j]表示计算矩阵Ai到Aj的最小标量乘法次数
 * 3. 对于每个可能的分割点k，我们将链分成两部分：Ai..Ak 和 Ak+1..Aj
 * 4. 总成本 = 左半部分成本 + 右半部分成本 + 合并两部分的成本
 * 5. 合并成本是dimensions[i] * dimensions[k+1] * dimensions[j+1]
 * 
 * 参数:
 * - dimensions: 矩阵维度数组，长度为n+1
 *   如果有n个矩阵，dimensions[i-1]和dimensions[i]分别是第i个矩阵的行数和列数
 * - splitPoints: 用于记录最优分割点的二维数组
 * 
 * 返回值:
 * - 计算整个矩阵链A1到An的最小标量乘法次数
 */
int matrixChainOrder(const vector<int>& dimensions, vector<vector<int>>& splitPoints) {
    int n = dimensions.size() - 1; // 矩阵数量
    
    // 创建DP表，m[i][j]表示计算矩阵Ai...Aj所需的最小标量乘法次数
    // 初始时所有值为0，因为单个矩阵(即i==j时)不需要任何乘法运算
    vector<vector<int>> m(n, vector<int>(n, 0));
    
    cout << "开始填充DP表..." << endl;
    cout << "链长度从2开始，逐步增加到" << n << endl;
    
    // L是链的长度，从2开始（单个矩阵不需要计算）
    for (int L = 2; L <= n; L++) {
        cout << "\n--- 计算长度为 " << L << " 的矩阵链 ---" << endl;
        
        // i是链的起始矩阵索引
        for (int i = 0; i < n - L + 1; i++) {
            int j = i + L - 1; // j是链的结束矩阵索引
            m[i][j] = INT_MAX; // 初始化为无穷大
            
            cout << "  计算 m[" << i << "][" << j << "] (矩阵A" << (i+1) << "到A" << (j+1) << ")" << endl;
            
            // 尝试所有可能的分割点k
            for (int k = i; k < j; k++) {
                // 计算在k处分割的标量乘法次数
                // 左半部分：Ai到Ak，成本存储在m[i][k]
                // 右半部分：Ak+1到Aj，成本存储在m[k+1][j]
                // 合并成本：dimensions[i] * dimensions[k+1] * dimensions[j+1]
                int cost = m[i][k] + m[k + 1][j] + dimensions[i] * dimensions[k + 1] * dimensions[j + 1];
                
                cout << "    在k=" << k << "处分割: 左半部分成本=" << m[i][k] 
                     << ", 右半部分成本=" << m[k+1][j] << ", 合并成本=" 
                     << dimensions[i] << "×" << dimensions[k+1] << "×" << dimensions[j+1] 
                     << "=" << dimensions[i] * dimensions[k+1] * dimensions[j+1]
                     << ", 总成本=" << cost << endl;
                
                if (cost < m[i][j]) {
                    m[i][j] = cost;
                    splitPoints[i][j] = k; // 记录最优分割点
                    cout << "    找到更优解: 最小成本更新为 " << cost << ", 最优分割点k=" << k << endl;
                }
            }
            cout << "  最终结果: m[" << i << "][" << j << "] = " << m[i][j] 
                 << ", 最优分割点k=" << splitPoints[i][j] << endl;
        }
    }
    
    return m[0][n - 1];
}

/**
 * 打印最优括号化方案
 * 
 * 这个函数递归地打印出最优的括号化方案
 * 
 * 参数:
 * - splitPoints: 包含最优分割点信息的二维数组
 * - i: 起始矩阵索引
 * - j: 结束矩阵索引
 */
void printOptimalParentheses(const vector<vector<int>>& splitPoints, int i, int j) {
    // 基本情况：只有一个矩阵时，直接输出该矩阵名称
    if (i == j) {
        cout << "A" << i + 1;
    } else {
        // 递归情况：在最优分割点处分开，分别处理左右两部分
        cout << "(";
        // 打印左半部分的括号化方案
        printOptimalParentheses(splitPoints, i, splitPoints[i][j]);
        // 输出乘法符号
        cout << " × ";
        // 打印右半部分的括号化方案
        printOptimalParentheses(splitPoints, splitPoints[i][j] + 1, j);
        cout << ")";
    }
}

/**
 * 打印DP表
 * 显示计算每一段矩阵链所需的最小标量乘法次数
 */
void printDPTable(const vector<vector<int>>& m, int n) {
    cout << "\n========================================================" << endl;
    cout << "DP表 (m[i][j]表示矩阵Ai到Aj的最小标量乘法次数):" << endl;
    cout << "行列索引从0开始" << endl;
    cout << "========================================================" << endl;
    cout << "列j-> ";
    for (int j = 0; j < n; j++) {
        cout << setw(10) << "A" + to_string(j + 1);
    }
    cout << "\n";
    
    for (int i = 0; i < n; i++) {
        cout << "A" << i + 1 << "(i↓)";
        for (int j = 0; j < n; j++) {
            if (j < i) {
                cout << setw(10) << "-";
            } else {
                cout << setw(10) << m[i][j];
            }
        }
        cout << "\n";
    }
    cout << "========================================================" << endl;
}

/**
 * 打印分割点表
 * 显示每一段矩阵链的最优分割点
 */
void printSplitPoints(const vector<vector<int>>& splitPoints, int n) {
    cout << "\n========================================================" << endl;
    cout << "分割点表 (splitPoints[i][j]表示矩阵Ai到Aj的最优分割点):" << endl;
    cout << "行列索引从0开始" << endl;
    cout << "========================================================" << endl;
    cout << "列j-> ";
    for (int j = 0; j < n; j++) {
        cout << setw(10) << "A" + to_string(j + 1);
    }
    cout << "\n";
    
    for (int i = 0; i < n; i++) {
        cout << "A" << i + 1 << "(i↓)";
        for (int j = 0; j < n; j++) {
            if (j <= i) {
                cout << setw(10) << "-";
            } else {
                cout << setw(10) << "k=" + to_string(splitPoints[i][j] + 1);
            }
        }
        cout << "\n";
    }
    cout << "========================================================" << endl;
}

/**
 * 主函数
 * 演示矩阵链乘法问题的求解过程
 */
int main() {
#ifdef ACM_LOCAL
    freopen("data.in", "r", stdin);
    freopen("data.out", "w", stdout);
#endif
    cout << "========================================================" << endl;
    cout << "           矩阵链乘法问题演示程序" << endl;
    cout << "========================================================" << endl;
    cout << "问题描述：" << endl;
    cout << "给定一系列矩阵，如何加括号使得计算它们连乘积时" << endl;
    cout << "标量乘法次数最少？" << endl;
    cout << "========================================================\n" << endl;
    
    // 示例：矩阵维度序列 <30, 35, 15, 5, 10, 20, 25>
    // 表示6个矩阵: A1(30×35), A2(35×15), A3(15×5), A4(5×10), A5(10×20), A6(20×25)
    vector<int> dimensions = {30, 35, 15, 5, 10, 20, 25};
    int n = dimensions.size() - 1; // 矩阵数量
    
    cout << "【输入】矩阵维度序列: <";
    for (int i = 0; i < dimensions.size(); i++) {
        cout << dimensions[i];
        if (i < dimensions.size() - 1) cout << ", ";
    }
    cout << ">" << endl;
    
    cout << "\n【解释】对应的矩阵及其维度:" << endl;
    for (int i = 0; i < n; i++) {
        cout << "  A" << (i + 1) << ": " << dimensions[i] << "×" << dimensions[i + 1] << endl;
    }
    
    cout << "\n【说明】" << endl;
    cout << "这意味着我们要计算 A1 × A2 × A3 × A4 × A5 × A6" << endl;
    cout << "其中A1是30×35矩阵，A2是35×15矩阵，依此类推" << endl;
    cout << "========================================================" << endl;
    
    // 创建分割点表，用于记录每个子问题的最优分割点
    vector<vector<int>> splitPoints(n, vector<int>(n, 0));
    
    cout << "\n【第一步】使用动态规划计算最小标量乘法次数..." << endl;
    // 计算最小标量乘法次数
    int minCost = matrixChainOrder(dimensions, splitPoints);
    
    cout << "\n【第二步】结果显示" << endl;
    cout << "最小标量乘法次数: " << minCost << endl;
    
    // 创建DP表用于显示（重新计算一遍以便显示）
    vector<vector<int>> m(n, vector<int>(n, 0));
    for (int L = 2; L <= n; L++) {
        for (int i = 0; i < n - L + 1; i++) {
            int j = i + L - 1;
            m[i][j] = INT_MAX;
            for (int k = i; k < j; k++) {
                int cost = m[i][k] + m[k + 1][j] + dimensions[i] * dimensions[k + 1] * dimensions[j + 1];
                if (cost < m[i][j]) {
                    m[i][j] = cost;
                }
            }
        }
    }
    
    // 打印表格
    printDPTable(m, n);
    printSplitPoints(splitPoints, n);
    
    // 打印最优括号化方案
    cout << "\n【第三步】最优括号化方案: ";
    printOptimalParentheses(splitPoints, 0, n - 1);
    cout << endl;
    
    cout << "\n【最终解释】" << endl;
    cout << "最优计算顺序是按照上面的括号化方案进行计算" << endl;
    cout << "这样可以使得总的标量乘法次数最少，为" << minCost << "次" << endl;
    cout << "========================================================" << endl;
    
    return 0;
}