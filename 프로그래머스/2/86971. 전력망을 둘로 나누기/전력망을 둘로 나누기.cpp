#include <vector>
#include <iostream>

using namespace std;

vector<vector<int>> adj;
vector<int> node_cnt;
vector<bool> visited;

void dfs(const int &n, const int &curr, int &answer) {    
    visited[curr] = true;
    
    for(int i = 0; i < adj[curr].size(); ++i) {
        int child = adj[curr][i];
        
        if(visited[child]) {
            continue;
        }
        
        visited[child] = true;
        dfs(n, child, answer);
        
        node_cnt[curr] += node_cnt[child];
    }
    
    int power1 = node_cnt[curr];
    int power2 = n - node_cnt[curr];
    int diff = power1 > power2 ? power1 - power2 : power2 - power1;
    
    answer = min(answer, diff);

    return;
}

int solution(int n, vector<vector<int>> wires) {   
    int answer = n;
    
    // 리프노드(root)부터 시작 -> 1 <-> n-1, 2 <-> n-2, ...
    // 1. 인접리스트 만들기
    adj.resize(n + 1);
    for(const auto &wire : wires) {
        adj[wire[0]].push_back(wire[1]);
        adj[wire[1]].push_back(wire[0]);
    }
    
    // 2. 각 노드들의 자식 개수 구한 후, 전력망 나누면서 차이 값 비교 (dfs)
    visited.resize(n + 1);
    node_cnt.resize(n + 1, 1);
    
    dfs(n, 1, answer);
    
    return answer;
}