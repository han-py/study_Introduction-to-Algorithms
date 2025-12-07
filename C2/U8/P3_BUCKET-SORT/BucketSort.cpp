//
// Created by HaPpY on 2025/12/7.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <list>

/**
 * 打印数组元素
 * @param arr 要打印的数组
 * @param msg 打印信息
 */
void printArray(const std::vector<float>& arr, const std::string& msg = "") {
    if (!msg.empty()) {
        std::cout << msg;
    }
    for (size_t i = 0; i < arr.size(); i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

/**
 * 桶排序算法实现
 * 《算法导论》第八章线性时间排序中的桶排序
 * @param arr 待排序的数组，假设元素都在[0, 1)区间内
 */
void bucketSort(std::vector<float>& arr) {
    if (arr.empty()) return;
    
    std::cout << "开始桶排序..." << std::endl;
    printArray(arr, "原数组: ");
    
    int n = arr.size();
    
    // 创建n个空桶
    std::vector<std::list<float>> buckets(n);
    
    // 将数组元素分配到各个桶中
    std::cout << "将元素分配到桶中:" << std::endl;
    for (int i = 0; i < n; i++) {
        // 计算元素应该放入哪个桶
        int bucketIndex = n * arr[i];
        buckets[bucketIndex].push_back(arr[i]);
        std::cout << "  元素 " << arr[i] << " 放入桶 " << bucketIndex << std::endl;
    }
    
    // 显示每个桶的内容
    std::cout << "各桶内容:" << std::endl;
    for (int i = 0; i < n; i++) {
        std::cout << "  桶 " << i << ": ";
        for (float val : buckets[i]) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }
    
    // 对每个桶内的元素进行排序
    std::cout << "对每个桶内元素进行排序:" << std::endl;
    for (int i = 0; i < n; i++) {
        if (!buckets[i].empty()) {
            buckets[i].sort(); // 使用list自带的sort方法
            std::cout << "  桶 " << i << " 排序后: ";
            for (float val : buckets[i]) {
                std::cout << val << " ";
            }
            std::cout << std::endl;
        }
    }
    
    // 按顺序将各桶中的元素放回原数组
    std::cout << "合并各桶元素到结果数组:" << std::endl;
    int index = 0;
    for (int i = 0; i < n; i++) {
        for (float val : buckets[i]) {
            arr[index++] = val;
        }
    }
}

/**
 * 主函数，用于测试桶排序算法
 */
int main() {
#ifdef ACM_LOCAL
    freopen("data.in", "r", stdin);
    freopen("data.out", "w", stdout);
#endif
    
    std::cout << "========================================" << std::endl;
    std::cout << "           桶排序算法演示" << std::endl;
    std::cout << "========================================" << std::endl << std::endl;
    
    // 测试用例
    std::vector<float> arr = {0.78, 0.17, 0.39, 0.26, 0.72, 0.94, 0.21, 0.12, 0.23, 0.68};
    std::cout << "测试用例:" << std::endl;
    printArray(arr, "排序前: ");
    std::cout << std::endl;
    
    bucketSort(arr);
    
    std::cout << std::endl;
    std::cout << "========================================" << std::endl;
    printArray(arr, "最终排序结果: ");
    std::cout << "桶排序算法演示完成!" << std::endl;
    
    return 0;
}