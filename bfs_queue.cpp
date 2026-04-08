/*
    너비 우선 탐색으로 모든 그래프의 노드를 순회하는 함수 solution()
    - start: 시작노드
    - graph 배열: [출발 노드, 도착 노드] 쌍으로 들어있는 배열
    - 반환값: 시작 노드부터 모든 노드를 너비 우선 탐색으로 탐색한 경로가 순서대로 저장된 배열
    - 제약 조건
        : 노드의 최대 개수는 100개를 넘지 않음
        : 시작 노드부터 시작해서 모든 노드를 방문할 수 있는 경로가 항상 있음
        : 그래프의 각 노드는 숫자
*/

#include <queue>
#include <vector>
#include <unordered_map>
#include <unordered_set>

using namespace std;

vector<int> solution(vector<pair<int, int>> graph, int start) {
    vector<int> ans;
    unordered_map<int, vector<int>> adjList;
    unordered_set<int> visited;

    // 1. 인접 리스트 생성
    for(const auto &[u, v] : graph) {
        adjList[u].push_back(v);
    }

    queue<int> q;

    // 2. 시작 노드 방문
    q.push(start);
    visited.insert(start);
    ans.push_back(start);

    while(!q.empty()) {
        int cur = q.front();
        
        q.pop();
        //ans.push_back(cur);

        // 3. 현재 노드의 인접 노드 중 아직 방문하지 않은 노드 방문
        for(const int &edge : adjList[cur]) {
            if(visited.find(edge) == visited.end()) {
                q.push(edge);
                visited.insert(edge);
                ans.push_back(edge);
            }
        }
    }

    return ans;
}