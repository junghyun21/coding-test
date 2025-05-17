#include <vector>

using namespace std;

int solution(vector<vector<int>> triangle) {
    vector<vector<int>> dp(triangle.size());
    
    dp[0].push_back(triangle[0][0]);
    
    for(int i = 1; i < triangle.size(); ++i) {
        dp[i].push_back(dp[i - 1][0] + triangle[i][0]);
        for(int j = 1; j < i; ++j)
            dp[i].push_back(max(dp[i - 1][j - 1], dp[i - 1][j]) + triangle[i][j]);
        dp[i].push_back(dp[i - 1][i - 1] + triangle[i][i]);
    }
    
    int answer = 0;
    for(const int &v : dp[triangle.size() - 1])
        answer = max(answer, v);
    
    return answer;
}