#include <limits>
#include <queue>
#include <vector>

using namespace std;

const int INF = numeric_limits<int>::max();

struct Compare {
    bool operator()(const pair<int, int> &a, const pair<int, int> &b) {
        return a.second > b.second;
    }
};

// n: 총 지역 수
// roads: 두 지역을 왕복할 수 있는 길 정보
// sources: 각 부대원이 위치한 지역 정보
// destination: 강철 부대의 지역
vector<int> solution(int n, vector<vector<int>> roads, vector<int> sources, int destination) {
    vector<int> answer; // sources의 원소 순서대로 부대로 복귀할 수 있는 최단 시간
    
    // 인접 리스트 초기화
    vector<vector<int>> adjList(n + 1);
    for(const auto &road : roads) {
        adjList[road[0]].push_back(road[1]);
        adjList[road[1]].push_back(road[0]);
    }
    
    vector<bool> visited(n + 1, false);
    vector<int> distance(n + 1, INF);
    distance[destination] = 0;
    
    priority_queue<pair<int, int>, vector<pair<int, int>>, Compare> pq;
    pq.push({destination, 0}); // <현재 노드, 지금까지의 거리>
    
    // destination에서부터 sources 내 요소들 간의 최단 경로
    while(!pq.empty()) {
        int currNode = pq.top().first;
        int currDistance = pq.top().second;
        pq.pop();
        
        if(visited[currNode])
            continue;
        
        visited[currNode] = true;
        
        for(const auto &v : adjList[currNode]) {
            int newDistance = 1 + currDistance;
            
            if(newDistance < distance[v]) {
                distance[v] = newDistance;
                pq.push({v, newDistance});
            }
        }
    }
    
    for(const auto &source : sources) {
        answer.push_back(distance[source] == INF ? -1 : distance[source]);
    }
    
    return answer;
}