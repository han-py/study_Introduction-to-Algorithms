#include <iostream>
#include "DoublyLinkedList.cpp"

void testDoublyLinkedList() {
    std::cout << "=== 双向链表测试 ===" << std::endl;
    DoublyLinkedList<std::string> list;
    
    // 测试空链表
    std::cout << "1. 测试空链表:" << std::endl;
    std::cout << "   链表是否为空: " << (list.empty() ? "是" : "否") << std::endl;
    std::cout << "   链表大小: " << list.getSize() << std::endl;
    
    // 测试插入操作
    std::cout << "\n2. 测试插入操作:" << std::endl;
    list.push_front("front1");
    list.push_front("front2");
    std::cout << "   在头部插入 \"front1\", \"front2\" 后:" << std::endl;
    list.print();
    
    list.push_back("back1");
    list.push_back("back2");
    std::cout << "   在尾部插入 \"back1\", \"back2\" 后:" << std::endl;
    list.print();
    
    list.insert(2, "middle");
    std::cout << "   在索引2处插入 \"middle\" 后:" << std::endl;
    list.print();
    
    // 测试访问操作
    std::cout << "\n3. 测试访问操作:" << std::endl;
    std::cout << "   第一个元素: " << list.front() << std::endl;
    std::cout << "   最后一个元素: " << list.back() << std::endl;
    
    // 测试反向打印
    std::cout << "   反向打印链表:" << std::endl;
    list.printReverse();
    
    // 测试删除操作
    std::cout << "\n4. 测试删除操作:" << std::endl;
    list.pop_front();
    std::cout << "   删除头部元素后:" << std::endl;
    list.print();
    
    list.pop_back();
    std::cout << "   删除尾部元素后:" << std::endl;
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
        testDoublyLinkedList();
    } catch (const std::exception& e) {
        std::cerr << "发生异常: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}