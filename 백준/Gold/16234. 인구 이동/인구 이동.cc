#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int dr[] = {-1, 1, 0, 0};
const int dc[] = {0, 0, -1, 1};

vector<vector<int>> A;
vector<vector<bool>> visited;
vector<pair<int, int>> country;
int N, L, R;

void dfs(int r, int c);

int main() {
    cin >> N >> L >> R;

    A.resize(N, vector<int>(N));
    
    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < N; ++j) {
            cin >> A[i][j];
        }
    }

    bool moved = true;
    int days = 0;

    while(true) {
        vector<vector<int>> temp = A;
        
        visited.assign(N, vector<bool>(N));
        moved = false;

        for(int i = 0; i < N; ++i) {
            for(int j = 0; j < N; ++j) {
                if(visited[i][j]) {
                    continue;
                }

                dfs(i, j);

                if(country.size() > 1) {
                    int sum = 0;
                    for(const auto &c : country) {
                        sum += A[c.first][c.second];
                    }

                    int people = sum / country.size();
                    for(const auto &c : country) {
                        temp[c.first][c.second] = people;
                    }

                    moved = true;
                }
                
                country.clear();
            }
        }

        if(!moved) {
            break;
        }

        A = temp;
        ++days;
    }

    cout << days << endl;

    return 0;
}

void dfs(int r, int c) {
    visited[r][c] = true;
    country.push_back({r, c});

    for(int i = 0; i < 4; ++i) {
        int nr = r + dr[i];
        int nc = c + dc[i];

        if(nr < 0 || nr >= N || nc < 0 || nc >= N) {
            continue;
        }

        int max_people = max(A[r][c], A[nr][nc]);
        int min_people = min(A[r][c], A[nr][nc]);

        if(visited[nr][nc]) {
            continue;
        }

        if((max_people - min_people < L) || (max_people - min_people > R)) {
            continue;
        }

        dfs(nr, nc);
    }

    return;
}