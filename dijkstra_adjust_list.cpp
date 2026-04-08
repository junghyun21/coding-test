/*
    다익스트라 알고리즘을 구현하는 solution()
    - start: 시작노드
    - numNodes: 노드의 개수
    - edges 배열: [시작 노드, 도착 노드, 가중치] 형태로 간선의 정보를 담은 배열
    - 반환값: 시작노드 start부터 각 노드까지 최소비용을 담은 벡터 반환
    - 제약 조건
        : 노드의 최대 개수는 100개를 넘지 않음
        : 각 노드는 0 이상의 정수로 표현
        : 모든 가중치는 0 이상의 정수이며 10,000을 넘지 않음
*/

#include <vector>
#include <tuple>
#include <queue>
#include <limits>
#include <algorithm>

using namespace std;

const int INF = numeric_limits<int>::max();

struct Compare {
    bool operator()(const pair<int, int> &a, const pair<int, int> &b) {
        return a.second > b.second;
    }
};

vector<int> solution(int start, int numNodes, vector<tuple<int, int, int>> edges) {
    vector<vector<pair<int, int>>> ajdList(numNodes);     // [v, w]
    for(const auto &[u, v, w] : edges) {
        ajdList[u].emplace_back(v, w);
        // ajdList[u].emplace_back({v, w}); -> 오류
        // ajdList[u].push_back({v, w}); -> 가능
    }

    vector<int> distance(numNodes, INF);
    distance[start] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, Compare> pq;
    pq.push({start, 0});

    vector<bool> visited(numNodes, false);

    while(!pq.empty()) {
        int curNode = pq.top().first;
        int curDistance = pq.top().second;

        pq.pop();

        if(visited[curNode]) {
            continue;
        }
        visited[curNode] = true;

        for(const auto &[v, w] : ajdList[curNode]) {
            int newDistance = distance[curNode] + w;
            if(newDistance < distance[v]) {
                distance[v] = newDistance;
                pq.push({v, newDistance});
            }
        }
    }
    

    return distance;
}