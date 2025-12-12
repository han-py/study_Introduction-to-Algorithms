#include <iostream>
#include <vector>
#include <stack>

/**
 * 核算法示例程序
 * 
 * 本程序演示了《算法导论》第17章摊还分析中的核算法（也称为记账方法或银行家方法）
 * 主要包含三个经典示例：
 * 1. 栈操作（包括MULTIPOP）
 * 2. 二进制计数器自增
 * 3. 动态数组扩容
 */

// ==================== 栈操作示例 ====================
class StackWithAccounting {
private:
    std::stack<int> data;
    int totalOperations;      // 总操作数
    int totalActualCost;      // 总实际代价
    int totalCredit;          // 总信用（存款）
    int totalAmortizedCost;   // 总摊还代价

public:
    StackWithAccounting() : totalOperations(0), totalActualCost(0), totalCredit(0), totalAmortizedCost(0) {}

    /**
     * PUSH操作
     * 实际代价: 1 (将元素压入栈)
     * 摊还代价: 2 (1用于实际操作，1作为信用存储在该元素上)
     */
    void push(int value) {
        std::cout << "执行 PUSH(" << value << ")" << std::endl;
        std::cout << "  实际代价: 1 (压入元素)" << std::endl;
        std::cout << "  摊还代价: 2 (1用于实际操作，1作为信用存储在该元素上)" << std::endl;
        
        data.push(value);
        totalOperations++;
        totalActualCost += 1;
        totalCredit += 1;  // 存储1个信用单位在该元素上
        totalAmortizedCost += 2;
        
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
        std::cout << "  当前信用总额: " << totalCredit << std::endl;
    }

    /**
     * POP操作
     * 实际代价: 1 (弹出栈顶元素)
     * 摊还代价: 0 (使用该元素上的信用支付实际代价)
     */
    void pop() {
        if (data.empty()) {
            std::cout << "执行 POP - 栈为空，无元素可弹出" << std::endl;
            return;
        }
        
        int value = data.top();
        std::cout << "执行 POP - 弹出元素: " << value << std::endl;
        std::cout << "  实际代价: 1 (弹出元素)" << std::endl;
        std::cout << "  摊还代价: 0 (使用该元素上的信用支付实际代价)" << std::endl;
        
        data.pop();
        totalOperations++;
        totalActualCost += 1;
        totalCredit -= 1;  // 使用1个信用单位支付实际代价
        totalAmortizedCost += 0;
        
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
        std::cout << "  当前信用总额: " << totalCredit << std::endl;
    }

    /**
     * MULTIPOP操作
     * 实际代价: min(s, k) (弹出k个元素或栈中所有元素)
     * 摊还代价: 0 (使用被弹出元素上的信用支付实际代价)
     */
    void multipop(int k) {
        int popCount = std::min(k, (int)data.size());
        if (popCount == 0) {
            std::cout << "执行 MULTIPOP(" << k << ") - 栈为空，无元素可弹出" << std::endl;
            return;
        }
        
        std::cout << "执行 MULTIPOP(" << k << ") - 实际弹出 " << popCount << " 个元素" << std::endl;
        std::cout << "  实际代价: " << popCount << " (弹出" << popCount << "个元素)" << std::endl;
        std::cout << "  摊还代价: 0 (使用被弹出元素上的信用支付实际代价)" << std::endl;
        
        for (int i = 0; i < popCount; i++) {
            std::cout << "  弹出元素: " << data.top() << std::endl;
            data.pop();
        }
        
        totalOperations++;
        totalActualCost += popCount;
        totalCredit -= popCount;  // 使用popCount个信用单位支付实际代价
        totalAmortizedCost += 0;
        
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
        std::cout << "  当前信用总额: " << totalCredit << std::endl;
    }

    /**
     * 获取总操作数和总实际代价
     */
    void getStats() const {
        std::cout << "\n栈操作统计:" << std::endl;
        std::cout << "  总操作数: " << totalOperations << std::endl;
        std::cout << "  总实际代价: " << totalActualCost << std::endl;
        std::cout << "  总摊还代价: " << totalAmortizedCost << std::endl;
        std::cout << "  总信用余额: " << totalCredit << std::endl;
        if (totalOperations > 0) {
            std::cout << "  平均实际代价: " << (double)totalActualCost / totalOperations << std::endl;
            std::cout << "  平均摊还代价: " << (double)totalAmortizedCost / totalOperations << std::endl;
        }
    }
};

// ==================== 二进制计数器示例 ====================
class BinaryCounterWithAccounting {
private:
    std::vector<bool> bits;
    int totalIncrements;
    int totalBitFlips;
    int totalCredit;
    int totalAmortizedCost;

public:
    BinaryCounterWithAccounting(int numBits) : bits(numBits, false), totalIncrements(0), 
                                               totalBitFlips(0), totalCredit(0), totalAmortizedCost(0) {
        std::cout << "创建 " << numBits << " 位二进制计数器，初始值为: ";
        printCounter();
    }

