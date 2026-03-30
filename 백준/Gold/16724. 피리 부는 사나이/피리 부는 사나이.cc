#include <iostream>

using namespace std;

const int dr[] = {-1, 0, 1, 0};
const int dc[] = {0, -1, 0, 1};
const int U = 0;
const int L = 1;
const int D = 2;
const int R = 3;

int map[1000][1000];
bool visited[1000][1000];
bool finished[1000][1000];
int ans;

void dfs(int row, int col) {
    int new_row = row + dr[map[row][col]];
    int new_col = col + dc[map[row][col]];

    visited[row][col] = true;

    if(!visited[new_row][new_col]) {
        dfs(new_row, new_col);
    }
    else if(!finished[new_row][new_col]) {
        ++ans;
    }

    finished[row][col] = true;

    return;
}

int main() {
    int N, M;
    cin >> N >> M;

    char tmp;
    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < M; ++j) {
            cin >> tmp;

            if(tmp == 'D') {map[i][j] = D;}
            else if(tmp == 'L') {map[i][j] = L;}
            else if(tmp == 'R') {map[i][j] = R;}
            else if(tmp == 'U') {map[i][j] = U;}
        }
    }

    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < M; ++j) {
            if(!visited[i][j]) {
                dfs(i, j);
            }
        }
    }

    cout << ans << endl;

    return 0;
}