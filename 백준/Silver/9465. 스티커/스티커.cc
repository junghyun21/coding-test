#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    vector<int> res;
    int T, N;

    cin >> T;
    while(T--) {
        cin >> N;
        
        vector<vector<int>> score(2, vector<int>(N + 1));
        for(int i = 0; i < 2; ++i) {
            for(int j = 1; j <= N; ++j) {
                cin >> score[i][j];
            }
        }

        vector<vector<int>> DP(2, vector<int>(N + 1));
        DP[0][1] = score[0][1];
        DP[1][1] = score[1][1];

        for(int i = 2; i <= N; ++i) {
            DP[0][i] = max(DP[1][i - 1], max(DP[0][i - 2], DP[1][i - 2])) + score[0][i];
            DP[1][i] = max(DP[0][i - 1], max(DP[0][i - 2], DP[1][i - 2])) + score[1][i];
        }

        res.push_back(max(DP[0][N], DP[1][N]));
    }

    for(const int &r : res) {
        cout << r << endl;
    }

    return 0;
}