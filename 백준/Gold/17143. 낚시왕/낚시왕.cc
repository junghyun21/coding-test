#include <iostream>
#include <vector>

using namespace std;

typedef struct shark {
    int r;
    int c;
    int s;
    int d;
    int z;
} Shark;

const int dr[] = {0, -1, 1, 0, 0};
const int dc[] = {0, 0, 0, 1, -1};

void moveShark(int R, int C, Shark &shark);

int main() {
    vector<vector<int>> map;    // shark의 idx
    vector<Shark> sharkInfo;    // shark의 정보 (0번 idx: dummy)
    int R, C, M;
    int ans = 0;

    cin >> R >> C >> M;

    map.resize(R + 1, vector<int>(C + 1));
    sharkInfo.resize(M + 1);
    for(int i = 1; i <= M; ++i) {
        cin >> sharkInfo[i].r >> sharkInfo[i].c >> sharkInfo[i].s >> sharkInfo[i].d >> sharkInfo[i].z;

        map[sharkInfo[i].r][sharkInfo[i].c] = i;
    }

    for(int i = 1; i <= C; ++i) {
        // 낚시꾼 이동 및 상어 포획
        for(int j = 1; j <= R; ++j) {
            if(map[j][i] == 0) {
                continue;
            }

            ans += sharkInfo[map[j][i]].z;

            sharkInfo[map[j][i]].z = -1;
            map[j][i] = 0;

            break;
        }

        // 상어 이동
        vector<vector<int>> nextMap(R + 1, vector<int>(C + 1));
        for(int j = 1; j <= M; ++j) {
            if(sharkInfo[j].z == -1) {
                continue;
            }

            moveShark(R, C, sharkInfo[j]);
            int newR = sharkInfo[j].r;
            int newC = sharkInfo[j].c;

            // 충돌 처리
            if(nextMap[newR][newC] == 0) {
                nextMap[newR][newC] = j;
            }
            else {
                int other = nextMap[newR][newC];

                if(sharkInfo[other].z > sharkInfo[j].z) {
                    sharkInfo[j].z = -1;
                }
                else {
                    sharkInfo[other].z = -1;
                    nextMap[newR][newC] = j;
                }
            }
        }

        map.swap(nextMap);
    }

    cout << ans << endl;

    return 0;
}

void moveShark(int R, int C, Shark &shark) {
    int move = shark.s;

    if(shark.d == 1 || shark.d == 2) {
        move %= (2 * (R - 1));  
    }
    else if(shark.d == 3 || shark.d == 4) {
        move %= (2 * (C - 1));   
    }

    while(move--) {
        // 상
        if(shark.d == 1) {
            if(shark.r == 1) {
                shark.d = 2;
            }
            shark.r += dr[shark.d];
        }
        // 하
        else if(shark.d == 2) {
            if(shark.r == R) {
                shark.d = 1;
            }
            shark.r += dr[shark.d];
        }
        // 우
        else if(shark.d == 3) {
            if(shark.c == C) {
                shark.d = 4;
            }
            shark.c += dc[shark.d];
        }
        // 좌
        else if(shark.d == 4) {
            if(shark.c == 1) {
                shark.d = 3;
            }
            shark.c += dc[shark.d];
        }
    }
}