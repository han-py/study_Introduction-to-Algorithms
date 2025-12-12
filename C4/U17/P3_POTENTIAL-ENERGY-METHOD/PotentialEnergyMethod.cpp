#include <iostream>
#include <vector>
#include <stack>
#include <cmath>

/**
 * 势能法示例程序
 * 
 * 本程序演示了《算法导论》第17章摊还分析中的势能法（也称为物理学家方法）
 * 主要包含三个经典示例：
 * 1. 栈操作（包括MULTIPOP）
 * 2. 二进制计数器自增
 * 3. 动态数组扩容
 */

// ==================== 栈操作示例 ====================
class StackWithPotential {
private:
    std::stack<int> data;
    int totalOperations;      // 总操作数
    int totalActualCost;      // 总实际代价
    int totalAmortizedCost;   // 总摊还代价

public:
    StackWithPotential() : totalOperations(0), totalActualCost(0), totalAmortizedCost(0) {}

    /**
     * 势函数: Φ(Di) = 栈中元素个数
     * 初始状态: Φ(D0) = 0
     * 任何时刻: Φ(Di) ≥ 0
     */
    int potentialFunction() const {
        return data.size();
    }

    /**
     * PUSH操作
     * 实际代价: 1 (将元素压入栈)
     * 摊还代价: 实际代价 + 势能变化 = 1 + (s+1) - s = 2
     */
    void push(int value) {
        int oldPotential = potentialFunction();
        
        std::cout << "执行 PUSH(" << value << ")" << std::endl;
        std::cout << "  实际代价: 1 (压入元素)" << std::endl;
        
        data.push(value);
        totalOperations++;
        totalActualCost += 1;
        
        int newPotential = potentialFunction();
        int potentialChange = newPotential - oldPotential;
        int amortizedCost = 1 + potentialChange;
        totalAmortizedCost += amortizedCost;
        
        std::cout << "  势能变化: " << newPotential << " - " << oldPotential << " = " << potentialChange << std::endl;
        std::cout << "  摊还代价: 1 + " << potentialChange << " = " << amortizedCost << std::endl;
        
        std::cout << "  当前栈内容: ";
        std::stack<int> temp = data;
        std::vector<int> elements;
        while (!temp.empty()) {
            elements.push_back(temp.top());
            temp.pop();
        }
        for (int i = elements.size() - 1; i >= 0; i--) {
            std::cout << elements[i] << " ";
        }
        std::cout << std::endl;
        std::cout << "  当前势能: " << newPotential << std::endl;
    }

    /**
     * POP操作
     * 实际代价: 1 (弹出栈顶元素)
     * 摊还代价: 实际代价 + 势能变化 = 1 + (s-1) - s = 0
     */
    void pop() {
        if (data.empty()) {
            std::cout << "执行 POP - 栈为空，无元素可弹出" << std::endl;
            return;
        }
        
        int oldPotential = potentialFunction();
        int value = data.top();
        
        std::cout << "执行 POP - 弹出元素: " << value << std::endl;
        std::cout << "  实际代价: 1 (弹出元素)" << std::endl;
        
        data.pop();
        totalOperations++;
        totalActualCost += 1;
        
        int newPotential = potentialFunction();
        int potentialChange = newPotential - oldPotential;
        int amortizedCost = 1 + potentialChange;
        totalAmortizedCost += amortizedCost;
        
        std::cout << "  势能变化: " << newPotential << " - " << oldPotential << " = " << potentialChange << std::endl;
        std::cout << "  摊还代价: 1 + " << potentialChange << " = " << amortizedCost << std::endl;
        
        std::cout << "  当前栈内容: ";
        std::stack<int> temp = data;
        std::vector<int> elements;
        while (!temp.empty()) {
            elements.push_back(temp.top());
            temp.pop();
        }
        for (int i = elements.size() - 1; i >= 0; i--) {
            std::cout << elements[i] << " ";
        }
        std::cout << std::endl;
        std::cout << "  当前势能: " << newPotential << std::endl;
    }

    /**
     * MULTIPOP操作
     * 实际代价: min(s, k) (弹出k个元素或栈中所有元素)
     * 摊还代价: 实际代价 + 势能变化 = k + (s-k) - s = 0
     */
    void multipop(int k) {
        int popCount = std::min(k, (int)data.size());
        if (popCount == 0) {
            std::cout << "执行 MULTIPOP(" << k << ") - 栈为空，无元素可弹出" << std::endl;
            return;
        }
        
        int oldPotential = potentialFunction();
        
        std::cout << "执行 MULTIPOP(" << k << ") - 实际弹出 " << popCount << " 个元素" << std::endl;
        std::cout << "  实际代价: " << popCount << " (弹出" << popCount << "个元素)" << std::endl;
        
        for (int i = 0; i < popCount; i++) {
            std::cout << "  弹出元素: " << data.top() << std::endl;
            data.pop();
        }
        
        totalOperations++;
        totalActualCost += popCount;
        
        int newPotential = potentialFunction();
        int potentialChange = newPotential - oldPotential;
        int amortizedCost = popCount + potentialChange;
        totalAmortizedCost += amortizedCost;
        
        std::cout << "  势能变化: " << newPotential << " - " << oldPotential << " = " << potentialChange << std::endl;
        std::cout << "  摊还代价: " << popCount << " + " << potentialChange << " = " << amortizedCost << std::endl;
        
        std::cout << "  当前栈内容: ";
        std::stack<int> temp = data;
        std::vector<int> elements;
        while (!temp.empty()) {
            elements.push_back(temp.top());
            temp.pop();
        }
        for (int i = elements.size() - 1; i >= 0; i--) {
            std::cout << elements[i] << " ";
        }
        std::cout << std::endl;
        std::cout << "  当前势能: " << newPotential << std::endl;
    }

