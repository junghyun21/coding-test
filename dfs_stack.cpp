#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <stack>

using namespace std;

void solution(vector<pair<int, int>> graph, int start) {
    unordered_map<int, vector<int>> adjList;
    unordered_set<int> visited;
    stack<int> s;

    for(const auto &[u, v] : graph) {
        adjList[u].push_back(v);
        adjList[v].push_back(u); // 무방향 그래프인 경우
    }

    // 1. 시작 노드를 스택에 푸시
    s.push(start);

    while(!s.empty()) {
        // 2. 팝한 후 방문상태인지 확인
        int cur = s.top();
        s.pop();

        // 3-1. 방문처리가 된 경우에는 아무 작업도 하지 않음
        if(visited.find(cur) != visited.end()) {
            continue;
        }

        // 3-2. 방문처리가 안 된 경우에는 방문처리 후 인접 노드 푸시
        visited.insert(cur);

        for(const int &next : adjList[cur]) {
            s.push(next);
        }
    }

    // 4. 스택이 비었으면 작업 끝
    return;
}