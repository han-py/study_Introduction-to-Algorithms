//
// Created by HaPpY on 2025/12/5.
//

#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <numeric>

/**
 * @brief 雇佣问题模拟
 * 
 * 根据《算法导论》第五章5.1节的雇佣问题，模拟雇佣过程
 * 假设要雇佣一名新的办公助理，雇佣代理每天推荐一个应聘者
 * 需要面试每个应聘者，如果应聘者比当前办公助理更优秀，则雇佣他
 */

class HiringProblem {
private:
    int interviewCost;      // 面试费用
    int hiringCost;         // 雇佣费用
    int totalCost;          // 总费用
    int hiredCount;         // 雇佣次数
    int currentBest;        // 当前最佳应聘者的能力值

public:
    /**
     * @brief 构造函数
     * @param interviewCost 面试费用
     * @param hiringCost 雇佣费用
     */
    HiringProblem(int interviewCost = 1, int hiringCost = 10) 
        : interviewCost(interviewCost), hiringCost(hiringCost), 
          totalCost(0), hiredCount(0), currentBest(0) {}

    /**
     * @brief 重置状态
     */
    void reset() {
        totalCost = 0;
        hiredCount = 0;
        currentBest = 0;
    }

    /**
     * @brief 处理单个应聘者
     * @param candidateQuality 应聘者能力值
     */
    void processCandidate(int candidateQuality) {
        // 面试费用
        totalCost += interviewCost;
        
        // 如果应聘者比当前最佳更优秀，则雇佣
        if (candidateQuality > currentBest) {
            currentBest = candidateQuality;
            hiredCount++;
            totalCost += hiringCost;
        }
    }

    /**
     * @brief 获取总费用
     * @return 总费用
     */
    int getTotalCost() const {
        return totalCost;
    }

    /**
     * @brief 获取雇佣次数
     * @return 雇佣次数
     */
    int getHiredCount() const {
        return hiredCount;
    }
};

/**
 * @brief 随机打乱应聘者顺序
 * @param candidates 应聘者能力值向量
 */
void shuffleCandidates(std::vector<int>& candidates) {
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(candidates.begin(), candidates.end(), g);
}

/**
 * @brief 模拟雇佣过程（随机顺序）
 * @param n 应聘者数量
 * @return 总费用
 */
int simulateHiring(int n) {
    // 创建应聘者能力值（1到n，数值越大越优秀）
    std::vector<int> candidates(n);
    std::iota(candidates.begin(), candidates.end(), 1);
    
    // 随机打乱顺序
    shuffleCandidates(candidates);
    
    // 初始化雇佣问题
    HiringProblem hiring(1, 10);  // 面试费用1，雇佣费用10
    
    // 处理每个应聘者
    for (int i = 0; i < n; i++) {
        hiring.processCandidate(candidates[i]);
    }
    
    return hiring.getTotalCost();
}

/**
 * @brief 最坏情况：应聘者按能力递增顺序出现
 * @param n 应聘者数量
 * @return 总费用
 */
int worstCaseHiring(int n) {
    HiringProblem hiring(1, 10);
    
    // 按能力值递增顺序处理应聘者
    for (int i = 1; i <= n; i++) {
        hiring.processCandidate(i);
    }
    
    return hiring.getTotalCost();
}

/**
 * @brief 最好情况：最佳应聘者首先出现
 * @param n 应聘者数量
 * @return 总费用
 */
int bestCaseHiring(int n) {
    HiringProblem hiring(1, 10);
    
    // 最佳应聘者首先出现
    hiring.processCandidate(n);
    
    // 其余应聘者能力值较小
    for (int i = 1; i < n; i++) {
        hiring.processCandidate(i);
    }
    
    return hiring.getTotalCost();
}

/**
 * @brief 多次模拟并计算平均费用
 * @param n 应聘者数量
 * @param simulations 模拟次数
 * @return 平均费用
 */
double averageCostSimulation(int n, int simulations = 1000) {
    long long totalCost = 0;
    
    for (int i = 0; i < simulations; i++) {
        totalCost += simulateHiring(n);
    }
    
    return static_cast<double>(totalCost) / simulations;
}

/**
 * @brief 主函数：演示雇佣问题的不同情况
 */
int main() {
#ifdef ACM_LOCAL
    freopen("data.in", "r", stdin);
    freopen("data.out", "w", stdout);
#endif
    const int n = 10;  // 应聘者数量
    const int simulations = 1000;  // 模拟次数
    
    std::cout << "=== 雇佣问题模拟 ===" << std::endl;
    std::cout << "应聘者数量: " << n << std::endl;
    std::cout << "面试费用: 1, 雇佣费用: 10" << std::endl;
    std::cout << std::endl;
    
    // 最坏情况
    int worstCost = worstCaseHiring(n);
    std::cout << "最坏情况费用 (所有应聘者按能力递增顺序出现): " << worstCost << std::endl;
    
    // 最好情况
    int bestCost = bestCaseHiring(n);
    std::cout << "最好情况费用 (最佳应聘者首先出现): " << bestCost << std::endl;
    
    // 平均情况（多次模拟）
    double avgCost = averageCostSimulation(n, simulations);
    std::cout << "平均情况费用 (" << simulations << "次模拟): " << avgCost << std::endl;
    
    // 数学期望
    double expectedHirings = 0;
    for (int i = 1; i <= n; i++) {
        expectedHirings += 1.0 / i;
    }
    double expectedCost = n * 1 + expectedHirings * 10;  // n次面试 + 期望雇佣次数*雇佣费用
    std::cout << "数学期望费用: " << expectedCost << std::endl;
    
    return 0;
}