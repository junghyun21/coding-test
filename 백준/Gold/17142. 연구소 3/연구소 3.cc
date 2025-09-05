#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

const int dr[] = {-1, 1, 0, 0};
const int dc[] = {0, 0, -1, 1};
const int INF = 10000;

typedef struct point {
    int r;
    int c;
    int time;
} Point;

vector<vector<int>> map;
vector<pair<int, int>> virus;
int N, M;
int road;
int ans;

void solution(vector<int> activated, int cnt, int idx);
int bfs(const vector<int> &activated);

int main() {
    ans = INF;

    cin >> N >> M;
    
    map.resize(N + 2, vector<int>(N + 2, 1));
    for(int i = 1; i <= N; ++i) {
        for(int j = 1; j <= N; ++j) {
            cin >> map[i][j];
            
            if(map[i][j] == 0) {
                ++road;
            }
            else if(map[i][j] == 2) {
                virus.push_back({i, j});
            }
        }
    }
    
    if(road == 0) {
        cout << 0 << endl;
    }
    else {
        solution(vector<int>(), 0, 0);
        
        cout << ((ans == INF) ? -1 : ans) << endl;
    }

    return 0;
}

void solution(vector<int> activated, int cnt, int idx) {
    if(cnt == M) {
        int res = bfs(activated);
        ans = min(ans, res);

        return ;
    }

    if(idx < virus.size()) {
        activated.push_back(idx);
        solution(activated, cnt + 1, idx + 1);
        activated.pop_back();

        solution(activated, cnt, idx + 1);
    }
    
    return;
}

int bfs(const vector<int> &activated) {
    vector<vector<bool>> visited(N + 2, vector<bool>(N + 2));
    queue<Point> q;
    int res = 0;
    int cnt = 0;
    
    for(const auto &idx : activated) {
        int r = virus[idx].first;
        int c = virus[idx].second;

        q.push({r, c, 0});

        visited[r][c] = true;
    }

    while(!q.empty()) {
        Point p = q.front();
        q.pop();

        res = max(res, p.time);

        for(int i = 0; i < 4; ++i) {
            int new_r = p.r + dr[i];
            int new_c = p.c + dc[i];

            if(visited[new_r][new_c] || map[new_r][new_c] == 1) {
                continue;
            }
            visited[new_r][new_c] = true;
            
            if(map[new_r][new_c] == 0) {
                ++cnt;

                if(cnt == road) {
                    return p.time + 1;
                }
            }

            q.push({new_r, new_c, p.time + 1});
        }
    }

    return INF;
}