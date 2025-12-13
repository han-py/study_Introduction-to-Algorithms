#include <iostream>
#include <vector>
#include <iomanip>

/**
 * 不相交集合数据结构（并查集）实现
 * 
 * 根据《算法导论》第21章内容实现
 * 
 * 不相交集合数据结构支持以下操作：
 * 1. MAKE-SET(x) - 创建一个新的集合，其唯一成员是x
 * 2. UNION(x, y) - 将包含x和y的集合合并
 * 3. FIND-SET(x) - 返回包含x的集合的代表元素
 * 
 * 优化策略：
 * 1. 按秩合并（Union by rank）- 将秩较小的树连接到秩较大的树下
 * 2. 路径压缩（Path compression）- 在FIND-SET操作中，使查找路径上的每个节点直接指向根节点
 * 
 * 时间复杂度：
 * - MAKE-SET: O(1)
 * - UNION: O(α(n))
 * - FIND-SET: O(α(n))
 * 其中α(n)是反Ackermann函数，实际上可以认为是常数时间
 */

class DisjointSet {
private:
    std::vector<int> parent;  // parent[x] 表示元素x的父节点
    std::vector<int> rank;    // rank[x] 表示以x为根的子树的高度上界（秩）
    
public:
    /**
     * 构造函数
     * @param n 集合中元素的数量，元素编号从0到n-1
     */
    explicit DisjointSet(int n) : parent(n), rank(n, 0) {
        // 初始化时，每个元素都是自己集合的代表元素
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
        std::cout << "创建不相交集合数据结构，包含 " << n << " 个元素 [0.." << (n-1) << "]" << std::endl;
    }
    
    /**
     * MAKE-SET操作：创建只包含元素x的集合
     * 在初始化后一般不需要调用此方法，但在某些动态场景中可能有用
     * @param x 元素索引
     */
    void makeSet(int x) {
        std::cout << "MAKE-SET(" << x << "): 创建只包含元素 " << x << " 的新集合" << std::endl;
        parent[x] = x;
        rank[x] = 0;
    }
    
    /**
     * FIND-SET操作：查找包含元素x的集合的代表元素（根节点）
     * 使用路径压缩优化
     * @param x 要查找的元素
     * @return 包含x的集合的代表元素
     */
    int findSet(int x) {
        std::cout << "FIND-SET(" << x << "): ";
        
        // 路径压缩：如果x不是根节点，则将x的父节点设置为根节点
        if (parent[x] != x) {
            std::cout << "路径压缩 ";
            parent[x] = findSet(parent[x]);  // 递归查找根节点，并进行路径压缩
        }
        
        std::cout << "返回根节点 " << parent[x] << std::endl;
        return parent[x];
    }
    
    /**
     * 迭代版本的FIND-SET操作
     * 避免在很深的递归调用中可能出现的栈溢出问题
     * @param x 要查找的元素
     * @return 包含x的集合的代表元素
     */
    int findSetIterative(int x) {
        std::cout << "FIND-SET-ITERATIVE(" << x << "): ";
        
        // 第一遍查找根节点
        int root = x;
        while (parent[root] != root) {
            root = parent[root];
        }
        
        // 第二遍进行路径压缩
        while (parent[x] != x) {
            int next = parent[x];
            parent[x] = root;
            x = next;
        }
        
        std::cout << "返回根节点 " << root << std::endl;
        return root;
    }
    
