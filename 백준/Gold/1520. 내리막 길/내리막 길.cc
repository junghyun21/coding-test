#include <iostream>
#include <vector>

using namespace std;

const int INF = 10001;
const int dc[] = {1, -1, 0, 0};
const int dr[] = {0, 0, 1, -1};

vector<vector<int>> cnt;
vector<vector<int>> map;
int M, N;

int dfs(int row, int col);

int main() {
    cin >> M >> N;

    cnt.assign(M + 2, vector<int>(N + 2));
    map.assign(M + 2, vector<int>(N + 2, INF));
    for(int i = 1; i <= M; ++i) {
        for(int j = 1; j <= N; ++j) {
            cin >> map[i][j];
        }
    }

    (void)dfs(1, 1);

    cout << ((cnt[1][1] == -1) ? 0 : cnt[1][1]) << endl;

    return 0;
}

int dfs(int row, int col) {
    if(row == M && col == N) {
        return 1;
    }

    if(cnt[row][col] > 0) {
        return cnt[row][col];
    }

    for(int i = 0; i < 4; ++i) {
        int new_row = row + dr[i];
        int new_col = col + dc[i];

        if(cnt[new_row][new_col] >= 0 && map[new_row][new_col] < map[row][col]) {
            int res = dfs(new_row, new_col);
            
            if(res > 0) {
                cnt[row][col] += res;
            }
        }
    }

    if(cnt[row][col] == 0) {
        cnt[row][col] = -1;
    }
    
    return cnt[row][col];
}