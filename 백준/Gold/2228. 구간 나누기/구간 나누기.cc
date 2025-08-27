#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;

const int MIN_NUM = numeric_limits<int>::min(); // 배열을 이루는 수들은 -32768 이상 32767 이하의 정수

int main() {
    int N, M;
    cin >> N >> M;
    
    vector<int> num;
    num.resize(N);

    for(int i = 0; i < N; ++i) {
        cin >> num[i];
    }

    // DP[i][j][k]: i번째 원소까지 고려해서 j개의 구간으로 나눈 최댓값
    // k=0: i번째 원소를 포함하지 않는 경우
    // k=1: i번째 원소를 포함한 경우
    vector<vector<vector<int>>> DP(N, vector<vector<int>>(M + 1, vector<int>(2, MIN_NUM)));
    DP[0][0][0] = 0;
    DP[0][0][1] = 0;
    DP[0][1][1] = num[0];

    for(int i = 1; i < N; ++i) {
        DP[i][0][0] = 0;
        DP[i][0][1] = MIN_NUM;

        int limit = min((i / M) + M, M + 1);

        for(int j = 1; j < limit; ++j) {
            if(DP[i - 1][j][0] == MIN_NUM || DP[i - 1][j][1] == MIN_NUM) {
                if(!(DP[i - 1][j][0] == MIN_NUM && DP[i - 1][j][1] == MIN_NUM)) {
                    DP[i][j][0] = (DP[i - 1][j][0] == MIN_NUM) ? DP[i - 1][j][1] : DP[i - 1][j][0];
                }
            }
            else {
                DP[i][j][0] = max(DP[i - 1][j][0], DP[i - 1][j][1]);
            }

            if(DP[i - 1][j - 1][0] == MIN_NUM || DP[i - 1][j][1] == MIN_NUM) {
                if(!(DP[i - 1][j - 1][0] == MIN_NUM && DP[i - 1][j][1] == MIN_NUM)) {
                    DP[i][j][1] = (DP[i - 1][j - 1][0] == MIN_NUM) ? DP[i - 1][j][1] : DP[i - 1][j - 1][0];
                    DP[i][j][1] += num[i];
                }
            }
            else {
                DP[i][j][1] = max(DP[i - 1][j - 1][0], DP[i - 1][j][1]) + num[i];
            }
        }
    }

    cout << max(DP[N - 1][M][0], DP[N - 1][M][1]) << endl;

    return 0;
}