#include <iostream>

using namespace std;

constexpr int MOD = 1000000000;

constexpr int MAX_N = 100;          // N이 가질 수 있는 최대 값
constexpr int NUM_DIGIT = 10;       // 1의 자리수에 들어갈 수 있는 숫자의 개수 (0~9)

int main() {
    int unitDigit[MAX_N + 1][NUM_DIGIT] = {0, };
    int ans = 0;
    int N;

    cin >> N;

    // 한 자리수인 경우
    for(int i = 1; i < NUM_DIGIT; ++i) {
        unitDigit[1][i] = 1;
    }

    // 두 자리수 이상인 경우
    for(int i = 2; i <= N; ++i) {
        for(int j = 0; j < NUM_DIGIT; ++j) {
            if(j != 0) {
                unitDigit[i][j - 1] = (unitDigit[i - 1][j] + unitDigit[i][j - 1]) % MOD;
            }

            if(j != 9) {
                unitDigit[i][j + 1] = (unitDigit[i - 1][j] + unitDigit[i][j + 1]) % MOD;
            }
        }
    }

    for(int u : unitDigit[N]) {
        ans = (ans + u) % MOD;
    }

    cout << ans << endl;

    return 0;
}