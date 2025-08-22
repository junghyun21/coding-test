#include <iostream>
#include <vector>

using namespace std;

int main() {
    vector<int> coins;
    int N, K;
    
    cin >> N >> K;

    coins.resize(N);
    for(int i = 0; i < N; ++i) {
        cin >> coins[i];
    }

    // DP[i][j]: coins[i]의 코인을 포함할 수 있을 때, 가치가 j가 되는 경우의 수
    // 2차원 배열의 매커니즘을 1차원 배열에 두고, 이전 행의 값을 덮어씀
    vector<int> DP(K + 1);
    for(int i = 0; i <= K; i += coins[0]) {
        DP[i] = 1;
    }

    for(int i = 1; i < N; ++i) {
        for(int j = 0; j <= K; ++j) {
            int idx = j - coins[i];
            DP[j] += (idx < 0) ? 0 : DP[idx];
        }
    }
    
    cout << DP[K];

    return 0;
}