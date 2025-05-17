#include <vector>

using namespace std;

const int MOD = 1000000007;

int solution(int n) {
    int answer = 0;
    vector<long long> dp(n + 1);
    
    dp[0] = 1;
    dp[2] = 3;
    
    if(n % 2 == 0) {
        for(int i = 4; i <= n; i += 2) {
            // dp[i] = ((dp[i - 2] * 3) + (dp[i - 4] * 2) + (dp[i - 2] - dp[i - 4] * 3)) % MOD;
            dp[i] = ((dp[i - 2] * 4) - dp[i - 4] + MOD) % MOD;
        }
        answer = (int)dp[n];
    }
    
    return answer;
}