    /**
     * INCREMENT操作
     * 实际代价: 翻转的比特位数量
     * 摊还代价: 2 (1用于将0翻转为1，1作为信用存储在该位上)
     */
    void increment() {
        std::cout << "\n执行第 " << (totalIncrements + 1) << " 次 INCREMENT 操作:" << std::endl;
        std::cout << "  操作前: ";
        printCounter();
        
        int flips = 0;  // 记录本次操作翻转的比特位数
        int i = 0;
        
        // 翻转所有连续的1位为0（使用这些位上的信用支付）
        while (i < bits.size() && bits[i] == true) {
            std::cout << "  翻转位 " << i << " 从 1 到 0 (使用该位上的信用支付)" << std::endl;
            bits[i] = false;
            flips++;
            totalCredit -= 1;  // 使用1个信用单位支付翻转代价
            i++;
        }
        
        // 如果还有剩余位，将第一个0位翻转为1（支付1个单位实际代价，存储1个单位信用）
        if (i < bits.size()) {
            std::cout << "  翻转位 " << i << " 从 0 到 1 (支付1个单位实际代价，存储1个单位信用)" << std::endl;
            bits[i] = true;
            flips++;
            totalCredit += 1;  // 存储1个信用单位在该位上
        }
        
        totalIncrements++;
        totalBitFlips += flips;
        totalAmortizedCost += 2;  // 摊还代价恒为2
        
        std::cout << "  操作后: ";
        printCounter();
        std::cout << "  本次翻转位数: " << flips << std::endl;
        std::cout << "  本次实际代价: " << flips << std::endl;
        std::cout << "  本次摊还代价: 2" << std::endl;
        std::cout << "  当前信用总额: " << totalCredit << std::endl;
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
        std::cout << "  总信用余额: " << totalCredit << std::endl;
        if (totalIncrements > 0) {
            std::cout << "  平均每次翻转位数: " << (double)totalBitFlips / totalIncrements << std::endl;
            std::cout << "  平均摊还代价: " << (double)totalAmortizedCost / totalIncrements << std::endl;
        }
    }
};

// ==================== 动态数组示例 ====================
class DynamicArrayWithAccounting {
private:
    std::vector<int> data;
    int capacity;
    int totalOperations;
    int totalActualCost;
    int totalCredit;
    int totalAmortizedCost;

public:
    DynamicArrayWithAccounting() : capacity(1), totalOperations(0), totalActualCost(0), 
                                   totalCredit(0), totalAmortizedCost(0) {
        data.reserve(capacity);
        std::cout << "创建动态数组，初始容量: " << capacity << std::endl;
    }

    /**
     * PUSH操作（可能导致扩容）
     * 实际代价: 1 (插入元素) + 扩容时代价(复制所有元素)
     * 摊还代价: 3 (1用于插入元素，2作为信用存储在未来用于扩容)
     */
    void push(int value) {
        std::cout << "\n执行 PUSH(" << value << ")" << std::endl;
        std::cout << "  当前大小: " << data.size() << ", 容量: " << capacity << std::endl;
        
        int actualCost = 1;  // 插入元素的代价
        
        // 检查是否需要扩容
        if (data.size() == capacity) {
            std::cout << "  ⚠️  需要扩容!" << std::endl;
            int oldCapacity = capacity;
            capacity *= 2;  // 扩容为原来的2倍
            
            // 复制元素的代价
            actualCost += data.size();  // 需要复制所有现有元素
            totalCredit -= data.size(); // 使用之前存储的信用支付复制代价
            
            std::cout << "  扩容: " << oldCapacity << " -> " << capacity << std::endl;
            std::cout << "  复制元素代价: " << data.size() << " (使用之前存储的信用支付)" << std::endl;
        }
        
        data.push_back(value);
        totalOperations++;
        totalActualCost += actualCost;
        totalCredit += 2;  // 存储2个信用单位用于未来的扩容
        totalAmortizedCost += 3;  // 摊还代价恒为3
        
        std::cout << "  插入元素 " << value << ", 实际代价: " << actualCost << std::endl;
        std::cout << "  摊还代价: 3 (1用于插入元素，2作为信用存储用于未来扩容)" << std::endl;
        std::cout << "  当前信用总额: " << totalCredit << std::endl;
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
        std::cout << "  总信用余额: " << totalCredit << std::endl;
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
    std::cout << "🎓 算法导论第17.2节 - 核算法 (Accounting Method)\n";
    std::cout << "================================================\n\n";

    // ==================== 栈操作演示 ====================
    std::cout << "🧮 示例1: 栈操作 (包括MULTIPOP)\n";
    std::cout << "----------------------------------------\n";
    
    StackWithAccounting stack;
    
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
    
    BinaryCounterWithAccounting counter(6);  // 6位计数器
    
    // 执行多次自增操作
    for (int i = 0; i < 10; i++) {
        counter.increment();
    }
    
    counter.getStats();

    // ==================== 动态数组演示 ====================
    std::cout << "\n\n📈 示例3: 动态数组扩容\n";
    std::cout << "----------------------------------------\n";
    
    DynamicArrayWithAccounting dynArr;
    
    // 插入一系列元素
    for (int i = 1; i <= 12; i++) {
        dynArr.push(i);
    }
    
    dynArr.getStats();

    std::cout << "\n✅ 核算法演示完成!" << std::endl;
    std::cout << "\n📘 核算法核心思想:" << std::endl;
    std::cout << "   1. 为不同操作分配不同的摊还代价" << std::endl;
    std::cout << "   2. 某些操作的摊还代价高于实际代价，差额作为信用存储" << std::endl;
    std::cout << "   3. 某些操作的摊还代价低于实际代价，使用信用支付差额" << std::endl;
    std::cout << "   4. 总信用必须始终保持非负" << std::endl;
    std::cout << "   5. 总摊还代价必须是总实际代价的上界" << std::endl;

    return 0;
}