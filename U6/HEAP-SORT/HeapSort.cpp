//
// Created by HaPpY on 2025/12/6.
//

#include <iostream>
#include <vector>

/**
 * 维护最大堆性质
 * @param arr 数组表示的堆
 * @param heapSize 堆的大小
 * @param i 需要维护节点的索引
 * @param step 步骤编号
 */
void maxHeapify(std::vector<int>& arr, int heapSize, int i, int& step) {
    std::cout << "第" << step++ << "步: 调整节点 " << i << ", 当前堆大小: " << heapSize << std::endl;
    std::cout << "  调整前: ";
    for (int k = 0; k < heapSize; k++) {
        std::cout << arr[k] << " ";
    }
    std::cout << "| ";
    for (int k = heapSize; k < (int)arr.size(); k++) {
        std::cout << arr[k] << " ";
    }
    std::cout << std::endl;

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
        std::cout << "  交换 arr[" << i << "]=" << arr[i] << " 和 arr[" << largest << "]=" << arr[largest] << std::endl;
        std::swap(arr[i], arr[largest]);
        // 递归地调整受影响的子树
        maxHeapify(arr, heapSize, largest, step);
    } else {
        std::cout << "  节点 " << i << " 已满足最大堆性质，无需调整" << std::endl;
    }
    
    std::cout << "  调整后: ";
    for (int k = 0; k < heapSize; k++) {
        std::cout << arr[k] << " ";
    }
    std::cout << "| ";
    for (int k = heapSize; k < (int)arr.size(); k++) {
        std::cout << arr[k] << " ";
    }
    std::cout << std::endl << std::endl;
}

// 重载版本，不带step参数
void maxHeapify(std::vector<int>& arr, int heapSize, int i) {
    static int step = 1;
    maxHeapify(arr, heapSize, i, step);
}

/**
 * 构建最大堆
 * @param arr 待构建堆的数组
 * @param n 数组长度
 */
void buildMaxHeap(std::vector<int>& arr, int n) {
    std::cout << "开始构建最大堆..." << std::endl;
    std::cout << "初始数组: ";
    for (int i = 0; i < n; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl << std::endl;

    // 从最后一个非叶子节点开始，自底向上构建最大堆
    for (int i = n / 2 - 1; i >= 0; i--) {
        static int step = 1;
        maxHeapify(arr, n, i, step);
    }
    
    std::cout << "最大堆构建完成!" << std::endl;
    std::cout << "最大堆: ";
    for (int i = 0; i < n; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl << std::endl;
}

/**
 * 堆排序算法实现
 * @param arr 待排序的数组
 */
void heapSort(std::vector<int>& arr) {
    int n = arr.size();
    std::cout << "开始执行堆排序算法..." << std::endl;
    std::cout << "========================================" << std::endl;

    // 构建最大堆
    buildMaxHeap(arr, n);

    std::cout << "开始排序阶段..." << std::endl;
    std::cout << "========================================" << std::endl;

    // 逐个从堆顶取出元素
    for (int i = n - 1; i > 0; i--) {
        std::cout << "第 " << (n-i) << " 轮排序:" << std::endl;
        std::cout << "  交换堆顶元素 " << arr[0] << " 与末尾元素 " << arr[i] << std::endl;
        // 将当前最大元素（堆顶）移到数组末尾
        std::swap(arr[0], arr[i]);
        
        std::cout << "  交换后: ";
        for (int k = 0; k <= i; k++) {
            std::cout << arr[k] << " ";
        }
        std::cout << "| ";
        for (int k = i+1; k < n; k++) {
            std::cout << arr[k] << " ";
        }
        std::cout << " (已排序部分)" << std::endl;

        // 对剩下的元素重新调整为最大堆
        static int step = 1;
        maxHeapify(arr, i, 0, step);
    }
}

/**
 * 打印数组元素
 * @param arr 要打印的数组
 * @param msg 打印信息
 */
void printArray(const std::vector<int>& arr, const std::string& msg = "") {
    if (!msg.empty()) {
        std::cout << msg;
    }
    for (size_t i = 0; i < arr.size(); i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

/**
 * 主函数，用于测试堆排序算法
 */
int main() {
#ifdef ACM_LOCAL
    freopen("data.in", "r", stdin);
    freopen("data.out", "w", stdout);
#endif
    std::vector<int> arr = {4, 1, 3, 2, 16, 9, 10, 14, 8, 7};
    std::cout << "========================================" << std::endl;
    std::cout << "           堆排序算法演示" << std::endl;
    std::cout << "========================================" << std::endl << std::endl;
    
    printArray(arr, "排序前: ");
    std::cout << std::endl;
    
    heapSort(arr);
    
    std::cout << "========================================" << std::endl;
    std::cout << "排序完成!" << std::endl;
    printArray(arr, "排序后: ");
    
    return 0;
}