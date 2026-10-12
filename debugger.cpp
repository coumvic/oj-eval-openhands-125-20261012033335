#include <vector>
#include <cstdio>
#include <unordered_map>

// Union-Find data structure for handling equality constraints with optimized performance
class UnionFind {
private:
    std::unordered_map<int, int> parent;
    std::unordered_map<int, int> rank;
    
public:
    int find(int x) {
        auto it = parent.find(x);
        if (it == parent.end()) {
            parent[x] = x;
            rank[x] = 0;
            return x;
        }
        
        if (parent[x] != x) {
            parent[x] = find(parent[x]); // Path compression
        }
        return parent[x];
    }
    
    void unite(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        
        if (rootX != rootY) {
            // Union by rank
            auto rankX = rank[rootX];
            auto rankY = rank[rootY];
            
            if (rankX < rankY) {
                parent[rootX] = rootY;
            } else if (rankX > rankY) {
                parent[rootY] = rootX;
            } else {
                parent[rootY] = rootX;
                rank[rootX] = rankX + 1;
            }
        }
    }
    
    bool connected(int x, int y) {
        return find(x) == find(y);
    }
};

int main() {
    int t;
    scanf("%d", &t);
    
    while (t--) {
        int n;
        scanf("%d", &n);
        
        // Create union-find structure
        UnionFind uf;
        
        // Vectors to store inequality constraints for later checking
        std::vector<std::pair<int, int>> not_equals;
        
        // Read all constraints and process equality constraints immediately
        for (int i = 0; i < n; i++) {
            int x, y, e;
            scanf("%d %d %d", &x, &y, &e);
            
            if (e == 1) {
                uf.unite(x, y);
            } else {
                not_equals.push_back({x, y});
            }
        }
        
        // Check if any inequality constraint contradicts the equality constraints
        bool valid = true;
        for (const auto& p : not_equals) {
            if (uf.connected(p.first, p.second)) {
                valid = false;
                break;
            }
        }
        
        if (valid) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }
    }
    
    return 0;
}