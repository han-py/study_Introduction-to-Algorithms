//
// Created by HaPpY on 2025/12/11.
//

#include <iostream>
#include <vector>
#include <algorithm>

/**
 * 活动结构体，表示一个活动
 */
struct Activity {
    int id;          // 活动编号
    int startTime;   // 开始时间
    int finishTime;  // 结束时间
    
    // 构造函数
    Activity(int id, int start, int finish) : id(id), startTime(start), finishTime(finish) {}
};

/**
 * 比较函数，用于按结束时间排序
 * @param a 第一个活动
 * @param b 第二个活动
 * @return 如果a的结束时间小于b的结束时间，则返回true
 */
bool compareActivities(const Activity& a, const Activity& b) {
    return a.finishTime < b.finishTime;
}

/**
 * 迭代贪心算法实现活动选择问题
 * 选择最多数量的兼容活动
 * 
 * @param activities 活动集合
 * @return 选中的活动集合
 */
std::vector<Activity> iterativeActivitySelection(std::vector<Activity>& activities) {
    // 步骤1：按结束时间排序
    std::sort(activities.begin(), activities.end(), compareActivities);
    
    // 存储选中的活动
    std::vector<Activity> selected;
    
    // 步骤2：选择第一个活动
    selected.push_back(activities[0]);
    int lastSelectedIndex = 0;
    
    std::cout << "选择活动 " << activities[0].id << " (时间: " << activities[0].startTime 
              << "-" << activities[0].finishTime << ")" << std::endl;
    
    // 步骤3：按贪心策略选择后续活动
    for (int i = 1; i < activities.size(); i++) {
        // 如果当前活动的开始时间不早于上一个选中活动的结束时间，则选择该活动
        if (activities[i].startTime >= activities[lastSelectedIndex].finishTime) {
            selected.push_back(activities[i]);
            lastSelectedIndex = i;
            std::cout << "选择活动 " << activities[i].id << " (时间: " << activities[i].startTime 
                      << "-" << activities[i].finishTime << ")" << std::endl;
        }
    }
    
    return selected;
}

/**
 * 递归贪心算法实现活动选择问题
 * 
 * @param activities 按结束时间排序的活动集合
 * @param k 上一个选中的活动索引
 * @param n 活动总数
 * @return 选中的活动集合
 */
std::vector<Activity> recursiveActivitySelection(const std::vector<Activity>& activities, int k, int n) {
    // 寻找第一个与活动k兼容的活动
    int m = k + 1;
    while (m < n && activities[m].startTime < activities[k].finishTime) {
        m++;
    }
    
    // 如果找到了兼容活动
    if (m < n) {
        std::cout << "选择活动 " << activities[m].id << " (时间: " << activities[m].startTime 
                  << "-" << activities[m].finishTime << ")" << std::endl;
        
        // 递归选择后续活动
        std::vector<Activity> result = recursiveActivitySelection(activities, m, n);
        result.push_back(activities[m]);
        return result;
    } else {
        // 没有更多兼容活动
        return std::vector<Activity>();
    }
}

/**
 * 递归贪心算法的包装函数
 * 
 * @param activities 活动集合
 * @return 选中的活动集合
 */
std::vector<Activity> recursiveActivitySelectionWrapper(std::vector<Activity>& activities) {
    // 按结束时间排序
    std::sort(activities.begin(), activities.end(), compareActivities);
    
    // 创建结果容器
    std::vector<Activity> selected;
    
    // 选择第一个活动
    std::cout << "选择活动 " << activities[0].id << " (时间: " << activities[0].startTime 
              << "-" << activities[0].finishTime << ")" << std::endl;
    selected.push_back(activities[0]);
    
    // 递归选择其余活动
    std::vector<Activity> recursiveResult = recursiveActivitySelection(activities, 0, activities.size());
    
    // 将递归结果添加到选中活动中
    for (int i = recursiveResult.size() - 1; i >= 0; i--) {
        selected.push_back(recursiveResult[i]);
    }
    
    return selected;
}

