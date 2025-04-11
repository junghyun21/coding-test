#include <limits>
#include <queue>
#include <vector>

using namespace std;

const int INF = numeric_limits<int>::max();

struct Compare {
    bool operator()(const pair<int, int> &a, const pair<int, int> &b) {
        return a.second > b.second; // 오름 차순
    }  
};

vector<vector<pair<int, int>>> adjList; // <이웃한 지점, 가중치>

vector<int> calDistance(const int &size, const int &start) {
    vector<bool> visited(size, false);
    
    vector<int> distance(size, INF);
    distance[start] = 0;
    
    priority_queue<pair<int, int>, vector<pair<int, int>>, Compare> pq; // <현재 노드, 지금까지 요금>
    pq.push({start, 0});
    
    while(!pq.empty()) {
        int currNode = pq.top().first;
        int currDistance = pq.top().second;
        pq.pop();
        
        if(visited[currNode])
            continue;
        
        visited[currNode] = true;
        
        for(const auto &[v, w] : adjList[currNode]) {
            int newDistance = currDistance + w;
            
            if(newDistance < distance[v]) {
                distance[v] = newDistance;
                pq.push({v, newDistance});
            }
        }
    }
    
    return distance;
}

// n: 지점의 개수
// s: 출발 지점
// a,b: A와 B의 각각의 도착 지점
// fares: 지점 사이의 택시 요금 [지점, 지점, 예상 요금]
int solution(int n, int s, int a, int b, vector<vector<int>> fares) {
    int answer = INF;
    
    // 인접 리스트 초기화
    adjList.resize(n + 1);
    for(const auto &fare : fares) {
        adjList[fare[0]].emplace_back(fare[1], fare[2]);
        adjList[fare[1]].emplace_back(fare[0], fare[2]);
    }
    
    // S -> 합승 끝 지점 -> A or B
    // 출발지와 목적지를 서로 바꾸어도 요금은 동일
    // 'S/A/B -> 합승 끝 지점'의 합이 가장 적은 경우를 리턴
    vector<int> distance_a = calDistance(n + 1, a);
    vector<int> distance_b = calDistance(n + 1, b);
    vector<int> distance_s = calDistance(n + 1, s);
    
    for(int i = 1; i <= n; ++i) {
        answer = min(answer, distance_a[i] + distance_b[i] + distance_s[i]);
    }
    
    return answer;
}