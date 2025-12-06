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
 * 堆排序算法实现
 * @param arr 待排序的数组
 */
void heapSort(std::vector<int>& arr) {
    int n = arr.size();

    // 构建最大堆
    buildMaxHeap(arr, n);

    // 逐个从堆顶取出元素
    for (int i = n - 1; i > 0; i--) {
        // 将当前最大元素（堆顶）移到数组末尾
        std::swap(arr[0], arr[i]);

        // 对剩下的元素重新调整为最大堆
        maxHeapify(arr, i, 0);
    }
}

/**
 * 打印数组元素
 * @param arr 要打印的数组
 */
void printArray(const std::vector<int>& arr) {
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
    std::cout << "排序前: ";
    printArray(arr);
    
    heapSort(arr);
    
    std::cout << "排序后: ";
    printArray(arr);
    
    return 0;
}