/**
 * 打印活动列表
 * @param activities 活动集合
 */
void printActivities(const std::vector<Activity>& activities) {
    std::cout << "活动列表:" << std::endl;
    std::cout << "ID\t开始时间\t结束时间" << std::endl;
    std::cout << "--------------------------------" << std::endl;
    for (const auto& activity : activities) {
        std::cout << activity.id << "\t" << activity.startTime << "\t\t" << activity.finishTime << std::endl;
    }
    std::cout << std::endl;
}

/**
 * 主函数 - 演示活动选择问题
 */
int main() {
#ifdef ACM_LOCAL
    freopen("data.in", "r", stdin);
    freopen("data.out", "w", stdout);
#endif
    std::cout << "==============================================" << std::endl;
    std::cout << "           活动选择问题演示程序" << std::endl;
    std::cout << "==============================================" << std::endl;
    std::cout << "问题描述：" << std::endl;
    std::cout << "给定n个活动集合，每个活动都有开始时间和结束时间，" << std::endl;
    std::cout << "选择出最大数量的兼容活动（活动时间不冲突）。" << std::endl;
    std::cout << "==============================================" << std::endl << std::endl;
    
    // 创建示例活动集合（《算法导论》图16-1）
    std::vector<Activity> activities1 = {
        Activity(1, 1, 4),
        Activity(2, 3, 5),
        Activity(3, 0, 6),
        Activity(4, 5, 7),
        Activity(5, 3, 9),
        Activity(6, 5, 9),
        Activity(7, 6, 10),
        Activity(8, 8, 11),
        Activity(9, 8, 12),
        Activity(10, 2, 14),
        Activity(11, 12, 16)
    };
    
    std::vector<Activity> activities2 = activities1; // 为递归算法复制一份
    
    // 打印原始活动列表
    std::cout << "原始活动列表：" << std::endl;
    printActivities(activities1);
    
    // 执行迭代贪心算法
    std::cout << "【迭代贪心算法】" << std::endl;
    std::cout << "执行活动选择算法..." << std::endl;
    std::cout << "选择过程：" << std::endl;
    std::vector<Activity> selectedActivitiesIterative = iterativeActivitySelection(activities1);
    
    // 输出迭代算法结果
    std::cout << std::endl << "==============================================" << std::endl;
    std::cout << "迭代算法执行完毕！" << std::endl;
    std::cout << "选中的活动数量: " << selectedActivitiesIterative.size() << std::endl;
    std::cout << "选中的活动列表:" << std::endl;
    std::cout << "ID\t开始时间\t结束时间" << std::endl;
    std::cout << "--------------------------------" << std::endl;
    for (const auto& activity : selectedActivitiesIterative) {
        std::cout << activity.id << "\t" << activity.startTime << "\t\t" << activity.finishTime << std::endl;
    }
    std::cout << "==============================================" << std::endl << std::endl;
    
    // 执行递归贪心算法
    std::cout << "【递归贪心算法】" << std::endl;
    std::cout << "执行活动选择算法..." << std::endl;
    std::cout << "选择过程：" << std::endl;
    std::vector<Activity> selectedActivitiesRecursive = recursiveActivitySelectionWrapper(activities2);
    
    // 输出递归算法结果
    std::cout << std::endl << "==============================================" << std::endl;
    std::cout << "递归算法执行完毕！" << std::endl;
    std::cout << "选中的活动数量: " << selectedActivitiesRecursive.size() << std::endl;
    std::cout << "选中的活动列表:" << std::endl;
    std::cout << "ID\t开始时间\t结束时间" << std::endl;
    std::cout << "--------------------------------" << std::endl;
    for (const auto& activity : selectedActivitiesRecursive) {
        std::cout << activity.id << "\t" << activity.startTime << "\t\t" << activity.finishTime << std::endl;
    }
    std::cout << "==============================================" << std::endl;
    
    return 0;
}