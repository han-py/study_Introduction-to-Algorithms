#include <iostream>
#include <vector>
#include <bitset>
#include <cmath>

/**
 * 聚合分析示例程序
 * 
 * 本程序演示了《算法导论》第17章摊还分析中的聚合分析方法
 * 主要包含三个经典示例：
 * 1. 栈操作（包括MULTIPOP）
 * 2. 二进制计数器自增
 * 3. 动态数组扩容
 */

// ==================== 栈操作示例 ====================
class StackWithMultipop {
private:
    std::vector<int> data;
    int totalOperations;     // 总操作数
    int totalActualCost;     // 总实际代价

public:
    StackWithMultipop() : totalOperations(0), totalActualCost(0) {}

    /**
     * PUSH操作
     * 实际代价: 1 (将元素压入栈)
     */
    void push(int value) {
        std::cout << "执行 PUSH(" << value << ")" << std::endl;
        data.push_back(value);
        totalOperations++;
        totalActualCost += 1;  // 实际代价为1
        std::cout << "  当前栈内容: ";
        for (int val : data) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }

    /**
     * POP操作
     * 实际代价: 1 (弹出栈顶元素)
     */
    void pop() {
        if (data.empty()) {
            std::cout << "执行 POP - 栈为空，无元素可弹出" << std::endl;
            return;
        }
        
        std::cout << "执行 POP - 弹出元素: " << data.back() << std::endl;
        data.pop_back();
        totalOperations++;
        totalActualCost += 1;  // 实际代价为1
        std::cout << "  当前栈内容: ";
        for (int val : data) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }

    /**
     * MULTIPOP操作
     * 实际代价: min(s, k) (弹出k个元素或栈中所有元素)
     */
    void multipop(int k) {
        int popCount = std::min(k, (int)data.size());
        std::cout << "执行 MULTIPOP(" << k << ") - 实际弹出 " << popCount << " 个元素" << std::endl;
        
        for (int i = 0; i < popCount; i++) {
            std::cout << "  弹出元素: " << data.back() << std::endl;
            data.pop_back();
        }
        
        totalOperations++;
        totalActualCost += popCount;  // 实际代价为popCount
        std::cout << "  当前栈内容: ";
        for (int val : data) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }

    /**
     * 获取总操作数和总实际代价
     */
    void getStats() const {
        std::cout << "\n栈操作统计:" << std::endl;
        std::cout << "  总操作数: " << totalOperations << std::endl;
        std::cout << "  总实际代价: " << totalActualCost << std::endl;
        if (totalOperations > 0) {
            std::cout << "  平均代价(摊还代价): " << (double)totalActualCost / totalOperations << std::endl;
        }
    }
};

// ==================== 二进制计数器示例 ====================
class BinaryCounter {
private:
    std::vector<bool> bits;
    int totalIncrements;
    int totalBitFlips;

public:
    BinaryCounter(int numBits) : bits(numBits, false), totalIncrements(0), totalBitFlips(0) {
        std::cout << "创建 " << numBits << " 位二进制计数器，初始值为: ";
        printCounter();
    }

    /**
     * INCREMENT操作
     * 实际代价: 翻转的比特位数量
     */
    void increment() {
        std::cout << "\n执行第 " << (totalIncrements + 1) << " 次 INCREMENT 操作:" << std::endl;
        std::cout << "  操作前: ";
        printCounter();
        
        int flips = 0;  // 记录本次操作翻转的比特位数
        int i = 0;
        
        // 翻转所有连续的1位为0
        while (i < bits.size() && bits[i] == true) {
            bits[i] = false;
            flips++;
            i++;
        }
        
        // 如果还有剩余位，将第一个0位翻转为1
        if (i < bits.size()) {
            bits[i] = true;
            flips++;
        }
        
        totalIncrements++;
        totalBitFlips += flips;
        
        std::cout << "  操作后: ";
        printCounter();
        std::cout << "  本次翻转位数: " << flips << std::endl;
    }

    /**
     * 打印当前计数器值
     */
    void printCounter() const {
        for (int i = bits.size() - 1; i >= 0; i--) {
            std::cout << bits[i];
        }
        std::cout << " (十进制: " << getValue() << ")";
        std::cout << std::endl;
    }

    /**
     * 计算十进制值
     */
    int getValue() const {
        int value = 0;
        for (int i = 0; i < bits.size(); i++) {
            if (bits[i]) {
                value += pow(2, i);
            }
        }
        return value;
    }

    /**
     * 获取统计信息
     */
    void getStats() const {
        std::cout << "\n二进制计数器统计:" << std::endl;
        std::cout << "  总增量操作数: " << totalIncrements << std::endl;
        std::cout << "  总比特位翻转数: " << totalBitFlips << std::endl;
        if (totalIncrements > 0) {
            std::cout << "  平均每次翻转位数(摊还代价): " << (double)totalBitFlips / totalIncrements << std::endl;
        }
        
        // 理论分析：第i位翻转次数约为n/2^i
        std::cout << "\n理论分析:" << std::endl;
        std::cout << "  各位翻转次数估计:" << std::endl;
        double theoreticalTotal = 0;
        for (int i = 0; i < std::min(5, (int)bits.size()); i++) {  // 只显示前5位
            double flips = (double)totalIncrements / pow(2, i+1);
            std::cout << "    第" << (i+1) << "位: 约 " << flips << " 次" << std::endl;
            theoreticalTotal += flips;
        }
        std::cout << "  理论总翻转次数: 约 " << theoreticalTotal << std::endl;
        std::cout << "  理论摊还代价: 约 " << theoreticalTotal / totalIncrements << " 每次操作" << std::endl;
    }
};

