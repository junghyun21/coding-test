#include <vector>
#include <algorithm>

using namespace std;

int solution(vector<vector<int>> land)
{
    int n = land.size();
    vector<vector<int>> score(n, vector<int>(4));
    
    for(int i = 0; i < 4; ++i)
        score[0][i] = land[0][i];
    
    for(int i = 1; i < n; ++i) {
        for(int j = 0; j < 4; ++j) {
            int pre = 0;
            for(int k = 0; k < 4; ++k) {
                if(j == k) continue;
                pre = max(pre, score[i - 1][k]);
            }
            score[i][j] = land[i][j] + pre;
        }
    }

    return *max_element(score.back().begin(), score.back().end());
}