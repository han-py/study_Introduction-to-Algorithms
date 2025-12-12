#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <iomanip>

/**
 * 用拟阵求解任务调度问题
 * 
 * 问题描述:
 * 在单处理器上具有期限和惩罚的单位时间任务调度问题：
 * 给定一个有穷单位时间任务的集合S，集合S中的每个任务都有一个截止期限d_i和超时惩罚w_i，
 * 需要找出集合S的一个调度，使得因任务误期所导致的总惩罚最小。
 * 
 * 算法思路:
 * 1. 将最小化迟任务的惩罚之和问题转化为最大化早任务的惩罚之和的问题
 * 2. 使用拟阵理论，通过贪心算法找到最优的早任务集合
 * 3. 早任务按截止时间排序执行，迟任务随意排在后面
 */

// 任务结构
struct Task {
    int id;           // 任务ID
    int deadline;     // 截止时间
    int penalty;      // 惩罚权重
    
    Task(int id, int deadline, int penalty) 
        : id(id), deadline(deadline), penalty(penalty) {}
    
    // 用于按惩罚降序排序
    bool operator<(const Task& other) const {
        return penalty > other.penalty;  // 惩罚高的优先
    }
};

// 任务调度拟阵类
class TaskSchedulingMatroid {
private:
    std::vector<Task> tasks;
    
    /**
     * 检查任务集合是否独立
     * 根据引理16.12，任务集合A独立当且仅当对于t=0,1,2,...,n，有Nt(A) <= t
     * 其中Nt(A)表示A中截止时间<=t的任务数量
     */
    bool isIndependentHelper(const std::set<int>& taskIds) const {
        if (taskIds.empty()) return true;
        
        // 计算每个时间点的累计任务数
        std::vector<int> countByDeadline(tasks.size() + 1, 0);
        
        // 统计各个截止时间的任务数量
        for (int taskId : taskIds) {
            // 找到对应的任务
            const Task* task = nullptr;
            for (const auto& t : tasks) {
                if (t.id == taskId) {
                    task = &t;
                    break;
                }
            }
            if (task) {
                // 限制截止时间不超过任务总数
                int adjustedDeadline = std::min(task->deadline, (int)tasks.size());
                countByDeadline[adjustedDeadline]++;
            }
        }
        
        // 计算前缀和并检查独立性条件
        int cumulativeCount = 0;
        for (int t = 1; t <= (int)tasks.size(); t++) {
            cumulativeCount += countByDeadline[t];
            if (cumulativeCount > t) {
                return false;  // 违反了拟阵的独立性条件
            }
        }
        
        return true;
    }

public:
    TaskSchedulingMatroid(const std::vector<Task>& tasks) : tasks(tasks) {}
    
    /**
     * 检查任务子集是否独立（符合拟阵定义）
     * 根据定理16.13，如果S是一个给定了截止时间的单位时间任务集合，
     * I是所有独立任务集合的集合，则对应的系统(M = (S, I))是一个拟阵
     */
    bool isIndependent(const std::set<int>& taskIds) const {
        return isIndependentHelper(taskIds);
    }
    
    // 获取所有任务
    const std::vector<Task>& getTasks() const {
        return tasks;
    }
};

/**
 * 贪心算法求解任务调度问题
 * 根据定理16.11，若M=(S,I)是一个加权拟阵，权重函数是w，
 * 那么GREEDY(M,w)返回一个最优子集
 */
std::vector<Task> greedyTaskScheduling(const TaskSchedulingMatroid& matroid) {
    // 获取任务并按惩罚降序排序
    std::vector<Task> tasks = matroid.getTasks();
    std::sort(tasks.begin(), tasks.end());
    
    std::cout << "🔧 执行任务调度贪心算法:\n";
    std::cout << "   按惩罚降序排列的任务: ";
    for (const auto& task : tasks) {
        std::cout << "(任务" << task.id << ",截止时间:" << task.deadline 
                  << ",惩罚:" << task.penalty << ") ";
    }
    std::cout << "\n\n";
    
    std::set<int> independentSet;
    std::vector<Task> scheduledTasks;
    
    // 贪心选择
    for (const Task& task : tasks) {
        std::set<int> tentativeSet = independentSet;
        tentativeSet.insert(task.id);
        
        std::cout << "   考虑调度任务 " << task.id << " (截止时间: " << task.deadline 
                  << ", 惩罚: " << task.penalty << ")...";
        
        if (matroid.isIndependent(tentativeSet)) {
            independentSet.insert(task.id);
            scheduledTasks.push_back(task);
            std::cout << " ✅ 调度成功\n";
        } else {
            std::cout << " ❌ 调度失败（会导致任务超时）\n";
        }
    }
    
    return scheduledTasks;
}

