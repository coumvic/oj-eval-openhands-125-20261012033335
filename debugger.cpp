#include <vector>
#include <cstdio>
#include <algorithm>
#include <unordered_map>

// Fast input function for large input sizes
inline int readInt() {
    int x = 0;
    char c = getchar_unlocked();
    while (c < '0' || c > '9') {
        c = getchar_unlocked();
    }
    while (c >= '0' && c <= '9') {
        x = x * 10 + (c - '0');
        c = getchar_unlocked();
    }
    return x;
}

// Union-Find data structure with array-based implementation for better performance
class UnionFind {
private:
    std::vector<int> parent;
    std::vector<int> rank;
    int n;
    
public:
    UnionFind(int size) : n(size) {
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
    
    void unite(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        
        if (rootX != rootY) {
            // Union by rank
            if (rank[rootX] < rank[rootY]) {
                parent[rootX] = rootY;
            } else if (rank[rootX] > rank[rootY]) {
                parent[rootY] = rootX;
            } else {
                parent[rootY] = rootX;
                rank[rootX]++;
            }
        }
    }
    
    bool connected(int x, int y) {
        return find(x) == find(y);
    }
};

int main() {
    int t = readInt();
    
    while (t--) {
        int n = readInt();
        
        // Vectors to store all constraints for coordinate compression
        std::vector<int> variables;
        std::vector<std::pair<int, int>> equals;
        std::vector<std::pair<int, int>> not_equals;
        
        // Read all constraints
        bool valid = true;
        for (int i = 0; i < n; i++) {
            int x = readInt();
            int y = readInt();
            int e = readInt();
            
            // Handle the case where x == y
            if (x == y) {
                if (e == 0) {
                    // A variable cannot be not equal to itself
                    valid = false;
                }
                // If e == 1, x == x is always true, so we can ignore this constraint
                continue;
            }
            
            // Collect all variables for coordinate compression
            variables.push_back(x);
            variables.push_back(y);
            
            if (e == 1) {
                equals.push_back({x, y});
            } else {
                not_equals.push_back({x, y});
            }
        }
        
        // If we found an impossible constraint (x != x), output NO and skip the rest
        if (!valid) {
            printf("NO\n");
            continue;
        }
        
        // Coordinate compression
        std::sort(variables.begin(), variables.end());
        variables.erase(std::unique(variables.begin(), variables.end()), variables.end());
        
        // Create mapping from original variable to compressed index
        std::unordered_map<int, int> comp_map;
        for (size_t i = 0; i < variables.size(); i++) {
            comp_map[variables[i]] = static_cast<int>(i);
        }
        
        // Create union-find structure with compressed indices
        UnionFind uf(variables.size());
        
        // Process all equality constraints
        for (const auto& p : equals) {
            int x = comp_map[p.first];
            int y = comp_map[p.second];
            uf.unite(x, y);
        }
        
        // Check if any inequality constraint contradicts the equality constraints
        bool result = true;
        for (const auto& p : not_equals) {
            int x = comp_map[p.first];
            int y = comp_map[p.second];
            if (uf.connected(x, y)) {
                result = false;
                break;
            }
        }
        
        if (result) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }
    }
    
    return 0;
}