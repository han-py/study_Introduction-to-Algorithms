#include <iostream>
#include "SinglyLinkedList.cpp"

void testSinglyLinkedList() {
    std::cout << "=== 单向链表测试 ===" << std::endl;
    SinglyLinkedList<int> list;
    
    // 测试空链表
    std::cout << "1. 测试空链表:" << std::endl;
    std::cout << "   链表是否为空: " << (list.empty() ? "是" : "否") << std::endl;
    std::cout << "   链表大小: " << list.getSize() << std::endl;
    
    // 测试插入操作
    std::cout << "\n2. 测试插入操作:" << std::endl;
    list.push_front(3);
    list.push_front(2);
    list.push_front(1);
    std::cout << "   在头部插入 3, 2, 1 后:" << std::endl;
    list.print();
    
    list.insert(1, 4);
    std::cout << "   在索引1处插入4后:" << std::endl;
    list.print();
    
    // 测试访问操作
    std::cout << "\n3. 测试访问操作:" << std::endl;
    std::cout << "   第一个元素: " << list.front() << std::endl;
    
    // 测试删除操作
    std::cout << "\n4. 测试删除操作:" << std::endl;
    list.pop_front();
    std::cout << "   删除头部元素后:" << std::endl;
    list.print();
    
    list.erase(1);
    std::cout << "   删除索引1处的元素后:" << std::endl;
    list.print();
    
    std::cout << "   链表大小: " << list.getSize() << std::endl;
    
    // 清空链表
    std::cout << "\n5. 清空链表:" << std::endl;
    list.clear();
    std::cout << "   清空后链表是否为空: " << (list.empty() ? "是" : "否") << std::endl;
    list.print();
}

int main() {
#ifdef ACM_LOCAL
    freopen("data.in", "r", stdin);
    freopen("data.out", "w", stdout);
#endif
    try {
        testSinglyLinkedList();
    } catch (const std::exception& e) {
        std::cerr << "发生异常: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}