#include <iostream>
#include <vector>
#include <unordered_map>
#include <cstdio>

using namespace std;

// Union-Find data structure for handling equality constraints
class UnionFind {
private:
    unordered_map<int, int> parent;
    unordered_map<int, int> rank;
    
public:
    int find(int x) {
        if (parent.find(x) == parent.end()) {
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
    int t;
    scanf("%d", &t);
    
    while (t--) {
        int n;
        scanf("%d", &n);
        
        // Vectors to store equality and inequality constraints
        vector<pair<int, int>> equals;
        vector<pair<int, int>> not_equals;
        
        // Read all constraints
        for (int i = 0; i < n; i++) {
            int x, y, e;
            scanf("%d %d %d", &x, &y, &e);
            
            if (e == 1) {
                equals.push_back({x, y});
            } else {
                not_equals.push_back({x, y});
            }
        }
        
        // Create union-find structure
        UnionFind uf;
        
        // Process all equality constraints first
        for (auto& p : equals) {
            uf.unite(p.first, p.second);
        }
        
        // Check if any inequality constraint contradicts the equality constraints
        bool valid = true;
        for (auto& p : not_equals) {
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