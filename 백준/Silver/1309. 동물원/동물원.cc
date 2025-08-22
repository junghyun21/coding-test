#include <iostream>
#include <vector>

using namespace std;

const int MOD = 9901;

int main() {
    int n;
    cin >> n;
    
    // DP[i][0]: i열에 사자를 한 마리도 두지 않을 때
    // DP[i][1]: i열의 왼쪽에 사자가 있는 경우
    // DP[i][2]: i열의 오른쪽에 사자가 있는 경우
    vector<vector<int>> DP(n, vector<int>(3));
    DP[0][0] = 1;
    DP[0][1] = 1;
    DP[0][2] = 1;
    
    for(int i = 1; i < n; ++i) {
        int m_0 = DP[i - 1][0] % MOD;
        int m_1 = DP[i - 1][1] % MOD;
        int m_2 = DP[i - 1][2] % MOD;

        DP[i][0] = (m_0 + m_1 + m_2) % MOD;
        DP[i][1] = (m_0 + m_2) % MOD;
        DP[i][2] = (m_0 + m_1) % MOD;
    }

    cout << (DP[n - 1][0] + DP[n - 1][1] + DP[n - 1][2]) % MOD << endl;

    return 0;
}