// 다익스트라 알고리즘: 가중치가 있는 그래프의 최단 경로를 구하는 문제 (음의 가중치가 없을 때)

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
#include <limits>
#include <algorithm>

using namespace std;

const int MAX_NODES = 100;
const int INF = numeric_limits<int>::max();
int graph[100][100];
bool visited[100];

vector<int> solution(int start, int numNodes, vector<tuple<int, int, int>> edges) {
    // 1. 그래프 및 방문 여부 초기화
    for(int i = 0; i < MAX_NODES; ++i) {
        fill_n(graph[i], MAX_NODES, INF);
        visited[i] = false;
    }

    // 2. 입력받은 간선 정보를 그래프로 표현
    for(const auto &[u, v, w] : edges) {
        graph[u][v] = w;
    }

    // 3. 시작 노드를 제외한 모든 노드의 최소 비용을 INF로 초기화
    vector<int> distance(numNodes, INF);
    distance[start] = 0;

    for(int i = 0; i < numNodes - 1; ++i) {
        int minDistance = INF;
        int closestNode = -1;

        // 4. 최소 거리 노드 찾기
        for(int j = 0; j < numNodes; ++j) {
            if(!visited[j] && distance[j] < minDistance) {
                minDistance = distance[j];
                closestNode = j;
            }
        }

        // 5. 찾은 노드를 방문 처리
        visited[closestNode] = true;

        // 6. 인접 노드에 대한 거리 업데이트
        for(int j = 0; j < numNodes; ++j) {
            int newDistance = distance[closestNode] + graph[closestNode][j];

            if(!visited[j] && graph[closestNode][j] != INF && newDistance < distance[j]) {
                distance[j] = newDistance;
            }
        }
    }

    return distance;
}