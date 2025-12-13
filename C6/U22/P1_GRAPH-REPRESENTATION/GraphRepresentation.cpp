#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <stack>
#include <iomanip>

/**
 * 图的表示方法实现
 * 
 * 根据《算法导论》第22章22.1节内容实现
 * 
 * 图可以用多种方式表示，最常见的有：
 * 1. 邻接表表示法 (Adjacency-List Representation)
 * 2. 邻接矩阵表示法 (Adjacency-Matrix Representation)
 * 
 * 本程序将实现这两种表示方法，并演示它们的基本操作
 */

// 邻接表表示的有向图
class DirectedAdjacencyListGraph {
private:
    int vertices;                           // 顶点数
    std::vector<std::list<int>> adjList;    // 邻接表
    std::vector<int> inDegree;              // 入度数组
    
public:
    /**
     * 构造函数
     * @param v 顶点数量
     */
    explicit DirectedAdjacencyListGraph(int v) : vertices(v), adjList(v), inDegree(v, 0) {
        std::cout << "创建邻接表表示的有向图，包含 " << v << " 个顶点 [0.." << (v-1) << "]" << std::endl;
    }
    
    /**
     * 添加一条有向边 (u, v)
     * @param u 起点
     * @param v 终点
     */
    void addEdge(int u, int v) {
        std::cout << "添加有向边 (" << u << ", " << v << ")" << std::endl;
        adjList[u].push_back(v);
        inDegree[v]++;  // 增加终点的入度
    }
    
    /**
     * 打印邻接表表示
     */
    void printGraph() {
        std::cout << "\n========== 邻接表表示 ==========" << std::endl;
        for (int i = 0; i < vertices; i++) {
            std::cout << "顶点 " << i << " (入度: " << inDegree[i] << "): ";
            for (int neighbor : adjList[i]) {
                std::cout << neighbor << " ";
            }
            std::cout << std::endl;
        }
        std::cout << "===============================" << std::endl;
    }
    
    /**
     * 获取顶点数
     * @return 顶点数量
     */
    int getVertexCount() const {
        return vertices;
    }
    
    /**
     * 获取边数
     * @return 边的数量
     */
    int getEdgeCount() const {
        int count = 0;
        for (int i = 0; i < vertices; i++) {
            count += adjList[i].size();
        }
        return count;
    }
    
    /**
     * 获取指定顶点的邻接点
     * @param v 顶点
     * @return 邻接点列表
     */
    const std::list<int>& getAdjacent(int v) const {
        return adjList[v];
    }
    
    /**
     * 检查是否存在边 (u, v)
     * @param u 起点
     * @param v 终点
     * @return 如果存在边返回true，否则返回false
     */
    bool hasEdge(int u, int v) const {
        for (int neighbor : adjList[u]) {
            if (neighbor == v) {
                return true;
            }
        }
        return false;
    }
    
    /**
     * 获取顶点的出度
     * @param v 顶点
     * @return 出度
     */
    int getOutDegree(int v) const {
        return adjList[v].size();
    }
    
    /**
     * 获取顶点的入度
     * @param v 顶点
     * @return 入度
     */
    int getInDegree(int v) const {
        return inDegree[v];
    }
};

// 邻接表表示的无向图
class UndirectedAdjacencyListGraph {
private:
    int vertices;                           // 顶点数
    std::vector<std::list<int>> adjList;    // 邻接表
    
public:
    /**
     * 构造函数
     * @param v 顶点数量
     */
    explicit UndirectedAdjacencyListGraph(int v) : vertices(v), adjList(v) {
        std::cout << "创建邻接表表示的无向图，包含 " << v << " 个顶点 [0.." << (v-1) << "]" << std::endl;
    }
    
    /**
     * 添加一条无向边 (u, v)
     * @param u 顶点u
     * @param v 顶点v
     */
    void addEdge(int u, int v) {
        std::cout << "添加无向边 (" << u << ", " << v << ")" << std::endl;
        adjList[u].push_back(v);
        adjList[v].push_back(u);  // 无向图需要在两个顶点的邻接表中都添加对方
    }
    
    /**
     * 打印邻接表表示
     */
    void printGraph() {
        std::cout << "\n========== 无向图邻接表表示 ==========" << std::endl;
        for (int i = 0; i < vertices; i++) {
            std::cout << "顶点 " << i << " (度数: " << adjList[i].size() << "): ";
            for (int neighbor : adjList[i]) {
                std::cout << neighbor << " ";
            }
            std::cout << std::endl;
        }
        std::cout << "===================================" << std::endl;
    }
    
