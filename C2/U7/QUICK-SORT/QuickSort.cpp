//
// Created by HaPpY on 2025/12/7.
//

#include <iostream>
#include <vector>

// 添加全局变量用于跟踪递归深度
int recursionDepth = 0;

/**
 * 分区函数，快速排序的核心
 * @param arr 待排序数组
 * @param low 起始索引
 * @param high 结束索引
 * @return 分区点索引
 */
int partition(std::vector<int>& arr, int low, int high) {
    std::cout << "  ";
    for (int i = 0; i < recursionDepth; i++) std::cout << "  ";
    std::cout << "执行分区操作，范围: [" << low << ", " << high << "]" << std::endl;
    
    int pivot = arr[high];  // 选择最后一个元素作为基准
    std::cout << "  ";
    for (int i = 0; i < recursionDepth; i++) std::cout << "  ";
    std::cout << "基准元素(pivot): " << pivot << std::endl;
    
    int i = low - 1;  // 较小元素的索引

    for (int j = low; j <= high - 1; j++) {
        // 如果当前元素小于或等于基准
        if (arr[j] <= pivot) {
            i++;  // 较小元素索引增加
            if (i != j) {  // 只有当需要交换时才显示
                std::cout << "  ";
                for (int k = 0; k < recursionDepth; k++) std::cout << "  ";
                std::cout << "交换 arr[" << i << "]=" << arr[i] << " 和 arr[" << j << "]=" << arr[j] << std::endl;
                std::swap(arr[i], arr[j]);
            }
        }
    }
    std::cout << "  ";
    for (int k = 0; k < recursionDepth; k++) std::cout << "  ";
    std::cout << "将基准元素放到正确位置，交换 arr[" << (i+1) << "]=" << arr[i+1] << " 和 arr[" << high << "]=" << arr[high] << std::endl;
    std::swap(arr[i + 1], arr[high]);
    
    std::cout << "  ";
    for (int k = 0; k < recursionDepth; k++) std::cout << "  ";
    std::cout << "分区完成，基准元素位置: " << (i+1) << std::endl;
    return (i + 1);
}

/**
 * 快速排序主函数
 * @param arr 待排序数组
 * @param low 起始索引
 * @param high 结束索引
 */
void quickSort(std::vector<int>& arr, int low, int high) {
    // 打印当前处理范围
    std::cout << std::endl;
    for (int i = 0; i < recursionDepth; i++) std::cout << "  ";
    std::cout << "递归深度 " << recursionDepth << ": 处理范围 [" << low << ", " << high << "]" << std::endl;
    
    // 打印当前子数组状态
    std::cout << "  ";
    for (int i = 0; i < recursionDepth; i++) std::cout << "  ";
    std::cout << "当前子数组: ";
    for (int k = low; k <= high; k++) {
        std::cout << arr[k] << " ";
    }
    std::cout << std::endl;
    
    if (low < high) {
        // 获取分区索引
        recursionDepth++;
        int pi = partition(arr, low, high);
        recursionDepth--;

        std::cout << std::endl;
        for (int i = 0; i < recursionDepth; i++) std::cout << "  ";
        std::cout << "递归深度 " << recursionDepth << ": 基准位置 " << pi << ", 值为 " << arr[pi] << std::endl;
        
        // 分别对基准元素左右两部分进行排序
        std::cout << "  ";
        for (int i = 0; i < recursionDepth; i++) std::cout << "  ";
        std::cout << "递归处理左半部分: [" << low << ", " << (pi-1) << "]" << std::endl;
        recursionDepth++;
        quickSort(arr, low, pi - 1);
        recursionDepth--;
        
        std::cout << std::endl;
        for (int i = 0; i < recursionDepth; i++) std::cout << "  ";
        std::cout << "递归深度 " << recursionDepth << ": 处理右半部分: [" << (pi+1) << ", " << high << "]" << std::endl;
        recursionDepth++;
        quickSort(arr, pi + 1, high);
        recursionDepth--;
    } else {
        std::cout << "  ";
        for (int i = 0; i < recursionDepth; i++) std::cout << "  ";
        if (low == high) {
            std::cout << "递归终止条件: 子数组只有一个元素 " << arr[low] << std::endl;
        } else {
            std::cout << "递归终止条件: 无效范围 [" << low << ", " << high << "]" << std::endl;
        }
    }
}

/**
 * 快速排序包装函数
 * @param arr 待排序数组
 */
void quickSort(std::vector<int>& arr) {
    std::cout << "开始快速排序..." << std::endl;
    quickSort(arr, 0, arr.size() - 1);
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
 * 主函数，用于测试快速排序算法
 */
int main() {
#ifdef ACM_LOCAL
    freopen("data.in", "r", stdin);
    freopen("data.out", "w", stdout);
#endif
    
    std::vector<int> arr = {10, 7, 8, 9, 1, 5};
    std::cout << "========================================" << std::endl;
    std::cout << "           快速排序算法演示" << std::endl;
    std::cout << "========================================" << std::endl << std::endl;
    
    printArray(arr, "排序前: ");
    std::cout << std::endl;
    
    quickSort(arr);
    
    std::cout << std::endl << "========================================" << std::endl;
    std::cout << "排序完成!" << std::endl;
    printArray(arr, "排序后: ");
    
    return 0;
}