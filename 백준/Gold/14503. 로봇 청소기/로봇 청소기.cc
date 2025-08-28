#include <iostream>

using namespace std;

const int dr[] = {-1, 0, 1, 0};
const int dc[] = {0, 1, 0 ,-1};

int main() {
    bool map[52][52] = {0, };
    bool visited[52][52] = {0, };
    int cnt = 0;
    int N, M, r, c, d;

    cin >> N >> M;
    cin >> r >> c >> d;

    // 0: 벽, 1: 빈칸 (문제에서는 반대지만 편의를 위해 변경)
    bool tmp;
    for(int i = 1; i <= N; ++i) {
        for(int j = 1; j <= M; ++j) {
            cin >> tmp;
            map[i][j] = !tmp;
        }
    }

    ++r;
    ++c;

    while(true) {
        if(!visited[r][c]) {
            visited[r][c] = true;
            ++cnt;
        }
        
        bool moved = false;
        
        for(int i = 0; i < 4; ++i) {
            d = (d + 3) % 4;

            int new_r = r + dr[d];
            int new_c = c + dc[d];

            if(map[new_r][new_c] && !visited[new_r][new_c]) {
                moved = true;
                r = new_r;
                c = new_c;

                break;
            }
        }

        if(!moved) {
            r = r + dr[(d + 2) % 4];
            c = c + dc[(d + 2) % 4];

            if(!map[r][c]) {
                break;
            }   
        }
    }

    cout << cnt << endl;

    return 0;
}