    /**
     * 获取顶点数
     * @return 顶点数量
     */
    int getVertexCount() const {
        return vertices;
    }
    
    /**
     * 获取边数
     * @return 边的数量
     */
    int getEdgeCount() const {
        int count = 0;
        for (int i = 0; i < vertices; i++) {
            count += adjList[i].size();
        }
        return count / 2;  // 无向图中每条边被计算了两次
    }
    
    /**
     * 获取指定顶点的邻接点
     * @param v 顶点
     * @return 邻接点列表
     */
    const std::list<int>& getAdjacent(int v) const {
        return adjList[v];
    }
    
    /**
     * 检查是否存在边 (u, v)
     * @param u 顶点u
     * @param v 顶点v
     * @return 如果存在边返回true，否则返回false
     */
    bool hasEdge(int u, int v) const {
        for (int neighbor : adjList[u]) {
            if (neighbor == v) {
                return true;
            }
        }
        return false;
    }
    
    /**
     * 获取顶点的度数
     * @param v 顶点
     * @return 度数
     */
    int getDegree(int v) const {
        return adjList[v].size();
    }
};

// 邻接矩阵表示的图
class AdjacencyMatrixGraph {
private:
    int vertices;                    // 顶点数
    std::vector<std::vector<int>> adjMatrix;  // 邻接矩阵
    
public:
    /**
     * 构造函数
     * @param v 顶点数量
     */
    explicit AdjacencyMatrixGraph(int v) : vertices(v), adjMatrix(v, std::vector<int>(v, 0)) {
        std::cout << "创建邻接矩阵表示的图，包含 " << v << " 个顶点 [0.." << (v-1) << "]" << std::endl;
    }
    
    /**
     * 添加一条边 (u, v)
     * @param u 起点
     * @param v 终点
     */
    void addEdge(int u, int v) {
        std::cout << "添加边 (" << u << ", " << v << ")" << std::endl;
        adjMatrix[u][v] = 1;
    }
    
    /**
     * 打印邻接矩阵表示
     */
    void printGraph() {
        std::cout << "\n========== 邻接矩阵表示 ==========" << std::endl;
        std::cout << "    ";
        for (int i = 0; i < vertices; i++) {
            std::cout << std::setw(3) << i;
        }
        std::cout << std::endl;
        
        for (int i = 0; i < vertices; i++) {
            std::cout << std::setw(3) << i << " ";
            for (int j = 0; j < vertices; j++) {
                std::cout << std::setw(3) << adjMatrix[i][j];
            }
            std::cout << std::endl;
        }
        std::cout << "================================" << std::endl;
    }
    
    /**
     * 获取顶点数
     * @return 顶点数量
     */
    int getVertexCount() const {
        return vertices;
    }
    
    /**
     * 获取边数
     * @return 边的数量
     */
    int getEdgeCount() const {
        int count = 0;
        for (int i = 0; i < vertices; i++) {
            for (int j = 0; j < vertices; j++) {
                if (adjMatrix[i][j] == 1) {
                    count++;
                }
            }
        }
        return count;
    }
    
    /**
     * 检查是否存在边 (u, v)
     * @param u 起点
     * @param v 终点
     * @return 如果存在边返回true，否则返回false
     */
    bool hasEdge(int u, int v) const {
        return adjMatrix[u][v] == 1;
    }
    
    /**
     * 获取指定顶点的出度
     * @param v 顶点
     * @return 出度
     */
    int getOutDegree(int v) const {
        int degree = 0;
        for (int j = 0; j < vertices; j++) {
            if (adjMatrix[v][j] == 1) {
                degree++;
            }
        }
        return degree;
    }
    
    /**
     * 获取指定顶点的入度
     * @param v 顶点
     * @return 入度
     */
    int getInDegree(int v) const {
        int degree = 0;
        for (int i = 0; i < vertices; i++) {
            if (adjMatrix[i][v] == 1) {
                degree++;
            }
        }
        return degree;
    }
};

/**
 * 图的遍历算法 - 广度优先搜索 (BFS)
 * @param graph 邻接表表示的图
 * @param start 起始顶点
 */
void BFS(const DirectedAdjacencyListGraph& graph, int start) {
    std::cout << "\n--- 广度优先搜索 (BFS) 从顶点 " << start << " 开始 ---" << std::endl;
    
    int vertices = graph.getVertexCount();
    std::vector<bool> visited(vertices, false);
    std::queue<int> queue;
    
    visited[start] = true;
    queue.push(start);
    std::cout << "访问顶点: " << start << std::endl;
    
    while (!queue.empty()) {
        int current = queue.front();
        queue.pop();
        
        // 访问当前顶点的所有未访问过的邻居
        for (int neighbor : graph.getAdjacent(current)) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                queue.push(neighbor);
                std::cout << "访问顶点: " << neighbor << std::endl;
            }
        }
    }
}

