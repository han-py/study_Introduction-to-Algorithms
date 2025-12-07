//
// Created by HaPpY on 2025/12/7.
//

#include <iostream>
#include <vector>
#include <climits>

/**
 * 维护最大堆性质
 * @param arr 数组表示的堆
 * @param heapSize 堆的大小
 * @param i 需要维护节点的索引
 */
void maxHeapify(std::vector<int>& arr, int heapSize, int i) {
    int largest = i;          // 初始化最大值为根节点
    int left = 2 * i + 1;     // 左子节点
    int right = 2 * i + 2;    // 右子节点

    // 如果左子节点存在且大于根节点
    if (left < heapSize && arr[left] > arr[largest])
        largest = left;

    // 如果右子节点存在且大于当前最大值
    if (right < heapSize && arr[right] > arr[largest])
        largest = right;

    // 如果最大值不是根节点
    if (largest != i) {
        std::swap(arr[i], arr[largest]);
        // 递归地调整受影响的子树
        maxHeapify(arr, heapSize, largest);
    }
}

/**
 * 构建最大堆
 * @param arr 待构建堆的数组
 * @param n 数组长度
 */
void buildMaxHeap(std::vector<int>& arr, int n) {
    // 从最后一个非叶子节点开始，自底向上构建最大堆
    for (int i = n / 2 - 1; i >= 0; i--)
        maxHeapify(arr, n, i);
}

/**
 * 向最大堆中插入一个元素
 * @param arr 堆数组
 * @param key 要插入的元素
 */
void heapInsert(std::vector<int>& arr, int& heapSize, int key) {
    // 增加堆的大小
    heapSize++;
    if (heapSize > (int)arr.size()) {
        arr.push_back(key);
    } else {
        arr[heapSize - 1] = key;
    }
    
    // 保持最大堆性质
    int i = heapSize - 1;
    while (i > 0 && arr[(i - 1) / 2] < arr[i]) {
        std::swap(arr[i], arr[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

/**
 * 获取最大元素（堆顶元素）
 * @param arr 堆数组
 * @return 堆顶元素
 */
int heapMaximum(const std::vector<int>& arr) {
    if (arr.empty()) {
        std::cerr << "堆为空" << std::endl;
        return INT_MIN;
    }
    return arr[0];
}

/**
 * 提取并删除最大元素（堆顶元素）
 * @param arr 堆数组
 * @param heapSize 堆大小的引用
 * @return 堆顶元素
 */
int heapExtractMax(std::vector<int>& arr, int& heapSize) {
    if (heapSize < 1) {
        std::cerr << "堆下溢" << std::endl;
        return INT_MIN;
    }
    
    int max = arr[0];
    arr[0] = arr[heapSize - 1];
    heapSize--;
    maxHeapify(arr, heapSize, 0);
    return max;
}

/**
 * 增加堆中某个元素的值
 * @param arr 堆数组
 * @param i 要增加元素的索引
 * @param key 新的键值
 */
void heapIncreaseKey(std::vector<int>& arr, int i, int key) {
    if (key < arr[i]) {
        std::cerr << "新的键值比当前键值小" << std::endl;
        return;
    }
    
    arr[i] = key;
    while (i > 0 && arr[(i - 1) / 2] < arr[i]) {
        std::swap(arr[i], arr[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

/**
 * 打印数组元素
 * @param arr 要打印的数组
 * @param msg 打印信息
 */
void printArray(const std::vector<int>& arr, int heapSize, const std::string& msg = "") {
    if (!msg.empty()) {
        std::cout << msg;
    }
    for (int i = 0; i < heapSize; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

/**
 * 主函数，用于测试优先队列（最大堆实现）
 */
int main() {
#ifdef ACM_LOCAL
    freopen("data.in", "r", stdin);
    freopen("data.out", "w", stdout);
#endif
    
    std::cout << "========================================" << std::endl;
    std::cout << "           优先队列算法演示" << std::endl;
    std::cout << "========================================" << std::endl << std::endl;
    
    // 初始化优先队列
    std::vector<int> priorityQueue = {15, 13, 9, 5, 12, 8, 7, 4, 0, 6, 2, 1};
    int heapSize = priorityQueue.size();
    
    std::cout << "初始优先队列: ";
    printArray(priorityQueue, heapSize);
    std::cout << std::endl;
    
    // 构建最大堆
    buildMaxHeap(priorityQueue, heapSize);
    std::cout << "构建最大堆后: ";
    printArray(priorityQueue, heapSize);
    std::cout << std::endl;
    
    // 获取最大元素
    std::cout << "当前最大元素: " << heapMaximum(priorityQueue) << std::endl << std::endl;
    
    // 提取最大元素
    int maxElement = heapExtractMax(priorityQueue, heapSize);
    std::cout << "提取的最大元素: " << maxElement << std::endl;
    std::cout << "提取后优先队列: ";
    printArray(priorityQueue, heapSize);
    std::cout << std::endl;
    
    // 插入新元素
    int newKey = 10;
    std::cout << "插入新元素 " << newKey << ": ";
    heapInsert(priorityQueue, heapSize, newKey);
    printArray(priorityQueue, heapSize);
    std::cout << std::endl;
    
    // 增加某个元素的值
    std::cout << "将索引1处的元素增加到14: ";
    heapIncreaseKey(priorityQueue, 1, 14);
    printArray(priorityQueue, heapSize);
    std::cout << std::endl;
    
    // 再次提取最大元素
    maxElement = heapExtractMax(priorityQueue, heapSize);
    std::cout << "再次提取的最大元素: " << maxElement << std::endl;
    std::cout << "提取后优先队列: ";
    printArray(priorityQueue, heapSize);
    
    return 0;
}