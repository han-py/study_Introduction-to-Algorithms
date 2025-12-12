#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

/**
 * Matroid and Greedy Algorithm Implementation
 * 
 * This program demonstrates the concept of matroids and how greedy algorithms
 * can be used to solve optimization problems when the underlying structure
 * is a matroid.
 */

// Structure to represent an element with weight
struct Element {
    int id;
    int weight;
    
    Element(int id, int weight) : id(id), weight(weight) {}
    
    // For sorting in descending order of weights
    bool operator<(const Element& other) const {
        return weight > other.weight;
    }
};

// Matroid abstract base class
class Matroid {
public:
    virtual ~Matroid() = default;
    
    // Check if a set is independent
    virtual bool isIndependent(const std::set<int>& subset) const = 0;
    
    // Get all elements
    virtual const std::vector<Element>& getElements() const = 0;
};

// Graphic matroid implementation (based on graphs and forests)
class GraphicMatroid : public Matroid {
private:
    std::vector<Element> elements;
    std::vector<std::pair<int, int>> edges; // Pair of vertices for each edge
    int numVertices;
    
    // Union-Find data structure for cycle detection
    class UnionFind {
    private:
        std::vector<int> parent, rank;
        
    public:
        UnionFind(int n) {
            parent.resize(n);
            rank.resize(n, 0);
            for (int i = 0; i < n; i++) {
                parent[i] = i;
            }
        }
        
        int find(int x) {
            if (parent[x] != x) {
                parent[x] = find(parent[x]); // Path compression
            }
            return parent[x];
        }
        
        bool unite(int x, int y) {
            int rootX = find(x);
            int rootY = find(y);
            
            if (rootX == rootY) {
                return false; // Cycle detected
            }
            
            // Union by rank
            if (rank[rootX] < rank[rootY]) {
                std::swap(rootX, rootY);
            }
            parent[rootY] = rootX;
            if (rank[rootX] == rank[rootY]) {
                rank[rootX]++;
            }
            return true;
        }
    };
    
public:
    GraphicMatroid(const std::vector<Element>& elements, 
                  const std::vector<std::pair<int, int>>& edges, 
                  int numVertices) 
        : elements(elements), edges(edges), numVertices(numVertices) {}
    
    bool isIndependent(const std::set<int>& subset) const override {
        UnionFind uf(numVertices);
        
        // Check if adding these edges creates a cycle
        for (int edgeId : subset) {
            if (edgeId >= 0 && edgeId < (int)edges.size()) {
                auto edge = edges[edgeId];
                // If we cannot unite, it means there's a cycle
                if (!uf.unite(edge.first, edge.second)) {
                    return false;
                }
            }
        }
        return true;
    }
    
    const std::vector<Element>& getElements() const override {
        return elements;
    }
};

// Weighted matroid greedy algorithm
std::vector<Element> greedyAlgorithm(const Matroid& matroid) {
    // Get elements and sort by weight in descending order
    std::vector<Element> elements = matroid.getElements();
    std::sort(elements.begin(), elements.end());
    
    std::set<int> independentSet;
    std::vector<Element> result;
    
    std::cout << "🔧 执行加权拟阵贪心算法:\n";
    std::cout << "   排序后的元素: ";
    for (const auto& elem : elements) {
        std::cout << "(" << elem.id << "," << elem.weight << ") ";
    }
    std::cout << "\n\n";
    
    // Greedy selection
    for (const Element& element : elements) {
        std::set<int> tentativeSet = independentSet;
        tentativeSet.insert(element.id);
        
        std::cout << "   考虑添加元素 " << element.id << " (权重: " << element.weight << ")...";
        
        if (matroid.isIndependent(tentativeSet)) {
            independentSet.insert(element.id);
            result.push_back(element);
            std::cout << " ✅ 添加成功\n";
        } else {
            std::cout << " ❌ 添加失败（会破坏独立性）\n";
        }
    }
    
    return result;
}

// Helper function to print result
void printResult(const std::vector<Element>& result) {
    std::cout << "\n🏆 贪心算法结果:\n";
    std::cout << "   选中的元素: ";
    int totalWeight = 0;
    for (const auto& elem : result) {
        std::cout << elem.id << " ";
        totalWeight += elem.weight;
    }
    std::cout << "\n   总权重: " << totalWeight << "\n";
}

int main() {
#ifdef ACM_LOCAL
    freopen("data.in", "r", stdin);
    freopen("data.out", "w", stdout);
#endif
    std::cout << "🎓 算法导论第16.4节 - 拟阵与贪心算法\n";
    std::cout << "==========================================\n\n";
    
    std::cout << "📖 理论介绍:\n";
    std::cout << "   拟阵是一个有序对 M = (S, I)，满足:\n";
    std::cout << "   1. 如果 A ∈ I, B ⊆ A, 则 B ∈ I (遗传性)\n";
    std::cout << "   2. 如果 A ∈ I, B ∈ I 且 |A| < |B|, 则存在某个 x ∈ B - A 使得 A ∪ {x} ∈ I (交换性)\n\n";
    
    std::cout << "   当一个问题可以表示为拟阵时，贪心算法能够产生最优解!\n\n";
    
    // Example: Graphic matroid (finding maximum weight spanning forest)
    std::cout << "📊 示例: 图形拟阵 (最大权重生成森林)\n";
    std::cout << "   问题: 在加权无向图中找到最大权重的无环边集\n\n";
    
    // Create a sample graph
    // Vertices: 0, 1, 2, 3
    // Edges with weights:
    std::vector<Element> elements = {
        Element(0, 4), // Edge 0: (0,1) weight 4
        Element(1, 2), // Edge 1: (1,2) weight 2
        Element(2, 3), // Edge 2: (2,3) weight 3
        Element(3, 1), // Edge 3: (0,3) weight 1
        Element(4, 5)  // Edge 4: (1,3) weight 5
    };
    
    std::vector<std::pair<int, int>> edges = {
        {0, 1}, // Edge 0
        {1, 2}, // Edge 1
        {2, 3}, // Edge 2
        {0, 3}, // Edge 3
        {1, 3}  // Edge 4
    };
    
    std::cout << "   图的边集 (顶点对, 权重):\n";
    for (int i = 0; i < (int)elements.size(); i++) {
        std::cout << "   " << elements[i].id << ": (" << edges[i].first << "," 
                  << edges[i].second << ") 权重=" << elements[i].weight << "\n";
    }
    std::cout << "\n";
    
    GraphicMatroid graphicMatroid(elements, edges, 4);
    
    // Apply greedy algorithm
    std::vector<Element> result = greedyAlgorithm(graphicMatroid);
    
    printResult(result);
    
    std::cout << "\n✅ 算法完成! 贪心算法在这个拟阵实例中找到了最优解。\n";
    
    return 0;
}