    /**
     * UNION操作：合并包含元素x和y的集合
     * 使用按秩合并优化
     * @param x 第一个元素
     * @param y 第二个元素
     */
    void unionSets(int x, int y) {
        std::cout << "\nUNION(" << x << ", " << y << "): ";
        int rootX = findSet(x);
        int rootY = findSet(y);
        
        // 如果x和y已经在同一个集合中，则无需合并
        if (rootX == rootY) {
            std::cout << "元素 " << x << " 和 " << y << " 已经在同一个集合中" << std::endl;
            return;
        }
        
        std::cout << "合并包含 " << x << " 和 " << y << " 的集合" << std::endl;
        
        // 按秩合并：将秩较小的树连接到秩较大的树下
        if (rank[rootX] < rank[rootY]) {
            std::cout << "  将秩为 " << rank[rootX] << " 的树连接到秩为 " << rank[rootY] << " 的树下" << std::endl;
            parent[rootX] = rootY;
        } else if (rank[rootX] > rank[rootY]) {
            std::cout << "  将秩为 " << rank[rootY] << " 的树连接到秩为 " << rank[rootX] << " 的树下" << std::endl;
            parent[rootY] = rootX;
        } else {
            // 如果两棵树的秩相同，任选其一作为根，并将其秩加1
            std::cout << "  两棵树秩相同(" << rank[rootX] << ")，将其中一棵树连接到另一棵下，新根节点秩增加" << std::endl;
            parent[rootY] = rootX;
            rank[rootX]++;
        }
    }
    
    /**
     * 打印当前不相交集合的状态
     */
    void printSets() {
        std::cout << "\n========== 当前不相交集合状态 ==========" << std::endl;
        int n = parent.size();
        
        // 显示每个元素及其父节点
        std::cout << "元素:    ";
        for (int i = 0; i < n; i++) {
            std::cout << std::setw(3) << i;
        }
        std::cout << std::endl;
        
        std::cout << "父节点:  ";
        for (int i = 0; i < n; i++) {
            std::cout << std::setw(3) << parent[i];
        }
        std::cout << std::endl;
        
        std::cout << "秩:      ";
        for (int i = 0; i < n; i++) {
            std::cout << std::setw(3) << rank[i];
        }
        std::cout << std::endl;
        
        // 显示每个集合的组成
        std::cout << "\n集合分组:" << std::endl;
        std::vector<std::vector<int>> sets(n);
        for (int i = 0; i < n; i++) {
            int root = findSet(i);
            sets[root].push_back(i);
        }
        
        for (int i = 0; i < n; i++) {
            if (!sets[i].empty()) {
                std::cout << "  集合代表 " << i << ": {";
                for (size_t j = 0; j < sets[i].size(); j++) {
                    if (j > 0) std::cout << ", ";
                    std::cout << sets[i][j];
                }
                std::cout << "}" << std::endl;
            }
        }
        std::cout << "======================================" << std::endl;
    }
    
    /**
     * 检查两个元素是否属于同一个集合
     * @param x 第一个元素
     * @param y 第二个元素
     * @return 如果x和y在同一个集合中返回true，否则返回false
     */
    bool isConnected(int x, int y) {
        std::cout << "IS-CONNECTED(" << x << ", " << y << "): ";
        bool result = (findSet(x) == findSet(y));
        std::cout << (result ? "是" : "否") << " connected" << std::endl;
        return result;
    }
    
    /**
     * 获取集合的数量
     * @return 当前不相交集合中独立集合的数量
     */
    int getSetCount() {
        int count = 0;
        int n = parent.size();
        for (int i = 0; i < n; i++) {
            if (parent[i] == i) {  // 根节点代表一个集合
                count++;
            }
        }
        return count;
    }
};

/**
 * 演示不相交集合数据结构的操作
 */
