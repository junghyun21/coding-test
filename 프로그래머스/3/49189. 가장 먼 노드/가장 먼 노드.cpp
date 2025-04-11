#include <algorithm>
#include <queue>
#include <limits>
#include <vector>

using namespace std;

// 현재 거리(가중치)에 따라 오름차순으로 정렬
struct Compare {
    bool operator()(const pair<int, int> &a, const pair<int, int> &b) {
        return a.second > b.second; // 작은 값부터 먼저 꺼냄 -> 오름차순
    }
};

// n: 노드의 개수
// edge: 연결된 두 개의 노드
int solution(int n, vector<vector<int>> edge) {
    // 연결 리스트 생성
    vector<vector<int>> adjList(n + 1);
    for(const auto &e : edge) {
        adjList[e[0]].push_back(e[1]);
        adjList[e[1]].push_back(e[0]);
    }
    
    // 방문 여부와 총 거리
    vector<bool> visited(n + 1, false);
    vector<int> distance(n + 1, numeric_limits<int>::max());
    distance[1] = 0;
    
    // (현재 방문한 노드, 지금까지의 거리)
    priority_queue<pair<int, int>, vector<pair<int, int>>, Compare> pq;
    pq.push({1, 0});
    
    while(!pq.empty()) {
        int currNode = pq.top().first;
        int currDistance = pq.top().second;
        pq.pop();
        
        if(visited[currNode])
            continue;
        
        visited[currNode] = true;
        
        for(const auto &v: adjList[currNode]) {
            int newDistance = 1 + currDistance;
            
            if(newDistance < distance[v]) {
                distance[v] = newDistance;
                pq.push({v, newDistance});
            }
        }
    }
    
    int farDistance = -1;
    for(int i = 1; i <= n; ++i) {
        farDistance = max(farDistance, distance[i]);
    }
    
    return count(distance.begin(), distance.end(), farDistance);
}