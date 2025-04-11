#include <algorithm>
#include <queue>
#include <limits>
#include <vector>

using namespace std;

const int INF = numeric_limits<int>::max();

// 가중치에 따라 오름차순 정렬
struct Compare {
    bool operator()(const pair<int, int> &a, const pair<int, int> &b) {
        return a.second > b.second;
    }  
};

// N: 마을의 개수 (1 ~ 50)
// road: 각 마을을 연결하는 도로의 정보 (1 ~ 2,000), (마을 번호, 마을 번호, 가중치)
// K: 음식 배달이 가능한 시간 (1 ~ 500,000)
int solution(int N, vector<vector<int>> road, int K) {
    int answer = 0;

    // 인접 리스트 생성 <이웃 정점, 가중치>
    vector<vector<pair<int, int>>> adjList(N + 1); 
    for(const auto &r : road) {
        adjList[r[0]].emplace_back(r[1], r[2]);
        adjList[r[1]].emplace_back(r[0], r[2]);
    }
    
    // 방문 여부와 거리
    vector<bool> visited(N + 1, false);
    vector<int> distance(N + 1, INF);
    distance[1] = 0;
    
    // 우선 순위 큐에 인접한 노드 중 가중치가 적은 순으로 저장
    priority_queue<pair<int, int>, vector<pair<int, int>>, Compare> pq;
    pq.push({1, 0});
    
    // 다익스트라 알고리즘을 통해 1번 마을부터 모든 마을까지의 거리 구함
    while(!pq.empty()) {
        int currNode = pq.top().first;
        int currDistance = pq.top().second;
        pq.pop();
        
        if(visited[currNode])
            continue;
        
        visited[currNode] = true;
        
        for(const auto &[v, w] : adjList[currNode]) {
            int newDistance = distance[currNode] + w;
            
            if(newDistance < distance[v]) {
                distance[v] = newDistance;
                pq.push({v, newDistance});
            }
        }
        
    }
    
    for(int i = 1; i <= N; ++i) {
        if(distance[i] <= K) {
            ++answer;
        }
    }

    return answer;
}