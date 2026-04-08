#include <vector>
#include <unordered_set>

using namespace std;

int roots[200];
int ranks[200];

int find(int node) {
    if(node != roots[node]) {
        roots[node] = find(roots[node]);
    }
    
    return roots[node];
}

void union_root(int x, int y) {
    int rootX = find(x);
    int rootY = find(y);
    
    if(rootX != rootY) {
        roots[rootX] = rootY;
    }
    
    return;
}

int solution(int n, vector<vector<int>> computers) {
    for(int i = 0; i < n; ++i) {
        roots[i] = i;
    }
    
    for(int i = 0; i < n - 1; ++i) {
        for(int j = i + 1; j < n; ++j) {
            if(computers[i][j]) {
                union_root(i, j);
            }
        }
    }
    
    for(int i = 0; i < n; ++i) {
        find(i);     // 최종 경로 단축
    }
    
    unordered_set<int> root_set;
    for(int i = 0; i < n; ++i) {
        root_set.insert(roots[i]);
    }
    
    return root_set.size();
}