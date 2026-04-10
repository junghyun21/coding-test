#include <vector>
#include <algorithm>
#include <limits>
#include <cmath>

using namespace std;

int dfs(int cur, int parent, const vector<vector<int>> &tree) {
    int cnt = 1;
    
    for(const int &child : tree[cur]) {
        if(child != parent) {
            cnt += dfs(child, cur, tree);
        }
    }
    
    return cnt;
}

int solution(int n, vector<vector<int>> wires) {
    vector<vector<int>> tree(n + 1);
    for(const auto &wire : wires) {
        tree[wire[0]].emplace_back(wire[1]);
        tree[wire[1]].emplace_back(wire[0]);
    }
    
    int min_diff = numeric_limits<int>::max();
    for(const auto &wire : wires) {
        int u = wire[0];
        int v = wire[1];
        
        tree[u].erase(remove(tree[u].begin(), tree[u].end(), v), tree[u].end());
        tree[v].erase(remove(tree[v].begin(), tree[v].end(), u), tree[v].end());
        
        int u_cnt = dfs(u, v, tree);
        int v_cnt = n - u_cnt;
        
        min_diff = min(min_diff, abs(u_cnt - v_cnt));
        
        tree[u].emplace_back(v);
        tree[v].emplace_back(u);
    }
    
    return min_diff;
}