#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>

using namespace std;

const int INF = numeric_limits<int>::max();

vector<vector<pair<int, int>>> adjList;

struct Compare {
    bool operator()(const pair<int, int> &a, const pair<int, int> &b) {
        return a.second > b.second;
    }
};

vector<int> distance(const int &size, const int &start)
{
    vector<bool> visited(size, false);
    vector<int> dist(size, INF);
    dist[start] = 0;

    // <정점 번호, 현재까지 거리>
    priority_queue<pair<int, int>, vector<pair<int, int>>, Compare> pq;
    pq.push({start, 0});

    while(!pq.empty()) {
        int currNode = pq.top().first;
        int currDist = pq.top().second;

        pq.pop();

        if(visited[currNode])
            continue;

        visited[currNode] = true;

        for(const auto &[v, d] : adjList[currNode]) {
            int newDist = dist[currNode] + d;
            if(newDist < dist[v]) {
                dist[v] = newDist;
                pq.push({v, newDist});
            }
        }
    }
    
    return dist;
}

int main()
{
    // 정점의 개수, 간선의 개수
    int N, E;
    cin >> N >> E;

    // 인접리스트 <정점, 거리>
    int a, b, c;

    adjList.resize(N + 1);
    for(int i = 0; i < E; ++i) {
        cin >> a >> b >> c;

        adjList[a].push_back({b, c});
        adjList[b].push_back({a, c});
    }

    // 반드시 거쳐야하는 정점
    int v1, v2;
    cin >> v1 >> v2;

    // 거리
    vector<int> dist_from_1 = distance(N + 1, 1); // 1 -> v1, v2
    vector<int> dist_from_N = distance(N + 1, N); // N -> v1, v2
    vector<int> dist_from_V = distance(N + 1, v1); // v1 -> v2

    if(dist_from_1[v1] == INF || dist_from_1[v2] == INF ||
       dist_from_N[v1] == INF || dist_from_N[v2] == INF || 
       dist_from_V[v2] == INF)
       cout << -1 << endl;
    else
        cout << min(dist_from_1[v1] + dist_from_N[v2], dist_from_1[v2] + dist_from_N[v1]) + dist_from_V[v2] << endl;

    return 0;
}