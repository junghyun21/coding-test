/*
    깊이 우선 탐색으로 모든 그래프의 노드를 순회하는 함수 solution()
    - start: 시작노드
    - graph 배열: [출발 노드, 도착 노드] 쌍으로 들어있는 배열
    - 반환값: 시작 노드부터 모든 노드를 깊이 우선 탐색으로 탐색한 경로가 순서대로 저장된 배열
    - 제약 조건
        : 노드의 최대 개수는 100개를 넘지 않음
        : 시작 노드부터 시작해서 모든 노드를 방문할 수 있는 경로가 항상 있음
        : 그래프의 각 노드는 대문자 알파벳 문자임
*/

#include <vector>
#include <unordered_map>
#include <unordered_set>

using namespace std;

unordered_map<char, vector<char>> adjList;
unordered_set<char> visited;
vector<char> ans;

void dfs(char node) {
    // 3. 현재 노드를 방문한 노드 및 경로에 추가
    ans.push_back(node);
    visited.insert(node);

    // 4. 현재 노드와 인접한 노드 중 방문하지 않은 노드에 대해 깊이 우선 탐색 진행
    for(const char &next : adjList[node]) {
        if(visited.find(next) == visited.end()) {
            dfs(next);
        }
    }

    return;
}

vector<char> solution(vector<pair<char, char>> graph, char start) { 
    // 1. 인접 리스트 생성
    for(const auto &edge : graph) {
        int u = edge.first;
        int v = edge.second;
        adjList[u].push_back(v);
    }

    // 2. 시작 노드부터 깊이 우선 탐색 시작
    dfs(start);

    return ans;
}