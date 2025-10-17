#include <iostream>
#include <vector>

using namespace std;

typedef struct Ice {
    int r;
    int c;
    int &h;

    Ice(int rr, int cc, int &hh) : r(rr), c(cc), h(hh) {}
} Ice;

const int dr[4] = {-1, 1, 0, 0};
const int dc[4] = {0, 0, -1, 1};

vector<vector<int>> map;
vector<vector<bool>> visited;
vector<Ice> ice;
int ice_cnt;
int ice_idx;
int N, M;

void dfs(int r, int c, int &visited_cnt);
void melt();

int main() {
    int year = 0;
    
    cin >> N >> M;
    
    map.resize(N, vector<int>(M));
    visited.resize(N, vector<bool>(M));

    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < M; ++j) {
            cin >> map[i][j];
            
            if(map[i][j] != 0) {
                ice.push_back({i, j, map[i][j]});
            }
        }
    }
    ice_cnt = ice.size();

    while(ice_cnt > 0) {
        int visited_cnt = 0;

        ++year;
        
        melt();
        visited.assign(N, vector<bool>(M, false));
        dfs(ice[ice_idx].r, ice[ice_idx].c, visited_cnt);
        
        if(ice_cnt != visited_cnt) {
            break;
        }

    }

    cout << ((ice_cnt == 0) ? 0 : year) << endl;

    return 0;
}

void dfs(int r, int c, int &visited_cnt) {
    visited[r][c] = true;
    ++visited_cnt;

    for(int i = 0; i < 4; ++i) {
        int nr = r + dr[i];
        int nc = c + dc[i];

        if(visited[nr][nc] || map[nr][nc] == 0) {
            continue;
        }

        dfs(nr, nc, visited_cnt);
    }

    return;
}

void melt() {
    vector<vector<int>> temp(N, vector<int>(M));

    for(int i = 0; i < ice.size(); ++i) {
        int r = ice[i].r;
        int c = ice[i].c;
        int h = ice[i].h;

        if(h == 0) {
            continue;
        }

        int sea = 0;
        for(int j = 0; j < 4; ++j) {
            if(map[r + dr[j]][c + dc[j]] == 0) {
                ++sea;
            }
        }

        temp[r][c] = max(0, h - sea);
        if (temp[r][c] > 0) {
            ice_idx = i;
        }
        else {
            --ice_cnt;
        }
    }

    map = temp;

    return;
}