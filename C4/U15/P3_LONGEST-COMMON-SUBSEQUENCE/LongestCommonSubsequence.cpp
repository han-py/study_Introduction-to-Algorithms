#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>

using namespace std;

/**
 * 最长公共子序列（LCS）问题
 * 
 * 根据《算法导论》第15章动态规划内容实现
 * 
 * 问题定义：
 * 给定两个序列X和Y，求它们的最长公共子序列长度
 * 子序列是指在原序列中删除若干元素后得到的新序列，元素相对顺序保持不变
 * 
 * 算法思路：
 * 使用动态规划方法解决
 * 1. 创建二维DP表c[i][j]表示X[0...i-1]和Y[0...j-1]的LCS长度
 * 2. 状态转移方程：
 *    - 如果X[i-1] == Y[j-1]，则c[i][j] = c[i-1][j-1] + 1
 *    - 否则c[i][j] = max(c[i-1][j], c[i][j-1])
 * 3. 通过回溯DP表构造实际的LCS序列
 * 
 * 时间复杂度：O(m*n)
 * 空间复杂度：O(m*n)
 */

/**
 * 计算最长公共子序列的长度
 * @param X 第一个序列
 * @param Y 第二个序列
 * @param c DP表，用于存储子问题的解
 * @param b 方向表，用于记录决策路径（便于构造LCS序列）
 */
void lcsLength(const string& X, const string& Y, vector<vector<int>>& c, vector<vector<char>>& b) {
    int m = X.length();
    int n = Y.length();
    
    // 初始化DP表和方向表
    c.assign(m + 1, vector<int>(n + 1, 0));
    b.assign(m + 1, vector<char>(n + 1, '0'));
    
    cout << "开始填充DP表..." << endl;
    cout << "X序列: \"" << X << "\" (长度: " << m << ")" << endl;
    cout << "Y序列: \"" << Y << "\" (长度: " << n << ")" << endl;
    
    // 填充DP表
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            // 如果两个字符相同
            if (X[i - 1] == Y[j - 1]) {
                c[i][j] = c[i - 1][j - 1] + 1;
                b[i][j] = '\\';  // 表示从左上角转移而来
                cout << "  字符匹配: X[" << (i-1) << "]='" << X[i-1] 
                     << "' == Y[" << (j-1) << "]='" << Y[j-1] 
                     << "', c[" << i << "][" << j << "]=" << c[i][j] << endl;
            }
            // 如果两个字符不同，选择较大的值
            else if (c[i - 1][j] >= c[i][j - 1]) {
                c[i][j] = c[i - 1][j];
                b[i][j] = '|';   // 表示从上方转移而来
                cout << "  字符不匹配: 选择上方 c[" << (i-1) << "][" << j 
                     << "]=" << c[i-1][j] << " >= 左方 c[" << i << "][" << (j-1) 
                     << "]=" << c[i][j-1] << ", c[" << i << "][" << j << "]=" << c[i][j] << endl;
            }
            else {
                c[i][j] = c[i][j - 1];
                b[i][j] = '-';   // 表示从左方转移而来
                cout << "  字符不匹配: 选择左方 c[" << i << "][" << (j-1) 
                     << "]=" << c[i][j-1] << " > 上方 c[" << (i-1) << "][" << j 
                     << "]=" << c[i-1][j] << ", c[" << i << "][" << j << "]=" << c[i][j] << endl;
            }
        }
    }
}

/**
 * 通过回溯方向表构造LCS序列
 * @param X 第一个序列
 * @param Y 第二个序列
 * @param b 方向表
 * @param i 当前行索引
 * @param j 当前列索引
 * @param lcs 存储构造的LCS序列
 */
void printLCS(const string& X, const string& Y, const vector<vector<char>>& b, 
              int i, int j, string& lcs) {
    // 基本情况：到达边界
    if (i == 0 || j == 0) {
        return;
    }
    
    // 如果字符相同，该字符属于LCS
    if (b[i][j] == '\\') {
        printLCS(X, Y, b, i - 1, j - 1, lcs);
        lcs += X[i - 1];
        cout << "  添加字符 '" << X[i-1] << "' 到LCS序列" << endl;
    }
    // 否则根据方向继续回溯
    else if (b[i][j] == '|') {
        printLCS(X, Y, b, i - 1, j, lcs);
    }
    else {
        printLCS(X, Y, b, i, j - 1, lcs);
    }
}

/**
 * 打印DP表
 * @param c DP表
 * @param X 第一个序列
 * @param Y 第二个序列
 */
void printDPTable(const vector<vector<int>>& c, const string& X, const string& Y) {
    int m = X.length();
    int n = Y.length();
    
    cout << "\n==================== DP表 ====================" << endl;
    cout << "c[i][j] 表示 X[0..i-1] 和 Y[0..j-1] 的LCS长度" << endl;
    
    // 打印列标题
    cout << "    ";
    for (int j = 0; j < n; j++) {
        cout << "  " << Y[j] << " ";
    }
    cout << endl;
    
    // 打印表内容
    for (int i = 0; i <= m; i++) {
        if (i == 0) {
            cout << "  ";
        } else {
            cout << X[i-1] << " ";
        }
        
        for (int j = 0; j <= n; j++) {
            cout << setw(3) << c[i][j] << " ";
        }
        cout << endl;
    }
    cout << "=============================================" << endl;
}