// ==================== 动态数组示例 ====================
class DynamicArray {
private:
    std::vector<int> data;
    int capacity;
    int totalOperations;
    int totalActualCost;

public:
    DynamicArray() : capacity(1), totalOperations(0), totalActualCost(0) {
        data.reserve(capacity);
        std::cout << "创建动态数组，初始容量: " << capacity << std::endl;
    }

    /**
     * PUSH操作（可能导致扩容）
     * 实际代价: 1 (插入元素) + 扩容时代价(复制所有元素)
     */
    void push(int value) {
        std::cout << "\n执行 PUSH(" << value << ")" << std::endl;
        std::cout << "  当前大小: " << data.size() << ", 容量: " << capacity << std::endl;
        
        int cost = 1;  // 插入元素的代价
        
        // 检查是否需要扩容
        if (data.size() == capacity) {
            std::cout << "  ⚠️  需要扩容!" << std::endl;
            int oldCapacity = capacity;
            capacity *= 2;  // 扩容为原来的2倍
            
            // 复制元素的代价
            cost += data.size();  // 需要复制所有现有元素
            
            std::cout << "  扩容: " << oldCapacity << " -> " << capacity << std::endl;
            std::cout << "  复制元素代价: " << data.size() << std::endl;
        }
        
        data.push_back(value);
        totalOperations++;
        totalActualCost += cost;
        
        std::cout << "  插入元素 " << value << ", 实际代价: " << cost << std::endl;
        std::cout << "  当前数组: ";
        for (int val : data) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }

    /**
     * 获取统计信息
     */
    void getStats() const {
        std::cout << "\n动态数组统计:" << std::endl;
        std::cout << "  总操作数: " << totalOperations << std::endl;
        std::cout << "  总实际代价: " << totalActualCost << std::endl;
        if (totalOperations > 0) {
            std::cout << "  平均代价(摊还代价): " << (double)totalActualCost / totalOperations << std::endl;
        }
        
        // 理论分析
        std::cout << "\n理论分析:" << std::endl;
        std::cout << "  第i次扩容发生在第2^i个元素插入时，复制2^i个元素" << std::endl;
        std::cout << "  总代价 = n(插入) + (1+2+4+...+n/2) = n + (n-1) = 2n-1 = O(n)" << std::endl;
        std::cout << "  摊还代价 = O(n)/n = O(1)" << std::endl;
    }
};

int main() {
#ifdef ACM_LOCAL
    freopen("data.in", "r", stdin);
    freopen("data.out", "w", stdout);
#endif
    std::cout << "🎓 算法导论第17.1节 - 聚合分析 (Aggregate Analysis)\n";
    std::cout << "=====================================================\n\n";

    // ==================== 栈操作演示 ====================
    std::cout << "🧮 示例1: 栈操作 (包括MULTIPOP)\n";
    std::cout << "----------------------------------------\n";
    
    StackWithMultipop stack;
    
    // 执行一系列操作
    stack.push(1);
    stack.push(2);
    stack.push(3);
    stack.push(4);
    stack.push(5);
    
    stack.pop();
    
    stack.multipop(3);
    
    stack.push(6);
    stack.push(7);
    
    stack.getStats();

    // ==================== 二进制计数器演示 ====================
    std::cout << "\n\n🔢 示例2: 二进制计数器自增\n";
    std::cout << "----------------------------------------\n";
    
    BinaryCounter counter(6);  // 6位计数器
    
    // 执行多次自增操作
    for (int i = 0; i < 10; i++) {
        counter.increment();
    }
    
    counter.getStats();

    // ==================== 动态数组演示 ====================
    std::cout << "\n\n📈 示例3: 动态数组扩容\n";
    std::cout << "----------------------------------------\n";
    
    DynamicArray dynArr;
    
    // 插入一系列元素
    for (int i = 1; i <= 12; i++) {
        dynArr.push(i);
    }
    
    dynArr.getStats();

    std::cout << "\n✅ 聚合分析演示完成!" << std::endl;
    std::cout << "\n📘 聚合分析核心思想:" << std::endl;
    std::cout << "   1. 分析n个操作序列的最坏情况总时间T(n)" << std::endl;
    std::cout << "   2. 每个操作的摊还代价为T(n)/n" << std::endl;
    std::cout << "   3. 不同于平均情况分析，聚合分析不涉及概率" << std::endl;
    std::cout << "   4. 适用于大多数操作便宜但少数操作昂贵的场景" << std::endl;

    return 0;
}