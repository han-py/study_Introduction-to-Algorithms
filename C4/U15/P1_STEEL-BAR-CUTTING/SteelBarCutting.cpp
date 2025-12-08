#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <chrono>

using namespace std;
using namespace std::chrono;

// 钢条切割问题 - 自顶向下递归实现（朴素递归）
int cutRodRecursive(const vector<int>& prices, int n) {
    // 基本情况
    if (n <= 0) return 0;
    
    int maxValue = INT_MIN;
    
    // 尝试所有可能的切割方式
    for (int i = 0; i < n; i++) {
        maxValue = max(maxValue, prices[i] + cutRodRecursive(prices, n - i - 1));
    }
    
    return maxValue;
}

// 钢条切割问题 - 自顶向下递归实现（带备忘录）
int cutRodMemoized(const vector<int>& prices, int n, vector<int>& memo) {
    // 基本情况
    if (n <= 0) return 0;
    
    // 如果已经计算过，直接返回结果
    if (memo[n] != -1) return memo[n];
    
    int maxValue = INT_MIN;
    
    // 尝试所有可能的切割方式
    for (int i = 0; i < n; i++) {
        maxValue = max(maxValue, prices[i] + cutRodMemoized(prices, n - i - 1, memo));
    }
    
    // 存储结果
    memo[n] = maxValue;
    return maxValue;
}

// 钢条切割问题 - 自底向上动态规划实现
int cutRodBottomUp(const vector<int>& prices, int n) {
    // 创建dp数组，dp[i]表示长度为i的钢条能获得的最大收益
    vector<int> dp(n + 1, 0);
    
    // 自底向上计算
    for (int i = 1; i <= n; i++) {
        int maxValue = INT_MIN;
        // 尝试所有可能的切割方式
        for (int j = 0; j < i; j++) {
            maxValue = max(maxValue, prices[j] + dp[i - j - 1]);
        }
        dp[i] = maxValue;
    }
    
    return dp[n];
}

// 钢条切割问题 - 自底向上动态规划实现（带方案记录）
pair<int, vector<int>> cutRodBottomUpWithSolution(const vector<int>& prices, int n) {
    // 创建dp数组和解决方案数组
    vector<int> dp(n + 1, 0);
    vector<int> solution(n + 1, 0);
    
    // 自底向上计算
    for (int i = 1; i <= n; i++) {
        int maxValue = INT_MIN;
        int bestCut = 0;
        // 尝试所有可能的切割方式
        for (int j = 0; j < i; j++) {
            if (prices[j] + dp[i - j - 1] > maxValue) {
                maxValue = prices[j] + dp[i - j - 1];
                bestCut = j + 1;  // 记录最优切割点
            }
        }
        dp[i] = maxValue;
        solution[i] = bestCut;
    }
    
    // 重构解决方案
    vector<int> cuts;
    int remainingLength = n;
    while (remainingLength > 0) {
        cuts.push_back(solution[remainingLength]);
        remainingLength -= solution[remainingLength];
    }
    
    return make_pair(dp[n], cuts);
}

// 打印切割方案
void printSolution(const vector<int>& cuts) {
    cout << "最佳切割方案: ";
    for (size_t i = 0; i < cuts.size(); i++) {
        cout << cuts[i];
        if (i < cuts.size() - 1) cout << " + ";
    }
    cout << endl;
}

// 性能测试函数
void performanceTest(const vector<int>& prices, int maxSize) {
    cout << "\n性能测试 (单位: 微秒):\n";
    cout << "长度\t朴素递归\t备忘递归\t动态规划\n";
    
    for (int i = 1; i <= min(maxSize, 20); i++) {  // 限制朴素递归的测试范围
        cout << i << "\t";
        
        // 测试朴素递归（只测试较小的值）
        if (i <= 15) {
            auto start = high_resolution_clock::now();
            cutRodRecursive(prices, i);
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(stop - start);
            cout << duration.count() << "\t\t";
        } else {
            cout << "超时\t\t";
        }
        
        // 测试备忘递归
        {
            vector<int> memo(i + 1, -1);
            auto start = high_resolution_clock::now();
            cutRodMemoized(prices, i, memo);
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(stop - start);
            cout << duration.count() << "\t\t";
        }
        
        // 测试动态规划
        {
            auto start = high_resolution_clock::now();
            cutRodBottomUp(prices, i);
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(stop - start);
            cout << duration.count() << endl;
        }
    }
}

int main() {
#ifdef ACM_LOCAL
    freopen("data.in", "r", stdin);
    freopen("data.out", "w", stdout);
#endif
    // 钢条价格表（长度1-10对应的价格）
    vector<int> prices = {1, 5, 8, 9, 10, 17, 17, 20, 24, 30};
    
    cout << "钢条切割问题演示\n";
    cout << "================\n\n";
    
    cout << "钢条价格表:\n";
    cout << "长度: ";
    for (int i = 1; i <= 10; i++) {
        cout << i << "\t";
    }
    cout << "\n价格: ";
    for (size_t i = 0; i < prices.size(); i++) {
        cout << prices[i] << "\t";
    }
    cout << "\n\n";
    
    // 测试不同长度的钢条
    for (int length = 1; length <= 10; length++) {
        cout << "长度为 " << length << " 的钢条:\n";
        
        // 自底向上动态规划（带方案）
        auto result = cutRodBottomUpWithSolution(prices, length);
        cout << "  最大收益: " << result.first << endl;
        cout << "  ";
        printSolution(result.second);
        cout << endl;
    }
    
    // 性能测试
    performanceTest(prices, 25);
    
    return 0;
}