void demonstrateDisjointSet() {
    std::cout << "\n########################################" << std::endl;
    std::cout << "##### 不相交集合数据结构操作演示 #####" << std::endl;
    std::cout << "########################################" << std::endl;
    
    // 创建包含9个元素的不相交集合（编号0-8）
    DisjointSet ds(9);
    ds.printSets();
    
    std::cout << "\n--- 执行一系列UNION操作 ---" << std::endl;
    
    // 执行Union操作创建集合
    ds.unionSets(1, 2);
    ds.printSets();
    
    ds.unionSets(3, 4);
    ds.printSets();
    
    ds.unionSets(5, 6);
    ds.printSets();
    
    ds.unionSets(7, 8);
    ds.printSets();
    
    ds.unionSets(1, 3);
    ds.printSets();
    
    ds.unionSets(5, 7);
    ds.printSets();
    
    ds.unionSets(1, 5);
    ds.printSets();
    
    std::cout << "\n--- 执行FIND-SET操作 ---" << std::endl;
    ds.findSet(2);
    ds.findSet(4);
    ds.findSet(6);
    ds.findSet(8);
    
    std::cout << "\n--- 执行IS-CONNECTED操作 ---" << std::endl;
    ds.isConnected(2, 8);
    ds.isConnected(1, 7);
    ds.isConnected(0, 1);
    
    std::cout << "\n--- 路径压缩效果演示 ---" << std::endl;
    std::cout << "多次执行FIND-SET(8)观察路径压缩效果:" << std::endl;
    ds.findSet(8);
    ds.findSet(8);
    ds.findSet(8);
    
    std::cout << "\n--- 迭代版本FIND-SET演示 ---" << std::endl;
    ds.findSetIterative(2);
    
    std::cout << "\n--- 当前集合数量 ---" << std::endl;
    std::cout << "当前共有 " << ds.getSetCount() << " 个独立集合" << std::endl;
}

/**
 * Kruskal最小生成树算法示例
 * 展示不相交集合在图算法中的应用
 */
void demonstrateKruskal() {
    std::cout << "\n########################################" << std::endl;
    std::cout << "###### Kruskal算法应用演示 ########" << std::endl;
    std::cout << "########################################" << std::endl;
    
    // 假设有一个包含6个顶点(0-5)的图
    const int vertices = 6;
    DisjointSet ds(vertices);
    
    // 边的表示：{起点, 终点, 权重}
    std::vector<std::tuple<int, int, int>> edges = {
        {0, 1, 4}, {0, 2, 3}, {1, 2, 1}, {1, 3, 2},
        {2, 3, 4}, {3, 4, 2}, {3, 5, 6}, {4, 5, 3}
    };
    
    std::cout << "图的边列表（已按权重排序）：" << std::endl;
    for (const auto& edge : edges) {
        int u, v, weight;
        std::tie(u, v, weight) = edge;
        std::cout << "  (" << u << "," << v << ") 权重: " << weight << std::endl;
    }
    
    std::cout << "\n执行Kruskal算法构建最小生成树：" << std::endl;
    std::vector<std::tuple<int, int, int>> mst;
    
    for (const auto& edge : edges) {
        int u, v, weight;
        std::tie(u, v, weight) = edge;
        
        // 如果两个顶点不在同一集合中，则添加该边到MST
        if (ds.findSet(u) != ds.findSet(v)) {
            ds.unionSets(u, v);
            mst.push_back(edge);
            std::cout << "添加边 (" << u << "," << v << ") 权重: " << weight << std::endl;
        } else {
            std::cout << "跳过边 (" << u << "," << v << ") 权重: " << weight << " (会形成环路)" << std::endl;
        }
    }
    
    std::cout << "\n最小生成树包含的边：" << std::endl;
    int totalWeight = 0;
    for (const auto& edge : mst) {
        int u, v, weight;
        std::tie(u, v, weight) = edge;
        std::cout << "  (" << u << "," << v << ") 权重: " << weight << std::endl;
        totalWeight += weight;
    }
    std::cout << "最小生成树总权重: " << totalWeight << std::endl;
}

/**
 * 主函数
 */
int main() {
#ifdef ACM_LOCAL
    freopen("data.in", "r", stdin);
    freopen("data.out", "w", stdout);
#endif
    std::cout << "========================================" << std::endl;
    std::cout << "=== 不相交集合数据结构演示程序 ===" << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "本程序演示了《算法导论》第21章中不相交集合数据结构的实现" << std::endl;
    std::cout << "包括MAKE-SET、UNION、FIND-SET等核心操作" << std::endl;
    std::cout << "以及按秩合并和路径压缩两种优化策略" << std::endl;
    
    demonstrateDisjointSet();
    demonstrateKruskal();
    
    std::cout << "\n程序执行完毕，感谢使用！" << std::endl;
    return 0;
}