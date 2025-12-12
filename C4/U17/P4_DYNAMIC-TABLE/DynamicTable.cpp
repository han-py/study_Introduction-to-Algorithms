#include <iostream>
#include <algorithm>
#include <iomanip>

/**
 * 动态表实现示例程序
 * 
 * 本程序演示了《算法导论》第17章摊还分析中的动态表（Dynamic Table）概念
 * 包括表的扩张和收缩策略及其摊还分析
 */

class DynamicTable {
private:
    int* table;           // 存储元素的数组
    int size;             // 表的总容量
    int num;              // 当前存储的元素数量
    
public:
    // 构造函数
    DynamicTable() : table(nullptr), size(0), num(0) {}
    
    // 析构函数
    ~DynamicTable() {
        delete[] table;
    }
    
    // 获取当前表的大小
    int getSize() const { return size; }
    
    // 获取当前元素数量
    int getNum() const { return num; }
    
    // 获取负载因子
    double getLoadFactor() const {
        if (size == 0) return 0.0;
        return static_cast<double>(num) / size;
    }
    
    // 插入元素（只增加num，不实际存储值）
    void insert() {
        // 如果表已满，则进行扩张
        if (num == size) {
            std::cout << "扩张操作: ";
            expand();
        }
        
        num++;
        std::cout << "插入元素，当前元素数: " << num 
                  << ", 表容量: " << size 
                  << ", 负载因子: " << std::fixed << std::setprecision(2) << getLoadFactor() 
                  << std::endl;
    }
    
    // 删除元素
    void remove() {
        if (num == 0) {
            std::cout << "表为空，无法删除元素" << std::endl;
            return;
        }
        
        num--;
        std::cout << "删除元素，当前元素数: " << num 
                  << ", 表容量: " << size 
                  << ", 负载因子: " << std::fixed << std::setprecision(2) << getLoadFactor()
                  << std::endl;
        
        // 如果负载因子低于1/4且表容量大于1，则进行收缩
        if (size > 1 && getLoadFactor() < 0.25) {
            std::cout << "收缩操作: ";
            contract();
        }
    }
    
private:
    // 扩张表（倍增策略）
    void expand() {
        int newSize = (size == 0) ? 1 : size * 2;
        int* newTable = new int[newSize];
        
        // 复制原有元素
        for (int i = 0; i < num; i++) {
            newTable[i] = table[i];
        }
        
        // 删除旧表并更新指针
        delete[] table;
        table = newTable;
        size = newSize;
        
        std::cout << "表从容量 " << size/2 << " 扩张到 " << size << std::endl;
    }
    
    // 收缩表（半减策略）
    void contract() {
        int newSize = size / 2;
        int* newTable = new int[newSize];
        
        // 复制现有元素
        for (int i = 0; i < num; i++) {
            newTable[i] = table[i];
        }
        
        // 删除旧表并更新指针
        delete[] table;
        table = newTable;
        size = newSize;
        
        std::cout << "表从容量 " << size*2 << " 收缩到 " << size << std::endl;
    }
};

// 演示动态表操作
void demonstrateDynamicTable() {
    std::cout << "=== 动态表演示 ===" << std::endl;
    DynamicTable dt;
    
    std::cout << "\n--- 插入元素 ---" << std::endl;
    // 插入一系列元素
    for (int i = 0; i < 10; i++) {
        dt.insert();
    }
    
    std::cout << "\n--- 删除元素 ---" << std::endl;
    // 删除一些元素触发收缩
    for (int i = 0; i < 7; i++) {
        dt.remove();
    }
}

// 计算摊还成本示例
void analyzeAmortizedCost() {
    std::cout << "\n=== 摊还成本分析 ===" << std::endl;
    std::cout << "假设我们进行n次插入操作:" << std::endl;
    std::cout << "1. 实际成本：某些操作成本高（需要扩张），大多数操作成本低（仅插入）" << std::endl;
    std::cout << "2. 摊还成本：通过势能法分析，每次操作的摊还成本为O(1)" << std::endl;
    std::cout << "\n势函数定义: Φ(T) = 2*num - size" << std::endl;
    std::cout << "- 当表未满时，势能非负" << std::endl;
    std::cout << "- 当表扩张时，势能帮助分摊扩张的成本" << std::endl;
}

int main() {
#ifdef ACM_LOCAL
    freopen("data.in", "r", stdin);
    freopen("data.out", "w", stdout);
#endif
    demonstrateDynamicTable();
    analyzeAmortizedCost();
    
    return 0;
}