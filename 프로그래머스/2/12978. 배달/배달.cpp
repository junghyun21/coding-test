#include <vector>
#include <queue>
#include <limits>

using namespace std;

const int INF = numeric_limits<int>::max();

struct Compare {
    bool operator()(const pair<int, int> &a, const pair<int, int> &b) {
        return a.second > b.second;
    }  
};

int solution(int N, vector<vector<int>> road, int K) {    
    vector<vector<pair<int, int>>> adjList(N + 1);      // adjList[u] -> <v, w>
    for(const auto &r : road) {
        adjList[r[0]].emplace_back(r[1], r[2]);
        adjList[r[1]].emplace_back(r[0], r[2]);
    }
    
    vector<bool> visited(N + 1);
    vector<int> time(N + 1, INF);
    priority_queue<pair<int, int>, vector<pair<int, int>>, Compare> pq;
    
    pq.push({1, 0});
    time[1] = 0;
    
    while(!pq.empty()) {
        int curNode = pq.top().first;
        int curTime = pq.top().second;
        
        pq.pop();
        
        if(visited[curNode]) {
            continue;
        }
        
        visited[curNode] = true;
        
        for(const auto &[v, w] : adjList[curNode]) {
            int newTime = curTime + w;
            if(newTime < time[v]) {
                time[v] = newTime;
                pq.push({v, newTime});
            }
        }
    }
    
    int answer = 0;
    for(int i = 1; i <= N; ++i) {
        if(time[i] <= K) {
            ++answer;
        }
    }
    
    return answer;
}