#include <iostream>
#include <memory>

/**
 * 指针和对象实现示例
 * 根据《算法导论》第10章内容实现
 */

// 对象结构体
struct Object {
    int key;
    Object* next;  // 指向下一个对象的指针
    
    Object() : key(0), next(nullptr) {}
    Object(int k) : key(k), next(nullptr) {}
};

// 指针和对象操作类
class PointerObjectManager {
private:
    Object* freeList;  // 空闲对象链表
    Object* allocatedObjects;  // 已分配对象链表
    
public:
    PointerObjectManager() : freeList(nullptr), allocatedObjects(nullptr) {
        // 初始化一些空闲对象
        for (int i = 0; i < 10; i++) {
            Object* obj = new Object();
            obj->next = freeList;
            freeList = obj;
        }
    }
    
    ~PointerObjectManager() {
        // 清理所有对象
        while (freeList) {
            Object* temp = freeList;
            freeList = freeList->next;
            delete temp;
        }
        
        while (allocatedObjects) {
            Object* temp = allocatedObjects;
            allocatedObjects = allocatedObjects->next;
            delete temp;
        }
    }
    
    /**
     * 分配一个对象
     * @return 指向新分配对象的指针
     */
    Object* allocateObject() {
        if (!freeList) {
            // 如果没有空闲对象，则创建一个新对象
            Object* newObj = new Object();
            newObj->next = allocatedObjects;
            allocatedObjects = newObj;
            return newObj;
        }
        
        // 从空闲链表中取出一个对象
        Object* obj = freeList;
        freeList = freeList->next;
        
        // 将对象加入已分配链表
        obj->next = allocatedObjects;
        allocatedObjects = obj;
        
        return obj;
    }
    
    /**
     * 释放一个对象
     * @param obj 要释放的对象指针
     */
    void freeObject(Object* obj) {
        if (!obj) return;
        
        // 从已分配链表中移除对象
        if (allocatedObjects == obj) {
            allocatedObjects = allocatedObjects->next;
        } else {
            Object* current = allocatedObjects;
            while (current && current->next != obj) {
                current = current->next;
            }
            
            if (current) {
                current->next = obj->next;
            } else {
                // 对象不在已分配链表中
                return;
            }
        }
        
        // 将对象加入空闲链表
        obj->next = freeList;
        freeList = obj;
    }
    
    /**
     * 设置对象的键值
     * @param obj 对象指针
     * @param key 键值
     */
    void setObjectKey(Object* obj, int key) {
        if (obj) {
            obj->key = key;
        }
    }
    
    /**
     * 获取对象的键值
     * @param obj 对象指针
     * @return 对象的键值
     */
    int getObjectKey(Object* obj) {
        return obj ? obj->key : -1;
    }
    
    /**
     * 打印已分配对象列表
     */
    void printAllocatedObjects() {
        std::cout << "已分配对象列表: ";
        Object* current = allocatedObjects;
        while (current) {
            std::cout << current->key << " -> ";
            current = current->next;
        }
        std::cout << "nullptr" << std::endl;
    }
    
    /**
     * 打印空闲对象列表
     */
    void printFreeObjects() {
        std::cout << "空闲对象列表: ";
        Object* current = freeList;
        while (current) {
            std::cout << current->key << " -> ";
            current = current->next;
        }
        std::cout << "nullptr" << std::endl;
    }
};

int main() {
#ifdef ACM_LOCAL
    freopen("data.in", "r", stdin);
    freopen("data.out", "w", stdout);
#endif
    std::cout << "=== 指针和对象实现演示 ===" << std::endl;
    
    // 创建指针对象管理器
    PointerObjectManager manager;
    
    std::cout << "\n初始状态:" << std::endl;
    manager.printAllocatedObjects();
    manager.printFreeObjects();
    
    // 分配几个对象
    std::cout << "\n分配3个对象..." << std::endl;
    Object* obj1 = manager.allocateObject();
    Object* obj2 = manager.allocateObject();
    Object* obj3 = manager.allocateObject();
    
    manager.setObjectKey(obj1, 10);
    manager.setObjectKey(obj2, 20);
    manager.setObjectKey(obj3, 30);
    
    std::cout << "设置键值后:" << std::endl;
    std::cout << "obj1.key = " << manager.getObjectKey(obj1) << std::endl;
    std::cout << "obj2.key = " << manager.getObjectKey(obj2) << std::endl;
    std::cout << "obj3.key = " << manager.getObjectKey(obj3) << std::endl;
    
    manager.printAllocatedObjects();
    manager.printFreeObjects();
    
    // 释放一个对象
    std::cout << "\n释放obj2..." << std::endl;
    manager.freeObject(obj2);
    
    manager.printAllocatedObjects();
    manager.printFreeObjects();
    
    // 再分配一个对象
    std::cout << "\n再分配一个对象..." << std::endl;
    Object* obj4 = manager.allocateObject();
    manager.setObjectKey(obj4, 40);
    
    std::cout << "obj4.key = " << manager.getObjectKey(obj4) << std::endl;
    manager.printAllocatedObjects();
    manager.printFreeObjects();
    
    return 0;
}