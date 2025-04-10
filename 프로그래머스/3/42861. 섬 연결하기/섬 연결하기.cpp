#include <vector>
#include <algorithm>

using namespace std;

vector<int> g_parents;

int findRoot(int x) {
    // 자신의 노드와 부모 노드가 같은 경우 == 루트 노드인 경우
    if(x == g_parents[x])
        return x;
    
    g_parents[x] = findRoot(g_parents[x]);
    
    return g_parents[x];
}

// costs[i][0], costs[i][1]: 연결 된 두 섬의 번호
// costs[i][2]: 두 섬을 연결하는 다리를 건설할 때 드는 비용
// -> 모든 섬이 통행할 때 가능한 최소 비용
int solution(int n, vector<vector<int>> costs) {
    int answer = 0;
    
    // 각 섬이 연결되지 않은 상태
    // 우선은 자신의 부모 노드를 자신으로 지정
    for(int i = 0; i < n; ++i) {
        g_parents.push_back(i);
    }
    
    // 비용에 따라 오름차순으로 정렬
    // 비용이 낮은 것부터 접근하여 연결하면 비용이 최소가 될 확률이 높음
    sort(costs.begin(), costs.end(), [](vector<int> a, vector<int> b) {
        return a[2] < b[2];
    });
    
    // 섬 연결
    for(int i = 0; i < costs.size(); ++i) {
        // 이미 연결되어 있는 섬인지 확인 -> 루트 노드가 동일한지 확인
        int root1 = findRoot(costs[i][0]);
        int root2 = findRoot(costs[i][1]);

        // 연결되지 않았다면 연결 (root1을 root2에 연결 -> root2가 최종 루트 노드)
        // 연결한 다리의 비용 리턴
        if(root1 != root2) {
            answer += costs[i][2];
            g_parents[root1] = root2;
        }
    }
    
    return answer;
}