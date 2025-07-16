#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

// 상: 0, 우: 1, 하: 2, 좌: 3
const int dx[] = {0, 1, 0, -1};
const int dy[] = {-1, 0, 1, 0};

vector<vector<int>> Map;
int N, M;
int ans;

void dfs(int cal, int row, int cnt);
void check_road(vector<pair<int, int>> &visited, int cal, int row, int idx);
void uncheck_road(vector<pair<int, int>> &visited);

int main() {
    int Road = 0;

    cin >> N >> M;

    Map.resize(N + 2, vector<int>(M + 2, 6)); // 모두 벽(6)으로 초기화

    for(int i = 1; i <= N; ++i) {
        for(int j = 1; j <= M; ++j) {
            cin >> Map[i][j];

            if(Map[i][j] == 0) {
                ++Road;
            }
        }
    }

    ans = Road;
    dfs(1, 1, Road);

    cout << ans << endl;

    return 0;
}

void dfs(int cal, int row, int cnt) {
    if(cal > N || cnt == 0) {
        ans = min(ans, cnt);
        return;
    }

    int new_c = cal;
    int new_r = row + 1;

    if(new_r > M) {
        new_r = 1;
        ++new_c;
    }
    
    vector<pair<int, int>> visited;
    switch(Map[cal][row]) {
        case 1:
            for(int i = 0; i < 4; ++i) {
                check_road(visited, cal, row, i);
                dfs(new_c, new_r, cnt - visited.size());
                uncheck_road(visited);
            }
            break;

        case 2:
            for(int i = 0; i < 2; ++i) {
                for(int j = 0; j < 2; ++j) {
                    int idx = i + j * 2;
                    check_road(visited, cal, row, idx);
                }
                dfs(new_c, new_r, cnt - visited.size());
                uncheck_road(visited);
            }
            break;

        case 3:
            for(int i = 0; i < 4; ++i) {       
                // CCTV가 바라보는 방향 중 길(0)이 있으면 감시했음을 표시
                // 벽 뒤부터는 더 이상 감시 불가
                for(int j = 0; j < 2; ++j) {
                    int idx = (i + j >= 4) ? (j + i) % 4 : i + j; 
                    check_road(visited, cal, row, idx);
                }
                dfs(new_c, new_r, cnt - visited.size());
                uncheck_road(visited);
            }
            break;

        case 4:
            for(int i = 0; i < 4; ++i) {   
                // CCTV가 바라보는 방향 중 길(0)이 있으면 감시했음을 표시
                // 벽 뒤부터는 더 이상 감시 불가
                for(int j = 0; j < 3; ++j) {
                    int idx = (i + j >= 4) ? (j + i) % 4 : i + j; 
                    check_road(visited, cal, row, idx);
                }
                dfs(new_c, new_r, cnt - visited.size());
                uncheck_road(visited);
            }
            break;
            
        case 5:
            for(int i = 0; i < 4; ++i) {
                check_road(visited, cal, row, i);
            } 
            dfs(new_c, new_r, cnt - visited.size());
            uncheck_road(visited);
            break;

        default:
            dfs(new_c, new_r, cnt);
            break;
    }



    return;
}

void check_road(vector<pair<int, int>> &visited, int cal, int row, int idx) {
    while(Map[cal][row] != 6) {
        if(Map[cal][row] == 0) {
            Map[cal][row] = -1; // 감시했음을 표시
            visited.push_back({cal, row});
        }

        cal += dy[idx];
        row += dx[idx];
    }

    return;
}

void uncheck_road(vector<pair<int, int>> &visited) {
    for(auto v : visited) {
        Map[v.first][v.second] = 0;
    }
    visited.resize(0);

    return;
}           