/**
 * 打印方向表
 * @param b 方向表
 * @param X 第一个序列
 * @param Y 第二个序列
 */
void printDirectionTable(const vector<vector<char>>& b, const string& X, const string& Y) {
    int m = X.length();
    int n = Y.length();
    
    cout << "\n================== 方向表 ===================" << endl;
    cout << "\\ 表示字符匹配，从左上角转移" << endl;
    cout << "| 表示从上方转移" << endl;
    cout << "- 表示从左方转移" << endl;
    
    // 打印列标题
    cout << "    ";
    for (int j = 0; j < n; j++) {
        cout << "  " << Y[j] << " ";
    }
    cout << endl;
    
    // 打印表内容
    for (int i = 0; i <= m; i++) {
        if (i == 0) {
            cout << "  ";
        } else {
            cout << X[i-1] << " ";
        }
        
        for (int j = 0; j <= n; j++) {
            cout << "  " << b[i][j] << " ";
        }
        cout << endl;
    }
    cout << "=============================================" << endl;
}

/**
 * 主函数 - 演示LCS算法
 */
int main() {
#ifdef ACM_LOCAL
    freopen("data.in", "r", stdin);
    freopen("data.out", "w", stdout);
#endif
    
    cout << "========================================================" << endl;
    cout << "           最长公共子序列（LCS）演示程序" << endl;
    cout << "========================================================" << endl;
    cout << "问题描述：" << endl;
    cout << "给定两个序列，找出它们最长的公共子序列" << endl;
    cout << "子序列是指在原序列中删除若干元素后得到的新序列" << endl;
    cout << "元素相对顺序保持不变，但不要求连续" << endl;
    cout << "========================================================\n" << endl;
    
    // 示例1：经典的LCS示例
    string X1 = "ABCBDAB";
    string Y1 = "BDCABA";
    
    cout << "【示例1】经典LCS问题" << endl;
    cout << "X = \"" << X1 << "\"" << endl;
    cout << "Y = \"" << Y1 << "\"" << endl;
    
    vector<vector<int>> c1;
    vector<vector<char>> b1;
    
    lcsLength(X1, Y1, c1, b1);
    
    printDPTable(c1, X1, Y1);
    printDirectionTable(b1, X1, Y1);
    
    string lcs1 = "";
    printLCS(X1, Y1, b1, X1.length(), Y1.length(), lcs1);
    
    cout << "\n最长公共子序列长度: " << c1[X1.length()][Y1.length()] << endl;
    cout << "最长公共子序列: \"" << lcs1 << "\"" << endl;
    
    // 示例2：DNA序列比对
    cout << "\n\n【示例2】DNA序列比对" << endl;
    string X2 = "ACCGGTCGAGTGCGCGGAAGCCGGCCGAA";
    string Y2 = "GTCGTTCGGAATGCCGTTGCTCTGTAAA";
    
    cout << "X = \"" << X2 << "\"" << endl;
    cout << "Y = \"" << Y2 << "\"" << endl;
    
    vector<vector<int>> c2;
    vector<vector<char>> b2;
    
    lcsLength(X2, Y2, c2, b2);
    
    string lcs2 = "";
    printLCS(X2, Y2, b2, X2.length(), Y2.length(), lcs2);
    
    cout << "\n最长公共子序列长度: " << c2[X2.length()][Y2.length()] << endl;
    cout << "最长公共子序列: \"" << lcs2 << "\"" << endl;
    
    // 示例3：文本相似度检测
    cout << "\n\n【示例3】文本相似度检测" << endl;
    string X3 = "algorithm";
    string Y3 = "logarithm";
    
    cout << "X = \"" << X3 << "\" (算法)" << endl;
    cout << "Y = \"" << Y3 << "\" (对数)" << endl;
    
    vector<vector<int>> c3;
    vector<vector<char>> b3;
    
    lcsLength(X3, Y3, c3, b3);
    
    string lcs3 = "";
    printLCS(X3, Y3, b3, X3.length(), Y3.length(), lcs3);
    
    cout << "\n最长公共子序列长度: " << c3[X3.length()][Y3.length()] << endl;
    cout << "最长公共子序列: \"" << lcs3 << "\"" << endl;
    
    cout << "\n========================================================" << endl;
    cout << "                   算法分析" << endl;
    cout << "========================================================" << endl;
    cout << "时间复杂度: O(m×n)，其中m和n分别是两个序列的长度" << endl;
    cout << "空间复杂度: O(m×n)，用于存储DP表" << endl;
    cout << "========================================================" << endl;
    
    return 0;
}