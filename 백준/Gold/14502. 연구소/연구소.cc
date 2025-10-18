#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int BLANK = 0;
const int WALL = 1;
const int VIRUS = 2;

const int dr[] = {-1, 1, 0, 0};
const int dc[] = {0, 0, -1, 1};

vector<vector<int>> map;
vector<vector<bool>> visited;
vector<pair<int, int>> virus;
vector<pair<int, int>> blank;
int safe;
int N, M;
int answer;

void dfs(int idx, int num);
int solution();

int main() {
    cin >> N >> M;

    map.resize(N + 2, vector<int>(M + 2, 1));
    for(int i = 1; i <= N; ++i) {
        for(int j = 1; j <= M; ++j) {
            cin >> map[i][j];

            if(map[i][j] == BLANK) {
                ++safe;
                blank.push_back({i, j});
            }
            else if(map[i][j] == VIRUS) {
                virus.push_back({i , j});
            }

        }
    }

    dfs(0, 0);

    cout << answer << endl;

    return 0;
}

void dfs(int idx, int num) {
    if(num == 3) {
        int temp = solution();
        answer = (temp > answer) ? temp : answer;

        return;
    }

    for(int i = idx; i < blank.size(); ++i) {
        int r = blank[i].first;
        int c = blank[i].second;

        map[r][c] = WALL;
        --safe;

        dfs(i + 1, num + 1);

        ++safe;
        map[r][c] = BLANK;
    }
}

int solution() {
    queue<pair<int, int>> q;
    int res = safe;

    visited.assign(N + 2, vector<bool>(M + 2, false));

    for(const auto &v : virus) {
        visited[v.first][v.second] = true;
        q.push({v.first, v.second});

        while(!q.empty()) {
            int cr = q.front().first;
            int cc = q.front().second;  

            q.pop();

            for(int i = 0; i < 4; ++i) {
                int nr = cr + dr[i];
                int nc = cc + dc[i];

                if(visited[nr][nc] || map[nr][nc] != BLANK) {
                    continue;
                }

                visited[nr][nc] = true;
                --res;

                q.push({nr, nc});
            }
        }
    }

    return res;
}