// 打印结果
void printResult(const std::vector<Task>& allTasks, const std::vector<Task>& scheduledTasks) {
    std::cout << "\n🏆 贪心算法结果:\n";
    
    // 计算总惩罚
    int totalPenalty = 0;
    std::set<int> scheduledIds;
    for (const auto& task : scheduledTasks) {
        scheduledIds.insert(task.id);
    }
    
    std::cout << "   早任务(按时完成): ";
    for (const auto& task : scheduledTasks) {
        std::cout << task.id << " ";
    }
    std::cout << "\n";
    
    std::cout << "   迟任务(超时完成): ";
    int latePenalty = 0;
    for (const auto& task : allTasks) {
        if (scheduledIds.find(task.id) == scheduledIds.end()) {
            std::cout << task.id << " ";
            latePenalty += task.penalty;
        }
    }
    std::cout << "\n";
    
    std::cout << "   总惩罚: " << latePenalty << "\n";
    
    // 显示调度顺序
    std::cout << "\n📋 最终调度顺序:\n";
    std::cout << "   时刻: ";
    for (int i = 0; i < (int)scheduledTasks.size(); i++) {
        std::cout << std::setw(3) << i << " ";
    }
    for (int i = (int)scheduledTasks.size(); i < (int)allTasks.size(); i++) {
        std::cout << std::setw(3) << i << " ";
    }
    std::cout << "\n";
    
    std::cout << "   任务: ";
    for (const auto& task : scheduledTasks) {
        std::cout << std::setw(3) << task.id << " ";
    }
    
    std::set<int> printedLate;
    for (const auto& task : allTasks) {
        if (scheduledIds.find(task.id) == scheduledIds.end() && 
            printedLate.find(task.id) == printedLate.end()) {
            std::cout << std::setw(3) << task.id << " ";
            printedLate.insert(task.id);
        }
    }
    std::cout << "\n";
}

int main() {
#ifdef ACM_LOCAL
    freopen("data.in", "r", stdin);
    freopen("data.out", "w", stdout);
#endif
    std::cout << "🎓 算法导论第16.5节 - 用拟阵求解任务调度问题\n";
    std::cout << "================================================\n\n";
    
    std::cout << "📖 问题描述:\n";
    std::cout << "   在单处理器上具有期限和惩罚的单位时间任务调度问题：\n";
    std::cout << "   给定n个单位时间任务的集合S，每个任务都有截止期限和超时惩罚，\n";
    std::cout << "   目标是找出一个调度使得总惩罚最小。\n\n";
    
    std::cout << "🧠 算法原理:\n";
    std::cout << "   1. 将问题转化为寻找最大权重的独立任务集合（早任务）\n";
    std::cout << "   2. 利用拟阵结构和贪心算法求解\n";
    std::cout << "   3. 早任务按截止时间排序执行，迟任务排在后面\n\n";
    
    // 示例：任务调度问题
    std::cout << "📊 示例: 单位时间任务调度问题\n";
    std::cout << "   问题: 给定一组任务，找到总惩罚最小的调度方案\n\n";
    
    // 创建任务集合
    // 任务格式: (ID, 截止时间, 惩罚)
    std::vector<Task> tasks = {
        Task(1, 4, 70),  // 任务1: 截止时间4，惩罚70
        Task(2, 2, 60),  // 任务2: 截止时间2，惩罚60
        Task(3, 4, 50),  // 任务3: 截止时间4，惩罚50
        Task(4, 3, 40),  // 任务4: 截止时间3，惩罚40
        Task(5, 1, 30),  // 任务5: 截止时间1，惩罚30
        Task(6, 4, 20),  // 任务6: 截止时间4，惩罚20
        Task(7, 6, 10)   // 任务7: 截止时间6，惩罚10
    };
    
    std::cout << "   任务列表:\n";
    std::cout << "   ID\t截止时间\t惩罚\n";
    std::cout << "   ------------------------\n";
    for (const auto& task : tasks) {
        std::cout << "   " << task.id << "\t" << task.deadline << "\t\t" << task.penalty << "\n";
    }
    std::cout << "\n";
    
    TaskSchedulingMatroid taskMatroid(tasks);
    
    // 应用贪心算法
    std::vector<Task> scheduledTasks = greedyTaskScheduling(taskMatroid);
    
    printResult(tasks, scheduledTasks);
    
    std::cout << "\n✅ 算法完成! 贪心算法在这个任务调度拟阵实例中找到了最优解。\n";
    
    return 0;
}