    /**
     * 获取总操作数和总实际代价
     */
    void getStats() const {
        std::cout << "\n栈操作统计:" << std::endl;
        std::cout << "  总操作数: " << totalOperations << std::endl;
        std::cout << "  总实际代价: " << totalActualCost << std::endl;
        std::cout << "  总摊还代价: " << totalAmortizedCost << std::endl;
        std::cout << "  当前势能: " << potentialFunction() << std::endl;
        if (totalOperations > 0) {
            std::cout << "  平均实际代价: " << (double)totalActualCost / totalOperations << std::endl;
            std::cout << "  平均摊还代价: " << (double)totalAmortizedCost / totalOperations << std::endl;
        }
    }
};

// ==================== 二进制计数器示例 ====================
class BinaryCounterWithPotential {
private:
    std::vector<bool> bits;
    int totalIncrements;
    int totalBitFlips;
    int totalAmortizedCost;

public:
    BinaryCounterWithPotential(int numBits) : bits(numBits, false), totalIncrements(0), 
                                              totalBitFlips(0), totalAmortizedCost(0) {
        std::cout << "创建 " << numBits << " 位二进制计数器，初始值为: ";
        printCounter();
        std::cout << "  初始势能: " << potentialFunction() << std::endl;
    }

    /**
     * 势函数: Φ(Di) = 计数器中1的个数
     * 初始状态: Φ(D0) = 0
     * 任何时刻: Φ(Di) ≥ 0
     */
    int potentialFunction() const {
        int count = 0;
        for (bool bit : bits) {
            if (bit) count++;
        }
        return count;
    }

    /**
     * INCREMENT操作
     * 实际代价: 翻转的比特位数量
     * 摊还代价: 实际代价 + 势能变化
     * 
     * 假设第i次INCREMENT操作重置了t位，那么:
     * - 实际代价: t+1 (t位从1变为0，1位从0变为1)
     * - 势能变化: (bi-1 - t + 1) - bi-1 = 1 - t
     * - 摊还代价: (t+1) + (1-t) = 2
     */
    void increment() {
        std::cout << "\n执行第 " << (totalIncrements + 1) << " 次 INCREMENT 操作:" << std::endl;
        std::cout << "  操作前: ";
        printCounter();
        std::cout << "  操作前势能: " << potentialFunction() << std::endl;
        
        int oldPotential = potentialFunction();
        int flips = 0;  // 记录本次操作翻转的比特位数
        int i = 0;
        
        // 翻转所有连续的1位为0
        while (i < bits.size() && bits[i] == true) {
            std::cout << "  翻转位 " << i << " 从 1 到 0" << std::endl;
            bits[i] = false;
            flips++;
            i++;
        }
        
        // 如果还有剩余位，将第一个0位翻转为1
        if (i < bits.size()) {
            std::cout << "  翻转位 " << i << " 从 0 到 1" << std::endl;
            bits[i] = true;
            flips++;
        }
        
        totalIncrements++;
        totalBitFlips += flips;
        
        int newPotential = potentialFunction();
        int potentialChange = newPotential - oldPotential;
        int amortizedCost = flips + potentialChange;
        totalAmortizedCost += amortizedCost;
        
        std::cout << "  操作后: ";
        printCounter();
        std::cout << "  操作后势能: " << newPotential << std::endl;
        std::cout << "  本次翻转位数: " << flips << std::endl;
        std::cout << "  本次实际代价: " << flips << std::endl;
        std::cout << "  势能变化: " << newPotential << " - " << oldPotential << " = " << potentialChange << std::endl;
        std::cout << "  本次摊还代价: " << flips << " + " << potentialChange << " = " << amortizedCost << std::endl;
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
                value += (1 << i);
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
        std::cout << "  总摊还代价: " << totalAmortizedCost << std::endl;
        std::cout << "  当前势能: " << potentialFunction() << std::endl;
        if (totalIncrements > 0) {
            std::cout << "  平均每次翻转位数: " << (double)totalBitFlips / totalIncrements << std::endl;
            std::cout << "  平均摊还代价: " << (double)totalAmortizedCost / totalIncrements << std::endl;
        }
    }
};