/**
 * 图的遍历算法 - 深度优先搜索 (DFS) 递归版本
 * @param graph 邻接表表示的图
 * @param vertex 当前顶点
 * @param visited 访问标记数组
 */
void DFSUtil(const DirectedAdjacencyListGraph& graph, int vertex, std::vector<bool>& visited) {
    visited[vertex] = true;
    std::cout << "访问顶点: " << vertex << std::endl;
    
    // 递归访问所有未访问过的邻居
    for (int neighbor : graph.getAdjacent(vertex)) {
        if (!visited[neighbor]) {
            DFSUtil(graph, neighbor, visited);
        }
    }
}

/**
 * 图的遍历算法 - 深度优先搜索 (DFS) 递归版本
 * @param graph 邻接表表示的图
 * @param start 起始顶点
 */
void DFSRecursive(const DirectedAdjacencyListGraph& graph, int start) {
    std::cout << "\n--- 深度优先搜索 (DFS) 递归版本 从顶点 " << start << " 开始 ---" << std::endl;
    
    int vertices = graph.getVertexCount();
    std::vector<bool> visited(vertices, false);
    
    DFSUtil(graph, start, visited);
}

/**
 * 图的遍历算法 - 深度优先搜索 (DFS) 迭代版本
 * @param graph 邻接表表示的图
 * @param start 起始顶点
 */
void DFSIterative(const DirectedAdjacencyListGraph& graph, int start) {
    std::cout << "\n--- 深度优先搜索 (DFS) 迭代版本 从顶点 " << start << " 开始 ---" << std::endl;
    
    int vertices = graph.getVertexCount();
    std::vector<bool> visited(vertices, false);
    std::stack<int> stack;
    
    stack.push(start);
    
    while (!stack.empty()) {
        int current = stack.top();
        stack.pop();
        
        if (!visited[current]) {
            visited[current] = true;
            std::cout << "访问顶点: " << current << std::endl;
            
            // 将所有未访问的邻居压入栈中
            // 注意：为了保持与递归版本一致的访问顺序，我们需要逆序压栈
            std::vector<int> neighbors;
            for (int neighbor : graph.getAdjacent(current)) {
                if (!visited[neighbor]) {
                    neighbors.push_back(neighbor);
                }
            }
            
            // 逆序压栈以保证访问顺序一致
            for (int i = neighbors.size() - 1; i >= 0; i--) {
                stack.push(neighbors[i]);
            }
        }
    }
}

/**
 * 演示有向图的不同表示方法
 */
