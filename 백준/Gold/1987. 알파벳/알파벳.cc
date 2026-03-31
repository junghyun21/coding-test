#include <iostream>

using namespace std;

const int dr[] = {1, -1, 0, 0};
const int dc[] = {0, 0, 1, -1};

char map[22][22];
bool has_alphabet[26];
int ans;

void dfs(int row, int col, int cnt) {
    int idx = map[row][col] - 'A';
    
    if(has_alphabet[idx] || map[row][col] == '\0') {
        ans = (ans < cnt) ? cnt : ans; 
        return;
    }

    has_alphabet[idx] = true;

    for(int i = 0; i < 4; ++i) {
        int new_row = row + dr[i];
        int new_col = col + dc[i];

        dfs(new_row, new_col, cnt + 1);
    }

    has_alphabet[idx] = false;

    return;
}

int main() {
    int R, C;

    cin >> R >> C;

    for(int i = 1; i <= R; ++i) {
        for(int j = 1; j <= C; ++j) {
            cin >> map[i][j];
        }
    }

    dfs(1, 1, 0);

    cout << ans << endl;

    return 0;
}