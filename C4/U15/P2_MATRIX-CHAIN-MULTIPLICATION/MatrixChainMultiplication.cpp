#include <iostream>
#include <vector>
#include <climits>
#include <iomanip>

using namespace std;

// 矩阵链乘法问题 - 计算最小标量乘法次数
int matrixChainOrder(const vector<int>& dimensions, vector<vector<int>>& splitPoints) {
    int n = dimensions.size() - 1; // 矩阵数量
    
    // 创建DP表，m[i][j]表示计算矩阵Ai...Aj所需的最小标量乘法次数
    vector<vector<int>> m(n, vector<int>(n, 0));
    
    // L是链的长度
    for (int L = 2; L <= n; L++) {
        for (int i = 0; i < n - L + 1; i++) {
            int j = i + L - 1;
            m[i][j] = INT_MAX;
            
            // 尝试所有可能的分割点k
            for (int k = i; k < j; k++) {
                // 计算标量乘法次数
                int cost = m[i][k] + m[k + 1][j] + dimensions[i] * dimensions[k + 1] * dimensions[j + 1];
                
                if (cost < m[i][j]) {
                    m[i][j] = cost;
                    splitPoints[i][j] = k; // 记录最优分割点
                }
            }
        }
    }
    
    return m[0][n - 1];
}

// 打印最优括号化方案
void printOptimalParentheses(const vector<vector<int>>& splitPoints, int i, int j) {
    if (i == j) {
        cout << "A" << i + 1;
    } else {
        cout << "(";
        printOptimalParentheses(splitPoints, i, splitPoints[i][j]);
        cout << " × ";
        printOptimalParentheses(splitPoints, splitPoints[i][j] + 1, j);
        cout << ")";
    }
}

// 打印DP表
void printDPTable(const vector<vector<int>>& m, int n) {
    cout << "\nDP表 (m[i][j]表示矩阵Ai到Aj的最小标量乘法次数):\n";
    cout << "行列索引从0开始\n";
    cout << "   ";
    for (int j = 0; j < n; j++) {
        cout << setw(8) << "A" + to_string(j + 1);
    }
    cout << "\n";
    
    for (int i = 0; i < n; i++) {
        cout << "A" << i + 1 << " ";
        for (int j = 0; j < n; j++) {
            if (j < i) {
                cout << setw(8) << "-";
            } else {
                cout << setw(8) << m[i][j];
            }
        }
        cout << "\n";
    }
}

// 打印分割点表
void printSplitPoints(const vector<vector<int>>& splitPoints, int n) {
    cout << "\n分割点表 (splitPoints[i][j]表示矩阵Ai到Aj的最优分割点):\n";
    cout << "行列索引从0开始\n";
    cout << "   ";
    for (int j = 0; j < n; j++) {
        cout << setw(8) << "A" + to_string(j + 1);
    }
    cout << "\n";
    
    for (int i = 0; i < n; i++) {
        cout << "A" << i + 1 << " ";
        for (int j = 0; j < n; j++) {
            if (j <= i) {
                cout << setw(8) << "-";
            } else {
                cout << setw(8) << "k=" + to_string(splitPoints[i][j] + 1);
            }
        }
        cout << "\n";
    }
}

int main() {
#ifdef ACM_LOCAL
    freopen("data.in", "r", stdin);
    freopen("data.out", "w", stdout);
#endif
    cout << "=== 矩阵链乘法问题演示 ===\n" << endl;
    
    // 示例：矩阵维度序列 <30, 35, 15, 5, 10, 20, 25>
    // 表示5个矩阵: A1(30×35), A2(35×15), A3(15×5), A4(5×10), A5(10×20), A6(20×25)
    vector<int> dimensions = {30, 35, 15, 5, 10, 20, 25};
    int n = dimensions.size() - 1;
    
    cout << "矩阵维度序列: <";
    for (int i = 0; i < dimensions.size(); i++) {
        cout << dimensions[i];
        if (i < dimensions.size() - 1) cout << ", ";
    }
    cout << ">" << endl;
    
    cout << "\n对应的矩阵:" << endl;
    for (int i = 0; i < n; i++) {
        cout << "A" << (i + 1) << ": " << dimensions[i] << "×" << dimensions[i + 1] << endl;
    }
    
    // 创建分割点表
    vector<vector<int>> splitPoints(n, vector<int>(n, 0));
    
    // 计算最小标量乘法次数
    int minCost = matrixChainOrder(dimensions, splitPoints);
    
    cout << "\n最小标量乘法次数: " << minCost << endl;
    
    // 创建DP表用于显示
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
    cout << "\n最优括号化方案: ";
    printOptimalParentheses(splitPoints, 0, n - 1);
    cout << endl;
    
    return 0;
}