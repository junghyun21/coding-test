#include <algorithm>
#include <vector>

using namespace std;

vector<int> parent;

int find(int x) {
    if(x == parent[x])
        return x;
    
    return parent[x] = find(parent[x]);
}

int solution(int n, vector<vector<int>> computers) {
    for(int i = 0; i < n; ++i) {
        parent.push_back(i);
    }
    
    for(int i = 0; i < n; ++i) {
        int root = find(i);
        
        for(int j = i + 1; j < n; ++j) {
            if(computers[i][j]) {
                int temp = find(j);
                
                if(temp != root)
                    parent[temp] = root;
            }
        }
    }
    
    // 최종적으로 각 원소의 대표(root)를 갱신
    // 집합들을 합치는 과정에서 경로 단축을 하지 않았기 때문
    for (int i = 0; i < n; ++i) {
        parent[i] = find(i);
    }
    
    sort(parent.begin(), parent.end());
    parent.erase(unique(parent.begin(), parent.end()), parent.end());
    
    return parent.size();
}