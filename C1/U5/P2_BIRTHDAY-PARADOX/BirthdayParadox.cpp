//
// Created by HaPpY on 2025/12/5.
//

#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <cmath>
#include <iomanip>

/**
 * @brief 生日悖论问题实现
 * 
 * 根据《算法导论》第五章5.4.1节的生日悖论问题
 * 计算在k个人中至少有两人生日相同的概率
 */

class BirthdayParadox {
private:
    static const int DAYS_IN_YEAR = 365;

public:
    /**
     * @brief 精确计算生日悖论的概率（使用数学公式）
     * @param k 人数
     * @return 至少两人生日相同的概率
     */
    static double calculateProbability(int k) {
        if (k > DAYS_IN_YEAR) {
            // 根据鸽巢原理，当k > 365时，概率为1
            return 1.0;
        }
        
        if (k <= 1) {
            return 0.0;
        }
        
        // 计算所有人生日都不同的概率
        // Q = (365/365) * (364/365) * (363/365) * ... * ((365-k+1)/365)
        double probAllDifferent = 1.0;
        for (int i = 1; i < k; i++) {
            probAllDifferent *= static_cast<double>(DAYS_IN_YEAR - i) / DAYS_IN_YEAR;
        }
        
        // 至少两人生日相同的概率 = 1 - 所有人都不同的概率
        return 1.0 - probAllDifferent;
    }
    
    /**
     * @brief 通过模拟实验计算生日悖论的概率
     * @param k 人数
     * @param trials 实验次数
     * @return 至少两人生日相同的概率
     */
    static double simulateProbability(int k, int trials = 100000) {
        if (k <= 1) {
            return 0.0;
        }
        
        if (k > DAYS_IN_YEAR) {
            return 1.0;
        }
        
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(1, DAYS_IN_YEAR);
        
        int collisionCount = 0;
        
        for (int i = 0; i < trials; i++) {
            // 生成k个人的生日
            std::vector<int> birthdays(k);
            for (int j = 0; j < k; j++) {
                birthdays[j] = dis(gen);
            }
            
            // 检查是否有重复生日（通过排序后检查相邻元素）
            std::sort(birthdays.begin(), birthdays.end());
            bool hasCollision = false;
            for (int j = 1; j < k; j++) {
                if (birthdays[j] == birthdays[j-1]) {
                    hasCollision = true;
                    break;
                }
            }
            
            if (hasCollision) {
                collisionCount++;
            }
        }
        
        return static_cast<double>(collisionCount) / trials;
    }
    
    /**
     * @brief 查找使概率超过指定值的最小人数
     * @param targetProbability 目标概率
     * @return 最小人数
     */
    static int findMinPeopleForProbability(double targetProbability) {
        for (int k = 1; k <= DAYS_IN_YEAR; k++) {
            double prob = calculateProbability(k);
            if (prob >= targetProbability) {
                return k;
            }
        }
        return DAYS_IN_YEAR + 1;
    }
};

/**
 * @brief 打印不同人数下的生日悖论概率表
 */
void printProbabilityTable() {
    std::cout << "=== 生日悖论概率表 ===" << std::endl;
    std::cout << "人数\t精确概率\t模拟概率(100000次)" << std::endl;
    std::cout << "----\t--------\t-------------" << std::endl;
    
    std::vector<int> peopleCounts = {1, 5, 10, 15, 20, 23, 25, 30, 40, 50, 60, 70, 80, 90, 100};
    
    for (int k : peopleCounts) {
        double exactProb = BirthdayParadox::calculateProbability(k);
        double simulatedProb = BirthdayParadox::simulateProbability(k, 100000);
        std::cout << k << "\t" << std::fixed << std::setprecision(6) << exactProb 
                  << "\t" << simulatedProb << std::endl;
    }
}

/**
 * @brief 分析关键概率点
 */
void analyzeKeyPoints() {
    std::cout << "\n=== 关键概率点分析 ===" << std::endl;
    
    std::vector<double> targetProbs = {0.25, 0.5, 0.75, 0.9, 0.95, 0.99};
    
    for (double target : targetProbs) {
        int minPeople = BirthdayParadox::findMinPeopleForProbability(target);
        double actualProb = BirthdayParadox::calculateProbability(minPeople);
        std::cout << "概率达到 " << std::fixed << std::setprecision(2) << target 
                  << " 需要至少 " << minPeople << " 人 (实际概率: " 
                  << std::setprecision(6) << actualProb << ")" << std::endl;
    }
}

/**
 * @brief 演示数学推导过程
 */
void demonstrateMathematicalDerivation() {
    std::cout << "\n=== 数学推导过程演示 ===" << std::endl;
    std::cout << "生日悖论的数学原理：" << std::endl;
    std::cout << "1. 假设一年有365天，忽略闰年" << std::endl;
    std::cout << "2. 所有人的生日独立且均匀分布" << std::endl;
    std::cout << "3. 计算所有人都生日不同的概率，然后用1减去该概率" << std::endl;
    std::cout << std::endl;
    std::cout << "公式：" << std::endl;
    std::cout << "P(n) = 1 - (365/365) × (364/365) × (363/365) × ... × ((365-n+1)/365)" << std::endl;
    std::cout << "     = 1 - Π(i=1 to n-1) (365-i)/365" << std::endl;
    std::cout << std::endl;
    
    // 显示几个人的手动计算过程
    std::cout << "手动计算示例：" << std::endl;
    std::cout << "2人时: P(2) = 1 - (365/365) × (364/365) = 1 - 0.9973 = 0.0027" << std::endl;
    std::cout << "3人时: P(3) = 1 - (365/365) × (364/365) × (363/365) = 1 - 0.9918 = 0.0082" << std::endl;
    std::cout << "23人时: P(23) = 1 - 0.4927 = 0.5073" << std::endl;
}

/**
 * @brief 主函数：演示生日悖论问题
 */
int main() {
#ifdef ACM_LOCAL
    freopen("data.in", "r", stdin);
    freopen("data.out", "w", stdout);
#endif
    std::cout << "=== 生日悖论问题演示 ===" << std::endl;
    std::cout << "《算法导论》第五章5.4.1节" << std::endl << std::endl;
    
    // 演示数学推导过程
    demonstrateMathematicalDerivation();
    
    // 打印概率表
    printProbabilityTable();
    
    // 分析关键概率点
    analyzeKeyPoints();
    
    // 特别强调经典结果
    std::cout << "\n=== 经典结果 ===" << std::endl;
    std::cout << "23人时，至少两人生日相同的概率约为: " 
              << std::fixed << std::setprecision(6) 
              << BirthdayParadox::calculateProbability(23) << std::endl;
    std::cout << "30人时，至少两人生日相同的概率约为: " 
              << BirthdayParadox::calculateProbability(30) << std::endl;
    std::cout << "50人时，至少两人生日相同的概率约为: " 
              << BirthdayParadox::calculateProbability(50) << std::endl;
    std::cout << "70人时，至少两人生日相同的概率约为: " 
              << BirthdayParadox::calculateProbability(70) << std::endl;
    
    return 0;
}