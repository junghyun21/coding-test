#include <vector>
#include <queue>
#include <limits>
#include <algorithm>

using namespace std;

const int dr[] = {1, -1, 0, 0};
const int dc[] = {0, 0, 1, -1};

typedef struct Node {
    int r;
    int c;
    int d;
} Node;

int solution(vector<vector<int>> board) {
    int cost[27][27][4];
    int map[27][27];
    int n = board.size();
    
    fill(&cost[0][0][0], &cost[0][0][0] + 27 * 27 * 4, -1);
    fill(&map[0][0], &map[0][0] + 27 * 27, 1);
    
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j) {
            map[i + 1][j + 1] = board[i][j];
        }
    }
    
    queue<Node> q;
    q.push({1, 1, 0});
    q.push({1, 1, 2});
    
    cost[1][1][0] = 0;
    cost[1][1][2] = 0;
    
    while(!q.empty()) {
        auto [r, c, d] = q.front();
        q.pop();
        
        for(int i = 0; i < 4; ++i) {
            int new_r = r + dr[i];
            int new_c = c + dc[i];
            int new_cost = (i == d) ? cost[r][c][d] + 100 : cost[r][c][d] + 600;
            
            if(map[new_r][new_c] == 1) {
                continue;
            }
            
            if(cost[new_r][new_c][i] == -1 || cost[new_r][new_c][i] > new_cost) {
                cost[new_r][new_c][i] = new_cost;
                q.push({new_r, new_c, i});
            }
        }
    }
    
    int answer = numeric_limits<int>::max();
    for(int i = 0; i < 4; ++i) {
        if(cost[n][n][i] == -1) { 
            continue;
        }
        
        answer = (cost[n][n][i] < answer) ? cost[n][n][i] : answer;
    }
    
    return answer;
}