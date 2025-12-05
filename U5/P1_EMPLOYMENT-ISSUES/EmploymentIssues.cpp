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
    bool verbose;           // 是否显示详细过程

public:
    /**
     * @brief 构造函数
     * @param interviewCost 面试费用
     * @param hiringCost 雇佣费用
     * @param verbose 是否显示详细过程
     */
    HiringProblem(int interviewCost = 1, int hiringCost = 10, bool verbose = false) 
        : interviewCost(interviewCost), hiringCost(hiringCost), 
          totalCost(0), hiredCount(0), currentBest(0), verbose(verbose) {}

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
     * @param candidateIndex 应聘者索引
     * @param candidateQuality 应聘者能力值
     */
    void processCandidate(int candidateIndex, int candidateQuality) {
        // 面试费用
        totalCost += interviewCost;
        
        if (verbose) {
            std::cout << "面试应聘者 #" << candidateIndex 
                      << " (能力值: " << candidateQuality << ")";
        }
        
        // 如果应聘者比当前最佳更优秀，则雇佣
        if (candidateQuality > currentBest) {
            currentBest = candidateQuality;
            hiredCount++;
            totalCost += hiringCost;
            
            if (verbose) {
                std::cout << " => 雇佣! (当前最佳: " << currentBest 
                          << ", 已雇佣: " << hiredCount << "次, 总费用: " << totalCost << ")";
            }
        } else {
            if (verbose) {
                std::cout << " => 不雇佣 (当前最佳: " << currentBest << ")";
            }
        }
        
        if (verbose) {
            std::cout << std::endl;
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
    
    /**
     * @brief 获取当前最佳能力值
     * @return 当前最佳能力值
     */
    int getCurrentBest() const {
        return currentBest;
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
 * @param verbose 是否显示详细过程
 * @return 总费用
 */
int simulateHiring(int n, bool verbose = false) {
    // 创建应聘者能力值（1到n，数值越大越优秀）
    std::vector<int> candidates(n);
    std::iota(candidates.begin(), candidates.end(), 1);
    
    // 随机打乱顺序
    shuffleCandidates(candidates);
    
    if (verbose) {
        std::cout << "应聘者能力值顺序: ";
        for (int i = 0; i < n; i++) {
            std::cout << candidates[i] << " ";
        }
        std::cout << std::endl << std::endl;
        
        std::cout << "面试过程详情:" << std::endl;
        std::cout << "----------------------------------------" << std::endl;
    }
    
    // 初始化雇佣问题
    HiringProblem hiring(1, 10, verbose);  // 面试费用1，雇佣费用10
    
    // 处理每个应聘者
    for (int i = 0; i < n; i++) {
        hiring.processCandidate(i+1, candidates[i]);
    }
    
    if (verbose) {
        std::cout << "----------------------------------------" << std::endl;
    }
    
    return hiring.getTotalCost();
}

/**
 * @brief 最坏情况：应聘者按能力递增顺序出现
 * @param n 应聘者数量
 * @param verbose 是否显示详细过程
 * @return 总费用
 */
int worstCaseHiring(int n, bool verbose = false) {
    HiringProblem hiring(1, 10, verbose);
    
    if (verbose) {
        std::cout << "最坏情况: 应聘者按能力值递增顺序出现" << std::endl;
        std::cout << "应聘者能力值顺序: ";
        for (int i = 1; i <= n; i++) {
            std::cout << i << " ";
        }
        std::cout << std::endl << std::endl;
        
        std::cout << "面试过程详情:" << std::endl;
        std::cout << "----------------------------------------" << std::endl;
    }
    
    // 按能力值递增顺序处理应聘者
    for (int i = 1; i <= n; i++) {
        hiring.processCandidate(i, i);
    }
    
    if (verbose) {
        std::cout << "----------------------------------------" << std::endl;
    }
    
    return hiring.getTotalCost();
}

/**
 * @brief 最好情况：最佳应聘者首先出现
 * @param n 应聘者数量
 * @param verbose 是否显示详细过程
 * @return 总费用
 */
int bestCaseHiring(int n, bool verbose = false) {
    HiringProblem hiring(1, 10, verbose);
    
    if (verbose) {
        std::cout << "最好情况: 最佳应聘者首先出现" << std::endl;
        std::cout << "应聘者能力值顺序: " << n << " ";
        for (int i = 1; i < n; i++) {
            std::cout << i << " ";
        }
        std::cout << std::endl << std::endl;
        
        std::cout << "面试过程详情:" << std::endl;
        std::cout << "----------------------------------------" << std::endl;
    }
    
    // 最佳应聘者首先出现
    hiring.processCandidate(1, n);
    
    // 其余应聘者能力值较小
    for (int i = 1; i < n; i++) {
        hiring.processCandidate(i+1, i);
    }
    
    if (verbose) {
        std::cout << "----------------------------------------" << std::endl;
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
    long long totalHires = 0;
    
    for (int i = 0; i < simulations; i++) {
        // 创建应聘者能力值（1到n，数值越大越优秀）
        std::vector<int> candidates(n);
        std::iota(candidates.begin(), candidates.end(), 1);
        
        // 随机打乱顺序
        shuffleCandidates(candidates);
        
        // 初始化雇佣问题（不显示详细过程）
        HiringProblem hiring(1, 10, false);
        
        // 处理每个应聘者
        for (int j = 0; j < n; j++) {
            hiring.processCandidate(j+1, candidates[j]);
        }
        
        totalCost += hiring.getTotalCost();
        totalHires += hiring.getHiredCount();
    }
    
    std::cout << "   在" << simulations << "次模拟中:" << std::endl;
    std::cout << "   - 总面试费用: " << totalCost - totalHires * 10 << std::endl;
    std::cout << "   - 总雇佣费用: " << totalHires * 10 << std::endl;
    std::cout << "   - 总费用: " << totalCost << std::endl;
    std::cout << "   - 平均雇佣次数: " << static_cast<double>(totalHires) / simulations << std::endl;
    
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
    const int simulations = 10000;  // 模拟次数
    
    std::cout << "=== 雇佣问题模拟 ===" << std::endl;
    std::cout << "应聘者数量: " << n << std::endl;
    std::cout << "面试费用: 1, 雇佣费用: 10" << std::endl;
    std::cout << std::endl;
    
    // 最坏情况（详细输出）
    std::cout << "【最坏情况】" << std::endl;
    int worstCost = worstCaseHiring(n, true);
    std::cout << "最坏情况费用 (所有应聘者按能力递增顺序出现): " << worstCost << std::endl;
    std::cout << std::endl;
    
    // 最好情况（详细输出）
    std::cout << "【最好情况】" << std::endl;
    int bestCost = bestCaseHiring(n, true);
    std::cout << "最好情况费用 (最佳应聘者首先出现): " << bestCost << std::endl;
    std::cout << std::endl;
    
    // 随机情况示例（详细输出）
    std::cout << "【随机情况示例】" << std::endl;
    int randomCost = simulateHiring(n, true);
    std::cout << "随机情况费用示例: " << randomCost << std::endl;
    std::cout << std::endl;
    
    // 平均情况（多次模拟）
    std::cout << "【平均情况】" << std::endl;
    std::cout << "平均情况费用 (" << simulations << "次模拟): " << std::endl;
    double avgCost = averageCostSimulation(n, simulations);
    std::cout << "平均费用: " << avgCost << std::endl;
    std::cout << std::endl;
    
    // 数学期望
    std::cout << "【数学期望】" << std::endl;
    double expectedHirings = 0;
    for (int i = 1; i <= n; i++) {
        expectedHirings += 1.0 / i;
    }
    double expectedCost = n * 1 + expectedHirings * 10;  // n次面试 + 期望雇佣次数*雇佣费用
    std::cout << "期望雇佣次数: " << expectedHirings << std::endl;
    std::cout << "数学期望费用: " << expectedCost << std::endl;
    std::cout << "(面试费用: " << n << ", 雇佣费用: " << expectedHirings * 10 << ")" << std::endl;
    
    return 0;
}