void demonstrateDirectedGraphRepresentations() {
    std::cout << "\n########################################" << std::endl;
    std::cout << "######## 有向图表示方法演示 ########" << std::endl;
    std::cout << "########################################" << std::endl;
    
    // 创建一个有向图示例（《算法导论》图22.1）
    // 顶点: 0, 1, 2, 3, 4, 5
    // 边: (0,1), (0,4), (1,2), (1,3), (2,4), (3,2), (3,5), (4,3), (5,5)
    
    std::cout << "\n--- 创建邻接表表示的有向图 ---" << std::endl;
    DirectedAdjacencyListGraph adjListGraph(6);
    adjListGraph.addEdge(0, 1);
    adjListGraph.addEdge(0, 4);
    adjListGraph.addEdge(1, 2);
    adjListGraph.addEdge(1, 3);
    adjListGraph.addEdge(2, 4);
    adjListGraph.addEdge(3, 2);
    adjListGraph.addEdge(3, 5);
    adjListGraph.addEdge(4, 3);
    adjListGraph.addEdge(5, 5);  // 自环
    
    adjListGraph.printGraph();
    
    std::cout << "\n图信息:" << std::endl;
    std::cout << "顶点数: " << adjListGraph.getVertexCount() << std::endl;
    std::cout << "边数: " << adjListGraph.getEdgeCount() << std::endl;
    
    std::cout << "\n顶点度数信息:" << std::endl;
    for (int i = 0; i < 6; i++) {
        std::cout << "顶点 " << i << " 的出度: " << adjListGraph.getOutDegree(i) 
                  << ", 入度: " << adjListGraph.getInDegree(i) << std::endl;
    }
    
    std::cout << "\n边的存在性检查:" << std::endl;
    std::cout << "是否存在边 (0,1): " << (adjListGraph.hasEdge(0, 1) ? "是" : "否") << std::endl;
    std::cout << "是否存在边 (2,1): " << (adjListGraph.hasEdge(2, 1) ? "是" : "否") << std::endl;
    
    std::cout << "\n--- 创建邻接矩阵表示的有向图 ---" << std::endl;
    AdjacencyMatrixGraph adjMatrixGraph(6);
    adjMatrixGraph.addEdge(0, 1);
    adjMatrixGraph.addEdge(0, 4);
    adjMatrixGraph.addEdge(1, 2);
    adjMatrixGraph.addEdge(1, 3);
    adjMatrixGraph.addEdge(2, 4);
    adjMatrixGraph.addEdge(3, 2);
    adjMatrixGraph.addEdge(3, 5);
    adjMatrixGraph.addEdge(4, 3);
    adjMatrixGraph.addEdge(5, 5);  // 自环
    
    adjMatrixGraph.printGraph();
    
    std::cout << "\n图信息:" << std::endl;
    std::cout << "顶点数: " << adjMatrixGraph.getVertexCount() << std::endl;
    std::cout << "边数: " << adjMatrixGraph.getEdgeCount() << std::endl;
    
    std::cout << "\n顶点度数信息:" << std::endl;
    for (int i = 0; i < 6; i++) {
        std::cout << "顶点 " << i << " 的出度: " << adjMatrixGraph.getOutDegree(i) 
                  << ", 入度: " << adjMatrixGraph.getInDegree(i) << std::endl;
    }
    
    std::cout << "\n边的存在性检查:" << std::endl;
    std::cout << "是否存在边 (0,1): " << (adjMatrixGraph.hasEdge(0, 1) ? "是" : "否") << std::endl;
    std::cout << "是否存在边 (2,1): " << (adjMatrixGraph.hasEdge(2, 1) ? "是" : "否") << std::endl;
}

/**
 * 演示无向图的不同表示方法
 */
void demonstrateUndirectedGraphRepresentations() {
    std::cout << "\n########################################" << std::endl;
    std::cout << "######## 无向图表示方法演示 ########" << std::endl;
    std::cout << "########################################" << std::endl;
    
    // 创建一个无向图示例
    // 顶点: 0, 1, 2, 3
    // 边: (0,1), (0,2), (1,2), (2,3)
    
    std::cout << "\n--- 创建邻接表表示的无向图 ---" << std::endl;
    UndirectedAdjacencyListGraph undirectedGraph(4);
    undirectedGraph.addEdge(0, 1);
    undirectedGraph.addEdge(0, 2);
    undirectedGraph.addEdge(1, 2);
    undirectedGraph.addEdge(2, 3);
    
    undirectedGraph.printGraph();
    
    std::cout << "\n图信息:" << std::endl;
    std::cout << "顶点数: " << undirectedGraph.getVertexCount() << std::endl;
    std::cout << "边数: " << undirectedGraph.getEdgeCount() << std::endl;
    
    std::cout << "\n顶点度数信息:" << std::endl;
    for (int i = 0; i < 4; i++) {
        std::cout << "顶点 " << i << " 的度数: " << undirectedGraph.getDegree(i) << std::endl;
    }
}

/**
 * 演示图的遍历算法
 */
void demonstrateGraphTraversal() {
    std::cout << "\n########################################" << std::endl;
    std::cout << "######## 图的遍历算法演示 ########" << std::endl;
    std::cout << "########################################" << std::endl;
    
    // 创建一个简单的有向图
    DirectedAdjacencyListGraph graph(6);
    graph.addEdge(0, 1);
    graph.addEdge(0, 4);
    graph.addEdge(1, 2);
    graph.addEdge(1, 3);
    graph.addEdge(2, 4);
    graph.addEdge(3, 2);
    graph.addEdge(3, 5);
    graph.addEdge(4, 3);
    graph.addEdge(5, 5);
    
    BFS(graph, 0);
    DFSRecursive(graph, 0);
    DFSIterative(graph, 0);
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
    std::cout << "====== 图的表示方法演示程序 ======" << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "本程序演示了《算法导论》第22章22.1节中图的表示方法" << std::endl;
    std::cout << "包括邻接表和邻接矩阵两种表示方法" << std::endl;
    std::cout << "以及图的基本操作和遍历算法" << std::endl;
    
    demonstrateDirectedGraphRepresentations();
    demonstrateUndirectedGraphRepresentations();
    demonstrateGraphTraversal();
    
    std::cout << "\n程序执行完毕，感谢使用！" << std::endl;
    return 0;
}