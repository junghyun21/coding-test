#include <vector>
#include <limits>
#include <queue>
#include <algorithm>

using namespace std;

const int INF = numeric_limits<int>::max();
const int dx[4] = {0, 0, -1, 1};
const int dy[4] = {-1, 1, 0, 0};

typedef struct Node {
    int x;
    int y;
    int cost;
    int direct;
} Node;

int solution(vector<vector<int>> board) {
    int N = board.size();
    
    int new_board[N + 2][N + 2];
    int cost[4][N + 2][N + 2]; // 0: 위, 1: 아래, 2: 왼쪽, 3: 오른쪽
    
    fill(&new_board[0][0], &new_board[0][0] + (N + 2) * (N + 2), 1);
    fill(&cost[0][0][0], &cost[0][0][0] + 4 * (N + 2) * (N + 2), INF);
    
    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < N; ++j) {
            new_board[i + 1][j + 1] = board[i][j];
        }
    }

    queue<Node> q;
    q.push({1, 1, 0, 3}); // 오른쪽 방향으로 출발
    q.push({1, 1, 0, 1}); // 아래 방향으로 출발
    
    for(int i = 0; i < 4; ++i) {
        cost[i][1][1] = 0;
    }
    
    while(!q.empty()) {
        Node curr = q.front();
        q.pop();
        
        // 도착지라면 더 이상 경로 탐색하지 않음
        if(curr.x == N && curr.y == N) {
            continue;
        }
        
        // 좌,우,위,아래 방향으로 경로 탐색
        for(int i = 0; i < 4; ++i) {
            int new_x = curr.x + dx[i];
            int new_y = curr.y + dy[i];
            int new_cost = (curr.direct == i) ? curr.cost + 100 : curr.cost + 600;
            
            // 벽이라면 탐색하지 않음
            if(new_board[new_y][new_x]) {
                continue;
            }
            
            // 비용이 더 저렴한 경우 최소값 갱신
            if(cost[i][new_y][new_x] > new_cost) {
                cost[i][new_y][new_x] = new_cost;
                q.push({new_x, new_y, new_cost, i});
            }
            
        }
    }
    
    int answer = INF;
    for(int i = 0; i < 4; ++i) {
        answer = min(answer, cost[i][N][N]);
    }
    
    return answer;
}