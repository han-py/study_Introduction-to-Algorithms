//
// Created by HaPpY on 2025/12/7.
//

#include <iostream>
#include <stdexcept>
#include <vector>

/**
 * 栈的数组实现
 * 栈是一种后进先出（LIFO）的数据结构
 * 支持的主要操作：
 * 1. push - 入栈
 * 2. pop - 出栈
 * 3. top/peek - 查看栈顶元素
 * 4. isEmpty - 判断栈是否为空
 * 5. isFull - 判断栈是否已满
 */
class Stack {
private:
    int* array;           // 存储栈元素的数组
    int capacity;         // 栈的容量
    int topIndex;         // 指向栈顶元素的索引

public:
    /**
     * 构造函数，初始化栈
     * @param size 栈的最大容量
     */
    explicit Stack(int size) : capacity(size), topIndex(-1) {
        if (size <= 0) {
            throw std::invalid_argument("栈容量必须为正整数");
        }
        array = new int[size];
    }

    /**
     * 析构函数，释放动态分配的内存
     */
    ~Stack() {
        delete[] array;
    }

    /**
     * 拷贝构造函数
     */
    Stack(const Stack& other) : capacity(other.capacity), topIndex(other.topIndex) {
        array = new int[capacity];
        for (int i = 0; i <= topIndex; i++) {
            array[i] = other.array[i];
        }
    }

    /**
     * 赋值操作符重载
     */
    Stack& operator=(const Stack& other) {
        if (this != &other) {
            delete[] array;
            capacity = other.capacity;
            topIndex = other.topIndex;
            array = new int[capacity];
            for (int i = 0; i <= topIndex; i++) {
                array[i] = other.array[i];
            }
        }
        return *this;
    }

    /**
     * 入栈操作
     * @param value 要压入栈的元素
     */
    void push(int value) {
        if (isFull()) {
            throw std::overflow_error("栈已满，无法执行入栈操作");
        }
        array[++topIndex] = value;
        std::cout << "元素 " << value << " 已入栈" << std::endl;
    }

    /**
     * 出栈操作
     * @return 栈顶元素的值
     */
    int pop() {
        if (isEmpty()) {
            throw std::underflow_error("栈为空，无法执行出栈操作");
        }
        int value = array[topIndex--];
        std::cout << "元素 " << value << " 已出栈" << std::endl;
        return value;
    }

    /**
     * 查看栈顶元素但不移除它
     * @return 栈顶元素的值
     */
    int top() const {
        if (isEmpty()) {
            throw std::underflow_error("栈为空，无法获取栈顶元素");
        }
        return array[topIndex];
    }

    /**
     * 检查栈是否为空
     * @return 如果栈为空返回true，否则返回false
     */
    bool isEmpty() const {
        return topIndex == -1;
    }

    /**
     * 检查栈是否已满
     * @return 如果栈已满返回true，否则返回false
     */
    bool isFull() const {
        return topIndex == capacity - 1;
    }

    /**
     * 获取栈中元素的数量
     * @return 栈中元素的数量
     */
    int size() const {
        return topIndex + 1;
    }

    /**
     * 获取栈的容量
     * @return 栈的最大容量
     */
    int getCapacity() const {
        return capacity;
    }

    /**
     * 打印栈中所有元素（从栈顶到栈底）
     */
    void display() const {
        if (isEmpty()) {
            std::cout << "栈为空" << std::endl;
            return;
        }

        std::cout << "栈中元素（从栈顶到栈底）: ";
        for (int i = topIndex; i >= 0; i--) {
            std::cout << array[i] << " ";
        }
        std::cout << std::endl;
    }
};

/**
 * 测试函数，演示栈的各种操作
 */
void demonstrateStackOperations() {
    try {
        std::cout << "=== 栈操作演示 ===" << std::endl;
        
        // 创建一个容量为5的栈
        Stack stack(5);
        std::cout << "创建了一个容量为 " << stack.getCapacity() << " 的栈" << std::endl;

        // 检查栈是否为空
        std::cout << "栈是否为空: " << (stack.isEmpty() ? "是" : "否") << std::endl;

        // 入栈操作
        std::cout << "\n--- 入栈操作 ---" << std::endl;
        stack.push(10);
        stack.push(20);
        stack.push(30);
        stack.display();

        // 查看栈顶元素
        std::cout << "\n--- 查看栈顶元素 ---" << std::endl;
        std::cout << "栈顶元素是: " << stack.top() << std::endl;
        std::cout << "栈的大小: " << stack.size() << std::endl;

        // 继续入栈
        std::cout << "\n--- 继续入栈 ---" << std::endl;
        stack.push(40);
        stack.push(50);
        stack.display();
        std::cout << "栈是否已满: " << (stack.isFull() ? "是" : "否") << std::endl;

        // 尝试在满栈时入栈
        std::cout << "\n--- 尝试在满栈时入栈 ---" << std::endl;
        try {
            stack.push(60);
        } catch (const std::overflow_error& e) {
            std::cout << "捕获异常: " << e.what() << std::endl;
        }

        // 出栈操作
        std::cout << "\n--- 出栈操作 ---" << std::endl;
        stack.pop();
        stack.display();
        stack.pop();
        stack.display();

        // 检查栈的状态
        std::cout << "栈的大小: " << stack.size() << std::endl;
        std::cout << "栈是否为空: " << (stack.isEmpty() ? "是" : "否") << std::endl;
        std::cout << "栈是否已满: " << (stack.isFull() ? "是" : "否") << std::endl;

        // 继续出栈直到栈为空
        std::cout << "\n--- 继续出栈直到栈为空 ---" << std::endl;
        while (!stack.isEmpty()) {
            stack.pop();
            if (!stack.isEmpty()) {
                stack.display();
            }
        }
        std::cout << "栈是否为空: " << (stack.isEmpty() ? "是" : "否") << std::endl;

        // 尝试在空栈时出栈
        std::cout << "\n--- 尝试在空栈时出栈 ---" << std::endl;
        try {
            stack.pop();
        } catch (const std::underflow_error& e) {
            std::cout << "捕获异常: " << e.what() << std::endl;
        }

    } catch (const std::exception& e) {
        std::cerr << "发生错误: " << e.what() << std::endl;
    }
}

/**
 * 主函数
 */
int main() {
#ifdef ACM_LOCAL
    freopen("data.in", "r", stdin);
    freopen("data.out", "w", stdout);
#endif
    demonstrateStackOperations();
    return 0;
}