// ==================== 动态数组示例 ====================
class DynamicArrayWithPotential {
private:
    std::vector<int> data;
    int capacity;
    int totalOperations;
    int totalActualCost;
    int totalAmortizedCost;

public:
    DynamicArrayWithPotential() : capacity(1), totalOperations(0), totalActualCost(0), totalAmortizedCost(0) {
        data.reserve(capacity);
        std::cout << "创建动态数组，初始容量: " << capacity << std::endl;
        std::cout << "  初始势能: " << potentialFunction() << std::endl;
    }

    /**
     * 势函数: Φ(Di) = 2 * numi -sizei
     * 其中numi是数组中元素个数，sizei是数组容量
     * 
     * 初始状态: Φ(D0) = 2*0 - 1 = -1
     * 但我们可以通过定义Φ'(Di) = Φ(Di) - Φ(D0) = Φ(Di) + 1来使Φ'(D0) = 0
     * 
     * 为简化，我们使用: Φ(Di) = 2 * numi -sizei + 1
     * 这样Φ(D0) = 2*0 - 1 + 1 = 0
     * 
     * 任何时候: Φ(Di) ≥ 0，因为sizei ≥ numi，所以2*numi -sizei ≤ numi，因此2*numi -sizei + 1 > 0
     */
    int potentialFunction() const {
        return 2 * data.size() - capacity + 1;
    }

    /**
     * PUSH操作（可能导致扩容）
     * 实际代价: 1 (插入元素) + 扩容时代价(复制所有元素)
     * 摊还代价: 实际代价 + 势能变化
     */
    void push(int value) {
        std::cout << "\n执行 PUSH(" << value << ")" << std::endl;
        std::cout << "  当前大小: " << data.size() << ", 容量: " << capacity << std::endl;
        std::cout << "  操作前势能: " << potentialFunction() << std::endl;
        
        int oldPotential = potentialFunction();
        int actualCost = 1;  // 插入元素的代价
        
        // 检查是否需要扩容
        if (data.size() == capacity) {
            std::cout << "  ⚠️  需要扩容!" << std::endl;
            int oldCapacity = capacity;
            capacity *= 2;  // 扩容为原来的2倍
            
            // 复制元素的代价
            actualCost += data.size();  // 需要复制所有现有元素
            
            std::cout << "  扩容: " << oldCapacity << " -> " << capacity << std::endl;
            std::cout << "  复制元素代价: " << data.size() << std::endl;
        }
        
        data.push_back(value);
        totalOperations++;
        totalActualCost += actualCost;
        
        int newPotential = potentialFunction();
        int potentialChange = newPotential - oldPotential;
        int amortizedCost = actualCost + potentialChange;
        totalAmortizedCost += amortizedCost;
        
        std::cout << "  插入元素 " << value << ", 实际代价: " << actualCost << std::endl;
        std::cout << "  操作后势能: " << newPotential << std::endl;
        std::cout << "  势能变化: " << newPotential << " - " << oldPotential << " = " << potentialChange << std::endl;
        std::cout << "  本次摊还代价: " << actualCost << " + " << potentialChange << " = " << amortizedCost << std::endl;
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
        std::cout << "  总摊还代价: " << totalAmortizedCost << std::endl;
        std::cout << "  当前势能: " << potentialFunction() << std::endl;
        if (totalOperations > 0) {
            std::cout << "  平均实际代价: " << (double)totalActualCost / totalOperations << std::endl;
            std::cout << "  平均摊还代价: " << (double)totalAmortizedCost / totalOperations << std::endl;
        }
    }
};

int main() {
#ifdef ACM_LOCAL
    freopen("data.in", "r", stdin);
    freopen("data.out", "w", stdout);
#endif
    std::cout << "🎓 算法导论第17.3节 - 势能法 (Potential Method)\n";
    std::cout << "===============================================\n\n";

    // ==================== 栈操作演示 ====================
    std::cout << "🧮 示例1: 栈操作 (包括MULTIPOP)\n";
    std::cout << "----------------------------------------\n";
    
    StackWithPotential stack;
    
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
    
    BinaryCounterWithPotential counter(6);  // 6位计数器
    
    // 执行多次自增操作
    for (int i = 0; i < 10; i++) {
        counter.increment();
    }
    
    counter.getStats();

    // ==================== 动态数组演示 ====================
    std::cout << "\n\n📈 示例3: 动态数组扩容\n";
    std::cout << "----------------------------------------\n";
    
    DynamicArrayWithPotential dynArr;
    
    // 插入一系列元素
    for (int i = 1; i <= 12; i++) {
        dynArr.push(i);
    }
    
    dynArr.getStats();

    std::cout << "\n✅ 势能法演示完成!" << std::endl;
    std::cout << "\n📘 势能法核心思想:" << std::endl;
    std::cout << "   1. 定义一个势函数Φ，将数据结构Di映射为实数" << std::endl;
    std::cout << "   2. 确保Φ(D0) = 0且对所有i有Φ(Di) ≥ 0" << std::endl;
    std::cout << "   3. 第i个操作的摊还代价ĉi = ci + Φ(Di) - Φ(Di-1)" << std::endl;
    std::cout << "   4. 总摊还代价是总实际代价的上界" << std::endl;

    return 0;
}